#pragma once

#include <antlr4-runtime.h>
#include <numbers>
#include "ComputeFrame.hpp"
#include "fluxppBaseVisitor.h"
#include "diagnose/diagnostic_engine.hpp"
#include "diagnose/diagnostic_builder.hpp"
#include "immutable.hpp"
#include "ir_exec.hpp"
#include "ExprReturn.hpp"

namespace scripting::fluxpp {
    class Interpreter : public fluxppBaseVisitor {
    public:
        Interpreter(
            std::shared_ptr<df::DataFrame> df_,
            std::shared_ptr<DiagnosticEngine> engine_,
            const std::unordered_map<std::string, Immutable>& immutes)
            : df(std::move(df_)), engine(std::move(engine_)), immutables(immutes), n_rows(df->Rows())
        {
            generator = IRGenerator();
        }

        std::any visitSingle(fluxppParser::SingleContext *ctx) override {
            engine->report(scripting::fluxpp::ErrorCode::SEM002_ISOLATED_EXPRESSION)
            .at(ctx->expr())
            .expected("Isolated expressions are not allowed");
            return 0;
        }

        std::any visitAssignment(fluxppParser::AssignmentContext *ctx) override {
            const std::string id = ctx->ID()->getText();
            const auto& imm = immutables.at(id); // This should work. If it wasn't defined, static analyzer would've picked up.

            if (imm.is_used) {
                // Only generate expression if the value will be used
                const auto ret = visitExpr(ctx->expr());
                if (ret.isVector) {
                    immutables.at(id).loc = ret.location;
                }
                immutable_values.insert_or_assign(id, std::move(ret));
            }
            return 0;
        }

        std::any visitCreate(fluxppParser::CreateContext *ctx) override {
            const std::string id = ctx->ID()->getText();
            const uint16_t string_idx = generator.RegisterStringLiteral(id);
            const auto ret = visitExpr(ctx->expr());

            if (ret.isVector) {
                // If vector copy directly
                switch (ret.type) {
                    case Type::TBOOL:
                    case Type::TREAL:
                    case Type::TTIMESTAMP:
                        df->AddColumnSemantic(id, ret.type, ret.data);
                        break;
                    case Type::TSTRING:
                        engine->report(ErrorCode::TYP002_UNSUPPORTED_TYPE_FOR_OP)
                        .at(ctx->expr())
                        .what("STRING type is not supported when creating new columns")
                        .expected("An expression that evaluates to REAL, BOOL or TIMESTAMP");
                        break;
                    case Type::TNULL:
                        engine->report(ErrorCode::TYP002_UNSUPPORTED_TYPE_FOR_OP)
                        .at(ctx->expr())
                        .what("Expression evaluates to NULL")
                        .expected("An expression that evaluates to REAL, BOOL or TIMESTAMP");
                        break;
                }
                generator.emit_create(string_idx, ret.location);
            }
            else {
                // Broadcast the scalar
                switch (ret.type) {
                    case Type::TBOOL:
                    case Type::TREAL:
                    case Type::TTIMESTAMP:
                        df->AddColumnBroadcastSemantic(id, ret.type, ret.asRealScalar());
                        break;
                    case Type::TSTRING:
                        engine->report(ErrorCode::TYP002_UNSUPPORTED_TYPE_FOR_OP)
                        .at(ctx->expr())
                        .what("STRING type is not supported when creating new columns")
                        .expected("An expression that evaluates to REAL, BOOL or TIMESTAMP");
                        break;
                    case Type::TNULL:
                        engine->report(ErrorCode::TYP002_UNSUPPORTED_TYPE_FOR_OP)
                        .at(ctx->expr())
                        .what("Expression evaluates to NULL")
                        .expected("An expression that evaluates to REAL, BOOL or TIMESTAMP");
                        break;
                }
                const uint16_t litIdx = generator.RegisterLiteral(ret.asRealScalar(), ret.type);
                generator.emit_create(string_idx, litIdx);
            }
            return 0;
        }

        std::any visitFilter(fluxppParser::FilterContext *ctx) override;

        std::any visitDrop_row(fluxppParser::Drop_rowContext *ctx) override;

        std::any visitDrop_col(fluxppParser::Drop_colContext *ctx) override;

        std::any visitClamp(fluxppParser::ClampContext *ctx) override;

        std::any visitSet(fluxppParser::SetContext *ctx) override;

        std::any visitRename(fluxppParser::RenameContext *ctx) override;

        std::any visitFill(fluxppParser::FillContext *ctx) override;

        std::any visitAssert_statement(fluxppParser::Assert_statementContext *ctx) override;

        std::any visitTernary(fluxppParser::TernaryContext *ctx) override;

        std::any visitParens(fluxppParser::ParensContext *ctx) override {
            return visitExpr(ctx->expr());
        }

        std::any visitTime(fluxppParser::TimeContext *ctx) override {
            const std::string tstr = ctx->getText();
            const TimeStampAlignType ts = parse_time(tstr);
            ConstEval ret(Type::TTIMESTAMP);
            ret.SetTimeStamp(ts);
            return ret; // To avoid this copy when returning, TypedAlignedStorage will only store the pointer
        }

        std::any visitExponentiation(fluxppParser::ExponentiationContext *ctx) override {
            const auto left = visitExpr(ctx->left);
            const auto right = visitExpr(ctx->right);

            ConstEval ret(Type::TREAL);
            if (!left.isVector && !right.isVector) {
                // Constant
                ret.SetReal(std::pow(left.asRealScalar(), right.asRealScalar()));
                return ret;
            }
            if (left.isVector && !right.isVector) {
                // Right is constant
                const auto idx = generator.RegisterLiteral(right.asRealScalar(), Type::TREAL);
                const auto dest = generator.AllocateTemporary();
                generator.emit_pow(left.location, idx, dest);
                ret.SetAsVector(dest);
                return ret;
            }
            if (!left.isVector && right.isVector) {
                // Left is constant
                const auto idx = generator.RegisterLiteral(left.asRealScalar(), Type::TREAL);
                const auto dest = generator.AllocateTemporary();
                generator.emit_pow(idx, right.location, dest);
                ret.SetAsVector(dest);
                return ret;
            }
            const auto dest = generator.AllocateTemporary();
            generator.emit_pow(left.location, right.location, dest);
            ret.SetAsVector(dest);
            return ret;
        }

        std::any visitChainedComparisonAscending(fluxppParser::ChainedComparisonAscendingContext *ctx) override;

        std::any visitDateTime(fluxppParser::DateTimeContext *ctx) override {
            const std::string tstr = ctx->getText();
            const TimeStampAlignType ts = parse_datetime(tstr);
            ConstEval ret(Type::TTIMESTAMP);
            ret.SetTimeStamp(ts);
            return ret;
        }

        std::any visitDate(fluxppParser::DateContext *ctx) override {
            const std::string tstr = ctx->getText();
            const TimeStampAlignType ts = parse_date(tstr);
            ConstEval ret(Type::TTIMESTAMP);
            ret.SetTimeStamp(ts);
            return ret;
        }

        std::any visitLogicalOr(fluxppParser::LogicalOrContext *ctx) override {
            return visitBinaryOp(
                ctx->left,
                ctx->right,
                Type::TBOOL,
                [](const ConstEval& e) { return e.asBoolScalar();},
                [](const bool l, const bool r) {
                            ConstEval ret(Type::TBOOL);
                            ret.SetBool(l || r);
                            return ret;
                        },
                [&](auto l, auto r, auto d) { generator.emit_or(l, r, d); }
                );
        }

        std::any visitFalseLiteral(fluxppParser::FalseLiteralContext *ctx) override {
            ConstEval ret(Type::TBOOL);
            ret.SetBool(false);
            return ret;
        }

        std::any visitLogicalNot(fluxppParser::LogicalNotContext *ctx) override {
            const auto res = visitExpr(ctx->expr());
            ConstEval ret(Type::TBOOL);
            if (res.isVector) {
                const auto dest = generator.AllocateTemporary();
                generator.emit_not(res.location, dest);
                ret.SetAsVector(dest);
                return ret;
            }
            ret.SetBool(!res.asBoolScalar());
            return ret;
        }

        std::any visitChainedComparisonDescending(fluxppParser::ChainedComparisonDescendingContext *ctx) override;

        std::any visitMultiplicative(fluxppParser::MultiplicativeContext *ctx) override {
            if (ctx->op->getText() == "*") {
                return visitBinaryOp(
                    ctx->left,
                    ctx->right,
                    Type::TREAL,
                    [](const ConstEval& e) { return e.asRealScalar();},
                    [](const double l, const double r) {
                                ConstEval ret(Type::TREAL);
                                ret.SetBool(l * r);
                                return ret;
                            },
                    [&](auto l, auto r, auto d) { generator.emit_mul(l, r, d); }
                    );
            }
            return visitBinaryOp(
                ctx->left,
                ctx->right,
                Type::TREAL,
                [](const ConstEval& e) { return e.asRealScalar();},
                [](const double l, const double r) {
                    ConstEval ret(Type::TREAL);
                    ret.SetBool(l / r);
                    return ret;
                },
                [&](auto l, auto r, auto d) { generator.emit_div(l, r, d); }
            );
        }

        std::any visitAdditive(fluxppParser::AdditiveContext *ctx) override {
            const auto type = static_cast<Type>(ctx->type);
            const std::string op = ctx->op->getText();

            switch (type) {
                case Type::TREAL: {
                    if (op == "+") {
                        return visitBinaryOp(
                             ctx->left,
                             ctx->right,
                             Type::TREAL,
                             [](const ConstEval& e) { return e.asRealScalar();},
                             [](const double l, const double r) {
                                 ConstEval ret(Type::TREAL);
                                 ret.SetReal(l + r);
                                 return ret;
                             },
                             [&](auto l, auto r, auto d) { generator.emit_add(Type::TREAL,l, r, d); }
                        );
                    }
                    return visitBinaryOp(
                             ctx->left,
                             ctx->right,
                             Type::TREAL,
                             [](const ConstEval& e) { return e.asRealScalar();},
                             [](const double l, const double r) {
                                 ConstEval ret(Type::TREAL);
                                 ret.SetReal(l - r);
                                 return ret;
                             },
                             [&](auto l, auto r, auto d) { generator.emit_sub(Type::TREAL,l, r, d); }
                        );
                }
                case Type::TTIMESTAMP: {
                    if (op == "+") {
                        return visitBinaryOp(
                             ctx->left,
                             ctx->right,
                             Type::TTIMESTAMP,
                             [](const ConstEval& e) { return e.asTimeStampScalar();},
                             [](const TimeStampAlignType l, const TimeStampAlignType r) {
                                 ConstEval ret(Type::TTIMESTAMP);
                                 ret.SetTimeStamp(l + r);
                                 return ret;
                             },
                             [&](auto l, auto r, auto d) { generator.emit_add(Type::TTIMESTAMP,l, r, d); }
                        );
                    }
                    return visitBinaryOp(
                             ctx->left,
                             ctx->right,
                             Type::TTIMESTAMP,
                             [](const ConstEval& e) { return e.asTimeStampScalar();},
                             [](const TimeStampAlignType l, const TimeStampAlignType r) {
                                 ConstEval ret(Type::TTIMESTAMP);
                                 ret.SetTimeStamp(l - r);
                                 return ret;
                             },
                             [&](auto l, auto r, auto d) { generator.emit_sub(Type::TTIMESTAMP, l, r, d); }
                        );
                }
                default:
                    return 0;
            }
        }

        std::any visitAbs(fluxppParser::AbsContext *ctx) override {
            const auto res = visitExpr(ctx->expr());
            ConstEval ret(Type::TREAL);
            if (res.isVector) {
                const auto dest = generator.AllocateTemporary();
                generator.emit_abs(res.location, dest);
                ret.SetAsVector(dest);
                return ret;
            }
            ret.SetReal(std::abs(res.asRealScalar()));
            return ret;
        }

        std::any visitIdentifier(fluxppParser::IdentifierContext *ctx) override {
            const auto id = ctx->ID()->getText();
            if (df->HasColumn(id)) {
                const auto col_idx = df->ColIdx(id);
                const auto& meta = df->Meta(col_idx);
                ConstEval ret(meta.type);
                ret.SetAsVector(col_idx);
                return ret;
            }
            if (immutables.contains(id)) {
                const auto& imm = immutable_values.at(id);
                ConstEval ret(imm.type);
                ret.SetAsVector(imm.location);
                return ret;
            }
            if (id == "e") {
                ConstEval ret(Type::TREAL);
                ret.SetReal(std::numbers::e_v<double>);
                return ret;
            }
            if (id == "pi") {
                ConstEval ret(Type::TREAL);
                ret.SetReal(std::numbers::pi_v<double>);
                return ret;
            }
            engine->report(ErrorCode::REF004_UNKNOWN_VARIABLE_OR_COLUMN)
            .at(ctx->ID()->getSymbol())
            .what("Unknown symbol encountered");
            return 0;
        }

        std::any visitNumber(fluxppParser::NumberContext *ctx) override {
            ConstEval ret(Type::TREAL);
            ret.SetReal(std::stod(ctx->NUMBER()->getText()));
            return ret;
        }

        std::any visitStringLiteral(fluxppParser::StringLiteralContext *ctx) override {
            ConstEval ret(Type::TSTRING);
            const auto str_idx = generator.RegisterStringLiteral(ctx->STRING_LITERAL()->getText());
            const auto lit_idx = generator.RegisterLiteral(str_idx, Type::TSTRING);
            ret.SetStringIndex(lit_idx);
            return ret;
        }

        std::any visitTrueLiteral(fluxppParser::TrueLiteralContext *ctx) override {
            ConstEval ret(Type::TBOOL);
            ret.SetBool(false);
            return ret;
        }

        std::any visitComparison(fluxppParser::ComparisonContext *ctx) override {
            const auto type = static_cast<Type>(ctx->type);
            const std::string op = ctx->op->getText();

            switch (type) {
                case Type::TBOOL: {
                    if (op == "==") {
                        return visitBinaryOp(
                             ctx->left,
                             ctx->right,
                             Type::TBOOL,
                             [](const ConstEval& e) { return e.asBoolScalar();},
                             [](const bool l, const bool r) {
                                 ConstEval ret(Type::TBOOL);
                                 ret.SetBool(l == r);
                                 return ret;
                             },
                             [&](auto l, auto r, auto d) { generator.emit_eq(Type::TBOOL,l, r, d); }
                         );
                    }
                    if (op == "!=") {
                        return visitBinaryOp(
                             ctx->left,
                             ctx->right,
                             Type::TBOOL,
                             [](const ConstEval& e) { return e.asBoolScalar();},
                             [](const bool l, const bool r) {
                                 ConstEval ret(Type::TBOOL);
                                 ret.SetBool(l != r);
                                 return ret;
                             },
                             [&](auto l, auto r, auto d) { generator.emit_neq(Type::TBOOL,l, r, d); }
                        );
                    }
                }
                case Type::TREAL: {
                    if (op == "==") {
                        return visitBinaryOp(
                             ctx->left,
                             ctx->right,
                             Type::TBOOL,
                             [](const ConstEval& e) { return e.asRealScalar();},
                             [](const double l, const double r) {
                                 ConstEval ret(Type::TBOOL);
                                 ret.SetBool(l == r);
                                 return ret;
                             },
                             [&](auto l, auto r, auto d) { generator.emit_neq(Type::TREAL,l, r, d); }
                        );
                    }
                    return visitBinaryOp(
                             ctx->left,
                             ctx->right,
                             Type::TBOOL,
                             [](const ConstEval& e) { return e.asRealScalar();},
                             [](const double l, const double r) {
                                 ConstEval ret(Type::TBOOL);
                                 ret.SetBool(l != r);
                                 return ret;
                             },
                             [&](auto l, auto r, auto d) { generator.emit_neq(Type::TREAL,l, r, d); }
                        );
                }
                case Type::TTIMESTAMP: {
                    if (op == "==") {
                        return visitBinaryOp(
                             ctx->left,
                             ctx->right,
                             Type::TBOOL,
                             [](const ConstEval& e) { return e.asTimeStampScalar();},
                             [](const TimeStampAlignType l, const TimeStampAlignType r) {
                                 ConstEval ret(Type::TBOOL);
                                 ret.SetBool(l == r);
                                 return ret;
                             },
                             [&](auto l, auto r, auto d) { generator.emit_neq(Type::TTIMESTAMP,l, r, d); }
                        );
                    }
                    return visitBinaryOp(
                             ctx->left,
                             ctx->right,
                             Type::TBOOL,
                             [](const ConstEval& e) { return e.asTimeStampScalar();},
                             [](const TimeStampAlignType l, const TimeStampAlignType r) {
                                 ConstEval ret(Type::TBOOL);
                                 ret.SetBool(l != r);
                                 return ret;
                             },
                             [&](auto l, auto r, auto d) { generator.emit_neq(Type::TTIMESTAMP,l, r, d); }
                        );
                }
                case Type::TSTRING: {
                    if (op == "==") {
                        return visitBinaryOp(
                             ctx->left,
                             ctx->right,
                             Type::TBOOL,
                             [](const ConstEval& e) { return e.asIntScalar();},
                             [](const int64_t l, const int64_t r) {
                                 ConstEval ret(Type::TBOOL);
                                 ret.SetBool(l == r);
                                 return ret;
                             },
                             [&](auto l, auto r, auto d) { generator.emit_neq(Type::TSTRING,l, r, d); }
                        );
                    }
                    return visitBinaryOp(
                             ctx->left,
                             ctx->right,
                             Type::TBOOL,
                             [](const ConstEval& e) { return e.asIntScalar();},
                             [](const int64_t l, const int64_t r) {
                                 ConstEval ret(Type::TBOOL);
                                 ret.SetBool(l != r);
                                 return ret;
                             },
                             [&](auto l, auto r, auto d) { generator.emit_neq(Type::TSTRING,l, r, d); }
                        );
                }
                default:
                    return 0;
            }
        }

        std::any visitLessInequal(fluxppParser::LessInequalContext *ctx) override {
            const auto type = static_cast<Type>(ctx->type);
            const std::string op = ctx->op->getText();

            switch (type) {
                case Type::TREAL: {
                    if (op == "<") {
                        return visitBinaryOp(
                             ctx->left,
                             ctx->right,
                             Type::TBOOL,
                             [](const ConstEval& e) { return e.asRealScalar();},
                             [](const double l, const double r) {
                                 ConstEval ret(Type::TBOOL);
                                 ret.SetBool(l < r);
                                 return ret;
                             },
                             [&](auto l, auto r, auto d) { generator.emit_ieq(Type::TREAL, LT,l, r, d); }
                        );
                    }
                    return visitBinaryOp(
                             ctx->left,
                             ctx->right,
                             Type::TBOOL,
                             [](const ConstEval& e) { return e.asRealScalar();},
                             [](const double l, const double r) {
                                 ConstEval ret(Type::TBOOL);
                                 ret.SetBool(l <= r);
                                 return ret;
                             },
                             [&](auto l, auto r, auto d) { generator.emit_ieq(Type::TREAL, LTE,l, r, d); }
                        );
                }
                case Type::TTIMESTAMP: {
                    if (op == "<") {
                        return visitBinaryOp(
                             ctx->left,
                             ctx->right,
                             Type::TBOOL,
                             [](const ConstEval& e) { return e.asTimeStampScalar();},
                             [](const TimeStampAlignType l, const TimeStampAlignType r) {
                                 ConstEval ret(Type::TBOOL);
                                 ret.SetBool(l < r);
                                 return ret;
                             },
                             [&](auto l, auto r, auto d) { generator.emit_ieq(Type::TTIMESTAMP, LT,l, r, d); }
                        );
                    }
                    return visitBinaryOp(
                             ctx->left,
                             ctx->right,
                             Type::TBOOL,
                             [](const ConstEval& e) { return e.asTimeStampScalar();},
                             [](const TimeStampAlignType l, const TimeStampAlignType r) {
                                 ConstEval ret(Type::TBOOL);
                                 ret.SetBool(l <= r);
                                 return ret;
                             },
                             [&](auto l, auto r, auto d) { generator.emit_ieq(Type::TTIMESTAMP, LTE,l, r, d); }
                        );
                }
                default:
                    return 0;
            }
        }

        std::any visitGreaterInequal(fluxppParser::GreaterInequalContext *ctx) override {
            const auto type = static_cast<Type>(ctx->type);
            const std::string op = ctx->op->getText();

            switch (type) {
                case Type::TREAL: {
                    if (op == ">") {
                        return visitBinaryOp(
                             ctx->left,
                             ctx->right,
                             Type::TBOOL,
                             [](const ConstEval& e) { return e.asRealScalar();},
                             [](const double l, const double r) {
                                 ConstEval ret(Type::TBOOL);
                                 ret.SetBool(l > r);
                                 return ret;
                             },
                             [&](auto l, auto r, auto d) { generator.emit_ieq(Type::TREAL, GT,l, r, d); }
                        );
                    }
                    return visitBinaryOp(
                             ctx->left,
                             ctx->right,
                             Type::TBOOL,
                             [](const ConstEval& e) { return e.asRealScalar();},
                             [](const double l, const double r) {
                                 ConstEval ret(Type::TBOOL);
                                 ret.SetBool(l >= r);
                                 return ret;
                             },
                             [&](auto l, auto r, auto d) { generator.emit_ieq(Type::TREAL, GTE,l, r, d); }
                        );
                }
                case Type::TTIMESTAMP: {
                    if (op == ">") {
                        return visitBinaryOp(
                             ctx->left,
                             ctx->right,
                             Type::TBOOL,
                             [](const ConstEval& e) { return e.asTimeStampScalar();},
                             [](const TimeStampAlignType l, const TimeStampAlignType r) {
                                 ConstEval ret(Type::TBOOL);
                                 ret.SetBool(l > r);
                                 return ret;
                             },
                             [&](auto l, auto r, auto d) { generator.emit_ieq(Type::TTIMESTAMP, GT,l, r, d); }
                        );
                    }
                    return visitBinaryOp(
                             ctx->left,
                             ctx->right,
                             Type::TBOOL,
                             [](const ConstEval& e) { return e.asTimeStampScalar();},
                             [](const TimeStampAlignType l, const TimeStampAlignType r) {
                                 ConstEval ret(Type::TBOOL);
                                 ret.SetBool(l >= r);
                                 return ret;
                             },
                             [&](auto l, auto r, auto d) { generator.emit_ieq(Type::TTIMESTAMP, GTE,l, r, d); }
                        );
                }
                default:
                    return 0;
            }
        }

        std::any visitLogicalAnd(fluxppParser::LogicalAndContext *ctx) override {
            return visitBinaryOp(
                ctx->left,
                ctx->right,
                Type::TBOOL,
                [](const ConstEval& e) { return e.asBoolScalar();},
                [](const bool l, const bool r) {
                            ConstEval ret(Type::TBOOL);
                            ret.SetBool(l && r);
                            return ret;
                        },
                [&](auto l, auto r, auto d) { generator.emit_and(l, r, d); }
                );
        }

        std::any visitFunctionCall(fluxppParser::FunctionCallContext *ctx) override {
            const auto id = ctx->ID()->getText();
            const auto fn = get_fn_index(id);
            if (fn.fnt == REDUCE) {
                generator.set_gen_to_remove();
                visit(ctx->args());
                constexpr double LITERAL_TO_FILL = std::bit_cast<double>(0xFFFFFFFFFFFFFFFF);
                const auto lit_to_fill = generator.RegisterLiteral(LITERAL_TO_FILL, Type::TREAL);
                generator.emit_call_reduce(fn.index, lit_to_fill);
                generator.set_gen_to_keep();
                ConstEval ret(Type::TREAL);
                ret.SetAsVector(lit_to_fill);
                return ret;
            }
            const auto isScalar = std::any_cast<bool>(visit(ctx->args()));
            if (fn.fnt == PASS && isScalar) {
                const auto value = resolve_scalar_function_scalar(arg_array_, fn.index);
                ConstEval ret(Type::TREAL);
                ret.SetReal(value);
                return ret;
            }
            const auto dest = generator.AllocateTemporary();
            generator.emit_call(fn.index, dest);
            ConstEval ret(Type::TREAL);
            ret.SetAsVector(dest);
            return ret;
        }

        std::any visitNegate(fluxppParser::NegateContext *ctx) override {
            const auto res = visitExpr(ctx->expr());
            ConstEval ret(Type::TREAL);
            if (res.isVector) {
                const auto dest = generator.AllocateTemporary();
                generator.emit_neg(res.location, dest);
                ret.SetAsVector(dest);
                return ret;
            }
            ret.SetReal(-res.asRealScalar());
            return ret;
        }

        std::any visitNullLiteral(fluxppParser::NullLiteralContext *ctx) override {
            engine->report(ErrorCode::SEM001_ASSERT_FAILED)
            .at(ctx)
            .what("Encountered null literal");
            return 0;
        }

        std::any visitArgs(fluxppParser::ArgsContext *ctx) override {
            bool isAnyVector = false;
            std::vector<ConstEval> results;
            uint16_t arg_idx = 0;
            for (auto* argp : ctx->expr()) {
                const auto res = visitExpr(argp);
                if (res.isVector) {
                    isAnyVector = true;
                }
                results.push_back(res);
            }
            for (const auto& res : results) {
                if (isAnyVector) {
                    if (res.isVector) {
                        generator.emit_load_vector_arg(res.location, arg_idx);
                    }
                    else {
                        const auto lit_idx = generator.RegisterLiteral(res.asRealScalar(), res.type);
                        const auto dest = generator.AllocateTemporary();
                        generator.emit_broadcast(lit_idx, dest);
                        generator.emit_load_vector_arg(dest, arg_idx);
                    }
                }
                else {
                    const auto lit_idx = generator.RegisterLiteral(res.asRealScalar(), res.type);
                    generator.emit_load_scalar_arg(lit_idx, arg_idx);
                    arg_array_[arg_idx] = res.asRealScalar();
                }
                ++arg_idx;
            }
            return !isAnyVector;
        }

        ConstEval visitExpr(fluxppParser::ExprContext* ctx) {
            return std::any_cast<ConstEval>(visit(ctx));
        }
    private:
        std::shared_ptr<df::DataFrame> df;
        std::shared_ptr<DiagnosticEngine> engine;
        std::unordered_map<std::string, Immutable> immutables;
        std::unordered_map<std::string, ConstEval> immutable_values;
        ArgArray arg_array_ {};
        IRGenerator generator;
        size_t n_rows;


        template<typename GetScalar, typename ScalarOp, typename EmitOp>
        ConstEval visitBinaryOp(
            fluxppParser::ExprContext* leftCtx,
            fluxppParser::ExprContext* rightCtx,
            const Type resultType,
            GetScalar getScalar,  // (const ConstEval&) -> scalar_type
            ScalarOp scalarOp,    // (scalar, scalar)   -> ConstEval
            EmitOp emitOp)        // (loc, loc, dest)   -> void
        {
            const auto left  = visitExpr(leftCtx);
            const auto right = visitExpr(rightCtx);

            if (!left.isVector && !right.isVector)
                return scalarOp(getScalar(left), getScalar(right));

            auto toLoc = [&](const ConstEval& e) {
                return e.isVector
                    ? e.location
                    : generator.RegisterLiteral(getScalar(e), resultType);
            };

            ConstEval ret(resultType);
            const auto dest = generator.AllocateTemporary();
            emitOp(toLoc(left), toLoc(right), dest);
            ret.SetAsVector(dest);
            return ret;
        }
    };
}

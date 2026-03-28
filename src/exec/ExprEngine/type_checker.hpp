#pragma once

#include <format>
#include <types.hpp>
#include <antlr/antlr4-runtime.h>
#include "exprEngineParserBaseVisitor.h"
#include "../ComputeGraph/ComputeSchema.hpp"
#include "diagnostic_builder.hpp"
#include "diagnostic_engine.hpp"
#include "ref.hpp"

namespace exec::expr {

    struct Identifier {
        std::string name;
        Type type;
    };

    struct ExprReturn {
        Type type;
        bool isVector;
    };

    class TypeChecker : public exprEngineParserBaseVisitor {
    public:
        explicit TypeChecker(BoxRef<DiagnosticEngine> engine) : engine(std::move(engine)) {}
        ExprReturn visitExpr(exprEngineParser::ExprContext *ctx) {
            return std::any_cast<ExprReturn>(visit(ctx));
        }

        std::any visitAggregateOver(exprEngineParser::AggregateOverContext *ctx) override {
            const auto [name, type] = std::any_cast<Identifier>(visit(ctx->identifier()));

            if (const auto& col = schema.getColumnSchema(name); col.getType() == TREAL) {
                engine->report(ErrorCode::E201_TYPE_MISMATCH)
                .what("Aggregate functions cannot be applied OVER REAL columns")
                .at(ctx)
                .expected("Column of type INT, BOOL, STRING, or TIMESTAMP")
                .found(std::format("Column '{}' of type REAL", name));
            }
            visit(ctx->aggregateFn());
            return 0;
        }

        std::any visitExprNot(exprEngineParser::ExprNotContext *ctx) override {
            const auto res = visitExpr(ctx->expr());
            if (res.type != TBOOL) {
                engine->report(ErrorCode::E205_UNARY_OPERAND_MISMATCH)
                .what("Logical NOT operator requires a boolean operand")
                .at(ctx)
                .found(std::format("Operand of type {}", typeName(res.type)));
                return 0;
            }
            return ExprReturn(TBOOL, res.isVector);
        }

        std::any visitExprNegate(exprEngineParser::ExprNegateContext *ctx) override {
            const auto res = visitExpr(ctx->expr());
            if (res.type != TREAL && res.type != TINT) {
                engine->report(ErrorCode::E205_UNARY_OPERAND_MISMATCH)
                .what("Unary negation operator requires an integer or real operand")
                .at(ctx)
                .found(std::format("Operand of type {}", typeName(res.type)));
                return 0;
            }
            return ExprReturn(res.type, res.isVector);
        }

        std::any visitExprDiv(exprEngineParser::ExprDivContext *ctx) override {
            const auto left = visitExpr(ctx->left);
            const auto right = visitExpr(ctx->right);
            if (left.type == TINT || right.type == TINT) {
                engine->report(ErrorCode::E902_IMPCAST_WIDENING_WARNING)
                .what("Implicit cast applied. Integer to Real")
                .at(ctx);
            }
            if (left.type != TREAL && left.type != TINT && right.type != TREAL && right.type != TINT) {
                engine->report(ErrorCode::E205_UNARY_OPERAND_MISMATCH)
                .what("Division operator requires numeric operands")
                .at(ctx)
                .found(std::format("Left operand of type {}, right operand of type {}", typeName(left.type), typeName(right.type)));
                return 0;
            }
            return ExprReturn(TREAL, left.isVector || right.isVector); // Broadcast applied
        }

        std::any visitExprAbs(exprEngineParser::ExprAbsContext *ctx) override {
            const auto res = visitExpr(ctx->expr());
            if (res.type != TREAL && res.type != TINT) {
                engine->report(ErrorCode::E205_UNARY_OPERAND_MISMATCH)
                .what("Absolute value operator requires an integer or real operand")
                .at(ctx)
                .found(std::format("Operand of type {}", typeName(res.type)));
                return 0;
            }
            return ExprReturn(res.type, res.isVector);
        }

        std::any visitExprEq(exprEngineParser::ExprEqContext *ctx) override {
            const auto left = visitExpr(ctx->left);
            const auto right = visitExpr(ctx->right);
            if (left.type != right.type) {
                engine->report(ErrorCode::E204_BINARY_OPERAND_MISMATCH)
                .what("Equality operator requires operands of the same type")
                .at(ctx)
                .found(std::format("Left operand of type {}, right operand of type {}", typeName(left.type), typeName(right.type)));
                return 0;
            }
            return ExprReturn(TBOOL, left.isVector || right.isVector); // Broadcast applied
        }

        std::any visitExprGt(exprEngineParser::ExprGtContext *ctx) override {
            const auto left = visitExpr(ctx->left);
            const auto right = visitExpr(ctx->right);
            if (left.type != right.type) {
                engine->report(ErrorCode::E204_BINARY_OPERAND_MISMATCH)
                .what("Greater Than operator requires operands of the same type")
                .at(ctx)
                .found(std::format("Left operand of type {}, right operand of type {}", typeName(left.type), typeName(right.type)));
                return 0;
            }
            return ExprReturn(TBOOL, left.isVector || right.isVector); // Broadcast applied
        }

        std::any visitExprLiteral(exprEngineParser::ExprLiteralContext *ctx) override {
            return visit(ctx->literal());
        }

        std::any visitExprParen(exprEngineParser::ExprParenContext *ctx) override {
            return visitExpr(ctx->expr());
        }

        std::any visitExprSub(exprEngineParser::ExprSubContext *ctx) override {
            const auto left = visitExpr(ctx->left);
            const auto right = visitExpr(ctx->right);
            if (left.type == TINT || right.type == TINT) {
                engine->report(ErrorCode::E902_IMPCAST_WIDENING_WARNING)
                .what("Implicit cast applied. Integer to Real")
                .at(ctx);
            }
            if (left.type != TREAL && left.type != TINT && right.type != TREAL && right.type != TINT) {
                engine->report(ErrorCode::E205_UNARY_OPERAND_MISMATCH)
                .what("Subtraction operator requires numeric operands")
                .at(ctx)
                .found(std::format("Left operand of type {}, right operand of type {}", typeName(left.type), typeName(right.type)));
                return 0;
            }
            const Type rt = left.type == TREAL || right.type == TREAL ? TREAL : TINT; // Always promotes (1.5 - 1 => 1.0 (real))
            return ExprReturn(rt, left.isVector || right.isVector); // Broadcast applied
        }

        std::any visitExprOr(exprEngineParser::ExprOrContext *ctx) override {
            const auto left = visitExpr(ctx->left);
            const auto right = visitExpr(ctx->right);
            if (left.type != TBOOL && right.type != TBOOL) {
                engine->report(ErrorCode::E205_UNARY_OPERAND_MISMATCH)
                .what("Logical OR operator requires boolean operands")
                .at(ctx)
                .found(std::format("Left operand of type {}, right operand of type {}", typeName(left.type), typeName(right.type)));
                return 0;
            }
            return ExprReturn(TBOOL, left.isVector || right.isVector); // Broadcast applied
        }

        std::any visitExprExp(exprEngineParser::ExprExpContext *ctx) override {
            const auto left = visitExpr(ctx->left);
            const auto right = visitExpr(ctx->right);
            if (left.type == TINT || right.type == TINT) {
                engine->report(ErrorCode::E902_IMPCAST_WIDENING_WARNING)
                .what("Implicit cast applied. Integer to Real")
                .at(ctx);
            }
            if (left.type != TREAL && left.type != TINT && right.type != TREAL && right.type != TINT) {
                engine->report(ErrorCode::E205_UNARY_OPERAND_MISMATCH)
                .what("Exponentiation operator requires numeric operands")
                .at(ctx)
                .found(std::format("Left operand of type {}, right operand of type {}", typeName(left.type), typeName(right.type)));
                return 0;
            }

            return ExprReturn(TREAL, left.isVector || right.isVector); // Broadcast applied, Always real
        }

        std::any visitExprLte(exprEngineParser::ExprLteContext *ctx) override {
            const auto left = visitExpr(ctx->left);
            const auto right = visitExpr(ctx->right);
            if (left.type != right.type) {
                engine->report(ErrorCode::E204_BINARY_OPERAND_MISMATCH)
                .what("Less Than or Equal To (<=) operator requires operands of the same type")
                .at(ctx)
                .found(std::format("Left operand of type {}, right operand of type {}", typeName(left.type), typeName(right.type)));
                return 0;
            }
            if (!canCompareType(left.type) || !canCompareType(right.type)) {
                engine->report(ErrorCode::E301_UNSUPPORTED_OPERATION)
                .what("Comparison operators are not supported for BOOL or STRING types")
                .at(ctx)
                .found(std::format("Left operand of type {}, right operand of type {}", typeName(left.type), typeName(right.type)));
                return 0;
            }
            return ExprReturn(TBOOL, left.isVector || right.isVector); // Broadcast applied
        }

        std::any visitExprCall(exprEngineParser::ExprCallContext *ctx) override {
            return visit(ctx->functionCall());
        }

        std::any visitExprLt(exprEngineParser::ExprLtContext *ctx) override {
            const auto left = visitExpr(ctx->left);
            const auto right = visitExpr(ctx->right);
            if (left.type != right.type) {
                engine->report(ErrorCode::E204_BINARY_OPERAND_MISMATCH)
                .what("Less Than (<) operator requires operands of the same type")
                .at(ctx)
                .found(std::format("Left operand of type {}, right operand of type {}", typeName(left.type), typeName(right.type)));
                return 0;
            }
            if (!canCompareType(left.type) || !canCompareType(right.type)) {
                engine->report(ErrorCode::E301_UNSUPPORTED_OPERATION)
                .what("Comparison operators are not supported for BOOL or STRING types")
                .at(ctx)
                .found(std::format("Left operand of type {}, right operand of type {}", typeName(left.type), typeName(right.type)));
                return 0;
            }
            return ExprReturn(TBOOL, left.isVector || right.isVector); // Broadcast applied
        }

        std::any visitExprMul(exprEngineParser::ExprMulContext *ctx) override {
            const auto left = visitExpr(ctx->left);
            const auto right = visitExpr(ctx->right);
            if (shouldCast(left.type, right.type)) {
                engine->report(ErrorCode::E902_IMPCAST_WIDENING_WARNING)
                .what("Implicit cast applied. Integer to Real")
                .at(ctx);
            }
            if (left.type != TREAL && left.type != TINT && right.type != TREAL && right.type != TINT) {
                engine->report(ErrorCode::E205_UNARY_OPERAND_MISMATCH)
                .what("Multiplication operator requires numeric operands")
                .at(ctx)
                .found(std::format("Left operand of type {}, right operand of type {}", typeName(left.type), typeName(right.type)));
                return 0;
            }
            const Type rt = left.type == TREAL || right.type == TREAL ? TREAL : TINT; // Always promotes (1.5 - 1 => 1.0 (real))
            return ExprReturn(rt, left.isVector || right.isVector); // Broadcast applied
        }

        std::any visitExprAdd(exprEngineParser::ExprAddContext *ctx) override {
            const auto left = visitExpr(ctx->left);
            const auto right = visitExpr(ctx->right);
            if (shouldCast(left.type, right.type)) {
                engine->report(ErrorCode::E902_IMPCAST_WIDENING_WARNING)
                .what("Implicit cast applied. Integer to Real")
                .at(ctx);
            }
            if (!isNumeric(left.type) || !isNumeric(right.type)) {
                engine->report(ErrorCode::E205_UNARY_OPERAND_MISMATCH)
                .what("Addition operator requires numeric operands")
                .at(ctx)
                .found(std::format("Left operand of type {}, right operand of type {}", typeName(left.type), typeName(right.type)));
                return 0;
            }
            const Type rt = left.type == TREAL || right.type == TREAL ? TREAL : TINT; // Always promotes (1.5 - 1 => 1.0 (real))
            return ExprReturn(rt, left.isVector || right.isVector); // Broadcast applied
        }

        std::any visitExprMod(exprEngineParser::ExprModContext *ctx) override {
            const auto left = visitExpr(ctx->left);
            const auto right = visitExpr(ctx->right);
            if (!isNumeric(left.type) && right.type != TINT) {
                engine->report(ErrorCode::E205_UNARY_OPERAND_MISMATCH)
                .what("Modulo operator requires integer operands")
                .at(ctx)
                .found(std::format("Left operand of type {}, right operand of type {}", typeName(left.type), typeName(right.type)));
                return 0;
            }
            if (left.type == TREAL) {
                engine->report(ErrorCode::E901_IMPCAST_PREC_LOSS_WARNING)
                .what("Implicit cast from REAL to INTEGER. Precision maybe lost")
                .at(ctx);
            }
            return ExprReturn(TINT, left.isVector || right.isVector); // Broadcast applied
        }

        std::any visitExprAnd(exprEngineParser::ExprAndContext *ctx) override {
            const auto left = visitExpr(ctx->left);
            const auto right = visitExpr(ctx->right);
            if (left.type != TBOOL && right.type != TBOOL) {
                engine->report(ErrorCode::E205_UNARY_OPERAND_MISMATCH)
                .what("Logical AND operator requires boolean operands")
                .at(ctx)
                .found(std::format("Left operand of type {}, right operand of type {}", typeName(left.type), typeName(right.type)));
                return 0;
            }
            return ExprReturn(TBOOL, left.isVector || right.isVector); // Broadcast applied
        }

        std::any visitExprGte(exprEngineParser::ExprGteContext *ctx) override {
            const auto left = visitExpr(ctx->left);
            const auto right = visitExpr(ctx->right);
            if (left.type != right.type) {
                engine->report(ErrorCode::E204_BINARY_OPERAND_MISMATCH)
                .what("Greater Than or Equal To (>=) operator requires operands of the same type")
                .at(ctx)
                .found(std::format("Left operand of type {}, right operand of type {}", typeName(left.type), typeName(right.type)));
                return 0;
            }
            if (!canCompareType(left.type) || !canCompareType(right.type)) {
                engine->report(ErrorCode::E301_UNSUPPORTED_OPERATION)
                .what("Comparison operators are not supported for BOOL or STRING types")
                .at(ctx)
                .found(std::format("Left operand of type {}, right operand of type {}", typeName(left.type), typeName(right.type)));
                return 0;
            }
            return ExprReturn(TBOOL, left.isVector || right.isVector); // Broadcast applied
        }

        std::any visitExprIntDiv(exprEngineParser::ExprIntDivContext *ctx) override {
            const auto left = visitExpr(ctx->left);
            const auto right = visitExpr(ctx->right);
            if (left.type != TINT && right.type != TINT) {
                engine->report(ErrorCode::E205_UNARY_OPERAND_MISMATCH)
                .what("Integer division operator requires integer operands")
                .at(ctx)
                .found(std::format("Left operand of type {}, right operand of type {}", typeName(left.type), typeName(right.type)));
                return 0;
            }
            return ExprReturn(TINT, left.isVector || right.isVector); // Broadcast applied
        }

        std::any visitExprIndentifier(exprEngineParser::ExprIndentifierContext *ctx) override {
            const auto id = std::any_cast<Identifier>(visit(ctx->identifier()));
            return ExprReturn(id.type, true); // Identifiers always refer to vectors (columns)
        }

        std::any visitExprNeq(exprEngineParser::ExprNeqContext *ctx) override {
            const auto left = visitExpr(ctx->left);
            const auto right = visitExpr(ctx->right);
            if (left.type != right.type) {
                engine->report(ErrorCode::E204_BINARY_OPERAND_MISMATCH)
                .what("Not Equal operator requires operands of the same type")
                .at(ctx)
                .found(std::format("Left operand of type {}, right operand of type {}", typeName(left.type), typeName(right.type)));
                return 0;
            }
            return ExprReturn(TBOOL, left.isVector || right.isVector); // Broadcast applied
        }

        std::any visitIdentifier(exprEngineParser::IdentifierContext *ctx) override {
            std::string name;
            if (ctx->IDENTIFIER()) {
                name = ctx->IDENTIFIER()->getText();
            }
            else {
                const auto tmp = ctx->QUOTED_IDENTIFIER()->getText();
                name = tmp.substr(1, tmp.size() - 2); // Remove quotes
            }

            if (schema.hasColumn(name)) {
                const auto& col = schema.getColumnSchema(name);
                return Identifier{name, col.getType()};
            }
            engine->report(ErrorCode::E101_UNKNOWN_REFERENCE)
                    .at(ctx)
                    .found(std::format("Column '{}' not found in schema", name));
            return Identifier{name, TINT};
        }

        std::any visitAggFn(exprEngineParser::ExprContext *expr) {
            const auto res = visitExpr(expr);
            if (res.type != TREAL && res.type != TINT) {
                engine->report(ErrorCode::E302_UNSUPPORTED_ARGUMENT_TYPE)
                        .what("Aggregate functions requires a numeric argument")
                        .at(expr)
                        .found(std::format("Argument of type {}", typeName(res.type)));
                return 0;
            }
            if (!res.isVector) {
                engine->report(ErrorCode::E303_NON_VECTOR_AGGREGATE)
                        .what("Aggregate functions requires a vector argument")
                        .at(expr)
                        .found("Argument is not a vector");
                return 0;
            }
            return ExprReturn(TREAL, false);
        }

        std::any visitFnAgg_Mean(exprEngineParser::FnAgg_MeanContext *ctx) override {
            return visitAggFn(ctx->expr()); // Result of aggregate functions is always a scalar
        }

        std::any visitFnAgg_Median(exprEngineParser::FnAgg_MedianContext *ctx) override {
            return visitAggFn(ctx->expr());
        }

        std::any visitFnAgg_StdDev(exprEngineParser::FnAgg_StdDevContext *ctx) override {
            return visitAggFn(ctx->expr());
        }

        std::any visitFnAgg_Variance(exprEngineParser::FnAgg_VarianceContext *ctx) override {
            return visitAggFn(ctx->expr());
        }

        std::any visitFnAgg_Max(exprEngineParser::FnAgg_MaxContext *ctx) override {
            return visitAggFn(ctx->expr());
        }

        std::any visitFnAgg_Min(exprEngineParser::FnAgg_MinContext *ctx) override {
            return visitAggFn(ctx->expr());
        }

        std::any visitFnAgg_Sum(exprEngineParser::FnAgg_SumContext *ctx) override {
            return visitAggFn(ctx->expr());
        }

        std::any visitFnAgg_Prod(exprEngineParser::FnAgg_ProdContext *ctx) override {
            return visitAggFn(ctx->expr());
        }

        std::any visitNumericSLFN(exprEngineParser::ExprContext *ctx, const char * const fn) {
            const auto res = visitExpr(ctx);
            if (res.type != TREAL && res.type != TINT) {
                engine->report(ErrorCode::E302_UNSUPPORTED_ARGUMENT_TYPE)
                        .what(std::format("{} function requires a numeric argument", fn))
                        .at(ctx)
                        .found(std::format("Argument of type {}", typeName(res.type)));
                return 0;
            }
            return ExprReturn(res.type, res.isVector);
        }

        std::any visitFnSL_Abs(exprEngineParser::FnSL_AbsContext *ctx) override {
            return visitNumericSLFN(ctx->expr(), "ABS");
        }

        std::any visitFnSL_Sign(exprEngineParser::FnSL_SignContext *ctx) override {
            return visitNumericSLFN(ctx->expr(), "SIGN");
        }

        std::any visitFnSL_Sqrt(exprEngineParser::FnSL_SqrtContext *ctx) override {
            return visitNumericSLFN(ctx->expr(), "SQRT");
        }

        std::any visitFnSL_Pow(exprEngineParser::FnSL_PowContext *ctx) override {
            const auto left = visitExpr(ctx->left);
            const auto right = visitExpr(ctx->right);
            if (left.type == TINT || right.type == TINT) {
                engine->report(ErrorCode::E902_IMPCAST_WIDENING_WARNING)
                .what("Implicit cast applied. Integer to Real")
                .at(ctx);
            }
            if (left.type != TREAL && left.type != TINT && right.type != TREAL && right.type != TINT) {
                engine->report(ErrorCode::E205_UNARY_OPERAND_MISMATCH)
                .what("Exponentiation operator requires numeric operands")
                .at(ctx)
                .found(std::format("Left operand of type {}, right operand of type {}", typeName(left.type), typeName(right.type)));
                return 0;
            }

            return ExprReturn(TREAL, left.isVector || right.isVector); // Broadcast applied, Always real
        }

        std::any visitFnSL_Log(exprEngineParser::FnSL_LogContext *ctx) override {
            return visitNumericSLFN(ctx->expr(), "LOG");
        }

        std::any visitFnSL_Log2(exprEngineParser::FnSL_Log2Context *ctx) override {
            return visitNumericSLFN(ctx->expr(), "LOG2");
        }

        std::any visitFnSL_Log10(exprEngineParser::FnSL_Log10Context *ctx) override {
            return visitNumericSLFN(ctx->expr(), "LOG10");
        }

        std::any visitFnSL_Exp(exprEngineParser::FnSL_ExpContext *ctx) override {
            return visitNumericSLFN(ctx->expr(), "EXP");
        }

        std::any visitFnSL_Erf(exprEngineParser::FnSL_ErfContext *ctx) override {
            return visitNumericSLFN(ctx->expr(), "ERF");
        }

        std::any visitFnSL_CdfNorm(exprEngineParser::FnSL_CdfNormContext *ctx) override {
            return visitNumericSLFN(ctx->expr(), "CDFNORM");
        }

        std::any visitFnSL_Floor(exprEngineParser::FnSL_FloorContext *ctx) override {
            const auto res = visitExpr(ctx->expr());
            if (res.type == TINT) {
                engine->report(ErrorCode::E902_IMPCAST_WIDENING_WARNING)
                .what("Applying FLOOR function on INTEGER arguments converts the argument to REAL")
                .at(ctx);
                return ExprReturn(TREAL, res.isVector);
            }
            if (res.type != TREAL) {
                engine->report(ErrorCode::E302_UNSUPPORTED_ARGUMENT_TYPE)
                .what("FLOOR function requires a numeric argument")
                .at(ctx)
                .found(std::format("Argument of type {}", typeName(res.type)));
                return 0;
            }
            return ExprReturn(TREAL, res.isVector);
        }

        std::any visitFnSL_Ceil(exprEngineParser::FnSL_CeilContext *ctx) override {
            const auto res = visitExpr(ctx->expr());
            if (res.type == TINT) {
                engine->report(ErrorCode::E902_IMPCAST_WIDENING_WARNING)
                .what("Applying CEIL function on INTEGER arguments converts the argument to REAL")
                .at(ctx);
                return ExprReturn(TREAL, res.isVector);
            }
            if (res.type != TREAL) {
                engine->report(ErrorCode::E302_UNSUPPORTED_ARGUMENT_TYPE)
                .what("CEIL function requires a numeric argument")
                .at(ctx)
                .found(std::format("Argument of type {}", typeName(res.type)));
                return 0;
            }
            return ExprReturn(TREAL, res.isVector);
        }

        std::any visitFnSL_Round(exprEngineParser::FnSL_RoundContext *ctx) override {
            const auto res = visitExpr(ctx->expr());
            if (res.type == TINT) {
                engine->report(ErrorCode::E902_IMPCAST_WIDENING_WARNING)
                .what("Applying ROUND function on INTEGER arguments converts the argument to REAL")
                .at(ctx);
                return ExprReturn(TREAL, res.isVector);
            }
            if (res.type != TREAL) {
                engine->report(ErrorCode::E302_UNSUPPORTED_ARGUMENT_TYPE)
                .what("ROUND function requires a numeric argument")
                .at(ctx)
                .found(std::format("Argument of type {}", typeName(res.type)));
                return 0;
            }
            return ExprReturn(TREAL, res.isVector);
        }

        std::any visitFnSL_Sin(exprEngineParser::FnSL_SinContext *ctx) override {
            return visitNumericSLFN(ctx->expr(), "SIN");
        }

        std::any visitFnSL_Cos(exprEngineParser::FnSL_CosContext *ctx) override {
            return visitNumericSLFN(ctx->expr(), "COS");
        }

        std::any visitFnSL_Tan(exprEngineParser::FnSL_TanContext *ctx) override {
            return visitNumericSLFN(ctx->expr(), "TAN");
        }

        std::any visitFnSL_CloseEnough(exprEngineParser::FnSL_CloseEnoughContext *ctx) override {
            const auto arg1 = visitExpr(ctx->arg1);
            const auto arg2 = visitExpr(ctx->arg2);

            if (arg1.type != TREAL || arg2.type != TREAL) {
                engine->report(ErrorCode::E302_UNSUPPORTED_ARGUMENT_TYPE)
                .what("CLOSEENOUGH function explicitly requires a REAL arguments")
                .at(ctx)
                .found(std::format("Arguments of type {}, {}", typeName(arg1.type), typeName(arg2.type)))
                .fix("Use Equality (==) operator for other types");
                return 0;
            }
            return ExprReturn(TBOOL, arg1.isVector || arg2.isVector);
        }

        std::any visitFnSL_Length(exprEngineParser::FnSL_LengthContext *ctx) override {
            const auto res = visitExpr(ctx->expr());
            if (res.type != TSTRING) {
                engine->report(ErrorCode::E302_UNSUPPORTED_ARGUMENT_TYPE)
                .what("LENGTH function requires a STRING argument")
                .at(ctx)
                .found(std::format("Argument of type {}", typeName(res.type)));
                return 0;
            }
            return ExprReturn(TINT, res.isVector);
        }

        std::any visitFnSL_Contains(exprEngineParser::FnSL_ContainsContext *ctx) override {
            const auto input = visitExpr(ctx->input);
            const auto pattern = visitExpr(ctx->pattern);
            if (input.type != TSTRING || pattern.type != TSTRING) {
                engine->report(ErrorCode::E302_UNSUPPORTED_ARGUMENT_TYPE)
                .what("CONTAINS function requires a STRING argument")
                .at(ctx)
                .found(std::format("Argument of type {}, {}", typeName(input.type), typeName(pattern.type)));
                return 0;
            }
            if (pattern.isVector) {
                engine->report(ErrorCode::E302_UNSUPPORTED_ARGUMENT_TYPE)
                .at(ctx)
                .what("Search string for the CONTAINS function must be STRING scalar");
                return 0;
            }
            return ExprReturn(TBOOL, input.isVector);
        }

        std::any visitFnSL_StartsWith(exprEngineParser::FnSL_StartsWithContext *ctx) override {
            const auto input = visitExpr(ctx->input);
            const auto pattern = visitExpr(ctx->pattern);
            if (input.type != TSTRING || pattern.type != TSTRING) {
                engine->report(ErrorCode::E302_UNSUPPORTED_ARGUMENT_TYPE)
                .what("STARTS WITH function requires a STRING argument")
                .at(ctx)
                .found(std::format("Argument of type {}, {}", typeName(input.type), typeName(pattern.type)));
                return 0;
            }
            if (pattern.isVector) {
                engine->report(ErrorCode::E302_UNSUPPORTED_ARGUMENT_TYPE)
                .at(ctx)
                .what("Search string for the STARTS WITH function must be STRING scalar");
                return 0;
            }
            return ExprReturn(TBOOL, input.isVector);
        }

        std::any visitFnSL_EndsWith(exprEngineParser::FnSL_EndsWithContext *ctx) override {
            const auto input = visitExpr(ctx->input);
            const auto pattern = visitExpr(ctx->pattern);
            if (input.type != TSTRING || pattern.type != TSTRING) {
                engine->report(ErrorCode::E302_UNSUPPORTED_ARGUMENT_TYPE)
                .what("ENDS WITH function requires a STRING argument")
                .at(ctx)
                .found(std::format("Argument of type {}, {}", typeName(input.type), typeName(pattern.type)));
                return 0;
            }
            if (pattern.isVector) {
                engine->report(ErrorCode::E302_UNSUPPORTED_ARGUMENT_TYPE)
                .at(ctx)
                .what("Search string for the ENDS WITH function must be STRING scalar");
                return 0;
            }
            return ExprReturn(TBOOL, input.isVector);
        }

        std::any visitFnSL_Like(exprEngineParser::FnSL_LikeContext *ctx) override {
            const auto input = visitExpr(ctx->input);
            const auto pattern = visitExpr(ctx->pattern);
            if (input.type != TSTRING || pattern.type != TSTRING) {
                engine->report(ErrorCode::E302_UNSUPPORTED_ARGUMENT_TYPE)
                .what("LIKE function requires a STRING argument")
                .at(ctx)
                .found(std::format("Argument of type {}, {}", typeName(input.type), typeName(pattern.type)));
                return 0;
            }
            if (pattern.isVector) {
                engine->report(ErrorCode::E302_UNSUPPORTED_ARGUMENT_TYPE)
                .at(ctx)
                .what("Search pattern for the LIKE function must be STRING scalar");
                return 0;
            }
            return ExprReturn(TBOOL, input.isVector);
        }

        std::any visitDateFNSL(exprEngineParser::ExprContext *ctx, const char * const fn) {
            const auto res = visitExpr(ctx);
            if (res.type != TTIMESTAMP) {
                engine->report(ErrorCode::E302_UNSUPPORTED_ARGUMENT_TYPE)
                        .what(std::format("{} function requires a TIMESTAMP argument", fn))
                        .at(ctx)
                        .found(std::format("Argument of type {}", typeName(res.type)));
                return 0;
            }
            return ExprReturn(TREAL, res.isVector);
        }

        std::any visitFnSL_Year(exprEngineParser::FnSL_YearContext *ctx) override {
            return visitDateFNSL(ctx->expr(), "YEAR");
        }

        std::any visitFnSL_Month(exprEngineParser::FnSL_MonthContext *ctx) override {
            return visitDateFNSL(ctx->expr(), "MONTH");
        }

        std::any visitFnSL_Day(exprEngineParser::FnSL_DayContext *ctx) override {
            return visitDateFNSL(ctx->expr(), "DAY");
        }

        std::any visitFnSL_Hour(exprEngineParser::FnSL_HourContext *ctx) override {
            return visitDateFNSL(ctx->expr(), "HOUR");
        }

        std::any visitFnSL_Minute(exprEngineParser::FnSL_MinuteContext *ctx) override {
            return visitDateFNSL(ctx->expr(), "MINUTE");
        }

        std::any visitFnSL_Second(exprEngineParser::FnSL_SecondContext *ctx) override {
            return visitDateFNSL(ctx->expr(), "SECOND");
        }

        std::any visitFnSL_SecondOfDay(exprEngineParser::FnSL_SecondOfDayContext *ctx) override {
            return visitDateFNSL(ctx->expr(), "SecondOfDay");
        }

        std::any visitFnSL_WeekOfMonth(exprEngineParser::FnSL_WeekOfMonthContext *ctx) override {
            return visitDateFNSL(ctx->expr(), "WeekOfMonth");
        }

        std::any visitFnSL_DayOfWeek(exprEngineParser::FnSL_DayOfWeekContext *ctx) override {
            return visitDateFNSL(ctx->expr(), "DayOfWeek");
        }

        std::any visitFnSL_WeekOfYear(exprEngineParser::FnSL_WeekOfYearContext *ctx) override {
            return visitDateFNSL(ctx->expr(), "WeekOfYear");
        }

        std::any visitFnSL_DateDiff(exprEngineParser::FnSL_DateDiffContext *ctx) override {
            const auto date1 = visitExpr(ctx->date1);
            const auto date2 = visitExpr(ctx->date2);
            if (date1.type != TTIMESTAMP || date2.type != TTIMESTAMP) {
                engine->report(ErrorCode::E302_UNSUPPORTED_ARGUMENT_TYPE)
                .what("DateDiff function requires a TIMESTAMP argument")
                .at(ctx)
                .found(std::format("Argument of type {}", typeName(date1.type)));
                return 0;
            }
            return ExprReturn(TREAL, date1.isVector || date2.isVector);
        }

        std::any visitFnSL_DateAdd(exprEngineParser::FnSL_DateAddContext *ctx) override {
            const auto date1 = visitExpr(ctx->date1);
            const auto duration = visitExpr(ctx->duration);
            if (date1.type != TTIMESTAMP) {
                engine->report(ErrorCode::E302_UNSUPPORTED_ARGUMENT_TYPE)
                .what("DateAdd function requires the first argument to be TIMESTAMP")
                .at(ctx)
                .found(std::format("Argument of type {}", typeName(date1.type)));
                return 0;
            }
            if (duration.type != TINT && duration.type != TREAL) {
                engine->report(ErrorCode::E302_UNSUPPORTED_ARGUMENT_TYPE)
                .what("DateAdd function requires the second argument to be a numeric type")
                .at(ctx)
                .found(std::format("Argument of type {}", typeName(duration.type)));
                return 0;
            }
            return ExprReturn(TTIMESTAMP, date1.isVector || duration.isVector);
        }

        std::any visitRealLit(exprEngineParser::RealLitContext *ctx) override {
            return ExprReturn(TREAL, false);
        }

        std::any visitIntLit(exprEngineParser::IntLitContext *ctx) override {
            return ExprReturn(TINT, false);
        }

        std::any visitBoolLit(exprEngineParser::BoolLitContext *ctx) override {
            return ExprReturn(TBOOL, false);
        }

        std::any visitStringLit(exprEngineParser::StringLitContext *ctx) override {
            return ExprReturn(TSTRING, false);
        }

        std::any visitTimestampLit(exprEngineParser::TimestampLitContext *ctx) override {
            return ExprReturn(TTIMESTAMP, false);
        }

        std::any visitNullLit(exprEngineParser::NullLitContext *ctx) override {
            return 0; // This should not occur
        }

    private:
        ComputeSchema schema;
        BoxRef<DiagnosticEngine> engine;
    };
}
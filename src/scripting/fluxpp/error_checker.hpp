#pragma once

#include <format>
#include <utility>
#include <antlr4-runtime.h>
#include "fluxppBaseVisitor.h"
#include "diagnose/diagnostic_engine.hpp"
#include "diagnose/diagnose_helpers.hpp"
#include "diagnose/diagnostic_builder.hpp"
#include "types.hpp"
#include "ComputeFrame.hpp"
#include "functions.hpp"
#include "immutable.hpp"

namespace scripting::fluxpp {
    class StaticAnalyzer : public fluxppBaseVisitor {

        struct Returns {
            Type type;
            bool isVector;

            Returns(const Type type_, const bool isVector_) : type(type_), isVector(isVector_) {}

            bool operator==(const Returns& other) const {
                return type == other.type && isVector == other.isVector;
            }
        };

        struct Args {
            size_t args;
            bool ifAnyVector;
        };

    public:
        explicit StaticAnalyzer(std::shared_ptr<df::DataFrame> df_ptr, std::shared_ptr<DiagnosticEngine> engine_) : fn_type(), df{std::move(df_ptr)}, engine(std::move(engine_)) {
        }

       /* std::any visitErrorNode(antlr4::tree::ErrorNode *ctx) override {
            engine->report(ErrorCode::SYN001_SYNTAX_ERROR).at(ctx->getSymbol());
            return 0;
        }*/

        std::any visitSingle(fluxppParser::SingleContext *ctx) override {
            engine->report(ErrorCode::SEM002_ISOLATED_EXPRESSION)
            .at(ctx)
            .what("A standalone expression is not a valid statement")
            .fix("Wrap the expression in a statement, e.g. LET x = <expr> or ASSERT <expr>");
            return 0;
        }

        std::any visitAssignment(fluxppParser::AssignmentContext *ctx) override {
            if (const std::string id = ctx->ID()->getText(); immutables.contains(id)) {
                engine->report(ErrorCode::SSA001_IMMUTABLE_REASSIGNMENT)
                .at(ctx->ID()->getSymbol())
                .what(whatReassign(id))
                .expected("Variables declared using 'LET' are immutable and cannot be reassigned")
                .found(firstDeclaredAt(id, immutables.at(id).line) + "; a second assignment appears here")
                .fix("Use a different name if declaring a new variable");
            }
            else if (df->HasColumn(id)) {
                engine->report(ErrorCode::SSA002_LET_SHADOWS_COLUMN)
                .at(ctx->ID()->getSymbol())
                .what(std::format("Assigning to  column '{}'", id))
                .expected("Cannot directly assign to a column of the active data frame using LET keyword")
                .fix(std::format("SET {} = {} ; Use SET keyword instead", id, ctx->expr()->getText()));
                //.fix(std::format("Use 'SET {} = <expr>' to modify an existing column", id))
            }
            else {
                const auto [type, isVector] = std::any_cast<Returns>(visit(ctx->expr()));
                immutables.insert({id, {id, type, isVector, ctx->ID()->getSymbol()->getLine()}});
            }
            return 0;
        }

        std::any visitCreate(fluxppParser::CreateContext *ctx) override {
            const std::string id = ctx->ID()->getText();
            if (immutables.contains(id)) {
                engine->report(ErrorCode::REF001_CREATE_SHADOWS_VARIABLE)
                .at(ctx->ID()->getSymbol())
                .what(std::format("'Identifier {}' is already declared as a variable", id));
                return 0;
            }
            else if (df->HasColumn(id)) {
                engine->report(ErrorCode::REF002_CREATE_DUPLICATE_COLUMN)
                .at(ctx->ID()->getSymbol())
                .what(std::format("'{}' already exists as a column in the active data frame", id));
                return 0;
            }
            const auto [type, isVector] = std::any_cast<Returns>(visit(ctx->expr()));
            if (!isVector) {
                engine->report(ErrorCode::W_SEM002_CREATE_SCALAR_BROADCAST).at(ctx->expr());
            }
            if (type != Type::TREAL) {
                engine->report(ErrorCode::W_TYP001_IMPLICIT_CAST).at(ctx->expr());
            }
            return 0;
        }

        std::any visitFilter(fluxppParser::FilterContext *ctx) override {
            const auto [type, isVector] = std::any_cast<Returns>(visit(ctx->expr()));
            if (type != Type::TBOOL) {
                engine->report(ErrorCode::TYP003_CONDITION_NOT_BOOL)
                .at(ctx->expr())
                .what("KEEP IF condition must evaluate to a bool vector");
            }

            if (!isVector) {
                engine->report(ErrorCode::DIM001_EXPECTED_VECTOR_GOT_SCALAR).at(ctx->expr());
            }
            return 0;
        }

        std::any visitDrop_row(fluxppParser::Drop_rowContext *ctx) override {
            const auto [type, isVector] = std::any_cast<Returns>(visit(ctx->expr()));
            if (type != Type::TBOOL) {
                engine->report(ErrorCode::TYP003_CONDITION_NOT_BOOL)
                .at(ctx->expr())
                .what("DROP IF condition must evaluate to a bool vector");
            }

            if (!isVector) {
                engine->report(ErrorCode::DIM001_EXPECTED_VECTOR_GOT_SCALAR).at(ctx->expr());
            }
            return 0;
        }

        std::any visitDrop_col(fluxppParser::Drop_colContext *ctx) override {
            for (const auto* idc : ctx->ID()) {
                std::string id = idc->getSymbol()->getText();
                if (!df->HasColumn(id)) {
                    engine->report(ErrorCode::REF003_UNKNOWN_COLUMN)
                    .at(idc->getSymbol())
                    .what(whatUnknownCol(id))
                    .expected("An existing column in the active data frame");
                }
            }
            if (ctx->expr()) {
                const auto [type, isVector] = std::any_cast<Returns>(visit(ctx->expr()));

                if (type != Type::TBOOL) {
                    engine->report(ErrorCode::TYP003_CONDITION_NOT_BOOL)
                    .at(ctx->expr())
                    .what("REMOVE expression must evaluate to a boolean expression");
                }

                if (isVector) {
                    engine->report(ErrorCode::DIM002_EXPECTED_SCALAR_GOT_VECTOR)
                    .at(ctx->expr())
                    .what("REMOVE condition must be a scalar bool, not a vector")
                    .expected("A scalar bool expression (applies the condition to the whole statement)")
                    .found("A vector bool expression")
                    .fix("Use a scalar condition, e.g.  REMOVE col1, col2 IF flag == true");
                }
            }
            return 0;
        }

        std::any visitClamp(fluxppParser::ClampContext *ctx) override {
            std::string id = ctx->ID()->getText();
            if (!df->HasColumn(id)) {
                engine->report(ErrorCode::REF003_UNKNOWN_COLUMN)
                .at(ctx)
                .what(whatUnknownCol(id))
                .expected("An existing column in the active data frame");
                return 0;
            }

            const auto from = std::any_cast<Returns>(visit(ctx->from));
            const auto to = std::any_cast<Returns>(visit(ctx->to));
            const Type colT = df->Meta(df->ColIdx(id)).type;

            if (from.type != to.type) {
                engine->report(ErrorCode::TYP005_CLAMP_BOUNDS_TYPE_MISMATCH)
                .at(ctx->from)
                .expected("CLAMP bounds must have the same type");
                return 0;
            }

            if (from.type != Type::TREAL && from.type != Type::TTIMESTAMP) {
                engine->report(ErrorCode::TYP006_CLAMP_BOUND_UNSUPPORTED_TYPE)
                .at(ctx->from)
                .expected("CLAMP bound expressions must evaluate to real or timestamp types");
                return 0;
            }

            if (from.type != colT) {
                engine->report(ErrorCode::TYP007_SET_TYPE_MISMATCH)
                .at(ctx->from)
                .what("CLAMP bound expression types differ from the column type")
                .expected(std::format("Bound expressions must evaluate to the same type as the column ({})", typeName(colT)));
                return 0;
            }

            if (from.isVector || to.isVector) {
                engine->report(ErrorCode::DIM002_EXPECTED_SCALAR_GOT_VECTOR)
                .at(ctx->from)
                .expected("Bound expressions must evaluate to scalars");
            }
            return 0;
        }

        std::any visitSet(fluxppParser::SetContext *ctx) override {
            std::string id = ctx->ID()->getText();
            if (!df->HasColumn(id)) {
                engine->report(ErrorCode::REF003_UNKNOWN_COLUMN)
                .at(ctx->ID()->getSymbol())
                .what(whatUnknownCol(id))
                .expected("An existing column in the active data frame");
                return 0;
            }
            const auto [type, isVector] = std::any_cast<Returns>(visit(ctx->expr()));
            const auto colT = df->Meta(df->ColIdx(id)).type;
            if (type != colT) {
                engine->report(ErrorCode::TYP007_SET_TYPE_MISMATCH)
                .at(ctx->expr())
                .expected(std::format("SET expressions must evaluate to the same type as the column ({})", typeName(colT)))
                .found(to_string(type));
                return 0;
            }

            if (!isVector) {
                engine->report(ErrorCode::W_SEM003_SET_SCALAR_BROADCAST).at(ctx->expr());
            }
            if (type != Type::TREAL) {
                engine->report(ErrorCode::W_TYP001_IMPLICIT_CAST).at(ctx->expr());
            }
            return 0;
        }

        std::any visitRename(fluxppParser::RenameContext *ctx) override {
            std::string old = ctx->oldCol->getText();
            std::string news= ctx->newCol->getText();

            if (!df->HasColumn(old)) {
                engine->report(ErrorCode::REF005_RENAME_SRC_NOT_FOUND)
                .at(ctx->oldCol)
                .what("RENAME source column does not exist in the active data frame")
                .expected("An existing column in the active data frame");
            }
            if (df->HasColumn(news)) {
                engine->report(ErrorCode::REF006_RENAME_DST_CONFLICT)
                .at(ctx->newCol)
                .what("RENAME destination column already exists in the active data frame");
            }
            if (immutables.contains(news)) {
                engine->report(ErrorCode::REF006_RENAME_DST_CONFLICT)
                .at(ctx->newCol)
                .what(std::format("RENAME destination column shadows the already declared immutable variable '{}'", news))
                .found(firstDeclaredAt(news, immutables.at(news).line));
            }

            return 0;
        }

        std::any visitFill(fluxppParser::FillContext *ctx) override {
            std::string id = ctx->ID()->getText();
            const auto [type, isVector] = std::any_cast<Returns>(visit(ctx->expr()));
            if (!df->HasColumn(id)) {
                engine->report(ErrorCode::REF003_UNKNOWN_COLUMN)
                .at(ctx->ID()->getSymbol())
                .what(whatUnknownCol(id))
                .expected("An existing column in the active data frame");
                return 0;
            }
            const auto& meta = df->Meta(df->ColIdx(id));

            if (meta.type != type) {
                engine->report(ErrorCode::TYP008_FILL_TYPE_MISMATCH)
                .at(ctx->expr())
                .expected(std::format("FILL expression must evaluate to the same type as the column ({})", typeName(meta.type)));
            }

            if (isVector) {
                engine->report(ErrorCode::DIM002_EXPECTED_SCALAR_GOT_VECTOR)
                .at(ctx->expr())
                .expected("FILL expression must evaluate to a scalar value.");
            }
            return 0;
        }

        std::any visitAssert_statement(fluxppParser::Assert_statementContext *ctx) override {
            const auto [type, isVector] = std::any_cast<Returns>(visit(ctx->expr()));
            if (isVector) {
                engine->report(ErrorCode::DIM002_EXPECTED_SCALAR_GOT_VECTOR)
                .at(ctx->expr())
                .expected("ASSERT expression must evaluate to a scalar value.");
            }
            if (type != Type::TBOOL) {
                engine->report(ErrorCode::TYP003_CONDITION_NOT_BOOL)
                .at(ctx->expr())
                .expected("ASSERT expression must evaluate to a boolean");
            }
            return 0;
        }

        std::any visitTernary(fluxppParser::TernaryContext *ctx) override {
            const auto trx = std::any_cast<Returns>(visit(ctx->trueExpr));
            const auto flx = std::any_cast<Returns>(visit(ctx->falseExpr));
            const auto cond = std::any_cast<Returns>(visit(ctx->cond));

            if (trx.type != flx.type) {
                engine->report(ErrorCode::TYP004_TERNARY_BRANCH_MISMATCH)
                .at(ctx)
                .expected("Both branches in the ternary expression must evaluate to the same type")
                .found(std::format("True branch: {}, False branch: {}", typeName(trx.type), typeName(flx.type)));
                return 0;
            }
            if (trx.isVector != flx.isVector) {
                engine->report(ErrorCode::DIM004_TERNARY_DIM_MISMATCH)
                .at(ctx)
                .expected("Both branches in the ternary expression must have the same dimensionality")
                .found(std::format("True branch: {}, False branch: {}", dimName(trx.isVector), dimName(flx.isVector)));
                return 0;
            }
            if (cond.type != Type::TBOOL) {
                engine->report(ErrorCode::TYP003_CONDITION_NOT_BOOL)
                .at(ctx->cond)
                .found(to_string(cond.type));
                return 0;
            }
            if (cond.isVector) {
                engine->report(ErrorCode::DIM002_EXPECTED_SCALAR_GOT_VECTOR)
                .at(ctx->cond)
                .what("Condition expression of a ternary expression must evaluate to a scalar value.");
                return 0;
            }

            return Returns({trx.type, trx.isVector});
        }

        std::any visitParens(fluxppParser::ParensContext *ctx) override {
            return visit(ctx->expr());
        }

        std::any visitTime(fluxppParser::TimeContext *ctx) override {
            return Returns(Type::TTIMESTAMP, false);
        }

        std::any visitExponentiation(fluxppParser::ExponentiationContext *ctx) override {
            const auto left  = std::any_cast<Returns>(visit(ctx->left));
            const auto right = std::any_cast<Returns>(visit(ctx->right));
            if (left.type != right.type) {
                engine->report(ErrorCode::TYP013_ARITHMETIC_TYPE_MISMATCH)
                .at(ctx->left)
                .expected("Both operands must evaluate to real")
                .found(std::format("Left: {}, Right: {}", typeName(left.type), typeName(right.type)));
                return 0;
            }
            if (left.type != Type::TREAL) {
                engine->report(ErrorCode::TYP014_ARITHMETIC_UNSUPPORTED_TYPE)
                .at(ctx->left)
                .what("Binary exponentiation only support real operands")
                .found(to_string(left.type));
                return 0;
            }
            if (right.type != Type::TREAL) {
                engine->report(ErrorCode::TYP014_ARITHMETIC_UNSUPPORTED_TYPE)
                .at(ctx->right)
                .what("Binary exponentiation only support real operands")
                .found(to_string(right.type));
                return 0;
            }
            return Returns(left.type, left.isVector || right.isVector); // Broadcasting
        }

        std::any visitChainedComparisonAscending(fluxppParser::ChainedComparisonAscendingContext *ctx) override {
            const auto left  = std::any_cast<Returns>(visit(ctx->left));
            const auto middle  = std::any_cast<Returns>(visit(ctx->middle));
            const auto right = std::any_cast<Returns>(visit(ctx->right));
            if (!(left.type == middle.type && middle.type == right.type)) {
                engine->report(ErrorCode::TYP011_COMPARISON_TYPE_MISMATCH)
                .at(ctx)
                .expected("All operands must evaluate to the same type");
                return 0;
            }
            if (!supportsComparisons(left.type) || !supportsComparisons(middle.type) || !supportsComparisons(right.type)) {
                engine->report(ErrorCode::TYP002_UNSUPPORTED_TYPE_FOR_OP)
                .at(ctx)
                .what("Chained comparison only support real and timestamp types");
                return 0;
            }
            return Returns(Type::TBOOL, left.isVector || middle.isVector || right.isVector);
        }

        std::any visitDateTime(fluxppParser::DateTimeContext *ctx) override {
            return Returns(Type::TTIMESTAMP, false);
        }

        std::any visitDate(fluxppParser::DateContext *ctx) override {
            return Returns(Type::TTIMESTAMP, false);
        }

        std::any visitLogicalOr(fluxppParser::LogicalOrContext *ctx) override {
            const auto left  = std::any_cast<Returns>(visit(ctx->left));
            const auto right = std::any_cast<Returns>(visit(ctx->right));
            if (left.type != Type::TBOOL) {
                engine->report(ErrorCode::TYP002_UNSUPPORTED_TYPE_FOR_OP)
                .at(ctx->left)
                .what("Logical OR operator requires boolean operands")
                .found(to_string(left.type));
                return 0;
            }
            if (right.type != Type::TBOOL) {
                engine->report(ErrorCode::TYP002_UNSUPPORTED_TYPE_FOR_OP)
                .at(ctx->right)
                .what("Logical OR operator requires boolean operands")
                .found(to_string(right.type));
                return 0;
            }
            return Returns(Type::TBOOL, left.isVector || right.isVector); // Broadcasting
        }

        std::any visitFalseLiteral(fluxppParser::FalseLiteralContext *ctx) override {
            return Returns(Type::TBOOL, false);
        }

        std::any visitLogicalNot(fluxppParser::LogicalNotContext *ctx) override {
            const auto expr = std::any_cast<Returns>(visit(ctx->expr()));
            if (expr.type != Type::TBOOL) {
                engine->report(ErrorCode::TYP002_UNSUPPORTED_TYPE_FOR_OP)
                .at(ctx->expr())
                .what("Logical NOT operator requires a boolean operand")
                .found(to_string(expr.type));
                return 0;
            }
            return Returns(Type::TBOOL, expr.isVector);
        }

        std::any visitChainedComparisonDescending(fluxppParser::ChainedComparisonDescendingContext *ctx) override {
            const auto left  = std::any_cast<Returns>(visit(ctx->left));
            const auto middle  = std::any_cast<Returns>(visit(ctx->middle));
            const auto right = std::any_cast<Returns>(visit(ctx->right));
            if (!(left.type == middle.type && middle.type == right.type)) {
                engine->report(ErrorCode::TYP011_COMPARISON_TYPE_MISMATCH)
                .at(ctx)
                .expected("All operands must evaluate to the same type");
                return 0;
            }
            if (!supportsComparisons(left.type) || !supportsComparisons(middle.type) || !supportsComparisons(right.type)) {
                engine->report(ErrorCode::TYP002_UNSUPPORTED_TYPE_FOR_OP)
                .at(ctx)
                .what("Chained comparison only support real and timestamp types");
                return 0;
            }
            if (!(left.isVector == middle.isVector && middle.isVector == right.isVector)) {
                engine->report(ErrorCode::DIM004_TERNARY_DIM_MISMATCH)
                .at(ctx)
                .what("Chained comparison require all operands to have the same dimensionality");
                return 0;
            }
            return Returns(Type::TBOOL, left.isVector && middle.isVector && right.isVector);
        }

        std::any visitMultiplicative(fluxppParser::MultiplicativeContext *ctx) override {
            const auto left  = std::any_cast<Returns>(visit(ctx->left));
            const auto right = std::any_cast<Returns>(visit(ctx->right));
            if (left.type != Type::TREAL) {
                engine->report(ErrorCode::TYP014_ARITHMETIC_UNSUPPORTED_TYPE)
                .at(ctx->left)
                .what("Operator only supports real valued operands")
                .found(to_string(left.type));
                return 0;
            }
            if (right.type != Type::TREAL) {
                engine->report(ErrorCode::TYP014_ARITHMETIC_UNSUPPORTED_TYPE)
                .at(ctx->right)
                .what("Operator only supports real valued operands")
                .found(to_string(right.type));
                return 0;
            }
            return Returns(Type::TREAL, left.isVector || right.isVector); // Broadcasting
        }

        std::any visitAdditive(fluxppParser::AdditiveContext *ctx) override {
            const auto left  = std::any_cast<Returns>(visit(ctx->left));
            const auto right = std::any_cast<Returns>(visit(ctx->right));
            if (!supportsComparisons(left.type)) {
                engine->report(ErrorCode::TYP014_ARITHMETIC_UNSUPPORTED_TYPE)
                .at(ctx->left)
                .what("Operator only supports real valued or timestamp operands")
                .found(to_string(left.type));
                return 0;
            }
            if (!supportsComparisons(right.type)) {
                engine->report(ErrorCode::TYP014_ARITHMETIC_UNSUPPORTED_TYPE)
                .at(ctx->right)
                .what("Operator only supports real valued or timestamp operands")
                .found(to_string(right.type));
                return 0;
            }
            return Returns(Type::TREAL, left.isVector || right.isVector); // Broadcasting
        }

        std::any visitAbs(fluxppParser::AbsContext *ctx) override {
            const auto expr = std::any_cast<Returns>(visit(ctx->expr()));
            if (expr.type != Type::TREAL) {
                engine->report(ErrorCode::TYP017_ABS_NOT_REAL)
                .at(ctx->expr())
                .what("Expression evaluates to an unsupported type")
                .expected("Nd Norm requires a real operand")
                .found(to_string(expr.type));
                return 0;
            }
            return Returns(Type::TREAL, expr.isVector);
        }

        std::any visitIdentifier(fluxppParser::IdentifierContext *ctx) override {
            const std::string id = ctx->ID()->getText();
            if (immutables.contains(id)) {
                auto& imm = immutables.at(id);
                imm.is_used = true;
                return Returns(imm.type, imm.isVector);
            }
            if (df->HasColumn(id)) {
                const auto& [name, type] = df->Meta(df->ColIdx(id));
                return Returns(type, true);
            }
            if (std::tolower(id[0]) == 'e' || id == "pi") {
                return Returns(Type::TREAL, false);
            }
            engine->report(ErrorCode::REF004_UNKNOWN_VARIABLE_OR_COLUMN)
            .what(whatUnknownId(id))
            .expected("A variable declared with LET, or an existing column")
            .fix(std::format("Check for a typo in '{}', or declare it with LET", id));
            return 0;
        }

        std::any visitNumber(fluxppParser::NumberContext *ctx) override {
            return Returns(Type::TREAL, false);
        }

        std::any visitStringLiteral(fluxppParser::StringLiteralContext *ctx) override {
            return Returns(Type::TSTRING, false);
        }

        std::any visitTrueLiteral(fluxppParser::TrueLiteralContext *ctx) override {
            return Returns(Type::TBOOL, false);
        }

        std::any visitComparison(fluxppParser::ComparisonContext *ctx) override {
            const std::string op = ctx->op->getText();
            const auto left  = std::any_cast<Returns>(visit(ctx->left));
            const auto right = std::any_cast<Returns>(visit(ctx->right));
            if (left.type != right.type) {
                engine->report(ErrorCode::TYP001_TYPE_MISMATCH)
                .at(ctx->op)
                .expected("Both operands must evaluate to the same type");
                return 0;
            }
            return Returns(Type::TBOOL, left.isVector || right.isVector);
        }

        std::any visitLessInequal(fluxppParser::LessInequalContext *ctx) override {
            const auto left = std::any_cast<Returns>(visit(ctx->left));
            const auto right = std::any_cast<Returns>(visit(ctx->right));
            if (left.type != right.type) {
                engine->report(ErrorCode::TYP001_TYPE_MISMATCH)
                .at(ctx->op)
                .expected("Both operands must evaluate to the same type");
                return 0;
            }
            if (!supportsComparisons(left.type)) {
                engine->report(ErrorCode::TYP002_UNSUPPORTED_TYPE_FOR_OP)
                .at(ctx->left)
                .what("Operator only supports real valued or timestamp operands")
                .found(to_string(left.type));
                return 0;
            }
            if (!supportsComparisons(right.type)) {
                engine->report(ErrorCode::TYP002_UNSUPPORTED_TYPE_FOR_OP)
                .at(ctx->right)
                .what("Operator only supports real valued or timestamp operands")
                .found(to_string(right.type));
                return 0;
            }
            return Returns(Type::TBOOL, left.isVector || right.isVector);
        }

        std::any visitGreaterInequal(fluxppParser::GreaterInequalContext *ctx) override {
            const auto left = std::any_cast<Returns>(visit(ctx->left));
            const auto right = std::any_cast<Returns>(visit(ctx->right));
            if (left.type != right.type) {
                engine->report(ErrorCode::TYP001_TYPE_MISMATCH)
                .at(ctx->op)
                .expected("Both operands must evaluate to the same type");
                return 0;
            }
            if (!supportsComparisons(left.type)) {
                engine->report(ErrorCode::TYP002_UNSUPPORTED_TYPE_FOR_OP)
                .at(ctx->left)
                .what("Operator only supports real valued or timestamp operands")
                .found(to_string(left.type));
                return 0;
            }
            if (!supportsComparisons(right.type)) {
                engine->report(ErrorCode::TYP002_UNSUPPORTED_TYPE_FOR_OP)
                .at(ctx->right)
                .what("Operator only supports real valued or timestamp operands")
                .found(to_string(right.type));
                return 0;
            }
            return Returns(Type::TBOOL, left.isVector || right.isVector);
        }

        std::any visitLogicalAnd(fluxppParser::LogicalAndContext *ctx) override {
            const auto left  = std::any_cast<Returns>(visit(ctx->left));
            const auto right = std::any_cast<Returns>(visit(ctx->right));
            if (left.type != Type::TBOOL) {
                engine->report(ErrorCode::TYP002_UNSUPPORTED_TYPE_FOR_OP)
                .at(ctx->left)
                .what("Logical AND operator requires boolean operands")
                .found(to_string(left.type));
                return 0;
            }
            if (right.type != Type::TBOOL) {
                engine->report(ErrorCode::TYP002_UNSUPPORTED_TYPE_FOR_OP)
                .at(ctx->right)
                .what("Logical AND operator requires boolean operands")
                .found(to_string(right.type));
                return 0;
            }
            return Returns(Type::TBOOL, left.isVector || right.isVector); // Broadcasting
        }

        std::any visitFunctionCall(fluxppParser::FunctionCallContext *ctx) override {
            std::string id = ctx->ID()->getText();
            scripting::fluxpp::FN_DATA fn = scripting::fluxpp::get_fn_index(id);

            if (fn.index == std::numeric_limits<uint64_t>::max()) {
                engine->report(ErrorCode::REF007_UNKNOWN_FUNCTION)
                .at(ctx->ID()->getSymbol())
                .what(whatUnknownFn(id));
                return 0;
            }
            fn_type = fn.arg_type;

            const auto args = std::any_cast<Args>(visit(ctx->args()));
            if (args.args != fn.arg_count) {
                engine->report(ErrorCode::ARG001_WRONG_ARG_COUNT)
                .at(ctx->args())
                .what(whatWrongArgCount(id, fn.arg_count, args.args));
                return 0;
            }
            if (args.ifAnyVector && !fn.supports_vectors) {
                engine->report(ErrorCode::DIM003_FUNC_ARG_DIM_MISMATCH)
                .at(ctx->args())
                .what(std::format("Function '{}' does not support vector arguments", id));
                return 0;
            }
            if (!args.ifAnyVector && !fn.supports_scalars) {
                engine->report(ErrorCode::DIM003_FUNC_ARG_DIM_MISMATCH)
               .at(ctx->args())
               .what(std::format("Function '{}' does not support scalar arguments", id));
                return 0;
            }
            if (fn.fnt == PASS) {
                return Returns(Type::TREAL, args.ifAnyVector);
            }
            if (fn.fnt == REDUCE) {
                return Returns(Type::TREAL, false);
            }
            if (fn.fnt == EXPAND) {
                return Returns(Type::TREAL, true);
            }
            engine->report(ErrorCode::SYN003_NO_VIABLE_ALTERNATIVE)
            .at(ctx)
            .what("Unknown error occurred while resolving function call")
            .fix("Likely a compiler bug. Please report.");
            return 0;
        }

        std::any visitNegate(fluxppParser::NegateContext *ctx) override {
            const auto expr = std::any_cast<Returns>(visit(ctx->expr()));
            if (expr.type != Type::TREAL) {
                engine->report(ErrorCode::TYP016_NEGATION_NOT_REAL)
                .at(ctx->expr())
                .found(to_string(expr.type));
                return 0;
            }
            return Returns(Type::TREAL, expr.isVector);
        }

        std::any visitNullLiteral(fluxppParser::NullLiteralContext *ctx) override {
            return Returns(Type::TNULL, false);
        }

        std::any visitArgs(fluxppParser::ArgsContext *ctx) override {
            bool isAny = false;
            auto t = Type::TREAL;
            uint8_t count = 0;
            for (auto* arg : ctx->expr()) {
                const auto [type, isVector] = std::any_cast<Returns>(visit(arg));
                isAny = isAny || isVector;
                if (count == 0) t = type;
                if (t != type) {
                    engine->report(ErrorCode::TYP010_FUNC_ARGS_HETEROGENEOUS)
                    .at(arg);
                    return 0;
                }
                count++;
                if (type != fn_type) {
                    engine->report(ErrorCode::TYP009_FUNC_ARG_TYPE_MISMATCH)
                    .at(arg)
                    .what(std::format("Function does not support '{}' typed arguments", to_string(type)))
                    .expected(to_string(fn_type));
                    return 0;
                }
            }

            return Args(ctx->expr().size(), isAny);
        }

    private:
        Type fn_type;
        std::unordered_map<std::string, Immutable> immutables;
        std::shared_ptr<df::DataFrame> df;
        std::shared_ptr<DiagnosticEngine> engine;
    };

    class ErrorListener : public antlr4::BaseErrorListener {
    public:
        explicit ErrorListener(std::shared_ptr<DiagnosticEngine> engine) : engine(std::move(engine)) {}
        void syntaxError(antlr4::Recognizer *recognizer, antlr4::Token *offendingSymbol, size_t line,
            size_t charPositionInLine, const std::string &msg, std::exception_ptr e) override {
            engine->report(ErrorCode::SYN001_SYNTAX_ERROR)
            .at(offendingSymbol)
            .what(msg);
        }
    private:
        std::shared_ptr<DiagnosticEngine> engine;
    };
};
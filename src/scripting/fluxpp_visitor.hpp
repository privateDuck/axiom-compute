#pragma once

#include "antlr/antlr4-runtime.h"
#include "fluxpp/fluxppVisitor.h"
#include "HashMap.hpp"
#include <EigenDefinitions.hpp>
#include "fluxpp/ExprReturn.hpp"
#include "fluxpp/functions.hpp"

class FluxPPTreeInterpreter : fluxppVisitor {
public:
    std::any visitProgram(fluxppParser::ProgramContext *context) override;
    std::any visitFlux(fluxppParser::FluxContext *context) override;
    std::any visitSingle(fluxppParser::SingleContext *context) override;
    std::any visitStatement(fluxppParser::StatementContext *context) override;
    std::any visitAssignment(fluxppParser::AssignmentContext *context) override;
    std::any visitCreate(fluxppParser::CreateContext *context) override;
    std::any visitFilter(fluxppParser::FilterContext *context) override;
    std::any visitDrop_row(fluxppParser::Drop_rowContext *context) override;
    std::any visitDrop_col(fluxppParser::Drop_colContext *context) override;
    std::any visitClamp(fluxppParser::ClampContext *context) override;
    std::any visitSet(fluxppParser::SetContext *context) override;
    std::any visitRename(fluxppParser::RenameContext *context) override;
    std::any visitFill(fluxppParser::FillContext *context) override;
    std::any visitAssert(fluxppParser::AssertContext *context) override;
    std::any visitParens(fluxppParser::ParensContext *context) override;
    std::any visitAbs(fluxppParser::AbsContext *context) override;
    std::any visitFunctionCall(fluxppParser::FunctionCallContext *context) override;
    std::any visitArgs(fluxppParser::ArgsContext *context) override;
    std::any visitExponentiation(fluxppParser::ExponentiationContext *context) override;
    std::any visitNegate(fluxppParser::NegateContext *context) override;
    std::any visitLogicalNot(fluxppParser::LogicalNotContext *context) override;
    std::any visitMultiplicative(fluxppParser::MultiplicativeContext *context) override;
    std::any visitAdditive(fluxppParser::AdditiveContext *context) override;
    std::any visitChainedComparisonAscending(fluxppParser::ChainedComparisonAscendingContext *context) override;
    std::any visitChainedComparisonDescending(fluxppParser::ChainedComparisonDescendingContext *context) override;
    std::any visitComparison(fluxppParser::ComparisonContext *context) override;
    std::any visitLogicalAnd(fluxppParser::LogicalAndContext *context) override;
    std::any visitLogicalOr(fluxppParser::LogicalOrContext *context) override;
    std::any visitTernary(fluxppParser::TernaryContext *context) override;
    std::any visitIdentifier(fluxppParser::IdentifierContext *context) override;
    std::any visitNumber(fluxppParser::NumberContext *context) override;
    std::any visitStringLiteral(fluxppParser::StringLiteralContext *context) override;
    std::any visitTrueLiteral(fluxppParser::TrueLiteralContext *context) override;
    std::any visitFalseLiteral(fluxppParser::FalseLiteralContext *context) override;
    std::any visitNullLiteral(fluxppParser::NullLiteralContext *context) override;
    std::any visitDateTime(fluxppParser::DateTimeContext *context) override;
    std::any visitDate(fluxppParser::DateContext *context) override;
    std::any visitTime(fluxppParser::TimeContext *context) override;

private:
    HashMapStrInt variable_map;
    HashMapStrInt feature_map;
    EigenColAlignedDoubleMat data;
    uint64_t ndims = 0;
    std::vector<std::string> errors;
    std::array<EigenColDoubleVec, 4> vector_register;
    std::array<double, 4> scalar_register = {};

    struct ArgReturn {
        bool isConst;
    };

    ArgReturn visitArgs(fluxppParser::ArgsContext *context, scripting::fluxpp::FN_DATA& fn_data, const std::string& fn_name);

    scripting::fluxpp::ExprReturn visitExpr(fluxppParser::ExprContext* context)
    {
        auto vr = std::any_cast<scripting::fluxpp::ExprReturn>(visit(context));
        return vr;
    }

    void RecordError(const antlr4::ParserRuleContext *const ctx, const std::string& message, const bool isError = true) {
        errors.emplace_back(std::format("[{} at line {}]: {}", isError ? "Error" : "Warning", ctx->getStart()->getLine(), message));
    }

    template<typename... Args>
    void RecordErrorFmt(const antlr4::ParserRuleContext* ctx, const std::format_string<Args...> fmt_msg, Args&&... args) {
        RecordError(ctx, std::vformat(fmt_msg.get(), std::make_format_args(args...)), true);
    }

    template<typename... Args>
    void RecordWarningFmt(const antlr4::ParserRuleContext* ctx, const std::format_string<Args...> fmt_msg, Args&&... args) {
        RecordError(ctx, std::vformat(fmt_msg.get(), std::make_format_args(args...)), false);
    }
};

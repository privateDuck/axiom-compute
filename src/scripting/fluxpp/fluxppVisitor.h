
// Generated from fluxpp.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "fluxppParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by fluxppParser.
 */
class  fluxppVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by fluxppParser.
   */
    virtual std::any visitProgram(fluxppParser::ProgramContext *context) = 0;

    virtual std::any visitFlux(fluxppParser::FluxContext *context) = 0;

    virtual std::any visitSingle(fluxppParser::SingleContext *context) = 0;

    virtual std::any visitStatement(fluxppParser::StatementContext *context) = 0;

    virtual std::any visitAssignment(fluxppParser::AssignmentContext *context) = 0;

    virtual std::any visitCreate(fluxppParser::CreateContext *context) = 0;

    virtual std::any visitFilter(fluxppParser::FilterContext *context) = 0;

    virtual std::any visitDrop_row(fluxppParser::Drop_rowContext *context) = 0;

    virtual std::any visitDrop_col(fluxppParser::Drop_colContext *context) = 0;

    virtual std::any visitClamp(fluxppParser::ClampContext *context) = 0;

    virtual std::any visitSet(fluxppParser::SetContext *context) = 0;

    virtual std::any visitRename(fluxppParser::RenameContext *context) = 0;

    virtual std::any visitFill(fluxppParser::FillContext *context) = 0;

    virtual std::any visitAssert_statement(fluxppParser::Assert_statementContext *context) = 0;

    virtual std::any visitParens(fluxppParser::ParensContext *context) = 0;

    virtual std::any visitTime(fluxppParser::TimeContext *context) = 0;

    virtual std::any visitExponentiation(fluxppParser::ExponentiationContext *context) = 0;

    virtual std::any visitDateTime(fluxppParser::DateTimeContext *context) = 0;

    virtual std::any visitLogicalOr(fluxppParser::LogicalOrContext *context) = 0;

    virtual std::any visitFalseLiteral(fluxppParser::FalseLiteralContext *context) = 0;

    virtual std::any visitLogicalNot(fluxppParser::LogicalNotContext *context) = 0;

    virtual std::any visitChainedComparisonDescending(fluxppParser::ChainedComparisonDescendingContext *context) = 0;

    virtual std::any visitMultiplicative(fluxppParser::MultiplicativeContext *context) = 0;

    virtual std::any visitAdditive(fluxppParser::AdditiveContext *context) = 0;

    virtual std::any visitLessInequal(fluxppParser::LessInequalContext *context) = 0;

    virtual std::any visitAbs(fluxppParser::AbsContext *context) = 0;

    virtual std::any visitIdentifier(fluxppParser::IdentifierContext *context) = 0;

    virtual std::any visitNumber(fluxppParser::NumberContext *context) = 0;

    virtual std::any visitTrueLiteral(fluxppParser::TrueLiteralContext *context) = 0;

    virtual std::any visitComparison(fluxppParser::ComparisonContext *context) = 0;

    virtual std::any visitLogicalAnd(fluxppParser::LogicalAndContext *context) = 0;

    virtual std::any visitFunctionCall(fluxppParser::FunctionCallContext *context) = 0;

    virtual std::any visitTernary(fluxppParser::TernaryContext *context) = 0;

    virtual std::any visitChainedComparisonAscending(fluxppParser::ChainedComparisonAscendingContext *context) = 0;

    virtual std::any visitDate(fluxppParser::DateContext *context) = 0;

    virtual std::any visitGreaterInequal(fluxppParser::GreaterInequalContext *context) = 0;

    virtual std::any visitStringLiteral(fluxppParser::StringLiteralContext *context) = 0;

    virtual std::any visitNegate(fluxppParser::NegateContext *context) = 0;

    virtual std::any visitNullLiteral(fluxppParser::NullLiteralContext *context) = 0;

    virtual std::any visitArgs(fluxppParser::ArgsContext *context) = 0;


};


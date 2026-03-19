
// Generated from fluxpp.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "fluxppParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by fluxppParser.
 */
class  fluxppListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterProgram(fluxppParser::ProgramContext *ctx) = 0;
  virtual void exitProgram(fluxppParser::ProgramContext *ctx) = 0;

  virtual void enterFlux(fluxppParser::FluxContext *ctx) = 0;
  virtual void exitFlux(fluxppParser::FluxContext *ctx) = 0;

  virtual void enterSingle(fluxppParser::SingleContext *ctx) = 0;
  virtual void exitSingle(fluxppParser::SingleContext *ctx) = 0;

  virtual void enterStatement(fluxppParser::StatementContext *ctx) = 0;
  virtual void exitStatement(fluxppParser::StatementContext *ctx) = 0;

  virtual void enterAssignment(fluxppParser::AssignmentContext *ctx) = 0;
  virtual void exitAssignment(fluxppParser::AssignmentContext *ctx) = 0;

  virtual void enterCreate(fluxppParser::CreateContext *ctx) = 0;
  virtual void exitCreate(fluxppParser::CreateContext *ctx) = 0;

  virtual void enterFilter(fluxppParser::FilterContext *ctx) = 0;
  virtual void exitFilter(fluxppParser::FilterContext *ctx) = 0;

  virtual void enterDrop_row(fluxppParser::Drop_rowContext *ctx) = 0;
  virtual void exitDrop_row(fluxppParser::Drop_rowContext *ctx) = 0;

  virtual void enterDrop_col(fluxppParser::Drop_colContext *ctx) = 0;
  virtual void exitDrop_col(fluxppParser::Drop_colContext *ctx) = 0;

  virtual void enterClamp(fluxppParser::ClampContext *ctx) = 0;
  virtual void exitClamp(fluxppParser::ClampContext *ctx) = 0;

  virtual void enterSet(fluxppParser::SetContext *ctx) = 0;
  virtual void exitSet(fluxppParser::SetContext *ctx) = 0;

  virtual void enterRename(fluxppParser::RenameContext *ctx) = 0;
  virtual void exitRename(fluxppParser::RenameContext *ctx) = 0;

  virtual void enterFill(fluxppParser::FillContext *ctx) = 0;
  virtual void exitFill(fluxppParser::FillContext *ctx) = 0;

  virtual void enterAssert_statement(fluxppParser::Assert_statementContext *ctx) = 0;
  virtual void exitAssert_statement(fluxppParser::Assert_statementContext *ctx) = 0;

  virtual void enterParens(fluxppParser::ParensContext *ctx) = 0;
  virtual void exitParens(fluxppParser::ParensContext *ctx) = 0;

  virtual void enterTime(fluxppParser::TimeContext *ctx) = 0;
  virtual void exitTime(fluxppParser::TimeContext *ctx) = 0;

  virtual void enterExponentiation(fluxppParser::ExponentiationContext *ctx) = 0;
  virtual void exitExponentiation(fluxppParser::ExponentiationContext *ctx) = 0;

  virtual void enterDateTime(fluxppParser::DateTimeContext *ctx) = 0;
  virtual void exitDateTime(fluxppParser::DateTimeContext *ctx) = 0;

  virtual void enterLogicalOr(fluxppParser::LogicalOrContext *ctx) = 0;
  virtual void exitLogicalOr(fluxppParser::LogicalOrContext *ctx) = 0;

  virtual void enterFalseLiteral(fluxppParser::FalseLiteralContext *ctx) = 0;
  virtual void exitFalseLiteral(fluxppParser::FalseLiteralContext *ctx) = 0;

  virtual void enterLogicalNot(fluxppParser::LogicalNotContext *ctx) = 0;
  virtual void exitLogicalNot(fluxppParser::LogicalNotContext *ctx) = 0;

  virtual void enterChainedComparisonDescending(fluxppParser::ChainedComparisonDescendingContext *ctx) = 0;
  virtual void exitChainedComparisonDescending(fluxppParser::ChainedComparisonDescendingContext *ctx) = 0;

  virtual void enterMultiplicative(fluxppParser::MultiplicativeContext *ctx) = 0;
  virtual void exitMultiplicative(fluxppParser::MultiplicativeContext *ctx) = 0;

  virtual void enterAdditive(fluxppParser::AdditiveContext *ctx) = 0;
  virtual void exitAdditive(fluxppParser::AdditiveContext *ctx) = 0;

  virtual void enterLessInequal(fluxppParser::LessInequalContext *ctx) = 0;
  virtual void exitLessInequal(fluxppParser::LessInequalContext *ctx) = 0;

  virtual void enterAbs(fluxppParser::AbsContext *ctx) = 0;
  virtual void exitAbs(fluxppParser::AbsContext *ctx) = 0;

  virtual void enterIdentifier(fluxppParser::IdentifierContext *ctx) = 0;
  virtual void exitIdentifier(fluxppParser::IdentifierContext *ctx) = 0;

  virtual void enterNumber(fluxppParser::NumberContext *ctx) = 0;
  virtual void exitNumber(fluxppParser::NumberContext *ctx) = 0;

  virtual void enterTrueLiteral(fluxppParser::TrueLiteralContext *ctx) = 0;
  virtual void exitTrueLiteral(fluxppParser::TrueLiteralContext *ctx) = 0;

  virtual void enterComparison(fluxppParser::ComparisonContext *ctx) = 0;
  virtual void exitComparison(fluxppParser::ComparisonContext *ctx) = 0;

  virtual void enterLogicalAnd(fluxppParser::LogicalAndContext *ctx) = 0;
  virtual void exitLogicalAnd(fluxppParser::LogicalAndContext *ctx) = 0;

  virtual void enterFunctionCall(fluxppParser::FunctionCallContext *ctx) = 0;
  virtual void exitFunctionCall(fluxppParser::FunctionCallContext *ctx) = 0;

  virtual void enterTernary(fluxppParser::TernaryContext *ctx) = 0;
  virtual void exitTernary(fluxppParser::TernaryContext *ctx) = 0;

  virtual void enterChainedComparisonAscending(fluxppParser::ChainedComparisonAscendingContext *ctx) = 0;
  virtual void exitChainedComparisonAscending(fluxppParser::ChainedComparisonAscendingContext *ctx) = 0;

  virtual void enterDate(fluxppParser::DateContext *ctx) = 0;
  virtual void exitDate(fluxppParser::DateContext *ctx) = 0;

  virtual void enterGreaterInequal(fluxppParser::GreaterInequalContext *ctx) = 0;
  virtual void exitGreaterInequal(fluxppParser::GreaterInequalContext *ctx) = 0;

  virtual void enterStringLiteral(fluxppParser::StringLiteralContext *ctx) = 0;
  virtual void exitStringLiteral(fluxppParser::StringLiteralContext *ctx) = 0;

  virtual void enterNegate(fluxppParser::NegateContext *ctx) = 0;
  virtual void exitNegate(fluxppParser::NegateContext *ctx) = 0;

  virtual void enterNullLiteral(fluxppParser::NullLiteralContext *ctx) = 0;
  virtual void exitNullLiteral(fluxppParser::NullLiteralContext *ctx) = 0;

  virtual void enterArgs(fluxppParser::ArgsContext *ctx) = 0;
  virtual void exitArgs(fluxppParser::ArgsContext *ctx) = 0;


};


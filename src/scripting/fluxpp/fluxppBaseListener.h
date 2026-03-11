
// Generated from fluxpp.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "fluxppListener.h"


/**
 * This class provides an empty implementation of fluxppListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  fluxppBaseListener : public fluxppListener {
public:

  virtual void enterProgram(fluxppParser::ProgramContext * /*ctx*/) override { }
  virtual void exitProgram(fluxppParser::ProgramContext * /*ctx*/) override { }

  virtual void enterFlux(fluxppParser::FluxContext * /*ctx*/) override { }
  virtual void exitFlux(fluxppParser::FluxContext * /*ctx*/) override { }

  virtual void enterSingle(fluxppParser::SingleContext * /*ctx*/) override { }
  virtual void exitSingle(fluxppParser::SingleContext * /*ctx*/) override { }

  virtual void enterStatement(fluxppParser::StatementContext * /*ctx*/) override { }
  virtual void exitStatement(fluxppParser::StatementContext * /*ctx*/) override { }

  virtual void enterAssignment(fluxppParser::AssignmentContext * /*ctx*/) override { }
  virtual void exitAssignment(fluxppParser::AssignmentContext * /*ctx*/) override { }

  virtual void enterCreate(fluxppParser::CreateContext * /*ctx*/) override { }
  virtual void exitCreate(fluxppParser::CreateContext * /*ctx*/) override { }

  virtual void enterFilter(fluxppParser::FilterContext * /*ctx*/) override { }
  virtual void exitFilter(fluxppParser::FilterContext * /*ctx*/) override { }

  virtual void enterDrop_row(fluxppParser::Drop_rowContext * /*ctx*/) override { }
  virtual void exitDrop_row(fluxppParser::Drop_rowContext * /*ctx*/) override { }

  virtual void enterDrop_col(fluxppParser::Drop_colContext * /*ctx*/) override { }
  virtual void exitDrop_col(fluxppParser::Drop_colContext * /*ctx*/) override { }

  virtual void enterClamp(fluxppParser::ClampContext * /*ctx*/) override { }
  virtual void exitClamp(fluxppParser::ClampContext * /*ctx*/) override { }

  virtual void enterSet(fluxppParser::SetContext * /*ctx*/) override { }
  virtual void exitSet(fluxppParser::SetContext * /*ctx*/) override { }

  virtual void enterRename(fluxppParser::RenameContext * /*ctx*/) override { }
  virtual void exitRename(fluxppParser::RenameContext * /*ctx*/) override { }

  virtual void enterFill(fluxppParser::FillContext * /*ctx*/) override { }
  virtual void exitFill(fluxppParser::FillContext * /*ctx*/) override { }

  virtual void enterAssert_statement(fluxppParser::Assert_statementContext * /*ctx*/) override { }
  virtual void exitAssert_statement(fluxppParser::Assert_statementContext * /*ctx*/) override { }

  virtual void enterTernary(fluxppParser::TernaryContext * /*ctx*/) override { }
  virtual void exitTernary(fluxppParser::TernaryContext * /*ctx*/) override { }

  virtual void enterParens(fluxppParser::ParensContext * /*ctx*/) override { }
  virtual void exitParens(fluxppParser::ParensContext * /*ctx*/) override { }

  virtual void enterTime(fluxppParser::TimeContext * /*ctx*/) override { }
  virtual void exitTime(fluxppParser::TimeContext * /*ctx*/) override { }

  virtual void enterExponentiation(fluxppParser::ExponentiationContext * /*ctx*/) override { }
  virtual void exitExponentiation(fluxppParser::ExponentiationContext * /*ctx*/) override { }

  virtual void enterChainedComparisonAscending(fluxppParser::ChainedComparisonAscendingContext * /*ctx*/) override { }
  virtual void exitChainedComparisonAscending(fluxppParser::ChainedComparisonAscendingContext * /*ctx*/) override { }

  virtual void enterDateTime(fluxppParser::DateTimeContext * /*ctx*/) override { }
  virtual void exitDateTime(fluxppParser::DateTimeContext * /*ctx*/) override { }

  virtual void enterDate(fluxppParser::DateContext * /*ctx*/) override { }
  virtual void exitDate(fluxppParser::DateContext * /*ctx*/) override { }

  virtual void enterLogicalOr(fluxppParser::LogicalOrContext * /*ctx*/) override { }
  virtual void exitLogicalOr(fluxppParser::LogicalOrContext * /*ctx*/) override { }

  virtual void enterFalseLiteral(fluxppParser::FalseLiteralContext * /*ctx*/) override { }
  virtual void exitFalseLiteral(fluxppParser::FalseLiteralContext * /*ctx*/) override { }

  virtual void enterLogicalNot(fluxppParser::LogicalNotContext * /*ctx*/) override { }
  virtual void exitLogicalNot(fluxppParser::LogicalNotContext * /*ctx*/) override { }

  virtual void enterChainedComparisonDescending(fluxppParser::ChainedComparisonDescendingContext * /*ctx*/) override { }
  virtual void exitChainedComparisonDescending(fluxppParser::ChainedComparisonDescendingContext * /*ctx*/) override { }

  virtual void enterMultiplicative(fluxppParser::MultiplicativeContext * /*ctx*/) override { }
  virtual void exitMultiplicative(fluxppParser::MultiplicativeContext * /*ctx*/) override { }

  virtual void enterAdditive(fluxppParser::AdditiveContext * /*ctx*/) override { }
  virtual void exitAdditive(fluxppParser::AdditiveContext * /*ctx*/) override { }

  virtual void enterAbs(fluxppParser::AbsContext * /*ctx*/) override { }
  virtual void exitAbs(fluxppParser::AbsContext * /*ctx*/) override { }

  virtual void enterIdentifier(fluxppParser::IdentifierContext * /*ctx*/) override { }
  virtual void exitIdentifier(fluxppParser::IdentifierContext * /*ctx*/) override { }

  virtual void enterNumber(fluxppParser::NumberContext * /*ctx*/) override { }
  virtual void exitNumber(fluxppParser::NumberContext * /*ctx*/) override { }

  virtual void enterStringLiteral(fluxppParser::StringLiteralContext * /*ctx*/) override { }
  virtual void exitStringLiteral(fluxppParser::StringLiteralContext * /*ctx*/) override { }

  virtual void enterTrueLiteral(fluxppParser::TrueLiteralContext * /*ctx*/) override { }
  virtual void exitTrueLiteral(fluxppParser::TrueLiteralContext * /*ctx*/) override { }

  virtual void enterComparison(fluxppParser::ComparisonContext * /*ctx*/) override { }
  virtual void exitComparison(fluxppParser::ComparisonContext * /*ctx*/) override { }

  virtual void enterLogicalAnd(fluxppParser::LogicalAndContext * /*ctx*/) override { }
  virtual void exitLogicalAnd(fluxppParser::LogicalAndContext * /*ctx*/) override { }

  virtual void enterFunctionCall(fluxppParser::FunctionCallContext * /*ctx*/) override { }
  virtual void exitFunctionCall(fluxppParser::FunctionCallContext * /*ctx*/) override { }

  virtual void enterNegate(fluxppParser::NegateContext * /*ctx*/) override { }
  virtual void exitNegate(fluxppParser::NegateContext * /*ctx*/) override { }

  virtual void enterNullLiteral(fluxppParser::NullLiteralContext * /*ctx*/) override { }
  virtual void exitNullLiteral(fluxppParser::NullLiteralContext * /*ctx*/) override { }

  virtual void enterArgs(fluxppParser::ArgsContext * /*ctx*/) override { }
  virtual void exitArgs(fluxppParser::ArgsContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};


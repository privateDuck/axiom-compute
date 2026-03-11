
// Generated from fluxpp.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "fluxppVisitor.h"


/**
 * This class provides an empty implementation of fluxppVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  fluxppBaseVisitor : public fluxppVisitor {
public:

  virtual std::any visitProgram(fluxppParser::ProgramContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFlux(fluxppParser::FluxContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSingle(fluxppParser::SingleContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatement(fluxppParser::StatementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssignment(fluxppParser::AssignmentContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitCreate(fluxppParser::CreateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFilter(fluxppParser::FilterContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDrop_row(fluxppParser::Drop_rowContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDrop_col(fluxppParser::Drop_colContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitClamp(fluxppParser::ClampContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitSet(fluxppParser::SetContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRename(fluxppParser::RenameContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFill(fluxppParser::FillContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAssert_statement(fluxppParser::Assert_statementContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTernary(fluxppParser::TernaryContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitParens(fluxppParser::ParensContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTime(fluxppParser::TimeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExponentiation(fluxppParser::ExponentiationContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChainedComparisonAscending(fluxppParser::ChainedComparisonAscendingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDateTime(fluxppParser::DateTimeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitDate(fluxppParser::DateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalOr(fluxppParser::LogicalOrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFalseLiteral(fluxppParser::FalseLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalNot(fluxppParser::LogicalNotContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitChainedComparisonDescending(fluxppParser::ChainedComparisonDescendingContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitMultiplicative(fluxppParser::MultiplicativeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAdditive(fluxppParser::AdditiveContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAbs(fluxppParser::AbsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifier(fluxppParser::IdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNumber(fluxppParser::NumberContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStringLiteral(fluxppParser::StringLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTrueLiteral(fluxppParser::TrueLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitComparison(fluxppParser::ComparisonContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLogicalAnd(fluxppParser::LogicalAndContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCall(fluxppParser::FunctionCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNegate(fluxppParser::NegateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNullLiteral(fluxppParser::NullLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitArgs(fluxppParser::ArgsContext *ctx) override {
    return visitChildren(ctx);
  }


};


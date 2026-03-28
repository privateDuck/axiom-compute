
// Generated from exprEngineParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "exprEngineParserVisitor.h"


/**
 * This class provides an empty implementation of exprEngineParserVisitor, which can be
 * extended to create a visitor which only needs to handle a subset of the available methods.
 */
class  exprEngineParserBaseVisitor : public exprEngineParserVisitor {
public:

  virtual std::any visitExpression(exprEngineParser::ExpressionContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprNot(exprEngineParser::ExprNotContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprNegate(exprEngineParser::ExprNegateContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprDiv(exprEngineParser::ExprDivContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprAbs(exprEngineParser::ExprAbsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprEq(exprEngineParser::ExprEqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprGt(exprEngineParser::ExprGtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprLiteral(exprEngineParser::ExprLiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprParen(exprEngineParser::ExprParenContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprSub(exprEngineParser::ExprSubContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprOr(exprEngineParser::ExprOrContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprExp(exprEngineParser::ExprExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprLte(exprEngineParser::ExprLteContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprCall(exprEngineParser::ExprCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprLt(exprEngineParser::ExprLtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprMul(exprEngineParser::ExprMulContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprConcat(exprEngineParser::ExprConcatContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprAdd(exprEngineParser::ExprAddContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprMod(exprEngineParser::ExprModContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprAnd(exprEngineParser::ExprAndContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprGte(exprEngineParser::ExprGteContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprIntDiv(exprEngineParser::ExprIntDivContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprIndentifier(exprEngineParser::ExprIndentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitExprNeq(exprEngineParser::ExprNeqContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitAggregateOver(exprEngineParser::AggregateOverContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIdentifier(exprEngineParser::IdentifierContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFunctionCall(exprEngineParser::FunctionCallContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStatelessFn(exprEngineParser::StatelessFnContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnAgg_Mean(exprEngineParser::FnAgg_MeanContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnAgg_Median(exprEngineParser::FnAgg_MedianContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnAgg_StdDev(exprEngineParser::FnAgg_StdDevContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnAgg_Variance(exprEngineParser::FnAgg_VarianceContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnAgg_Max(exprEngineParser::FnAgg_MaxContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnAgg_Min(exprEngineParser::FnAgg_MinContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnAgg_Sum(exprEngineParser::FnAgg_SumContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnAgg_Prod(exprEngineParser::FnAgg_ProdContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Abs(exprEngineParser::FnSL_AbsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Sign(exprEngineParser::FnSL_SignContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Sqrt(exprEngineParser::FnSL_SqrtContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Pow(exprEngineParser::FnSL_PowContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Log(exprEngineParser::FnSL_LogContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Log2(exprEngineParser::FnSL_Log2Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Log10(exprEngineParser::FnSL_Log10Context *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Exp(exprEngineParser::FnSL_ExpContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Erf(exprEngineParser::FnSL_ErfContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_CdfNorm(exprEngineParser::FnSL_CdfNormContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Floor(exprEngineParser::FnSL_FloorContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Ceil(exprEngineParser::FnSL_CeilContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Round(exprEngineParser::FnSL_RoundContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Sin(exprEngineParser::FnSL_SinContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Cos(exprEngineParser::FnSL_CosContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Tan(exprEngineParser::FnSL_TanContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_CloseEnough(exprEngineParser::FnSL_CloseEnoughContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Length(exprEngineParser::FnSL_LengthContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Contains(exprEngineParser::FnSL_ContainsContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_StartsWith(exprEngineParser::FnSL_StartsWithContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_EndsWith(exprEngineParser::FnSL_EndsWithContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Like(exprEngineParser::FnSL_LikeContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Year(exprEngineParser::FnSL_YearContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Month(exprEngineParser::FnSL_MonthContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Day(exprEngineParser::FnSL_DayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Hour(exprEngineParser::FnSL_HourContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Minute(exprEngineParser::FnSL_MinuteContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_Second(exprEngineParser::FnSL_SecondContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_SecondOfDay(exprEngineParser::FnSL_SecondOfDayContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_WeekOfMonth(exprEngineParser::FnSL_WeekOfMonthContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_DayOfWeek(exprEngineParser::FnSL_DayOfWeekContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_WeekOfYear(exprEngineParser::FnSL_WeekOfYearContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_DateDiff(exprEngineParser::FnSL_DateDiffContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitFnSL_DateAdd(exprEngineParser::FnSL_DateAddContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitLiteral(exprEngineParser::LiteralContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitRealLit(exprEngineParser::RealLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitIntLit(exprEngineParser::IntLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitBoolLit(exprEngineParser::BoolLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitStringLit(exprEngineParser::StringLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTimestampLit(exprEngineParser::TimestampLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitNullLit(exprEngineParser::NullLitContext *ctx) override {
    return visitChildren(ctx);
  }

  virtual std::any visitTimeUnit(exprEngineParser::TimeUnitContext *ctx) override {
    return visitChildren(ctx);
  }


};


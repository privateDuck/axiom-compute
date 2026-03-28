
// Generated from exprEngineParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "exprEngineParser.h"


/**
 * This interface defines an abstract listener for a parse tree produced by exprEngineParser.
 */
class  exprEngineParserListener : public antlr4::tree::ParseTreeListener {
public:

  virtual void enterExpression(exprEngineParser::ExpressionContext *ctx) = 0;
  virtual void exitExpression(exprEngineParser::ExpressionContext *ctx) = 0;

  virtual void enterExprNot(exprEngineParser::ExprNotContext *ctx) = 0;
  virtual void exitExprNot(exprEngineParser::ExprNotContext *ctx) = 0;

  virtual void enterExprNegate(exprEngineParser::ExprNegateContext *ctx) = 0;
  virtual void exitExprNegate(exprEngineParser::ExprNegateContext *ctx) = 0;

  virtual void enterExprDiv(exprEngineParser::ExprDivContext *ctx) = 0;
  virtual void exitExprDiv(exprEngineParser::ExprDivContext *ctx) = 0;

  virtual void enterExprAbs(exprEngineParser::ExprAbsContext *ctx) = 0;
  virtual void exitExprAbs(exprEngineParser::ExprAbsContext *ctx) = 0;

  virtual void enterExprEq(exprEngineParser::ExprEqContext *ctx) = 0;
  virtual void exitExprEq(exprEngineParser::ExprEqContext *ctx) = 0;

  virtual void enterExprGt(exprEngineParser::ExprGtContext *ctx) = 0;
  virtual void exitExprGt(exprEngineParser::ExprGtContext *ctx) = 0;

  virtual void enterExprLiteral(exprEngineParser::ExprLiteralContext *ctx) = 0;
  virtual void exitExprLiteral(exprEngineParser::ExprLiteralContext *ctx) = 0;

  virtual void enterExprParen(exprEngineParser::ExprParenContext *ctx) = 0;
  virtual void exitExprParen(exprEngineParser::ExprParenContext *ctx) = 0;

  virtual void enterExprSub(exprEngineParser::ExprSubContext *ctx) = 0;
  virtual void exitExprSub(exprEngineParser::ExprSubContext *ctx) = 0;

  virtual void enterExprOr(exprEngineParser::ExprOrContext *ctx) = 0;
  virtual void exitExprOr(exprEngineParser::ExprOrContext *ctx) = 0;

  virtual void enterExprExp(exprEngineParser::ExprExpContext *ctx) = 0;
  virtual void exitExprExp(exprEngineParser::ExprExpContext *ctx) = 0;

  virtual void enterExprLte(exprEngineParser::ExprLteContext *ctx) = 0;
  virtual void exitExprLte(exprEngineParser::ExprLteContext *ctx) = 0;

  virtual void enterExprCall(exprEngineParser::ExprCallContext *ctx) = 0;
  virtual void exitExprCall(exprEngineParser::ExprCallContext *ctx) = 0;

  virtual void enterExprLt(exprEngineParser::ExprLtContext *ctx) = 0;
  virtual void exitExprLt(exprEngineParser::ExprLtContext *ctx) = 0;

  virtual void enterExprMul(exprEngineParser::ExprMulContext *ctx) = 0;
  virtual void exitExprMul(exprEngineParser::ExprMulContext *ctx) = 0;

  virtual void enterExprConcat(exprEngineParser::ExprConcatContext *ctx) = 0;
  virtual void exitExprConcat(exprEngineParser::ExprConcatContext *ctx) = 0;

  virtual void enterExprAdd(exprEngineParser::ExprAddContext *ctx) = 0;
  virtual void exitExprAdd(exprEngineParser::ExprAddContext *ctx) = 0;

  virtual void enterExprMod(exprEngineParser::ExprModContext *ctx) = 0;
  virtual void exitExprMod(exprEngineParser::ExprModContext *ctx) = 0;

  virtual void enterExprAnd(exprEngineParser::ExprAndContext *ctx) = 0;
  virtual void exitExprAnd(exprEngineParser::ExprAndContext *ctx) = 0;

  virtual void enterExprGte(exprEngineParser::ExprGteContext *ctx) = 0;
  virtual void exitExprGte(exprEngineParser::ExprGteContext *ctx) = 0;

  virtual void enterExprIntDiv(exprEngineParser::ExprIntDivContext *ctx) = 0;
  virtual void exitExprIntDiv(exprEngineParser::ExprIntDivContext *ctx) = 0;

  virtual void enterExprIndentifier(exprEngineParser::ExprIndentifierContext *ctx) = 0;
  virtual void exitExprIndentifier(exprEngineParser::ExprIndentifierContext *ctx) = 0;

  virtual void enterExprNeq(exprEngineParser::ExprNeqContext *ctx) = 0;
  virtual void exitExprNeq(exprEngineParser::ExprNeqContext *ctx) = 0;

  virtual void enterAggregateOver(exprEngineParser::AggregateOverContext *ctx) = 0;
  virtual void exitAggregateOver(exprEngineParser::AggregateOverContext *ctx) = 0;

  virtual void enterIdentifier(exprEngineParser::IdentifierContext *ctx) = 0;
  virtual void exitIdentifier(exprEngineParser::IdentifierContext *ctx) = 0;

  virtual void enterFunctionCall(exprEngineParser::FunctionCallContext *ctx) = 0;
  virtual void exitFunctionCall(exprEngineParser::FunctionCallContext *ctx) = 0;

  virtual void enterStatelessFn(exprEngineParser::StatelessFnContext *ctx) = 0;
  virtual void exitStatelessFn(exprEngineParser::StatelessFnContext *ctx) = 0;

  virtual void enterFnAgg_Mean(exprEngineParser::FnAgg_MeanContext *ctx) = 0;
  virtual void exitFnAgg_Mean(exprEngineParser::FnAgg_MeanContext *ctx) = 0;

  virtual void enterFnAgg_Median(exprEngineParser::FnAgg_MedianContext *ctx) = 0;
  virtual void exitFnAgg_Median(exprEngineParser::FnAgg_MedianContext *ctx) = 0;

  virtual void enterFnAgg_StdDev(exprEngineParser::FnAgg_StdDevContext *ctx) = 0;
  virtual void exitFnAgg_StdDev(exprEngineParser::FnAgg_StdDevContext *ctx) = 0;

  virtual void enterFnAgg_Variance(exprEngineParser::FnAgg_VarianceContext *ctx) = 0;
  virtual void exitFnAgg_Variance(exprEngineParser::FnAgg_VarianceContext *ctx) = 0;

  virtual void enterFnAgg_Max(exprEngineParser::FnAgg_MaxContext *ctx) = 0;
  virtual void exitFnAgg_Max(exprEngineParser::FnAgg_MaxContext *ctx) = 0;

  virtual void enterFnAgg_Min(exprEngineParser::FnAgg_MinContext *ctx) = 0;
  virtual void exitFnAgg_Min(exprEngineParser::FnAgg_MinContext *ctx) = 0;

  virtual void enterFnAgg_Sum(exprEngineParser::FnAgg_SumContext *ctx) = 0;
  virtual void exitFnAgg_Sum(exprEngineParser::FnAgg_SumContext *ctx) = 0;

  virtual void enterFnAgg_Prod(exprEngineParser::FnAgg_ProdContext *ctx) = 0;
  virtual void exitFnAgg_Prod(exprEngineParser::FnAgg_ProdContext *ctx) = 0;

  virtual void enterFnSL_Abs(exprEngineParser::FnSL_AbsContext *ctx) = 0;
  virtual void exitFnSL_Abs(exprEngineParser::FnSL_AbsContext *ctx) = 0;

  virtual void enterFnSL_Sign(exprEngineParser::FnSL_SignContext *ctx) = 0;
  virtual void exitFnSL_Sign(exprEngineParser::FnSL_SignContext *ctx) = 0;

  virtual void enterFnSL_Sqrt(exprEngineParser::FnSL_SqrtContext *ctx) = 0;
  virtual void exitFnSL_Sqrt(exprEngineParser::FnSL_SqrtContext *ctx) = 0;

  virtual void enterFnSL_Pow(exprEngineParser::FnSL_PowContext *ctx) = 0;
  virtual void exitFnSL_Pow(exprEngineParser::FnSL_PowContext *ctx) = 0;

  virtual void enterFnSL_Log(exprEngineParser::FnSL_LogContext *ctx) = 0;
  virtual void exitFnSL_Log(exprEngineParser::FnSL_LogContext *ctx) = 0;

  virtual void enterFnSL_Log2(exprEngineParser::FnSL_Log2Context *ctx) = 0;
  virtual void exitFnSL_Log2(exprEngineParser::FnSL_Log2Context *ctx) = 0;

  virtual void enterFnSL_Log10(exprEngineParser::FnSL_Log10Context *ctx) = 0;
  virtual void exitFnSL_Log10(exprEngineParser::FnSL_Log10Context *ctx) = 0;

  virtual void enterFnSL_Exp(exprEngineParser::FnSL_ExpContext *ctx) = 0;
  virtual void exitFnSL_Exp(exprEngineParser::FnSL_ExpContext *ctx) = 0;

  virtual void enterFnSL_Erf(exprEngineParser::FnSL_ErfContext *ctx) = 0;
  virtual void exitFnSL_Erf(exprEngineParser::FnSL_ErfContext *ctx) = 0;

  virtual void enterFnSL_CdfNorm(exprEngineParser::FnSL_CdfNormContext *ctx) = 0;
  virtual void exitFnSL_CdfNorm(exprEngineParser::FnSL_CdfNormContext *ctx) = 0;

  virtual void enterFnSL_Floor(exprEngineParser::FnSL_FloorContext *ctx) = 0;
  virtual void exitFnSL_Floor(exprEngineParser::FnSL_FloorContext *ctx) = 0;

  virtual void enterFnSL_Ceil(exprEngineParser::FnSL_CeilContext *ctx) = 0;
  virtual void exitFnSL_Ceil(exprEngineParser::FnSL_CeilContext *ctx) = 0;

  virtual void enterFnSL_Round(exprEngineParser::FnSL_RoundContext *ctx) = 0;
  virtual void exitFnSL_Round(exprEngineParser::FnSL_RoundContext *ctx) = 0;

  virtual void enterFnSL_Sin(exprEngineParser::FnSL_SinContext *ctx) = 0;
  virtual void exitFnSL_Sin(exprEngineParser::FnSL_SinContext *ctx) = 0;

  virtual void enterFnSL_Cos(exprEngineParser::FnSL_CosContext *ctx) = 0;
  virtual void exitFnSL_Cos(exprEngineParser::FnSL_CosContext *ctx) = 0;

  virtual void enterFnSL_Tan(exprEngineParser::FnSL_TanContext *ctx) = 0;
  virtual void exitFnSL_Tan(exprEngineParser::FnSL_TanContext *ctx) = 0;

  virtual void enterFnSL_CloseEnough(exprEngineParser::FnSL_CloseEnoughContext *ctx) = 0;
  virtual void exitFnSL_CloseEnough(exprEngineParser::FnSL_CloseEnoughContext *ctx) = 0;

  virtual void enterFnSL_Length(exprEngineParser::FnSL_LengthContext *ctx) = 0;
  virtual void exitFnSL_Length(exprEngineParser::FnSL_LengthContext *ctx) = 0;

  virtual void enterFnSL_Contains(exprEngineParser::FnSL_ContainsContext *ctx) = 0;
  virtual void exitFnSL_Contains(exprEngineParser::FnSL_ContainsContext *ctx) = 0;

  virtual void enterFnSL_StartsWith(exprEngineParser::FnSL_StartsWithContext *ctx) = 0;
  virtual void exitFnSL_StartsWith(exprEngineParser::FnSL_StartsWithContext *ctx) = 0;

  virtual void enterFnSL_EndsWith(exprEngineParser::FnSL_EndsWithContext *ctx) = 0;
  virtual void exitFnSL_EndsWith(exprEngineParser::FnSL_EndsWithContext *ctx) = 0;

  virtual void enterFnSL_Like(exprEngineParser::FnSL_LikeContext *ctx) = 0;
  virtual void exitFnSL_Like(exprEngineParser::FnSL_LikeContext *ctx) = 0;

  virtual void enterFnSL_Year(exprEngineParser::FnSL_YearContext *ctx) = 0;
  virtual void exitFnSL_Year(exprEngineParser::FnSL_YearContext *ctx) = 0;

  virtual void enterFnSL_Month(exprEngineParser::FnSL_MonthContext *ctx) = 0;
  virtual void exitFnSL_Month(exprEngineParser::FnSL_MonthContext *ctx) = 0;

  virtual void enterFnSL_Day(exprEngineParser::FnSL_DayContext *ctx) = 0;
  virtual void exitFnSL_Day(exprEngineParser::FnSL_DayContext *ctx) = 0;

  virtual void enterFnSL_Hour(exprEngineParser::FnSL_HourContext *ctx) = 0;
  virtual void exitFnSL_Hour(exprEngineParser::FnSL_HourContext *ctx) = 0;

  virtual void enterFnSL_Minute(exprEngineParser::FnSL_MinuteContext *ctx) = 0;
  virtual void exitFnSL_Minute(exprEngineParser::FnSL_MinuteContext *ctx) = 0;

  virtual void enterFnSL_Second(exprEngineParser::FnSL_SecondContext *ctx) = 0;
  virtual void exitFnSL_Second(exprEngineParser::FnSL_SecondContext *ctx) = 0;

  virtual void enterFnSL_SecondOfDay(exprEngineParser::FnSL_SecondOfDayContext *ctx) = 0;
  virtual void exitFnSL_SecondOfDay(exprEngineParser::FnSL_SecondOfDayContext *ctx) = 0;

  virtual void enterFnSL_WeekOfMonth(exprEngineParser::FnSL_WeekOfMonthContext *ctx) = 0;
  virtual void exitFnSL_WeekOfMonth(exprEngineParser::FnSL_WeekOfMonthContext *ctx) = 0;

  virtual void enterFnSL_DayOfWeek(exprEngineParser::FnSL_DayOfWeekContext *ctx) = 0;
  virtual void exitFnSL_DayOfWeek(exprEngineParser::FnSL_DayOfWeekContext *ctx) = 0;

  virtual void enterFnSL_WeekOfYear(exprEngineParser::FnSL_WeekOfYearContext *ctx) = 0;
  virtual void exitFnSL_WeekOfYear(exprEngineParser::FnSL_WeekOfYearContext *ctx) = 0;

  virtual void enterFnSL_DateDiff(exprEngineParser::FnSL_DateDiffContext *ctx) = 0;
  virtual void exitFnSL_DateDiff(exprEngineParser::FnSL_DateDiffContext *ctx) = 0;

  virtual void enterFnSL_DateAdd(exprEngineParser::FnSL_DateAddContext *ctx) = 0;
  virtual void exitFnSL_DateAdd(exprEngineParser::FnSL_DateAddContext *ctx) = 0;

  virtual void enterLiteral(exprEngineParser::LiteralContext *ctx) = 0;
  virtual void exitLiteral(exprEngineParser::LiteralContext *ctx) = 0;

  virtual void enterRealLit(exprEngineParser::RealLitContext *ctx) = 0;
  virtual void exitRealLit(exprEngineParser::RealLitContext *ctx) = 0;

  virtual void enterIntLit(exprEngineParser::IntLitContext *ctx) = 0;
  virtual void exitIntLit(exprEngineParser::IntLitContext *ctx) = 0;

  virtual void enterBoolLit(exprEngineParser::BoolLitContext *ctx) = 0;
  virtual void exitBoolLit(exprEngineParser::BoolLitContext *ctx) = 0;

  virtual void enterStringLit(exprEngineParser::StringLitContext *ctx) = 0;
  virtual void exitStringLit(exprEngineParser::StringLitContext *ctx) = 0;

  virtual void enterTimestampLit(exprEngineParser::TimestampLitContext *ctx) = 0;
  virtual void exitTimestampLit(exprEngineParser::TimestampLitContext *ctx) = 0;

  virtual void enterNullLit(exprEngineParser::NullLitContext *ctx) = 0;
  virtual void exitNullLit(exprEngineParser::NullLitContext *ctx) = 0;

  virtual void enterTimeUnit(exprEngineParser::TimeUnitContext *ctx) = 0;
  virtual void exitTimeUnit(exprEngineParser::TimeUnitContext *ctx) = 0;


};



// Generated from exprEngineParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "exprEngineParserListener.h"


/**
 * This class provides an empty implementation of exprEngineParserListener,
 * which can be extended to create a listener which only needs to handle a subset
 * of the available methods.
 */
class  exprEngineParserBaseListener : public exprEngineParserListener {
public:

  virtual void enterExpression(exprEngineParser::ExpressionContext * /*ctx*/) override { }
  virtual void exitExpression(exprEngineParser::ExpressionContext * /*ctx*/) override { }

  virtual void enterExprNot(exprEngineParser::ExprNotContext * /*ctx*/) override { }
  virtual void exitExprNot(exprEngineParser::ExprNotContext * /*ctx*/) override { }

  virtual void enterExprNegate(exprEngineParser::ExprNegateContext * /*ctx*/) override { }
  virtual void exitExprNegate(exprEngineParser::ExprNegateContext * /*ctx*/) override { }

  virtual void enterExprDiv(exprEngineParser::ExprDivContext * /*ctx*/) override { }
  virtual void exitExprDiv(exprEngineParser::ExprDivContext * /*ctx*/) override { }

  virtual void enterExprAbs(exprEngineParser::ExprAbsContext * /*ctx*/) override { }
  virtual void exitExprAbs(exprEngineParser::ExprAbsContext * /*ctx*/) override { }

  virtual void enterExprEq(exprEngineParser::ExprEqContext * /*ctx*/) override { }
  virtual void exitExprEq(exprEngineParser::ExprEqContext * /*ctx*/) override { }

  virtual void enterExprGt(exprEngineParser::ExprGtContext * /*ctx*/) override { }
  virtual void exitExprGt(exprEngineParser::ExprGtContext * /*ctx*/) override { }

  virtual void enterExprLiteral(exprEngineParser::ExprLiteralContext * /*ctx*/) override { }
  virtual void exitExprLiteral(exprEngineParser::ExprLiteralContext * /*ctx*/) override { }

  virtual void enterExprParen(exprEngineParser::ExprParenContext * /*ctx*/) override { }
  virtual void exitExprParen(exprEngineParser::ExprParenContext * /*ctx*/) override { }

  virtual void enterExprSub(exprEngineParser::ExprSubContext * /*ctx*/) override { }
  virtual void exitExprSub(exprEngineParser::ExprSubContext * /*ctx*/) override { }

  virtual void enterExprOr(exprEngineParser::ExprOrContext * /*ctx*/) override { }
  virtual void exitExprOr(exprEngineParser::ExprOrContext * /*ctx*/) override { }

  virtual void enterExprExp(exprEngineParser::ExprExpContext * /*ctx*/) override { }
  virtual void exitExprExp(exprEngineParser::ExprExpContext * /*ctx*/) override { }

  virtual void enterExprLte(exprEngineParser::ExprLteContext * /*ctx*/) override { }
  virtual void exitExprLte(exprEngineParser::ExprLteContext * /*ctx*/) override { }

  virtual void enterExprCall(exprEngineParser::ExprCallContext * /*ctx*/) override { }
  virtual void exitExprCall(exprEngineParser::ExprCallContext * /*ctx*/) override { }

  virtual void enterExprLt(exprEngineParser::ExprLtContext * /*ctx*/) override { }
  virtual void exitExprLt(exprEngineParser::ExprLtContext * /*ctx*/) override { }

  virtual void enterExprMul(exprEngineParser::ExprMulContext * /*ctx*/) override { }
  virtual void exitExprMul(exprEngineParser::ExprMulContext * /*ctx*/) override { }

  virtual void enterExprConcat(exprEngineParser::ExprConcatContext * /*ctx*/) override { }
  virtual void exitExprConcat(exprEngineParser::ExprConcatContext * /*ctx*/) override { }

  virtual void enterExprAdd(exprEngineParser::ExprAddContext * /*ctx*/) override { }
  virtual void exitExprAdd(exprEngineParser::ExprAddContext * /*ctx*/) override { }

  virtual void enterExprMod(exprEngineParser::ExprModContext * /*ctx*/) override { }
  virtual void exitExprMod(exprEngineParser::ExprModContext * /*ctx*/) override { }

  virtual void enterExprAnd(exprEngineParser::ExprAndContext * /*ctx*/) override { }
  virtual void exitExprAnd(exprEngineParser::ExprAndContext * /*ctx*/) override { }

  virtual void enterExprGte(exprEngineParser::ExprGteContext * /*ctx*/) override { }
  virtual void exitExprGte(exprEngineParser::ExprGteContext * /*ctx*/) override { }

  virtual void enterExprIntDiv(exprEngineParser::ExprIntDivContext * /*ctx*/) override { }
  virtual void exitExprIntDiv(exprEngineParser::ExprIntDivContext * /*ctx*/) override { }

  virtual void enterExprIndentifier(exprEngineParser::ExprIndentifierContext * /*ctx*/) override { }
  virtual void exitExprIndentifier(exprEngineParser::ExprIndentifierContext * /*ctx*/) override { }

  virtual void enterExprNeq(exprEngineParser::ExprNeqContext * /*ctx*/) override { }
  virtual void exitExprNeq(exprEngineParser::ExprNeqContext * /*ctx*/) override { }

  virtual void enterAggregateOver(exprEngineParser::AggregateOverContext * /*ctx*/) override { }
  virtual void exitAggregateOver(exprEngineParser::AggregateOverContext * /*ctx*/) override { }

  virtual void enterIdentifier(exprEngineParser::IdentifierContext * /*ctx*/) override { }
  virtual void exitIdentifier(exprEngineParser::IdentifierContext * /*ctx*/) override { }

  virtual void enterFunctionCall(exprEngineParser::FunctionCallContext * /*ctx*/) override { }
  virtual void exitFunctionCall(exprEngineParser::FunctionCallContext * /*ctx*/) override { }

  virtual void enterStatelessFn(exprEngineParser::StatelessFnContext * /*ctx*/) override { }
  virtual void exitStatelessFn(exprEngineParser::StatelessFnContext * /*ctx*/) override { }

  virtual void enterFnAgg_Mean(exprEngineParser::FnAgg_MeanContext * /*ctx*/) override { }
  virtual void exitFnAgg_Mean(exprEngineParser::FnAgg_MeanContext * /*ctx*/) override { }

  virtual void enterFnAgg_Median(exprEngineParser::FnAgg_MedianContext * /*ctx*/) override { }
  virtual void exitFnAgg_Median(exprEngineParser::FnAgg_MedianContext * /*ctx*/) override { }

  virtual void enterFnAgg_StdDev(exprEngineParser::FnAgg_StdDevContext * /*ctx*/) override { }
  virtual void exitFnAgg_StdDev(exprEngineParser::FnAgg_StdDevContext * /*ctx*/) override { }

  virtual void enterFnAgg_Variance(exprEngineParser::FnAgg_VarianceContext * /*ctx*/) override { }
  virtual void exitFnAgg_Variance(exprEngineParser::FnAgg_VarianceContext * /*ctx*/) override { }

  virtual void enterFnAgg_Max(exprEngineParser::FnAgg_MaxContext * /*ctx*/) override { }
  virtual void exitFnAgg_Max(exprEngineParser::FnAgg_MaxContext * /*ctx*/) override { }

  virtual void enterFnAgg_Min(exprEngineParser::FnAgg_MinContext * /*ctx*/) override { }
  virtual void exitFnAgg_Min(exprEngineParser::FnAgg_MinContext * /*ctx*/) override { }

  virtual void enterFnAgg_Sum(exprEngineParser::FnAgg_SumContext * /*ctx*/) override { }
  virtual void exitFnAgg_Sum(exprEngineParser::FnAgg_SumContext * /*ctx*/) override { }

  virtual void enterFnAgg_Prod(exprEngineParser::FnAgg_ProdContext * /*ctx*/) override { }
  virtual void exitFnAgg_Prod(exprEngineParser::FnAgg_ProdContext * /*ctx*/) override { }

  virtual void enterFnSL_Abs(exprEngineParser::FnSL_AbsContext * /*ctx*/) override { }
  virtual void exitFnSL_Abs(exprEngineParser::FnSL_AbsContext * /*ctx*/) override { }

  virtual void enterFnSL_Sign(exprEngineParser::FnSL_SignContext * /*ctx*/) override { }
  virtual void exitFnSL_Sign(exprEngineParser::FnSL_SignContext * /*ctx*/) override { }

  virtual void enterFnSL_Sqrt(exprEngineParser::FnSL_SqrtContext * /*ctx*/) override { }
  virtual void exitFnSL_Sqrt(exprEngineParser::FnSL_SqrtContext * /*ctx*/) override { }

  virtual void enterFnSL_Pow(exprEngineParser::FnSL_PowContext * /*ctx*/) override { }
  virtual void exitFnSL_Pow(exprEngineParser::FnSL_PowContext * /*ctx*/) override { }

  virtual void enterFnSL_Log(exprEngineParser::FnSL_LogContext * /*ctx*/) override { }
  virtual void exitFnSL_Log(exprEngineParser::FnSL_LogContext * /*ctx*/) override { }

  virtual void enterFnSL_Log2(exprEngineParser::FnSL_Log2Context * /*ctx*/) override { }
  virtual void exitFnSL_Log2(exprEngineParser::FnSL_Log2Context * /*ctx*/) override { }

  virtual void enterFnSL_Log10(exprEngineParser::FnSL_Log10Context * /*ctx*/) override { }
  virtual void exitFnSL_Log10(exprEngineParser::FnSL_Log10Context * /*ctx*/) override { }

  virtual void enterFnSL_Exp(exprEngineParser::FnSL_ExpContext * /*ctx*/) override { }
  virtual void exitFnSL_Exp(exprEngineParser::FnSL_ExpContext * /*ctx*/) override { }

  virtual void enterFnSL_Erf(exprEngineParser::FnSL_ErfContext * /*ctx*/) override { }
  virtual void exitFnSL_Erf(exprEngineParser::FnSL_ErfContext * /*ctx*/) override { }

  virtual void enterFnSL_CdfNorm(exprEngineParser::FnSL_CdfNormContext * /*ctx*/) override { }
  virtual void exitFnSL_CdfNorm(exprEngineParser::FnSL_CdfNormContext * /*ctx*/) override { }

  virtual void enterFnSL_Floor(exprEngineParser::FnSL_FloorContext * /*ctx*/) override { }
  virtual void exitFnSL_Floor(exprEngineParser::FnSL_FloorContext * /*ctx*/) override { }

  virtual void enterFnSL_Ceil(exprEngineParser::FnSL_CeilContext * /*ctx*/) override { }
  virtual void exitFnSL_Ceil(exprEngineParser::FnSL_CeilContext * /*ctx*/) override { }

  virtual void enterFnSL_Round(exprEngineParser::FnSL_RoundContext * /*ctx*/) override { }
  virtual void exitFnSL_Round(exprEngineParser::FnSL_RoundContext * /*ctx*/) override { }

  virtual void enterFnSL_Sin(exprEngineParser::FnSL_SinContext * /*ctx*/) override { }
  virtual void exitFnSL_Sin(exprEngineParser::FnSL_SinContext * /*ctx*/) override { }

  virtual void enterFnSL_Cos(exprEngineParser::FnSL_CosContext * /*ctx*/) override { }
  virtual void exitFnSL_Cos(exprEngineParser::FnSL_CosContext * /*ctx*/) override { }

  virtual void enterFnSL_Tan(exprEngineParser::FnSL_TanContext * /*ctx*/) override { }
  virtual void exitFnSL_Tan(exprEngineParser::FnSL_TanContext * /*ctx*/) override { }

  virtual void enterFnSL_CloseEnough(exprEngineParser::FnSL_CloseEnoughContext * /*ctx*/) override { }
  virtual void exitFnSL_CloseEnough(exprEngineParser::FnSL_CloseEnoughContext * /*ctx*/) override { }

  virtual void enterFnSL_Length(exprEngineParser::FnSL_LengthContext * /*ctx*/) override { }
  virtual void exitFnSL_Length(exprEngineParser::FnSL_LengthContext * /*ctx*/) override { }

  virtual void enterFnSL_Contains(exprEngineParser::FnSL_ContainsContext * /*ctx*/) override { }
  virtual void exitFnSL_Contains(exprEngineParser::FnSL_ContainsContext * /*ctx*/) override { }

  virtual void enterFnSL_StartsWith(exprEngineParser::FnSL_StartsWithContext * /*ctx*/) override { }
  virtual void exitFnSL_StartsWith(exprEngineParser::FnSL_StartsWithContext * /*ctx*/) override { }

  virtual void enterFnSL_EndsWith(exprEngineParser::FnSL_EndsWithContext * /*ctx*/) override { }
  virtual void exitFnSL_EndsWith(exprEngineParser::FnSL_EndsWithContext * /*ctx*/) override { }

  virtual void enterFnSL_Like(exprEngineParser::FnSL_LikeContext * /*ctx*/) override { }
  virtual void exitFnSL_Like(exprEngineParser::FnSL_LikeContext * /*ctx*/) override { }

  virtual void enterFnSL_Year(exprEngineParser::FnSL_YearContext * /*ctx*/) override { }
  virtual void exitFnSL_Year(exprEngineParser::FnSL_YearContext * /*ctx*/) override { }

  virtual void enterFnSL_Month(exprEngineParser::FnSL_MonthContext * /*ctx*/) override { }
  virtual void exitFnSL_Month(exprEngineParser::FnSL_MonthContext * /*ctx*/) override { }

  virtual void enterFnSL_Day(exprEngineParser::FnSL_DayContext * /*ctx*/) override { }
  virtual void exitFnSL_Day(exprEngineParser::FnSL_DayContext * /*ctx*/) override { }

  virtual void enterFnSL_Hour(exprEngineParser::FnSL_HourContext * /*ctx*/) override { }
  virtual void exitFnSL_Hour(exprEngineParser::FnSL_HourContext * /*ctx*/) override { }

  virtual void enterFnSL_Minute(exprEngineParser::FnSL_MinuteContext * /*ctx*/) override { }
  virtual void exitFnSL_Minute(exprEngineParser::FnSL_MinuteContext * /*ctx*/) override { }

  virtual void enterFnSL_Second(exprEngineParser::FnSL_SecondContext * /*ctx*/) override { }
  virtual void exitFnSL_Second(exprEngineParser::FnSL_SecondContext * /*ctx*/) override { }

  virtual void enterFnSL_SecondOfDay(exprEngineParser::FnSL_SecondOfDayContext * /*ctx*/) override { }
  virtual void exitFnSL_SecondOfDay(exprEngineParser::FnSL_SecondOfDayContext * /*ctx*/) override { }

  virtual void enterFnSL_WeekOfMonth(exprEngineParser::FnSL_WeekOfMonthContext * /*ctx*/) override { }
  virtual void exitFnSL_WeekOfMonth(exprEngineParser::FnSL_WeekOfMonthContext * /*ctx*/) override { }

  virtual void enterFnSL_DayOfWeek(exprEngineParser::FnSL_DayOfWeekContext * /*ctx*/) override { }
  virtual void exitFnSL_DayOfWeek(exprEngineParser::FnSL_DayOfWeekContext * /*ctx*/) override { }

  virtual void enterFnSL_WeekOfYear(exprEngineParser::FnSL_WeekOfYearContext * /*ctx*/) override { }
  virtual void exitFnSL_WeekOfYear(exprEngineParser::FnSL_WeekOfYearContext * /*ctx*/) override { }

  virtual void enterFnSL_DateDiff(exprEngineParser::FnSL_DateDiffContext * /*ctx*/) override { }
  virtual void exitFnSL_DateDiff(exprEngineParser::FnSL_DateDiffContext * /*ctx*/) override { }

  virtual void enterFnSL_DateAdd(exprEngineParser::FnSL_DateAddContext * /*ctx*/) override { }
  virtual void exitFnSL_DateAdd(exprEngineParser::FnSL_DateAddContext * /*ctx*/) override { }

  virtual void enterLiteral(exprEngineParser::LiteralContext * /*ctx*/) override { }
  virtual void exitLiteral(exprEngineParser::LiteralContext * /*ctx*/) override { }

  virtual void enterRealLit(exprEngineParser::RealLitContext * /*ctx*/) override { }
  virtual void exitRealLit(exprEngineParser::RealLitContext * /*ctx*/) override { }

  virtual void enterIntLit(exprEngineParser::IntLitContext * /*ctx*/) override { }
  virtual void exitIntLit(exprEngineParser::IntLitContext * /*ctx*/) override { }

  virtual void enterBoolLit(exprEngineParser::BoolLitContext * /*ctx*/) override { }
  virtual void exitBoolLit(exprEngineParser::BoolLitContext * /*ctx*/) override { }

  virtual void enterStringLit(exprEngineParser::StringLitContext * /*ctx*/) override { }
  virtual void exitStringLit(exprEngineParser::StringLitContext * /*ctx*/) override { }

  virtual void enterTimestampLit(exprEngineParser::TimestampLitContext * /*ctx*/) override { }
  virtual void exitTimestampLit(exprEngineParser::TimestampLitContext * /*ctx*/) override { }

  virtual void enterNullLit(exprEngineParser::NullLitContext * /*ctx*/) override { }
  virtual void exitNullLit(exprEngineParser::NullLitContext * /*ctx*/) override { }

  virtual void enterTimeUnit(exprEngineParser::TimeUnitContext * /*ctx*/) override { }
  virtual void exitTimeUnit(exprEngineParser::TimeUnitContext * /*ctx*/) override { }


  virtual void enterEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void exitEveryRule(antlr4::ParserRuleContext * /*ctx*/) override { }
  virtual void visitTerminal(antlr4::tree::TerminalNode * /*node*/) override { }
  virtual void visitErrorNode(antlr4::tree::ErrorNode * /*node*/) override { }

};


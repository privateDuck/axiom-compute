
// Generated from exprEngineParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"
#include "exprEngineParser.h"



/**
 * This class defines an abstract visitor for a parse tree
 * produced by exprEngineParser.
 */
class  exprEngineParserVisitor : public antlr4::tree::AbstractParseTreeVisitor {
public:

  /**
   * Visit parse trees produced by exprEngineParser.
   */
    virtual std::any visitExpression(exprEngineParser::ExpressionContext *context) = 0;

    virtual std::any visitExprNot(exprEngineParser::ExprNotContext *context) = 0;

    virtual std::any visitExprNegate(exprEngineParser::ExprNegateContext *context) = 0;

    virtual std::any visitExprDiv(exprEngineParser::ExprDivContext *context) = 0;

    virtual std::any visitExprAbs(exprEngineParser::ExprAbsContext *context) = 0;

    virtual std::any visitExprEq(exprEngineParser::ExprEqContext *context) = 0;

    virtual std::any visitExprGt(exprEngineParser::ExprGtContext *context) = 0;

    virtual std::any visitExprLiteral(exprEngineParser::ExprLiteralContext *context) = 0;

    virtual std::any visitExprParen(exprEngineParser::ExprParenContext *context) = 0;

    virtual std::any visitExprSub(exprEngineParser::ExprSubContext *context) = 0;

    virtual std::any visitExprOr(exprEngineParser::ExprOrContext *context) = 0;

    virtual std::any visitExprExp(exprEngineParser::ExprExpContext *context) = 0;

    virtual std::any visitExprLte(exprEngineParser::ExprLteContext *context) = 0;

    virtual std::any visitExprCall(exprEngineParser::ExprCallContext *context) = 0;

    virtual std::any visitExprLt(exprEngineParser::ExprLtContext *context) = 0;

    virtual std::any visitExprMul(exprEngineParser::ExprMulContext *context) = 0;

    virtual std::any visitExprConcat(exprEngineParser::ExprConcatContext *context) = 0;

    virtual std::any visitExprAdd(exprEngineParser::ExprAddContext *context) = 0;

    virtual std::any visitExprMod(exprEngineParser::ExprModContext *context) = 0;

    virtual std::any visitExprAnd(exprEngineParser::ExprAndContext *context) = 0;

    virtual std::any visitExprGte(exprEngineParser::ExprGteContext *context) = 0;

    virtual std::any visitExprIntDiv(exprEngineParser::ExprIntDivContext *context) = 0;

    virtual std::any visitExprIndentifier(exprEngineParser::ExprIndentifierContext *context) = 0;

    virtual std::any visitExprNeq(exprEngineParser::ExprNeqContext *context) = 0;

    virtual std::any visitAggregateOver(exprEngineParser::AggregateOverContext *context) = 0;

    virtual std::any visitIdentifier(exprEngineParser::IdentifierContext *context) = 0;

    virtual std::any visitFunctionCall(exprEngineParser::FunctionCallContext *context) = 0;

    virtual std::any visitStatelessFn(exprEngineParser::StatelessFnContext *context) = 0;

    virtual std::any visitFnAgg_Mean(exprEngineParser::FnAgg_MeanContext *context) = 0;

    virtual std::any visitFnAgg_Median(exprEngineParser::FnAgg_MedianContext *context) = 0;

    virtual std::any visitFnAgg_StdDev(exprEngineParser::FnAgg_StdDevContext *context) = 0;

    virtual std::any visitFnAgg_Variance(exprEngineParser::FnAgg_VarianceContext *context) = 0;

    virtual std::any visitFnAgg_Max(exprEngineParser::FnAgg_MaxContext *context) = 0;

    virtual std::any visitFnAgg_Min(exprEngineParser::FnAgg_MinContext *context) = 0;

    virtual std::any visitFnAgg_Sum(exprEngineParser::FnAgg_SumContext *context) = 0;

    virtual std::any visitFnAgg_Prod(exprEngineParser::FnAgg_ProdContext *context) = 0;

    virtual std::any visitFnSL_Abs(exprEngineParser::FnSL_AbsContext *context) = 0;

    virtual std::any visitFnSL_Sign(exprEngineParser::FnSL_SignContext *context) = 0;

    virtual std::any visitFnSL_Sqrt(exprEngineParser::FnSL_SqrtContext *context) = 0;

    virtual std::any visitFnSL_Pow(exprEngineParser::FnSL_PowContext *context) = 0;

    virtual std::any visitFnSL_Log(exprEngineParser::FnSL_LogContext *context) = 0;

    virtual std::any visitFnSL_Log2(exprEngineParser::FnSL_Log2Context *context) = 0;

    virtual std::any visitFnSL_Log10(exprEngineParser::FnSL_Log10Context *context) = 0;

    virtual std::any visitFnSL_Exp(exprEngineParser::FnSL_ExpContext *context) = 0;

    virtual std::any visitFnSL_Erf(exprEngineParser::FnSL_ErfContext *context) = 0;

    virtual std::any visitFnSL_CdfNorm(exprEngineParser::FnSL_CdfNormContext *context) = 0;

    virtual std::any visitFnSL_Floor(exprEngineParser::FnSL_FloorContext *context) = 0;

    virtual std::any visitFnSL_Ceil(exprEngineParser::FnSL_CeilContext *context) = 0;

    virtual std::any visitFnSL_Round(exprEngineParser::FnSL_RoundContext *context) = 0;

    virtual std::any visitFnSL_Sin(exprEngineParser::FnSL_SinContext *context) = 0;

    virtual std::any visitFnSL_Cos(exprEngineParser::FnSL_CosContext *context) = 0;

    virtual std::any visitFnSL_Tan(exprEngineParser::FnSL_TanContext *context) = 0;

    virtual std::any visitFnSL_CloseEnough(exprEngineParser::FnSL_CloseEnoughContext *context) = 0;

    virtual std::any visitFnSL_Length(exprEngineParser::FnSL_LengthContext *context) = 0;

    virtual std::any visitFnSL_Contains(exprEngineParser::FnSL_ContainsContext *context) = 0;

    virtual std::any visitFnSL_StartsWith(exprEngineParser::FnSL_StartsWithContext *context) = 0;

    virtual std::any visitFnSL_EndsWith(exprEngineParser::FnSL_EndsWithContext *context) = 0;

    virtual std::any visitFnSL_Like(exprEngineParser::FnSL_LikeContext *context) = 0;

    virtual std::any visitFnSL_Year(exprEngineParser::FnSL_YearContext *context) = 0;

    virtual std::any visitFnSL_Month(exprEngineParser::FnSL_MonthContext *context) = 0;

    virtual std::any visitFnSL_Day(exprEngineParser::FnSL_DayContext *context) = 0;

    virtual std::any visitFnSL_Hour(exprEngineParser::FnSL_HourContext *context) = 0;

    virtual std::any visitFnSL_Minute(exprEngineParser::FnSL_MinuteContext *context) = 0;

    virtual std::any visitFnSL_Second(exprEngineParser::FnSL_SecondContext *context) = 0;

    virtual std::any visitFnSL_SecondOfDay(exprEngineParser::FnSL_SecondOfDayContext *context) = 0;

    virtual std::any visitFnSL_WeekOfMonth(exprEngineParser::FnSL_WeekOfMonthContext *context) = 0;

    virtual std::any visitFnSL_DayOfWeek(exprEngineParser::FnSL_DayOfWeekContext *context) = 0;

    virtual std::any visitFnSL_WeekOfYear(exprEngineParser::FnSL_WeekOfYearContext *context) = 0;

    virtual std::any visitFnSL_DateDiff(exprEngineParser::FnSL_DateDiffContext *context) = 0;

    virtual std::any visitFnSL_DateAdd(exprEngineParser::FnSL_DateAddContext *context) = 0;

    virtual std::any visitLiteral(exprEngineParser::LiteralContext *context) = 0;

    virtual std::any visitRealLit(exprEngineParser::RealLitContext *context) = 0;

    virtual std::any visitIntLit(exprEngineParser::IntLitContext *context) = 0;

    virtual std::any visitBoolLit(exprEngineParser::BoolLitContext *context) = 0;

    virtual std::any visitStringLit(exprEngineParser::StringLitContext *context) = 0;

    virtual std::any visitTimestampLit(exprEngineParser::TimestampLitContext *context) = 0;

    virtual std::any visitNullLit(exprEngineParser::NullLitContext *context) = 0;

    virtual std::any visitTimeUnit(exprEngineParser::TimeUnitContext *context) = 0;


};


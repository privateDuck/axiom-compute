
// Generated from exprEngineParser.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  exprEngineParser : public antlr4::Parser {
public:
  enum {
    YEARS = 1, MONTHS = 2, DAYS = 3, WEEKS = 4, HOURS = 5, MINUTES = 6, 
    SECONDS = 7, POPULATION = 8, SAMPLE = 9, ABS = 10, SIGN = 11, SQRT = 12, 
    POW = 13, LOG = 14, LOG2 = 15, LOG10 = 16, EXP = 17, ERF = 18, CDFNORM = 19, 
    FLOOR = 20, CEIL = 21, ROUND = 22, SIN = 23, COS = 24, TAN = 25, CLOSEENOUGH = 26, 
    AGGREGATE = 27, OVER = 28, MEAN = 29, MEDIAN = 30, STDDEV = 31, VARIANCE = 32, 
    MAX = 33, MIN = 34, SUM = 35, PROD = 36, LENGTH = 37, CONTAINS = 38, 
    STARTSWITH = 39, ENDSWITH = 40, LIKE = 41, DATEDIFF = 42, DATEADD = 43, 
    WEEKOFYEAR = 44, WEEKOFMONTH = 45, DAYOFWEEK = 46, SECONDOFDAY = 47, 
    YEAR = 48, MONTH = 49, DAY = 50, HOUR = 51, MINUTE = 52, SECOND = 53, 
    TRUE = 54, FALSE = 55, NULL_ = 56, NOT = 57, AND = 58, OR = 59, EQ = 60, 
    NEQ = 61, LT = 62, GT = 63, LTE = 64, GTE = 65, PLUS = 66, MINUS = 67, 
    STAR = 68, SLASH = 69, DSLASH = 70, PERCENT = 71, CARET = 72, CONCAT = 73, 
    COMMA = 74, LPAREN = 75, RPAREN = 76, PIPE = 77, LBRACKET = 78, RBRACKET = 79, 
    SQUOTE = 80, BACKTICK = 81, QUOTED_IDENTIFIER = 82, IDENTIFIER = 83, 
    REAL_LITERAL = 84, INT_LITERAL = 85, ISO_DATETIME = 86, ISO_DATE = 87, 
    ISO_TIME = 88, STRING_LITERAL = 89, UNTERMINATED_STRING_LITERAL = 90, 
    WS = 91
  };

  enum {
    RuleExpression = 0, RuleExpr = 1, RuleAggregateOver = 2, RuleIdentifier = 3, 
    RuleFunctionCall = 4, RuleStatelessFn = 5, RuleAggregateFn = 6, RuleMathFn = 7, 
    RuleStringFn = 8, RuleTimestampFn = 9, RuleLiteral = 10, RuleRealLit = 11, 
    RuleIntLit = 12, RuleBoolLit = 13, RuleStringLit = 14, RuleTimestampLit = 15, 
    RuleNullLit = 16, RuleTimeUnit = 17
  };

  explicit exprEngineParser(antlr4::TokenStream *input);

  exprEngineParser(antlr4::TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options);

  ~exprEngineParser() override;

  std::string getGrammarFileName() const override;

  const antlr4::atn::ATN& getATN() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;


  class ExpressionContext;
  class ExprContext;
  class AggregateOverContext;
  class IdentifierContext;
  class FunctionCallContext;
  class StatelessFnContext;
  class AggregateFnContext;
  class MathFnContext;
  class StringFnContext;
  class TimestampFnContext;
  class LiteralContext;
  class RealLitContext;
  class IntLitContext;
  class BoolLitContext;
  class StringLitContext;
  class TimestampLitContext;
  class NullLitContext;
  class TimeUnitContext; 

  class  ExpressionContext : public antlr4::ParserRuleContext {
  public:
    ExpressionContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    ExprContext *expr();
    AggregateOverContext *aggregateOver();
    antlr4::tree::TerminalNode *EOF();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  ExpressionContext* expression();

  class  ExprContext : public antlr4::ParserRuleContext {
  public:
    int returnType = 0;
    ExprContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    ExprContext() = default;
    void copyFrom(ExprContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  ExprNotContext : public ExprContext {
  public:
    ExprNotContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *NOT();
    ExprContext *expr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprNegateContext : public ExprContext {
  public:
    ExprNegateContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *MINUS();
    ExprContext *expr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprDivContext : public ExprContext {
  public:
    ExprDivContext(ExprContext *ctx);

    exprEngineParser::ExprContext *left = nullptr;
    exprEngineParser::ExprContext *right = nullptr;
    antlr4::tree::TerminalNode *SLASH();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprAbsContext : public ExprContext {
  public:
    ExprAbsContext(ExprContext *ctx);

    std::vector<antlr4::tree::TerminalNode *> PIPE();
    antlr4::tree::TerminalNode* PIPE(size_t i);
    ExprContext *expr();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprEqContext : public ExprContext {
  public:
    ExprEqContext(ExprContext *ctx);

    exprEngineParser::ExprContext *left = nullptr;
    exprEngineParser::ExprContext *right = nullptr;
    antlr4::tree::TerminalNode *EQ();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprGtContext : public ExprContext {
  public:
    ExprGtContext(ExprContext *ctx);

    exprEngineParser::ExprContext *left = nullptr;
    exprEngineParser::ExprContext *right = nullptr;
    antlr4::tree::TerminalNode *GT();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprLiteralContext : public ExprContext {
  public:
    ExprLiteralContext(ExprContext *ctx);

    LiteralContext *literal();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprParenContext : public ExprContext {
  public:
    ExprParenContext(ExprContext *ctx);

    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprSubContext : public ExprContext {
  public:
    ExprSubContext(ExprContext *ctx);

    exprEngineParser::ExprContext *left = nullptr;
    exprEngineParser::ExprContext *right = nullptr;
    antlr4::tree::TerminalNode *MINUS();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprOrContext : public ExprContext {
  public:
    ExprOrContext(ExprContext *ctx);

    exprEngineParser::ExprContext *left = nullptr;
    exprEngineParser::ExprContext *right = nullptr;
    antlr4::tree::TerminalNode *OR();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprExpContext : public ExprContext {
  public:
    ExprExpContext(ExprContext *ctx);

    exprEngineParser::ExprContext *left = nullptr;
    exprEngineParser::ExprContext *right = nullptr;
    antlr4::tree::TerminalNode *CARET();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprLteContext : public ExprContext {
  public:
    ExprLteContext(ExprContext *ctx);

    exprEngineParser::ExprContext *left = nullptr;
    exprEngineParser::ExprContext *right = nullptr;
    antlr4::tree::TerminalNode *LTE();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprCallContext : public ExprContext {
  public:
    ExprCallContext(ExprContext *ctx);

    FunctionCallContext *functionCall();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprLtContext : public ExprContext {
  public:
    ExprLtContext(ExprContext *ctx);

    exprEngineParser::ExprContext *left = nullptr;
    exprEngineParser::ExprContext *right = nullptr;
    antlr4::tree::TerminalNode *LT();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprMulContext : public ExprContext {
  public:
    ExprMulContext(ExprContext *ctx);

    exprEngineParser::ExprContext *left = nullptr;
    exprEngineParser::ExprContext *right = nullptr;
    antlr4::tree::TerminalNode *STAR();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprConcatContext : public ExprContext {
  public:
    ExprConcatContext(ExprContext *ctx);

    exprEngineParser::ExprContext *left = nullptr;
    exprEngineParser::ExprContext *right = nullptr;
    antlr4::tree::TerminalNode *CONCAT();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprAddContext : public ExprContext {
  public:
    ExprAddContext(ExprContext *ctx);

    exprEngineParser::ExprContext *left = nullptr;
    exprEngineParser::ExprContext *right = nullptr;
    antlr4::tree::TerminalNode *PLUS();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprModContext : public ExprContext {
  public:
    ExprModContext(ExprContext *ctx);

    exprEngineParser::ExprContext *left = nullptr;
    exprEngineParser::ExprContext *right = nullptr;
    antlr4::tree::TerminalNode *PERCENT();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprAndContext : public ExprContext {
  public:
    ExprAndContext(ExprContext *ctx);

    exprEngineParser::ExprContext *left = nullptr;
    exprEngineParser::ExprContext *right = nullptr;
    antlr4::tree::TerminalNode *AND();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprGteContext : public ExprContext {
  public:
    ExprGteContext(ExprContext *ctx);

    exprEngineParser::ExprContext *left = nullptr;
    exprEngineParser::ExprContext *right = nullptr;
    antlr4::tree::TerminalNode *GTE();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprIntDivContext : public ExprContext {
  public:
    ExprIntDivContext(ExprContext *ctx);

    exprEngineParser::ExprContext *left = nullptr;
    exprEngineParser::ExprContext *right = nullptr;
    antlr4::tree::TerminalNode *DSLASH();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprIndentifierContext : public ExprContext {
  public:
    ExprIndentifierContext(ExprContext *ctx);

    IdentifierContext *identifier();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  ExprNeqContext : public ExprContext {
  public:
    ExprNeqContext(ExprContext *ctx);

    exprEngineParser::ExprContext *left = nullptr;
    exprEngineParser::ExprContext *right = nullptr;
    antlr4::tree::TerminalNode *NEQ();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  ExprContext* expr();
  ExprContext* expr(int precedence);
  class  AggregateOverContext : public antlr4::ParserRuleContext {
  public:
    AggregateOverContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *AGGREGATE();
    AggregateFnContext *aggregateFn();
    antlr4::tree::TerminalNode *OVER();
    IdentifierContext *identifier();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  AggregateOverContext* aggregateOver();

  class  IdentifierContext : public antlr4::ParserRuleContext {
  public:
    IdentifierContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *IDENTIFIER();
    antlr4::tree::TerminalNode *QUOTED_IDENTIFIER();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IdentifierContext* identifier();

  class  FunctionCallContext : public antlr4::ParserRuleContext {
  public:
    FunctionCallContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    StatelessFnContext *statelessFn();
    AggregateFnContext *aggregateFn();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  FunctionCallContext* functionCall();

  class  StatelessFnContext : public antlr4::ParserRuleContext {
  public:
    StatelessFnContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    MathFnContext *mathFn();
    StringFnContext *stringFn();
    TimestampFnContext *timestampFn();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StatelessFnContext* statelessFn();

  class  AggregateFnContext : public antlr4::ParserRuleContext {
  public:
    AggregateFnContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    AggregateFnContext() = default;
    void copyFrom(AggregateFnContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  FnAgg_MeanContext : public AggregateFnContext {
  public:
    FnAgg_MeanContext(AggregateFnContext *ctx);

    antlr4::tree::TerminalNode *MEAN();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnAgg_SumContext : public AggregateFnContext {
  public:
    FnAgg_SumContext(AggregateFnContext *ctx);

    antlr4::tree::TerminalNode *SUM();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnAgg_ProdContext : public AggregateFnContext {
  public:
    FnAgg_ProdContext(AggregateFnContext *ctx);

    antlr4::tree::TerminalNode *PROD();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnAgg_MedianContext : public AggregateFnContext {
  public:
    FnAgg_MedianContext(AggregateFnContext *ctx);

    antlr4::tree::TerminalNode *MEDIAN();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnAgg_MinContext : public AggregateFnContext {
  public:
    FnAgg_MinContext(AggregateFnContext *ctx);

    antlr4::tree::TerminalNode *MIN();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnAgg_MaxContext : public AggregateFnContext {
  public:
    FnAgg_MaxContext(AggregateFnContext *ctx);

    antlr4::tree::TerminalNode *MAX();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnAgg_VarianceContext : public AggregateFnContext {
  public:
    FnAgg_VarianceContext(AggregateFnContext *ctx);

    antlr4::tree::TerminalNode *VARIANCE();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnAgg_StdDevContext : public AggregateFnContext {
  public:
    FnAgg_StdDevContext(AggregateFnContext *ctx);

    antlr4::tree::TerminalNode *STDDEV();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  AggregateFnContext* aggregateFn();

  class  MathFnContext : public antlr4::ParserRuleContext {
  public:
    MathFnContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    MathFnContext() = default;
    void copyFrom(MathFnContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  FnSL_Log10Context : public MathFnContext {
  public:
    FnSL_Log10Context(MathFnContext *ctx);

    antlr4::tree::TerminalNode *LOG10();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_TanContext : public MathFnContext {
  public:
    FnSL_TanContext(MathFnContext *ctx);

    antlr4::tree::TerminalNode *TAN();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_FloorContext : public MathFnContext {
  public:
    FnSL_FloorContext(MathFnContext *ctx);

    antlr4::tree::TerminalNode *FLOOR();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_SqrtContext : public MathFnContext {
  public:
    FnSL_SqrtContext(MathFnContext *ctx);

    antlr4::tree::TerminalNode *SQRT();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_LogContext : public MathFnContext {
  public:
    FnSL_LogContext(MathFnContext *ctx);

    antlr4::tree::TerminalNode *LOG();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_SignContext : public MathFnContext {
  public:
    FnSL_SignContext(MathFnContext *ctx);

    antlr4::tree::TerminalNode *SIGN();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_CdfNormContext : public MathFnContext {
  public:
    FnSL_CdfNormContext(MathFnContext *ctx);

    antlr4::tree::TerminalNode *CDFNORM();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_RoundContext : public MathFnContext {
  public:
    FnSL_RoundContext(MathFnContext *ctx);

    antlr4::tree::TerminalNode *ROUND();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_CloseEnoughContext : public MathFnContext {
  public:
    FnSL_CloseEnoughContext(MathFnContext *ctx);

    exprEngineParser::ExprContext *arg1 = nullptr;
    exprEngineParser::ExprContext *arg2 = nullptr;
    antlr4::tree::TerminalNode *CLOSEENOUGH();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_CosContext : public MathFnContext {
  public:
    FnSL_CosContext(MathFnContext *ctx);

    antlr4::tree::TerminalNode *COS();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_Log2Context : public MathFnContext {
  public:
    FnSL_Log2Context(MathFnContext *ctx);

    antlr4::tree::TerminalNode *LOG2();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_AbsContext : public MathFnContext {
  public:
    FnSL_AbsContext(MathFnContext *ctx);

    antlr4::tree::TerminalNode *ABS();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_CeilContext : public MathFnContext {
  public:
    FnSL_CeilContext(MathFnContext *ctx);

    antlr4::tree::TerminalNode *CEIL();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_PowContext : public MathFnContext {
  public:
    FnSL_PowContext(MathFnContext *ctx);

    exprEngineParser::ExprContext *left = nullptr;
    exprEngineParser::ExprContext *right = nullptr;
    antlr4::tree::TerminalNode *POW();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_ErfContext : public MathFnContext {
  public:
    FnSL_ErfContext(MathFnContext *ctx);

    antlr4::tree::TerminalNode *ERF();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_SinContext : public MathFnContext {
  public:
    FnSL_SinContext(MathFnContext *ctx);

    antlr4::tree::TerminalNode *SIN();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_ExpContext : public MathFnContext {
  public:
    FnSL_ExpContext(MathFnContext *ctx);

    antlr4::tree::TerminalNode *EXP();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  MathFnContext* mathFn();

  class  StringFnContext : public antlr4::ParserRuleContext {
  public:
    StringFnContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    StringFnContext() = default;
    void copyFrom(StringFnContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  FnSL_ContainsContext : public StringFnContext {
  public:
    FnSL_ContainsContext(StringFnContext *ctx);

    exprEngineParser::ExprContext *input = nullptr;
    exprEngineParser::ExprContext *pattern = nullptr;
    antlr4::tree::TerminalNode *CONTAINS();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_StartsWithContext : public StringFnContext {
  public:
    FnSL_StartsWithContext(StringFnContext *ctx);

    exprEngineParser::ExprContext *input = nullptr;
    exprEngineParser::ExprContext *pattern = nullptr;
    antlr4::tree::TerminalNode *STARTSWITH();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_LikeContext : public StringFnContext {
  public:
    FnSL_LikeContext(StringFnContext *ctx);

    exprEngineParser::ExprContext *input = nullptr;
    exprEngineParser::ExprContext *pattern = nullptr;
    antlr4::tree::TerminalNode *LIKE();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_LengthContext : public StringFnContext {
  public:
    FnSL_LengthContext(StringFnContext *ctx);

    antlr4::tree::TerminalNode *LENGTH();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_EndsWithContext : public StringFnContext {
  public:
    FnSL_EndsWithContext(StringFnContext *ctx);

    exprEngineParser::ExprContext *input = nullptr;
    exprEngineParser::ExprContext *pattern = nullptr;
    antlr4::tree::TerminalNode *ENDSWITH();
    antlr4::tree::TerminalNode *LPAREN();
    antlr4::tree::TerminalNode *COMMA();
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  StringFnContext* stringFn();

  class  TimestampFnContext : public antlr4::ParserRuleContext {
  public:
    TimestampFnContext(antlr4::ParserRuleContext *parent, size_t invokingState);
   
    TimestampFnContext() = default;
    void copyFrom(TimestampFnContext *context);
    using antlr4::ParserRuleContext::copyFrom;

    virtual size_t getRuleIndex() const override;

   
  };

  class  FnSL_MonthContext : public TimestampFnContext {
  public:
    FnSL_MonthContext(TimestampFnContext *ctx);

    antlr4::tree::TerminalNode *MONTH();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_DateDiffContext : public TimestampFnContext {
  public:
    FnSL_DateDiffContext(TimestampFnContext *ctx);

    exprEngineParser::ExprContext *date1 = nullptr;
    exprEngineParser::ExprContext *date2 = nullptr;
    exprEngineParser::TimeUnitContext *unit = nullptr;
    antlr4::tree::TerminalNode *DATEDIFF();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    TimeUnitContext *timeUnit();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_YearContext : public TimestampFnContext {
  public:
    FnSL_YearContext(TimestampFnContext *ctx);

    antlr4::tree::TerminalNode *YEAR();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_MinuteContext : public TimestampFnContext {
  public:
    FnSL_MinuteContext(TimestampFnContext *ctx);

    antlr4::tree::TerminalNode *MINUTE();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_SecondContext : public TimestampFnContext {
  public:
    FnSL_SecondContext(TimestampFnContext *ctx);

    antlr4::tree::TerminalNode *SECOND();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_SecondOfDayContext : public TimestampFnContext {
  public:
    FnSL_SecondOfDayContext(TimestampFnContext *ctx);

    antlr4::tree::TerminalNode *SECONDOFDAY();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_DayOfWeekContext : public TimestampFnContext {
  public:
    FnSL_DayOfWeekContext(TimestampFnContext *ctx);

    antlr4::tree::TerminalNode *DAYOFWEEK();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_DateAddContext : public TimestampFnContext {
  public:
    FnSL_DateAddContext(TimestampFnContext *ctx);

    exprEngineParser::ExprContext *date1 = nullptr;
    exprEngineParser::ExprContext *duration = nullptr;
    exprEngineParser::TimeUnitContext *unit = nullptr;
    antlr4::tree::TerminalNode *DATEADD();
    antlr4::tree::TerminalNode *LPAREN();
    std::vector<antlr4::tree::TerminalNode *> COMMA();
    antlr4::tree::TerminalNode* COMMA(size_t i);
    antlr4::tree::TerminalNode *RPAREN();
    std::vector<ExprContext *> expr();
    ExprContext* expr(size_t i);
    TimeUnitContext *timeUnit();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_HourContext : public TimestampFnContext {
  public:
    FnSL_HourContext(TimestampFnContext *ctx);

    antlr4::tree::TerminalNode *HOUR();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_WeekOfYearContext : public TimestampFnContext {
  public:
    FnSL_WeekOfYearContext(TimestampFnContext *ctx);

    antlr4::tree::TerminalNode *WEEKOFYEAR();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_WeekOfMonthContext : public TimestampFnContext {
  public:
    FnSL_WeekOfMonthContext(TimestampFnContext *ctx);

    antlr4::tree::TerminalNode *WEEKOFMONTH();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  class  FnSL_DayContext : public TimestampFnContext {
  public:
    FnSL_DayContext(TimestampFnContext *ctx);

    antlr4::tree::TerminalNode *DAY();
    antlr4::tree::TerminalNode *LPAREN();
    ExprContext *expr();
    antlr4::tree::TerminalNode *RPAREN();
    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
  };

  TimestampFnContext* timestampFn();

  class  LiteralContext : public antlr4::ParserRuleContext {
  public:
    LiteralContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    RealLitContext *realLit();
    IntLitContext *intLit();
    BoolLitContext *boolLit();
    StringLitContext *stringLit();
    TimestampLitContext *timestampLit();
    NullLitContext *nullLit();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  LiteralContext* literal();

  class  RealLitContext : public antlr4::ParserRuleContext {
  public:
    RealLitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *REAL_LITERAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  RealLitContext* realLit();

  class  IntLitContext : public antlr4::ParserRuleContext {
  public:
    IntLitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *INT_LITERAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  IntLitContext* intLit();

  class  BoolLitContext : public antlr4::ParserRuleContext {
  public:
    BoolLitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *TRUE();
    antlr4::tree::TerminalNode *FALSE();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  BoolLitContext* boolLit();

  class  StringLitContext : public antlr4::ParserRuleContext {
  public:
    StringLitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *STRING_LITERAL();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  StringLitContext* stringLit();

  class  TimestampLitContext : public antlr4::ParserRuleContext {
  public:
    TimestampLitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *ISO_DATETIME();
    antlr4::tree::TerminalNode *ISO_DATE();
    antlr4::tree::TerminalNode *ISO_TIME();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TimestampLitContext* timestampLit();

  class  NullLitContext : public antlr4::ParserRuleContext {
  public:
    NullLitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *NULL_();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  NullLitContext* nullLit();

  class  TimeUnitContext : public antlr4::ParserRuleContext {
  public:
    TimeUnitContext(antlr4::ParserRuleContext *parent, size_t invokingState);
    virtual size_t getRuleIndex() const override;
    antlr4::tree::TerminalNode *YEARS();
    antlr4::tree::TerminalNode *MONTHS();
    antlr4::tree::TerminalNode *DAYS();
    antlr4::tree::TerminalNode *WEEKS();
    antlr4::tree::TerminalNode *HOURS();
    antlr4::tree::TerminalNode *MINUTES();
    antlr4::tree::TerminalNode *SECONDS();

    virtual void enterRule(antlr4::tree::ParseTreeListener *listener) override;
    virtual void exitRule(antlr4::tree::ParseTreeListener *listener) override;

    virtual std::any accept(antlr4::tree::ParseTreeVisitor *visitor) override;
   
  };

  TimeUnitContext* timeUnit();


  bool sempred(antlr4::RuleContext *_localctx, size_t ruleIndex, size_t predicateIndex) override;

  bool exprSempred(ExprContext *_localctx, size_t predicateIndex);

  // By default the static state used to implement the parser is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:
};


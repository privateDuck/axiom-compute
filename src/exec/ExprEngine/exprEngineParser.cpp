
// Generated from exprEngineParser.g4 by ANTLR 4.13.2


#include "exprEngineParserListener.h"
#include "exprEngineParserVisitor.h"

#include "exprEngineParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct ExprEngineParserStaticData final {
  ExprEngineParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  ExprEngineParserStaticData(const ExprEngineParserStaticData&) = delete;
  ExprEngineParserStaticData(ExprEngineParserStaticData&&) = delete;
  ExprEngineParserStaticData& operator=(const ExprEngineParserStaticData&) = delete;
  ExprEngineParserStaticData& operator=(ExprEngineParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag exprengineparserParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<ExprEngineParserStaticData> exprengineparserParserStaticData = nullptr;

void exprengineparserParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (exprengineparserParserStaticData != nullptr) {
    return;
  }
#else
  assert(exprengineparserParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<ExprEngineParserStaticData>(
    std::vector<std::string>{
      "expression", "expr", "aggregateOver", "identifier", "functionCall", 
      "statelessFn", "aggregateFn", "mathFn", "stringFn", "timestampFn", 
      "literal", "realLit", "intLit", "boolLit", "stringLit", "timestampLit", 
      "nullLit", "timeUnit"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "", "", "", "", "", "", "", "", "", "'='", "'!='", "'<'", "'>'", "'<='", 
      "'>='", "'+'", "'-'", "'*'", "'/'", "'//'", "'%'", "'^'", "'||'", 
      "','", "'('", "')'", "'|'", "'['", "']'", "'''", "'`'"
    },
    std::vector<std::string>{
      "", "YEARS", "MONTHS", "DAYS", "WEEKS", "HOURS", "MINUTES", "SECONDS", 
      "POPULATION", "SAMPLE", "ABS", "SIGN", "SQRT", "POW", "LOG", "LOG2", 
      "LOG10", "EXP", "ERF", "CDFNORM", "FLOOR", "CEIL", "ROUND", "SIN", 
      "COS", "TAN", "CLOSEENOUGH", "AGGREGATE", "OVER", "MEAN", "MEDIAN", 
      "STDDEV", "VARIANCE", "MAX", "MIN", "SUM", "PROD", "LENGTH", "CONTAINS", 
      "STARTSWITH", "ENDSWITH", "LIKE", "DATEDIFF", "DATEADD", "WEEKOFYEAR", 
      "WEEKOFMONTH", "DAYOFWEEK", "SECONDOFDAY", "YEAR", "MONTH", "DAY", 
      "HOUR", "MINUTE", "SECOND", "TRUE", "FALSE", "NULL_", "NOT", "AND", 
      "OR", "EQ", "NEQ", "LT", "GT", "LTE", "GTE", "PLUS", "MINUS", "STAR", 
      "SLASH", "DSLASH", "PERCENT", "CARET", "CONCAT", "COMMA", "LPAREN", 
      "RPAREN", "PIPE", "LBRACKET", "RBRACKET", "SQUOTE", "BACKTICK", "QUOTED_IDENTIFIER", 
      "IDENTIFIER", "REAL_LITERAL", "INT_LITERAL", "ISO_DATETIME", "ISO_DATE", 
      "ISO_TIME", "STRING_LITERAL", "UNTERMINATED_STRING_LITERAL", "WS"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,91,389,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,2,16,7,16,2,17,7,17,1,0,1,0,1,0,3,0,40,8,0,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,3,1,58,8,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,
  	1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,5,1,108,8,1,10,1,12,1,111,
  	9,1,1,2,1,2,1,2,1,2,1,2,1,3,1,3,1,4,1,4,3,4,122,8,4,1,5,1,5,1,5,3,5,127,
  	8,5,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,
  	6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,1,6,
  	1,6,1,6,1,6,1,6,1,6,1,6,3,6,169,8,6,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,
  	7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,
  	1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,
  	7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,
  	1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,
  	7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,1,7,3,7,260,8,7,1,8,1,8,1,8,1,8,
  	1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,
  	8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,1,8,3,8,295,8,8,1,9,1,9,1,9,
  	1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,
  	9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,
  	1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,
  	9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,3,9,365,8,9,1,10,1,
  	10,1,10,1,10,1,10,1,10,3,10,373,8,10,1,11,1,11,1,12,1,12,1,13,1,13,1,
  	14,1,14,1,15,1,15,1,16,1,16,1,17,1,17,1,17,0,1,2,18,0,2,4,6,8,10,12,14,
  	16,18,20,22,24,26,28,30,32,34,0,4,1,0,82,83,1,0,54,55,1,0,86,88,1,0,1,
  	7,440,0,39,1,0,0,0,2,57,1,0,0,0,4,112,1,0,0,0,6,117,1,0,0,0,8,121,1,0,
  	0,0,10,126,1,0,0,0,12,168,1,0,0,0,14,259,1,0,0,0,16,294,1,0,0,0,18,364,
  	1,0,0,0,20,372,1,0,0,0,22,374,1,0,0,0,24,376,1,0,0,0,26,378,1,0,0,0,28,
  	380,1,0,0,0,30,382,1,0,0,0,32,384,1,0,0,0,34,386,1,0,0,0,36,40,3,2,1,
  	0,37,40,3,4,2,0,38,40,5,0,0,1,39,36,1,0,0,0,39,37,1,0,0,0,39,38,1,0,0,
  	0,40,1,1,0,0,0,41,42,6,1,-1,0,42,43,5,75,0,0,43,44,3,2,1,0,44,45,5,76,
  	0,0,45,58,1,0,0,0,46,47,5,77,0,0,47,48,3,2,1,0,48,49,5,77,0,0,49,58,1,
  	0,0,0,50,58,3,8,4,0,51,52,5,67,0,0,52,58,3,2,1,19,53,54,5,57,0,0,54,58,
  	3,2,1,18,55,58,3,20,10,0,56,58,3,6,3,0,57,41,1,0,0,0,57,46,1,0,0,0,57,
  	50,1,0,0,0,57,51,1,0,0,0,57,53,1,0,0,0,57,55,1,0,0,0,57,56,1,0,0,0,58,
  	109,1,0,0,0,59,60,10,20,0,0,60,61,5,72,0,0,61,108,3,2,1,20,62,63,10,17,
  	0,0,63,64,5,68,0,0,64,108,3,2,1,18,65,66,10,16,0,0,66,67,5,69,0,0,67,
  	108,3,2,1,17,68,69,10,15,0,0,69,70,5,71,0,0,70,108,3,2,1,16,71,72,10,
  	14,0,0,72,73,5,70,0,0,73,108,3,2,1,15,74,75,10,13,0,0,75,76,5,66,0,0,
  	76,108,3,2,1,14,77,78,10,12,0,0,78,79,5,67,0,0,79,108,3,2,1,13,80,81,
  	10,11,0,0,81,82,5,60,0,0,82,108,3,2,1,12,83,84,10,10,0,0,84,85,5,61,0,
  	0,85,108,3,2,1,11,86,87,10,9,0,0,87,88,5,62,0,0,88,108,3,2,1,10,89,90,
  	10,8,0,0,90,91,5,64,0,0,91,108,3,2,1,9,92,93,10,7,0,0,93,94,5,63,0,0,
  	94,108,3,2,1,8,95,96,10,6,0,0,96,97,5,65,0,0,97,108,3,2,1,7,98,99,10,
  	5,0,0,99,100,5,58,0,0,100,108,3,2,1,6,101,102,10,4,0,0,102,103,5,59,0,
  	0,103,108,3,2,1,5,104,105,10,3,0,0,105,106,5,73,0,0,106,108,3,2,1,4,107,
  	59,1,0,0,0,107,62,1,0,0,0,107,65,1,0,0,0,107,68,1,0,0,0,107,71,1,0,0,
  	0,107,74,1,0,0,0,107,77,1,0,0,0,107,80,1,0,0,0,107,83,1,0,0,0,107,86,
  	1,0,0,0,107,89,1,0,0,0,107,92,1,0,0,0,107,95,1,0,0,0,107,98,1,0,0,0,107,
  	101,1,0,0,0,107,104,1,0,0,0,108,111,1,0,0,0,109,107,1,0,0,0,109,110,1,
  	0,0,0,110,3,1,0,0,0,111,109,1,0,0,0,112,113,5,27,0,0,113,114,3,12,6,0,
  	114,115,5,28,0,0,115,116,3,6,3,0,116,5,1,0,0,0,117,118,7,0,0,0,118,7,
  	1,0,0,0,119,122,3,10,5,0,120,122,3,12,6,0,121,119,1,0,0,0,121,120,1,0,
  	0,0,122,9,1,0,0,0,123,127,3,14,7,0,124,127,3,16,8,0,125,127,3,18,9,0,
  	126,123,1,0,0,0,126,124,1,0,0,0,126,125,1,0,0,0,127,11,1,0,0,0,128,129,
  	5,29,0,0,129,130,5,75,0,0,130,131,3,2,1,0,131,132,5,76,0,0,132,169,1,
  	0,0,0,133,134,5,30,0,0,134,135,5,75,0,0,135,136,3,2,1,0,136,137,5,76,
  	0,0,137,169,1,0,0,0,138,139,5,31,0,0,139,140,5,75,0,0,140,141,3,2,1,0,
  	141,142,5,76,0,0,142,169,1,0,0,0,143,144,5,32,0,0,144,145,5,75,0,0,145,
  	146,3,2,1,0,146,147,5,76,0,0,147,169,1,0,0,0,148,149,5,33,0,0,149,150,
  	5,75,0,0,150,151,3,2,1,0,151,152,5,76,0,0,152,169,1,0,0,0,153,154,5,34,
  	0,0,154,155,5,75,0,0,155,156,3,2,1,0,156,157,5,76,0,0,157,169,1,0,0,0,
  	158,159,5,35,0,0,159,160,5,75,0,0,160,161,3,2,1,0,161,162,5,76,0,0,162,
  	169,1,0,0,0,163,164,5,36,0,0,164,165,5,75,0,0,165,166,3,2,1,0,166,167,
  	5,76,0,0,167,169,1,0,0,0,168,128,1,0,0,0,168,133,1,0,0,0,168,138,1,0,
  	0,0,168,143,1,0,0,0,168,148,1,0,0,0,168,153,1,0,0,0,168,158,1,0,0,0,168,
  	163,1,0,0,0,169,13,1,0,0,0,170,171,5,10,0,0,171,172,5,75,0,0,172,173,
  	3,2,1,0,173,174,5,76,0,0,174,260,1,0,0,0,175,176,5,11,0,0,176,177,5,75,
  	0,0,177,178,3,2,1,0,178,179,5,76,0,0,179,260,1,0,0,0,180,181,5,12,0,0,
  	181,182,5,75,0,0,182,183,3,2,1,0,183,184,5,76,0,0,184,260,1,0,0,0,185,
  	186,5,13,0,0,186,187,5,75,0,0,187,188,3,2,1,0,188,189,5,74,0,0,189,190,
  	3,2,1,0,190,191,5,76,0,0,191,260,1,0,0,0,192,193,5,14,0,0,193,194,5,75,
  	0,0,194,195,3,2,1,0,195,196,5,76,0,0,196,260,1,0,0,0,197,198,5,15,0,0,
  	198,199,5,75,0,0,199,200,3,2,1,0,200,201,5,76,0,0,201,260,1,0,0,0,202,
  	203,5,16,0,0,203,204,5,75,0,0,204,205,3,2,1,0,205,206,5,76,0,0,206,260,
  	1,0,0,0,207,208,5,17,0,0,208,209,5,75,0,0,209,210,3,2,1,0,210,211,5,76,
  	0,0,211,260,1,0,0,0,212,213,5,18,0,0,213,214,5,75,0,0,214,215,3,2,1,0,
  	215,216,5,76,0,0,216,260,1,0,0,0,217,218,5,19,0,0,218,219,5,75,0,0,219,
  	220,3,2,1,0,220,221,5,76,0,0,221,260,1,0,0,0,222,223,5,20,0,0,223,224,
  	5,75,0,0,224,225,3,2,1,0,225,226,5,76,0,0,226,260,1,0,0,0,227,228,5,21,
  	0,0,228,229,5,75,0,0,229,230,3,2,1,0,230,231,5,76,0,0,231,260,1,0,0,0,
  	232,233,5,22,0,0,233,234,5,75,0,0,234,235,3,2,1,0,235,236,5,76,0,0,236,
  	260,1,0,0,0,237,238,5,23,0,0,238,239,5,75,0,0,239,240,3,2,1,0,240,241,
  	5,76,0,0,241,260,1,0,0,0,242,243,5,24,0,0,243,244,5,75,0,0,244,245,3,
  	2,1,0,245,246,5,76,0,0,246,260,1,0,0,0,247,248,5,25,0,0,248,249,5,75,
  	0,0,249,250,3,2,1,0,250,251,5,76,0,0,251,260,1,0,0,0,252,253,5,26,0,0,
  	253,254,5,75,0,0,254,255,3,2,1,0,255,256,5,74,0,0,256,257,3,2,1,0,257,
  	258,5,76,0,0,258,260,1,0,0,0,259,170,1,0,0,0,259,175,1,0,0,0,259,180,
  	1,0,0,0,259,185,1,0,0,0,259,192,1,0,0,0,259,197,1,0,0,0,259,202,1,0,0,
  	0,259,207,1,0,0,0,259,212,1,0,0,0,259,217,1,0,0,0,259,222,1,0,0,0,259,
  	227,1,0,0,0,259,232,1,0,0,0,259,237,1,0,0,0,259,242,1,0,0,0,259,247,1,
  	0,0,0,259,252,1,0,0,0,260,15,1,0,0,0,261,262,5,37,0,0,262,263,5,75,0,
  	0,263,264,3,2,1,0,264,265,5,76,0,0,265,295,1,0,0,0,266,267,5,38,0,0,267,
  	268,5,75,0,0,268,269,3,2,1,0,269,270,5,74,0,0,270,271,3,2,1,0,271,272,
  	5,76,0,0,272,295,1,0,0,0,273,274,5,39,0,0,274,275,5,75,0,0,275,276,3,
  	2,1,0,276,277,5,74,0,0,277,278,3,2,1,0,278,279,5,76,0,0,279,295,1,0,0,
  	0,280,281,5,40,0,0,281,282,5,75,0,0,282,283,3,2,1,0,283,284,5,74,0,0,
  	284,285,3,2,1,0,285,286,5,76,0,0,286,295,1,0,0,0,287,288,5,41,0,0,288,
  	289,5,75,0,0,289,290,3,2,1,0,290,291,5,74,0,0,291,292,3,2,1,0,292,293,
  	5,76,0,0,293,295,1,0,0,0,294,261,1,0,0,0,294,266,1,0,0,0,294,273,1,0,
  	0,0,294,280,1,0,0,0,294,287,1,0,0,0,295,17,1,0,0,0,296,297,5,48,0,0,297,
  	298,5,75,0,0,298,299,3,2,1,0,299,300,5,76,0,0,300,365,1,0,0,0,301,302,
  	5,49,0,0,302,303,5,75,0,0,303,304,3,2,1,0,304,305,5,76,0,0,305,365,1,
  	0,0,0,306,307,5,50,0,0,307,308,5,75,0,0,308,309,3,2,1,0,309,310,5,76,
  	0,0,310,365,1,0,0,0,311,312,5,51,0,0,312,313,5,75,0,0,313,314,3,2,1,0,
  	314,315,5,76,0,0,315,365,1,0,0,0,316,317,5,52,0,0,317,318,5,75,0,0,318,
  	319,3,2,1,0,319,320,5,76,0,0,320,365,1,0,0,0,321,322,5,53,0,0,322,323,
  	5,75,0,0,323,324,3,2,1,0,324,325,5,76,0,0,325,365,1,0,0,0,326,327,5,47,
  	0,0,327,328,5,75,0,0,328,329,3,2,1,0,329,330,5,76,0,0,330,365,1,0,0,0,
  	331,332,5,45,0,0,332,333,5,75,0,0,333,334,3,2,1,0,334,335,5,76,0,0,335,
  	365,1,0,0,0,336,337,5,46,0,0,337,338,5,75,0,0,338,339,3,2,1,0,339,340,
  	5,76,0,0,340,365,1,0,0,0,341,342,5,44,0,0,342,343,5,75,0,0,343,344,3,
  	2,1,0,344,345,5,76,0,0,345,365,1,0,0,0,346,347,5,42,0,0,347,348,5,75,
  	0,0,348,349,3,2,1,0,349,350,5,74,0,0,350,351,3,2,1,0,351,352,5,74,0,0,
  	352,353,3,34,17,0,353,354,5,76,0,0,354,365,1,0,0,0,355,356,5,43,0,0,356,
  	357,5,75,0,0,357,358,3,2,1,0,358,359,5,74,0,0,359,360,3,2,1,0,360,361,
  	5,74,0,0,361,362,3,34,17,0,362,363,5,76,0,0,363,365,1,0,0,0,364,296,1,
  	0,0,0,364,301,1,0,0,0,364,306,1,0,0,0,364,311,1,0,0,0,364,316,1,0,0,0,
  	364,321,1,0,0,0,364,326,1,0,0,0,364,331,1,0,0,0,364,336,1,0,0,0,364,341,
  	1,0,0,0,364,346,1,0,0,0,364,355,1,0,0,0,365,19,1,0,0,0,366,373,3,22,11,
  	0,367,373,3,24,12,0,368,373,3,26,13,0,369,373,3,28,14,0,370,373,3,30,
  	15,0,371,373,3,32,16,0,372,366,1,0,0,0,372,367,1,0,0,0,372,368,1,0,0,
  	0,372,369,1,0,0,0,372,370,1,0,0,0,372,371,1,0,0,0,373,21,1,0,0,0,374,
  	375,5,84,0,0,375,23,1,0,0,0,376,377,5,85,0,0,377,25,1,0,0,0,378,379,7,
  	1,0,0,379,27,1,0,0,0,380,381,5,89,0,0,381,29,1,0,0,0,382,383,7,2,0,0,
  	383,31,1,0,0,0,384,385,5,56,0,0,385,33,1,0,0,0,386,387,7,3,0,0,387,35,
  	1,0,0,0,11,39,57,107,109,121,126,168,259,294,364,372
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  exprengineparserParserStaticData = std::move(staticData);
}

}

exprEngineParser::exprEngineParser(TokenStream *input) : exprEngineParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

exprEngineParser::exprEngineParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  exprEngineParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *exprengineparserParserStaticData->atn, exprengineparserParserStaticData->decisionToDFA, exprengineparserParserStaticData->sharedContextCache, options);
}

exprEngineParser::~exprEngineParser() {
  delete _interpreter;
}

const atn::ATN& exprEngineParser::getATN() const {
  return *exprengineparserParserStaticData->atn;
}

std::string exprEngineParser::getGrammarFileName() const {
  return "exprEngineParser.g4";
}

const std::vector<std::string>& exprEngineParser::getRuleNames() const {
  return exprengineparserParserStaticData->ruleNames;
}

const dfa::Vocabulary& exprEngineParser::getVocabulary() const {
  return exprengineparserParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView exprEngineParser::getSerializedATN() const {
  return exprengineparserParserStaticData->serializedATN;
}


//----------------- ExpressionContext ------------------------------------------------------------------

exprEngineParser::ExpressionContext::ExpressionContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

exprEngineParser::ExprContext* exprEngineParser::ExpressionContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

exprEngineParser::AggregateOverContext* exprEngineParser::ExpressionContext::aggregateOver() {
  return getRuleContext<exprEngineParser::AggregateOverContext>(0);
}

tree::TerminalNode* exprEngineParser::ExpressionContext::EOF() {
  return getToken(exprEngineParser::EOF, 0);
}


size_t exprEngineParser::ExpressionContext::getRuleIndex() const {
  return exprEngineParser::RuleExpression;
}

void exprEngineParser::ExpressionContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExpression(this);
}

void exprEngineParser::ExpressionContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExpression(this);
}


std::any exprEngineParser::ExpressionContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExpression(this);
  else
    return visitor->visitChildren(this);
}

exprEngineParser::ExpressionContext* exprEngineParser::expression() {
  ExpressionContext *_localctx = _tracker.createInstance<ExpressionContext>(_ctx, getState());
  enterRule(_localctx, 0, exprEngineParser::RuleExpression);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(39);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case exprEngineParser::ABS:
      case exprEngineParser::SIGN:
      case exprEngineParser::SQRT:
      case exprEngineParser::POW:
      case exprEngineParser::LOG:
      case exprEngineParser::LOG2:
      case exprEngineParser::LOG10:
      case exprEngineParser::EXP:
      case exprEngineParser::ERF:
      case exprEngineParser::CDFNORM:
      case exprEngineParser::FLOOR:
      case exprEngineParser::CEIL:
      case exprEngineParser::ROUND:
      case exprEngineParser::SIN:
      case exprEngineParser::COS:
      case exprEngineParser::TAN:
      case exprEngineParser::CLOSEENOUGH:
      case exprEngineParser::MEAN:
      case exprEngineParser::MEDIAN:
      case exprEngineParser::STDDEV:
      case exprEngineParser::VARIANCE:
      case exprEngineParser::MAX:
      case exprEngineParser::MIN:
      case exprEngineParser::SUM:
      case exprEngineParser::PROD:
      case exprEngineParser::LENGTH:
      case exprEngineParser::CONTAINS:
      case exprEngineParser::STARTSWITH:
      case exprEngineParser::ENDSWITH:
      case exprEngineParser::LIKE:
      case exprEngineParser::DATEDIFF:
      case exprEngineParser::DATEADD:
      case exprEngineParser::WEEKOFYEAR:
      case exprEngineParser::WEEKOFMONTH:
      case exprEngineParser::DAYOFWEEK:
      case exprEngineParser::SECONDOFDAY:
      case exprEngineParser::YEAR:
      case exprEngineParser::MONTH:
      case exprEngineParser::DAY:
      case exprEngineParser::HOUR:
      case exprEngineParser::MINUTE:
      case exprEngineParser::SECOND:
      case exprEngineParser::TRUE:
      case exprEngineParser::FALSE:
      case exprEngineParser::NULL_:
      case exprEngineParser::NOT:
      case exprEngineParser::MINUS:
      case exprEngineParser::LPAREN:
      case exprEngineParser::PIPE:
      case exprEngineParser::QUOTED_IDENTIFIER:
      case exprEngineParser::IDENTIFIER:
      case exprEngineParser::REAL_LITERAL:
      case exprEngineParser::INT_LITERAL:
      case exprEngineParser::ISO_DATETIME:
      case exprEngineParser::ISO_DATE:
      case exprEngineParser::ISO_TIME:
      case exprEngineParser::STRING_LITERAL: {
        enterOuterAlt(_localctx, 1);
        setState(36);
        expr(0);
        break;
      }

      case exprEngineParser::AGGREGATE: {
        enterOuterAlt(_localctx, 2);
        setState(37);
        aggregateOver();
        break;
      }

      case exprEngineParser::EOF: {
        enterOuterAlt(_localctx, 3);
        setState(38);
        match(exprEngineParser::EOF);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

exprEngineParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t exprEngineParser::ExprContext::getRuleIndex() const {
  return exprEngineParser::RuleExpr;
}

void exprEngineParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
  this->returnType = ctx->returnType;
}

//----------------- ExprNotContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::ExprNotContext::NOT() {
  return getToken(exprEngineParser::NOT, 0);
}

exprEngineParser::ExprContext* exprEngineParser::ExprNotContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

exprEngineParser::ExprNotContext::ExprNotContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprNotContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprNot(this);
}
void exprEngineParser::ExprNotContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprNot(this);
}

std::any exprEngineParser::ExprNotContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprNot(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprNegateContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::ExprNegateContext::MINUS() {
  return getToken(exprEngineParser::MINUS, 0);
}

exprEngineParser::ExprContext* exprEngineParser::ExprNegateContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

exprEngineParser::ExprNegateContext::ExprNegateContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprNegateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprNegate(this);
}
void exprEngineParser::ExprNegateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprNegate(this);
}

std::any exprEngineParser::ExprNegateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprNegate(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprDivContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::ExprDivContext::SLASH() {
  return getToken(exprEngineParser::SLASH, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::ExprDivContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::ExprDivContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::ExprDivContext::ExprDivContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprDivContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprDiv(this);
}
void exprEngineParser::ExprDivContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprDiv(this);
}

std::any exprEngineParser::ExprDivContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprDiv(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprAbsContext ------------------------------------------------------------------

std::vector<tree::TerminalNode *> exprEngineParser::ExprAbsContext::PIPE() {
  return getTokens(exprEngineParser::PIPE);
}

tree::TerminalNode* exprEngineParser::ExprAbsContext::PIPE(size_t i) {
  return getToken(exprEngineParser::PIPE, i);
}

exprEngineParser::ExprContext* exprEngineParser::ExprAbsContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

exprEngineParser::ExprAbsContext::ExprAbsContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprAbsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprAbs(this);
}
void exprEngineParser::ExprAbsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprAbs(this);
}

std::any exprEngineParser::ExprAbsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprAbs(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprEqContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::ExprEqContext::EQ() {
  return getToken(exprEngineParser::EQ, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::ExprEqContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::ExprEqContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::ExprEqContext::ExprEqContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprEqContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprEq(this);
}
void exprEngineParser::ExprEqContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprEq(this);
}

std::any exprEngineParser::ExprEqContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprEq(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprGtContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::ExprGtContext::GT() {
  return getToken(exprEngineParser::GT, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::ExprGtContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::ExprGtContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::ExprGtContext::ExprGtContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprGtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprGt(this);
}
void exprEngineParser::ExprGtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprGt(this);
}

std::any exprEngineParser::ExprGtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprGt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprLiteralContext ------------------------------------------------------------------

exprEngineParser::LiteralContext* exprEngineParser::ExprLiteralContext::literal() {
  return getRuleContext<exprEngineParser::LiteralContext>(0);
}

exprEngineParser::ExprLiteralContext::ExprLiteralContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprLiteral(this);
}
void exprEngineParser::ExprLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprLiteral(this);
}

std::any exprEngineParser::ExprLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprParenContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::ExprParenContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::ExprParenContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::ExprParenContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::ExprParenContext::ExprParenContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprParenContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprParen(this);
}
void exprEngineParser::ExprParenContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprParen(this);
}

std::any exprEngineParser::ExprParenContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprParen(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprSubContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::ExprSubContext::MINUS() {
  return getToken(exprEngineParser::MINUS, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::ExprSubContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::ExprSubContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::ExprSubContext::ExprSubContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprSubContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprSub(this);
}
void exprEngineParser::ExprSubContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprSub(this);
}

std::any exprEngineParser::ExprSubContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprSub(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprOrContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::ExprOrContext::OR() {
  return getToken(exprEngineParser::OR, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::ExprOrContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::ExprOrContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::ExprOrContext::ExprOrContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprOrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprOr(this);
}
void exprEngineParser::ExprOrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprOr(this);
}

std::any exprEngineParser::ExprOrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprOr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprExpContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::ExprExpContext::CARET() {
  return getToken(exprEngineParser::CARET, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::ExprExpContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::ExprExpContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::ExprExpContext::ExprExpContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprExp(this);
}
void exprEngineParser::ExprExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprExp(this);
}

std::any exprEngineParser::ExprExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprExp(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprLteContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::ExprLteContext::LTE() {
  return getToken(exprEngineParser::LTE, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::ExprLteContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::ExprLteContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::ExprLteContext::ExprLteContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprLteContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprLte(this);
}
void exprEngineParser::ExprLteContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprLte(this);
}

std::any exprEngineParser::ExprLteContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprLte(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprCallContext ------------------------------------------------------------------

exprEngineParser::FunctionCallContext* exprEngineParser::ExprCallContext::functionCall() {
  return getRuleContext<exprEngineParser::FunctionCallContext>(0);
}

exprEngineParser::ExprCallContext::ExprCallContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprCall(this);
}
void exprEngineParser::ExprCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprCall(this);
}

std::any exprEngineParser::ExprCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprLtContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::ExprLtContext::LT() {
  return getToken(exprEngineParser::LT, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::ExprLtContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::ExprLtContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::ExprLtContext::ExprLtContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprLtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprLt(this);
}
void exprEngineParser::ExprLtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprLt(this);
}

std::any exprEngineParser::ExprLtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprLt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprMulContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::ExprMulContext::STAR() {
  return getToken(exprEngineParser::STAR, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::ExprMulContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::ExprMulContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::ExprMulContext::ExprMulContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprMulContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprMul(this);
}
void exprEngineParser::ExprMulContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprMul(this);
}

std::any exprEngineParser::ExprMulContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprMul(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprConcatContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::ExprConcatContext::CONCAT() {
  return getToken(exprEngineParser::CONCAT, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::ExprConcatContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::ExprConcatContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::ExprConcatContext::ExprConcatContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprConcatContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprConcat(this);
}
void exprEngineParser::ExprConcatContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprConcat(this);
}

std::any exprEngineParser::ExprConcatContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprConcat(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprAddContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::ExprAddContext::PLUS() {
  return getToken(exprEngineParser::PLUS, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::ExprAddContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::ExprAddContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::ExprAddContext::ExprAddContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprAddContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprAdd(this);
}
void exprEngineParser::ExprAddContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprAdd(this);
}

std::any exprEngineParser::ExprAddContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprAdd(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprModContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::ExprModContext::PERCENT() {
  return getToken(exprEngineParser::PERCENT, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::ExprModContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::ExprModContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::ExprModContext::ExprModContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprModContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprMod(this);
}
void exprEngineParser::ExprModContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprMod(this);
}

std::any exprEngineParser::ExprModContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprMod(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprAndContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::ExprAndContext::AND() {
  return getToken(exprEngineParser::AND, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::ExprAndContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::ExprAndContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::ExprAndContext::ExprAndContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprAndContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprAnd(this);
}
void exprEngineParser::ExprAndContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprAnd(this);
}

std::any exprEngineParser::ExprAndContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprAnd(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprGteContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::ExprGteContext::GTE() {
  return getToken(exprEngineParser::GTE, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::ExprGteContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::ExprGteContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::ExprGteContext::ExprGteContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprGteContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprGte(this);
}
void exprEngineParser::ExprGteContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprGte(this);
}

std::any exprEngineParser::ExprGteContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprGte(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprIntDivContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::ExprIntDivContext::DSLASH() {
  return getToken(exprEngineParser::DSLASH, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::ExprIntDivContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::ExprIntDivContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::ExprIntDivContext::ExprIntDivContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprIntDivContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprIntDiv(this);
}
void exprEngineParser::ExprIntDivContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprIntDiv(this);
}

std::any exprEngineParser::ExprIntDivContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprIntDiv(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprIndentifierContext ------------------------------------------------------------------

exprEngineParser::IdentifierContext* exprEngineParser::ExprIndentifierContext::identifier() {
  return getRuleContext<exprEngineParser::IdentifierContext>(0);
}

exprEngineParser::ExprIndentifierContext::ExprIndentifierContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprIndentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprIndentifier(this);
}
void exprEngineParser::ExprIndentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprIndentifier(this);
}

std::any exprEngineParser::ExprIndentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprIndentifier(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExprNeqContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::ExprNeqContext::NEQ() {
  return getToken(exprEngineParser::NEQ, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::ExprNeqContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::ExprNeqContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::ExprNeqContext::ExprNeqContext(ExprContext *ctx) { copyFrom(ctx); }

void exprEngineParser::ExprNeqContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExprNeq(this);
}
void exprEngineParser::ExprNeqContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExprNeq(this);
}

std::any exprEngineParser::ExprNeqContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitExprNeq(this);
  else
    return visitor->visitChildren(this);
}

exprEngineParser::ExprContext* exprEngineParser::expr() {
   return expr(0);
}

exprEngineParser::ExprContext* exprEngineParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  exprEngineParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  exprEngineParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 2;
  enterRecursionRule(_localctx, 2, exprEngineParser::RuleExpr, precedence);

    

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    unrollRecursionContexts(parentContext);
  });
  try {
    size_t alt;
    enterOuterAlt(_localctx, 1);
    setState(57);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case exprEngineParser::LPAREN: {
        _localctx = _tracker.createInstance<ExprParenContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;

        setState(42);
        match(exprEngineParser::LPAREN);
        setState(43);
        expr(0);
        setState(44);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::PIPE: {
        _localctx = _tracker.createInstance<ExprAbsContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(46);
        match(exprEngineParser::PIPE);
        setState(47);
        expr(0);
        setState(48);
        match(exprEngineParser::PIPE);
        break;
      }

      case exprEngineParser::ABS:
      case exprEngineParser::SIGN:
      case exprEngineParser::SQRT:
      case exprEngineParser::POW:
      case exprEngineParser::LOG:
      case exprEngineParser::LOG2:
      case exprEngineParser::LOG10:
      case exprEngineParser::EXP:
      case exprEngineParser::ERF:
      case exprEngineParser::CDFNORM:
      case exprEngineParser::FLOOR:
      case exprEngineParser::CEIL:
      case exprEngineParser::ROUND:
      case exprEngineParser::SIN:
      case exprEngineParser::COS:
      case exprEngineParser::TAN:
      case exprEngineParser::CLOSEENOUGH:
      case exprEngineParser::MEAN:
      case exprEngineParser::MEDIAN:
      case exprEngineParser::STDDEV:
      case exprEngineParser::VARIANCE:
      case exprEngineParser::MAX:
      case exprEngineParser::MIN:
      case exprEngineParser::SUM:
      case exprEngineParser::PROD:
      case exprEngineParser::LENGTH:
      case exprEngineParser::CONTAINS:
      case exprEngineParser::STARTSWITH:
      case exprEngineParser::ENDSWITH:
      case exprEngineParser::LIKE:
      case exprEngineParser::DATEDIFF:
      case exprEngineParser::DATEADD:
      case exprEngineParser::WEEKOFYEAR:
      case exprEngineParser::WEEKOFMONTH:
      case exprEngineParser::DAYOFWEEK:
      case exprEngineParser::SECONDOFDAY:
      case exprEngineParser::YEAR:
      case exprEngineParser::MONTH:
      case exprEngineParser::DAY:
      case exprEngineParser::HOUR:
      case exprEngineParser::MINUTE:
      case exprEngineParser::SECOND: {
        _localctx = _tracker.createInstance<ExprCallContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(50);
        functionCall();
        break;
      }

      case exprEngineParser::MINUS: {
        _localctx = _tracker.createInstance<ExprNegateContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(51);
        match(exprEngineParser::MINUS);
        setState(52);
        expr(19);
        break;
      }

      case exprEngineParser::NOT: {
        _localctx = _tracker.createInstance<ExprNotContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(53);
        match(exprEngineParser::NOT);
        setState(54);
        expr(18);
        break;
      }

      case exprEngineParser::TRUE:
      case exprEngineParser::FALSE:
      case exprEngineParser::NULL_:
      case exprEngineParser::REAL_LITERAL:
      case exprEngineParser::INT_LITERAL:
      case exprEngineParser::ISO_DATETIME:
      case exprEngineParser::ISO_DATE:
      case exprEngineParser::ISO_TIME:
      case exprEngineParser::STRING_LITERAL: {
        _localctx = _tracker.createInstance<ExprLiteralContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(55);
        literal();
        break;
      }

      case exprEngineParser::QUOTED_IDENTIFIER:
      case exprEngineParser::IDENTIFIER: {
        _localctx = _tracker.createInstance<ExprIndentifierContext>(_localctx);
        _ctx = _localctx;
        previousContext = _localctx;
        setState(56);
        identifier();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
    _ctx->stop = _input->LT(-1);
    setState(109);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(107);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 2, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<ExprExpContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(59);

          if (!(precpred(_ctx, 20))) throw FailedPredicateException(this, "precpred(_ctx, 20)");
          setState(60);
          match(exprEngineParser::CARET);
          setState(61);
          antlrcpp::downCast<ExprExpContext *>(_localctx)->right = expr(20);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<ExprMulContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(62);

          if (!(precpred(_ctx, 17))) throw FailedPredicateException(this, "precpred(_ctx, 17)");
          setState(63);
          match(exprEngineParser::STAR);
          setState(64);
          antlrcpp::downCast<ExprMulContext *>(_localctx)->right = expr(18);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<ExprDivContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(65);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(66);
          match(exprEngineParser::SLASH);
          setState(67);
          antlrcpp::downCast<ExprDivContext *>(_localctx)->right = expr(17);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<ExprModContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(68);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(69);
          match(exprEngineParser::PERCENT);
          setState(70);
          antlrcpp::downCast<ExprModContext *>(_localctx)->right = expr(16);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<ExprIntDivContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(71);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(72);
          match(exprEngineParser::DSLASH);
          setState(73);
          antlrcpp::downCast<ExprIntDivContext *>(_localctx)->right = expr(15);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<ExprAddContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(74);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(75);
          match(exprEngineParser::PLUS);
          setState(76);
          antlrcpp::downCast<ExprAddContext *>(_localctx)->right = expr(14);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<ExprSubContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(77);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(78);
          match(exprEngineParser::MINUS);
          setState(79);
          antlrcpp::downCast<ExprSubContext *>(_localctx)->right = expr(13);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<ExprEqContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(80);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(81);
          match(exprEngineParser::EQ);
          setState(82);
          antlrcpp::downCast<ExprEqContext *>(_localctx)->right = expr(12);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<ExprNeqContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(83);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(84);
          match(exprEngineParser::NEQ);
          setState(85);
          antlrcpp::downCast<ExprNeqContext *>(_localctx)->right = expr(11);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<ExprLtContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(86);

          if (!(precpred(_ctx, 9))) throw FailedPredicateException(this, "precpred(_ctx, 9)");
          setState(87);
          match(exprEngineParser::LT);
          setState(88);
          antlrcpp::downCast<ExprLtContext *>(_localctx)->right = expr(10);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<ExprLteContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(89);

          if (!(precpred(_ctx, 8))) throw FailedPredicateException(this, "precpred(_ctx, 8)");
          setState(90);
          match(exprEngineParser::LTE);
          setState(91);
          antlrcpp::downCast<ExprLteContext *>(_localctx)->right = expr(9);
          break;
        }

        case 12: {
          auto newContext = _tracker.createInstance<ExprGtContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(92);

          if (!(precpred(_ctx, 7))) throw FailedPredicateException(this, "precpred(_ctx, 7)");
          setState(93);
          match(exprEngineParser::GT);
          setState(94);
          antlrcpp::downCast<ExprGtContext *>(_localctx)->right = expr(8);
          break;
        }

        case 13: {
          auto newContext = _tracker.createInstance<ExprGteContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(95);

          if (!(precpred(_ctx, 6))) throw FailedPredicateException(this, "precpred(_ctx, 6)");
          setState(96);
          match(exprEngineParser::GTE);
          setState(97);
          antlrcpp::downCast<ExprGteContext *>(_localctx)->right = expr(7);
          break;
        }

        case 14: {
          auto newContext = _tracker.createInstance<ExprAndContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(98);

          if (!(precpred(_ctx, 5))) throw FailedPredicateException(this, "precpred(_ctx, 5)");
          setState(99);
          match(exprEngineParser::AND);
          setState(100);
          antlrcpp::downCast<ExprAndContext *>(_localctx)->right = expr(6);
          break;
        }

        case 15: {
          auto newContext = _tracker.createInstance<ExprOrContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(101);

          if (!(precpred(_ctx, 4))) throw FailedPredicateException(this, "precpred(_ctx, 4)");
          setState(102);
          match(exprEngineParser::OR);
          setState(103);
          antlrcpp::downCast<ExprOrContext *>(_localctx)->right = expr(5);
          break;
        }

        case 16: {
          auto newContext = _tracker.createInstance<ExprConcatContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(104);

          if (!(precpred(_ctx, 3))) throw FailedPredicateException(this, "precpred(_ctx, 3)");
          setState(105);
          match(exprEngineParser::CONCAT);
          setState(106);
          antlrcpp::downCast<ExprConcatContext *>(_localctx)->right = expr(4);
          break;
        }

        default:
          break;
        } 
      }
      setState(111);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 3, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- AggregateOverContext ------------------------------------------------------------------

exprEngineParser::AggregateOverContext::AggregateOverContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* exprEngineParser::AggregateOverContext::AGGREGATE() {
  return getToken(exprEngineParser::AGGREGATE, 0);
}

exprEngineParser::AggregateFnContext* exprEngineParser::AggregateOverContext::aggregateFn() {
  return getRuleContext<exprEngineParser::AggregateFnContext>(0);
}

tree::TerminalNode* exprEngineParser::AggregateOverContext::OVER() {
  return getToken(exprEngineParser::OVER, 0);
}

exprEngineParser::IdentifierContext* exprEngineParser::AggregateOverContext::identifier() {
  return getRuleContext<exprEngineParser::IdentifierContext>(0);
}


size_t exprEngineParser::AggregateOverContext::getRuleIndex() const {
  return exprEngineParser::RuleAggregateOver;
}

void exprEngineParser::AggregateOverContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAggregateOver(this);
}

void exprEngineParser::AggregateOverContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAggregateOver(this);
}


std::any exprEngineParser::AggregateOverContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitAggregateOver(this);
  else
    return visitor->visitChildren(this);
}

exprEngineParser::AggregateOverContext* exprEngineParser::aggregateOver() {
  AggregateOverContext *_localctx = _tracker.createInstance<AggregateOverContext>(_ctx, getState());
  enterRule(_localctx, 4, exprEngineParser::RuleAggregateOver);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(112);
    match(exprEngineParser::AGGREGATE);
    setState(113);
    aggregateFn();
    setState(114);
    match(exprEngineParser::OVER);
    setState(115);
    identifier();
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IdentifierContext ------------------------------------------------------------------

exprEngineParser::IdentifierContext::IdentifierContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* exprEngineParser::IdentifierContext::IDENTIFIER() {
  return getToken(exprEngineParser::IDENTIFIER, 0);
}

tree::TerminalNode* exprEngineParser::IdentifierContext::QUOTED_IDENTIFIER() {
  return getToken(exprEngineParser::QUOTED_IDENTIFIER, 0);
}


size_t exprEngineParser::IdentifierContext::getRuleIndex() const {
  return exprEngineParser::RuleIdentifier;
}

void exprEngineParser::IdentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifier(this);
}

void exprEngineParser::IdentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifier(this);
}


std::any exprEngineParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}

exprEngineParser::IdentifierContext* exprEngineParser::identifier() {
  IdentifierContext *_localctx = _tracker.createInstance<IdentifierContext>(_ctx, getState());
  enterRule(_localctx, 6, exprEngineParser::RuleIdentifier);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(117);
    _la = _input->LA(1);
    if (!(_la == exprEngineParser::QUOTED_IDENTIFIER

    || _la == exprEngineParser::IDENTIFIER)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FunctionCallContext ------------------------------------------------------------------

exprEngineParser::FunctionCallContext::FunctionCallContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

exprEngineParser::StatelessFnContext* exprEngineParser::FunctionCallContext::statelessFn() {
  return getRuleContext<exprEngineParser::StatelessFnContext>(0);
}

exprEngineParser::AggregateFnContext* exprEngineParser::FunctionCallContext::aggregateFn() {
  return getRuleContext<exprEngineParser::AggregateFnContext>(0);
}


size_t exprEngineParser::FunctionCallContext::getRuleIndex() const {
  return exprEngineParser::RuleFunctionCall;
}

void exprEngineParser::FunctionCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCall(this);
}

void exprEngineParser::FunctionCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCall(this);
}


std::any exprEngineParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}

exprEngineParser::FunctionCallContext* exprEngineParser::functionCall() {
  FunctionCallContext *_localctx = _tracker.createInstance<FunctionCallContext>(_ctx, getState());
  enterRule(_localctx, 8, exprEngineParser::RuleFunctionCall);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(121);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case exprEngineParser::ABS:
      case exprEngineParser::SIGN:
      case exprEngineParser::SQRT:
      case exprEngineParser::POW:
      case exprEngineParser::LOG:
      case exprEngineParser::LOG2:
      case exprEngineParser::LOG10:
      case exprEngineParser::EXP:
      case exprEngineParser::ERF:
      case exprEngineParser::CDFNORM:
      case exprEngineParser::FLOOR:
      case exprEngineParser::CEIL:
      case exprEngineParser::ROUND:
      case exprEngineParser::SIN:
      case exprEngineParser::COS:
      case exprEngineParser::TAN:
      case exprEngineParser::CLOSEENOUGH:
      case exprEngineParser::LENGTH:
      case exprEngineParser::CONTAINS:
      case exprEngineParser::STARTSWITH:
      case exprEngineParser::ENDSWITH:
      case exprEngineParser::LIKE:
      case exprEngineParser::DATEDIFF:
      case exprEngineParser::DATEADD:
      case exprEngineParser::WEEKOFYEAR:
      case exprEngineParser::WEEKOFMONTH:
      case exprEngineParser::DAYOFWEEK:
      case exprEngineParser::SECONDOFDAY:
      case exprEngineParser::YEAR:
      case exprEngineParser::MONTH:
      case exprEngineParser::DAY:
      case exprEngineParser::HOUR:
      case exprEngineParser::MINUTE:
      case exprEngineParser::SECOND: {
        enterOuterAlt(_localctx, 1);
        setState(119);
        statelessFn();
        break;
      }

      case exprEngineParser::MEAN:
      case exprEngineParser::MEDIAN:
      case exprEngineParser::STDDEV:
      case exprEngineParser::VARIANCE:
      case exprEngineParser::MAX:
      case exprEngineParser::MIN:
      case exprEngineParser::SUM:
      case exprEngineParser::PROD: {
        enterOuterAlt(_localctx, 2);
        setState(120);
        aggregateFn();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatelessFnContext ------------------------------------------------------------------

exprEngineParser::StatelessFnContext::StatelessFnContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

exprEngineParser::MathFnContext* exprEngineParser::StatelessFnContext::mathFn() {
  return getRuleContext<exprEngineParser::MathFnContext>(0);
}

exprEngineParser::StringFnContext* exprEngineParser::StatelessFnContext::stringFn() {
  return getRuleContext<exprEngineParser::StringFnContext>(0);
}

exprEngineParser::TimestampFnContext* exprEngineParser::StatelessFnContext::timestampFn() {
  return getRuleContext<exprEngineParser::TimestampFnContext>(0);
}


size_t exprEngineParser::StatelessFnContext::getRuleIndex() const {
  return exprEngineParser::RuleStatelessFn;
}

void exprEngineParser::StatelessFnContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatelessFn(this);
}

void exprEngineParser::StatelessFnContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatelessFn(this);
}


std::any exprEngineParser::StatelessFnContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitStatelessFn(this);
  else
    return visitor->visitChildren(this);
}

exprEngineParser::StatelessFnContext* exprEngineParser::statelessFn() {
  StatelessFnContext *_localctx = _tracker.createInstance<StatelessFnContext>(_ctx, getState());
  enterRule(_localctx, 10, exprEngineParser::RuleStatelessFn);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(126);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case exprEngineParser::ABS:
      case exprEngineParser::SIGN:
      case exprEngineParser::SQRT:
      case exprEngineParser::POW:
      case exprEngineParser::LOG:
      case exprEngineParser::LOG2:
      case exprEngineParser::LOG10:
      case exprEngineParser::EXP:
      case exprEngineParser::ERF:
      case exprEngineParser::CDFNORM:
      case exprEngineParser::FLOOR:
      case exprEngineParser::CEIL:
      case exprEngineParser::ROUND:
      case exprEngineParser::SIN:
      case exprEngineParser::COS:
      case exprEngineParser::TAN:
      case exprEngineParser::CLOSEENOUGH: {
        enterOuterAlt(_localctx, 1);
        setState(123);
        mathFn();
        break;
      }

      case exprEngineParser::LENGTH:
      case exprEngineParser::CONTAINS:
      case exprEngineParser::STARTSWITH:
      case exprEngineParser::ENDSWITH:
      case exprEngineParser::LIKE: {
        enterOuterAlt(_localctx, 2);
        setState(124);
        stringFn();
        break;
      }

      case exprEngineParser::DATEDIFF:
      case exprEngineParser::DATEADD:
      case exprEngineParser::WEEKOFYEAR:
      case exprEngineParser::WEEKOFMONTH:
      case exprEngineParser::DAYOFWEEK:
      case exprEngineParser::SECONDOFDAY:
      case exprEngineParser::YEAR:
      case exprEngineParser::MONTH:
      case exprEngineParser::DAY:
      case exprEngineParser::HOUR:
      case exprEngineParser::MINUTE:
      case exprEngineParser::SECOND: {
        enterOuterAlt(_localctx, 3);
        setState(125);
        timestampFn();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- AggregateFnContext ------------------------------------------------------------------

exprEngineParser::AggregateFnContext::AggregateFnContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t exprEngineParser::AggregateFnContext::getRuleIndex() const {
  return exprEngineParser::RuleAggregateFn;
}

void exprEngineParser::AggregateFnContext::copyFrom(AggregateFnContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FnAgg_MeanContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnAgg_MeanContext::MEAN() {
  return getToken(exprEngineParser::MEAN, 0);
}

tree::TerminalNode* exprEngineParser::FnAgg_MeanContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnAgg_MeanContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnAgg_MeanContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnAgg_MeanContext::FnAgg_MeanContext(AggregateFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnAgg_MeanContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnAgg_Mean(this);
}
void exprEngineParser::FnAgg_MeanContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnAgg_Mean(this);
}

std::any exprEngineParser::FnAgg_MeanContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnAgg_Mean(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnAgg_SumContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnAgg_SumContext::SUM() {
  return getToken(exprEngineParser::SUM, 0);
}

tree::TerminalNode* exprEngineParser::FnAgg_SumContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnAgg_SumContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnAgg_SumContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnAgg_SumContext::FnAgg_SumContext(AggregateFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnAgg_SumContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnAgg_Sum(this);
}
void exprEngineParser::FnAgg_SumContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnAgg_Sum(this);
}

std::any exprEngineParser::FnAgg_SumContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnAgg_Sum(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnAgg_ProdContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnAgg_ProdContext::PROD() {
  return getToken(exprEngineParser::PROD, 0);
}

tree::TerminalNode* exprEngineParser::FnAgg_ProdContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnAgg_ProdContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnAgg_ProdContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnAgg_ProdContext::FnAgg_ProdContext(AggregateFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnAgg_ProdContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnAgg_Prod(this);
}
void exprEngineParser::FnAgg_ProdContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnAgg_Prod(this);
}

std::any exprEngineParser::FnAgg_ProdContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnAgg_Prod(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnAgg_MedianContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnAgg_MedianContext::MEDIAN() {
  return getToken(exprEngineParser::MEDIAN, 0);
}

tree::TerminalNode* exprEngineParser::FnAgg_MedianContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnAgg_MedianContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnAgg_MedianContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnAgg_MedianContext::FnAgg_MedianContext(AggregateFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnAgg_MedianContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnAgg_Median(this);
}
void exprEngineParser::FnAgg_MedianContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnAgg_Median(this);
}

std::any exprEngineParser::FnAgg_MedianContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnAgg_Median(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnAgg_MinContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnAgg_MinContext::MIN() {
  return getToken(exprEngineParser::MIN, 0);
}

tree::TerminalNode* exprEngineParser::FnAgg_MinContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnAgg_MinContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnAgg_MinContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnAgg_MinContext::FnAgg_MinContext(AggregateFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnAgg_MinContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnAgg_Min(this);
}
void exprEngineParser::FnAgg_MinContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnAgg_Min(this);
}

std::any exprEngineParser::FnAgg_MinContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnAgg_Min(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnAgg_MaxContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnAgg_MaxContext::MAX() {
  return getToken(exprEngineParser::MAX, 0);
}

tree::TerminalNode* exprEngineParser::FnAgg_MaxContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnAgg_MaxContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnAgg_MaxContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnAgg_MaxContext::FnAgg_MaxContext(AggregateFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnAgg_MaxContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnAgg_Max(this);
}
void exprEngineParser::FnAgg_MaxContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnAgg_Max(this);
}

std::any exprEngineParser::FnAgg_MaxContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnAgg_Max(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnAgg_VarianceContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnAgg_VarianceContext::VARIANCE() {
  return getToken(exprEngineParser::VARIANCE, 0);
}

tree::TerminalNode* exprEngineParser::FnAgg_VarianceContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnAgg_VarianceContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnAgg_VarianceContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnAgg_VarianceContext::FnAgg_VarianceContext(AggregateFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnAgg_VarianceContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnAgg_Variance(this);
}
void exprEngineParser::FnAgg_VarianceContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnAgg_Variance(this);
}

std::any exprEngineParser::FnAgg_VarianceContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnAgg_Variance(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnAgg_StdDevContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnAgg_StdDevContext::STDDEV() {
  return getToken(exprEngineParser::STDDEV, 0);
}

tree::TerminalNode* exprEngineParser::FnAgg_StdDevContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnAgg_StdDevContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnAgg_StdDevContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnAgg_StdDevContext::FnAgg_StdDevContext(AggregateFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnAgg_StdDevContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnAgg_StdDev(this);
}
void exprEngineParser::FnAgg_StdDevContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnAgg_StdDev(this);
}

std::any exprEngineParser::FnAgg_StdDevContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnAgg_StdDev(this);
  else
    return visitor->visitChildren(this);
}
exprEngineParser::AggregateFnContext* exprEngineParser::aggregateFn() {
  AggregateFnContext *_localctx = _tracker.createInstance<AggregateFnContext>(_ctx, getState());
  enterRule(_localctx, 12, exprEngineParser::RuleAggregateFn);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(168);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case exprEngineParser::MEAN: {
        _localctx = _tracker.createInstance<exprEngineParser::FnAgg_MeanContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(128);
        match(exprEngineParser::MEAN);
        setState(129);
        match(exprEngineParser::LPAREN);
        setState(130);
        expr(0);
        setState(131);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::MEDIAN: {
        _localctx = _tracker.createInstance<exprEngineParser::FnAgg_MedianContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(133);
        match(exprEngineParser::MEDIAN);
        setState(134);
        match(exprEngineParser::LPAREN);
        setState(135);
        expr(0);
        setState(136);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::STDDEV: {
        _localctx = _tracker.createInstance<exprEngineParser::FnAgg_StdDevContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(138);
        match(exprEngineParser::STDDEV);
        setState(139);
        match(exprEngineParser::LPAREN);
        setState(140);
        expr(0);
        setState(141);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::VARIANCE: {
        _localctx = _tracker.createInstance<exprEngineParser::FnAgg_VarianceContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(143);
        match(exprEngineParser::VARIANCE);
        setState(144);
        match(exprEngineParser::LPAREN);
        setState(145);
        expr(0);
        setState(146);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::MAX: {
        _localctx = _tracker.createInstance<exprEngineParser::FnAgg_MaxContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(148);
        match(exprEngineParser::MAX);
        setState(149);
        match(exprEngineParser::LPAREN);
        setState(150);
        expr(0);
        setState(151);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::MIN: {
        _localctx = _tracker.createInstance<exprEngineParser::FnAgg_MinContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(153);
        match(exprEngineParser::MIN);
        setState(154);
        match(exprEngineParser::LPAREN);
        setState(155);
        expr(0);
        setState(156);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::SUM: {
        _localctx = _tracker.createInstance<exprEngineParser::FnAgg_SumContext>(_localctx);
        enterOuterAlt(_localctx, 7);
        setState(158);
        match(exprEngineParser::SUM);
        setState(159);
        match(exprEngineParser::LPAREN);
        setState(160);
        expr(0);
        setState(161);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::PROD: {
        _localctx = _tracker.createInstance<exprEngineParser::FnAgg_ProdContext>(_localctx);
        enterOuterAlt(_localctx, 8);
        setState(163);
        match(exprEngineParser::PROD);
        setState(164);
        match(exprEngineParser::LPAREN);
        setState(165);
        expr(0);
        setState(166);
        match(exprEngineParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- MathFnContext ------------------------------------------------------------------

exprEngineParser::MathFnContext::MathFnContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t exprEngineParser::MathFnContext::getRuleIndex() const {
  return exprEngineParser::RuleMathFn;
}

void exprEngineParser::MathFnContext::copyFrom(MathFnContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FnSL_Log10Context ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_Log10Context::LOG10() {
  return getToken(exprEngineParser::LOG10, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_Log10Context::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_Log10Context::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_Log10Context::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_Log10Context::FnSL_Log10Context(MathFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_Log10Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Log10(this);
}
void exprEngineParser::FnSL_Log10Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Log10(this);
}

std::any exprEngineParser::FnSL_Log10Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Log10(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_TanContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_TanContext::TAN() {
  return getToken(exprEngineParser::TAN, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_TanContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_TanContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_TanContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_TanContext::FnSL_TanContext(MathFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_TanContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Tan(this);
}
void exprEngineParser::FnSL_TanContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Tan(this);
}

std::any exprEngineParser::FnSL_TanContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Tan(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_FloorContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_FloorContext::FLOOR() {
  return getToken(exprEngineParser::FLOOR, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_FloorContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_FloorContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_FloorContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_FloorContext::FnSL_FloorContext(MathFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_FloorContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Floor(this);
}
void exprEngineParser::FnSL_FloorContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Floor(this);
}

std::any exprEngineParser::FnSL_FloorContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Floor(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_SqrtContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_SqrtContext::SQRT() {
  return getToken(exprEngineParser::SQRT, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_SqrtContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_SqrtContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_SqrtContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_SqrtContext::FnSL_SqrtContext(MathFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_SqrtContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Sqrt(this);
}
void exprEngineParser::FnSL_SqrtContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Sqrt(this);
}

std::any exprEngineParser::FnSL_SqrtContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Sqrt(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_LogContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_LogContext::LOG() {
  return getToken(exprEngineParser::LOG, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_LogContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_LogContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_LogContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_LogContext::FnSL_LogContext(MathFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_LogContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Log(this);
}
void exprEngineParser::FnSL_LogContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Log(this);
}

std::any exprEngineParser::FnSL_LogContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Log(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_SignContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_SignContext::SIGN() {
  return getToken(exprEngineParser::SIGN, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_SignContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_SignContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_SignContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_SignContext::FnSL_SignContext(MathFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_SignContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Sign(this);
}
void exprEngineParser::FnSL_SignContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Sign(this);
}

std::any exprEngineParser::FnSL_SignContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Sign(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_CdfNormContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_CdfNormContext::CDFNORM() {
  return getToken(exprEngineParser::CDFNORM, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_CdfNormContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_CdfNormContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_CdfNormContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_CdfNormContext::FnSL_CdfNormContext(MathFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_CdfNormContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_CdfNorm(this);
}
void exprEngineParser::FnSL_CdfNormContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_CdfNorm(this);
}

std::any exprEngineParser::FnSL_CdfNormContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_CdfNorm(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_RoundContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_RoundContext::ROUND() {
  return getToken(exprEngineParser::ROUND, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_RoundContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_RoundContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_RoundContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_RoundContext::FnSL_RoundContext(MathFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_RoundContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Round(this);
}
void exprEngineParser::FnSL_RoundContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Round(this);
}

std::any exprEngineParser::FnSL_RoundContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Round(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_CloseEnoughContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_CloseEnoughContext::CLOSEENOUGH() {
  return getToken(exprEngineParser::CLOSEENOUGH, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_CloseEnoughContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_CloseEnoughContext::COMMA() {
  return getToken(exprEngineParser::COMMA, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_CloseEnoughContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::FnSL_CloseEnoughContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_CloseEnoughContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::FnSL_CloseEnoughContext::FnSL_CloseEnoughContext(MathFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_CloseEnoughContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_CloseEnough(this);
}
void exprEngineParser::FnSL_CloseEnoughContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_CloseEnough(this);
}

std::any exprEngineParser::FnSL_CloseEnoughContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_CloseEnough(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_CosContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_CosContext::COS() {
  return getToken(exprEngineParser::COS, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_CosContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_CosContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_CosContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_CosContext::FnSL_CosContext(MathFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_CosContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Cos(this);
}
void exprEngineParser::FnSL_CosContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Cos(this);
}

std::any exprEngineParser::FnSL_CosContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Cos(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_Log2Context ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_Log2Context::LOG2() {
  return getToken(exprEngineParser::LOG2, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_Log2Context::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_Log2Context::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_Log2Context::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_Log2Context::FnSL_Log2Context(MathFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_Log2Context::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Log2(this);
}
void exprEngineParser::FnSL_Log2Context::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Log2(this);
}

std::any exprEngineParser::FnSL_Log2Context::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Log2(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_AbsContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_AbsContext::ABS() {
  return getToken(exprEngineParser::ABS, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_AbsContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_AbsContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_AbsContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_AbsContext::FnSL_AbsContext(MathFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_AbsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Abs(this);
}
void exprEngineParser::FnSL_AbsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Abs(this);
}

std::any exprEngineParser::FnSL_AbsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Abs(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_CeilContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_CeilContext::CEIL() {
  return getToken(exprEngineParser::CEIL, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_CeilContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_CeilContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_CeilContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_CeilContext::FnSL_CeilContext(MathFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_CeilContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Ceil(this);
}
void exprEngineParser::FnSL_CeilContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Ceil(this);
}

std::any exprEngineParser::FnSL_CeilContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Ceil(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_PowContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_PowContext::POW() {
  return getToken(exprEngineParser::POW, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_PowContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_PowContext::COMMA() {
  return getToken(exprEngineParser::COMMA, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_PowContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::FnSL_PowContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_PowContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::FnSL_PowContext::FnSL_PowContext(MathFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_PowContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Pow(this);
}
void exprEngineParser::FnSL_PowContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Pow(this);
}

std::any exprEngineParser::FnSL_PowContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Pow(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_ErfContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_ErfContext::ERF() {
  return getToken(exprEngineParser::ERF, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_ErfContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_ErfContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_ErfContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_ErfContext::FnSL_ErfContext(MathFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_ErfContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Erf(this);
}
void exprEngineParser::FnSL_ErfContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Erf(this);
}

std::any exprEngineParser::FnSL_ErfContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Erf(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_SinContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_SinContext::SIN() {
  return getToken(exprEngineParser::SIN, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_SinContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_SinContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_SinContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_SinContext::FnSL_SinContext(MathFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_SinContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Sin(this);
}
void exprEngineParser::FnSL_SinContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Sin(this);
}

std::any exprEngineParser::FnSL_SinContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Sin(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_ExpContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_ExpContext::EXP() {
  return getToken(exprEngineParser::EXP, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_ExpContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_ExpContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_ExpContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_ExpContext::FnSL_ExpContext(MathFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_ExpContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Exp(this);
}
void exprEngineParser::FnSL_ExpContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Exp(this);
}

std::any exprEngineParser::FnSL_ExpContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Exp(this);
  else
    return visitor->visitChildren(this);
}
exprEngineParser::MathFnContext* exprEngineParser::mathFn() {
  MathFnContext *_localctx = _tracker.createInstance<MathFnContext>(_ctx, getState());
  enterRule(_localctx, 14, exprEngineParser::RuleMathFn);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(259);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case exprEngineParser::ABS: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_AbsContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(170);
        match(exprEngineParser::ABS);
        setState(171);
        match(exprEngineParser::LPAREN);
        setState(172);
        expr(0);
        setState(173);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::SIGN: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_SignContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(175);
        match(exprEngineParser::SIGN);
        setState(176);
        match(exprEngineParser::LPAREN);
        setState(177);
        expr(0);
        setState(178);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::SQRT: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_SqrtContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(180);
        match(exprEngineParser::SQRT);
        setState(181);
        match(exprEngineParser::LPAREN);
        setState(182);
        expr(0);
        setState(183);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::POW: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_PowContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(185);
        match(exprEngineParser::POW);
        setState(186);
        match(exprEngineParser::LPAREN);
        setState(187);
        antlrcpp::downCast<FnSL_PowContext *>(_localctx)->left = expr(0);
        setState(188);
        match(exprEngineParser::COMMA);
        setState(189);
        antlrcpp::downCast<FnSL_PowContext *>(_localctx)->right = expr(0);
        setState(190);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::LOG: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_LogContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(192);
        match(exprEngineParser::LOG);
        setState(193);
        match(exprEngineParser::LPAREN);
        setState(194);
        expr(0);
        setState(195);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::LOG2: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_Log2Context>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(197);
        match(exprEngineParser::LOG2);
        setState(198);
        match(exprEngineParser::LPAREN);
        setState(199);
        expr(0);
        setState(200);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::LOG10: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_Log10Context>(_localctx);
        enterOuterAlt(_localctx, 7);
        setState(202);
        match(exprEngineParser::LOG10);
        setState(203);
        match(exprEngineParser::LPAREN);
        setState(204);
        expr(0);
        setState(205);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::EXP: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_ExpContext>(_localctx);
        enterOuterAlt(_localctx, 8);
        setState(207);
        match(exprEngineParser::EXP);
        setState(208);
        match(exprEngineParser::LPAREN);
        setState(209);
        expr(0);
        setState(210);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::ERF: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_ErfContext>(_localctx);
        enterOuterAlt(_localctx, 9);
        setState(212);
        match(exprEngineParser::ERF);
        setState(213);
        match(exprEngineParser::LPAREN);
        setState(214);
        expr(0);
        setState(215);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::CDFNORM: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_CdfNormContext>(_localctx);
        enterOuterAlt(_localctx, 10);
        setState(217);
        match(exprEngineParser::CDFNORM);
        setState(218);
        match(exprEngineParser::LPAREN);
        setState(219);
        expr(0);
        setState(220);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::FLOOR: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_FloorContext>(_localctx);
        enterOuterAlt(_localctx, 11);
        setState(222);
        match(exprEngineParser::FLOOR);
        setState(223);
        match(exprEngineParser::LPAREN);
        setState(224);
        expr(0);
        setState(225);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::CEIL: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_CeilContext>(_localctx);
        enterOuterAlt(_localctx, 12);
        setState(227);
        match(exprEngineParser::CEIL);
        setState(228);
        match(exprEngineParser::LPAREN);
        setState(229);
        expr(0);
        setState(230);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::ROUND: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_RoundContext>(_localctx);
        enterOuterAlt(_localctx, 13);
        setState(232);
        match(exprEngineParser::ROUND);
        setState(233);
        match(exprEngineParser::LPAREN);
        setState(234);
        expr(0);
        setState(235);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::SIN: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_SinContext>(_localctx);
        enterOuterAlt(_localctx, 14);
        setState(237);
        match(exprEngineParser::SIN);
        setState(238);
        match(exprEngineParser::LPAREN);
        setState(239);
        expr(0);
        setState(240);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::COS: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_CosContext>(_localctx);
        enterOuterAlt(_localctx, 15);
        setState(242);
        match(exprEngineParser::COS);
        setState(243);
        match(exprEngineParser::LPAREN);
        setState(244);
        expr(0);
        setState(245);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::TAN: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_TanContext>(_localctx);
        enterOuterAlt(_localctx, 16);
        setState(247);
        match(exprEngineParser::TAN);
        setState(248);
        match(exprEngineParser::LPAREN);
        setState(249);
        expr(0);
        setState(250);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::CLOSEENOUGH: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_CloseEnoughContext>(_localctx);
        enterOuterAlt(_localctx, 17);
        setState(252);
        match(exprEngineParser::CLOSEENOUGH);
        setState(253);
        match(exprEngineParser::LPAREN);
        setState(254);
        antlrcpp::downCast<FnSL_CloseEnoughContext *>(_localctx)->arg1 = expr(0);
        setState(255);
        match(exprEngineParser::COMMA);
        setState(256);
        antlrcpp::downCast<FnSL_CloseEnoughContext *>(_localctx)->arg2 = expr(0);
        setState(257);
        match(exprEngineParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StringFnContext ------------------------------------------------------------------

exprEngineParser::StringFnContext::StringFnContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t exprEngineParser::StringFnContext::getRuleIndex() const {
  return exprEngineParser::RuleStringFn;
}

void exprEngineParser::StringFnContext::copyFrom(StringFnContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FnSL_ContainsContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_ContainsContext::CONTAINS() {
  return getToken(exprEngineParser::CONTAINS, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_ContainsContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_ContainsContext::COMMA() {
  return getToken(exprEngineParser::COMMA, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_ContainsContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::FnSL_ContainsContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_ContainsContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::FnSL_ContainsContext::FnSL_ContainsContext(StringFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_ContainsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Contains(this);
}
void exprEngineParser::FnSL_ContainsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Contains(this);
}

std::any exprEngineParser::FnSL_ContainsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Contains(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_StartsWithContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_StartsWithContext::STARTSWITH() {
  return getToken(exprEngineParser::STARTSWITH, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_StartsWithContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_StartsWithContext::COMMA() {
  return getToken(exprEngineParser::COMMA, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_StartsWithContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::FnSL_StartsWithContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_StartsWithContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::FnSL_StartsWithContext::FnSL_StartsWithContext(StringFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_StartsWithContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_StartsWith(this);
}
void exprEngineParser::FnSL_StartsWithContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_StartsWith(this);
}

std::any exprEngineParser::FnSL_StartsWithContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_StartsWith(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_LikeContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_LikeContext::LIKE() {
  return getToken(exprEngineParser::LIKE, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_LikeContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_LikeContext::COMMA() {
  return getToken(exprEngineParser::COMMA, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_LikeContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::FnSL_LikeContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_LikeContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::FnSL_LikeContext::FnSL_LikeContext(StringFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_LikeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Like(this);
}
void exprEngineParser::FnSL_LikeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Like(this);
}

std::any exprEngineParser::FnSL_LikeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Like(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_LengthContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_LengthContext::LENGTH() {
  return getToken(exprEngineParser::LENGTH, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_LengthContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_LengthContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_LengthContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_LengthContext::FnSL_LengthContext(StringFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_LengthContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Length(this);
}
void exprEngineParser::FnSL_LengthContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Length(this);
}

std::any exprEngineParser::FnSL_LengthContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Length(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_EndsWithContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_EndsWithContext::ENDSWITH() {
  return getToken(exprEngineParser::ENDSWITH, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_EndsWithContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_EndsWithContext::COMMA() {
  return getToken(exprEngineParser::COMMA, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_EndsWithContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::FnSL_EndsWithContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_EndsWithContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::FnSL_EndsWithContext::FnSL_EndsWithContext(StringFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_EndsWithContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_EndsWith(this);
}
void exprEngineParser::FnSL_EndsWithContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_EndsWith(this);
}

std::any exprEngineParser::FnSL_EndsWithContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_EndsWith(this);
  else
    return visitor->visitChildren(this);
}
exprEngineParser::StringFnContext* exprEngineParser::stringFn() {
  StringFnContext *_localctx = _tracker.createInstance<StringFnContext>(_ctx, getState());
  enterRule(_localctx, 16, exprEngineParser::RuleStringFn);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(294);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case exprEngineParser::LENGTH: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_LengthContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(261);
        match(exprEngineParser::LENGTH);
        setState(262);
        match(exprEngineParser::LPAREN);
        setState(263);
        expr(0);
        setState(264);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::CONTAINS: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_ContainsContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(266);
        match(exprEngineParser::CONTAINS);
        setState(267);
        match(exprEngineParser::LPAREN);
        setState(268);
        antlrcpp::downCast<FnSL_ContainsContext *>(_localctx)->input = expr(0);
        setState(269);
        match(exprEngineParser::COMMA);
        setState(270);
        antlrcpp::downCast<FnSL_ContainsContext *>(_localctx)->pattern = expr(0);
        setState(271);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::STARTSWITH: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_StartsWithContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(273);
        match(exprEngineParser::STARTSWITH);
        setState(274);
        match(exprEngineParser::LPAREN);
        setState(275);
        antlrcpp::downCast<FnSL_StartsWithContext *>(_localctx)->input = expr(0);
        setState(276);
        match(exprEngineParser::COMMA);
        setState(277);
        antlrcpp::downCast<FnSL_StartsWithContext *>(_localctx)->pattern = expr(0);
        setState(278);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::ENDSWITH: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_EndsWithContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(280);
        match(exprEngineParser::ENDSWITH);
        setState(281);
        match(exprEngineParser::LPAREN);
        setState(282);
        antlrcpp::downCast<FnSL_EndsWithContext *>(_localctx)->input = expr(0);
        setState(283);
        match(exprEngineParser::COMMA);
        setState(284);
        antlrcpp::downCast<FnSL_EndsWithContext *>(_localctx)->pattern = expr(0);
        setState(285);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::LIKE: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_LikeContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(287);
        match(exprEngineParser::LIKE);
        setState(288);
        match(exprEngineParser::LPAREN);
        setState(289);
        antlrcpp::downCast<FnSL_LikeContext *>(_localctx)->input = expr(0);
        setState(290);
        match(exprEngineParser::COMMA);
        setState(291);
        antlrcpp::downCast<FnSL_LikeContext *>(_localctx)->pattern = expr(0);
        setState(292);
        match(exprEngineParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TimestampFnContext ------------------------------------------------------------------

exprEngineParser::TimestampFnContext::TimestampFnContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t exprEngineParser::TimestampFnContext::getRuleIndex() const {
  return exprEngineParser::RuleTimestampFn;
}

void exprEngineParser::TimestampFnContext::copyFrom(TimestampFnContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
}

//----------------- FnSL_MonthContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_MonthContext::MONTH() {
  return getToken(exprEngineParser::MONTH, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_MonthContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_MonthContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_MonthContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_MonthContext::FnSL_MonthContext(TimestampFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_MonthContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Month(this);
}
void exprEngineParser::FnSL_MonthContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Month(this);
}

std::any exprEngineParser::FnSL_MonthContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Month(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_DateDiffContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_DateDiffContext::DATEDIFF() {
  return getToken(exprEngineParser::DATEDIFF, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_DateDiffContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

std::vector<tree::TerminalNode *> exprEngineParser::FnSL_DateDiffContext::COMMA() {
  return getTokens(exprEngineParser::COMMA);
}

tree::TerminalNode* exprEngineParser::FnSL_DateDiffContext::COMMA(size_t i) {
  return getToken(exprEngineParser::COMMA, i);
}

tree::TerminalNode* exprEngineParser::FnSL_DateDiffContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::FnSL_DateDiffContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_DateDiffContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::TimeUnitContext* exprEngineParser::FnSL_DateDiffContext::timeUnit() {
  return getRuleContext<exprEngineParser::TimeUnitContext>(0);
}

exprEngineParser::FnSL_DateDiffContext::FnSL_DateDiffContext(TimestampFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_DateDiffContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_DateDiff(this);
}
void exprEngineParser::FnSL_DateDiffContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_DateDiff(this);
}

std::any exprEngineParser::FnSL_DateDiffContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_DateDiff(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_YearContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_YearContext::YEAR() {
  return getToken(exprEngineParser::YEAR, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_YearContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_YearContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_YearContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_YearContext::FnSL_YearContext(TimestampFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_YearContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Year(this);
}
void exprEngineParser::FnSL_YearContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Year(this);
}

std::any exprEngineParser::FnSL_YearContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Year(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_MinuteContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_MinuteContext::MINUTE() {
  return getToken(exprEngineParser::MINUTE, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_MinuteContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_MinuteContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_MinuteContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_MinuteContext::FnSL_MinuteContext(TimestampFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_MinuteContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Minute(this);
}
void exprEngineParser::FnSL_MinuteContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Minute(this);
}

std::any exprEngineParser::FnSL_MinuteContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Minute(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_SecondContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_SecondContext::SECOND() {
  return getToken(exprEngineParser::SECOND, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_SecondContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_SecondContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_SecondContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_SecondContext::FnSL_SecondContext(TimestampFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_SecondContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Second(this);
}
void exprEngineParser::FnSL_SecondContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Second(this);
}

std::any exprEngineParser::FnSL_SecondContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Second(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_SecondOfDayContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_SecondOfDayContext::SECONDOFDAY() {
  return getToken(exprEngineParser::SECONDOFDAY, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_SecondOfDayContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_SecondOfDayContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_SecondOfDayContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_SecondOfDayContext::FnSL_SecondOfDayContext(TimestampFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_SecondOfDayContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_SecondOfDay(this);
}
void exprEngineParser::FnSL_SecondOfDayContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_SecondOfDay(this);
}

std::any exprEngineParser::FnSL_SecondOfDayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_SecondOfDay(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_DayOfWeekContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_DayOfWeekContext::DAYOFWEEK() {
  return getToken(exprEngineParser::DAYOFWEEK, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_DayOfWeekContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_DayOfWeekContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_DayOfWeekContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_DayOfWeekContext::FnSL_DayOfWeekContext(TimestampFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_DayOfWeekContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_DayOfWeek(this);
}
void exprEngineParser::FnSL_DayOfWeekContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_DayOfWeek(this);
}

std::any exprEngineParser::FnSL_DayOfWeekContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_DayOfWeek(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_DateAddContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_DateAddContext::DATEADD() {
  return getToken(exprEngineParser::DATEADD, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_DateAddContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

std::vector<tree::TerminalNode *> exprEngineParser::FnSL_DateAddContext::COMMA() {
  return getTokens(exprEngineParser::COMMA);
}

tree::TerminalNode* exprEngineParser::FnSL_DateAddContext::COMMA(size_t i) {
  return getToken(exprEngineParser::COMMA, i);
}

tree::TerminalNode* exprEngineParser::FnSL_DateAddContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

std::vector<exprEngineParser::ExprContext *> exprEngineParser::FnSL_DateAddContext::expr() {
  return getRuleContexts<exprEngineParser::ExprContext>();
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_DateAddContext::expr(size_t i) {
  return getRuleContext<exprEngineParser::ExprContext>(i);
}

exprEngineParser::TimeUnitContext* exprEngineParser::FnSL_DateAddContext::timeUnit() {
  return getRuleContext<exprEngineParser::TimeUnitContext>(0);
}

exprEngineParser::FnSL_DateAddContext::FnSL_DateAddContext(TimestampFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_DateAddContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_DateAdd(this);
}
void exprEngineParser::FnSL_DateAddContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_DateAdd(this);
}

std::any exprEngineParser::FnSL_DateAddContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_DateAdd(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_HourContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_HourContext::HOUR() {
  return getToken(exprEngineParser::HOUR, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_HourContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_HourContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_HourContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_HourContext::FnSL_HourContext(TimestampFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_HourContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Hour(this);
}
void exprEngineParser::FnSL_HourContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Hour(this);
}

std::any exprEngineParser::FnSL_HourContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Hour(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_WeekOfYearContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_WeekOfYearContext::WEEKOFYEAR() {
  return getToken(exprEngineParser::WEEKOFYEAR, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_WeekOfYearContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_WeekOfYearContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_WeekOfYearContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_WeekOfYearContext::FnSL_WeekOfYearContext(TimestampFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_WeekOfYearContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_WeekOfYear(this);
}
void exprEngineParser::FnSL_WeekOfYearContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_WeekOfYear(this);
}

std::any exprEngineParser::FnSL_WeekOfYearContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_WeekOfYear(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_WeekOfMonthContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_WeekOfMonthContext::WEEKOFMONTH() {
  return getToken(exprEngineParser::WEEKOFMONTH, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_WeekOfMonthContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_WeekOfMonthContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_WeekOfMonthContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_WeekOfMonthContext::FnSL_WeekOfMonthContext(TimestampFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_WeekOfMonthContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_WeekOfMonth(this);
}
void exprEngineParser::FnSL_WeekOfMonthContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_WeekOfMonth(this);
}

std::any exprEngineParser::FnSL_WeekOfMonthContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_WeekOfMonth(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FnSL_DayContext ------------------------------------------------------------------

tree::TerminalNode* exprEngineParser::FnSL_DayContext::DAY() {
  return getToken(exprEngineParser::DAY, 0);
}

tree::TerminalNode* exprEngineParser::FnSL_DayContext::LPAREN() {
  return getToken(exprEngineParser::LPAREN, 0);
}

exprEngineParser::ExprContext* exprEngineParser::FnSL_DayContext::expr() {
  return getRuleContext<exprEngineParser::ExprContext>(0);
}

tree::TerminalNode* exprEngineParser::FnSL_DayContext::RPAREN() {
  return getToken(exprEngineParser::RPAREN, 0);
}

exprEngineParser::FnSL_DayContext::FnSL_DayContext(TimestampFnContext *ctx) { copyFrom(ctx); }

void exprEngineParser::FnSL_DayContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFnSL_Day(this);
}
void exprEngineParser::FnSL_DayContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFnSL_Day(this);
}

std::any exprEngineParser::FnSL_DayContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitFnSL_Day(this);
  else
    return visitor->visitChildren(this);
}
exprEngineParser::TimestampFnContext* exprEngineParser::timestampFn() {
  TimestampFnContext *_localctx = _tracker.createInstance<TimestampFnContext>(_ctx, getState());
  enterRule(_localctx, 18, exprEngineParser::RuleTimestampFn);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(364);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case exprEngineParser::YEAR: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_YearContext>(_localctx);
        enterOuterAlt(_localctx, 1);
        setState(296);
        match(exprEngineParser::YEAR);
        setState(297);
        match(exprEngineParser::LPAREN);
        setState(298);
        expr(0);
        setState(299);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::MONTH: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_MonthContext>(_localctx);
        enterOuterAlt(_localctx, 2);
        setState(301);
        match(exprEngineParser::MONTH);
        setState(302);
        match(exprEngineParser::LPAREN);
        setState(303);
        expr(0);
        setState(304);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::DAY: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_DayContext>(_localctx);
        enterOuterAlt(_localctx, 3);
        setState(306);
        match(exprEngineParser::DAY);
        setState(307);
        match(exprEngineParser::LPAREN);
        setState(308);
        expr(0);
        setState(309);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::HOUR: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_HourContext>(_localctx);
        enterOuterAlt(_localctx, 4);
        setState(311);
        match(exprEngineParser::HOUR);
        setState(312);
        match(exprEngineParser::LPAREN);
        setState(313);
        expr(0);
        setState(314);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::MINUTE: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_MinuteContext>(_localctx);
        enterOuterAlt(_localctx, 5);
        setState(316);
        match(exprEngineParser::MINUTE);
        setState(317);
        match(exprEngineParser::LPAREN);
        setState(318);
        expr(0);
        setState(319);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::SECOND: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_SecondContext>(_localctx);
        enterOuterAlt(_localctx, 6);
        setState(321);
        match(exprEngineParser::SECOND);
        setState(322);
        match(exprEngineParser::LPAREN);
        setState(323);
        expr(0);
        setState(324);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::SECONDOFDAY: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_SecondOfDayContext>(_localctx);
        enterOuterAlt(_localctx, 7);
        setState(326);
        match(exprEngineParser::SECONDOFDAY);
        setState(327);
        match(exprEngineParser::LPAREN);
        setState(328);
        expr(0);
        setState(329);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::WEEKOFMONTH: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_WeekOfMonthContext>(_localctx);
        enterOuterAlt(_localctx, 8);
        setState(331);
        match(exprEngineParser::WEEKOFMONTH);
        setState(332);
        match(exprEngineParser::LPAREN);
        setState(333);
        expr(0);
        setState(334);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::DAYOFWEEK: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_DayOfWeekContext>(_localctx);
        enterOuterAlt(_localctx, 9);
        setState(336);
        match(exprEngineParser::DAYOFWEEK);
        setState(337);
        match(exprEngineParser::LPAREN);
        setState(338);
        expr(0);
        setState(339);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::WEEKOFYEAR: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_WeekOfYearContext>(_localctx);
        enterOuterAlt(_localctx, 10);
        setState(341);
        match(exprEngineParser::WEEKOFYEAR);
        setState(342);
        match(exprEngineParser::LPAREN);
        setState(343);
        expr(0);
        setState(344);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::DATEDIFF: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_DateDiffContext>(_localctx);
        enterOuterAlt(_localctx, 11);
        setState(346);
        match(exprEngineParser::DATEDIFF);
        setState(347);
        match(exprEngineParser::LPAREN);
        setState(348);
        antlrcpp::downCast<FnSL_DateDiffContext *>(_localctx)->date1 = expr(0);
        setState(349);
        match(exprEngineParser::COMMA);
        setState(350);
        antlrcpp::downCast<FnSL_DateDiffContext *>(_localctx)->date2 = expr(0);
        setState(351);
        match(exprEngineParser::COMMA);
        setState(352);
        antlrcpp::downCast<FnSL_DateDiffContext *>(_localctx)->unit = timeUnit();
        setState(353);
        match(exprEngineParser::RPAREN);
        break;
      }

      case exprEngineParser::DATEADD: {
        _localctx = _tracker.createInstance<exprEngineParser::FnSL_DateAddContext>(_localctx);
        enterOuterAlt(_localctx, 12);
        setState(355);
        match(exprEngineParser::DATEADD);
        setState(356);
        match(exprEngineParser::LPAREN);
        setState(357);
        antlrcpp::downCast<FnSL_DateAddContext *>(_localctx)->date1 = expr(0);
        setState(358);
        match(exprEngineParser::COMMA);
        setState(359);
        antlrcpp::downCast<FnSL_DateAddContext *>(_localctx)->duration = expr(0);
        setState(360);
        match(exprEngineParser::COMMA);
        setState(361);
        antlrcpp::downCast<FnSL_DateAddContext *>(_localctx)->unit = timeUnit();
        setState(362);
        match(exprEngineParser::RPAREN);
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- LiteralContext ------------------------------------------------------------------

exprEngineParser::LiteralContext::LiteralContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

exprEngineParser::RealLitContext* exprEngineParser::LiteralContext::realLit() {
  return getRuleContext<exprEngineParser::RealLitContext>(0);
}

exprEngineParser::IntLitContext* exprEngineParser::LiteralContext::intLit() {
  return getRuleContext<exprEngineParser::IntLitContext>(0);
}

exprEngineParser::BoolLitContext* exprEngineParser::LiteralContext::boolLit() {
  return getRuleContext<exprEngineParser::BoolLitContext>(0);
}

exprEngineParser::StringLitContext* exprEngineParser::LiteralContext::stringLit() {
  return getRuleContext<exprEngineParser::StringLitContext>(0);
}

exprEngineParser::TimestampLitContext* exprEngineParser::LiteralContext::timestampLit() {
  return getRuleContext<exprEngineParser::TimestampLitContext>(0);
}

exprEngineParser::NullLitContext* exprEngineParser::LiteralContext::nullLit() {
  return getRuleContext<exprEngineParser::NullLitContext>(0);
}


size_t exprEngineParser::LiteralContext::getRuleIndex() const {
  return exprEngineParser::RuleLiteral;
}

void exprEngineParser::LiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLiteral(this);
}

void exprEngineParser::LiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLiteral(this);
}


std::any exprEngineParser::LiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitLiteral(this);
  else
    return visitor->visitChildren(this);
}

exprEngineParser::LiteralContext* exprEngineParser::literal() {
  LiteralContext *_localctx = _tracker.createInstance<LiteralContext>(_ctx, getState());
  enterRule(_localctx, 20, exprEngineParser::RuleLiteral);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(372);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case exprEngineParser::REAL_LITERAL: {
        enterOuterAlt(_localctx, 1);
        setState(366);
        realLit();
        break;
      }

      case exprEngineParser::INT_LITERAL: {
        enterOuterAlt(_localctx, 2);
        setState(367);
        intLit();
        break;
      }

      case exprEngineParser::TRUE:
      case exprEngineParser::FALSE: {
        enterOuterAlt(_localctx, 3);
        setState(368);
        boolLit();
        break;
      }

      case exprEngineParser::STRING_LITERAL: {
        enterOuterAlt(_localctx, 4);
        setState(369);
        stringLit();
        break;
      }

      case exprEngineParser::ISO_DATETIME:
      case exprEngineParser::ISO_DATE:
      case exprEngineParser::ISO_TIME: {
        enterOuterAlt(_localctx, 5);
        setState(370);
        timestampLit();
        break;
      }

      case exprEngineParser::NULL_: {
        enterOuterAlt(_localctx, 6);
        setState(371);
        nullLit();
        break;
      }

    default:
      throw NoViableAltException(this);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RealLitContext ------------------------------------------------------------------

exprEngineParser::RealLitContext::RealLitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* exprEngineParser::RealLitContext::REAL_LITERAL() {
  return getToken(exprEngineParser::REAL_LITERAL, 0);
}


size_t exprEngineParser::RealLitContext::getRuleIndex() const {
  return exprEngineParser::RuleRealLit;
}

void exprEngineParser::RealLitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRealLit(this);
}

void exprEngineParser::RealLitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRealLit(this);
}


std::any exprEngineParser::RealLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitRealLit(this);
  else
    return visitor->visitChildren(this);
}

exprEngineParser::RealLitContext* exprEngineParser::realLit() {
  RealLitContext *_localctx = _tracker.createInstance<RealLitContext>(_ctx, getState());
  enterRule(_localctx, 22, exprEngineParser::RuleRealLit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(374);
    match(exprEngineParser::REAL_LITERAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- IntLitContext ------------------------------------------------------------------

exprEngineParser::IntLitContext::IntLitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* exprEngineParser::IntLitContext::INT_LITERAL() {
  return getToken(exprEngineParser::INT_LITERAL, 0);
}


size_t exprEngineParser::IntLitContext::getRuleIndex() const {
  return exprEngineParser::RuleIntLit;
}

void exprEngineParser::IntLitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIntLit(this);
}

void exprEngineParser::IntLitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIntLit(this);
}


std::any exprEngineParser::IntLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitIntLit(this);
  else
    return visitor->visitChildren(this);
}

exprEngineParser::IntLitContext* exprEngineParser::intLit() {
  IntLitContext *_localctx = _tracker.createInstance<IntLitContext>(_ctx, getState());
  enterRule(_localctx, 24, exprEngineParser::RuleIntLit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(376);
    match(exprEngineParser::INT_LITERAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- BoolLitContext ------------------------------------------------------------------

exprEngineParser::BoolLitContext::BoolLitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* exprEngineParser::BoolLitContext::TRUE() {
  return getToken(exprEngineParser::TRUE, 0);
}

tree::TerminalNode* exprEngineParser::BoolLitContext::FALSE() {
  return getToken(exprEngineParser::FALSE, 0);
}


size_t exprEngineParser::BoolLitContext::getRuleIndex() const {
  return exprEngineParser::RuleBoolLit;
}

void exprEngineParser::BoolLitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterBoolLit(this);
}

void exprEngineParser::BoolLitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitBoolLit(this);
}


std::any exprEngineParser::BoolLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitBoolLit(this);
  else
    return visitor->visitChildren(this);
}

exprEngineParser::BoolLitContext* exprEngineParser::boolLit() {
  BoolLitContext *_localctx = _tracker.createInstance<BoolLitContext>(_ctx, getState());
  enterRule(_localctx, 26, exprEngineParser::RuleBoolLit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(378);
    _la = _input->LA(1);
    if (!(_la == exprEngineParser::TRUE

    || _la == exprEngineParser::FALSE)) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StringLitContext ------------------------------------------------------------------

exprEngineParser::StringLitContext::StringLitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* exprEngineParser::StringLitContext::STRING_LITERAL() {
  return getToken(exprEngineParser::STRING_LITERAL, 0);
}


size_t exprEngineParser::StringLitContext::getRuleIndex() const {
  return exprEngineParser::RuleStringLit;
}

void exprEngineParser::StringLitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStringLit(this);
}

void exprEngineParser::StringLitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStringLit(this);
}


std::any exprEngineParser::StringLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitStringLit(this);
  else
    return visitor->visitChildren(this);
}

exprEngineParser::StringLitContext* exprEngineParser::stringLit() {
  StringLitContext *_localctx = _tracker.createInstance<StringLitContext>(_ctx, getState());
  enterRule(_localctx, 28, exprEngineParser::RuleStringLit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(380);
    match(exprEngineParser::STRING_LITERAL);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TimestampLitContext ------------------------------------------------------------------

exprEngineParser::TimestampLitContext::TimestampLitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* exprEngineParser::TimestampLitContext::ISO_DATETIME() {
  return getToken(exprEngineParser::ISO_DATETIME, 0);
}

tree::TerminalNode* exprEngineParser::TimestampLitContext::ISO_DATE() {
  return getToken(exprEngineParser::ISO_DATE, 0);
}

tree::TerminalNode* exprEngineParser::TimestampLitContext::ISO_TIME() {
  return getToken(exprEngineParser::ISO_TIME, 0);
}


size_t exprEngineParser::TimestampLitContext::getRuleIndex() const {
  return exprEngineParser::RuleTimestampLit;
}

void exprEngineParser::TimestampLitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTimestampLit(this);
}

void exprEngineParser::TimestampLitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTimestampLit(this);
}


std::any exprEngineParser::TimestampLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitTimestampLit(this);
  else
    return visitor->visitChildren(this);
}

exprEngineParser::TimestampLitContext* exprEngineParser::timestampLit() {
  TimestampLitContext *_localctx = _tracker.createInstance<TimestampLitContext>(_ctx, getState());
  enterRule(_localctx, 30, exprEngineParser::RuleTimestampLit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(382);
    _la = _input->LA(1);
    if (!(((((_la - 86) & ~ 0x3fULL) == 0) &&
      ((1ULL << (_la - 86)) & 7) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- NullLitContext ------------------------------------------------------------------

exprEngineParser::NullLitContext::NullLitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* exprEngineParser::NullLitContext::NULL_() {
  return getToken(exprEngineParser::NULL_, 0);
}


size_t exprEngineParser::NullLitContext::getRuleIndex() const {
  return exprEngineParser::RuleNullLit;
}

void exprEngineParser::NullLitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNullLit(this);
}

void exprEngineParser::NullLitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNullLit(this);
}


std::any exprEngineParser::NullLitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitNullLit(this);
  else
    return visitor->visitChildren(this);
}

exprEngineParser::NullLitContext* exprEngineParser::nullLit() {
  NullLitContext *_localctx = _tracker.createInstance<NullLitContext>(_ctx, getState());
  enterRule(_localctx, 32, exprEngineParser::RuleNullLit);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(384);
    match(exprEngineParser::NULL_);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- TimeUnitContext ------------------------------------------------------------------

exprEngineParser::TimeUnitContext::TimeUnitContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* exprEngineParser::TimeUnitContext::YEARS() {
  return getToken(exprEngineParser::YEARS, 0);
}

tree::TerminalNode* exprEngineParser::TimeUnitContext::MONTHS() {
  return getToken(exprEngineParser::MONTHS, 0);
}

tree::TerminalNode* exprEngineParser::TimeUnitContext::DAYS() {
  return getToken(exprEngineParser::DAYS, 0);
}

tree::TerminalNode* exprEngineParser::TimeUnitContext::WEEKS() {
  return getToken(exprEngineParser::WEEKS, 0);
}

tree::TerminalNode* exprEngineParser::TimeUnitContext::HOURS() {
  return getToken(exprEngineParser::HOURS, 0);
}

tree::TerminalNode* exprEngineParser::TimeUnitContext::MINUTES() {
  return getToken(exprEngineParser::MINUTES, 0);
}

tree::TerminalNode* exprEngineParser::TimeUnitContext::SECONDS() {
  return getToken(exprEngineParser::SECONDS, 0);
}


size_t exprEngineParser::TimeUnitContext::getRuleIndex() const {
  return exprEngineParser::RuleTimeUnit;
}

void exprEngineParser::TimeUnitContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTimeUnit(this);
}

void exprEngineParser::TimeUnitContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<exprEngineParserListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTimeUnit(this);
}


std::any exprEngineParser::TimeUnitContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<exprEngineParserVisitor*>(visitor))
    return parserVisitor->visitTimeUnit(this);
  else
    return visitor->visitChildren(this);
}

exprEngineParser::TimeUnitContext* exprEngineParser::timeUnit() {
  TimeUnitContext *_localctx = _tracker.createInstance<TimeUnitContext>(_ctx, getState());
  enterRule(_localctx, 34, exprEngineParser::RuleTimeUnit);
  size_t _la = 0;

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(386);
    _la = _input->LA(1);
    if (!((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 254) != 0))) {
    _errHandler->recoverInline(this);
    }
    else {
      _errHandler->reportMatch(this);
      consume();
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool exprEngineParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 1: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool exprEngineParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 20);
    case 1: return precpred(_ctx, 17);
    case 2: return precpred(_ctx, 16);
    case 3: return precpred(_ctx, 15);
    case 4: return precpred(_ctx, 14);
    case 5: return precpred(_ctx, 13);
    case 6: return precpred(_ctx, 12);
    case 7: return precpred(_ctx, 11);
    case 8: return precpred(_ctx, 10);
    case 9: return precpred(_ctx, 9);
    case 10: return precpred(_ctx, 8);
    case 11: return precpred(_ctx, 7);
    case 12: return precpred(_ctx, 6);
    case 13: return precpred(_ctx, 5);
    case 14: return precpred(_ctx, 4);
    case 15: return precpred(_ctx, 3);

  default:
    break;
  }
  return true;
}

void exprEngineParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  exprengineparserParserInitialize();
#else
  ::antlr4::internal::call_once(exprengineparserParserOnceFlag, exprengineparserParserInitialize);
#endif
}

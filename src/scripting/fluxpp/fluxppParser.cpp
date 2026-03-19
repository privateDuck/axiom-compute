
// Generated from fluxpp.g4 by ANTLR 4.13.2


#include "fluxppListener.h"
#include "fluxppVisitor.h"

#include "fluxppParser.h"


using namespace antlrcpp;

using namespace antlr4;

namespace {

struct FluxppParserStaticData final {
  FluxppParserStaticData(std::vector<std::string> ruleNames,
                        std::vector<std::string> literalNames,
                        std::vector<std::string> symbolicNames)
      : ruleNames(std::move(ruleNames)), literalNames(std::move(literalNames)),
        symbolicNames(std::move(symbolicNames)),
        vocabulary(this->literalNames, this->symbolicNames) {}

  FluxppParserStaticData(const FluxppParserStaticData&) = delete;
  FluxppParserStaticData(FluxppParserStaticData&&) = delete;
  FluxppParserStaticData& operator=(const FluxppParserStaticData&) = delete;
  FluxppParserStaticData& operator=(FluxppParserStaticData&&) = delete;

  std::vector<antlr4::dfa::DFA> decisionToDFA;
  antlr4::atn::PredictionContextCache sharedContextCache;
  const std::vector<std::string> ruleNames;
  const std::vector<std::string> literalNames;
  const std::vector<std::string> symbolicNames;
  const antlr4::dfa::Vocabulary vocabulary;
  antlr4::atn::SerializedATNView serializedATN;
  std::unique_ptr<antlr4::atn::ATN> atn;
};

::antlr4::internal::OnceFlag fluxppParserOnceFlag;
#if ANTLR4_USE_THREAD_LOCAL_CACHE
static thread_local
#endif
std::unique_ptr<FluxppParserStaticData> fluxppParserStaticData = nullptr;

void fluxppParserInitialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  if (fluxppParserStaticData != nullptr) {
    return;
  }
#else
  assert(fluxppParserStaticData == nullptr);
#endif
  auto staticData = std::make_unique<FluxppParserStaticData>(
    std::vector<std::string>{
      "program", "flux", "single", "statement", "assignment", "create", 
      "filter", "drop_row", "drop_col", "clamp", "set", "rename", "fill", 
      "assert_statement", "expr", "args"
    },
    std::vector<std::string>{
      "", "'='", "','", "'('", "')'", "'|'", "'^'", "'-'", "'*'", "'/'", 
      "'+'", "'<'", "'<='", "'>'", "'>='", "'=='", "'!='", "'as'", "'and'", 
      "'else'", "'drop'", "'let'", "'create'", "'keep'", "'remove'", "'clamp'", 
      "'set'", "'rename'", "'fill'", "'assert'", "'with'", "'or'", "'not'", 
      "'if'", "'in'", "'from'", "'to'", "'null'", "'true'", "'false'", "", 
      "", "", "", "", "", "", "';'"
    },
    std::vector<std::string>{
      "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", "", 
      "AS", "AND", "ELSE", "DROP", "LET", "CREATE", "KEEP", "REMOVE", "CLAMP", 
      "SET", "RENAME", "FILL", "ASSERT", "WITH", "OR", "NOT", "IF", "IN", 
      "FROM", "TO", "NULL", "TRUE", "FALSE", "ISO_DATETIME", "ISO_DATE", 
      "ISO_TIME", "NUMBER", "STRING_LITERAL", "UNTERMINATED_STRING_LITERAL", 
      "ID", "ENDLINE", "NEWLINE", "WS", "BLOCK_COMMENT", "LINE_COMMENT"
    }
  );
  static const int32_t serializedATNSegment[] = {
  	4,1,51,211,2,0,7,0,2,1,7,1,2,2,7,2,2,3,7,3,2,4,7,4,2,5,7,5,2,6,7,6,2,
  	7,7,7,2,8,7,8,2,9,7,9,2,10,7,10,2,11,7,11,2,12,7,12,2,13,7,13,2,14,7,
  	14,2,15,7,15,1,0,1,0,3,0,35,8,0,1,1,5,1,38,8,1,10,1,12,1,41,9,1,1,1,1,
  	1,1,2,1,2,1,2,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,1,3,3,3,58,8,3,1,4,
  	1,4,1,4,1,4,1,4,1,4,1,5,1,5,1,5,1,5,1,5,1,5,1,6,1,6,1,6,1,6,1,6,1,7,1,
  	7,1,7,1,7,1,7,1,8,1,8,1,8,1,8,5,8,86,8,8,10,8,12,8,89,9,8,1,8,1,8,3,8,
  	93,8,8,1,8,1,8,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,9,1,10,1,10,1,10,1,10,1,
  	10,1,10,1,11,1,11,1,11,1,11,1,11,1,11,1,12,1,12,1,12,1,12,1,12,1,12,1,
  	13,1,13,1,13,1,13,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,
  	14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,
  	14,1,14,1,14,3,14,154,8,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,
  	14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,
  	14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,14,1,
  	14,1,14,1,14,1,14,1,14,1,14,5,14,198,8,14,10,14,12,14,201,9,14,1,15,1,
  	15,1,15,5,15,206,8,15,10,15,12,15,209,9,15,1,15,0,1,28,16,0,2,4,6,8,10,
  	12,14,16,18,20,22,24,26,28,30,0,5,1,0,8,9,2,0,7,7,10,10,1,0,11,12,1,0,
  	13,14,1,0,15,16,232,0,34,1,0,0,0,2,39,1,0,0,0,4,44,1,0,0,0,6,57,1,0,0,
  	0,8,59,1,0,0,0,10,65,1,0,0,0,12,71,1,0,0,0,14,76,1,0,0,0,16,81,1,0,0,
  	0,18,96,1,0,0,0,20,104,1,0,0,0,22,110,1,0,0,0,24,116,1,0,0,0,26,122,1,
  	0,0,0,28,153,1,0,0,0,30,202,1,0,0,0,32,35,3,2,1,0,33,35,3,4,2,0,34,32,
  	1,0,0,0,34,33,1,0,0,0,35,1,1,0,0,0,36,38,3,6,3,0,37,36,1,0,0,0,38,41,
  	1,0,0,0,39,37,1,0,0,0,39,40,1,0,0,0,40,42,1,0,0,0,41,39,1,0,0,0,42,43,
  	5,0,0,1,43,3,1,0,0,0,44,45,3,28,14,0,45,46,5,0,0,1,46,5,1,0,0,0,47,58,
  	3,10,5,0,48,58,3,8,4,0,49,58,3,12,6,0,50,58,3,14,7,0,51,58,3,16,8,0,52,
  	58,3,18,9,0,53,58,3,20,10,0,54,58,3,22,11,0,55,58,3,24,12,0,56,58,3,26,
  	13,0,57,47,1,0,0,0,57,48,1,0,0,0,57,49,1,0,0,0,57,50,1,0,0,0,57,51,1,
  	0,0,0,57,52,1,0,0,0,57,53,1,0,0,0,57,54,1,0,0,0,57,55,1,0,0,0,57,56,1,
  	0,0,0,58,7,1,0,0,0,59,60,5,21,0,0,60,61,5,46,0,0,61,62,5,1,0,0,62,63,
  	3,28,14,0,63,64,5,47,0,0,64,9,1,0,0,0,65,66,5,22,0,0,66,67,5,46,0,0,67,
  	68,5,17,0,0,68,69,3,28,14,0,69,70,5,47,0,0,70,11,1,0,0,0,71,72,5,23,0,
  	0,72,73,5,33,0,0,73,74,3,28,14,0,74,75,5,47,0,0,75,13,1,0,0,0,76,77,5,
  	20,0,0,77,78,5,33,0,0,78,79,3,28,14,0,79,80,5,47,0,0,80,15,1,0,0,0,81,
  	82,5,24,0,0,82,87,5,46,0,0,83,84,5,2,0,0,84,86,5,46,0,0,85,83,1,0,0,0,
  	86,89,1,0,0,0,87,85,1,0,0,0,87,88,1,0,0,0,88,92,1,0,0,0,89,87,1,0,0,0,
  	90,91,5,33,0,0,91,93,3,28,14,0,92,90,1,0,0,0,92,93,1,0,0,0,93,94,1,0,
  	0,0,94,95,5,47,0,0,95,17,1,0,0,0,96,97,5,25,0,0,97,98,5,46,0,0,98,99,
  	5,35,0,0,99,100,3,28,14,0,100,101,5,36,0,0,101,102,3,28,14,0,102,103,
  	5,47,0,0,103,19,1,0,0,0,104,105,5,26,0,0,105,106,5,46,0,0,106,107,5,1,
  	0,0,107,108,3,28,14,0,108,109,5,47,0,0,109,21,1,0,0,0,110,111,5,27,0,
  	0,111,112,5,46,0,0,112,113,5,36,0,0,113,114,5,46,0,0,114,115,5,47,0,0,
  	115,23,1,0,0,0,116,117,5,28,0,0,117,118,5,46,0,0,118,119,5,30,0,0,119,
  	120,3,28,14,0,120,121,5,47,0,0,121,25,1,0,0,0,122,123,5,29,0,0,123,124,
  	3,28,14,0,124,125,5,47,0,0,125,27,1,0,0,0,126,127,6,14,-1,0,127,128,5,
  	3,0,0,128,129,3,28,14,0,129,130,5,4,0,0,130,154,1,0,0,0,131,132,5,5,0,
  	0,132,133,3,28,14,0,133,134,5,5,0,0,134,154,1,0,0,0,135,136,5,46,0,0,
  	136,137,5,3,0,0,137,138,3,30,15,0,138,139,5,4,0,0,139,154,1,0,0,0,140,
  	141,5,7,0,0,141,154,3,28,14,21,142,143,5,32,0,0,143,154,3,28,14,20,144,
  	154,5,46,0,0,145,154,5,43,0,0,146,154,5,40,0,0,147,154,5,41,0,0,148,154,
  	5,42,0,0,149,154,5,44,0,0,150,154,5,38,0,0,151,154,5,39,0,0,152,154,5,
  	37,0,0,153,126,1,0,0,0,153,131,1,0,0,0,153,135,1,0,0,0,153,140,1,0,0,
  	0,153,142,1,0,0,0,153,144,1,0,0,0,153,145,1,0,0,0,153,146,1,0,0,0,153,
  	147,1,0,0,0,153,148,1,0,0,0,153,149,1,0,0,0,153,150,1,0,0,0,153,151,1,
  	0,0,0,153,152,1,0,0,0,154,199,1,0,0,0,155,156,10,22,0,0,156,157,5,6,0,
  	0,157,198,3,28,14,22,158,159,10,19,0,0,159,160,7,0,0,0,160,198,3,28,14,
  	20,161,162,10,18,0,0,162,163,7,1,0,0,163,198,3,28,14,19,164,165,10,17,
  	0,0,165,166,7,2,0,0,166,167,3,28,14,0,167,168,7,2,0,0,168,169,3,28,14,
  	18,169,198,1,0,0,0,170,171,10,16,0,0,171,172,7,3,0,0,172,173,3,28,14,
  	0,173,174,7,3,0,0,174,175,3,28,14,17,175,198,1,0,0,0,176,177,10,15,0,
  	0,177,178,7,4,0,0,178,198,3,28,14,16,179,180,10,14,0,0,180,181,7,2,0,
  	0,181,198,3,28,14,15,182,183,10,13,0,0,183,184,7,3,0,0,184,198,3,28,14,
  	14,185,186,10,12,0,0,186,187,5,18,0,0,187,198,3,28,14,13,188,189,10,11,
  	0,0,189,190,5,31,0,0,190,198,3,28,14,12,191,192,10,10,0,0,192,193,5,33,
  	0,0,193,194,3,28,14,0,194,195,5,19,0,0,195,196,3,28,14,10,196,198,1,0,
  	0,0,197,155,1,0,0,0,197,158,1,0,0,0,197,161,1,0,0,0,197,164,1,0,0,0,197,
  	170,1,0,0,0,197,176,1,0,0,0,197,179,1,0,0,0,197,182,1,0,0,0,197,185,1,
  	0,0,0,197,188,1,0,0,0,197,191,1,0,0,0,198,201,1,0,0,0,199,197,1,0,0,0,
  	199,200,1,0,0,0,200,29,1,0,0,0,201,199,1,0,0,0,202,207,3,28,14,0,203,
  	204,5,2,0,0,204,206,3,28,14,0,205,203,1,0,0,0,206,209,1,0,0,0,207,205,
  	1,0,0,0,207,208,1,0,0,0,208,31,1,0,0,0,209,207,1,0,0,0,9,34,39,57,87,
  	92,153,197,199,207
  };
  staticData->serializedATN = antlr4::atn::SerializedATNView(serializedATNSegment, sizeof(serializedATNSegment) / sizeof(serializedATNSegment[0]));

  antlr4::atn::ATNDeserializer deserializer;
  staticData->atn = deserializer.deserialize(staticData->serializedATN);

  const size_t count = staticData->atn->getNumberOfDecisions();
  staticData->decisionToDFA.reserve(count);
  for (size_t i = 0; i < count; i++) { 
    staticData->decisionToDFA.emplace_back(staticData->atn->getDecisionState(i), i);
  }
  fluxppParserStaticData = std::move(staticData);
}

}

fluxppParser::fluxppParser(TokenStream *input) : fluxppParser(input, antlr4::atn::ParserATNSimulatorOptions()) {}

fluxppParser::fluxppParser(TokenStream *input, const antlr4::atn::ParserATNSimulatorOptions &options) : Parser(input) {
  fluxppParser::initialize();
  _interpreter = new atn::ParserATNSimulator(this, *fluxppParserStaticData->atn, fluxppParserStaticData->decisionToDFA, fluxppParserStaticData->sharedContextCache, options);
}

fluxppParser::~fluxppParser() {
  delete _interpreter;
}

const atn::ATN& fluxppParser::getATN() const {
  return *fluxppParserStaticData->atn;
}

std::string fluxppParser::getGrammarFileName() const {
  return "fluxpp.g4";
}

const std::vector<std::string>& fluxppParser::getRuleNames() const {
  return fluxppParserStaticData->ruleNames;
}

const dfa::Vocabulary& fluxppParser::getVocabulary() const {
  return fluxppParserStaticData->vocabulary;
}

antlr4::atn::SerializedATNView fluxppParser::getSerializedATN() const {
  return fluxppParserStaticData->serializedATN;
}


//----------------- ProgramContext ------------------------------------------------------------------

fluxppParser::ProgramContext::ProgramContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

fluxppParser::FluxContext* fluxppParser::ProgramContext::flux() {
  return getRuleContext<fluxppParser::FluxContext>(0);
}

fluxppParser::SingleContext* fluxppParser::ProgramContext::single() {
  return getRuleContext<fluxppParser::SingleContext>(0);
}


size_t fluxppParser::ProgramContext::getRuleIndex() const {
  return fluxppParser::RuleProgram;
}

void fluxppParser::ProgramContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterProgram(this);
}

void fluxppParser::ProgramContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitProgram(this);
}


std::any fluxppParser::ProgramContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitProgram(this);
  else
    return visitor->visitChildren(this);
}

fluxppParser::ProgramContext* fluxppParser::program() {
  ProgramContext *_localctx = _tracker.createInstance<ProgramContext>(_ctx, getState());
  enterRule(_localctx, 0, fluxppParser::RuleProgram);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(34);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case fluxppParser::EOF:
      case fluxppParser::DROP:
      case fluxppParser::LET:
      case fluxppParser::CREATE:
      case fluxppParser::KEEP:
      case fluxppParser::REMOVE:
      case fluxppParser::CLAMP:
      case fluxppParser::SET:
      case fluxppParser::RENAME:
      case fluxppParser::FILL:
      case fluxppParser::ASSERT: {
        enterOuterAlt(_localctx, 1);
        setState(32);
        flux();
        break;
      }

      case fluxppParser::T__2:
      case fluxppParser::T__4:
      case fluxppParser::T__6:
      case fluxppParser::NOT:
      case fluxppParser::NULL_:
      case fluxppParser::TRUE:
      case fluxppParser::FALSE:
      case fluxppParser::ISO_DATETIME:
      case fluxppParser::ISO_DATE:
      case fluxppParser::ISO_TIME:
      case fluxppParser::NUMBER:
      case fluxppParser::STRING_LITERAL:
      case fluxppParser::ID: {
        enterOuterAlt(_localctx, 2);
        setState(33);
        single();
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

//----------------- FluxContext ------------------------------------------------------------------

fluxppParser::FluxContext::FluxContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fluxppParser::FluxContext::EOF() {
  return getToken(fluxppParser::EOF, 0);
}

std::vector<fluxppParser::StatementContext *> fluxppParser::FluxContext::statement() {
  return getRuleContexts<fluxppParser::StatementContext>();
}

fluxppParser::StatementContext* fluxppParser::FluxContext::statement(size_t i) {
  return getRuleContext<fluxppParser::StatementContext>(i);
}


size_t fluxppParser::FluxContext::getRuleIndex() const {
  return fluxppParser::RuleFlux;
}

void fluxppParser::FluxContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFlux(this);
}

void fluxppParser::FluxContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFlux(this);
}


std::any fluxppParser::FluxContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitFlux(this);
  else
    return visitor->visitChildren(this);
}

fluxppParser::FluxContext* fluxppParser::flux() {
  FluxContext *_localctx = _tracker.createInstance<FluxContext>(_ctx, getState());
  enterRule(_localctx, 2, fluxppParser::RuleFlux);
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
    setState(39);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while ((((_la & ~ 0x3fULL) == 0) &&
      ((1ULL << _la) & 1072693248) != 0)) {
      setState(36);
      statement();
      setState(41);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(42);
    match(fluxppParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SingleContext ------------------------------------------------------------------

fluxppParser::SingleContext::SingleContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

fluxppParser::ExprContext* fluxppParser::SingleContext::expr() {
  return getRuleContext<fluxppParser::ExprContext>(0);
}

tree::TerminalNode* fluxppParser::SingleContext::EOF() {
  return getToken(fluxppParser::EOF, 0);
}


size_t fluxppParser::SingleContext::getRuleIndex() const {
  return fluxppParser::RuleSingle;
}

void fluxppParser::SingleContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSingle(this);
}

void fluxppParser::SingleContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSingle(this);
}


std::any fluxppParser::SingleContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitSingle(this);
  else
    return visitor->visitChildren(this);
}

fluxppParser::SingleContext* fluxppParser::single() {
  SingleContext *_localctx = _tracker.createInstance<SingleContext>(_ctx, getState());
  enterRule(_localctx, 4, fluxppParser::RuleSingle);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(44);
    expr(0);
    setState(45);
    match(fluxppParser::EOF);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- StatementContext ------------------------------------------------------------------

fluxppParser::StatementContext::StatementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

fluxppParser::CreateContext* fluxppParser::StatementContext::create() {
  return getRuleContext<fluxppParser::CreateContext>(0);
}

fluxppParser::AssignmentContext* fluxppParser::StatementContext::assignment() {
  return getRuleContext<fluxppParser::AssignmentContext>(0);
}

fluxppParser::FilterContext* fluxppParser::StatementContext::filter() {
  return getRuleContext<fluxppParser::FilterContext>(0);
}

fluxppParser::Drop_rowContext* fluxppParser::StatementContext::drop_row() {
  return getRuleContext<fluxppParser::Drop_rowContext>(0);
}

fluxppParser::Drop_colContext* fluxppParser::StatementContext::drop_col() {
  return getRuleContext<fluxppParser::Drop_colContext>(0);
}

fluxppParser::ClampContext* fluxppParser::StatementContext::clamp() {
  return getRuleContext<fluxppParser::ClampContext>(0);
}

fluxppParser::SetContext* fluxppParser::StatementContext::set() {
  return getRuleContext<fluxppParser::SetContext>(0);
}

fluxppParser::RenameContext* fluxppParser::StatementContext::rename() {
  return getRuleContext<fluxppParser::RenameContext>(0);
}

fluxppParser::FillContext* fluxppParser::StatementContext::fill() {
  return getRuleContext<fluxppParser::FillContext>(0);
}

fluxppParser::Assert_statementContext* fluxppParser::StatementContext::assert_statement() {
  return getRuleContext<fluxppParser::Assert_statementContext>(0);
}


size_t fluxppParser::StatementContext::getRuleIndex() const {
  return fluxppParser::RuleStatement;
}

void fluxppParser::StatementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStatement(this);
}

void fluxppParser::StatementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStatement(this);
}


std::any fluxppParser::StatementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitStatement(this);
  else
    return visitor->visitChildren(this);
}

fluxppParser::StatementContext* fluxppParser::statement() {
  StatementContext *_localctx = _tracker.createInstance<StatementContext>(_ctx, getState());
  enterRule(_localctx, 6, fluxppParser::RuleStatement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    setState(57);
    _errHandler->sync(this);
    switch (_input->LA(1)) {
      case fluxppParser::CREATE: {
        enterOuterAlt(_localctx, 1);
        setState(47);
        create();
        break;
      }

      case fluxppParser::LET: {
        enterOuterAlt(_localctx, 2);
        setState(48);
        assignment();
        break;
      }

      case fluxppParser::KEEP: {
        enterOuterAlt(_localctx, 3);
        setState(49);
        filter();
        break;
      }

      case fluxppParser::DROP: {
        enterOuterAlt(_localctx, 4);
        setState(50);
        drop_row();
        break;
      }

      case fluxppParser::REMOVE: {
        enterOuterAlt(_localctx, 5);
        setState(51);
        drop_col();
        break;
      }

      case fluxppParser::CLAMP: {
        enterOuterAlt(_localctx, 6);
        setState(52);
        clamp();
        break;
      }

      case fluxppParser::SET: {
        enterOuterAlt(_localctx, 7);
        setState(53);
        set();
        break;
      }

      case fluxppParser::RENAME: {
        enterOuterAlt(_localctx, 8);
        setState(54);
        rename();
        break;
      }

      case fluxppParser::FILL: {
        enterOuterAlt(_localctx, 9);
        setState(55);
        fill();
        break;
      }

      case fluxppParser::ASSERT: {
        enterOuterAlt(_localctx, 10);
        setState(56);
        assert_statement();
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

//----------------- AssignmentContext ------------------------------------------------------------------

fluxppParser::AssignmentContext::AssignmentContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fluxppParser::AssignmentContext::LET() {
  return getToken(fluxppParser::LET, 0);
}

tree::TerminalNode* fluxppParser::AssignmentContext::ID() {
  return getToken(fluxppParser::ID, 0);
}

fluxppParser::ExprContext* fluxppParser::AssignmentContext::expr() {
  return getRuleContext<fluxppParser::ExprContext>(0);
}

tree::TerminalNode* fluxppParser::AssignmentContext::ENDLINE() {
  return getToken(fluxppParser::ENDLINE, 0);
}


size_t fluxppParser::AssignmentContext::getRuleIndex() const {
  return fluxppParser::RuleAssignment;
}

void fluxppParser::AssignmentContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssignment(this);
}

void fluxppParser::AssignmentContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssignment(this);
}


std::any fluxppParser::AssignmentContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitAssignment(this);
  else
    return visitor->visitChildren(this);
}

fluxppParser::AssignmentContext* fluxppParser::assignment() {
  AssignmentContext *_localctx = _tracker.createInstance<AssignmentContext>(_ctx, getState());
  enterRule(_localctx, 8, fluxppParser::RuleAssignment);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(59);
    match(fluxppParser::LET);
    setState(60);
    match(fluxppParser::ID);
    setState(61);
    match(fluxppParser::T__0);
    setState(62);
    expr(0);
    setState(63);
    match(fluxppParser::ENDLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- CreateContext ------------------------------------------------------------------

fluxppParser::CreateContext::CreateContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fluxppParser::CreateContext::CREATE() {
  return getToken(fluxppParser::CREATE, 0);
}

tree::TerminalNode* fluxppParser::CreateContext::ID() {
  return getToken(fluxppParser::ID, 0);
}

tree::TerminalNode* fluxppParser::CreateContext::AS() {
  return getToken(fluxppParser::AS, 0);
}

fluxppParser::ExprContext* fluxppParser::CreateContext::expr() {
  return getRuleContext<fluxppParser::ExprContext>(0);
}

tree::TerminalNode* fluxppParser::CreateContext::ENDLINE() {
  return getToken(fluxppParser::ENDLINE, 0);
}


size_t fluxppParser::CreateContext::getRuleIndex() const {
  return fluxppParser::RuleCreate;
}

void fluxppParser::CreateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterCreate(this);
}

void fluxppParser::CreateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitCreate(this);
}


std::any fluxppParser::CreateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitCreate(this);
  else
    return visitor->visitChildren(this);
}

fluxppParser::CreateContext* fluxppParser::create() {
  CreateContext *_localctx = _tracker.createInstance<CreateContext>(_ctx, getState());
  enterRule(_localctx, 10, fluxppParser::RuleCreate);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(65);
    match(fluxppParser::CREATE);
    setState(66);
    match(fluxppParser::ID);
    setState(67);
    match(fluxppParser::AS);
    setState(68);
    expr(0);
    setState(69);
    match(fluxppParser::ENDLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FilterContext ------------------------------------------------------------------

fluxppParser::FilterContext::FilterContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fluxppParser::FilterContext::KEEP() {
  return getToken(fluxppParser::KEEP, 0);
}

tree::TerminalNode* fluxppParser::FilterContext::IF() {
  return getToken(fluxppParser::IF, 0);
}

fluxppParser::ExprContext* fluxppParser::FilterContext::expr() {
  return getRuleContext<fluxppParser::ExprContext>(0);
}

tree::TerminalNode* fluxppParser::FilterContext::ENDLINE() {
  return getToken(fluxppParser::ENDLINE, 0);
}


size_t fluxppParser::FilterContext::getRuleIndex() const {
  return fluxppParser::RuleFilter;
}

void fluxppParser::FilterContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFilter(this);
}

void fluxppParser::FilterContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFilter(this);
}


std::any fluxppParser::FilterContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitFilter(this);
  else
    return visitor->visitChildren(this);
}

fluxppParser::FilterContext* fluxppParser::filter() {
  FilterContext *_localctx = _tracker.createInstance<FilterContext>(_ctx, getState());
  enterRule(_localctx, 12, fluxppParser::RuleFilter);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(71);
    match(fluxppParser::KEEP);
    setState(72);
    match(fluxppParser::IF);
    setState(73);
    expr(0);
    setState(74);
    match(fluxppParser::ENDLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Drop_rowContext ------------------------------------------------------------------

fluxppParser::Drop_rowContext::Drop_rowContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fluxppParser::Drop_rowContext::DROP() {
  return getToken(fluxppParser::DROP, 0);
}

tree::TerminalNode* fluxppParser::Drop_rowContext::IF() {
  return getToken(fluxppParser::IF, 0);
}

fluxppParser::ExprContext* fluxppParser::Drop_rowContext::expr() {
  return getRuleContext<fluxppParser::ExprContext>(0);
}

tree::TerminalNode* fluxppParser::Drop_rowContext::ENDLINE() {
  return getToken(fluxppParser::ENDLINE, 0);
}


size_t fluxppParser::Drop_rowContext::getRuleIndex() const {
  return fluxppParser::RuleDrop_row;
}

void fluxppParser::Drop_rowContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDrop_row(this);
}

void fluxppParser::Drop_rowContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDrop_row(this);
}


std::any fluxppParser::Drop_rowContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitDrop_row(this);
  else
    return visitor->visitChildren(this);
}

fluxppParser::Drop_rowContext* fluxppParser::drop_row() {
  Drop_rowContext *_localctx = _tracker.createInstance<Drop_rowContext>(_ctx, getState());
  enterRule(_localctx, 14, fluxppParser::RuleDrop_row);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(76);
    match(fluxppParser::DROP);
    setState(77);
    match(fluxppParser::IF);
    setState(78);
    expr(0);
    setState(79);
    match(fluxppParser::ENDLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Drop_colContext ------------------------------------------------------------------

fluxppParser::Drop_colContext::Drop_colContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fluxppParser::Drop_colContext::REMOVE() {
  return getToken(fluxppParser::REMOVE, 0);
}

std::vector<tree::TerminalNode *> fluxppParser::Drop_colContext::ID() {
  return getTokens(fluxppParser::ID);
}

tree::TerminalNode* fluxppParser::Drop_colContext::ID(size_t i) {
  return getToken(fluxppParser::ID, i);
}

tree::TerminalNode* fluxppParser::Drop_colContext::ENDLINE() {
  return getToken(fluxppParser::ENDLINE, 0);
}

tree::TerminalNode* fluxppParser::Drop_colContext::IF() {
  return getToken(fluxppParser::IF, 0);
}

fluxppParser::ExprContext* fluxppParser::Drop_colContext::expr() {
  return getRuleContext<fluxppParser::ExprContext>(0);
}


size_t fluxppParser::Drop_colContext::getRuleIndex() const {
  return fluxppParser::RuleDrop_col;
}

void fluxppParser::Drop_colContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDrop_col(this);
}

void fluxppParser::Drop_colContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDrop_col(this);
}


std::any fluxppParser::Drop_colContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitDrop_col(this);
  else
    return visitor->visitChildren(this);
}

fluxppParser::Drop_colContext* fluxppParser::drop_col() {
  Drop_colContext *_localctx = _tracker.createInstance<Drop_colContext>(_ctx, getState());
  enterRule(_localctx, 16, fluxppParser::RuleDrop_col);
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
    setState(81);
    match(fluxppParser::REMOVE);
    setState(82);
    match(fluxppParser::ID);
    setState(87);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == fluxppParser::T__1) {
      setState(83);
      match(fluxppParser::T__1);
      setState(84);
      match(fluxppParser::ID);
      setState(89);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
    setState(92);
    _errHandler->sync(this);

    _la = _input->LA(1);
    if (_la == fluxppParser::IF) {
      setState(90);
      match(fluxppParser::IF);
      setState(91);
      antlrcpp::downCast<Drop_colContext *>(_localctx)->cond = expr(0);
    }
    setState(94);
    match(fluxppParser::ENDLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ClampContext ------------------------------------------------------------------

fluxppParser::ClampContext::ClampContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fluxppParser::ClampContext::CLAMP() {
  return getToken(fluxppParser::CLAMP, 0);
}

tree::TerminalNode* fluxppParser::ClampContext::ID() {
  return getToken(fluxppParser::ID, 0);
}

tree::TerminalNode* fluxppParser::ClampContext::FROM() {
  return getToken(fluxppParser::FROM, 0);
}

tree::TerminalNode* fluxppParser::ClampContext::TO() {
  return getToken(fluxppParser::TO, 0);
}

tree::TerminalNode* fluxppParser::ClampContext::ENDLINE() {
  return getToken(fluxppParser::ENDLINE, 0);
}

std::vector<fluxppParser::ExprContext *> fluxppParser::ClampContext::expr() {
  return getRuleContexts<fluxppParser::ExprContext>();
}

fluxppParser::ExprContext* fluxppParser::ClampContext::expr(size_t i) {
  return getRuleContext<fluxppParser::ExprContext>(i);
}


size_t fluxppParser::ClampContext::getRuleIndex() const {
  return fluxppParser::RuleClamp;
}

void fluxppParser::ClampContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterClamp(this);
}

void fluxppParser::ClampContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitClamp(this);
}


std::any fluxppParser::ClampContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitClamp(this);
  else
    return visitor->visitChildren(this);
}

fluxppParser::ClampContext* fluxppParser::clamp() {
  ClampContext *_localctx = _tracker.createInstance<ClampContext>(_ctx, getState());
  enterRule(_localctx, 18, fluxppParser::RuleClamp);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(96);
    match(fluxppParser::CLAMP);
    setState(97);
    match(fluxppParser::ID);
    setState(98);
    match(fluxppParser::FROM);
    setState(99);
    antlrcpp::downCast<ClampContext *>(_localctx)->from = expr(0);
    setState(100);
    match(fluxppParser::TO);
    setState(101);
    antlrcpp::downCast<ClampContext *>(_localctx)->to = expr(0);
    setState(102);
    match(fluxppParser::ENDLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- SetContext ------------------------------------------------------------------

fluxppParser::SetContext::SetContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fluxppParser::SetContext::SET() {
  return getToken(fluxppParser::SET, 0);
}

tree::TerminalNode* fluxppParser::SetContext::ID() {
  return getToken(fluxppParser::ID, 0);
}

fluxppParser::ExprContext* fluxppParser::SetContext::expr() {
  return getRuleContext<fluxppParser::ExprContext>(0);
}

tree::TerminalNode* fluxppParser::SetContext::ENDLINE() {
  return getToken(fluxppParser::ENDLINE, 0);
}


size_t fluxppParser::SetContext::getRuleIndex() const {
  return fluxppParser::RuleSet;
}

void fluxppParser::SetContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterSet(this);
}

void fluxppParser::SetContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitSet(this);
}


std::any fluxppParser::SetContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitSet(this);
  else
    return visitor->visitChildren(this);
}

fluxppParser::SetContext* fluxppParser::set() {
  SetContext *_localctx = _tracker.createInstance<SetContext>(_ctx, getState());
  enterRule(_localctx, 20, fluxppParser::RuleSet);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(104);
    match(fluxppParser::SET);
    setState(105);
    match(fluxppParser::ID);
    setState(106);
    match(fluxppParser::T__0);
    setState(107);
    expr(0);
    setState(108);
    match(fluxppParser::ENDLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- RenameContext ------------------------------------------------------------------

fluxppParser::RenameContext::RenameContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fluxppParser::RenameContext::RENAME() {
  return getToken(fluxppParser::RENAME, 0);
}

tree::TerminalNode* fluxppParser::RenameContext::TO() {
  return getToken(fluxppParser::TO, 0);
}

tree::TerminalNode* fluxppParser::RenameContext::ENDLINE() {
  return getToken(fluxppParser::ENDLINE, 0);
}

std::vector<tree::TerminalNode *> fluxppParser::RenameContext::ID() {
  return getTokens(fluxppParser::ID);
}

tree::TerminalNode* fluxppParser::RenameContext::ID(size_t i) {
  return getToken(fluxppParser::ID, i);
}


size_t fluxppParser::RenameContext::getRuleIndex() const {
  return fluxppParser::RuleRename;
}

void fluxppParser::RenameContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterRename(this);
}

void fluxppParser::RenameContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitRename(this);
}


std::any fluxppParser::RenameContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitRename(this);
  else
    return visitor->visitChildren(this);
}

fluxppParser::RenameContext* fluxppParser::rename() {
  RenameContext *_localctx = _tracker.createInstance<RenameContext>(_ctx, getState());
  enterRule(_localctx, 22, fluxppParser::RuleRename);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(110);
    match(fluxppParser::RENAME);
    setState(111);
    antlrcpp::downCast<RenameContext *>(_localctx)->oldCol = match(fluxppParser::ID);
    setState(112);
    match(fluxppParser::TO);
    setState(113);
    antlrcpp::downCast<RenameContext *>(_localctx)->newCol = match(fluxppParser::ID);
    setState(114);
    match(fluxppParser::ENDLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- FillContext ------------------------------------------------------------------

fluxppParser::FillContext::FillContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fluxppParser::FillContext::FILL() {
  return getToken(fluxppParser::FILL, 0);
}

tree::TerminalNode* fluxppParser::FillContext::ID() {
  return getToken(fluxppParser::ID, 0);
}

tree::TerminalNode* fluxppParser::FillContext::WITH() {
  return getToken(fluxppParser::WITH, 0);
}

fluxppParser::ExprContext* fluxppParser::FillContext::expr() {
  return getRuleContext<fluxppParser::ExprContext>(0);
}

tree::TerminalNode* fluxppParser::FillContext::ENDLINE() {
  return getToken(fluxppParser::ENDLINE, 0);
}


size_t fluxppParser::FillContext::getRuleIndex() const {
  return fluxppParser::RuleFill;
}

void fluxppParser::FillContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFill(this);
}

void fluxppParser::FillContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFill(this);
}


std::any fluxppParser::FillContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitFill(this);
  else
    return visitor->visitChildren(this);
}

fluxppParser::FillContext* fluxppParser::fill() {
  FillContext *_localctx = _tracker.createInstance<FillContext>(_ctx, getState());
  enterRule(_localctx, 24, fluxppParser::RuleFill);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(116);
    match(fluxppParser::FILL);
    setState(117);
    match(fluxppParser::ID);
    setState(118);
    match(fluxppParser::WITH);
    setState(119);
    expr(0);
    setState(120);
    match(fluxppParser::ENDLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- Assert_statementContext ------------------------------------------------------------------

fluxppParser::Assert_statementContext::Assert_statementContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

tree::TerminalNode* fluxppParser::Assert_statementContext::ASSERT() {
  return getToken(fluxppParser::ASSERT, 0);
}

fluxppParser::ExprContext* fluxppParser::Assert_statementContext::expr() {
  return getRuleContext<fluxppParser::ExprContext>(0);
}

tree::TerminalNode* fluxppParser::Assert_statementContext::ENDLINE() {
  return getToken(fluxppParser::ENDLINE, 0);
}


size_t fluxppParser::Assert_statementContext::getRuleIndex() const {
  return fluxppParser::RuleAssert_statement;
}

void fluxppParser::Assert_statementContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAssert_statement(this);
}

void fluxppParser::Assert_statementContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAssert_statement(this);
}


std::any fluxppParser::Assert_statementContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitAssert_statement(this);
  else
    return visitor->visitChildren(this);
}

fluxppParser::Assert_statementContext* fluxppParser::assert_statement() {
  Assert_statementContext *_localctx = _tracker.createInstance<Assert_statementContext>(_ctx, getState());
  enterRule(_localctx, 26, fluxppParser::RuleAssert_statement);

#if __cplusplus > 201703L
  auto onExit = finally([=, this] {
#else
  auto onExit = finally([=] {
#endif
    exitRule();
  });
  try {
    enterOuterAlt(_localctx, 1);
    setState(122);
    match(fluxppParser::ASSERT);
    setState(123);
    expr(0);
    setState(124);
    match(fluxppParser::ENDLINE);
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

//----------------- ExprContext ------------------------------------------------------------------

fluxppParser::ExprContext::ExprContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}


size_t fluxppParser::ExprContext::getRuleIndex() const {
  return fluxppParser::RuleExpr;
}

void fluxppParser::ExprContext::copyFrom(ExprContext *ctx) {
  ParserRuleContext::copyFrom(ctx);
  this->type = ctx->type;
}

//----------------- ParensContext ------------------------------------------------------------------

fluxppParser::ExprContext* fluxppParser::ParensContext::expr() {
  return getRuleContext<fluxppParser::ExprContext>(0);
}

fluxppParser::ParensContext::ParensContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::ParensContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterParens(this);
}
void fluxppParser::ParensContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitParens(this);
}

std::any fluxppParser::ParensContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitParens(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TimeContext ------------------------------------------------------------------

tree::TerminalNode* fluxppParser::TimeContext::ISO_TIME() {
  return getToken(fluxppParser::ISO_TIME, 0);
}

fluxppParser::TimeContext::TimeContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::TimeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTime(this);
}
void fluxppParser::TimeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTime(this);
}

std::any fluxppParser::TimeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitTime(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ExponentiationContext ------------------------------------------------------------------

std::vector<fluxppParser::ExprContext *> fluxppParser::ExponentiationContext::expr() {
  return getRuleContexts<fluxppParser::ExprContext>();
}

fluxppParser::ExprContext* fluxppParser::ExponentiationContext::expr(size_t i) {
  return getRuleContext<fluxppParser::ExprContext>(i);
}

fluxppParser::ExponentiationContext::ExponentiationContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::ExponentiationContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterExponentiation(this);
}
void fluxppParser::ExponentiationContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitExponentiation(this);
}

std::any fluxppParser::ExponentiationContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitExponentiation(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DateTimeContext ------------------------------------------------------------------

tree::TerminalNode* fluxppParser::DateTimeContext::ISO_DATETIME() {
  return getToken(fluxppParser::ISO_DATETIME, 0);
}

fluxppParser::DateTimeContext::DateTimeContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::DateTimeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDateTime(this);
}
void fluxppParser::DateTimeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDateTime(this);
}

std::any fluxppParser::DateTimeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitDateTime(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LogicalOrContext ------------------------------------------------------------------

std::vector<fluxppParser::ExprContext *> fluxppParser::LogicalOrContext::expr() {
  return getRuleContexts<fluxppParser::ExprContext>();
}

fluxppParser::ExprContext* fluxppParser::LogicalOrContext::expr(size_t i) {
  return getRuleContext<fluxppParser::ExprContext>(i);
}

tree::TerminalNode* fluxppParser::LogicalOrContext::OR() {
  return getToken(fluxppParser::OR, 0);
}

fluxppParser::LogicalOrContext::LogicalOrContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::LogicalOrContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalOr(this);
}
void fluxppParser::LogicalOrContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalOr(this);
}

std::any fluxppParser::LogicalOrContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitLogicalOr(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FalseLiteralContext ------------------------------------------------------------------

tree::TerminalNode* fluxppParser::FalseLiteralContext::FALSE() {
  return getToken(fluxppParser::FALSE, 0);
}

fluxppParser::FalseLiteralContext::FalseLiteralContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::FalseLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFalseLiteral(this);
}
void fluxppParser::FalseLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFalseLiteral(this);
}

std::any fluxppParser::FalseLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitFalseLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LogicalNotContext ------------------------------------------------------------------

tree::TerminalNode* fluxppParser::LogicalNotContext::NOT() {
  return getToken(fluxppParser::NOT, 0);
}

fluxppParser::ExprContext* fluxppParser::LogicalNotContext::expr() {
  return getRuleContext<fluxppParser::ExprContext>(0);
}

fluxppParser::LogicalNotContext::LogicalNotContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::LogicalNotContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalNot(this);
}
void fluxppParser::LogicalNotContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalNot(this);
}

std::any fluxppParser::LogicalNotContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitLogicalNot(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ChainedComparisonDescendingContext ------------------------------------------------------------------

std::vector<fluxppParser::ExprContext *> fluxppParser::ChainedComparisonDescendingContext::expr() {
  return getRuleContexts<fluxppParser::ExprContext>();
}

fluxppParser::ExprContext* fluxppParser::ChainedComparisonDescendingContext::expr(size_t i) {
  return getRuleContext<fluxppParser::ExprContext>(i);
}

fluxppParser::ChainedComparisonDescendingContext::ChainedComparisonDescendingContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::ChainedComparisonDescendingContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChainedComparisonDescending(this);
}
void fluxppParser::ChainedComparisonDescendingContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChainedComparisonDescending(this);
}

std::any fluxppParser::ChainedComparisonDescendingContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitChainedComparisonDescending(this);
  else
    return visitor->visitChildren(this);
}
//----------------- MultiplicativeContext ------------------------------------------------------------------

std::vector<fluxppParser::ExprContext *> fluxppParser::MultiplicativeContext::expr() {
  return getRuleContexts<fluxppParser::ExprContext>();
}

fluxppParser::ExprContext* fluxppParser::MultiplicativeContext::expr(size_t i) {
  return getRuleContext<fluxppParser::ExprContext>(i);
}

fluxppParser::MultiplicativeContext::MultiplicativeContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::MultiplicativeContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterMultiplicative(this);
}
void fluxppParser::MultiplicativeContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitMultiplicative(this);
}

std::any fluxppParser::MultiplicativeContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitMultiplicative(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AdditiveContext ------------------------------------------------------------------

std::vector<fluxppParser::ExprContext *> fluxppParser::AdditiveContext::expr() {
  return getRuleContexts<fluxppParser::ExprContext>();
}

fluxppParser::ExprContext* fluxppParser::AdditiveContext::expr(size_t i) {
  return getRuleContext<fluxppParser::ExprContext>(i);
}

fluxppParser::AdditiveContext::AdditiveContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::AdditiveContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAdditive(this);
}
void fluxppParser::AdditiveContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAdditive(this);
}

std::any fluxppParser::AdditiveContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitAdditive(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LessInequalContext ------------------------------------------------------------------

std::vector<fluxppParser::ExprContext *> fluxppParser::LessInequalContext::expr() {
  return getRuleContexts<fluxppParser::ExprContext>();
}

fluxppParser::ExprContext* fluxppParser::LessInequalContext::expr(size_t i) {
  return getRuleContext<fluxppParser::ExprContext>(i);
}

fluxppParser::LessInequalContext::LessInequalContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::LessInequalContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLessInequal(this);
}
void fluxppParser::LessInequalContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLessInequal(this);
}

std::any fluxppParser::LessInequalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitLessInequal(this);
  else
    return visitor->visitChildren(this);
}
//----------------- AbsContext ------------------------------------------------------------------

fluxppParser::ExprContext* fluxppParser::AbsContext::expr() {
  return getRuleContext<fluxppParser::ExprContext>(0);
}

fluxppParser::AbsContext::AbsContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::AbsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterAbs(this);
}
void fluxppParser::AbsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitAbs(this);
}

std::any fluxppParser::AbsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitAbs(this);
  else
    return visitor->visitChildren(this);
}
//----------------- IdentifierContext ------------------------------------------------------------------

tree::TerminalNode* fluxppParser::IdentifierContext::ID() {
  return getToken(fluxppParser::ID, 0);
}

fluxppParser::IdentifierContext::IdentifierContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::IdentifierContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterIdentifier(this);
}
void fluxppParser::IdentifierContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitIdentifier(this);
}

std::any fluxppParser::IdentifierContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitIdentifier(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NumberContext ------------------------------------------------------------------

tree::TerminalNode* fluxppParser::NumberContext::NUMBER() {
  return getToken(fluxppParser::NUMBER, 0);
}

fluxppParser::NumberContext::NumberContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::NumberContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNumber(this);
}
void fluxppParser::NumberContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNumber(this);
}

std::any fluxppParser::NumberContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitNumber(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TrueLiteralContext ------------------------------------------------------------------

tree::TerminalNode* fluxppParser::TrueLiteralContext::TRUE() {
  return getToken(fluxppParser::TRUE, 0);
}

fluxppParser::TrueLiteralContext::TrueLiteralContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::TrueLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTrueLiteral(this);
}
void fluxppParser::TrueLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTrueLiteral(this);
}

std::any fluxppParser::TrueLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitTrueLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ComparisonContext ------------------------------------------------------------------

std::vector<fluxppParser::ExprContext *> fluxppParser::ComparisonContext::expr() {
  return getRuleContexts<fluxppParser::ExprContext>();
}

fluxppParser::ExprContext* fluxppParser::ComparisonContext::expr(size_t i) {
  return getRuleContext<fluxppParser::ExprContext>(i);
}

fluxppParser::ComparisonContext::ComparisonContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::ComparisonContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterComparison(this);
}
void fluxppParser::ComparisonContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitComparison(this);
}

std::any fluxppParser::ComparisonContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitComparison(this);
  else
    return visitor->visitChildren(this);
}
//----------------- LogicalAndContext ------------------------------------------------------------------

std::vector<fluxppParser::ExprContext *> fluxppParser::LogicalAndContext::expr() {
  return getRuleContexts<fluxppParser::ExprContext>();
}

fluxppParser::ExprContext* fluxppParser::LogicalAndContext::expr(size_t i) {
  return getRuleContext<fluxppParser::ExprContext>(i);
}

tree::TerminalNode* fluxppParser::LogicalAndContext::AND() {
  return getToken(fluxppParser::AND, 0);
}

fluxppParser::LogicalAndContext::LogicalAndContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::LogicalAndContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterLogicalAnd(this);
}
void fluxppParser::LogicalAndContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitLogicalAnd(this);
}

std::any fluxppParser::LogicalAndContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitLogicalAnd(this);
  else
    return visitor->visitChildren(this);
}
//----------------- FunctionCallContext ------------------------------------------------------------------

fluxppParser::ArgsContext* fluxppParser::FunctionCallContext::args() {
  return getRuleContext<fluxppParser::ArgsContext>(0);
}

tree::TerminalNode* fluxppParser::FunctionCallContext::ID() {
  return getToken(fluxppParser::ID, 0);
}

fluxppParser::FunctionCallContext::FunctionCallContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::FunctionCallContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterFunctionCall(this);
}
void fluxppParser::FunctionCallContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitFunctionCall(this);
}

std::any fluxppParser::FunctionCallContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitFunctionCall(this);
  else
    return visitor->visitChildren(this);
}
//----------------- TernaryContext ------------------------------------------------------------------

tree::TerminalNode* fluxppParser::TernaryContext::IF() {
  return getToken(fluxppParser::IF, 0);
}

tree::TerminalNode* fluxppParser::TernaryContext::ELSE() {
  return getToken(fluxppParser::ELSE, 0);
}

std::vector<fluxppParser::ExprContext *> fluxppParser::TernaryContext::expr() {
  return getRuleContexts<fluxppParser::ExprContext>();
}

fluxppParser::ExprContext* fluxppParser::TernaryContext::expr(size_t i) {
  return getRuleContext<fluxppParser::ExprContext>(i);
}

fluxppParser::TernaryContext::TernaryContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::TernaryContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterTernary(this);
}
void fluxppParser::TernaryContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitTernary(this);
}

std::any fluxppParser::TernaryContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitTernary(this);
  else
    return visitor->visitChildren(this);
}
//----------------- ChainedComparisonAscendingContext ------------------------------------------------------------------

std::vector<fluxppParser::ExprContext *> fluxppParser::ChainedComparisonAscendingContext::expr() {
  return getRuleContexts<fluxppParser::ExprContext>();
}

fluxppParser::ExprContext* fluxppParser::ChainedComparisonAscendingContext::expr(size_t i) {
  return getRuleContext<fluxppParser::ExprContext>(i);
}

fluxppParser::ChainedComparisonAscendingContext::ChainedComparisonAscendingContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::ChainedComparisonAscendingContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterChainedComparisonAscending(this);
}
void fluxppParser::ChainedComparisonAscendingContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitChainedComparisonAscending(this);
}

std::any fluxppParser::ChainedComparisonAscendingContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitChainedComparisonAscending(this);
  else
    return visitor->visitChildren(this);
}
//----------------- DateContext ------------------------------------------------------------------

tree::TerminalNode* fluxppParser::DateContext::ISO_DATE() {
  return getToken(fluxppParser::ISO_DATE, 0);
}

fluxppParser::DateContext::DateContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::DateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterDate(this);
}
void fluxppParser::DateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitDate(this);
}

std::any fluxppParser::DateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitDate(this);
  else
    return visitor->visitChildren(this);
}
//----------------- GreaterInequalContext ------------------------------------------------------------------

std::vector<fluxppParser::ExprContext *> fluxppParser::GreaterInequalContext::expr() {
  return getRuleContexts<fluxppParser::ExprContext>();
}

fluxppParser::ExprContext* fluxppParser::GreaterInequalContext::expr(size_t i) {
  return getRuleContext<fluxppParser::ExprContext>(i);
}

fluxppParser::GreaterInequalContext::GreaterInequalContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::GreaterInequalContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterGreaterInequal(this);
}
void fluxppParser::GreaterInequalContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitGreaterInequal(this);
}

std::any fluxppParser::GreaterInequalContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitGreaterInequal(this);
  else
    return visitor->visitChildren(this);
}
//----------------- StringLiteralContext ------------------------------------------------------------------

tree::TerminalNode* fluxppParser::StringLiteralContext::STRING_LITERAL() {
  return getToken(fluxppParser::STRING_LITERAL, 0);
}

fluxppParser::StringLiteralContext::StringLiteralContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::StringLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterStringLiteral(this);
}
void fluxppParser::StringLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitStringLiteral(this);
}

std::any fluxppParser::StringLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitStringLiteral(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NegateContext ------------------------------------------------------------------

fluxppParser::ExprContext* fluxppParser::NegateContext::expr() {
  return getRuleContext<fluxppParser::ExprContext>(0);
}

fluxppParser::NegateContext::NegateContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::NegateContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNegate(this);
}
void fluxppParser::NegateContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNegate(this);
}

std::any fluxppParser::NegateContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitNegate(this);
  else
    return visitor->visitChildren(this);
}
//----------------- NullLiteralContext ------------------------------------------------------------------

tree::TerminalNode* fluxppParser::NullLiteralContext::NULL_() {
  return getToken(fluxppParser::NULL_, 0);
}

fluxppParser::NullLiteralContext::NullLiteralContext(ExprContext *ctx) { copyFrom(ctx); }

void fluxppParser::NullLiteralContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterNullLiteral(this);
}
void fluxppParser::NullLiteralContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitNullLiteral(this);
}

std::any fluxppParser::NullLiteralContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitNullLiteral(this);
  else
    return visitor->visitChildren(this);
}

fluxppParser::ExprContext* fluxppParser::expr() {
   return expr(0);
}

fluxppParser::ExprContext* fluxppParser::expr(int precedence) {
  ParserRuleContext *parentContext = _ctx;
  size_t parentState = getState();
  fluxppParser::ExprContext *_localctx = _tracker.createInstance<ExprContext>(_ctx, parentState);
  fluxppParser::ExprContext *previousContext = _localctx;
  (void)previousContext; // Silence compiler, in case the context is not used by generated code.
  size_t startState = 28;
  enterRecursionRule(_localctx, 28, fluxppParser::RuleExpr, precedence);

    size_t _la = 0;

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
    setState(153);
    _errHandler->sync(this);
    switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 5, _ctx)) {
    case 1: {
      _localctx = _tracker.createInstance<ParensContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;

      setState(127);
      match(fluxppParser::T__2);
      setState(128);
      expr(0);
      setState(129);
      match(fluxppParser::T__3);
      break;
    }

    case 2: {
      _localctx = _tracker.createInstance<AbsContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(131);
      match(fluxppParser::T__4);
      setState(132);
      expr(0);
      setState(133);
      match(fluxppParser::T__4);
      break;
    }

    case 3: {
      _localctx = _tracker.createInstance<FunctionCallContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(135);
      antlrcpp::downCast<FunctionCallContext *>(_localctx)->function = match(fluxppParser::ID);
      setState(136);
      match(fluxppParser::T__2);
      setState(137);
      args();
      setState(138);
      match(fluxppParser::T__3);
      break;
    }

    case 4: {
      _localctx = _tracker.createInstance<NegateContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(140);
      match(fluxppParser::T__6);
      setState(141);
      expr(21);
      break;
    }

    case 5: {
      _localctx = _tracker.createInstance<LogicalNotContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(142);
      match(fluxppParser::NOT);
      setState(143);
      expr(20);
      break;
    }

    case 6: {
      _localctx = _tracker.createInstance<IdentifierContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(144);
      match(fluxppParser::ID);
      break;
    }

    case 7: {
      _localctx = _tracker.createInstance<NumberContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(145);
      match(fluxppParser::NUMBER);
      break;
    }

    case 8: {
      _localctx = _tracker.createInstance<DateTimeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(146);
      match(fluxppParser::ISO_DATETIME);
      break;
    }

    case 9: {
      _localctx = _tracker.createInstance<DateContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(147);
      match(fluxppParser::ISO_DATE);
      break;
    }

    case 10: {
      _localctx = _tracker.createInstance<TimeContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(148);
      match(fluxppParser::ISO_TIME);
      break;
    }

    case 11: {
      _localctx = _tracker.createInstance<StringLiteralContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(149);
      match(fluxppParser::STRING_LITERAL);
      break;
    }

    case 12: {
      _localctx = _tracker.createInstance<TrueLiteralContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(150);
      match(fluxppParser::TRUE);
      break;
    }

    case 13: {
      _localctx = _tracker.createInstance<FalseLiteralContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(151);
      match(fluxppParser::FALSE);
      break;
    }

    case 14: {
      _localctx = _tracker.createInstance<NullLiteralContext>(_localctx);
      _ctx = _localctx;
      previousContext = _localctx;
      setState(152);
      match(fluxppParser::NULL_);
      break;
    }

    default:
      break;
    }
    _ctx->stop = _input->LT(-1);
    setState(199);
    _errHandler->sync(this);
    alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    while (alt != 2 && alt != atn::ATN::INVALID_ALT_NUMBER) {
      if (alt == 1) {
        if (!_parseListeners.empty())
          triggerExitRuleEvent();
        previousContext = _localctx;
        setState(197);
        _errHandler->sync(this);
        switch (getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 6, _ctx)) {
        case 1: {
          auto newContext = _tracker.createInstance<ExponentiationContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(155);

          if (!(precpred(_ctx, 22))) throw FailedPredicateException(this, "precpred(_ctx, 22)");
          setState(156);
          antlrcpp::downCast<ExponentiationContext *>(_localctx)->op = match(fluxppParser::T__5);
          setState(157);
          antlrcpp::downCast<ExponentiationContext *>(_localctx)->right = expr(22);
          break;
        }

        case 2: {
          auto newContext = _tracker.createInstance<MultiplicativeContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(158);

          if (!(precpred(_ctx, 19))) throw FailedPredicateException(this, "precpred(_ctx, 19)");
          setState(159);
          antlrcpp::downCast<MultiplicativeContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == fluxppParser::T__7

          || _la == fluxppParser::T__8)) {
            antlrcpp::downCast<MultiplicativeContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(160);
          antlrcpp::downCast<MultiplicativeContext *>(_localctx)->right = expr(20);
          break;
        }

        case 3: {
          auto newContext = _tracker.createInstance<AdditiveContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(161);

          if (!(precpred(_ctx, 18))) throw FailedPredicateException(this, "precpred(_ctx, 18)");
          setState(162);
          antlrcpp::downCast<AdditiveContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == fluxppParser::T__6

          || _la == fluxppParser::T__9)) {
            antlrcpp::downCast<AdditiveContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(163);
          antlrcpp::downCast<AdditiveContext *>(_localctx)->right = expr(19);
          break;
        }

        case 4: {
          auto newContext = _tracker.createInstance<ChainedComparisonAscendingContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(164);

          if (!(precpred(_ctx, 17))) throw FailedPredicateException(this, "precpred(_ctx, 17)");
          setState(165);
          antlrcpp::downCast<ChainedComparisonAscendingContext *>(_localctx)->opleft = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == fluxppParser::T__10

          || _la == fluxppParser::T__11)) {
            antlrcpp::downCast<ChainedComparisonAscendingContext *>(_localctx)->opleft = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(166);
          antlrcpp::downCast<ChainedComparisonAscendingContext *>(_localctx)->middle = expr(0);
          setState(167);
          antlrcpp::downCast<ChainedComparisonAscendingContext *>(_localctx)->opright = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == fluxppParser::T__10

          || _la == fluxppParser::T__11)) {
            antlrcpp::downCast<ChainedComparisonAscendingContext *>(_localctx)->opright = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(168);
          antlrcpp::downCast<ChainedComparisonAscendingContext *>(_localctx)->right = expr(18);
          break;
        }

        case 5: {
          auto newContext = _tracker.createInstance<ChainedComparisonDescendingContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(170);

          if (!(precpred(_ctx, 16))) throw FailedPredicateException(this, "precpred(_ctx, 16)");
          setState(171);
          antlrcpp::downCast<ChainedComparisonDescendingContext *>(_localctx)->opleft = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == fluxppParser::T__12

          || _la == fluxppParser::T__13)) {
            antlrcpp::downCast<ChainedComparisonDescendingContext *>(_localctx)->opleft = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(172);
          antlrcpp::downCast<ChainedComparisonDescendingContext *>(_localctx)->middle = expr(0);
          setState(173);
          antlrcpp::downCast<ChainedComparisonDescendingContext *>(_localctx)->opright = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == fluxppParser::T__12

          || _la == fluxppParser::T__13)) {
            antlrcpp::downCast<ChainedComparisonDescendingContext *>(_localctx)->opright = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(174);
          antlrcpp::downCast<ChainedComparisonDescendingContext *>(_localctx)->right = expr(17);
          break;
        }

        case 6: {
          auto newContext = _tracker.createInstance<ComparisonContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(176);

          if (!(precpred(_ctx, 15))) throw FailedPredicateException(this, "precpred(_ctx, 15)");
          setState(177);
          antlrcpp::downCast<ComparisonContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == fluxppParser::T__14

          || _la == fluxppParser::T__15)) {
            antlrcpp::downCast<ComparisonContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(178);
          antlrcpp::downCast<ComparisonContext *>(_localctx)->right = expr(16);
          break;
        }

        case 7: {
          auto newContext = _tracker.createInstance<LessInequalContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(179);

          if (!(precpred(_ctx, 14))) throw FailedPredicateException(this, "precpred(_ctx, 14)");
          setState(180);
          antlrcpp::downCast<LessInequalContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == fluxppParser::T__10

          || _la == fluxppParser::T__11)) {
            antlrcpp::downCast<LessInequalContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(181);
          antlrcpp::downCast<LessInequalContext *>(_localctx)->right = expr(15);
          break;
        }

        case 8: {
          auto newContext = _tracker.createInstance<GreaterInequalContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(182);

          if (!(precpred(_ctx, 13))) throw FailedPredicateException(this, "precpred(_ctx, 13)");
          setState(183);
          antlrcpp::downCast<GreaterInequalContext *>(_localctx)->op = _input->LT(1);
          _la = _input->LA(1);
          if (!(_la == fluxppParser::T__12

          || _la == fluxppParser::T__13)) {
            antlrcpp::downCast<GreaterInequalContext *>(_localctx)->op = _errHandler->recoverInline(this);
          }
          else {
            _errHandler->reportMatch(this);
            consume();
          }
          setState(184);
          antlrcpp::downCast<GreaterInequalContext *>(_localctx)->right = expr(14);
          break;
        }

        case 9: {
          auto newContext = _tracker.createInstance<LogicalAndContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(185);

          if (!(precpred(_ctx, 12))) throw FailedPredicateException(this, "precpred(_ctx, 12)");
          setState(186);
          antlrcpp::downCast<LogicalAndContext *>(_localctx)->op = match(fluxppParser::AND);
          setState(187);
          antlrcpp::downCast<LogicalAndContext *>(_localctx)->right = expr(13);
          break;
        }

        case 10: {
          auto newContext = _tracker.createInstance<LogicalOrContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->left = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(188);

          if (!(precpred(_ctx, 11))) throw FailedPredicateException(this, "precpred(_ctx, 11)");
          setState(189);
          antlrcpp::downCast<LogicalOrContext *>(_localctx)->op = match(fluxppParser::OR);
          setState(190);
          antlrcpp::downCast<LogicalOrContext *>(_localctx)->right = expr(12);
          break;
        }

        case 11: {
          auto newContext = _tracker.createInstance<TernaryContext>(_tracker.createInstance<ExprContext>(parentContext, parentState));
          _localctx = newContext;
          newContext->trueExpr = previousContext;
          pushNewRecursionContext(newContext, startState, RuleExpr);
          setState(191);

          if (!(precpred(_ctx, 10))) throw FailedPredicateException(this, "precpred(_ctx, 10)");
          setState(192);
          match(fluxppParser::IF);
          setState(193);
          antlrcpp::downCast<TernaryContext *>(_localctx)->cond = expr(0);
          setState(194);
          match(fluxppParser::ELSE);
          setState(195);
          antlrcpp::downCast<TernaryContext *>(_localctx)->falseExpr = expr(10);
          break;
        }

        default:
          break;
        } 
      }
      setState(201);
      _errHandler->sync(this);
      alt = getInterpreter<atn::ParserATNSimulator>()->adaptivePredict(_input, 7, _ctx);
    }
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }
  return _localctx;
}

//----------------- ArgsContext ------------------------------------------------------------------

fluxppParser::ArgsContext::ArgsContext(ParserRuleContext *parent, size_t invokingState)
  : ParserRuleContext(parent, invokingState) {
}

std::vector<fluxppParser::ExprContext *> fluxppParser::ArgsContext::expr() {
  return getRuleContexts<fluxppParser::ExprContext>();
}

fluxppParser::ExprContext* fluxppParser::ArgsContext::expr(size_t i) {
  return getRuleContext<fluxppParser::ExprContext>(i);
}


size_t fluxppParser::ArgsContext::getRuleIndex() const {
  return fluxppParser::RuleArgs;
}

void fluxppParser::ArgsContext::enterRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->enterArgs(this);
}

void fluxppParser::ArgsContext::exitRule(tree::ParseTreeListener *listener) {
  auto parserListener = dynamic_cast<fluxppListener *>(listener);
  if (parserListener != nullptr)
    parserListener->exitArgs(this);
}


std::any fluxppParser::ArgsContext::accept(tree::ParseTreeVisitor *visitor) {
  if (auto parserVisitor = dynamic_cast<fluxppVisitor*>(visitor))
    return parserVisitor->visitArgs(this);
  else
    return visitor->visitChildren(this);
}

fluxppParser::ArgsContext* fluxppParser::args() {
  ArgsContext *_localctx = _tracker.createInstance<ArgsContext>(_ctx, getState());
  enterRule(_localctx, 30, fluxppParser::RuleArgs);
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
    setState(202);
    expr(0);
    setState(207);
    _errHandler->sync(this);
    _la = _input->LA(1);
    while (_la == fluxppParser::T__1) {
      setState(203);
      match(fluxppParser::T__1);
      setState(204);
      expr(0);
      setState(209);
      _errHandler->sync(this);
      _la = _input->LA(1);
    }
   
  }
  catch (RecognitionException &e) {
    _errHandler->reportError(this, e);
    _localctx->exception = std::current_exception();
    _errHandler->recover(this, _localctx->exception);
  }

  return _localctx;
}

bool fluxppParser::sempred(RuleContext *context, size_t ruleIndex, size_t predicateIndex) {
  switch (ruleIndex) {
    case 14: return exprSempred(antlrcpp::downCast<ExprContext *>(context), predicateIndex);

  default:
    break;
  }
  return true;
}

bool fluxppParser::exprSempred(ExprContext *_localctx, size_t predicateIndex) {
  switch (predicateIndex) {
    case 0: return precpred(_ctx, 22);
    case 1: return precpred(_ctx, 19);
    case 2: return precpred(_ctx, 18);
    case 3: return precpred(_ctx, 17);
    case 4: return precpred(_ctx, 16);
    case 5: return precpred(_ctx, 15);
    case 6: return precpred(_ctx, 14);
    case 7: return precpred(_ctx, 13);
    case 8: return precpred(_ctx, 12);
    case 9: return precpred(_ctx, 11);
    case 10: return precpred(_ctx, 10);

  default:
    break;
  }
  return true;
}

void fluxppParser::initialize() {
#if ANTLR4_USE_THREAD_LOCAL_CACHE
  fluxppParserInitialize();
#else
  ::antlr4::internal::call_once(fluxppParserOnceFlag, fluxppParserInitialize);
#endif
}

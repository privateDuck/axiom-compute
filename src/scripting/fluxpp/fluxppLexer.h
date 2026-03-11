
// Generated from fluxpp.g4 by ANTLR 4.13.2

#pragma once


#include "antlr4-runtime.h"




class  fluxppLexer : public antlr4::Lexer {
public:
  enum {
    T__0 = 1, T__1 = 2, T__2 = 3, T__3 = 4, T__4 = 5, T__5 = 6, T__6 = 7, 
    T__7 = 8, T__8 = 9, T__9 = 10, T__10 = 11, T__11 = 12, T__12 = 13, T__13 = 14, 
    T__14 = 15, T__15 = 16, T__16 = 17, AS = 18, AND = 19, ELSE = 20, DROP = 21, 
    LET = 22, CREATE = 23, KEEP = 24, REMOVE = 25, CLAMP = 26, SET = 27, 
    RENAME = 28, FILL = 29, ASSERT = 30, WITH = 31, OR = 32, NOT = 33, IF = 34, 
    IN = 35, FROM = 36, TO = 37, NULL_ = 38, TRUE = 39, FALSE = 40, ISO_DATETIME = 41, 
    ISO_DATE = 42, ISO_TIME = 43, NUMBER = 44, STRING_LITERAL = 45, UNTERMINATED_STRING_LITERAL = 46, 
    ID = 47, ENDLINE = 48, NEWLINE = 49, WS = 50, BLOCK_COMMENT = 51, LINE_COMMENT = 52
  };

  explicit fluxppLexer(antlr4::CharStream *input);

  ~fluxppLexer() override;


  std::string getGrammarFileName() const override;

  const std::vector<std::string>& getRuleNames() const override;

  const std::vector<std::string>& getChannelNames() const override;

  const std::vector<std::string>& getModeNames() const override;

  const antlr4::dfa::Vocabulary& getVocabulary() const override;

  antlr4::atn::SerializedATNView getSerializedATN() const override;

  const antlr4::atn::ATN& getATN() const override;

  // By default the static state used to implement the lexer is lazily initialized during the first
  // call to the constructor. You can call this function if you wish to initialize the static state
  // ahead of time.
  static void initialize();

private:

  // Individual action functions triggered by action() above.

  // Individual semantic predicate functions triggered by sempred() above.

};


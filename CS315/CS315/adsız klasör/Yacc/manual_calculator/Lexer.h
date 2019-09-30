#pragma once

#include <iostream>
#include <string>
#include <deque>
#include <inttypes.h>

class Token
{
public:
  enum TokenType { TT_IDENTIFIER, TT_INTEGER, TT_FLOAT, TT_CHAR };
  enum ValueType { VT_INTEGER, VT_STRING, VT_FLOAT, VT_CHAR };
  Token(std::string const & name);
  Token();
  Token(int64_t ival);
  Token(double fval);
  Token(char cval);
  Token(Token const & other);
  ~Token();
  Token const & operator = (Token const & other);
  TokenType getTokenType() const;
  ValueType getTokenValue() const;
  int64_t getIntegerValue() const;
  double getFloatValue() const;
  char getCharValue() const;
  std::string const & getStringValue() const;
private:
  TokenType tokenType_;
  ValueType valueType_;
  union {
    std::string * stringValue_;
    int64_t integerValue_;
    double floatValue_;
    char charValue_;
  } value_;
};

std::ostream & operator<< (std::ostream & ostr, Token const & token);

class Lexer
{
public:  
  Lexer(std::istream & input);
  bool getNextToken(Token & token);
  bool peekChar(char & c, int i=1);
private:
  bool getNextChar(char & c);
  static const int charBufferSize_ = 10;
  std::istream & input_;
  char charBuffer_[charBufferSize_];
  int bufferPos_;
  int numBufferedChars_;
};



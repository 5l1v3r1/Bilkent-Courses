#include "Lexer.h"

#include <cctype>
#include <sstream>
#include <cassert>

using namespace std;

Token::Token() 
  : tokenType_(TT_INTEGER), valueType_(VT_INTEGER)
{
  value_.integerValue_ = 0; 
}

Token::Token(string const & name) 
  : tokenType_(TT_IDENTIFIER), valueType_(VT_STRING)
{
  value_.stringValue_ = new string(name);
}

Token::Token(int64_t ival) 
  : tokenType_(TT_INTEGER), valueType_(VT_INTEGER)
{
  value_.integerValue_ = ival;
}

Token::Token(double fval) 
  : tokenType_(TT_FLOAT), valueType_(VT_FLOAT)
{
  value_.floatValue_ = fval;
}

Token::Token(char cval)
  : tokenType_(TT_CHAR), valueType_(VT_CHAR)
{
  value_.charValue_ = cval;
}

Token::Token(Token const & other)
  : tokenType_(other.tokenType_), valueType_(other.valueType_)
{ 
  value_ = other.value_;
  if (valueType_==VT_STRING) 
    value_.stringValue_ = new string(*other.value_.stringValue_); 
}

Token::~Token() 
{ 
  if (valueType_==VT_STRING) 
    delete value_.stringValue_; 
}

Token const & Token::operator= (Token const & other) 
{
  tokenType_ = other.tokenType_;
  valueType_ = other.valueType_;
  value_ = other.value_;
  if (valueType_==VT_STRING) 
    value_.stringValue_ = new string(*other.value_.stringValue_); 
}
 
Token::TokenType Token::getTokenType() const 
{ 
  return tokenType_; 
}

Token::ValueType Token::getTokenValue() const 
{ 
  return valueType_; 
}

int64_t Token::getIntegerValue() const 
{ 
  return value_.integerValue_; 
}

double Token::getFloatValue() const 
{ 
  return value_.floatValue_; 
}

char Token::getCharValue() const 
{ 
  return value_.charValue_; 
}

string const & Token::getStringValue() const 
{
  return *value_.stringValue_; 
}

ostream & operator<< (ostream & ostr, Token const & token)
{
  ostr << "[";
  switch(token.getTokenType()) {
  case Token::TT_IDENTIFIER:
    ostr << "ID: " << token.getStringValue();
    break;
  case Token::TT_INTEGER: 
    ostr << "INT: " << token.getIntegerValue();
    break;
  case Token::TT_FLOAT: 
    ostr << "FLOAT: " << token.getFloatValue();
    break;
  case Token::TT_CHAR:
    ostr << "CHAR: " << token.getCharValue();
    break;
  }
  ostr << "]";
  return ostr;
}

Lexer::Lexer(istream & input)
  : input_(input), bufferPos_(0), numBufferedChars_(0)
{}

bool Lexer::getNextChar(char & c)
{
  if (numBufferedChars_==0) {
    input_.get(c);
    if (input_.eof())
      return false;
  } else {
    c = charBuffer_[bufferPos_];
    bufferPos_ = (bufferPos_+1) % charBufferSize_; 
    numBufferedChars_--;
  }
  return true;
}

bool Lexer::peekChar(char & c, int i)
{
  assert(i>0);
  if (i>numBufferedChars_) {
    int nextPos = (bufferPos_+numBufferedChars_) % charBufferSize_;
    while (i>numBufferedChars_) {
      input_.get(c);
      if (input_.eof())
        return false;
      charBuffer_[nextPos] = c;
      nextPos = (nextPos+1) % charBufferSize_; 
      numBufferedChars_++;
    }
  }
  int pos = (bufferPos_ + i - 1) % charBufferSize_;
  c = charBuffer_[pos];
  return true;
}

bool Lexer::getNextToken(Token & token)
{
  char c, d, e, f;
  bool there = getNextChar(c);
  if (!there)
    return false;
  string result;
  // ignore space
  while (isspace(c)) {
    there = getNextChar(c);
    if (!there)
      return false;      
  }
  // a number
  if (isdigit(c) || 
      (c=='.' && peekChar(d) && isdigit(d))) {
    bool hasDot = (c=='.');
    result += c;
    if (!hasDot) {
      while (peekChar(d) && isdigit(d)) {
        getNextChar(c);
        result += c;
      }
      if (peekChar(d) && d=='.') {
        hasDot = true;
        getNextChar(c);
        result += c;
      }
    }
    if (hasDot) {
      while (peekChar(d) && isdigit(d)) {
        getNextChar(c);
        result += c;
      }        
    }
    bool hasExponent = false;
    if (peekChar(d) && (d=='e'||d=='E') && peekChar(e, 2) && 
        (isdigit(e) || ((e=='+'||e=='-') && peekChar(f, 3) && isdigit(f)))) {
      hasExponent = true;
      getNextChar(c);
      result += c;
      getNextChar(c);
      result += c; 
      while (peekChar(d) && isdigit(d)) {
        getNextChar(c);
        result += c;
      }       
    }
    if (hasDot || hasExponent) {
      stringstream istr(result);
      double fval;
      istr >> fval;
      token = Token(fval);
    } else {
      stringstream istr(result);
      int64_t ival;
      istr >> ival;
      token = Token(ival);
    }
  }
  // identifier
  else if (isalpha(c)) {
    result += c;
    while (peekChar(d) && isalnum(d)) {
      getNextChar(c);
      result += c;
    }
    token = Token(result);
  }
  // char
  else {
    token = Token(c);
  } 
  return true;
}



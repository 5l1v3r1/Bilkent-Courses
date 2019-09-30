#pragma once

#include "Lexer.h"

class BinaryExpression;
class Expression;
class Statement;

class Parser
{
public:
  Parser(Lexer & lexer);
  Statement * parse();
private:
  Statement * parse_stmt();
  Statement * parse_assign_stmt();
  Statement * parse_expr_stmt();
  Expression * parse_expr();
  Expression * parse_term_tail(Expression * leftExpr);
  Expression * parse_term();
  Expression * parse_factor_tail(Expression * leftExpr);
  Expression * parse_factor();
  Expression * parse_primary();
  Token const * peekToken(int i=1);
  void eatToken();
private:
  static const int tokenBufferSize_ = 10;
  Lexer & lexer_;
  Token tokenBuffer_[tokenBufferSize_];
  int bufferPos_;
  int numBufferedTokens_;

};

/*
01. expr         -> term term_tail
02. term_tail    -> ('+'|'-') term term_tail
03. term_tail    -> epsilon
04. term         -> factor factor_tail
05. factor_tail  -> ('*'|'/') factor factor_tail
06. factor_tail  -> epsilon
07. factor       -> '-' factor
08. factor       -> primary
09. primary      -> '(' expr ')'
10. primary      -> id 
11. primary      -> float
12. primary      -> integer

expr:
  PREDICT(01) = '-', '(', id, float, integer
term_tail:
  PREDICT(02) = '+', '-' 
  PREDICT(03) = $, ')'
term:
  PREDICT(04) = '-', '(', id, float, integer
factor_tail
  PREDICT(05) = '*', '/' 
  PREDICT(06) = '+', '-', $, ')'
factor:
  PREDICT(07) = '-', 
  PREDICT(08) = '(', id, float, integer
primary:
  PREDICT(09) = '('
  PREDICT(10) = id
  PREDICT(11) = float
  PREDICT(12) = integer
*/



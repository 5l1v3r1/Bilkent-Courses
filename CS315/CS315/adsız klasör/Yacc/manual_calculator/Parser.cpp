#include "Parser.h"

#include "Lexer.h"
#include "Expression.h"
#include "Statement.h"

#include <stdexcept>
#include <cassert>
#include <memory>

using namespace std;

Parser::Parser(Lexer & lexer)
  : lexer_(lexer), bufferPos_(0), numBufferedTokens_(0)
{}

void Parser::eatToken()
{
  if (numBufferedTokens_==0) {
    bool there = lexer_.getNextToken(tokenBuffer_[bufferPos_]);
    assert(there);
  } else {
    bufferPos_ = (bufferPos_+1) % tokenBufferSize_; 
    numBufferedTokens_--;
  }
}

Token const * Parser::peekToken(int i)
{
  assert(i>0);
  if (i>numBufferedTokens_) {
    int nextPos = (bufferPos_+numBufferedTokens_) % tokenBufferSize_;
    while (i>numBufferedTokens_) {
      bool there = lexer_.getNextToken(tokenBuffer_[nextPos]);
      if (!there)
        return NULL;
      nextPos = (nextPos+1) % tokenBufferSize_; 
      numBufferedTokens_++;
    }
  }
  int pos = (bufferPos_ + i - 1) % tokenBufferSize_;
  return & tokenBuffer_[pos];
}

Statement * Parser::parse()
{
  auto_ptr<Statement> stmt(parse_stmt());
  if (peekToken()!=NULL)
    throw std::runtime_error("parsing error");
  return stmt.release();
}

Statement * Parser::parse_stmt()
{
  Token const * token = peekToken(1);
  if (token!=0 && token->getTokenType()==Token::TT_IDENTIFIER) {
      token = peekToken(2);   
      if (token!=0 && token->getTokenType()==Token::TT_CHAR
          && token->getCharValue() =='=') 
        return parse_assign_stmt();
  } 
  return parse_expr_stmt();
}

Statement * Parser::parse_assign_stmt()
{
  Token const * token = peekToken();
  if (token!=0 && token->getTokenType()==Token::TT_IDENTIFIER) {
    string const & id = token->getStringValue();
    eatToken();
    token = peekToken();
    if (token!=0 && token->getTokenType()==Token::TT_CHAR &&
        token->getCharValue() == '=') {
      eatToken();
      Expression * expr = parse_expr();
      return new AssignmentStatement(id, expr);
    }
  }
  throw std::runtime_error("parsing error");
  return NULL;
}

Statement * Parser::parse_expr_stmt()
{
  Expression * expr = parse_expr();
  return new ExpressionStatement(expr);
}

Expression * Parser::parse_expr()
{
  Expression * leftExpr = parse_term();
  return parse_term_tail(leftExpr);
}

Expression * Parser::parse_term_tail(Expression * leftExpr)
{
  Token const * token = peekToken();
  if (token!=0 && token->getTokenType()==Token::TT_CHAR) {
    char c = token->getCharValue();
    if (c=='+' || c=='-') {
      eatToken();
      Expression * rightExpr = parse_term();
      Expression * topExpr = new BinaryExpression(BinaryExpression::getOperatorKind(c), leftExpr, rightExpr);
      return parse_term_tail(topExpr);
    }
  }
  return leftExpr; 
}

Expression * Parser::parse_term()
{
  Expression * leftExpr = parse_factor();
  return parse_factor_tail(leftExpr);
}

Expression * Parser::parse_factor_tail(Expression * leftExpr)
{
  Token const * token = peekToken();
  if (token!=0 && token->getTokenType()==Token::TT_CHAR) {
    char c = token->getCharValue();
    if (c=='*' || c=='/') {
      eatToken();
      Expression * rightExpr = parse_factor();
      BinaryExpression * topExpr = new BinaryExpression(BinaryExpression::getOperatorKind(c), leftExpr, rightExpr);
      return parse_factor_tail(topExpr);
    }
  } 
  return leftExpr;
}

Expression * Parser::parse_factor()
{
  Token const * token = peekToken();
  if (token!=0 && token->getTokenType()==Token::TT_CHAR) {
    char c = token->getCharValue();
    if (c=='-') {
      eatToken();
      Expression * expr = parse_factor();
      return new UnaryExpression(UnaryExpression::getOperatorKind(c), expr);
    }
  }
  return parse_primary();
}

Expression * Parser::parse_primary()
{
  Token const * token = peekToken();
  if (token) {
    if (token->getTokenType()==Token::TT_CHAR) {
      char c = token->getCharValue();
      if (c=='(') {
        eatToken();
        auto_ptr<Expression> expr(parse_expr());
        token = peekToken();
        if (token->getTokenType()==Token::TT_CHAR && token->getCharValue() == ')') {
          eatToken();
          return new UnaryExpression(UnaryExpression::getOperatorKind(c), expr.release());  
        }      
      }
    } else if (token->getTokenType()==Token::TT_IDENTIFIER) {
      auto_ptr<Expression> expr(new IdentifierExpression(token->getStringValue()));
      eatToken();
      return expr.release();
    } else if (token->getTokenType()==Token::TT_INTEGER) {
      auto_ptr<Expression> expr(new IntegerLiteralExpression(token->getIntegerValue()));
      eatToken();
      return expr.release();
    } else if (token->getTokenType()==Token::TT_FLOAT) {
      auto_ptr<Expression> expr(new FloatLiteralExpression(token->getFloatValue()));
      eatToken();
      return expr.release();
    }    
  }
  throw std::runtime_error("parsing error");
  return NULL;
}



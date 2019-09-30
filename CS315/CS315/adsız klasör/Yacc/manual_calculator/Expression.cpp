#include "Indenter.h"
#include "Expression.h"
#include <cassert>

using namespace std;

IdentifierExpression::IdentifierExpression(string const & id) 
  : id_(id) 
{}

string const & IdentifierExpression::getIdentifier() const 
{ 
  return id_; 
}

IntegerLiteralExpression::IntegerLiteralExpression(int64_t value) 
  : value_(value) 
{}

int64_t IntegerLiteralExpression::getValue() const 
{ 
  return value_; 
}

FloatLiteralExpression::FloatLiteralExpression(double value) 
  : value_(value) 
{}

double FloatLiteralExpression::getValue() const 
{ 
  return value_; 
}

UnaryExpression::UnaryExpression(Kind kind, Expression * expr)
  : kind_(kind), expr_(expr) 
{}

UnaryExpression::~UnaryExpression() 
{
  delete expr_;
}

UnaryExpression::Kind UnaryExpression::getKind() const 
{ 
  return kind_; 
}

char const * UnaryExpression::getKindString() const
{
  switch(kind_) {
  case Minus:
    return "-";
  case Paranthesis:
    return "()";
  default:
    assert("!cannot happen");
  }
}

Expression const & UnaryExpression::getExpression() const 
{
  return *expr_; 
} 

UnaryExpression::Kind UnaryExpression::getOperatorKind(char c) 
{
  switch (c) {
  case '-':
    return Minus;
  case '(':
    return Paranthesis;
  default:
    assert(!"cannot happen");
  }
}

BinaryExpression::BinaryExpression(Kind kind, Expression * left, Expression * right) 
  : kind_(kind), left_(left), right_(right) 
{}

BinaryExpression::~BinaryExpression() 
{
  delete left_;
  delete right_;
}

BinaryExpression::Kind BinaryExpression::getKind() const 
{
  return kind_; 
}

char const * BinaryExpression::getKindString() const
{
  switch(kind_) {
  case Plus:
    return "+";
  case Minus:
    return "-";
  case Times:
    return "*";
  case Divide:
    return "/";
  default:
    assert("!cannot happen");
  }
}

Expression const & BinaryExpression::getLeftExpression() const 
{
  return *left_; 
} 

Expression const & BinaryExpression::getRightExpression() const 
{ 
  return *right_; 
} 

void BinaryExpression::setLeftExpression(Expression * expr) 
{
  delete left_;
  left_ = expr;
}

void BinaryExpression::setRightExpression(Expression * expr) 
{
  delete right_;
  right_ = expr;
}

BinaryExpression::Kind BinaryExpression::getOperatorKind(char c) 
{
  switch (c) {
  case '+':
    return Plus;
  case '-':
    return Minus;
  case '*':
    return Times;
  case '/':
    return Divide;
  default:
    assert(!"cannot happen");
  }
}

void IdentifierExpression::print(ostream & ostr, int level)
{
  ostr << indent(level) << "(id " << id_ << ")";
}

void IdentifierExpression::prettyPrint(ostream & ostr)
{
  ostr << id_;
}

void IntegerLiteralExpression::print(ostream & ostr, int level)
{
  ostr << indent(level) << "(int " << value_ << ")";
}

void IntegerLiteralExpression::prettyPrint(ostream & ostr)
{
  ostr << value_;
}

void FloatLiteralExpression::print(ostream & ostr, int level)
{
  ostr << indent(level) << "(float " << value_ << ")";
}

void FloatLiteralExpression::prettyPrint(ostream & ostr)
{
  ostr << value_;
}


void UnaryExpression::print(ostream & ostr, int level)
{
  ostr << indent(level) << "(uexp op:" << getKindString() << "\n";
  expr_->print(ostr, level+1);
  ostr << "\n";
  ostr << indent(level) << ")";
}

void UnaryExpression::prettyPrint(ostream & ostr)
{
  string kstr = getKindString();
  if (kind_==Paranthesis) {
    ostr << kstr[0];
    expr_->prettyPrint(ostr);
    ostr << kstr[1];
  } else if (kind_==Minus) {
    ostr << kstr;    
    expr_->prettyPrint(ostr);
  }
}

void BinaryExpression::print(ostream & ostr, int level)
{
  ostr << indent(level) << "(binary_expression op:" << getKindString() << "\n";
  left_->print(ostr, level+1);
  ostr << "\n";
  right_->print(ostr, level+1);
  ostr << "\n";
  ostr << indent(level) << ")";
}

void BinaryExpression::prettyPrint(ostream & ostr)
{
  left_->prettyPrint(ostr);
  ostr << getKindString();
  right_->prettyPrint(ostr);
}


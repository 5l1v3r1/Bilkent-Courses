#pragma once

#include <iostream>
#include <vector>
#include <inttypes.h>

class Expression
{
public:
  virtual ~Expression() {}
  virtual void print(std::ostream & ostr, int level) = 0;
  virtual void prettyPrint(std::ostream & ostr) = 0;
};

class IdentifierExpression : public Expression
{
public:
  IdentifierExpression(std::string const & id);
  std::string const & getIdentifier() const;
  void print(std::ostream & ostr, int level);
  void prettyPrint(std::ostream & ostr);
private:
  std::string id_;
};

class IntegerLiteralExpression : public Expression
{
public:
  IntegerLiteralExpression(int64_t value);
  int64_t getValue() const;
  void print(std::ostream & ostr, int level);
  void prettyPrint(std::ostream & ostr);
private:
  int64_t value_;
};

class FloatLiteralExpression : public Expression
{
public:
  FloatLiteralExpression(double value);
  double getValue() const;
  void print(std::ostream & ostr, int level);
  void prettyPrint(std::ostream & ostr);
private:
  double value_;
};

class UnaryExpression : public Expression
{
public:
  enum Kind { Minus, Paranthesis };
  UnaryExpression (Kind kind, Expression * expr);
  ~UnaryExpression();
  Kind getKind() const;
  static Kind getOperatorKind(char c);
  char const * getKindString() const;
  Expression const & getExpression() const;
  void print(std::ostream & ostr, int level);
  void prettyPrint(std::ostream & ostr);
private:
  Kind kind_;
  Expression * expr_;
};

class BinaryExpression : public Expression
{
public:
  enum Kind { Plus, Minus, Times, Divide };
  BinaryExpression(Kind kind, Expression * left, Expression * right); 
  ~BinaryExpression();
  Kind getKind() const;
  static Kind getOperatorKind(char c);
  char const * getKindString() const;
  void setLeftExpression(Expression * expr);
  void setRightExpression(Expression * expr);
  Expression const & getLeftExpression() const;
  Expression const & getRightExpression() const;
  void print(std::ostream & ostr, int level);
  void prettyPrint(std::ostream & ostr);
private:
  Kind kind_;
  Expression * left_;
  Expression * right_;
};



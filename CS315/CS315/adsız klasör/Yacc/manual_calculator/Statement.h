#pragma once

#include <iostream>
#include <vector>

class Expression;

class Statement
{
public:
  virtual ~Statement() {}
  virtual void print(std::ostream & ostr, int level) = 0;
  virtual void prettyPrint(std::ostream & ostr) = 0;
};

class AssignmentStatement : public Statement
{
public:
  AssignmentStatement(std::string const & id, Expression * expr);
  std::string const & getIdentifier() const;
  Expression const & getExpression() const;
  void print(std::ostream & ostr, int level);
  void prettyPrint(std::ostream & ostr);
private:  
  std::string id_;
  Expression * expr_;
};

class ExpressionStatement : public Statement
{
public:
  ExpressionStatement(Expression * expr);
  Expression const & getExpression() const;
  void print(std::ostream & ostr, int level);
  void prettyPrint(std::ostream & ostr);
private:
  Expression * expr_;
};



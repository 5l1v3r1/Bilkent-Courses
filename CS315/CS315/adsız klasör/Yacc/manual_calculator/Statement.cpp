#include "Indenter.h"
#include "Statement.h"
#include "Expression.h"
#include <cassert>

using namespace std;

AssignmentStatement::AssignmentStatement(string const & id, Expression * expr)
  : id_(id), expr_(expr)
{}

std::string const & AssignmentStatement::getIdentifier() const
{
  return id_;
}
 
Expression const & AssignmentStatement::getExpression() const
{
  return *expr_;
}

ExpressionStatement::ExpressionStatement(Expression * expr)
  : expr_(expr)
{}

Expression const & ExpressionStatement::getExpression() const
{
  return *expr_;
}


void AssignmentStatement::print(ostream & ostr, int level)
{
  ostr << indent(level) << "(assgn " << id_ << "\n";
  expr_->print(ostr, level+1);
  ostr << "\n";
  ostr << indent(level) << ")";
}

void AssignmentStatement::prettyPrint(ostream & ostr)
{
  ostr << id_ << " = ";
  expr_->prettyPrint(ostr);
  ostr << "\n";
}


void ExpressionStatement::print(ostream & ostr, int level)
{
  ostr << indent(level) << "(expr \n";
  expr_->print(ostr, level+1);
  ostr << "\n";
  ostr << indent(level) << ")";
}

void ExpressionStatement::prettyPrint(ostream & ostr)
{
  expr_->prettyPrint(ostr);
  ostr << "\n";
}


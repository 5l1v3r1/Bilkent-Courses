#include "Lexer.h"
#include "Parser.h"
#include "Expression.h"
#include "Statement.h"
#include "Numeric.h"

#include <cstdlib>
#include <iostream>
#include <sstream>
#include <cassert>
#include <tr1/unordered_map>

using namespace std;
using namespace std::tr1;

unordered_map<string, Numeric> variables;

static Numeric evaluate(Expression const * expr)
{
  {
    BinaryExpression const * bexpr = dynamic_cast<BinaryExpression const *>(expr);
    if (bexpr!=0) {
      Expression const * left = &bexpr->getLeftExpression();
      Expression const * right = &bexpr->getRightExpression();
      Numeric leftRes = evaluate(left);
      Numeric rightRes = evaluate(right);
      switch (bexpr->getKind())
      {
      case BinaryExpression::Plus:
        return leftRes + rightRes;
      case BinaryExpression::Minus:
        return leftRes - rightRes;
      case BinaryExpression::Times:
        return leftRes * rightRes;
      case BinaryExpression::Divide:
        return leftRes / rightRes;
      }
    }
  }
  {
    UnaryExpression const * uexpr = dynamic_cast<UnaryExpression const *>(expr);
    if (uexpr!=0) {
      if (uexpr->getKind()==UnaryExpression::Minus)
        return -evaluate(&uexpr->getExpression());
      else // paranthesis
        return evaluate(&uexpr->getExpression());
    }
  }
  {
    FloatLiteralExpression const * fexpr = dynamic_cast<FloatLiteralExpression const *>(expr);
    if (fexpr!=0)  
      return Numeric(fexpr->getValue());
  }
  {
    IntegerLiteralExpression const * iexpr = dynamic_cast<IntegerLiteralExpression const *>(expr);
    if (iexpr!=0) 
      return Numeric(iexpr->getValue());
  }
  {
    IdentifierExpression const * iexpr = dynamic_cast<IdentifierExpression const *>(expr);
    if (iexpr!=0) {
      string const & id = iexpr->getIdentifier();
      if (variables.count(id)==0) 
        return Numeric(int64_t(0));
      else
        return variables[id];
    }
  }
  assert(!"cannot happen");
}

static Statement * parse(string const & line)    
{
  stringstream str(line);
  Lexer lexer(str);
  char c;
  if (!lexer.peekChar(c))
    return 0;
  Parser parser(lexer);
  return parser.parse();
}

int main()
{
  string line;
  while (true) {
    std::getline(cin, line);
    Statement * stmt;
    try {
      stmt = parse(line);
    } catch(exception const & e) {
      cerr << e.what() << endl;
      continue;
    }
    if (stmt==0) // empty line
      continue;
    AssignmentStatement * assgn = dynamic_cast<AssignmentStatement *>(stmt);
    if (assgn!=0) {
      string const & id = assgn->getIdentifier();
      Expression const * expr = &assgn->getExpression();
      variables[id] = evaluate(expr);
    } else {
      ExpressionStatement * exprStmt =  dynamic_cast<ExpressionStatement *>(stmt);
      Expression const * expr = &exprStmt->getExpression();
      Numeric result = evaluate(expr);     
      cout << result << endl;
    }
  }
  return EXIT_SUCCESS;
}

/*
  try {
    test("x*y+z");
    test("x+y*z");
    test("(x+y)*z");
    test("x-y-z");
    test("-x-y-z");
  } catch(exception const & e) {
    cerr << e.what() << endl;
  }
*/



#include "Expression.h"
#include <cassert>

using namespace std;

struct Indenter
{
  int level;
};

static Indenter indent(int level)
{
  Indenter indenter;
  indenter.level = level;
  return indenter;
}

ostream & operator << (ostream & ostr, Indenter const & indenter)
{
  for (int i=0; i<indenter.level; ++i)
    ostr << "  ";
  return ostr;
}

static string toLiteral(char c)
{
  switch (c){
    case '\n':
      return "\\n";
    case '\t':
      return "\\t";
    case '\r':
      return "\\r";
    case '.':
    case '*':
    case '+':
    case '?':
    case '|':
    case '^':
    case '$':
    case '\\':
    case '-':
    case '(':
    case ')':
    case '[':
    case ']':
      return string("\\") + c;
    default:
      return string(1, c);
  }     
  return string(1, c);
}

static string toLiteral(string const & str)
{
  string result;
  for (int i=0, iu=str.size(); i<iu; ++i) {
    char c = str[i];
    result += toLiteral(c);
  }
  return result;
}

void CharacterSequence::print(ostream & ostr, int level)
{
  ostr << indent(level) << "(character_sequnce " << toLiteral(sequence_) << ")";
}

void CharacterSequence::prettyPrint(ostream & ostr)
{
  ostr << toLiteral(sequence_);
}

void CharacterRange::print(ostream & ostr, int level)
{
  ostr << indent(level) << "(character_range " << toLiteral(characterStart_) << " " << toLiteral(characterEnd_) << ")";
}

void CharacterRange::prettyPrint(ostream & ostr)
{
  ostr << toLiteral(characterStart_) << "-" << toLiteral(characterEnd_);
}

void CharacterGroup::print(ostream & ostr, int level)
{
  ostr << indent(level) << "(character_group inverted:" << (inverted_?"true":"false") << "\n";
  for (int i=0, iu=sequenceOrRanges_.size(); i<iu; ++i) {
    sequenceOrRanges_[i]->print(ostr, level+1);
    ostr << "\n";
  }
  ostr << indent(level) << ")";
}

void CharacterGroup::prettyPrint(ostream & ostr)
{
  ostr << "[";
  if (inverted_)
    ostr << "^";
  for (int i=0, iu=sequenceOrRanges_.size(); i<iu; ++i)
    sequenceOrRanges_[i]->prettyPrint(ostr);
  ostr << "]";
}

void UnaryExpression::print(ostream & ostr, int level)
{
  ostr << indent(level) << "(unary_expression op:" << getKindString() << "\n";
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
  } else if (kind_==Caret) {
    ostr << kstr;    
    expr_->prettyPrint(ostr);
  } else {
    expr_->prettyPrint(ostr);
    ostr << kstr;
  }
}

char const * UnaryExpression::getKindString() const
{
  switch(kind_) {
  case KleeneStar:
    return "*";
  case OneOrMore:
    return "+";
  case ZeroOrOne:
    return "?";
  case Caret:
    return "^";
  case Dollar:
    return "$";
  case Paranthesis:
    return "()";
  default:
    assert("!cannot happen");
  }
}

void BinaryExpression::print(ostream & ostr, int level)
{
  ostr << indent(level) << "(binary_expression op:" << getKindString() << "\n";
  for (size_t i=0, iu=exprs_.size(); i<iu; ++i) {
    exprs_[i]->print(ostr, level+1);
    ostr << "\n";
  }
  ostr << indent(level) << ")";
}

void BinaryExpression::prettyPrint(ostream & ostr)
{
  exprs_[0]->prettyPrint(ostr);
  for (size_t i=1, iu=exprs_.size(); i<iu; ++i) {
    ostr << getKindString();
    exprs_[i]->prettyPrint(ostr);
  }
}

char const * BinaryExpression::getKindString() const
{
  switch(kind_) {
  case Concatenation:
    return "";
  case Alternation:
    return "|";
  default:
    assert("!cannot happen");
  }
}

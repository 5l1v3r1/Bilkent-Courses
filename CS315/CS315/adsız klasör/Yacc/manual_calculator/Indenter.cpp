#include "Indenter.h"

using namespace std;

Indenter indent(int level)
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



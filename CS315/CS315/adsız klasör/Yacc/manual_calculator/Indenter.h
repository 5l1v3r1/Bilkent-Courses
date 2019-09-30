#pragma once

#include <iostream>

struct Indenter
{
  int level;
};

Indenter indent(int level);
std::ostream & operator << (std::ostream & ostr, Indenter const & indenter);



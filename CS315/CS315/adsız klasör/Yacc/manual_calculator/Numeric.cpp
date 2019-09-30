#include "Numeric.h"

using namespace std;

Numeric operator+(Numeric lhs, Numeric rhs)
{
  if (lhs.isInteger()) {
    if (rhs.isInteger()) 
      return Numeric(lhs.getIntegerValue()+rhs.getIntegerValue());
    else 
      return Numeric(lhs.getIntegerValue()+rhs.getFloatValue());
  } else {
    if (rhs.isInteger()) 
      return Numeric(lhs.getFloatValue()+rhs.getIntegerValue());
    else 
      return Numeric(lhs.getFloatValue()+rhs.getFloatValue());
  }
}
Numeric operator-(Numeric lhs, Numeric rhs)
{
  if (lhs.isInteger()) {
    if (rhs.isInteger()) 
      return Numeric(lhs.getIntegerValue()-rhs.getIntegerValue());
    else 
      return Numeric(lhs.getIntegerValue()-rhs.getFloatValue());
  } else {
    if (rhs.isInteger()) 
      return Numeric(lhs.getFloatValue()-rhs.getIntegerValue());
    else 
      return Numeric(lhs.getFloatValue()-rhs.getFloatValue());
  }
}
Numeric operator*(Numeric lhs, Numeric rhs)
{
  if (lhs.isInteger()) {
    if (rhs.isInteger()) 
      return Numeric(lhs.getIntegerValue()*rhs.getIntegerValue());
    else 
      return Numeric(lhs.getIntegerValue()*rhs.getFloatValue());
  } else {
    if (rhs.isInteger()) 
      return Numeric(lhs.getFloatValue()*rhs.getIntegerValue());
    else 
      return Numeric(lhs.getFloatValue()*rhs.getFloatValue());
  }
}
Numeric operator/(Numeric lhs, Numeric rhs)
{
  if (lhs.isInteger()) {
    if (rhs.isInteger()) 
      return Numeric(lhs.getIntegerValue()/rhs.getIntegerValue());
    else 
      return Numeric(lhs.getIntegerValue()/rhs.getFloatValue());
  } else {
    if (rhs.isInteger()) 
      return Numeric(lhs.getFloatValue()/rhs.getIntegerValue());
    else 
      return Numeric(lhs.getFloatValue()/rhs.getFloatValue());
  }
}

ostream & operator<<(ostream & ostr, Numeric num)
{
  if (num.isInteger())
    ostr << num.getIntegerValue();
  else 
    ostr << num.getFloatValue();
  return ostr;
}

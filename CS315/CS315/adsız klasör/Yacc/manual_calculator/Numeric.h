#pragma once

#include <iostream>
#include <inttypes.h>

class Numeric
{
public:
  Numeric()
    : isInt_(true)
  {}
  Numeric(double value) 
    : isInt_(false)
  {
    value_.floatValue_ = value;
  }
  Numeric(int64_t value) 
    : isInt_(true)
  {
    value_.intValue_ = value;
  }
  bool isInteger() const
  {
    return isInt_;
  }
  bool isFloat() const
  {
    return !isInt_;
  }
  int64_t getIntegerValue() const 
  {
    return value_.intValue_;
  }
  double getFloatValue() const 
  {
    return value_.floatValue_;
  }
  Numeric operator-()
  {
    if (isInt_)
      return Numeric(-value_.intValue_);
    else
      return Numeric(-value_.floatValue_);
  }
private:
  bool isInt_;
  union {
    int64_t intValue_;
    double floatValue_;
  } value_;
};

Numeric operator+(Numeric lhs, Numeric rhs);
Numeric operator-(Numeric lhs, Numeric rhs);
Numeric operator*(Numeric lhs, Numeric rhs);
Numeric operator/(Numeric lhs, Numeric rhs);

std::ostream & operator<<(std::ostream & ostr, Numeric num);

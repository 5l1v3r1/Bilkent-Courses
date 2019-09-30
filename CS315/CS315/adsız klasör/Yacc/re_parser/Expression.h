#pragma once

#include <iostream>
#include <vector>

class Expression
{
public:
  virtual ~Expression() {}
  virtual void print(std::ostream & ostr, int level) = 0;
  virtual void prettyPrint(std::ostream & ostr) = 0;
};

class CharacterSequence: public Expression
{
public:
  CharacterSequence() {}
  CharacterSequence(char character) { addCharacter(character); }
  void addCharacter(char character) { sequence_ += character; }
  void addCharacters(std::string const & characters) { sequence_ += characters; }
  std::string const & getCharacters() const { return sequence_; }
  void print(std::ostream & ostr, int level);
  void prettyPrint(std::ostream & ostr);
private:
  std::string sequence_;
};

class CharacterRange : public Expression
{
public:
  CharacterRange(char characterStart, char characterEnd)
    : characterStart_(characterStart), 
      characterEnd_(characterEnd) {}
  char getRangeStartCharacter() const { return characterStart_; }
  char getRangeEndCharacter() const { return characterEnd_; }
  void print(std::ostream & ostr, int level);
  void prettyPrint(std::ostream & ostr);
private:
  char characterStart_;
  char characterEnd_;
};

class CharacterGroup : public Expression
{
public:
  CharacterGroup() :
    inverted_(false) {}
  ~CharacterGroup() {
    for (int i, iu=sequenceOrRanges_.size(); i<iu; ++i)
      delete sequenceOrRanges_[i];
  }
  void setInverted(bool inverted) { inverted_ = inverted; }
  bool isInverted() const { return inverted_; }
  std::vector<Expression *> const & getCharacterSequencesAndRanges()  const { return sequenceOrRanges_; }
  void addCharacterSequence(CharacterSequence * sequence) { sequenceOrRanges_.push_back(sequence); }
  void addCharacterRange(CharacterRange * range) { sequenceOrRanges_.push_back(range); }
  Expression & getLastSequenceOrRange() { return **sequenceOrRanges_.rbegin(); }
  void print(std::ostream & ostr, int level);
  void prettyPrint(std::ostream & ostr);
private:
  bool inverted_;
  std::vector<Expression *> sequenceOrRanges_;
};

class UnaryExpression : public Expression
{
public:
  enum Kind { KleeneStar, OneOrMore, ZeroOrOne, Caret, Dollar, Paranthesis };
  UnaryExpression (Kind kind, Expression * expr)
    : kind_(kind), expr_(expr) {}
  ~UnaryExpression() {
    delete expr_;
  }
  Kind getKind() const { return kind_; }
  char const * getKindString() const;
  Expression const & getExpression() const { return *expr_; } 
  void print(std::ostream & ostr, int level);
  void prettyPrint(std::ostream & ostr);
private:
  Expression * expr_;
  Kind kind_;
};

class BinaryExpression : public Expression
{
public:
  enum Kind { Concatenation, Alternation };
  BinaryExpression (Kind kind, Expression * left, Expression * right) 
      : kind_(kind) { 
    exprs_.push_back(left);
    exprs_.push_back(right);
  }
  ~BinaryExpression() {
    for (size_t i=0, iu=exprs_.size(); i<iu; ++i)
      delete exprs_[i];
  }
  Kind getKind() const { return kind_; }
  char const * getKindString() const;
  void addExpression(Expression * expr) { exprs_.push_back(expr); }
  Expression const & getLeftExpression() const { return *exprs_[0]; } 
  Expression const & getRightExpression() const { return *exprs_[1]; } 
  std::vector<Expression *> const & getExpressions() const { return exprs_; }
  void print(std::ostream & ostr, int level);
  void prettyPrint(std::ostream & ostr);
private:
  std::vector<Expression *> exprs_;
  Kind kind_;
};



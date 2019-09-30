// Define the tokens

%{
#include "Expression.h"
#include <cassert>
%}

%token KLEENE_STAR
%token ONE_OR_MORE
%token ZERO_OR_ONE
%token ALTERNATION
%token CONCATENATION
%token OPEN_BRACKET
%token CLOSE_BRACKET
%token OPEN_PARAN
%token CLOSE_PARAN
%token CARET
%token DOLLAR
%token DASH
%token CHAR
%token ERROR_CHAR

%union 
{
  char char_val;
  int int_val;
  struct Expression * exp_val;
}

%type <char_val> CHAR 
%type <exp_val> regex factor term exp in_bracket_exp
%type <int_val> repetition_op

%{
  #include <iostream> 
  using namespace std;
  // forward declarations
  void yyerror(char const *);
  int yylex(void);
  static BinaryExpression::Kind getBinaryExpressionKind(int kind);
  static UnaryExpression::Kind getUnaryExpressionKind(int kind);
%}

%%

program:
  program regex '\n'
    {
      Expression * exp = $2;
      cout << "TREE FORM:\n";
      exp->print(cout, 0);
      cout << endl;
      cout << "PRETTY PRINT:\n";
      exp->prettyPrint(cout);
      cout << endl;
    }
  | program error '\n'
  | 
  ;

regex:
    regex ALTERNATION factor
    {
      BinaryExpression::Kind kind = BinaryExpression::Alternation;
      BinaryExpression * left = dynamic_cast<BinaryExpression *>($1);
      if (left!=0 && left->getKind()==kind) {
        left->addExpression($3);
        $$ = left;
      } else {
        BinaryExpression * exp = new BinaryExpression(kind, $1, $3);
        $$ = exp;
      }
    }
  | factor
  ;

factor:
    factor term 
    {
      CharacterSequence * cseqLeft = dynamic_cast<CharacterSequence *>($1);
      CharacterSequence * cseqRight = dynamic_cast<CharacterSequence *>($2);
      if (cseqLeft!=0 && cseqRight!=0) {
        cseqLeft->addCharacters(cseqRight->getCharacters());
        $$ = cseqLeft;
      } else {      
        BinaryExpression::Kind kind = BinaryExpression::Concatenation;
        BinaryExpression * left = dynamic_cast<BinaryExpression *>($1);
        if (left!=0 && left->getKind()==kind) {
          left->addExpression($2);
          $$ = left;
        } else {        
          BinaryExpression * exp = new BinaryExpression(kind, $1, $2);
          $$ = exp;
        }
      }
    }
  | term
  ;

term:
    term repetition_op
    {
      UnaryExpression::Kind kind = getUnaryExpressionKind($2);
      UnaryExpression * exp = new UnaryExpression(kind, $1);
      $$ = exp;
    }
  | exp           
  ;

repetition_op: 
    KLEENE_STAR   
    { $$ = KLEENE_STAR; }
  | ONE_OR_MORE   
    { $$ = ONE_OR_MORE; }
  | ZERO_OR_ONE  
    { $$ = ZERO_OR_ONE; }

exp:
    CHAR
    { 
      CharacterSequence * cseq = new CharacterSequence($1);
      $$ = cseq;
    }
  | OPEN_PARAN regex CLOSE_PARAN
    {
      UnaryExpression::Kind kind = getUnaryExpressionKind(OPEN_PARAN);
      UnaryExpression * exp = new UnaryExpression(kind, $2);
      $$ = exp;
    }
  | OPEN_BRACKET in_bracket_exp CLOSE_BRACKET
    {
      $$ = $2;
    }
  | OPEN_BRACKET CARET in_bracket_exp CLOSE_BRACKET
    {
      CharacterGroup * group = static_cast<CharacterGroup *>($3);
      group->setInverted(true);
      $$ = $3;
    }
  ;

in_bracket_exp:
    CHAR                 
    { 
      CharacterGroup * group = new CharacterGroup();
      CharacterSequence * cseq = new CharacterSequence($1);
      group->addCharacterSequence(cseq);
      $$ = group;
    }
  | CHAR DASH CHAR       
    { 
      CharacterGroup * group = new CharacterGroup();
      CharacterRange * crange = new CharacterRange($1, $3);
      group->addCharacterRange(crange);
      $$ = group;
    }
  | in_bracket_exp CHAR  
    { 
      CharacterGroup * group = static_cast<CharacterGroup *>($1);
      Expression * last = & group->getLastSequenceOrRange();
      CharacterSequence * cseq = dynamic_cast<CharacterSequence*>(last);
      if (cseq!=0) {
        cseq->addCharacter($2);
      } else {
        cseq = new CharacterSequence($2);
        group->addCharacterSequence(cseq);
      }
      $$ = group;
    }
  | in_bracket_exp CHAR DASH CHAR
    { 
      CharacterGroup * group = static_cast<CharacterGroup *>($1);
      CharacterRange * crange = new CharacterRange($2, $4);
      group->addCharacterRange(crange);
      $$ = group;
    }
  ;

%%

BinaryExpression::Kind getBinaryExpressionKind(int kind)
{
  switch(kind)
  {
  case ALTERNATION:
    return BinaryExpression::Alternation;
  case CONCATENATION:
    return BinaryExpression::Concatenation;
  default:
    assert(!"cannot happen");
  }
}

UnaryExpression::Kind getUnaryExpressionKind(int kind)
{
  switch(kind)
  {
  case KLEENE_STAR:
    return UnaryExpression::KleeneStar;
  case ONE_OR_MORE:
    return UnaryExpression::OneOrMore;
  case ZERO_OR_ONE:
    return UnaryExpression::ZeroOrOne;
  case CARET:
    return UnaryExpression::Caret;
  case DOLLAR:
    return UnaryExpression::Dollar;
  case OPEN_PARAN:
    return UnaryExpression::Paranthesis;
  case CLOSE_PARAN:   
    return UnaryExpression::Paranthesis;
  default:
    assert(!"cannot happen");
  }
}


// report errors

void yyerror(char const *s) 
{
  cerr << s << endl;
}


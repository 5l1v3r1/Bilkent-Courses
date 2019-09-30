// Declare the tokens

%token INTEGER 
%token VARIABLE
%token ERROR_CHAR 

// Define the union that can hold different values for the tokens
 
%union 
{
  char * string;
  int integer;
}

// Define the token value types

%type <integer> INTEGER 
%type <string> VARIABLE
%type <integer> expr


// define associativity and precedence of operations

%left '+' '-' // the order defines precedence, 
%left '*' '/' // so * and / has higher precedence than + and -
// % left means left associative 
%nonassoc NEG  // negation--unary minus has the highest precedence, and is non-associative


%{
  #include <unordered_map> 
  #include <iostream> 
  using namespace std;
  // forward declarations
  void yyerror(char *);
  int yylex(void);
  // symbol table to hold variable values
  unordered_map<string, int> symbols;
%}

%%

program :
    program statement '\n' 
  | statement '\n' 
  | error '\n'
  ;

statement:
    expr               { cout << $1 << endl; }
  | VARIABLE '=' expr  { symbols[string($1)] = $3; }
  ;

expr:
    INTEGER            { $$ = $1; }
  | VARIABLE           { $$ = symbols.count(string($1)) ? symbols[string($1)] : 0; }
  | expr '+' expr      { $$ = $1 + $3; }
  | expr '-' expr      { $$ = $1 - $3; }
  | expr '*' expr      { $$ = $1 * $3; }
  | expr '/' expr      { $$ = $1 / $3; }
  | '-' expr %prec NEG { $$ = -$2; }
  | '(' expr ')'       { $$ = $2; }
;

%%

// report errors

void yyerror(char *s) 
{
  cerr << s << endl;
}

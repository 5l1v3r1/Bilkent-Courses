//Ellie Part II is coming. HYPE!

%{
	#include<stdio.h>
	int yylex(void);
	void yyerror(char *);

	extern int yylineno;
%}

//Ellie's Tokens
%token ENTRYPOINT
%token IFSTATEMENT
%token ELSEIFSTATEMENT
%token ELSESTATEMENT
%token FORLOOP
%token WHILELOOP
%token BOOLEAN
%token ATTRIBUTE
%token CLASSWITHARG
%token METHODCALL
%token METHOD
%token IN
%token IDENTIFIER
%token PARAMETERIDENTIFIER
%token CONSTANT
%token CLASS
%token INHERITANCE
%token LPARAN
%token RPARAN
%token LBRACKET
%token RBRACKET
%token RANGE
%token GREATER
%token LESS
%token GREATEROREQUAL
%token LESSOREQUAL
%token NOTEQUAL
%token NOT
%token ASSIGNMENT
%token COMPARISON
%token SEMICOLON
%token COMMA
%token OR
%token AND
%token INTEGER
%token DOUBLE
%token MULTIPLICATION
%token DIVISION
%token SUBTRACTION
%token ADDITION
%token REMAINDER
%token STRING

%%

ellie:
	  main		{printf("Ellie says: main function is fine\n");}
	| functiondecleration
	| inheritance
	;

inheritance:
	CLASS INHERITANCE CLASS LBRACKET functionbody RBRACKET {printf("Ellie says: inheritance is fine\n");}
	| error					{printf("Ellie says: Invalid inheritance around line %d\n", yylineno);}
	;

op:
	  IDENTIFIER            {printf("Ellie says: expression identifier\n");}
	| INTEGER
	| op ASSIGNMENT op		{printf("Ellie says: assigment\n");}
	| op LESS op			{printf("Ellie says: less\n");}
	| op LESSOREQUAL op		{printf("Ellie says: lessOrEqual\n");}
	| op GREATER op			{printf("Ellie says: greater\n");}
	| op GREATEROREQUAL op	{printf("Ellie says: greaterOrEqual\n");}
	| op COMPARISON op		{printf("Ellie says: comparison\n");}
	| op ADDITION op		{printf("Ellie says: addition\n");}
	| op SUBTRACTION op		{printf("Ellie says: subtraction\n");}
	| op MULTIPLICATION op	{printf("Ellie says: multiplication\n");}
	| op DIVISION op		{printf("Ellie says: division\n");}
	| op REMAINDER op		{printf("Ellie says: remainder\n");}
	;

objectCreation:
	  CLASS IDENTIFIER ASSIGNMENT CLASS LPARAN args RPARAN {printf("Ellie says: object creation\n");}
	  | CLASS IDENTIFIER ASSIGNMENT CONSTANT {printf("Ellie says: object creation\n");}
	  | CLASS IDENTIFIER ASSIGNMENT STRING {printf("Ellie says: object creation\n");}
	  | error {printf("Ellie says: Invalid class creation around line %d\n", yylineno);}
	;

stmt:
	  SEMICOLON 		{printf("Ellie says: semicolon\n");}
	  | error			{printf("Ellie says: You forgot semicolon around line %d\n", yylineno);}
	;

main:
	  ENTRYPOINT LBRACKET functionbody RBRACKET {printf("Ellie says: main function\n");}
	;

functiondecleration:
	  IDENTIFIER LPARAN args RPARAN LBRACKET functionbody RBRACKET	{printf("Ellie says: funtion decleration 1\n"); {yyerrok;}}
	  | IDENTIFIER LPARAN args RPARAN stmt	{printf("Ellie says: funtion decleration 2\n"); {yyerrok;}}
	  | METHODCALL LPARAN args RPARAN stmt {printf("Ellie says: funtion decleration 3\n"); {yyerrok;}} 
	  | error {printf("Ellie says: Invalid function decleration around line %d\n", yylineno);}
	;

functionbody:
	
	 stmt	{yyerrok;}
	| op stmt	{yyerrok;}
	| objectCreation stmt	{yyerrok;}
	| functiondecleration functionbody {yyerrok;}
	| functiondecleration {yyerrok;}
	| stmt functionbody	{yyerrok;}
	| op stmt functionbody	{yyerrok;}
	| objectCreation stmt functionbody	{yyerrok;}
	| conditional	{yyerrok;}
	;

args:
	  					//{printf("Ellie says: there is no argument\n");}
	| PARAMETERIDENTIFIER argsTail IDENTIFIER argsTail	{printf("Ellie says: identifier param\n");yyerrok;}
	| PARAMETERIDENTIFIER argsTail INTEGER argsTail	{printf("Ellie says: integer param\n");yyerrok;}
	| PARAMETERIDENTIFIER argsTail BOOLEAN argsTail	{printf("Ellie says: boolean param\n");yyerrok;}
	| PARAMETERIDENTIFIER argsTail CONSTANT argsTail	{printf("Ellie says: constant param\n");yyerrok;}
	| PARAMETERIDENTIFIER argsTail METHODCALL argsTail	{printf("Ellie says: methodcall param\n");yyerrok;}
	| PARAMETERIDENTIFIER argsTail CLASS argsTail	{printf("Ellie says: methodcall param\n");yyerrok;}
	| error {printf("Ellie says: Invalid arguments list around line %d\n", yylineno);}
	;

argsTail:
	| COMMA args	{yyerrok;}
	;

conditional:
	  IFSTATEMENT LPARAN op RPARAN LBRACKET functionbody RBRACKET	{printf("Ellie says: if statement\n");yyerrok;}
	| ELSESTATEMENT LPARAN op RPARAN LBRACKET functionbody RBRACKET	{printf("Ellie says: else statement\n");yyerrok;}
	| ELSEIFSTATEMENT LPARAN op RPARAN LBRACKET functionbody RBRACKET	{printf("Ellie says: else if statement\n");yyerrok;}
	| FORLOOP IDENTIFIER IN RANGE LBRACKET functionbody RBRACKET	{printf("Ellie says: for loop\n");yyerrok;}
	| WHILELOOP LPARAN op RPARAN LBRACKET functionbody RBRACKET	{printf("Ellie says: while loop\n");yyerrok;}
	| error {printf("Ellie says: Invalid conditional statement around line %d\n", yylineno);}
	;

%%



void yyerror(char *s) {	
	fprintf(stderr, "Ellie says: %s\n", s);
}

int main(void) {
	yyparse();
	return 0;
}

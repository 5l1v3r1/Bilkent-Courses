%{
    #include <cstdlib>
    #include <iostream>
    void yyerror(char const *);
    #include "y.tab.h"
%}

%option yylineno

space	[ \t]+
newline	[\n]
comment [/]+.*

digit	[0-9]
lowercase	[a-z]
uppercase	[A-Z]

lparan \(
rparan \)

lbrackets \{
rbrackets \}

semicolon \;
comma	\,
dot	\.

assignment (^|[^!><'=])=($|[^=])
comparison ==
greater	>
less <
greaterequal	>=
lessequal	<=
notequal !=
not !

multiplication	 \*
division	\/
subtraction	\-
addition	\+
remainder \%

or \|\|
and \&\&

entryPoint init

inheritance	->
ifstatement	whether
elseifstatement	"proviso whether"
elsestatement	proviso
boolean	True|False

forloop	for
whileloop while
in	in

string \"([^\\\"]|\\\"|\\\n|\\\\)*\"

alphanumeric ({lowercase}|{uppercase}|{digit})
identifier {lowercase}{alphanumeric}*
parameterIdentifier {identifier}:
class {uppercase}{alphanumeric}*
attribute {identifier}{dot}{class}
methodcall {identifier}{dot}{identifier}
main {entryPoint}{lparan}{rparan}
method {identifier}{lparan}{rparan}
classwitharg {class}{lparan}({identifier}|{string}){rparan}
constant {class}{dot}{class}
integer {digit}+
double [-+]?{digit}*(\.{digit}+)
listelem {space}?{integer}{space}?
listbody ({space}?|{listelem}(,{listelem})*)
list \[{listbody}\]
range {digit}\.\.\.{digit}

%%
{main}	return ENTRYPOINT;
{ifstatement}	return IFSTATEMENT;
{elseifstatement}	return ELSEIFSTATEMENT;
{elsestatement}	return ELSESTATEMENT;
{forloop}	return FORLOOP;
{whileloop}	return WHILELOOP;
{boolean}	return BOOLEAN;
{attribute}	return ATTRIBUTE;
{classwitharg}	return CLASSWITHARG;
{methodcall}	return METHODCALL;
{method}	return METHOD;
{in}	return IN;
{identifier}	return IDENTIFIER;
{parameterIdentifier}    return PARAMETERIDENTIFIER;
{constant}	return CONSTANT;
{class}	return CLASS;
{inheritance}	return INHERITANCE;
{lparan}	return LPARAN;
{rparan}	return RPARAN;
{lbrackets}	return LBRACKET;
{rbrackets}	return RBRACKET;

{range}	return RANGE;

{greater}	return GREATER;
{less}	return LESS;
{greaterequal}	return GREATEROREQUAL;
{lessequal}	return LESSOREQUAL;
{notequal}	return NOTEQUAL;
{not}	return NOT;
{comparison}	return COMPARISON;
{assignment}	return ASSIGNMENT;

{semicolon}	return SEMICOLON;
{comma}	return COMMA;

{or}	return OR;
{and}	return AND;

{integer}	return INTEGER;
{double}	return DOUBLE;

{multiplication}	return MULTIPLICATION;
{division}	return DIVISION;
{subtraction}	return SUBTRACTION;
{addition}	return ADDITION;
{remainder}	return REMAINDER;

{string} return STRING;

{comment}	;
{space}	;
{newline}	;

%%

int yywrap(void) {
	return 1;
}
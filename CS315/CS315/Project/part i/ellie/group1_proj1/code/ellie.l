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

assignment =
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
{entryPoint}	printf("<ENTRYPOINT>\n");
{ifstatement}	printf("<IFSTATEMENT>\n");
{elseifstatement}	printf("<ELSEIFSTATEMENT>\n");
{elsestatement}	printf("<ELSESTATEMENT>\n");
{forloop}	printf("<FORLOOP>\n");
{whileloop}	printf("<WHILELOOP>\n");
{boolean}	printf("<BOOLEAN>\n");
{attribute}	printf("<ATTRIBUTE>\n");
{classwitharg}	printf("<CLASSWITHARG>\n");
{methodcall}	printf("<METHODCALL>\n");
{method}	printf("<METHOD>\n");
{in}	printf("<IN>\n");
{identifier}	printf("<IDENTIFIER>\n");
{parameterIdentifier}    printf("<PARAMETERIDENTIFIER>\n");
{constant}	printf("<CONSTANT>\n");
{class}	printf("<CLASS>\n");
{inheritance}	printf("<INHERITANCE>\n");
{lparan}	printf("<LPARAN>\n");
{rparan}	printf("<RPARAN>\n");
{lbrackets}	printf("<LBRACKET>\n");
{rbrackets}	printf("<RBRACKET>\n");

{range}	printf("<RANGE>\n");

{greater}	printf("<GREATER>\n");
{less}	printf("<LESS>\n");
{greaterequal}	printf("<GREATEROREQUAL>\n");
{lessequal}	printf("<LESSOREQUAL>\n");
{notequal}	printf("<NOTEQUAL>\n");
{not}	printf("<NOT>\n");
{comparison}	printf("<COMPARISON>\n");
{assignment}	printf("<ASSIGNMENT>\n");

{semicolon}	printf("<SEMICOLON>\n");
{comma}	printf("<COMMA>\n");

{or}	printf("<OR>\n");
{and}	printf("<AND>\n");

{integer}	printf("<INTEGER>\n");
{double}	printf("<DOUBLE>\n");

{multiplication}	printf("<MULTIPLICATION>\n");
{division}	printf("<DIVISION>\n");
{subtraction}	printf("<SUBTRACTION>\n");
{addition}	printf("<ADDITION>\n");
{remainder}	printf("<REMAINDER>\n");

{string} printf("<STRING>\n");

{comment}	;
{space}	;
{newline}	;

%%

int yywrap(void) {
	return 1;
}

int main(void) {
	yylex();
	return 0;
}
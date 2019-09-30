
 /* Definitions */

space [ \t]+
digit [0-9]
alphabetic [a-zA-Z]
alphanumeric ({alphabetic}|{digit})
identifier {alphabetic}{alphanumeric}*
integer {digit}+
listelem {space}?{integer}{space}?
listbody ({space}?|{listelem}(,{listelem})*)
list \[{listbody}\]

%%

 /* Rules */

{integer}    printf("INT");
{identifier} printf("ID");
{list}       printf("LIST");
{space} ; /* skip spaces */

%%

int main() { 
  yylex();
  return 0; 
}

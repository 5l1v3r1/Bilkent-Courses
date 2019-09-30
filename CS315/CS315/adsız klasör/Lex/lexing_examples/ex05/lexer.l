
%%

[\t ]+ ;
monday|tuesday|wednesday|thursday|friday printf("<'%s' is a week day>",yytext);
saturday|sunday printf("<'%s' is a weekend>",yytext);
[a-zA-Z]+ printf("<'%s' is not a day>",yytext);

%%

int main() { 
  yylex();
  return 0; 
}

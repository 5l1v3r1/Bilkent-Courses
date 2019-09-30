
%%

monday|tuesday|wednesday|thursday|friday|saturday|sunday printf("<'%s' is a day>",yytext);

%%

int main() { 
  yylex();
  return 0; 
}

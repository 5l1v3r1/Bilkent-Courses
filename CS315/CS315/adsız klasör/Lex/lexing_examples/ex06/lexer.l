
%%

[\t ]+  /* Ignore Whitespace */;
[+-]?[0-9]+(\.[0-9]+)?([eE][+-]?[0-9]+)? printf(" %s:number", yytext);
[a-zA-Z0-9\.]+ printf(" %s:NOT number", yytext);

%%

int main() { 
  yylex();
  return 0; 
}

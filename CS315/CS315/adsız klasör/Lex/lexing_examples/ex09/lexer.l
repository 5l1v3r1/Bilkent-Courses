%%

-?[0-9]+ {
  int k = atoi(yytext);
  printf("%d", k%7 == 0 ?  k+3 : k+1) ;
}
-?[0-9\.]+ ECHO;
[A-Za-z][A-Za-z0-9]* printf("<%s>",yytext);

%%

int main() { 
  yylex();
  return 0; 
}

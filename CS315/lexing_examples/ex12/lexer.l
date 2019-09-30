%{
  int comms=0;
%}

%%

\/\*.*\*\/  {
  comms++;
  printf("COMMENT", yytext);
}
.|\n printf("%s", yytext);
 
%%

int main() { 
  yylex();
  printf("There are %d comments\n", comms);
  return 0; 
}

%{
  int line_num = 0;
%}

%%

^(.|\n) { 
  line_num++; 
  printf("%d:%s", line_num, yytext);
}

%%

int main() { 
  yylex();
  return 0; 
}

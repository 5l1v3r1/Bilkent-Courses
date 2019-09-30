%{
    #include <cstdlib>
    #include <iostream>
    void yyerror(char const *);
    #include "y.tab.h"
%}

%%

\* {
  return KLEENE_STAR;
}

\+ {
  return ONE_OR_MORE;
}

\? {
  return ZERO_OR_ONE;
}

\| {
  return ALTERNATION;
}

\[ { 
  return OPEN_BRACKET;
}

\] { 
  return CLOSE_BRACKET;
}

\( { 
  return OPEN_PARAN;
}

\) { 
  return CLOSE_PARAN;
}

\^ { 
  return CARET;
}

\$ { 
  return DOLLAR;
}

\- { 
  return DASH;
}

\\t {
  yylval.char_val = '\t';
  return CHAR;  
}

\\n {
  yylval.char_val = '\n';
  return CHAR;  
}

\\r {
  yylval.char_val = '\r';
  return CHAR;  
}

\\(\.|\*|\+|\?|\||\^|\$|\\|\[|\]|\(|\)|\-) {
  yylval.char_val = yytext[1];
  return CHAR;
}

\\ {
  yyerror("unknown escape sequence");
  return ERROR_CHAR;
}

\n {
  return *yytext;
}

. { 
  yylval.char_val = *yytext;
  return CHAR;
}

%%

int yywrap(void) 
{
  return 1;
}


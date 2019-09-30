%{
    #include <cstdlib>
    void yyerror(char *);
    #include "y.tab.h"
%}

%%

[a-zA-Z][a-zA-Z0-9]* { /* variables */
  yylval.string = strdup(yytext); // note that we use .string
  return VARIABLE;
}

[0-9]+ { /* integers */
  yylval.integer = atoi(yytext); // note that we use .integer
  return INTEGER;
}

[-+()/=*] { /* operators */
  return *yytext;
}

[\n] { /* new line */
  return *yytext;
}

[ \t] { /* skip whitespace */
  ;
}

. { /* anything else is error */
  return ERROR_CHAR;
}

%%

int yywrap(void) 
{
  return 1;
}


%{
  int comms=0;
%}

%x IN_COMMENT 

%%

<INITIAL>"/*"           BEGIN(IN_COMMENT);
<IN_COMMENT>"*/"        { BEGIN(INITIAL); comms++; printf("COMMENT"); }
<IN_COMMENT>"*"         // eat the Texas
<IN_COMMENT>[^*]+  // eat comment in chunks
 
%%

int main() { 
  yylex();
  printf("There are %d comments\n", comms);
  return 0; 
}

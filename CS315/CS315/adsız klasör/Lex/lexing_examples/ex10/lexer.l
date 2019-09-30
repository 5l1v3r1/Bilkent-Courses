%{
  #include <iostream>
  #include <map>
  using namespace std;
  map<int,int> lengs;
%}

word [^ \t\n,:;\.]+

%%

{word} {
  if (lengs.count(yyleng)==0)
    lengs[yyleng] = 1;
  else
    lengs[yyleng]++;
  cout << "<" << yytext << ">"; 
} 
.|\n ;

%%

int main() { 
  yylex();
  cout << endl << "======" << endl; 
  cout << "Length\t: no words" << endl;
  for(map<int,int>::iterator it=lengs.begin(); it!=lengs.end(); ++it) 
    cout << it->first << "\t: " << it->second << endl;
  return 0; 
}

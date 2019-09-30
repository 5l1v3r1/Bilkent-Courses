digit 			[a-f0-9]
nonzero 		[1-9]
integer 		[-+]?{digit}+
float 			[-+]?{digit}*(\.{digit}+)
identifier		[a-zA-Z][a-zA-Z0-9]*
streetType 		("One-Way"|"Two-Way")
point			("Point")
querry			("VAR"|"REACH"|"FROM"|"BY"|"SORTON"|"LIMIT")
returntype 		("INTEGER"|"STRING"|"FLOAT"|"BOOLEAN"|"LIST"|"MAP"|"SET")
array 			("[Integer]"|"[String]"|"[Boolean]"|"[Float]"|"[List]"|"[Map]"|"[Set]")

%%

"Integer"							{return("DATATYPE_INT")};
"String"							{return("DATATYPE_STR")};
"Float"								{return("DATATYPE_FLT")};
"querry								{return("DATATYPE_qry")};
"Boolean"							{return("DATATYPE_BLN")};
"List"								{return("DATATYPE_LIST")};
"Map"								{return("DATATYPE_MAP")};
"Set"								{return("DATATYPE_SET")};
"VAR"								{return("DATATYPE_VAR")};
"REACH"								{return("DATATYPE_REACH")};
"FROM"								{return("DATATYPE_FROM")};
"BY"								{return("DATATYPE_BY")};
"SORTON"							{return("DATATYPE_SORTON")};
"LIMIT"								{return("DATATYPE_LIMIT")};
"One-Way"							{return("One-Way")};
"Two-Way"							{return("Two-Way")};
"Point"								{return("Point")};
{returntype}						{return("RETURNTYPES")};
"begin"						 		{return("BEGIN")};
"end"							 	{return("END")};
"return"						 	{return("RETURN")};
"true"	 							{return("BOOLEAN")};
"false"								{return("BOOLEAN")};
"while"								{return("WHILE")};
"endwhile"							{return("END_WHILE")};
"for"								{return("FOR")};
"endfor"							{return("END_FOR")};
"if"								{return("IF")};
"endif"								{return("END_IF")};
"then" 						 	 	{return("THEN")};
"to" 							 	{return("TO")}; 
"else" 							 	{return("ELSE")};
"endelse" 						 	{return("END_ELSE")};
"and"								{return("L_AND")};
"or"								{return("L_OR")};
"|"									{return("ALTER")};
"+"									{return("CONCATENATION")};
"=="								{return("EQUAL")};
"!="								{return("N_EQUAL")};
"="									{return("ASSIGN")};
"<="								{return("L_EQUAL")};
"<"									{return("LESS_THAN")};
">="								{return("G_EQUAL")};
">"									{return("GREATER_THAN")};
";"									{return("SEMICOLON")};
","									{return("COMMA")};
"."									{return("DOT")};
"("									{return("LP")};
")"									{return("RP")};
"["									{return("L_BRAC")};
"]"									{return("R_BRAC")};
"*"									{return("REPETITION")};
"->"								{return("CONNECT_ONE_WAY")};
"<->"								{return("CONNECT_TWO_WAY")};
"toString"							{return("TOSTRING_FUNC")};
"insert"							{return("INSERT")};
{array}					 	 		{return("ARRAY")};
{direction}						 	{return("DIRECTION")};
{float}								{return("FLOAT")};
{integer}						 	{return("INTEGER")};
{identifier}						{return("IDENTIFIER")};
(["](.)*["])						{return("STRING")};

%%

int main(){
	yylex();
	return 0; 
}
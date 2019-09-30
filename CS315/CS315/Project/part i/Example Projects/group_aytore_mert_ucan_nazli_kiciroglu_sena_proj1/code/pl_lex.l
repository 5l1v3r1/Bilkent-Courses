
ASSIGN					=	
BOOLCHECK				==
ONEWAY					->
TWOWAY					=>	
CONCAT 					concat
ALTER 					alter
REP  					rep	
NOT						not 
VARIABLEVALUE			vary
GREATER					greater
LESS 					less
GREATEROREQUAL			greaterOrEqual
LESSOREQUAL				lessOrEqual
STARTSWITH				startsWith

STREETNETWORK 			SN 
PROPERTY				Property 
POINT					Point
STREET					Street
LIST					List 
MAP 					Map 
SET 					Set 
TIME					Time 
ADDPROPERTY				.addProperty
REMOVEPROPERTY			.removeProperty 
ADDDELAY				.addDelay 
REMOVEDELAY				.removeDelay 
CLOSED					.closed
OPENED					.opened
APPEND					.append 
REMOVE 					.remove
ADD 					.add
REMOVEKEY				.removeKey 
REMOVEVALUE 			.removeValue 
FINDROUTE				.findRoute 
SORTSHORTESTROUTE		.sortShortestRoute 
SORTSHORTESTDISTANCE 	.sortShortestDistance 
SORTSIMPLESTROUTE		.sortSimplestRoute 
ADDSTREET				.addStreet 

	
WHITESPACE 				[\ \t]+
DIGIT 					[0-9]
LPARAN 					\(
RPARAN 					\)
UNDERSCORE				\_
COLON					\:
SLASH					\/
LETTER 					[a-zA-Z]
NEWLINE 				\n
INT 					({DIGIT})+
FLOAT 					({INT})*(\.{INT}|{INT}\.)({INT})*
ENDSTATEMENT			\;
QUOTATION				\"
COMMENT 				{SLASH}{SLASH}([^\n])*\n
STRING					\"([^\\\"]|\\\"|\\\n|\\\\)*\"
CHARACTER				\'[^\\\']\'	
ID 						{LETTER}({LETTER}|{UNDERSCORE}|{DIGIT})*

%%
{ASSIGN} printf("<ASSIGN>");
{BOOLCHECK} printf("<BOOLCHECK>");
{ONEWAY} printf("<ONEWAY>");
{TWOWAY} printf("<TWOWAY>");

{CONCAT} printf("<CONCAT>");
{ALTER} printf("<ALTER>");
{REP} printf("<REP>");
{NOT} printf("<NOT>");
{GREATER} printf("<GREATER>");
{LESS} printf("<LESS>");
{GREATEROREQUAL} printf("<GREATEROREQUAL>");
{LESSOREQUAL} printf("<LESSOREQUAL>");
{STARTSWITH} printf("<STARTSWITH>");

{STREETNETWORK} printf("<STREETNETWORK>");
{PROPERTY} printf("<PROPERTY>");
{POINT} printf("<POINT>");
{STREET} printf("<STREET>");
{LIST} printf("<LIST>");
{MAP} printf("<MAP>");
{SET} printf("<SET>");
{TIME} printf("<TIME>");
{ADDPROPERTY} printf("<ADDPROPERTY>");
{REMOVEPROPERTY} printf("<REMOVEPROPERTY>");
{ADDDELAY} printf("<ADDDELAY>");
{REMOVEDELAY} printf("<REMOVEDELAY>");
{CLOSED} printf("<CLOSED>");
{OPENED} printf("<OPENED>");
{APPEND} printf("<APPEND>");
{REMOVE} printf("<REMOVE>");
{ADD} printf("<ADD>");
{REMOVEKEY} printf("<REMOVEKEY>");
{REMOVEVALUE} printf("<REMOVEVALUE>");
{FINDROUTE} printf("<FINDROUTE>");
{SORTSHORTESTROUTE} printf("<SORTSHORTESTROUTE>");
{SORTSHORTESTDISTANCE} printf("<SORTSHORTESTDISTANCE>");
{SORTSIMPLESTROUTE} printf("<SORTSIMPLESTROUTE>");

{WHITESPACE} printf("");
{DIGIT} printf("<DIGIT>");
{LPARAN} printf("<LPARAN>");
{RPARAN} printf("<RPARAN>");
{UNDERSCORE} printf("<UNDERSCORE>");
{COLON} printf("<COLON>");
{LETTER} printf("<LETTER>");
{NEWLINE} printf("\n");

{ID} printf("<ID,%s>",yytext);
{INT} printf("<INT>");
{FLOAT} printf("<FLOAT,%s>",yytext);
{ENDSTATEMENT} printf("<ENDSTATEMENT>");
{QUOTATION} printf("<QUOTATION>");
{COMMENT} printf("<COMMENT>\n");
{CHARACTER} printf("<CHARACTER,%s>",yytext);
{STRING} printf("<STRING,%s>",yytext);


%%

int main() { 
  yylex();
  return 0; 
}

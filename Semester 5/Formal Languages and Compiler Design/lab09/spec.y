%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern int yylex(void);

void yyerror(char *s);

#define YYDEBUG 1 
%}

%union {
    char *str;
}

%token ARRAY
%token BOOL
%token INT
%token CHAR
%token STRING
%token IF
%token ELIF
%token ELSE
%token DO
%token END
%token GETS
%token PUTS
%token CUTS
%token TO_I
%token START
%token STOP
%token WHILE
%token FOR
%token AND
%token OR
%token IN
%token BREAK
%token TRUE
%token FALSE
%token NIL
%token RETURN

%token plus
%token minus
%token mul
%token divs
%token mod
%token less
%token lessOrEqual
%token equal
%token different
%token moreOrEqual
%token more
%token eq

%token leftRoundBracket
%token rightRoundBracket
%token leftSquareBracket
%token rightSquareBracket
%token leftCurlyBracket
%token rightCurlyBracket
%token comma
%token colon
%token semicolon

%token BOOL_CONST
%token INT_CONST
%token CHAR_CONST
%token STRING_CONST
%token IDENTIFIER

%start program

%%

const : 	BOOL_CONST
		| INT_CONST
		| CHAR_CONST
		| STRING_CONST
		;

program : 	START statement_list STOP
		;
statement_list : 	statement semicolon 
			| statement semicolon statement_list
			;
statement : 	declaration_statement
		| assignment_statement 
		| if_statement 
		| while_statement 
		| return_statement 
		| for_statement 
		| break_statement
		| io_statement 
		| imod_statement
		;

declaration_statement : data_type IDENTIFIER
			;
data_type : 	INT 
		| STRING 
		| CHAR 
		| BOOL 
		| ARRAY
		;

assignment_statement : 	IDENTIFIER eq expression 
			| IDENTIFIER eq imod_statement
			| IDENTIFIER eq array_access
			| IDENTIFIER eq leftSquareBracket array_values rightSquareBracket
			| array_access eq expression
			;
array_values : 	const
             	| array_values comma const
             	;
expression : 	expression plus term 
		| expression minus term 
		| term
		;
term : 	term mul factor 
	| term divs factor 
	| term mod factor
	| factor
	;
factor :	leftRoundBracket expression rightRoundBracket 
		| const 
		| IDENTIFIER 
		;
array_access : 	IDENTIFIER leftSquareBracket expression rightSquareBracket
		;

if_statement : 	IF condition statement_list ELIF condition statement_list ELSE statement_list END
		| IF condition statement_list ELSE statement_list END
		| IF condition statement_list END
		;
condition : 	expression relation expression
		;
relation : 	less 
		| lessOrEqual 
		| equal 
		| different 
		| moreOrEqual 
		| more
		;

while_statement : 	WHILE condition compound_statement
			;
compound_statement : 	DO statement_list END
			;

return_statement : 	RETURN expression
			;

for_statement : 	FOR IDENTIFIER IN expression compound_statement
			;

break_statement: 	BREAK
			;

io_statement : 	GETS leftRoundBracket IDENTIFIER rightRoundBracket 
		| PUTS leftRoundBracket IDENTIFIER rightRoundBracket
		| PUTS leftRoundBracket const rightRoundBracket
		;

imod_statement : 	CUTS leftRoundBracket IDENTIFIER rightRoundBracket 
			| CUTS leftRoundBracket STRING_CONST rightRoundBracket 
			| TO_I leftRoundBracket IDENTIFIER rightRoundBracket 
			| TO_I leftRoundBracket STRING_CONST rightRoundBracket
			;

%%

extern FILE *yyin;

int yywrap() {
	return 1;
}

void yyerror(char *s)
{	
	printf("%s\n", s);
}

int main(int argc, char **argv)
{
	if(argc>1) yyin = fopen(argv[1],"r");
	if(argc>2 && !strcmp(argv[2],"-d")) yydebug = 1;
	if(!yyparse()) fprintf(stderr, "\tProgram is syntactically correct.\n");
	return 0;
}
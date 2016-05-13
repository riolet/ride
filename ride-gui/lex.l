%{
/* need this for the call to atof() below */
#include <math.h>
#include <string.h>

int col_number = 0;



%}


%option noyywrap

CLASSOP									":::"
SCOPERESOP								"::"
DIGIT    								[0-9]
RET      								"->"
SL_COMMENT 								"//".*
ML_COMMENT  							[/][*][^*]*[*]+([^*/][^*]*[*]+)*[/]
ML_UNTERMINATED_COMMENT					[/][*] 
STRING        							\"(\\.|[^\\"])*\"
CHAR        							\'(\\.|[^\\'])+\'

INT_TYPE								"int"

IDENTIFIER								[A-Za-z0-9]+

%%


{DIGIT}+ {
										size_t len = strlen(yytext);
										col_number+=len;
     									printf( "An integer: %s (%d)\n", yytext,
             								atoi( yytext ) );
             								
             							printf( "Length was: (%zu); and column is now: (%d) \n", len, col_number);
}

{DIGIT}+"."{DIGIT}* {
										size_t len = strlen(yytext);
										col_number+=len;
    									printf( "A float: %s (%g)\n", yytext,
             								atof( yytext ) );
             								
             							printf( "Length was: (%zu); and column is now: (%d) \n", len, col_number);
}

{INT_TYPE} {							
										size_t len = strlen(yytext);
										col_number+=len;
										printf( "An int type: %s\n", yytext);
										
             							printf( "Length was: (%zu); and column is now: (%d) \n", len, col_number);
}

{STRING} {								
										size_t len = strlen(yytext);
										col_number+=len;
										printf( "A string: %s\n", yytext);
             							printf( "Length was: (%zu); and column is now: (%d) \n", len, col_number);
}

{CHAR} {								
										size_t len = strlen(yytext);
										col_number+=len;
										printf( "A char: %s\n", yytext);
             							printf( "Length was: (%zu); and column is now: (%d) \n", len, col_number);
}

{CLASSOP} {								
										size_t len = strlen(yytext);
										col_number+=len;
										printf( "A class operator: %s\n", yytext );
             							printf( "Length was: (%zu); and column is now: (%d) \n", len, col_number);
}

{SCOPERESOP} {							
										size_t len = strlen(yytext);
										col_number+=len;
										printf( "A scope resolution operator: %s\n", yytext );
             							printf( "Length was: (%zu); and column is now: (%d) \n", len, col_number);
}

if|for {								
										size_t len = strlen(yytext);
										col_number+=len;
										printf( "A keyword: %s\n", yytext );
             							printf( "Length was: (%zu); and column is now: (%d) \n", len, col_number);
}

{RET} {									
										size_t len = strlen(yytext);
										col_number+=len;
										printf( "A return statement: %s\n", yytext );
             							printf( "Length was: (%zu); and column is now: (%d) \n", len, col_number);
}

{IDENTIFIER} {
										size_t len = strlen(yytext);
										col_number+=len;
										printf( "An identifier: %s\n", yytext );
             							printf( "Length was: (%zu); and column is now: (%d) \n", len, col_number);
}

{SL_COMMENT} { 					 		
										size_t len = strlen(yytext);
										col_number+=len;
										printf( "single line comment: %s\n", yytext );
             							printf( "Length was: (%zu); and column is now: (%d) \n", len, col_number);
}

{ML_COMMENT} {
										size_t len = strlen(yytext);
										col_number+=len;
										printf( "Multiline comment: %s\n", yytext);
             							printf( "Length was: (%zu); and column is now: (%d) \n", len, col_number);
}
							

{ML_UNTERMINATED_COMMENT} {
										size_t len = strlen(yytext);
										col_number+=len;
								 		printf( "Multiline unterminated comment\n");
             							printf( "Length was: (%zu); and column is now: (%d) \n", len, col_number);
}

. {
										size_t len = strlen(yytext);
										col_number+=len;
          								printf( "Unrecognized character: %s\n", yytext );
             							printf( "Length was: (%zu); and column is now: (%d) \n", len, col_number);
             							
             							
}


%%


/*int main( int argc, char **argv ) {
	++argv, --argc;  /* skip over program name */
	/*if ( argc > 0 )
	     yyin = fopen( argv[0], "r" );
	else
	     yyin = stdin;

	yylex();
}
*/

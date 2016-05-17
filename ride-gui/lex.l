%{
/* need this for the call to atof() below */
#include <math.h>
#include <string.h>
#include "lexershare.h"
RixLexer *_lex;
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
                                        _lex->styleToken(len, 1);
}

{DIGIT}+"."{DIGIT}* {
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, 2);
}

{INT_TYPE} {							
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, 3);
}

{STRING} {								
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, 4);
}

{CHAR} {								
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, 5);
}

{CLASSOP} {								
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, 6);
}

{SCOPERESOP} {							
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, 7);
}

if|for {								
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, 8);
}

{RET} {									
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, 9);
}

{IDENTIFIER} {
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, 10);
}

{SL_COMMENT} { 					 		
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, 11);
}

{ML_COMMENT} {
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, 12);
}
							

{ML_UNTERMINATED_COMMENT} {
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, 13);
}

. {
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, 0);
             							
}


%%


void scan_string(const char* str)
{
    yy_switch_to_buffer(yy_scan_string(str));
    yylex();
}

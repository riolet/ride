%{

/* need this for the call to atof() below */
#include <math.h>
#include <string.h>
#include <ctype.h>
#include "lexershare.h"
#include "syntaxcolours.h"
RixLexer *_lex;
int col_number = 0;
int* find_return_token_pos(const char* token);

%}

%x C_COMMENT

%option noyywrap

NEWLINE                                 "\n"
CLASSOP									":::"
SCOPERESOP								"::"
DIGIT    								[0-9]
RET      								"->"
SL_COMMENT 								"//".*
STRING        							\"(\\.|[^\\"])*\"
CHAR        							\'(\\.|[^\\'])+\'

INT_TYPE								"int"

IDENTIFIER								[A-Za-z0-9]+


%%


{SL_COMMENT} {
                                        size_t len = strlen(yytext);
                                        _lex->styleToken(len, SyntaxColours::Comm);
}

" " {
                                        size_t len = 1;
                                        _lex->styleToken(len, SyntaxColours::Noncoloured);
}

\t {
                                        size_t len = 1;
                                        _lex->styleToken(len, SyntaxColours::Noncoloured);
}

{DIGIT}+ {
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, SyntaxColours::Integer);
}

{DIGIT}+"."{DIGIT}* {
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, SyntaxColours::Float);
}

{INT_TYPE} {							
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, SyntaxColours::Int);
}

{STRING} {								
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, SyntaxColours::String);
}

{CHAR} {								
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, SyntaxColours::Char);
}

{CLASSOP} {								
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, SyntaxColours::Class);
}

{SCOPERESOP} {							
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, SyntaxColours::Scope);
}

if|for {								
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, SyntaxColours::Keyword);
}

{RET} {									
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, SyntaxColours::Return);
}

{IDENTIFIER} {
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, SyntaxColours::Identifier);
}

{NEWLINE} {
                                        size_t len = 1;
                                        _lex->styleToken(len, SyntaxColours::Noncoloured);
}

. {
										size_t len = strlen(yytext);
                                        _lex->styleToken(len, SyntaxColours::Noncoloured);
}


%%


void scan_string(const char* str)
{
    yy_switch_to_buffer(yy_scan_string(str));
    yylex();
}

int* find_return_token_pos(const char* token)
{
    int indexStart = 0;

    while(!isalnum(token[indexStart++])) {}
    int indexEnd = indexStart;
    while(isalnum(token[indexEnd++])) {}
    int indexBrack = indexEnd;
    while(token[indexBrack++] != '(') {}
    int ret[3] = {indexStart, indexEnd, indexBrack};
    return ret;
}

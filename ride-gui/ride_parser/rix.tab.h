/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Skeleton interface for Bison GLR parsers in C

   Copyright (C) 2002-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_RIX_TAB_H_INCLUDED
# define YY_YY_RIX_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    ENDOFFILE = 0,
    ENDOFLINE = 258,
    INT = 259,
    CHAR = 260,
    FLOAT = 261,
    STRING = 262,
    IDENT = 263,
    NEWIDENT = 264,
    UNMARKEDNEWIDENT = 265,
    FIELD = 266,
    VERB = 267,
    STATICVERB = 268,
    TYPE = 269,
    MATH_OP = 270,
    ASSIGNMENT = 271,
    LPAREN = 272,
    RPAREN = 273,
    LBRACKET = 274,
    RBRACKET = 275,
    RBRACKETASSIGN = 276,
    INDENT = 277,
    LBRACE = 278,
    RBRACE = 279,
    UNINDENT = 280,
    CONDITIONLINK = 281,
    UNARYNEGATE = 282,
    MATHASSIGN = 283,
    BITWISEOP = 284,
    BOOLEANOP = 285,
    COLON = 286,
    CLASSDEC = 287,
    CLASSDECPRIM = 288,
    PARAMCOMMA = 289,
    RETURN = 290,
    SELFIDENT = 291,
    SLCOMMENT = 292,
    COMPARISON = 293,
    LESSTHAN = 294,
    GREATERTHAN = 295,
    TERNARY = 296,
    CODE_INSERT = 297,
    CONDRETURN = 298,
    ACCESSOR = 299,
    DTV_EXTERNAL = 300,
    DTV_ADDSOURCE = 301,
    DESTRUCTOR = 302
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 23 "rix.y" /* glr.c:197  */

	int     ival;
	float   fval;
	char*   sval;
	Object* oval;

#line 110 "rix.tab.h" /* glr.c:197  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif

/* Location type.  */
#if ! defined YYLTYPE && ! defined YYLTYPE_IS_DECLARED
typedef struct YYLTYPE YYLTYPE;
struct YYLTYPE
{
  int first_line;
  int first_column;
  int last_line;
  int last_column;
};
# define YYLTYPE_IS_DECLARED 1
# define YYLTYPE_IS_TRIVIAL 1
#endif



int yyparse (void);

#endif /* !YY_YY_RIX_TAB_H_INCLUDED  */

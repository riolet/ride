/* 
===============================================================================
SOURCE FILE:	errors.c 
					This files houses all of the application logic for 
					handling error message

PROGRAM:		Linux Terminal

FUNCTIONS:		void errorInitial( char *);

PROGRAMMER(S):	Duy Pham

NOTES:
Standard Notes go here.
===============================================================================
*/

#ifndef ERRORS_H
#define ERRORS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "parser_error.h"

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

typedef enum
{
    ERROR_EndlessString = 1,
    ERROR_FunctionPlacement,
    ERROR_IncompatibleTypes,
    ERROR_UnexpectedIndent,
    ERROR_AssignToLiteral,
    ERROR_UnrecognizedSymbol,
    ERROR_UndefinedVerb,
    ERROR_UndefinedVariable,
    ERROR_UndefinedType,
    ERROR_CannotAllocateMemory,
    ERROR_InvalidArguments,
    ERROR_ParseError,
    ERROR_RuntimeError
} ErrorCode;

int e_count;
int e_flag;
int g_lineNum;
int g_lineCol;
int g_headerLines;

int errorMsg(const char *format, ...);
int warningMsg(const char *format, ...);
void criticalError(ErrorCode code, char *message);

/*
===============================================================================
FUNCTION: 		errorInitial 

PROGRAMMER(S):	Duy Pham

INTERFACE:		multi interface

PARAMETERS:		char *process: 
					The error message that is called from other interface

RETURNS:		void

NOTES:			This methods create an error object and send it back to rixc
				
===============================================================================
*/

void errorInitial( char *message );

#endif

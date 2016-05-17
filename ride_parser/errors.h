#ifndef ERRORS_H
#define ERRORS_H

#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

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

/*-------------------------------------------------------------------------*//**
 * @brief      Type define of an error object
 * @details    This object indicates an error message that can be returned to
 *             the GUI.
 * @author     Duy Pham
 * @version    1.0
 */
extern typedef struct error_object
{
    char *message;
    int message_length;
    int line_number;
    int column_start;
    int num_characters;
} Error;

int e_count;
int g_lineNum;
int g_lineCol;
int g_headerLines;

int errorMsg(const char *format, ...);
int warningMsg(const char *format, ...);
void criticalError(ErrorCode code, char *message);

/**
 * @brief      Initialize an error object
 *
 * @param      message  The message of the error
 */
void errorInitial( char *message );

#endif

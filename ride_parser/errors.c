#include "errors.h"

int warningMsg(const char *format, ...)
{
    int ret;
    //fprintf(stderr,"Line %d: Column:%d - ",lineNum,linePos);
    fprintf(stderr, ANSI_COLOR_YELLOW);
    va_list arg;
    va_start(arg, format);
    ret = vfprintf(stderr, format, arg);
    va_end(arg);
    fprintf(stderr, ANSI_COLOR_RESET);
    return ret;
}

int errorMsg(const char *format, ...)
{
    int ret;
    fprintf(stderr, ANSI_COLOR_RED);
    fprintf(stderr, "Line %d: Column:%d - ", g_lineNum - g_headerLines, g_lineCol);
    va_list arg;
    va_start(arg, format);
    ret = vfprintf(stderr, format, arg);
    fprintf(stderr, ANSI_COLOR_RESET);
    va_end(arg);
    return ret;
}

void errorInitial( Error *e, char* message )
{
    e->message  = message;
    e->line     = g_lineNum - g_headerLines;
    e->column   = g_lineCol;
}

void criticalError(ErrorCode code, char *message)
{
    Error error;
    Error *e = &error;

    error.code = code;

    fprintf(stderr, "\t");
    switch (code)
    {
    case ERROR_EndlessString:
        errorInitial(e, "Error parsing string. No closing quote.\n");
        break;
    case ERROR_IncompatibleTypes:
        errorInitial(e, "Type mismatch.\n");
        break;
    case ERROR_UnexpectedIndent:
        errorInitial(e, "Unexpected scope increase\n");
        break;
    case ERROR_AssignToLiteral:
        errorInitial(e, "Cannot assign to a literal.\n");
        break;
    case ERROR_UnrecognizedSymbol:
        errorInitial(e, "Unknown symbol detected.\n");
        break;
    case ERROR_CannotAllocateMemory:
        errorInitial(e, "Cannot allocate new space.\n");
        break;
    case ERROR_UndefinedVerb:
        errorInitial(e, "Verb encountered without definition.\n");
        break;
    case ERROR_UndefinedVariable:
        errorInitial(e, "Variable encountered without definition.\n");
        break;
    case ERROR_UndefinedType:
        errorInitial(e, "Type encountered without definition.\n");
        break;
    case ERROR_InvalidArguments:
        errorInitial(e, "Attempted to run a function with invalid arguments.\n");
        break;
    case ERROR_ParseError:
        errorInitial(e, "Error while parsing file.\n");
        break;
    default:
        errorInitial(e, "Unknown critical error. Aborting.\n");
    }
    if (message)
    {
        fprintf(stderr, "\t");
        fprintf(stderr, "%s", message);
    }
    // exit((int)code);
}

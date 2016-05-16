#include "errors.h"

int warningMsg(const char *format, ...)
{
    int ret;
    //fprintf(stderr,"Line %d: Column:%d - ",lineNum,linePos);
    fprintf(stderr, ANSI_COLOR_YELLOW);
    va_list arg;
    va_start(arg, format);
    ret = vfprintf(stderr, format, arg);
    errorInitial(ret);
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
    errorInitial(ret);
    fprintf(stderr, ANSI_COLOR_RESET);
    va_end(arg);
    return ret;
}

void errorInitial( Error *e, char *message )
{
    e = malloc(sizeof(Error));

    //add to errList

    e->message          = message;
    e->message_length   = strlen(message);
    e->line_number      = g_lineNum - g_headerLines;
    e->column_start     = g_lineCol;
    e->num_characters   = 0;

    e_count++;
    sendError(e);
}

void criticalError(ErrorCode code, char *message)
{
    fprintf(stderr, "\t");
    switch (code)
    {
    case ERROR_EndlessString:
        errorMsg(e, "Error parsing string. No closing quote.\n");
        break;
    case ERROR_IncompatibleTypes:
        errorMsg(e, "Type mismatch.\n");
        break;
    case ERROR_UnexpectedIndent:
        errorMsg(e, "Unexpected scope increase\n");
        break;
    case ERROR_AssignToLiteral:
        errorMsg(e, "Cannot assign to a literal.\n");
        break;
    case ERROR_UnrecognizedSymbol:
        errorMsg(e, "Unknown symbol detected.\n");
        break;
    case ERROR_CannotAllocateMemory:
        errorMsg(e, "Cannot allocate new space.\n");
        break;
    case ERROR_UndefinedVerb:
        errorMsg(e, "Verb encountered without definition.\n");
        break;
    case ERROR_UndefinedVariable:
        errorMsg(e, "Variable encountered without definition.\n");
        break;
    case ERROR_UndefinedType:
        errorMsg(e, "Type encountered without definition.\n");
        break;
    case ERROR_InvalidArguments:
        errorMsg(e, "Attempted to run a function with invalid arguments.\n");
        break;
    case ERROR_ParseError:
        errorMsg(e, "Error while parsing file.\n");
        break;
    default:
        errorMsg(e, "Unknown critical error. Aborting.\n");
    }
    if (message)
    {
        fprintf(stderr, "\t");
        fprintf(stderr, "%s", message);
    }
    // exit((int)code);
}

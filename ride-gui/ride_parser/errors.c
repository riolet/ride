#include "errors.h"

int warningMsg(const char *format, ...)
{
    // printf("CALLED FROM WARNING ERROR\n");
    int ret;
    //fprintf(stderr,"Line %d: Column:%d - ",lineNum,linePos);
    fprintf(stderr, ANSI_COLOR_YELLOW);
    va_list arg;
    va_start(arg, format);
    ret = vfprintf(stderr, format, arg);

    // In case we want to grab the error and modify it
    char buffer[1024];
    vsnprintf(buffer, 1024, format, arg);
    errorInitial(buffer);

    va_end(arg);
    fprintf(stderr, ANSI_COLOR_RESET);
    return ret;
}

int errorMsg(const char *format, ...)
{
    // printf("CALLED FROM ERROR MESSAGE\n");
    int ret;
    fprintf(stderr, ANSI_COLOR_RED);
    fprintf(stderr, "Line %d: Column:%d - ", g_lineNum - g_headerLines, g_lineCol);
    va_list arg;
    va_start(arg, format);

    // In case we want to grab the error and modify it
    char buffer[1024];
    vsnprintf(buffer, 1024, format, arg);
    errorInitial(buffer);

    ret = vfprintf(stderr, format, arg);
    fprintf(stderr, ANSI_COLOR_RESET);
    va_end(arg);
    return ret;
}

void criticalError(ErrorCode code, char *message)
{
    fprintf(stderr, "\t");
    e_flag++;
    // printf("CALLED FROM CRITICAL ERROR\n");
    switch (code)
    {
    case ERROR_EndlessString:
        errorMsg( "Error parsing string. No closing quote.\n");
        break;
    case ERROR_IncompatibleTypes:
        errorMsg( "Type mismatch.\n");
        break;
    case ERROR_UnexpectedIndent:
        errorMsg( "Unexpected scope increase\n");
        break;
    case ERROR_AssignToLiteral:
        errorMsg( "Cannot assign to a literal.\n");
        break;
    case ERROR_UnrecognizedSymbol:
        errorMsg( "Unknown symbol detected.\n");
        break;
    case ERROR_CannotAllocateMemory:
        errorMsg( "Cannot allocate new space.\n");
        break;
    case ERROR_UndefinedVerb:
        errorMsg( "Verb encountered without definition.\n");
        break;
    case ERROR_UndefinedVariable:
        errorMsg( "Variable encountered without definition.\n");
        break;
    case ERROR_UndefinedType:
        errorMsg( "Type encountered without definition.\n");
        break;
    case ERROR_InvalidArguments:
        errorMsg( "Attempted to run a function with invalid arguments.\n");
        break;
    case ERROR_ParseError:
        errorMsg( "Error while parsing file.\n");
        break;
    default:
        errorMsg( "Unknown critical error. Aborting.\n");
    }
    if (message)
    {
        fprintf(stderr, "\t");
        fprintf(stderr, "%s", message);
    }
    
    // exit(0);
}

/**
 * @brief      Initialize an error object
 *
 * @param      message  The message of the error
 */
void errorInitial( char *message )
{
    Error *e;
    // printf("A wild error has appeared\n");
    // 
    e = (Error *) malloc(sizeof(Error));

    //add to errList
    e->message          = (char*) malloc(sizeof(char) * strlen(message));
    strcpy(e->message, message);

    e->message_length   = strlen(message);
    e->line_number      = g_lineNum - g_headerLines;
    e->column_start     = g_lineCol;
    e->num_characters   = 0;
    e_count++;
    pushError(e);
}
/* 
===============================================================================
SOURCE FILE:	parser_error.h 
					This files houses the definatio of an error struct

PROGRAM:		Linux Terminal

FUNCTIONS:		

PROGRAMMER(S):	Duy Pham

NOTES:
This object indicates an error message that can be returned to
 *             the GUI.
===============================================================================
*/

#ifndef ERROR_OBJECT_H
#define ERROR_OBJECT_H

typedef struct error_object
{
    char *message;
    int message_length;
    int line_number;
    int column_start;
    int num_characters;
} Error;
#endif  // ERROR_OBJECT_H

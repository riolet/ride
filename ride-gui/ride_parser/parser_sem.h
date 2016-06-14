/* 
===============================================================================
SOURCE FILE:	parser_error.h 
					This files houses the defination of the semaphore structs

PROGRAM:		Linux Terminal

FUNCTIONS:		

PROGRAMMER(S):	Duy Pham

NOTES:
This hold the defination of the semaphore structs that we use to communicate
between the GUI and the Parser
===============================================================================
*/

#ifndef PARSER_SEM_H
#define PARSER_SEM_H

#include <semaphore.h>

#define SEM_CODE        		"/codesem"
#define SHARED_CODE     		"/code"

#define SEM_ERROR       		"/errsem"
#define SHARED_ERROR    		"/error"
#define SHARED_NUMBER_ERROR		"/error_num"

/**
 * @brief      GUI parse request struct
 */
struct semaphore_request
{
    sem_t   *sem;
    int     fd;     // fd is the start position of content in the shared memory block
    char    *content;
    int     max_size;
};

/**
 * @brief      Parser response struct
 */
struct semaphore_response
{
    sem_t   *sem;
    int     fd;     // fd is the start position of content in the shared memory block
    int 	fd_num_err;
    int     *errNumber;
    char   	*content;
    int     max_size;
};

extern struct semaphore_request sem_doc;
extern struct semaphore_response sem_error;

#endif //PARSER_SEM_H

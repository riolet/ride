#ifndef PARSER_SEM_H
#define PARSER_SEM_H

#include <semaphore.h>
#include "parser_error.h"

#define SHARED_CODE     "/code"
#define SHARED_ERROR    "/error"
#define SEM_CODE        "/codesem"
#define SEM_ERROR       "/errsem"

/**
 * @brief      GUI parse request struct
 */
struct semaphore_request
{
    int     fd;
    sem_t   *sem;
    char    *content;
};

/**
 * @brief      Parser response struct
 */
struct semaphore_response
{
    int     fd;
    sem_t   *sem;
    int     *errNumber;
    Error   **content;
};


extern struct semaphore_request sem_doc;
extern struct semaphore_response sem_error;
#endif //PARSER_SEM_H

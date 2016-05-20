#ifndef PARSER_SEM_H
#define PARSER_SEM_H

#include <semaphore.h>
#include "parser_error.h"

#define SHARED_CODE     "/code"
#define SHARED_ERROR    "/error"
#define SHARED_ERR_NUM  "/error_num"
#define SEM_CODE        "/codesem"
#define SEM_ERROR       "/errsem"

/**
 * @brief      GUI parse request struct
 */
struct semaphore_request
{
    sem_t   *sem;
    int     fd;     // fd is the start position of content in the shared memory block
    char    *content;
};

/**
 * @brief      Parser response struct
 */
struct semaphore_response
{
    sem_t   *sem;
    int     fd;     // fd is the start position of content in the shared memory block
    int     errNumber;
    Error   **content;
};

extern struct semaphore_request sem_doc;
extern struct semaphore_response sem_error;

#endif //PARSER_SEM_H

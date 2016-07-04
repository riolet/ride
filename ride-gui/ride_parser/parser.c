/* 
===============================================================================
SOURCE FILE:    parser.h 
                    This file houses all the parser functions that we uses
                    for parsing text and detects error

PROGRAM:        Linux Terminal

FUNCTIONS:      void sig_chld (int)
                int main(int , char **)

PROGRAMMER(S):  Duy Pham

NOTES:
===============================================================================
*/

#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>
#include <stdlib.h>

#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <sys/mman.h>
#include <semaphore.h>

#include "parser_sem.h"
#include "rixc.h"

struct  semaphore_request  sem_doc;
struct  semaphore_response sem_error;

Error **err_array;

void sig_chld (int signo)
{
    pid_t pid;
    int stat;
    pid = wait(&stat);
    return;
}

int main(int argc, char **argv)
{
    char *start;
    int i;
    char buf[1024];


    printf("Running parser!\n");

    printf("Map semaphore\n");
    sem_doc.sem         = sem_open(SEM_CODE,  0);
    sem_error.sem       = sem_open(SEM_ERROR, 0);

    if (sem_doc.sem == SEM_FAILED || sem_error.sem == SEM_FAILED)
    {
        perror("Semphore creation");
        return 1;
    }

    /* ------------------------------------------------------------------------------------ */
    printf("Map file descriptor\n");
    sem_doc.fd              = shm_open(SHARED_CODE, O_RDWR, 0666);
    sem_error.fd            = shm_open(SHARED_ERROR, O_RDWR, 0666);
    sem_error.fd_num_err    = shm_open(SHARED_NUMBER_ERROR, O_RDWR, 0666);

    // Checking for error
    if (sem_doc.fd == -1 || sem_error.fd == -1 || sem_error.fd_num_err == -1)
    {
        fprintf(stderr, "Parser could not start, error with shared memory.\n");
        return 1;
    }

    /* ------------------------------------------------------------------------------------ */
    printf("Map contents with file descriptor\n");
    sem_doc.content     = (char *) mmap(0, 10240, PROT_READ, MAP_SHARED, sem_doc.fd,   0);

    sem_error.errNumber = (int *) mmap(0, sizeof(int), PROT_WRITE, MAP_SHARED, sem_error.fd_num_err, 0);
    sem_error.content   = (char *) mmap(0, 10240, PROT_WRITE, MAP_SHARED, sem_error.fd, 0);
    
    /**
     * Parser start to parse the code continuously
     */ 
    while (true)
    {
        printf("Waiting on document.\n");
        sem_wait(sem_doc.sem);
        printf("Woken up\n");

        printf("Print document:\n%s\n", sem_doc.content);

        // errorDetect(error_array, sem_error.errNumber, sem_doc.content);
        *sem_error.errNumber = 2;

        Error *e = (Error*) malloc(sizeof(Error));
        e->message = "Hello Tyler";
        e->message_length = strlen(e->message);
        e->line_number = 0;
        e->column_start = 0;
        e->num_characters = 5;

        Error *e2 = (Error*) malloc(sizeof(Error));
        e2->message = "Goodbye Tyler";
        e2->message_length = strlen(e2->message);
        e2->line_number = 1;
        e2->column_start = 1;
        e2->num_characters = 6;

        err_array = (Error **) malloc (sizeof(Error*) * 2);
        err_array[0] = e;
        err_array[1] = e2;

        start = sem_error.content;
        
        for (i = 0; i < *sem_error.errNumber; i++)
        {
            memset(buf, 1024, 0);
            sprintf(buf,
                    "%d,%d,%d,%d,%s\n",
                    err_array[i]->message_length,
                    err_array[i]->line_number,
                    err_array[i]->column_start,
                    err_array[i]->num_characters,
                    err_array[i]->message
                   );
            sprintf(sem_error.content, "%s", buf);
            
            size_t travel = strlen(buf);
            sem_error.content += travel;
        }
        
        sem_error.content = start;
        // free(e);
        // free(e2);
        free(err_array);
        printf("Error detection finished\n");

        sem_post(sem_error.sem);
    }

    return 1;
}

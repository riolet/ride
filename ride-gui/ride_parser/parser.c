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

struct semaphore_request  sem_doc;
struct semaphore_response sem_error;

void sig_chld (int signo)
{
    pid_t pid;
    int stat;
    pid = wait(&stat);
    return;
}

int main(int argc, char **argv)
{
    char        word_doc_buffer[10023];
    Error     **error_array;
    int        *error_number;
    int doc, err;

    printf("Running parser!\n");

    /**
    * Start to map semaphore struc with shared memory
    */
    while (true)
    {

        sem_doc.sem         = sem_open(SEM_CODE,  0);
        sem_doc.fd          = shm_open(SHARED_CODE, O_RDONLY, 0666);
        sem_doc.content     = (char *) mmap(0, 10240, PROT_READ, MAP_SHARED, sem_doc.fd,   0);

        sem_error.sem       = sem_open(SEM_ERROR, 0);
        sem_error.fd        = shm_open(SHARED_ERROR, O_RDWR, 0666);
        sem_error.content   = (Error **) mmap(0, 10240, PROT_READ, MAP_SHARED, sem_error.fd, 0);


        // Checking for error
        if (sem_doc.sem == SEM_FAILED
                || sem_error.sem == SEM_FAILED
                || sem_doc.fd == -1
                || sem_error.fd == -1
                || sem_error.errNumber == -1)
        {
            fprintf(stderr, "Parser could not start, error with shared memory.\n");
            // return 1;
        }
        else
        {
            break;
        }

    }


    /**
     * Parser start to parse the code continuously
     */
    while (true)
    {
        printf("Waiting on document.\n");
        sem_wait(sem_doc.sem);
        printf("Woken up.\n");
        // Doing stuff
        errorDetect(sem_error.content, &(sem_error.errNumber), sem_doc.content);
        printf("Error detection finished.\n");
        sem_post(sem_error.sem);
    }

    return 1;
}

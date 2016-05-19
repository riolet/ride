#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>        /* For mode constants */
#include <fcntl.h>           /* For O_* constants */
#include "parser_sem.h"

int main(int argc, char **argv)
{
    char  word_doc[1024];
    char  word_error[1024];

    sem_doc.sem   = sem_open(SEM_CODE,  0);
    sem_error.sem = sem_open(SEM_ERROR, 0);

    sem_wait(sem_doc.sem);
    sem_wait(sem_error.sem);

    sem_doc.fd     = shm_open(SHARED_CODE,  O_RDWR, 0666);
    sem_error.fd   = shm_open(SHARED_ERROR, O_RDWR, 0666);

    if (sem_doc.fd == -1 || sem_error.fd == -1)
    {
        fprintf(stderr, "The program could not start, error with shared memory.\n");
        return 1;
    }

    // Critical section
    sem_doc.content   = (char *)mmap(0, 10240, PROT_READ, MAP_SHARED, sem_doc.fd,   0);
    sem_error.content = (char *)mmap(0, 10240, PROT_READ, MAP_SHARED, sem_error.fd, 0);

    printf("sem_doc.content:   [%s]\n", sem_doc.content);
    printf("sem_error.content: [%s]\n", sem_error.content);

    sem_post(sem_doc.sem);
    sem_post(sem_error.sem);

    return 1;
}

#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>        // For mode constants
#include <fcntl.h>           // For O_* constants
#include <stdio.h>
#include <QApplication>
#include "mainwindow.h"
#include "globals.h"

#define SHARED_CODE     "/code"
#define SHARED_ERROR    "/error"
#define SEM_CODE        "/codesem"
#define SEM_ERROR       "/errsem"

int      fd_doc;     // File descriptor for the shared memory for the code.
int      fd_error;   // File descriptor for the shared memory for error structs.
char*    temp_doc;   // Pointer to the temporary document memory.
char*    temp_error; // Pointer to the temporary error memory.

struct semaphore sem_doc;
struct semaphore sem_error;

void sig_chld (int signo)
{
    pid_t pid;
    int stat;
    pid = wait(&stat);
    return;
}

int main(int argc, char *argv[])
{
    /*sem_doc.sem   = sem_open(SEM_CODE, O_CREAT, 0600, 1);
    sem_error.sem = sem_open(SEM_ERROR,O_CREAT, 0600, 1);

    if (sem_doc.sem == SEM_FAILED || sem_error.sem == SEM_FAILED)
    {
        perror("Sema:");
        return 1;
    }

    // Signaling method, call it to wait for the child if it terminate
    signal (SIGCHLD, sig_chld);
    if (fork() == 0)
    {
        // Duy/Phill, put your c compilation stuff here if you want.
        printf("Ghosts\n");
        system("gcc ../parser.c -lpthread -lrt -o parser");
        execl("./parser", (char*)0);

        // THE CHILD WILL NEVER REACH HERE, IT IS REPLACED ENTIRELY
        return 0;
    }

    int doc, err;

    printf("Waiting");
    // Note: Use this ONLY for a HARD reset, you can easily screw up expected behaviour here.
    if(doc < 1) // Sometimes semaphores screw up, use this to reset it back to normal
    {
        sem_post(sem_doc.sem);
    }

    if(err < 1) // Sometimes semaphores screw up, use this to reset it back to normal
    {
        sem_post(sem_error.sem);
    }


    sem_getvalue(sem_doc.sem, &doc);
    sem_getvalue(sem_doc.sem, &err);

    // Note: Use this ONLY for a HARD reset, you can easily screw up expected behaviour here.
    if(doc < 1) // Sometimes semaphores screw up, use this to reset it back to normal
    {
        sem_post(sem_doc.sem);
    }

    if(err < 1) // Sometimes semaphores screw up, use this to reset it back to normal
    {
        sem_post(sem_error.sem);
    }

    sem_wait(sem_doc.sem);
    sem_wait(sem_error.sem);

    //Parent
    sem_doc.fd   = shm_open(SHARED_CODE,  O_RDWR | O_CREAT | O_TRUNC, 0666);
    sem_error.fd = shm_open(SHARED_ERROR, O_RDWR | O_CREAT | O_TRUNC, 0666);

    if (sem_doc.fd == -1 || sem_error.fd == -1)
    {
        std::cerr << "The program could not start, error with shared memory." << std::endl;
        return 1;
    }

    printf("Opening shared memory\n");

    ftruncate(sem_doc.fd,   10240);
    ftruncate(sem_error.fd, 10240);

    sem_doc.content   = (char *)mmap(0, 10240, PROT_WRITE, MAP_SHARED, sem_doc.fd,   0);
    sem_error.content = (char *)mmap(0, 10240, PROT_WRITE, MAP_SHARED, sem_error.fd, 0);

    printf("Writing to shared memory\n");

    sprintf(sem_doc.content,   "This is the test doc!\n");
    sprintf(sem_error.content, "Error, this is the error doc!\n");

    sleep(10);

    printf("Shutting down\n");

    sem_post(sem_doc.sem);
    sem_post(sem_error.sem);
    printf("Out of loop");

    sem_destroy(sem_doc.sem);
    sem_destroy(sem_error.sem);

    return 1;*/

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}

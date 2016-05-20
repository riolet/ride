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

struct semaphore_request  sem_doc;
struct semaphore_response sem_error;
pid_t child;

void sig_chld (int signo)
{
    pid_t pid;
    int stat;
    pid = wait(&stat);
    return;
}

int main(int argc, char *argv[])
{
    int* err_num;

    sem_doc.sem   = sem_open(SEM_CODE,  O_CREAT, 0600, 0);
    sem_error.sem = sem_open(SEM_ERROR, O_CREAT, 0600, 0);

    if (sem_doc.sem == SEM_FAILED || sem_error.sem == SEM_FAILED)
    {
        perror("Semphore creation");
        return 1;
    }

    int doc, err;

    // Note: Use this ONLY for a HARD reset, you can easily screw up expected behaviour here.
    do // Sometimes semaphores screw up, use this to reset it back to normal
    {
        sem_getvalue(sem_doc.sem, &doc);
        if(doc < 0)
        {
            sem_post(sem_doc.sem);
        }
        else if(doc > 0)
        {
            sem_wait(sem_doc.sem);
        }

    }
    while(doc != 0);

    do // Sometimes semaphores screw up, use this to reset it back to normal
    {
        sem_getvalue(sem_error.sem, &err);
        if(err < 0)
        {
            sem_post(sem_error.sem);
        }
        else if(err > 0)
        {
            sem_wait(sem_error.sem);
        }

    }
    while(err != 0);

    //Parent
    sem_doc.fd   = shm_open(SHARED_CODE,  O_RDWR | O_CREAT | O_TRUNC, 0666);
    sem_error.fd = shm_open(SHARED_ERROR, O_RDWR | O_CREAT | O_TRUNC, 0666);

    if (sem_doc.fd == -1 || sem_error.fd == -1)
    {
        perror("Shared memory creation");
        return 1;
    }

    printf("Manipulating shared memory size.\n");
    ftruncate(sem_doc.fd,   10240);
    ftruncate(sem_error.fd, 10240);

    sem_doc.content   = (char *)  mmap(0, 10240, PROT_WRITE, MAP_SHARED, sem_doc.fd,   0);
    sem_error.content = (Error **)mmap(0, 10240, PROT_WRITE, MAP_SHARED, sem_error.fd, 0);

    //Error tester.
    /*
    Error* error = (Error*) malloc(sizeof(Error));
    int* temp = (int*)malloc(sizeof(int));
    *temp = 1;

    (*error).message = (char *)malloc(10);
    sprintf((*error).message, "Hello");

    (*error).message_length = strlen((*error).message);
    (*error).line_number = 0;
    (*error).column_start = 0;
    (*error).num_characters = 5;
    sem_error.errNumber = temp;

    sem_error.content = &error;
    */

    // Signaling method, call it to wait for the child if it terminate
    signal (SIGCHLD, sig_chld);

    /*child = fork();
    if (child == 0)
    {

        //system("make rider-parser/make parser");
        //("./parser", ">cout.txt", "2>cerr.txt",(char *)0);

        //system("gcc ../parser.c -lpthread -lrt -o parser");
        printf("Go.\n");
        execl("./parser >cout.txt 2>cerr.txt", (char *)0);

        // THE CHILD WILL NEVER REACH HERE, IT IS REPLACED ENTIRELY
        return 0;
    }*/

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

}

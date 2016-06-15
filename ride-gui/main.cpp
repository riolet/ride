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

pid_t child;
struct semaphore_request  sem_doc;
struct semaphore_response sem_error;

int main(int argc, char *argv[])
{
    int doc, err;

    // Destroy all previous instances of all used semaphores
    //   note: if there is a zombie child, it will not be dead.
    sem_unlink(SEM_CODE);
    sem_unlink(SEM_ERROR);

    //
    // Create semaphore
    //
    printf("Initialize sempaphore\n");
    sem_doc.sem   = sem_open(SEM_CODE,  O_CREAT, 0600, 0);
    sem_error.sem = sem_open(SEM_ERROR, O_CREAT, 0600, 0);

    if (sem_doc.sem == SEM_FAILED || sem_error.sem == SEM_FAILED)
    {
        perror("Semphore creation");
        return 1;
    }

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

    //
    // Initialize file descriptor
    //
    printf("Initialize file descriptor\n");
    
    sem_doc.fd              = shm_open(SHARED_CODE,  O_RDWR | O_CREAT | O_TRUNC, 0666);
    sem_error.fd            = shm_open(SHARED_ERROR, O_RDWR | O_CREAT | O_TRUNC, 0666);
    sem_error.fd_num_err    = shm_open(SHARED_NUMBER_ERROR, O_RDWR | O_CREAT | O_TRUNC, 0666);

    if (sem_doc.fd == -1 || sem_error.fd == -1 || sem_error.fd_num_err == -1)
    {
        perror("Shared memory creation");
        return 1;
    }    

    //
    //Manipulate file descriptor size
    //
    sem_doc.max_size = 10240;
    sem_error.max_size = 10240;

    ftruncate(sem_doc.fd,   sem_doc.max_size);
    ftruncate(sem_error.fd, sem_error.max_size);
    ftruncate(sem_error.fd_num_err, sizeof(int));

    //
    // Map content with descriptor
    //
    printf("Map contents with file descriptor\n");

    sem_doc.content     = (char *)  mmap(0, sem_doc.max_size, PROT_WRITE, MAP_SHARED, sem_doc.fd,   0);
    
    sem_error.errNumber = (int*) mmap(0, sizeof(int), PROT_READ, MAP_SHARED, sem_error.fd_num_err, 0);  
    sem_error.content   = (char *) mmap(0, sem_error.max_size, PROT_READ, MAP_SHARED, sem_error.fd, 0);

    
    //
    // Fork child process
    //
    child = fork();
    if (child == 0)
    {
        system("./make ride_parser/make parser");

        execl("./ride_parser/parser", (char *)0);

        // THE CHILD WILL NEVER REACH HERE, IT IS REPLACED ENTIRELY
        return 0;
    }

    //
    // This block is a mockup testing
    //
    FILE *file;
    char str[sem_doc.max_size];
    size_t nread;

    file = fopen("ride_parser/www.rit", "r");
    if (file)
    {
        while ((nread = fread(str, 1, sizeof str, file)) > 0)
        {
            // fwrite(str, 1, nread, stdout);
        }
        if (ferror(file))
        {
            // deal with error
        }
        fclose(file);
    }
    sprintf(sem_doc.content, str);

    // View the contents here in Qt
    semaphore_request test = sem_doc;
    semaphore_response temp = sem_error;

    sem_post(sem_doc.sem);
    sem_wait(sem_error.sem);

    // View the contents here in Qt
    test = sem_doc;
    temp = sem_error;

    //
    // Start GUI
    //
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

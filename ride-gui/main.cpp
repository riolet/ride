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
    if(InitializeSharedMemory(&sem_doc, &sem_error) == -1)
        return -1;

    // Fork child process
    child = fork();
    if (child == 0)
    {
        system("make -C ride_parser clean");
        system("make -C ride_parser parser");
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
    memcpy(sem_doc.content, str, sem_doc.max_size);

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

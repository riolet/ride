#include "mainwindow.h"
#include <unistd.h>
#include <QApplication>

#define SNAME "parser/sem"

//sem_t *sem;

int main(int argc, char *argv[])
{
    pid_t pid;

    // Create shared memory


    pid = fork();
    if(pid == 0)
    {
        printf("I'm a child");
        //sleep for 3 seconds
        //sem = sem_open(SNAME, O_CREAT, 0644, 0); /* Initial value is 3. */

        //system("./rixparser");
    }
    else
    {
        //sem = sem_open(SNAME, 0);
        QApplication a(argc, argv);
        MainWindow w;
        w.show();

        a.exec();
    }

    // shem unlink here
    return 1;
}

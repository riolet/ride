#include "mainwindow.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <QApplication>

void sig_chld (int signo)
{
    pid_t pid;
    int stat;
    pid = wait(&stat);
    return;
}

int main(int argc, char *argv[])
{
    // Signaling method, call it to wait for the child if it terminate
    signal (SIGCHLD, sig_chld);
    if (fork() == 0)
    {
        // Here's the child process

        // Wait for

        // Do something here, consider "exec" the parser

        return 0;
    }
    else
    {
        // Here's the main process
        // Initialize shared resources
        // Run the GUI
        QApplication a(argc, argv);
        MainWindow w;
        w.show();
        return a.exec();
    }
}

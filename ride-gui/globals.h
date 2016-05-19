#ifndef GLOBALS_H
#define GLOBALS_H

#include <QFile>
#include <QDir>
#include <QString>
#include <iostream>
#include <vector>
#include <QFont>
#include <Qsci/qsciscintilla.h>
#include <QDebug>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>        // For mode constants
#include <fcntl.h>           // For O_* constants
#include <stdio.h>

struct semaphore
{
    int     fd;
    char*   content;
    sem_t*  sem;
};

extern struct semaphore sem_doc;
extern struct semaphore sem_error;

#endif // GLOBALS_H

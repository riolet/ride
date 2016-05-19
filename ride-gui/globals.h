#ifndef GLOBALS_H
#define GLOBALS_H

#include <semaphore.h>
#include <QFile>
#include <QDir>
#include <QString>
#include <iostream>
#include <vector>
#include <QFont>
#include <Qsci/qsciscintilla.h>
#include <QDebug>

extern int      fd_doc;     // File descriptor for the shared memory for the code.
extern int      fd_error;   // File descriptor for the shared memory for error structs.
extern char*    temp_doc;   // Pointer to the temporary document memory.
extern char*    temp_error;  // Pointer to the temporary error memory.

struct semaphore
{
    int     fd;
    char*   content;
    sem_t*  sem;
};

extern struct semaphore sem_doc;
extern struct semaphore sem_error;

#endif // GLOBALS_H

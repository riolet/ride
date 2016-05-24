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
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>        // For mode constants
#include <fcntl.h>           // For O_* constants
#include <stdio.h>
#include "ride_parser/parser_sem.h" //Contains the semaphores for the parser.
#include <string>
#include <regex>
#include <sstream>

extern pid_t child;

#endif // GLOBALS_H

/*===============================================================================
SOURCE FILE:    compilerhandler.cpp 
                    Definition of the compilerhandler.h dedicated to handling 
                    the compiler and running the "rix" shell script that is 
                    found inside of your rix folder.

PROGRAM:        Ride

FUNCTIONS:      explicit CompilerHandler(QObject *parent);
                void compileRixFile(ScintillaDoc* doc = NULL);
                void readCompilerOutput(FILE* output, FILE* error);

QT SIGNALS:     void compilerOutput(const QString& line);
                void compilerError(const QString& error);

PROGRAMMER(S):  Tyler Trepanier-Bracken

NOTES:
This source file defines all of the functions that were declared inside of the
compilerhandler.h file. This class runs the "rix" shell script and sends all
compilation messages to the mainwindow. This is done via signals which are
caught by the mainwindow slot.
===============================================================================*/
#include "compilerhandler.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 2048 // Size of a standard output/error line message.

CompilerHandler::CompilerHandler(QObject *parent) : QObject(parent)
{
    compile_begin   = QString("Starting compilation...");
    compile_end     = QString("End of compilation...");
}

bool CompilerHandler::compileRixFile(ScintillaDoc *doc)
{
    FILE *fp;
    FILE *output = fopen("output_temp.tmp", "w+");
    FILE *error  = fopen("error_temp.tmp",  "w+");
    
    QString filename("test.rit");
    QString cmd;

    if(doc != NULL)
    {
        filename = doc->_filepath;
    }

    cmd = QString("rix %1 >output_temp.tmp 2>error_temp.tmp").arg(filename);

    emit compilerOutput(compile_begin);

    if(output == NULL || error == NULL)
    {
        QString err("Cannot create temporary files for writing...");
        emit compilerOutput(err);
    }

    // Open the command for reading. 
    fp = popen(cmd.toStdString().c_str(), "r");
    if (fp == NULL)
    {
        QString err("Rix compilation unable to proceed.");
        emit compilerOutput(err);

        pclose(fp);
        fclose(output);
        fclose(error);

        return false;
    }

    readCompilerOutput(output, error);

    pclose(fp);
    fclose(output);
    fclose(error);

    emit compilerOutput(compile_end);

    // Remove the newly created output and error temp files.
    system("rm output_temp.tmp error_temp.tmp");
    return true;
}

void CompilerHandler::readCompilerOutput(FILE* output, FILE* error)
{
    char buffer[BUFSIZE];
    bool flag = false;

    while(true)
    {
        if(!flag)
            fseek(output, 0, SEEK_SET);

        if(fgets(buffer, BUFSIZE-1, output) != NULL)
        {
            flag = true;
        }
        else
        {
            flag = false;
        }

        if(strstr(buffer, "...END...") != NULL)
        {
            break;
        }
    }

    //Output is ready, place the file pointer to the beginning
    fseek(output, 0, SEEK_SET);
    while (fgets(buffer, BUFSIZE-1, output) != NULL)
    {
        int newline = strlen(buffer);
        
        // Do not show the ...END... message
        if(newline == 10 && strstr(buffer, "...END...\n") )
        {
            continue;
        }

        buffer[newline-1] = '\0'; //Remove newline character.
        QString line(buffer);
        
        emit compilerOutput(line);
    }

    // Read the output one line at a time - output it.
    fseek(error, 0, SEEK_SET);
    while (fgets(buffer, BUFSIZE-1, error) != NULL)
    {
        int newline = strlen(buffer);
        buffer[newline-1] = '\0'; //Remove newline character.
        QString err(buffer);

        emit compilerError(err);
    }
}

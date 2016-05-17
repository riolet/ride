#include "compilerhandler.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 2048
extern char **environ;

CompilerHandler::CompilerHandler(QObject *parent) : QObject(parent)
{
    compile_begin   = QString("Starting compilation...");
    compile_end     = QString("End of compilation...");
}

void CompilerHandler::compileRixFile(ScintillaDoc *doc)
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
        QString error("Cannot create temporary files for writing...");
        emit compilerOutput(error);
    }

    /* Open the command for reading. */
    fp = popen(cmd.toStdString().c_str(), "r");  // Close standard output
    if (fp == NULL)
    {
        QString err("Rix compilation unable to proceed.");
        emit compilerOutput(err);

        pclose(fp);
        fclose(output);
        fclose(error);

        return;
    }

    readCompilerOutput(output, error);

    pclose(fp);
    fclose(output);
    fclose(error);

    emit compilerOutput(compile_end);

    system("rm output_temp.tmp error_temp.tmp");

    /* close */


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

    //Output is ready
    fseek(output, 0, SEEK_SET);
    while (fgets(buffer, BUFSIZE-1, output) != NULL)
    {
        QString line(buffer);
        emit compilerOutput(line);
    }

    /* Read the output one line at a time - output it. */
    fseek(error, 0, SEEK_SET);
    while (fgets(buffer, BUFSIZE-1, error) != NULL)
    {
        QString err(buffer);
        emit compilerError(err);
    }
}

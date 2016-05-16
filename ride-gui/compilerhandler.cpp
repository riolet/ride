#include "compilerhandler.h"
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 2048
extern char **environ;

CompilerHandler::CompilerHandler(QObject *parent) : QObject(parent)
{

}

void CompilerHandler::compileRixFile(ScintillaDoc *doc)
{
    //system("rix test.rit");
    //system("echo $RIX_HOME");

    if(doc != NULL)
    {
        //TODO: Take in the document's information and read it.
        return;
    }

    FILE *fp;
    char buffer[BUFSIZE];

    /* Open the command for reading. */
    fp = popen("rix test.rit 2>&1", "r"); // Debugging, all cout/cerr to output
    //fp = popen("rix test.rit", "r");    // cout only to output, errors stay on Qt
    if (fp == NULL)
    {
        QString error("Rix compilation unable to proceed.");
        emit compilerOutput(error);
    }
    else
    {
        /* Read the output a line at a time - output it. */
        int i = 1;
        while (fgets(buffer, BUFSIZE-1, fp) != NULL)
        {
            QString line(buffer);
            QString num;
            num.setNum(i).append('}').prepend('{');
            line.prepend(num);
            emit compilerOutput(line);

            ++i;
        }
    }

    /* close */
    pclose(fp);
}

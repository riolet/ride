#include "compilerhandler.h"
#include <stdio.h>
#include <stdlib.h>
extern char **environ;

CompilerHandler::CompilerHandler(QObject *parent) : QObject(parent)
{
    system("rix test.rit");
    system("echo $RIX_HOME");
    std::cerr << "Hello" << std::endl;
    //for (char **env = environ; *env; ++env)
        //std::cerr << *env << std::endl;
    //char *oldenv = getenv("PATH"); // Make a copy of your PATH
    //std::cerr << oldenv << std::endl;
    //setenv("PATH", "hello", 1); // Overwrite it

    //system("echo $PATH"); // Outputs "hello"

    //setenv("PATH", oldenv, 1); // Restore old PATH
    //free(oldenv); // Don't forget to free!

    //system("echo $PATH"); // Outputs your actual PATH
    //system("env | grep RIX_HOME");
}

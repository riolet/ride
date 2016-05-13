#include "compilerhandler.h"

CompilerHandler::CompilerHandler(QObject *parent) : QObject(parent)
{
    system("cd ../");
    system("ls");
}

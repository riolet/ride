#ifndef AUTOCOMPLETION_H
#define AUTOCOMPLETION_H
#include <globals.h>

struct Function {
    std::string              name;
    std::string              r_type;
    std::vector<std::string> args;
};

struct Class {
    std::string           name;
    std::string           parent;
    std::vector<Function> members;
};

struct Completion {
    std::vector<Function> functs;
    std::vector<Class>    classes;
};

Completion completion;
void Detect ();

#endif // AUTOCOMPLETION_H

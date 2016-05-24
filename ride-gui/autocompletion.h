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
};


class Autocompletion {
private:
    std::vector<Function> functs;
    std::vector<Class>    classes;

public:
    void Detect (char* code);
};

#endif // AUTOCOMPLETION_H

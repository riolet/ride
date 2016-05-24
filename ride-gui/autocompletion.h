#ifndef AUTOCOMPLETION_H
#define AUTOCOMPLETION_H
#include <globals.h>

#define FLAG_ASSIGNMENT 1
#define FLAG_SUBJECT    2
#define FLAG_EXTERNAL   4
#define BUFFLEN 1024
#define LINESIZE 1024


struct Function {
    std::string              name;
    std::string              r_type;
    std::vector<std::string> args;
};

struct Class {
    std::string              name;
    std::string              parent;
};


class Autocompletion {
private:
    std::vector<Function>    functs;
    std::vector<Class>       classes;
    FILE*                    ritTempFile;
    int                      numline;

public:

    Autocompletion();

    void Detect (std::string code);
    std::vector<Function>    GetFunctions();
    std::vector<Class>       GetClasses();
    std::string FormatFunction(Function in);
    std::string FormatClass(Class in);
    std::string AutocompleteClass(Class in);
    std::string AutocompleteFunction(Function in);
    int HandleImports(char name[], FILE * ofp, int *numline);
};

#endif // AUTOCOMPLETION_H

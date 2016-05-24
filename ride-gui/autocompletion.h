#ifndef AUTOCOMPLETION_H
#define AUTOCOMPLETION_H
#include <globals.h>

#define FLAG_ASSIGNMENT 1
#define FLAG_SUBJECT    2
#define FLAG_EXTERNAL   4
#define BUFFLEN 1024
#define LINESIZE 1024


/*===============================================================================
FUNCTION:       Store Found Functions

PROGRAMMER(S):  Dimitry Rakhlei

NOTES:
Stores the function name, return type and all arguments as strings.
===============================================================================*/
struct Function {
    std::string              name;
    std::string              r_type;
    std::vector<std::string> args;
};

/*===============================================================================
FUNCTION:       Store Found Class Declarations

PROGRAMMER(S):  Dimitry Rakhlei

NOTES:
Stores the class name and it's parent's name.
===============================================================================*/
struct Class {
    std::string              name;
    std::string              parent;
};

/*===============================================================================
FUNCTION:       Handle the Autocompletion data.

PROGRAMMER(S):  Dimitry Rakhlei

INTERFACES:     Autocompletion()       - Constructor.
                Detect()               - Detects all functions and stores them.
                FormatFunction()       - Formats one function for display.
                FormatClass()          - Formats a class decl for display.
                AutocompleteClass()    - Formats a class decl for insertion.
                AutocompleteFunction() - Formats a function for insertion.
                HandleImports()        - Stitches imported files into one.
NOTES:
Used by rixlexer to display an autocompletion box.
===============================================================================*/
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

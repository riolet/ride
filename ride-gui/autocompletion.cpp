#include "autocompletion.h"

/*===============================================================================
FUNCTION:       Sets up autocompletion files.

PROGRAMMER(S):  Dimitry Rakhlei

NOTES:
Will be called each time text needs to be parsed.
===============================================================================*/
Autocompletion::Autocompletion() {
    numline = 0;
    //if(ritTempFile != 0) fclose(ritTempFile);
    ritTempFile = fopen("rix_temp_file.rit", "w");
    if (ritTempFile == 0) {
        perror("fopen failed");
    }
    HandleImports("rsl/rsl.rit", ritTempFile, &numline);
}

/*===============================================================================
FUNCTION:       Detects Function and Class declarations in Code.

PROGRAMMER(S):  Dimitry Rakhlei

NOTES:
Called once per check. Uses regular expressions to parse code.
===============================================================================*/
void Autocompletion::Detect (std::string code) {
    std::ofstream ofs("code.temp");
    ofs << code;
    ofs.close();
    HandleImports("code.temp", ritTempFile, &numline);
    fclose(ritTempFile);
    std::ifstream file("rix_temp_file.rit");
    std::string input;
    std::cout << input << std::endl;
    std::stringstream buffer;
    buffer << file.rdbuf();
    input = buffer.str();

    std::regex   funcre(R"(\s*(\w+)\s*->\s*(\w+)\s*\((.*?)\))"),
            classre(R"(^(\w+)\s*(\((.*?)\))?\s*::\s*(\w+))");
    std::regex re(R"((\w+)\s+\w+,?)");
    std::string  line;
    std::smatch  m;
    bool    in_class = false;
    std::string  class_name;
    Class   n_class;
    Function n_function;

    std::stringstream ss(input);

    while (getline(ss, line)) {
      if (line.size() > 0 && !isspace(line[0]))
        in_class = false;
      if (regex_search(line, m, classre)) {
        in_class = true;
        class_name = m.str(1);
        std::cout << "class name : " << m.str(1) << std::endl;
        std::cout << "clas parent: " << m.str(4) << std::endl;
        n_class.name = m.str(1);
        n_class.parent = m.str(4);
        classes.push_back(n_class);
      }
      else if (regex_search(line, m, funcre)) {
        std::cout << "function/method name: "
             << (in_class ? (class_name + "::" + m.str(1)) : m.str(1)) << std::endl;
        std::cout << "return type: " << m.str(2) << std::endl;

        n_function.name = in_class ? (class_name + "::" + m.str(1)) : m.str(1);

        n_function.r_type = m.str(2);

        std::smatch sm;
        std::string args = m.str(3);
        auto pos = args.cbegin(), end = args.cend();
        for ( ; regex_search(pos, end, sm, re); pos = sm.suffix().first) {
          std::cout << "parameter: " << sm.str(1) << std::endl;
          n_function.args.push_back(sm.str(1));
        }
        functs.push_back(n_function);
      }
    }
}


/*===============================================================================
FUNCTION:       Getter for Function struct vector.

PROGRAMMER(S):  Dimitry Rakhlei

NOTES:
Returns the vector of functions.
===============================================================================*/
std::vector<Function> Autocompletion::GetFunctions() {
    return functs;
}

/*===============================================================================
FUNCTION:       Getter for the Class struct vector.

PROGRAMMER(S):  Dimitry Rakhlei

NOTES:
Returns the vector of classes.
===============================================================================*/
std::vector<Class> Autocompletion::GetClasses() {
    return classes;
}


/*===============================================================================
FUNCTION:       Formats a Function struct for display.

OUTPUT FORMAT:  fname -> r_type ( arg_type, arg_type ... )

ARGUMENT(S):    (in) is the Function that will be formatted.

PROGRAMMER(S):  Dimitry Rakhlei

NOTES:
Function called on each Function before being displayed.
===============================================================================*/
std::string Autocompletion::FormatFunction(Function in) {
    std::string out;
    out += in.name;
    out += "->";
    out += "(";
    for(auto it : in.args)
        out += it;
    out += ")";
    std::cout << out << std::endl;
    return out;
}

/*===============================================================================
FUNCTION:       Formats a Class struct for display.

OUTPUT FORMAT:  Class_Name::Parent_Name

ARGUMENT(S):    (in) is the Class that will be formatted.

PROGRAMMER(S):  Dimitry Rakhlei

NOTES:
Function called on each Class before being displayed.
===============================================================================*/
std::string Autocompletion::FormatClass(Class in) {
    std::string out;
    out += in.name;
    out += "::";
    out += in.parent;
    std::cout << out << std::endl;
    return out;
}


/*===============================================================================
FUNCTION:       Formats a Class struct for insertion.

OUTPUT FORMAT:  Class_Name()

ARGUMENT(S):    (in) is the Class that will be formatted.

PROGRAMMER(S):  Dimitry Rakhlei

NOTES:
Function called on each Class before being inserted.
===============================================================================*/
std::string Autocompletion::AutocompleteClass(Class in) {
    std::string out;
    out += in.name;
    out += "(";
    out += ")";
    return out;
}

/*===============================================================================
FUNCTION:       Formats a Function struct for insertion.

OUTPUT FORMAT:  fname()

ARGUMENT(S):    (in) is the Function that will be formatted.

PROGRAMMER(S):  Dimitry Rakhlei

NOTES:
Function called on each Function before being inserted.
===============================================================================*/
std::string Autocompletion::AutocompleteFunction(Function in) {
    std::string out;
    out += in.name;
    out += "(";
    out += ");";
    return out;
}

/*===============================================================================
FUNCTION:       Recursively appends imported files for parsing.

OUTPUT FORMAT:  fname()

ARGUMENT(S):    (name)    The name of the file that will be opened and appended.
                (ofp)     The output file pointer that stores the total file.
                (numline) The current line in ofp.

PROGRAMMER(S):  Dimitry Rakhlei

NOTES:
Needed because we need to know the imported functions as well.
For example the Rix Standard Library Print function.
===============================================================================*/
int Autocompletion::HandleImports(char name[], FILE * ofp, int *numline) {
    FILE *fp;
    char line[LINESIZE], word[LINESIZE], word2[LINESIZE];
    size_t len = strlen(name);
    if (name[len - 1] == '"')
        name[len - 1] = '\0';
    if (name[0] == '"') {
        name++;
    }
    if ((fp = fopen(name, "r")) == 0) {

        const char *RIX_HOME = getenv("RIX_HOME");
        char importPath[BUFFLEN];
        if (RIX_HOME != 0) {
            snprintf(importPath, BUFFLEN, "%s/%s", RIX_HOME, name);
            if ((fp = fopen(importPath, "r")) == 0) {
                printf
                    ("Cannot find import file %s in working directory or RIX_HOME\n",
                     importPath);
                perror("open");
                return 1;
            }
        } else {

            perror("open");
            return 1;
        }
    }
    while (fgets(line, LINESIZE, fp)) {
        if (sscanf(line, "%s%s", word, word2) == 2 && strcmp(word, "import") == 0) {
            HandleImports(word2, ofp, numline);
        } else {
            (*numline)++;
            fprintf(ofp, "%s", line);
        }
    }
    return 1;
}

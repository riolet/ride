#include "autocompletion.h"

Autocompletion::Autocompletion() {
    numline = 0;
    //if(ritTempFile != 0) fclose(ritTempFile);
    ritTempFile = fopen("rix_temp_file.rit", "w");
    if (ritTempFile == 0) {
        perror("fopen failed");
    }
    HandleImports("rsl/rsl.rit", ritTempFile, &numline);
}


void Autocompletion::Detect (char* ifile) {
    HandleImports(ifile, ritTempFile, &numline);
    std::cout << "Detecting: " << ifile << std::endl;
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



std::vector<Function> Autocompletion::GetFunctions() {
    return functs;
}

std::vector<Class> Autocompletion::GetClasses() {
    return classes;
}

std::string Autocompletion::FormatFunction(Function in) {
    std::string out;
    out = out + in.name;

    return out;
}

std::string Autocompletion::FormatClass(Class in);


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

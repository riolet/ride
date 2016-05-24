#include "autocompletion.h"

void Autocompletion::Detect (char* code) {
  std::regex   funcre(R"(\s*(\w+)\s*->\s*(\w+)\s*\((.*?)\))"),
          classre(R"(^(\w+)\s*(\((.*?)\))?\s*::\s*(\w+))");
  std::regex re(R"((\w+)\s+\w+,?)");
  std::string  line;
  std::smatch  m;
  bool    in_class = false;
  std::string  class_name;
  Class   n_class;
  Function n_function;

  std::stringstream ss(std::string(code));

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

#include "Parser.h"

Parser::Parser(int argc, char* argv[]) {
  m_exec_name = argv[0];
  if (argc > 1) {
    for (int i = 1; i < argc; i++) {
      std::cout << "Arg " << i << ": " << argv[i] << std::endl;
    }
  }
}

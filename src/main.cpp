#include <iostream>

#include "Parser.h"
#include "Path.h"

int main(int argc, char* argv[]) {
  Parser* parser = new Parser(argc, argv);
  Path* path = new Path("/");
  std::cout << "Current working dir: " << path->CWD() << std::endl;
  return 0;
}

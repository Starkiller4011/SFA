#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <string>

class Parser {

public:
  Parser(int , char*[]);

private:
  std::string m_exec_name;
  std::string delimiter;

};

#endif

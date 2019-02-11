#ifndef PARSER_H
#define PARSER_H

#include <string>

namespace sfa {

class Parser {

public:
  // Constructor is dependant on command line args passed to main
  Parser(int , char*[]);
  // Public getters
  inline std::string InputFile() const { return input_file; }
  inline std::string OutputFile() const { return output_file; }
  inline std::string Delimiter() const { return delimiter; }
  inline bool Verbose() const { return verbose_mode; }

private:
  // Parse the command line args passed
  void ParseArgs(int argc, char* argv[]);
  // Get current date in mm-dd-yyyy format
  std::string CurrentDate();

private:
  std::string delimiter;
  std::string input_file;
  std::string output_file;
  bool specified_output;
  bool verbose_mode;

};

}

#endif
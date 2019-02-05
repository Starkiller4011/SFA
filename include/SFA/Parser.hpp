#ifndef PARSER_H
#define PARSER_H

class Parser {

public:
  // Constructor is dependant on command line args passed to main
  Parser(int , char*[]);
  // Returns passed input file, input file is required
  inline std::string InputFile() const { return inputFile; }
  // Returns output file
  inline std::string OutputFile() const { return outputFile; }
  // Returns delimiter
  inline std::string Delimiter() const { return delimiter; }

private:
  // Parse the command line args passed
  void ParseArgs(int argc, char* argv[]);
  // Get current date in mm-dd-yyyy format
  std::string CurrentDate();

private:
  std::string delimiter;
  std::string inputFile;
  std::string outputFile;
  bool specifiedOutput;

};

#endif

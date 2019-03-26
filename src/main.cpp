#include <iostream>
#include <string>

#include "SFA/Parser.h"
#include "SFA/Path.h"
#include "SFA/Lightcurve.h"
#include "SFA/StructureFunction.h"

// Temporary defines
#define StructureFunction sfa::StructureFunction //TODO - Remove and use SFA:: instead
#define Parser sfa::Parser //TODO - Remove and use SFA:: instead
#define Path sfa::Path //TODO - Remove and use SFA:: instead
#define Lightcurve sfa::Lightcurve //TODO - Remove and use SFA:: instead

// Helper function declarations
int RunInVerboseMode(Parser* parser); //TODO - replace with in-function verbose-mode
int RunInQuietMode(Parser* parser); //TODO - replace with in-function verbose-mode

int main(int argc, char* argv[]) {
  int exit_code; // Program exit code
  // Parse args using Parser object
  Parser* parser = new Parser(argc, argv);
  // If verbose run in verbose mode, TODO - replace with in-function verbose-mode
  if (parser->Verbose()) {
    exit_code = RunInVerboseMode(parser);
  } else {
    exit_code = RunInQuietMode(parser);
  }
  delete parser;
  return exit_code;
}

int RunInVerboseMode(Parser* parser) {
  std::cout << "Getting input file path" << std::endl;
  std::string in_path = parser->InputFile(); // TODO - Implement verbose mode in Parser::InputFile
  std::cout << "Getting output file path" << std::endl;
  std::string out_path = parser->OutputFile(); // TODO - Implement verbose mode in Parser::OutputFile
  std::cout << "Creating new Path from " << in_path << std::endl;
  Path InputPath(in_path); // TODO - Implement verbose mode in Path::Path()
  std::cout << "Creating new Path from " << out_path << std::endl;
  Path OutputPath(out_path);
  if(InputPath.IsFile()) {
    std::cout << "Creating new Lightcurve object from " << InputPath.Absolute().string() << std::endl;
    Lightcurve lightcurve(InputPath); // TODO - Implement verbose mode in Lightcurve::Lightcurve()
    std::cout << "Loading lightcurve data" << std::endl;
    lightcurve.LoadData(); // TODO - Implement verbose mode in Lightcurve::LoadData()
    std::cout << "Creating new Structure Function object" << std::endl;
    // TODO - Implement verbose mode in Lightcurve::TimeCol() and Lightcurve::ValueCol()
    StructureFunction sf(lightcurve.TimeCol(), lightcurve.ValueCol(), lightcurve.ErrorCol()); // TODO - Implement verbose mode in StructureFunction::StructureFunction()
    std::cout << "Calculating structure function from data" << std::endl;
    sf.Calculate(); // TODO - Implement verbose mode in StructureFunction::Calculate()
    std::cout << "Writing structure function data to " << OutputPath.Absolute().string() << std::endl;
    sf.WriteToFile(OutputPath); // TODO - Implement verbose mode in StructureFunction::WriteToFile()
    return 0;
  } else {
    std::cout << "Input file: " << InputPath.Absolute() << " does not exist or is not a file" << std::endl;
    return 1;
  }
}

int RunInQuietMode(Parser* parser) {
  std::string in_path = parser->InputFile();
  std::string out_path = parser->OutputFile();
  Path InputPath(in_path);
  Path OutputPath(out_path);
  if(InputPath.IsFile()) {
    Lightcurve lightcurve(InputPath);
    lightcurve.LoadData();
    StructureFunction sf(lightcurve.TimeCol(), lightcurve.ValueCol(), lightcurve.ErrorCol());
    sf.Calculate();
    sf.WriteToFile(OutputPath);
    return 0;
  } else {
    std::cout << "Input file: " << InputPath.Absolute() << " does not exist or is not a file" << std::endl;
    return 1;
  }
}

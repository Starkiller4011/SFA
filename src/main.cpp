#include <iostream>
#include <string>

#include "SFA/Parser.hpp"
#include "SFA/Path.hpp"
#include "SFA/Lightcurve.hpp"
#include "SFA/Collections.hpp"
#include "SFA/StructureFunction.hpp"

int main(int argc, char* argv[]) {
  std::cout << "Parse args" << std::endl;
  Parser* parser = new Parser(argc, argv);
  std::cout << "Get input path from parsed args" << std::endl;
  std::string inPath = parser->InputFile();
  std::cout << "Get output path from parsed args" << std::endl;
  std::string outPath = parser->OutputFile();
  std::cout << "Create new Path object from inPath: " << inPath << std::endl;
  Path InputPath(inPath);
  Path OutputPath(outPath);
  if(InputPath.IsFile()) {
    std::cout << "Create new Lightcurce instance from InputPath: " << InputPath.Absolute() << std::endl;
    Lightcurve lightcurve(InputPath);
    std::cout << "Load data into lightcurve" << std::endl;
    lightcurve.LoadData();
    std::cout << "Generating structure function" << std::endl;
    StructureFunction sf(lightcurve.TimeCol(), lightcurve.ValueCol());
    sf.Calculate();
    sf.WriteToFile(OutputPath);
  } else {
    std::cout << "Input file: " << InputPath.Absolute() << " does not exist or is not a file" << std::endl;
  }
  return 0;
}

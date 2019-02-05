#include <iostream>
#include <string>

#include "SFA/Parser.hpp"
#include "SFA/Path.hpp"
#include "SFA/Lightcurve.hpp"
#include "SFA/Collections.hpp"
#include "SFA/StructureFunction.hpp"

int main(int argc, char* argv[]) {
  Parser* parser = new Parser(argc, argv);
  std::string inPath = parser->InputFile();
  Path InputPath(inPath);
  Lightcurve lightcurve(InputPath);
  lightcurve.LoadData();
  int n = lightcurve.TimeCol().Size();
  for(int i = 0; i < n; i++) {
    std::cout << i << ": " << lightcurve.TimeCol().GetAtIndex(i) << std::endl;
  }
  StructureFunction sf(lightcurve.TimeCol(), lightcurve.ValueCol());
  sf.Calculate();
  return 0;
}

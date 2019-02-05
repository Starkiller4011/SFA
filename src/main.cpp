#include <iostream>
#include <string>

#include "SFA/Parser.hpp"
#include "SFA/Path.hpp"
#include "SFA/Lightcurve.hpp"
#include "SFA/Collections.hpp"

int main(int argc, char* argv[]) {
  Parser* parser = new Parser(argc, argv);
  Path InputPath(parser->InputFile());
  int testNumbers[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
  std::cout << "Array: [ " << testNumbers[0];
  for(int i = 1; i < 10; i++) {
    std::cout << ", " << testNumbers[i];
  }
  std::cout << " ]" << std::endl;
  List<int> myList;
  for(int i = 0; i < 10; i++) {
    std::cout << "Appending: " << testNumbers[9 - i] << std::endl;
    myList.Append(testNumbers[9 - i]);
  }
  std::cout << "List size: " << myList.Size() << std::endl;
  int n = myList.Size();
  std::cout << "Testing GetFirst: " << myList.GetFirst() << std::endl;
  std::cout << "Testing GetLast: " << myList.GetLast() << std::endl;
  std::cout << "Testing RemoveFirst:" << std::endl;
  List<int> newList;
  for(int i = 0; i < n; i++) {
    int tmp = myList.RemoveFirst();
    newList.Append(tmp);
    std::cout << "Element at index " << i << ": " << tmp << std::endl;
  }
  n = newList.Size();
  std::cout << "Testing RemoveLast:" << std::endl;
  for(int i = 0; i < n; i++) {
    int tmp = newList.RemoveLast();
    std::cout << "Element at index " << i << ": " << tmp << std::endl;
  }
  // std::cout << "CWD: " << fs::current_path().string() << std::endl;
  // std::cout << "InputPath Abs Path: " << InputPath.Absolute().string() << std::endl;
  // std::cout << "InputPath Rel Path: " << InputPath.Relative().string() << std::endl;
  // if(InputPath.IsFile()) {
  //   std::cout << "Input is file: " << InputPath.Absolute().filename() << std::endl;
  // } else {
  //   std::cout << "Input is directory: " << InputPath.Absolute().string() << std::endl;
  // }
  return 0;
}

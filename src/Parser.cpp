#include <iostream>
#include <algorithm>
#include <string>
#include <ctime>

#include "SFA/Parser.h"
#include "SFA/Help.h"

namespace sfa {

// Class constructor
Parser::Parser(int argc, char* argv[]) {
  // Set defaul values
  delimiter = "\0";
  specified_output = false;
  verbose_mode = false;
  // If args were passed parse args
  if (argc > 1) {
    ParseArgs(argc, argv);
  } else {
  // Else inform user of usage and exit
    PrintHelp();
  }
}

// Parse args
void Parser::ParseArgs(int argc, char* argv[]) {
  int usedArgs = 0; // Tally of user passed args
  // For each passed arg
  for (int i = 1; i < argc; i++) {
    // Convert to string
    std::string arg = argv[i];
    // If user is setting delimiter
    if ((arg == "-d") || (arg == "--delimiter")) {
      // Set delimiter to next arg as required and increment i to skip to next arg
      // TODO - handle possibility of '-d' improper usage
      delimiter = argv[i + 1];
      usedArgs += 2;
      i++;
    } else if((arg == "-o") || (arg == "--output")) {
      // Set output file to passed option and increment i to skip to next arg
      // TODO - handle possibility of '-o' improper usage
      specified_output = true;
      output_file = argv[i + 1];
      usedArgs += 2;
      i++;
    } else if((arg == "-v") || (arg == "--verbose")) {
      // Verbose mode flag
      verbose_mode = true;
      usedArgs++;
    }
  }
  // If there are still args left after user passed options
  if(usedArgs < (argc - 1)) {
    // Set the input file
    input_file = argv[argc - 1];
  } else {
  // Else inform user of usage and exit
    std::cout << "usage " << argv[0] << " [options] input_file" << std::endl;
    exit(1); //TODO - Standardize exit codes to be meaningful, currently all are 1 or 0 if no errors
  }
  // If the user did not set a specific output file
  if(!specified_output) {
    // Get current date in format mm-dd-yyyy
    std::string currentDate = CurrentDate();
    // Get current filename without extension
    std::string input_filename = input_file.substr(0, input_file.find("."));
    std::cout << input_filename << std::endl;
    // Set ouput file to SFA-[input]-[date].out
    output_file = input_filename + "-" + currentDate + ".out";
    std::cout << output_file << std::endl;
  }
}

// Gets current date
std::string Parser::CurrentDate() {
  // Initialize date string
  std::string date = "";
  // Get current datetime
  std::time_t now = time(0);
  // Set localtime
  tm *ltm = localtime(&now);
  // Get month day and year
  int month = 1 + ltm->tm_mon;
  int day = ltm->tm_mday;
  int year = 1900 + ltm->tm_year;
  // If month is less than 10 prepend a 0
  if(month < 10) {
    date += "0";
  }
  date += std::to_string(month);
  date += "-";
  // If day is less than 10 prepend a 0
  if(day < 10) {
    date += "0";
  }
  date += std::to_string(day);
  date += "-";
  date += std::to_string(year);
  return date;
}

}
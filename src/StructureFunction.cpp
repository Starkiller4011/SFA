#include <iostream>
#include <fstream>
#include <cmath>

#include "SFA/StructureFunction.h"

namespace sfa {

  StructureFunction::StructureFunction(std::vector<double> const _timeCol, std::vector<double> const _valueCol, std::vector<double> const _errorCol) {
    timeCol = _timeCol;
    valueCol = _valueCol;
    errorCol = _errorCol;
    T = timeCol.back() - timeCol.front();
    GetResolution();
    nBins = (int)(T / (delta + 1));
    std::cout << "Duration: " << T << ", Resolution: " << delta << ", Bins: " << nBins << std::endl;
  }

  void StructureFunction::Calculate() { // TODO - Fix nullptr bug, somewhere in here we get a core dump, was this fixed?
  // TODO - Subtract 2 times the mean variance of the measurement uncertainties
  // TODO - Generate error estimates on the structure function following sigma/N/2 root
    int N = timeCol.size();
    for(int i = 0; i < (N - 1); i++) {
      for(int j = i; j < N; j++) {
        double tau = timeCol[j] - timeCol[i];
        if(tau > 0) {
          std::map<double, std::vector<double>>::iterator it = interim.find(tau);
          if(it != interim.end()) {
            it->second.push_back(std::pow((valueCol[j] - valueCol[i]), 2));
          } else {
            std::vector<double> tmp;
            tmp.push_back(std::pow((valueCol[j] - valueCol[i]), 2));
            interim.insert({tau, tmp});
          }
        }
      }
    }
    for(auto it = interim.begin(); it != interim.end(); it++) {
      double sum = 0.0;
      for(unsigned int i = 0; i < it->second.size(); i++) {
        sum += it->second[i];
      }
      structure_function.insert({it->first, sum});
    }
  }

  void StructureFunction::GetResolution() {
    int N = timeCol.size();
    int count = 0;
    delta = 0;
    for(int i = 1; i < N; i++) {
      delta += (timeCol[i] - timeCol[i -1]);
      count++;
    }
    delta /= count;
  }

  void StructureFunction::WriteToFile(Path outfilePath) const {
    std::cout << "Writing to file " << outfilePath.Absolute().string() << std::endl;
    std::ofstream outFile;
    outFile.open(outfilePath.Absolute());
    for(auto it = structure_function.begin(); it != structure_function.end(); it++) {
      outFile << it->first << "\t" << it->second << std::endl;
    }
    outFile.close();
  }

}

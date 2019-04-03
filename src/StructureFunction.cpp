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
    nBins = (int)(T / (delta + 1));
    GetResolution();
    std::cout << "Duration: " << T << ", Resolution: " << delta << ", Bins: " << nBins << std::endl;
  }

  void StructureFunction::Calculate() {
    std::cout << "Initializing maps" << std::endl;
    InitializeMaps();
    std::cout << "Subtracting linear fit" << std::endl;
    SubtractLinearFit(); // TODO - Fix this, currently manually inputing linear fit
    std::cout << "Sorting measurement uncertainties" << std::endl;
    SortUncertainties();
    std::cout << "Calculating raw structure function values" << std::endl;
    CalculateRawValues();
    std::cout << "Binning structure function and uncertainty values" << std::endl;
    BinSF();
    std::cout << "Caluclating final structure function value" << std::endl;
    // Calculate the binned structure function values
    for(auto btau = binned_structure_function.begin(); btau != binned_structure_function.end(); btau++) {
      double sf = 0;
      double eavg = 0;
      double sigma = 0;
      auto vit = binned_structure_function_interim.find(btau->first);
      auto eit = binned_errors.find(btau->first);
      int N_e = eit->second.size();
      for(int i = 0; i < N_e; i++) {
        eavg += eit->second[i];
      }
      eavg /= N_e;
      for(int i = 0; i < N_e; i++) {
        sigma += std::pow((eit->second[i] - eavg), 2);
      }
      sigma /= N_e;
      int N_tau = vit->second.size();
      for(int i = 0; i < N_tau; i++) {
        sf += vit->second[i];
      }
      sf /= N_tau;
      sf -= sigma;
      btau->second = sf;
    }
    std::cout << "Caluclating final structure function uncertainty" << std::endl;
    // Calculate the structure function uncertainty
    for(auto btau = structure_function_error.begin(); btau != structure_function_error.end(); btau++) {
      auto sfit = binned_structure_function_interim.find(btau->first);
      double sfav = 0;
      int N_i = sfit->second.size();
      for(int i = 0; i < N_i; i++) {
        sfav += sfit->second[i];
      }
      //std::cout << "sfav: " << sfav;
      sfav /= N_i;
      //std::cout << ", sfav: " << sfav <<std::endl;
      double rms = 0;
      for(int i = 0; i < N_i; i++) {
        rms += std::pow((sfit->second[i] - sfav), 2);
      }
      rms = std::sqrt(rms / N_i);
      //std::cout << "N_i: " << N_i << ", rms: " << rms << std::endl;
      double error = rms / std::sqrt(N_i / 2);
      btau->second = error;
    }
  }

  // Get structure function resulution delta
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

  // Initialize the binned structure function and error maps
  void StructureFunction::InitializeMaps() {
    double T = timeCol.back() - timeCol.front();
    int lastBin = T / (delta + 1);
    for(int i = 1; i <= lastBin; i++) {
      std::vector<double> tmp;
      std::vector<double> etmp;
      double midpoint = (i - (1/2)) * delta;
      binned_structure_function.insert({midpoint, 0});
      binned_errors.insert({midpoint, etmp});
      binned_structure_function_interim.insert({midpoint, tmp});
      structure_function_error.insert({midpoint, 0});
    }
  }

  // Subtract a linear fit from the data to remove artificial steepening
  void StructureFunction::SubtractLinearFit() {
    double B0 = -2.71599448495183e-7;
    double B1 = 1.64427967530241e-11;
    double B2 = -3.31280436595384e-16;
    double B3 = 2.22159804429092e-21;
    int N = valueCol.size();
    for(int i = 0; i < N; i++) {
      //std::cout << "Index: " << i << std::endl;
      double predicted = B0 + (B1 * timeCol[i]) + (B2 * std::pow(timeCol[i], 2)) + (B3 * std::pow(timeCol[i], 3));
      valueCol[i] -= predicted;
    }
  }

  // Sort measurement uncertainties based on tau
  void StructureFunction::SortUncertainties() {
    int N_e = errorCol.size();
    for(int i = 0; i < (N_e - 1); i++) {
      for(int j = i; j < N_e; j++) {
        double tau = timeCol[j] - timeCol[i];
        if(tau > 0) {
          std::map<double, std::vector<double>>::iterator eit = errors.find(tau);
          if(eit != errors.end()) {
            eit->second.push_back(errorCol[i]);
            eit->second.push_back(errorCol[j]);
          } else {
            std::vector<double> tmp;
            tmp.push_back(errorCol[i]);
            tmp.push_back(errorCol[j]);
            errors.insert({tau, tmp});
          }
        }
      }
    }
  }

  // Sort squared measurement differences based on tau
  void StructureFunction::CalculateRawValues() {
    int N_v = timeCol.size();
    for(int i = 0; i < (N_v - 1); i++) {
      for(int j = i; j < N_v; j++) {
        double tau = timeCol[j] - timeCol[i];
        if(tau > 0) {
          std::map<double, std::vector<double>>::iterator vit = interim.find(tau);
          if(vit != interim.end()) {
            vit->second.push_back(std::pow((valueCol[j] - valueCol[i]), 2));
          } else {
            std::vector<double> tmp;
            tmp.push_back(std::pow((valueCol[j] - valueCol[i]), 2));
            interim.insert({tau, tmp});
          }
        }
      }
    }
    // Caluculate the raw structure function values
    for(auto it = interim.begin(); it != interim.end(); it++) {
      double sf = 0;
      for(long unsigned int i = 0; i < it->second.size(); i++) {
        sf += it->second[i];
      }
      sf /= it->second.size();
      raw_structure_function.insert({it->first, sf});
    }
  }

  void StructureFunction::BinSF() {
    // Bin the structure function
    for(auto btau = binned_structure_function_interim.begin(); btau != binned_structure_function_interim.end(); btau++) {
      for(auto it = raw_structure_function.begin(); it != raw_structure_function.end(); it++) {
        if((it->first > (btau->first - (delta / 2))) && (it->first <= (btau->first + (delta / 2)))) {
          btau->second.push_back(it->second);
        }
      }
    }
    // Bin the errors
    for(auto btau = binned_errors.begin(); btau != binned_errors.end(); btau++) {
      for(auto it = errors.begin(); it != errors.end(); it++) {
        if((it->first > (btau->first - (delta / 2))) && (it->first <= (btau->first + (delta / 2)))) {
          for(long unsigned int i = 0; i < it->second.size(); i++) {
            btau->second.push_back(it->second[i]);
          }
        }
      }
    }
  }

  // Write structure function to file
  void StructureFunction::WriteToFile(Path outfilePath) const {
    std::cout << "Writing to file " << outfilePath.Absolute().string() << std::endl;
    std::ofstream outFile;
    outFile.open(outfilePath.Absolute());
    outFile << "Tau,SF,+-" << std::endl;
    for(auto vit = binned_structure_function.begin(); vit != binned_structure_function.end(); vit++) {
      auto eit = structure_function_error.find(vit->first);
      outFile << vit->first << "," << vit->second << "," << eit->second << std::endl;
    }
    outFile.close();
  }

}

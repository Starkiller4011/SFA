#ifndef STRUCTUREFUNCTION_H
#define STRUCTUREFUNCTION_H

#include <map>
#include <vector>
#include "Path.h"

namespace sfa {

    class StructureFunction {
        
    public:
        StructureFunction(std::vector<double> const, std::vector<double> const, std::vector<double> const);
        void Calculate();
        inline double Resolution() const { return delta; }
        void WriteToFile(Path) const;

    private:
        void GetResolution();
        void InitializeMaps();
        void SubtractLinearFit();
        void SortUncertainties();
        void CalculateRawValues();
        void BinSF();

    private:
        int nBins;
        double delta;
        double T;
        std::vector<double> timeCol;
        std::vector<double> valueCol;
        std::vector<double> errorCol;
        std::map<double, std::vector<double>> errors;
        std::map<double, std::vector<double>> interim;

        std::map<double, double> raw_structure_function;
        std::map<double, std::vector<double>> binned_structure_function_interim;
        std::map<double, std::vector<double>> binned_errors;

        std::map<double, double> binned_structure_function;
        std::map<double, double> structure_function_error;

    };

}

#endif
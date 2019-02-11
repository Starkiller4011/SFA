#ifndef STRUCTUREFUNCTION_H
#define STRUCTUREFUNCTION_H

#include <map>
#include <vector>
#include "Path.h"

namespace sfa {

    class StructureFunction {
        
    public:
        StructureFunction(std::vector<double> const, std::vector<double> const);
        void Calculate();
        inline double Resolution() const { return delta; }
        void WriteToFile(Path) const;

    private:
        void GetResolution();

    private:
        int nBins;
        double delta;
        double T;
        std::vector<double> timeCol;
        std::vector<double> valueCol;
        std::map<double,std::vector<double>> interim;
        std::map<double, double> structure_function;

    };

}

#endif
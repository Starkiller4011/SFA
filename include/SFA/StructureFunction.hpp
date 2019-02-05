#ifndef STRUCTUREFUNCTION_H
#define STRUCTUREFUNCTION_H

#include "SFA/Collections.hpp"

class StructureFunction {

public:
    StructureFunction(List<double> const, List<double> const);
    void Calculate();
    inline double Resolution() const { return delta; }

private:
    void GetResolution();

private:
    int nBins;
    double delta;
    double T;
    List<double> timeCol;
    List<double> valueCol;
    List<double> taus;
    List<double> sqDiff;

};

#endif
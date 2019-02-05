#include <iostream>
#include <cmath>

#include "SFA/StructureFunction.hpp"

StructureFunction::StructureFunction(List<double> const _timeCol, List<double> const _valueCol) {
    timeCol = _timeCol;
    valueCol = _valueCol;
    T = timeCol.GetLast() - timeCol.GetFirst();
    GetResolution();
    nBins = (int)(T / (delta + 1));
    std::cout << "Duration: " << T << ", Resolution: " << delta << ", Bins: " << nBins << std::endl;
}

void StructureFunction::Calculate() {
    int N = timeCol.Size();
    for(int i = 0; i < (N - 1); i++) {
        for(int j = i; j < N; j++) {
            std::cout << "i: " << i << ", j: " << j << std::endl;
            taus.Append(timeCol.GetAtIndex(j) - timeCol.GetAtIndex(i));
            sqDiff.Append(std::pow((valueCol.GetAtIndex(j) - valueCol.GetAtIndex(i)), 2));
        }
    }
    taus.Print();
    sqDiff.Print();
}

void StructureFunction::GetResolution() {
    int N = timeCol.Size();
    int count = 0;
    delta = 0;
    for(int i = 1; i < N; i++) {
        delta += (timeCol.GetAtIndex(i) - timeCol.GetAtIndex(i -1));
        count++;
    }
    delta /= count;
}
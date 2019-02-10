#include <string>
#include <fstream>
#include <iostream>

#include "SFA/Path.hpp"
#include "SFA/Lightcurve.hpp"

Lightcurve::Lightcurve(Path _path) {
    datafilePath = _path;
}

void Lightcurve::LoadData() {
    std::ifstream dataFile;
    dataFile.open(datafilePath.Absolute());
    double t, v;
    // TODO - Implement handling for files with an extra empty line at the end
    while(!dataFile.eof()) {
        dataFile >> t;
        dataFile >> v;
        timeCol.push_back(t);
        valueCol.push_back(v);
    }
}

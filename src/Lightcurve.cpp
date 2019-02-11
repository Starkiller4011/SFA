#include <string>
#include <fstream>
#include <iostream>

#include "SFA/Path.h"
#include "SFA/Lightcurve.h"

namespace sfa {

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

}

#include <string>
#include <fstream>

#include "SFA/Path.hpp"
#include "SFA/Lightcurve.hpp"

Lightcurve::Lightcurve(Path _path) {
    datafilePath = _path;
}

void Lightcurve::LoadData() {
    std::ifstream dataFile;
    dataFile.open(datafilePath.Absolute());
    double t, v;
    while(!dataFile.eof()) {
        dataFile >> t;
        dataFile >> v;
        timeCol.Append(t);
        valueCol.Append(v);
    }
}

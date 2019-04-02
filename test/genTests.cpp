#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>
#include <map>

int randomIntInRange(int begin, int end);
double GenerateValue(double generator);
double GenerateDifference(double resolution);
double GenerateUncertainty();

const int MIN_RES = 1;
const int MAX_RES = 14;

int main(int argc, char* argv[]) {
    int lines;
    int files;
    std::srand(time(NULL));
    if (argc > 2) {
        std::string arg = argv[2];
        try {
            std::size_t pos;
            lines = std::stoi(arg, &pos);
            if (pos < arg.size()) {
                std::cerr << "Trailing characters after number: " << arg << std::endl;
            }
        } catch (std::invalid_argument const &ex) {
            std::cerr << "Invalid number: " << arg << std::endl;
        } catch (std::out_of_range const &ex) {
            std::cerr << "Number out of range: " << arg << std::endl;
        }
        arg = argv[1];
        try {
            std::size_t pos;
            files = std::stoi(arg, &pos);
            if (pos < arg.size()) {
                std::cerr << "Trailing characters after number: " << arg << std::endl;
            }
        } catch (std::invalid_argument const &ex) {
            std::cerr << "Invalid number: " << arg << std::endl;
        } catch (std::out_of_range const &ex) {
            std::cerr << "Number out of range: " << arg << std::endl;
        }
    } else if (argc > 1) {
        std::string arg = argv[1];
        try {
            std::size_t pos;
            files = std::stoi(arg, &pos);
            if (pos < arg.size()) {
                std::cerr << "Trailing characters after number: " << arg << std::endl;
            }
        } catch (std::invalid_argument const &ex) {
            std::cerr << "Invalid number: " << arg << std::endl;
        } catch (std::out_of_range const &ex) {
            std::cerr << "Number out of range: " << arg << std::endl;
        }
        lines = randomIntInRange(0, 2000);
    } else {
        lines = randomIntInRange(0, 2000);
        files = randomIntInRange(0, 10);
    }
    std::cout << "Generating test input files..." << std::endl;
    for (int i = 0; i < files; i++) {
        std::string filename;
        std::cout << i << ": ";
        if (i < 10) {
            filename = "test/test.0" + std::to_string(i) + ".in";
        } else {
            filename = "test/test." + std::to_string(i) + ".in";
        }
        std::cout << filename << std::endl;
        std::ofstream outFile;
        outFile.open(filename);
        double duration = randomIntInRange(300000, 600000) / randomIntInRange(10, 100);
        double res = duration / lines;
        double time_value = 0;
        std::vector<double> differences;
        std::map<double, double> values;
        std::map<double, double> errors;
        for(int j = 0; j < lines; j++) {
            double remaining = duration - time_value;
            double resolution = remaining / (lines - j);
            double difference = GenerateDifference(resolution);
            differences.push_back(difference);
            time_value += difference;
        }
        std::random_shuffle(differences.begin(), differences.end());
        time_value = 0;
        for(unsigned int index = 0; index < differences.size(); index++) {
            values.insert({time_value, 0});
            errors.insert({time_value, 0});
            time_value += differences[i];
        }
        for(auto vit = values.begin(); vit != values.end(); vit++) {
            auto eit = errors.find(vit->first);

        }
        std::cout << "Done!" << std::endl;
    }
    return 0;
}

int randomIntInRange(int begin, int end) {
    int result = rand() % (end - begin);
    result += begin;
    return result;
}

double GenerateValue(double generator) {
    double result = std::sin(generator);
    result += (4 * std::sin(generator / 2));
    result += (2 * std::sin((-1 * generator) / 4));
    result += (1.5 * std::sin(generator / 50));
    result += std::cos(generator);
    result += (8 * std::cos((-1 * generator) / 4));
    result /= 1e12;
    return result;
}

double GenerateDifference(double resolution) {
    int upper = (int)(10 * resolution);
    int lower = (int)(resolution);
    int tmp = randomIntInRange(lower, upper);
    return tmp / 5;
}

double GenerateUncertainty() {
    return randomIntInRange(1, 1000) / 1e14;
}

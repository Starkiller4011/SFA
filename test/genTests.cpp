#include <stdexcept>
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <string>
#include <time.h>

int randomIntInRange(int begin, int end);

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
        for (int i = 0; i < lines; i++) {
            int begin = 6 * i;
            int end = (6 * i) + 6;
            int time_value = randomIntInRange(begin, end);
            int value = randomIntInRange(0, 1357608741);
            outFile << time_value << "    " << value << std::endl;
        }
    }
    return 0;
}

int randomIntInRange(int begin, int end) {
    int result = rand() % (end - begin);
    result += begin;
    return result;
}

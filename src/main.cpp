#include <iostream>
#include <fstream>
#include <string>

#include "photon/executor/executor.hpp"
#include "photon/parser/photon_parser.hpp"

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        std::cerr << "Missing file argument" << std::endl;
        return 1;
    }
    std::string line;
    std::string filename = argv[1];
    std::ifstream myfile {argv[1]};
    if (!myfile.is_open()) {
        std::cerr << "Unable to open file" << std::endl;
        return 1;
    }

    try {
        photon::parser::StrixParser aParser;
        while (getline(myfile, line)) {
            aParser.parseLine(line);
        }
        myfile.close();

        photon::executor::Executor anExecutor;
        anExecutor.execute(aParser);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

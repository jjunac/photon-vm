#include <iostream>
#include <fstream>
#include <string>

#include "strix/executor/executor.hpp"
#include "strix/parser/strix_parser.hpp"

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
        strix::parser::StrixParser aParser;
        while (getline(myfile, line)) {
            aParser.parseLine(line);
        }
        myfile.close();

        strix::executor::Executor anExecutor;
        anExecutor.execute(aParser);
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}

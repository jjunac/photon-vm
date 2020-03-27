#include <iostream>
#include <fstream>
#include <string>

#include "strix/executor/executor.hpp"
#include "strix/parser/parser.hpp"

int main(int argc, char const *argv[]) {
    if (argc != 2) {
        std::cerr << "Missing file argument" << std::endl;
        return 1;
    }
    std::string line;
    std::ifstream myfile (argv[1]);
    if (!myfile.is_open()) {
        std::cout << "Unable to open file" << std::endl; 
        return 1;
    }

    strix::parser::Parser aParser;
    while (getline(myfile, line)) {
        // std::cout << line << std::endl;
        aParser.parseLine(line);
    }
    myfile.close();

    strix::executor::Executor anExecutor;
    anExecutor.execute(aParser);

    return 0;
}

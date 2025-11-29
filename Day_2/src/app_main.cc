#include "../include/resource_handler.h"

#include <iostream>
#include <fstream>
#include <string>

int main(int argc, char *argv[]) {
    // handle params.
    if(argc != 2) {
        std::cout << "ERROR: Please supply path to input file and nothing else." << std::endl;
        return 1;
    }
    std::string input_file = argv[1];

    ResourceHandler resource_handler;
    // load input reasource
    std::ifstream file(input_file);
    std::string file_line;
    while(std::getline(file, file_line)) {
        resource_handler.AddNewResourceLine(file_line);
    }

    bool use_problem_dampener = false;
    std::cout << "The number of safe levels is: " << resource_handler.GetNumOfSafeLevels(use_problem_dampener) << std::endl;
    
    use_problem_dampener = true;
    std::cout << "The number of safe levels with the problem dampener is: " << resource_handler.GetNumOfSafeLevels(use_problem_dampener) << std::endl;

    return 0;
}
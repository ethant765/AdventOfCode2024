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

    ResourceHandler resourceHandler;

    // load input reasource
    std::ifstream file(input_file);
    std::string file_line;
    while(std::getline(file, file_line)) {
        resourceHandler.AddResource(file_line);
    }

    std::cout << "The total of uncorrupted data multiplications is: " << resourceHandler.GetTotalMultiplications() << std::endl;

    return 0;
}
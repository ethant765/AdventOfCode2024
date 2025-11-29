#include "../include/resource_handler.h"

#include <iostream>
#include <fstream>
#include <string>
#include <memory>

int main(int argc, char *argv[]) {
    // handle params.
    if(argc != 2) {
        std::cout << "ERROR: Please supply path to input file and nothing else." << std::endl;
        return 1;
    }
    std::string input_file = argv[1];

    std::unique_ptr<ResourceHandler> resourceHandler = std::make_unique<ResourceHandler>();

    // load input reasource
    std::ifstream file(input_file);
    std::string file_line;
    while(std::getline(file, file_line)) {
        resourceHandler->AddResource(file_line);
    }

    std::cout << "The total of uncorrupted data multiplications is: " << resourceHandler->GetTotalMultiplications() << std::endl;
    std::cout << "The total value with the additional conditional statements is: " << resourceHandler->GetMultiplicationWithConditionals() << std::endl;

    return 0;
}
#include "../include/resource_handler.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <memory>

int main(int argc, char *argv[]) {
    // handle params.
    if(argc != 2) {
        std::cout << "ERROR: Please supply path to input file and nothing else." << std::endl;
        return 1;
    }
    std::string input_file = argv[1];

    // load input reasource
    std::ifstream file(input_file);
    std::string file_line;
    // we want 1 long string for this challenge.
    std::stringstream strstr;
    while(std::getline(file, file_line)) {
        strstr << file_line;
    }

    std::unique_ptr<day_three::ResourceHandler> resourceHandler = std::make_unique<day_three::ResourceHandler>();
    resourceHandler->AddResource(strstr.str());
    std::cout << "The total of uncorrupted data multiplications is: " << resourceHandler->GetTotalMultiplications() << std::endl;
    std::cout << "The total value with the additional conditional statements is: " << resourceHandler->GetMultiplicationWithConditionals() << std::endl;

    return 0;
}
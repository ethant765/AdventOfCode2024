#include "../include/resource_handler.h"

#include <iostream>
#include <fstream>
#include <string>
#include <memory>

int main(int argc, char *argv[]) {
    // handle params.
    if(argc != 2) {
        std::cout << "ERROR: Please supply path to input file, Nothing else." << std::endl;
        return 1;
    }
    std::string input_file = argv[1];

    std::unique_ptr<day_seven::ResourceHandler> resource_handler = std::make_unique<day_seven::ResourceHandler>();
    // load input reasource
    std::ifstream file(input_file);
    std::string file_line;
    while(std::getline(file, file_line)) {
        resource_handler->AddResource(file_line);
    }

    std::cout << "The sum result of day seven challenge one is: " << resource_handler->GetChallengeOneSum() << std::endl;

    return 0;
}
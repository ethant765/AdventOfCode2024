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

    std::unique_ptr<day_six::ResourceHandler> resource_handler = std::make_unique<day_six::ResourceHandler>();

    // load input reasource
    std::ifstream file(input_file);
    std::string file_line;
    while(std::getline(file, file_line)) {
        resource_handler->AddLineToMap(file_line);
    }

    resource_handler->PredictPositions();
    std::cout << "Number of distinct positions is: " << resource_handler->CountDistinctPositions() << std::endl;
    std::cout << "Number of Obstacle locations that will cause a guard loop: " << resource_handler->CountNumberOfLoopObstacles() << std::endl;

    return 0;
}
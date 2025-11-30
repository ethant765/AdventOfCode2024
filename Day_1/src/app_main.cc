#include "../include/resource_holder.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <cstdint>

int main(int argc, char *argv[]) {
    // handle params.
    if(argc != 2) {
        std::cout << "ERROR: Please supply path to input file and nothing else." << std::endl;
        return 1;
    }
    std::string input_file = argv[1];

    day_one::ResourceHolder resource_holder;
    
    // load input reasource
    std::ifstream file(input_file);
    std::string file_line;
    while(std::getline(file, file_line)) {
        std::stringstream strstr(file_line);
        uint32_t num1 = 0;
        uint32_t num2 = 0;
        if(strstr >> num1 >> num2) {
            resource_holder.AddToListOne(num1);
            resource_holder.AddToListTwo(num2);
        } else {
            std::cout << "ERROR: Failed to parse line: " << file_line << std::endl;
        }
    }

    resource_holder.OrderLists();
    std::cout << "Total distance to be travelled is: " << resource_holder.GetTotalDistance() << std::endl;
    std::cout << "The similarity score between the two lists is: " << resource_holder.GetSimilarityScore() << std::endl;
    return 0;
}
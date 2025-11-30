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

    std::unique_ptr<day_five::ResourceHandler> resource_handler = std::make_unique<day_five::ResourceHandler>();

    // load input reasource
    std::ifstream file(input_file);
    std::string file_line;
    bool rules_processed = false;
    while(std::getline(file, file_line)) {
        // all rules at the top of the file, followed by an empty line then all page orderings
        if(file_line.empty()) {
            rules_processed = true;
        } else if (!rules_processed) {
            resource_handler->AddNewRule(file_line);
        } else {
            resource_handler->AddNewPageOrdering(file_line);
        }
    }

    //resource_handler->Print();

    std::cout << "The total value of middle numbers of the valid page orderings is: " << resource_handler->GetMiddlePageSum() << std::endl;

    return 0;
}
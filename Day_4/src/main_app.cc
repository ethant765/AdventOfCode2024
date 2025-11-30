#include "../include/word_processor.h"

#include <iostream>
#include <fstream>
#include <string>
#include <memory>

int main(int argc, char *argv[]) {
    // handle params.
    if(argc != 3) {
        std::cout << "ERROR: Please supply path to input file, then the name of the word you are searching for. Nothing else." << std::endl;
        return 1;
    }
    std::string input_file = argv[1];
    std::string word_to_find = argv[2];
    std::unique_ptr<WordProcessor> word_processor = std::make_unique<WordProcessor>(word_to_find);
    // load input reasource
    std::ifstream file(input_file);
    std::string file_line;
    while(std::getline(file, file_line)) {
        word_processor->AddWordSearchRow(file_line);
    }
    std::cout << "The number of times word '" << word_to_find << "' is found in provided word search is: " << word_processor->FindXMAS() << std::endl;
    word_processor->PrintWordSearchSolution();

    return 0;
}
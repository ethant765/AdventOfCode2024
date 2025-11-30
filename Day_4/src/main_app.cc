#include "../include/word_processor.h"

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
    std::unique_ptr<WordProcessor> word_processor = std::make_unique<WordProcessor>();
    // load input reasource
    std::ifstream file(input_file);
    std::string file_line;
    while(std::getline(file, file_line)) {
        word_processor->AddWordSearchRow(file_line);
    }

    std::cout << "The number of times word 'XMAS' is found in provided word search is: " << word_processor->FindWord("XMAS") << std::endl;
    //word_processor->PrintWordSearchSolution();

    std::cout << "The number of times the cross of word 'MAS' is found in provided word search is: " << word_processor->FindCrossOfMAS() << std::endl;

    return 0;
}
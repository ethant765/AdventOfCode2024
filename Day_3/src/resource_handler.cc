#include "../include/resource_handler.h"

#include <iostream>
#include <string>
#include <regex>
#include <utility>
#include <cstdint>

void ResourceHandler::AddResource(const std::string& input) {
    std::regex mul_pattern(kRegexMatcher);
    std::regex num_pattern(kNumRegexMatcher);

    std::sregex_iterator iter(input.begin(), input.end(), mul_pattern);
    std::sregex_iterator end;

    // loop through all multiples within passed string
    while(iter != end) {
        for(size_t i = 0; i < iter->size(); ++i) {

            // break all multiple substrings into integer pairs
            std::string mul_str = (*iter)[i];
            std::sregex_iterator num_iter(mul_str.begin(), mul_str.end(), num_pattern);
            std::sregex_iterator num_end;

            if(num_iter->size() != 2) {
                std::cout << "ERROR: unexpected number of multipliers found!" << std::endl;
                return;
            }
            int one = std::stoi((*num_iter)[0]);
            ++num_iter;
            int two = std::stoi((*num_iter)[0]);
            std::pair<int, int> new_vals(one, two);
            values_.push_back(new_vals);
        }
        ++iter;
    }
}

uint64_t ResourceHandler::GetTotalMultiplications() {
    uint64_t total = 0;
    for(std::pair<int, int> vals : values_) {
        total += (vals.first * vals.second);
    }
    return total;
}

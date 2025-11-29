#include "../include/resource_handler.h"

#include <sstream>
#include <iostream>

void ResourceHandler::AddNewResourceLine(const std::string& line) {
    std::stringstream strstr(line);
    uint16_t val;
    std::vector<uint16_t> new_line_values;
    while(strstr >> val) {
        new_line_values.push_back(val);
    }
    resources_.push_back(new_line_values);
}

uint32_t ResourceHandler::GetNumOfSafeLevels() {
    uint32_t safe_levels = 0;
    for(size_t i = 0; i < resources_.size(); i++) {
        if(ValidateLine(resources_[i])) {
            safe_levels++;
        }
    }
    return safe_levels;
}

bool ResourceHandler::ValidateLine(const std::vector<uint16_t>& line) {
    bool increasing = false;
    bool decreasing = false;
    bool within_safe_bounds = true;

    // loop through passed vector, getting two values at a time, and checking they match requirements for being safe
    for(size_t curr_index = 0; (curr_index < line.size() - 1); curr_index++) {
        uint16_t current_val = line[curr_index];
        uint16_t next_val = line[curr_index + 1];

        if(current_val == next_val) {
            return false;
        } else if (current_val > next_val) {
            decreasing = true;
            within_safe_bounds = TestWithinBounds(next_val, current_val);
        } else if (current_val < next_val) {
            increasing = true;
            within_safe_bounds = TestWithinBounds(current_val, next_val);
        }

        if((increasing && decreasing) || !within_safe_bounds) {
            return false;
        }
    }

    return true;
}

bool ResourceHandler::TestWithinBounds(const uint16_t smaller_val, const uint16_t larger_val) {
    if((smaller_val == larger_val) || (smaller_val > larger_val)) {
        std::cout << "ERROR: Invalid values passed for bound comparrison. End result likely incorrect." << std::endl;
        return false;
    }

    // calculate if passed values are within the safe boundary values
    uint8_t difference = larger_val - smaller_val;
    if(difference > kMaxDiff) {
        return false;
    } else if ( difference < kMinDiff) {
        return false;
    }
    return true;
}
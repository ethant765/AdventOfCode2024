#include "../include/resource_handler.h"

#include <cstdint>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include <stdexcept>

namespace day_seven {

    void ResourceHandler::AddResource(const std::string& new_line) {
        input_holder_ new_input;
        std::vector<uint64_t> new_values;

        size_t delimiter_index = new_line.find(kInputDelimiter);
        if(delimiter_index == std::string::npos) {
            std::cout << "ERROR: Invalid input line provided. No delimiter between sum and values. Expected delimiter: " 
                      << kInputDelimiter << std::endl;
            return;
        }

        new_input.total = std::stol(new_line.substr(0, delimiter_index));
        std::stringstream values;
        values << new_line.substr(delimiter_index + 1);

        std::string new_val;
        while(std::getline(values, new_val, kValuesDelimiter)) {
            if(!new_val.empty()) {
                try {
                    new_values.push_back(std::stol(new_val));
                } catch(std::invalid_argument const& e) {
                    std::cout << "ERROR: unable to convert the inputted value: " << new_val << ", results may be incorrect" << std::endl;
                } catch(std::out_of_range const& e) {
                    std::cout << "ERROR: unable to convert the inputted value: " << new_val << ", results may be incorrect" << std::endl;
                }
            }
        }
        if(new_values.empty()) {
            std::cout << "ERROR: No valid input values added." << std::endl;
            return;
        }

        new_input.values = new_values;
        resources_.push_back(new_input);
    }

    uint64_t ResourceHandler::GetChallengeOneSum() {
        uint64_t sum = 0;
        
        for(input_holder_ resource : resources_) {
            uint64_t additions = 0;
            bool found = false;
            for(uint64_t v : resource.values){
                additions += (uint64_t)v;
            }
            if(additions == resource.total) {
                found = true;
                sum += additions;
            }

            // loop through adding multiplications if the total isn't just addition
            uint16_t number_of_x = 1;
            while(number_of_x < resource.values.size() && !found) {

                uint16_t index_to_start_x = 0;

                while((index_to_start_x + number_of_x) < resource.values.size() && !found) {

                    std::stringstream calculation;
                    uint16_t num_x_added = 0;

                    for(size_t i = 0; i < resource.values.size(); i++) {
                        calculation << resource.values[i];

                        if((i+1) < resource.values.size()) {
                            if((num_x_added < number_of_x) && (num_x_added > 0 || index_to_start_x == i)) {
                                calculation << kMultiplyOperator;
                                num_x_added++;
                            } else {
                                calculation << kPlusOperator;
                            }
                        }
                    }
                    uint64_t curr_sum = GetSumFromString(calculation.str());
                    if(resource.total == curr_sum) {
                        found = true;
                        sum += curr_sum;
                    }
                    index_to_start_x++;
                }
                number_of_x++;
            }
        }

        return sum;
    }

    uint64_t ResourceHandler::GetSumFromString(const std::string& calculation) {
        size_t prev_index = 0;
        std::vector<uint64_t> values;
        std::vector<char> operators;

        try {
            for(size_t c = 0; c < calculation.size(); c++) {
                if(calculation[c] == kMultiplyOperator || calculation[c] == kPlusOperator) {
                    operators.push_back(calculation[c]);
                    values.push_back(std::stol(calculation.substr(prev_index, c)));
                    prev_index = c+1;
                }
            }
            // add final number
            values.push_back(std::stol(calculation.substr(prev_index)));
        } catch(std::invalid_argument const& e) {
            std::cout << "ERROR: Failed parsing calculation values. Results may be inaccurate." << std::endl;
            return 0;
        } catch(std::out_of_range const& e) {
            std::cout << "ERROR: Failed parsing calculation values. Results may be inaccurate." << std::endl;
            return 0;
        }

        // verify we have exactly 1 more integer than we do operators
        if(operators.size() != (values.size()-1)) {
            std::cout << "ERROR: incorrectly parsed operators and values when performing calculation. Results may be inaccurate." << std::endl;
            return 0;
        }

        // DO NOT DO MULTIPLICATIONS FIRST - AOC rules are left to right ignoring BODMAS
        /*bool no_x = false;
        while(!operators.empty()) {
            bool mul_found = false;
            for(size_t i = 0; i < operators.size(); i++) {
                if(!no_x) {
                    if(operators[i] == kMultiplyOperator) {
                        uint64_t val_one = values[i];
                        uint64_t val_two = values[i + 1];

                        values.erase(values.begin() + (i+1));
                        values[i] = val_one * val_two;

                        operators.erase(operators.begin() + i);

                        //mul_found = true;
                        break;
                    } 
                } else {
                    uint64_t val_one = values[i];
                    uint64_t val_two = values[i + 1];

                    values.erase(values.begin() + (i+1));
                    values[i] = val_one + val_two;

                    operators.erase(operators.begin() + i);
                }
            }
            if(!mul_found) {
                no_x = true;
            }
        }*/

        while(!operators.empty()) {
            if(operators[0] == kMultiplyOperator) {
                uint64_t val_one = values[0];
                uint64_t val_two = values[1];

                values.erase(values.begin() + 1);
                values[0] = (uint64_t)val_one * (uint64_t)val_two;

                operators.erase(operators.begin());
            } else {
                uint64_t val_one = values[0];
                uint64_t val_two = values[1];

                values.erase(values.begin() + 1);
                values[0] = (uint64_t)val_one + (uint64_t)val_two;

                operators.erase(operators.begin());
            }
        }

        if(values.size() != 1) {
            std::cout << "ERROR: failed performing calculation of: " << calculation << ", results may be invalid." << std::endl;
            return 0;
        }

        return values[0];
    }

} // namespace day_seven
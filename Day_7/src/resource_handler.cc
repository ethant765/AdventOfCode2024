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
        std::vector<uint32_t> new_values;

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
            for(uint32_t v : resource.values){
                additions += v;
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
                                calculation << "*";
                                num_x_added++;
                            } else {
                                calculation << "+";
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
        return 0;
    }

} // namespace day_seven
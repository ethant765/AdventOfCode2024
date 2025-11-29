#include "../include/resource_handler.h"
#include "../include/instruction.h"

#include <iostream>
#include <string>
#include <regex>
#include <cstdint>

void ResourceHandler::AddResource(const std::string& input) {
    bool multiply_instruction = true; // defaults to do

    std::vector<std::string> allDosAndDonts = GetSubStrsOnFind(kDoCondition, kDontCondition, input);

    for(size_t i = 0; i < allDosAndDonts.size(); i++) {
        std::vector<std::string> muls = RegexStrFinder(kRegexMatcher, allDosAndDonts[i]);

        if(allDosAndDonts[i].find(kDoCondition) != std::string::npos) {
            std::cout << "True: " << allDosAndDonts[i] << std::endl << std::endl << std::endl;
            multiply_instruction = true;
        } else if (allDosAndDonts[i].find(kDontCondition) != std::string::npos) {
            std::cout << "False: " << allDosAndDonts[i] << std::endl << std::endl << std::endl;
            multiply_instruction = false;
        } else {
            // should only occur on first string. Instructions are to Do
            if(i != 0) {
                std::cout << "ERROR: not in first iteration of input line and found a substring without a do or don't" << std::endl;
                return;
            }
            std::cout << "True: " << allDosAndDonts[i] << std::endl << std::endl << std::endl;
            multiply_instruction = true;
        }

        for(const std::string& mul : muls) {
            std::vector<std::string> nums = RegexStrFinder(kNumRegexMatcher, mul);
            if(nums.size() != 2) {
                std::cout << "ERROR: unexpected number of multipliers found! expected 2, found: " << nums.size() << std::endl;
                return;
            }
            values_.push_back(Instruction(std::stoi(nums[0]), stoi(nums[1]), multiply_instruction));
        }

    }
}

uint64_t ResourceHandler::GetTotalMultiplications() {
    uint64_t total = 0;
    for(Instruction instruction : values_) {
        total += instruction.Mul();
    }
    return total;
}

uint64_t ResourceHandler::GetMultiplicationWithConditionals() {
    uint64_t total = 0;
    for(Instruction instruction : values_) {
        if(instruction.DoWeMultiply()) {
            total += instruction.Mul();
        }
    }
    return total;
}

std::vector<std::string> ResourceHandler::RegexStrFinder(const std::string& regex_string, const std::string& input) {
    std::vector<std::string> matches;
    std::regex pattern(regex_string);

    std::sregex_iterator iter(input.begin(), input.end(), pattern);
    std::sregex_iterator end;

    // loop through all matches within passed string
    while(iter != end) {
        matches.push_back((*iter)[0]);
        ++iter;
    }

    return matches;
}

std::vector<std::string> ResourceHandler::GetSubStrsOnFind(const std::string& string_match_one, const std::string& string_match_two, const std::string& input) {
    std::vector<std::string> values;

    std::size_t pos_one = FindFirstMatch(0, string_match_one, string_match_two, input);
    if(pos_one == std::string::npos) {
        std::cout << "ERROR: Unable to find any matches for: " << string_match_one << ", or: " << string_match_two << ", in: " << input << std::endl;
        return values;
    }
    // get first string before pos_one
    values.push_back(input.substr(0, pos_one));

    std::size_t pos_two = FindFirstMatch(pos_one+1, string_match_one, string_match_two, input);

    while(pos_two != std::string::npos) {
        values.push_back(input.substr(pos_one, (pos_two - pos_one)));
        pos_one = pos_two;
        pos_two = FindFirstMatch(pos_one+1, string_match_one, string_match_two, input);
    }

    // add the final sub string
    values.push_back(input.substr(pos_one, input.size() - 1));

    return values;
}

size_t ResourceHandler::FindFirstMatch(size_t starting_pos, const std::string& string_match_one, const std::string& string_match_two, const std::string& input) {
    return (input.find(string_match_one, starting_pos) < input.find(string_match_two, starting_pos)) ? 
                    input.find(string_match_one, starting_pos) : 
                    input.find(string_match_two, starting_pos);
}

#ifndef DAY_TWO_RESOURCE_HANDLER_H_
#define DAY_TWO_RESOURCE_HANDLER_H_

#include <vector>
#include <cstdint>
#include <string>

namespace day_two {
    /**
     * @brief Class for handling the input resource and processing the requirements of the Day_Two challenge
     */
    class ResourceHandler {
        public:
            /**
             * @brief Construct a new Resource Handler object
             */
            ResourceHandler() = default;

            /**
             * @brief Destroy the Resource Handler object
             */
            ~ResourceHandler() = default;

            /**
             * @brief Adds a new resource line directly from the input file to the stored values
             * 
             * @param line 
             */
            void AddNewResourceLine(const std::string& line);

            /**
             * @brief Calculates and returns the number of safe lines stored within the classes resources_ object
             * 
             * @param use_problem_dampener
             * @return uint32_t 
             */
            uint32_t GetNumOfSafeLevels(const bool use_problem_dampener = false);

        private:

            /**
             * @brief Validates the passed line of values
             * 
             * @param line 
             * @param use_problem_dampener
             * @return true 
             * @return false 
             */
            bool ValidateLine(const std::vector<uint16_t>& line, const bool use_problem_dampener);;

            /**
             * @brief compares if two passed values have a difference between the min and max difference allowance
             * 
             * @param smaller_val 
             * @param larger_val 
             * @return true 
             * @return false 
             */
            bool TestWithinBounds(const uint16_t smaller_val, const uint16_t larger_val);

            /**
             * @brief Stores all the resouces from the input file
             */
            std::vector<std::vector<uint16_t>> resources_;

            /**
             * @brief Minimum safe difference between two numbers
             */
            const uint8_t kMinDiff = 1;

            /**
             * @brief Maximum safe diffrence between two numbers
             */
            const uint8_t kMaxDiff = 3;
    };

} // namespace day_two

#endif
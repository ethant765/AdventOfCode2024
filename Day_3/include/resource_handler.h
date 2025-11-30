#ifndef DAY_THREE_RESOURCE_HANDLER_H_
#define DAY_THREE_RESOURCE_HANDLER_H_

#include "instruction.h"

#include <string>
#include <vector>
#include <cstdint>

namespace day_three {
    /**
     * @brief Class to store and handles the challenege resources
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
             * @brief parses and adds corrupt strings as pairs that require multiplying
             * 
             * @param input 
             */
            void AddResource(const std::string& input);

            /**
             * @brief Get the Total value of all pairs multiplies and added together 
             * 
             * @return uint64_t 
             */
            uint64_t GetTotalMultiplications();

            /**
             * @brief Get the Multiplication total With Conditional do/don't
             * 
             * @return uint64_t 
             */
            uint64_t GetMultiplicationWithConditionals();
        private:
            /**
             * @brief Finds all the sub-strings within the provided string that match the provided regex
             * 
             * @param regex_string 
             * @param input 
             * @return std::vector<std::string> 
             */
            std::vector<std::string> RegexStrFinder(const std::string& regex_string, const std::string& input);


            std::vector<std::string> GetSubStrsOnFind(const std::string& string_match_one, const std::string& string_match_two, const std::string& input);

            size_t FindFirstMatch(size_t starting_pos, const std::string& string_match_one, const std::string& string_match_two, const std::string& input);

            /**
             * @brief regex for finding mul(x,x) values
             */
            const std::string kRegexMatcher = "mul\\(\\d{1,3},\\d{1,3}\\)";

            /**
             * @brief regex for finding integers
             */
            const std::string kNumRegexMatcher = "(\\d+)";

            const std::string kDoCondition = "do()";
            const std::string kDontCondition = "don't()";

            /**
             * @brief stores value pairs
             */
            std::vector<Instruction> values_;
    };

} // namespace day_three

#endif
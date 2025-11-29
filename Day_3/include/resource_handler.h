#ifndef RESOURCE_HANDLER_H_
#define RESOURCE_HANDLER_H_

#include <string>
#include <vector>
#include <utility>
#include <cstdint>

/**
 * @brief 
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
    private:
        /**
         * @brief regex for finding mul(x,x) values
         */
        const std::string kRegexMatcher = "mul\\(\\d{1,3},\\d{1,3}\\)";

        /**
         * @brief regex for finding integers
         */
        const std::string kNumRegexMatcher = "(\\d+)";

        /**
         * @brief stores value pairs
         */
        std::vector<std::pair<int, int>> values_;
};

#endif
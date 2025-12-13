#ifndef DAY_SEVEN_RESOURCE_HANDLER_H_
#define DAY_SEVEN_RESOURCE_HANDLER_H_

#include <string>
#include <vector>
#include <cstdint>

namespace day_seven {
    class ResourceHandler {
        public:
            ResourceHandler() = default;
            ~ResourceHandler() = default;

            void AddResource(const std::string& new_line);
            uint64_t GetChallengeOneSum();
        private:
            struct input_holder_ {
                std::vector<uint32_t> values;
                uint64_t total;
            };

            uint64_t GetSumFromString(const std::string& calculation);

            std::vector<input_holder_> resources_;
            const char kInputDelimiter = ':';
            const char kValuesDelimiter = ' ';
            const char kPlusOperator = '+';
            const char kMultiplyOperator = '*';
    };
} // namespace day_seven

#endif
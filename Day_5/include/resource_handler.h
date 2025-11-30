#ifndef DAY_FIVE_RESOURCE_HANDLER_H_
#define DAY_FIVE_RESOURCE_HANDLER_H_

#include <vector>
#include <utility>
#include <cstdint>
#include <string>
#include <mutex>

namespace day_five {

    class ResourceHandler {
        public:
            ResourceHandler() = default;
            ~ResourceHandler() = default;

            void AddNewRule(const std::string& rule);
            void AddNewPageOrdering(const std::string& page_ordering);

            void Print();

            uint64_t GetMiddlePageSum();

        private:
            std::vector<size_t> GetValidPageOrderingIndexes();
            void TestOrderingValid(const size_t index_to_test);

            std::vector<std::pair<uint16_t, uint16_t>> rules_;
            std::vector<std::vector<uint16_t>> page_orderings_;
            std::vector<size_t> valid_indexes_;
            std::mutex mutex_;

            const char kRuleDelimeter = '|';
            const char kPageOrderingDelimeter = ',';
    };

} // namespace day_five

#endif
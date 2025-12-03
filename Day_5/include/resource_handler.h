#ifndef DAY_FIVE_RESOURCE_HANDLER_H_
#define DAY_FIVE_RESOURCE_HANDLER_H_

#include <vector>
#include <utility>
#include <cstdint>
#include <string>
#include <mutex>

namespace day_five {
    /**
     * @brief handles and processes the resources required for Day 5
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
             * @brief Adds new rules to the list
             * 
             * @param rule 
             */
            void AddNewRule(const std::string& rule);

            /**
             * @brief Addres new page orderings to the list
             * 
             * @param page_ordering 
             */
            void AddNewPageOrdering(const std::string& page_ordering);

            /**
             * @brief Prints the loaded in rules and page orderings
             */
            void Print();

            /**
             * @brief Gets the sum of the middle numbers of all valid pages
             * 
             * @return uint64_t 
             */
            uint64_t GetValidMiddlePageSum();

            /**
             * @brief Get the sum of the middle numbers of all invalid pages after they have been rearranged to be valid
             * 
             * @return uint64_t 
             */
            uint64_t GetInvalidMiddlePageSum();

            /**
             * @brief Sorts all the added page orderings into valid and invalid lists based on the current input rules and orderings
             */
            void SortPages();

        private:
            /**
             * @brief Tests if the ordering is valid for the page ordering at the provided index against all provided rules
             * 
             * @param index_to_test 
             */
            void TestOrderingValid(const size_t index_to_test);

            /**
             * @brief Rearranges the invalid ordering at the provided index for the provided rules
             * 
             * @param index_to_test 
             * @return std::vector<uint16_t> 
             */
            std::vector<uint16_t> RearrangeInvalid(const size_t index_to_test);

            std::vector<std::pair<uint16_t, uint16_t>> rules_;
            std::vector<std::vector<uint16_t>> page_orderings_;
            std::vector<size_t> valid_indexes_;
            std::vector<size_t> invalid_indexes_;
            std::mutex mutex_;

            const char kRuleDelimeter = '|';
            const char kPageOrderingDelimeter = ',';
    };

} // namespace day_five

#endif
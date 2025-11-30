#ifndef DAY_ONE_RESOURCE_HOLDER_H_
#define DAY_ONE_RESOURCE_HOLDER_H_

#include <vector>
#include <cstdint>

namespace day_one {
    /**
     * @brief Stores and processes resources associated with day 1 challenege
     */
    class ResourceHolder {
        public:
            /**
             * @brief Construct a new Resource Holder object
             */
            ResourceHolder();

            /**
             * @brief Add a value to list one
             * 
             * @param item
             */
            void AddToListOne(uint32_t item);

            /**
             * @brief Add a value to list two
             * 
             * @param item 
             */
            void AddToListTwo(uint32_t item);

            /**
             * @brief Get the Total Distance to be travelled
             * 
             * @return uint32_t 
             */
            uint32_t GetTotalDistance();

            /**
             * @brief Get the Similarity Score of the two lists
             * 
             * @return uint32_t 
             */
            uint32_t GetSimilarityScore();

            /**
             * @brief Orders elements in each list from smallest to largest
             */
            void OrderLists();
        private:
            /**
             * @brief Object that stores list one
             */
            std::vector<uint32_t> list_one_;

            /**
             * @brief Object that stores list two
             */
            std::vector<uint32_t> list_two_;
    };

} // namespace day_one

#endif
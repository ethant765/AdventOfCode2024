#pragma once

#include <vector>
#include <cstdint>

/**
 * @brief 
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
    private:
        /**
         * @brief Orders elements in each list from smallest to largest
         */
        void OrderLists();

        /**
         * @brief Object that stores list one
         */
        std::vector<uint32_t> list_one_;

        /**
         * @brief Object that stores list two
         */
        std::vector<uint32_t> list_two_;
};

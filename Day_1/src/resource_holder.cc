#include "../include/resource_holder.h"

#include <iostream>
#include <cstdint>
#include <algorithm>
#include <numeric>

ResourceHolder::ResourceHolder() {}

void ResourceHolder::AddToListOne(uint32_t item) {
    list_one_.push_back(item);
}

void ResourceHolder::AddToListTwo(uint32_t item) {
    list_two_.push_back(item);
}

uint32_t ResourceHolder::GetTotalDistance() {
    if(list_one_.size() != list_two_.size()) {
        std::cout << "ERROR: Lists don't contain the same number of values, unable to process." << std::endl;
        return 0;
    }

    uint32_t total_distance = 0;
    for(size_t i = 0; i < list_one_.size(); i++) {
        if(list_one_[i] > list_two_[i]) {
            total_distance += (list_one_[i] - list_two_[i]);
        } else {
            total_distance += (list_two_[i] - list_one_[i]);
        }

        //std::cout << "added values: " << list_one_[i] << ", " << list_two_[i] << ". current total distance: " << total_distance << std::endl;
    }
    return total_distance;
}

uint32_t ResourceHolder::GetSimilarityScore() {
    std::vector<uint32_t> duplicates;
    for(uint32_t first_val : list_one_) {
        int counter = 0;
        for(uint32_t second_val : list_two_) {
            if(first_val == second_val) {
                counter++;
            }
        }
        duplicates.push_back(counter * first_val);
    }
    return std::accumulate(duplicates.begin(), duplicates.end(), 0);
}

void ResourceHolder::OrderLists() {
    std::sort(list_one_.begin(), list_one_.end());
    std::sort(list_two_.begin(), list_two_.end());
}
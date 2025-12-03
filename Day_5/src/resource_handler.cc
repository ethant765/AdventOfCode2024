#include "../include/resource_handler.h"

#include <string>
#include <iostream>
#include <utility>
#include <cstdint>
#include <sstream>
#include <thread>
#include <mutex>

namespace day_five {
    void ResourceHandler::AddNewRule(const std::string& rule) {
        std::string first = rule.substr(0,rule.find(kRuleDelimeter));
        std::string second = rule.substr(rule.find(kRuleDelimeter) + 1, rule.size());

        rules_.push_back(std::pair<uint16_t, uint16_t>(std::stoi(first), std::stoi(second)));
    }

    void ResourceHandler::AddNewPageOrdering(const std::string& page_ordering) {
        std::vector<uint16_t> new_order;
        
        std::stringstream strstr(page_ordering);
        std::string new_item;
        while(std::getline(strstr, new_item, kPageOrderingDelimeter)) {
            new_order.push_back(std::stoi(new_item));
        }

        if(!new_order.empty()) {
            page_orderings_.push_back(new_order);
        }
    }

    uint64_t ResourceHandler::GetValidMiddlePageSum() {
        uint64_t sum_total = 0;

        for(size_t i : valid_indexes_) {
            auto mid_point = page_orderings_[i].begin() + page_orderings_[i].size() / 2;
            sum_total += *mid_point;
        }

        return sum_total;
    }

    uint64_t ResourceHandler::GetInvalidMiddlePageSum() {
        uint64_t sum_total = 0;

        for(size_t i : invalid_indexes_) {
            std::vector<uint16_t> rearranged_ordering = RearrangeInvalid(i);
            auto mid_point = rearranged_ordering.begin() + rearranged_ordering.size() / 2;
            sum_total += *mid_point;
        }

        return sum_total;
    }

    std::vector<uint16_t> ResourceHandler::RearrangeInvalid(const size_t index_to_test) {
        std::vector<uint16_t> new_order(page_orderings_[index_to_test].begin(), page_orderings_[index_to_test].end());

        bool invalid = true;
        while(invalid) {
            bool switched = false;
            for(size_t i = 1; i < new_order.size() && !switched; i++) {
                uint16_t current = new_order[i];
                for(long int j = i-1; j >= 0 && !switched; j--) {
                    uint16_t prev = new_order[j];
                    for(std::pair<uint16_t, uint16_t> rule : rules_) {
                        if((rule.first == current) && (rule.second == prev)) {
                            switched = true;
                            new_order[i] = prev;
                            new_order[j] = current;
                            break;
                        }
                    }
                }
            }

            if(!switched) {
                invalid = false;
            }
        }

        return new_order;
    }

    void ResourceHandler::SortPages() {
        valid_indexes_.clear();
        invalid_indexes_.clear();
        std::vector<std::thread> threads;

        for(size_t i = 0; i < page_orderings_.size(); i++) {
            std::thread thread(&ResourceHandler::TestOrderingValid, this, i);
            threads.push_back(std::move(thread));
        }

        for(auto& thread : threads) {
            thread.join();
        }
    }

    void ResourceHandler::TestOrderingValid(const size_t index_to_test) {
        std::vector<uint16_t> page_ordering = page_orderings_[index_to_test];

        bool valid = true;
        for(size_t i = 1; i < page_ordering.size() && valid; i++) {
            uint16_t current = page_ordering[i];
            for(long int j = i-1; j >= 0 && valid; j--) {
                uint16_t prev = page_ordering[j];
                for(std::pair<uint16_t, uint16_t> rule : rules_) {
                    if((rule.first == current) && (rule.second == prev)) {
                        valid = false;
                        break;
                    }
                }
            }
        }

        // add valid items to list of indexes
        {
            std::scoped_lock lock(mutex_);
            if(valid) {
                valid_indexes_.push_back(index_to_test);
            } else {
                invalid_indexes_.push_back(index_to_test);
            }
        }
    }

    void ResourceHandler::Print() {
        
        for(std::pair<uint16_t, uint16_t> rule : rules_)  {
            std::cout << rule.first << "|" << rule.second << std::endl;
        }
        std::cout << std::endl;
        for(std::vector<uint16_t> page_ordering : page_orderings_) {
            for(uint16_t page : page_ordering) {
                std::cout << page << ",";
            }
            std::cout << std::endl;
        }
    }
}
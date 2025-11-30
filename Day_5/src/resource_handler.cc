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

    uint64_t ResourceHandler::GetMiddlePageSum() {
        uint64_t sum_total = 0;
        std::vector<size_t> valid_orderings = GetValidPageOrderingIndexes();

        for(size_t i : valid_orderings) {
            auto mid_point = page_orderings_[i].begin() + page_orderings_[i].size() / 2;
            sum_total += *mid_point;
        }

        return sum_total;
    }

    std::vector<size_t> ResourceHandler::GetValidPageOrderingIndexes() {
        valid_indexes_.clear();
        std::vector<std::thread> threads;

        for(size_t i = 0; i < page_orderings_.size(); i++) {
            std::thread thread(&ResourceHandler::TestOrderingValid, this, i);
            threads.push_back(std::move(thread));
        }

        for(auto& thread : threads) {
            thread.join();
        }

        return valid_indexes_;
    }

    void ResourceHandler::TestOrderingValid(const size_t index_to_test) {
        //TODO: implement

        // add valid items to list of indexes
        {
            std::scoped_lock lock(mutex_);
            valid_indexes_.push_back(index_to_test);
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
#include "../include/word_processor.h"

#include <string>
#include <algorithm>
#include <cstdint>
#include <iostream>
#include <thread>

void WordProcessor::AddWordSearchRow(const std::string& row) {
    std::vector<char> vec(row.begin(), row.end());
    std::vector<char> placeholder_row;
    for(char x : vec) {
        placeholder_row.push_back('.');
    }

    // ensure all rows being added are the same length
    if(word_search_.empty() || word_search_[0].size() == vec.size()) {
        word_search_.push_back(vec);
        placeholder_search_.push_back(placeholder_row);
    } else {
        std::cout << "ERROR: all rows being added much be the same length. Length of existing rows: " 
                  << word_search_[0].size() << ", length being added: " << vec.size() << std::endl;
    }
}

uint64_t WordProcessor::FindWord(const std::string& word) {
    std::copy(word.begin(), word.end(), std::back_inserter(word_to_find_));
    num_of_matches_ = 0;
    std::vector<std::thread> threads;
    for(size_t vertical = 0; vertical < word_search_.size(); vertical++) {
        for(size_t horizontal = 0; horizontal < word_search_[vertical].size(); horizontal++) {
            if(word_search_[vertical][horizontal] == word_to_find_[0]) {
                for(int dir = UP_LEFT; dir != test_direction::END; ++dir) {
                    test_direction direction = static_cast<test_direction>(dir);
                    std::thread thread(&WordProcessor::TestSurroundingLettersForWord, this, vertical, horizontal, 1, direction);
                    threads.push_back(std::move(thread));
                }
            }
        }
    }

    for(auto& thread : threads) {
        thread.join();
    }

    return num_of_matches_;
}

uint64_t WordProcessor::FindCrossOfMAS() {
    num_of_matches_ = 0;
    std::vector<std::thread> threads;

    for(size_t vertical = 0; vertical < word_search_.size(); vertical++) {
        for(size_t horizontal = 0; horizontal < word_search_[vertical].size(); horizontal++) {
            if(word_search_[vertical][horizontal] == kCrossWord[1]) {
                std::thread thread(&WordProcessor::TestEachDirectionForCross, this, vertical, horizontal);
                threads.push_back(std::move(thread));
            }
        }
    }

    for(auto& thread : threads) {
        thread.join();
    }

    return num_of_matches_;
}

void WordProcessor::TestEachDirectionForCross(const size_t curr_vertical_pos, const size_t curr_horizontal_pos) {
    bool found = false;
    if ((TestForCharInDirection(curr_vertical_pos, curr_horizontal_pos, kCrossWord[0], test_direction::UP_LEFT)) && 
        (TestForCharInDirection(curr_vertical_pos, curr_horizontal_pos, kCrossWord[2], test_direction::DOWN_RIGHT))) {
        if ((TestForCharInDirection(curr_vertical_pos, curr_horizontal_pos, kCrossWord[0], test_direction::UP_RIGHT)) && 
            (TestForCharInDirection(curr_vertical_pos, curr_horizontal_pos, kCrossWord[2], test_direction::DOWN_LEFT))) {
            found = true;
        } else if ((TestForCharInDirection(curr_vertical_pos, curr_horizontal_pos, kCrossWord[2], test_direction::UP_RIGHT)) && 
                    (TestForCharInDirection(curr_vertical_pos, curr_horizontal_pos, kCrossWord[0], test_direction::DOWN_LEFT))) {
            found = true;
        }
    }
        
    if ((TestForCharInDirection(curr_vertical_pos, curr_horizontal_pos, kCrossWord[2], test_direction::UP_LEFT)) && 
        (TestForCharInDirection(curr_vertical_pos, curr_horizontal_pos, kCrossWord[0], test_direction::DOWN_RIGHT))) {
        if ((TestForCharInDirection(curr_vertical_pos, curr_horizontal_pos, kCrossWord[0], test_direction::UP_RIGHT)) && 
            (TestForCharInDirection(curr_vertical_pos, curr_horizontal_pos, kCrossWord[2], test_direction::DOWN_LEFT))) {
            found = true;
        } else if ((TestForCharInDirection(curr_vertical_pos, curr_horizontal_pos, kCrossWord[2], test_direction::UP_RIGHT)) && 
                    (TestForCharInDirection(curr_vertical_pos, curr_horizontal_pos, kCrossWord[0], test_direction::DOWN_LEFT))) {
            found = true;
        }
    }

    if(found) {
        // cross found
        std::scoped_lock lock(mutex_);
        num_of_matches_++;
    }
}

bool WordProcessor::TestForCharInDirection(const size_t curr_vertical_pos, const size_t curr_horizontal_pos, const char find, const test_direction direction) {
    std::pair<size_t, size_t> new_indexes = GetNewIndexes(curr_vertical_pos, curr_horizontal_pos, direction);

    if ((new_indexes.first != std::string::npos && new_indexes.second != std::string::npos) && word_search_[new_indexes.first][new_indexes.second] == find) {
        return true;
    }
    return false;
}

void WordProcessor::TestSurroundingLettersForWord(const size_t vertical_pos, const size_t horizontal_pos, const size_t word_to_find_pos, const test_direction direction) {
    if(word_to_find_pos == word_to_find_.size()) {
        //word found
        std::scoped_lock lock(mutex_);
        num_of_matches_++;

        // add word to placeholder
        test_direction new_direction = GetReverseDirection(direction);
        size_t vertical_index = vertical_pos;
        size_t horizontal_index = horizontal_pos;
        for(size_t i = word_to_find_pos; i > 0; i--) {
            char curr_letter = word_to_find_[i - 1];
            placeholder_search_[vertical_index][horizontal_index] = curr_letter;
            std::pair<size_t, size_t> new_indexes = GetNewIndexes(vertical_index, horizontal_index, new_direction);
            vertical_index = new_indexes.first;
            horizontal_index = new_indexes.second;
        }

        return;
    }
    
    char find_letter = word_to_find_[word_to_find_pos];
    std::pair<size_t, size_t> new_indexes = GetNewIndexes(vertical_pos, horizontal_pos, direction);
   

    if((new_indexes.first != std::string::npos && new_indexes.second != std::string::npos) && (word_search_[new_indexes.first][new_indexes.second] == find_letter)) {
        TestSurroundingLettersForWord(new_indexes.first, new_indexes.second, (word_to_find_pos + 1), direction);
    }
}

WordProcessor::test_direction WordProcessor::GetReverseDirection(const test_direction curr_direction) {
    switch(curr_direction) {
        case test_direction::RIGHT: {
            return test_direction::LEFT;
        }
        case test_direction::LEFT: {
            return test_direction::RIGHT;
        }
        case test_direction::DOWN: {
            return test_direction::UP;
        }
        case test_direction::UP: {
            return test_direction::DOWN;
        }
        case test_direction::DOWN_LEFT: {
            return test_direction::UP_RIGHT;
        }
        case test_direction::DOWN_RIGHT: {
            return test_direction::UP_LEFT;
        }
        case test_direction::UP_LEFT: {
            return test_direction::DOWN_RIGHT;
        }
        case test_direction::UP_RIGHT: {
            return test_direction::DOWN_LEFT;
        }
        default: {
            std::cout << "ERROR: getting new direction for placeholder word search chart. Chart will likely be invalid" << std::endl;
            return curr_direction;
        }
    }
}


std::pair<size_t, size_t> WordProcessor::GetNewIndexes(const size_t curr_vertical, const size_t curr_horizontal, const test_direction direction) {
    size_t new_horizontal = std::string::npos;
    size_t new_vertical = std::string::npos;
    switch(direction) {
        case test_direction::RIGHT: {
            if(curr_horizontal < (word_search_[curr_vertical].size() - 1)) {
                new_horizontal = curr_horizontal + 1;
                new_vertical = curr_vertical;
            }
            break;
        }
        case test_direction::LEFT: {
            if(curr_horizontal > 0) {
                new_horizontal = curr_horizontal - 1;
                new_vertical = curr_vertical;
            }
            break;
        }
        case test_direction::DOWN: {
            if(curr_vertical < (word_search_.size() - 1)) {
                new_vertical = curr_vertical + 1;
                new_horizontal = curr_horizontal;
            }
            break;
        }
        case test_direction::UP: {
            if(curr_vertical > 0) {
                new_vertical = curr_vertical - 1;
                new_horizontal = curr_horizontal;
            }
            break;
        }
        case test_direction::DOWN_LEFT: {
            if((curr_vertical < (word_search_.size() - 1)) && (curr_horizontal > 0)) {
                new_vertical = curr_vertical + 1;
                new_horizontal = curr_horizontal - 1;
            }
            break;
        }
        case test_direction::DOWN_RIGHT: {
            if((curr_vertical < (word_search_.size() - 1)) && (curr_horizontal < (word_search_[curr_vertical].size() - 1))) {
                new_vertical = curr_vertical + 1;
                new_horizontal = curr_horizontal + 1;
            }
            break;
        }
        case test_direction::UP_LEFT: {
            if((curr_vertical > 0) && (curr_horizontal > 0)) {
                new_vertical = curr_vertical - 1;
                new_horizontal = curr_horizontal - 1;
            }
            break;
        }
        case test_direction::UP_RIGHT: {
            if((curr_vertical > 0) && (curr_horizontal < (word_search_[curr_vertical].size() - 1))) {
                new_vertical = curr_vertical - 1;
                new_horizontal = curr_horizontal + 1;
            }
            break;
        }
        default: {
            std::cout << "unknown test direction provided, results may be invalid." << std::endl;
            break;
        }
    }
    return std::pair<size_t, size_t>(new_vertical, new_horizontal);
}

void WordProcessor::PrintWordSearchSolution() {
    for(size_t vertical = 0; vertical < placeholder_search_.size(); vertical++) {
        for(size_t horizontal = 0; horizontal < placeholder_search_[vertical].size(); horizontal++) {
            std::cout << placeholder_search_[vertical][horizontal];
        }
        std::cout << std::endl << std::endl << std::endl;
    }
}
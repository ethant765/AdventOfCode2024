#ifndef WORD_PROCESSOR_H_
#define WORD_PROCESSOR_H_

#include <vector>
#include <string>
#include <cstdint>
#include <mutex>
#include <utility>

class WordProcessor {
    public:
        WordProcessor(const std::string& word_to_find);
        ~WordProcessor() = default;

        void AddWordSearchRow(const std::string& row);

        uint64_t FindXMAS();

        void PrintWordSearchSolution();

    private:
        enum test_direction {
            UP_LEFT = 0,
            UP = 1,
            UP_RIGHT = 2,
            RIGHT = 3,
            DOWN_RIGHT = 4,
            DOWN = 5,
            DOWN_LEFT = 6,
            LEFT = 7,
            END = 8
        };
        void TestSurroundingLettersForWord(const size_t vertical_pos, const size_t horizontal_pos, const size_t word_to_find_pos, const test_direction direction);
        std::pair<size_t, size_t> GetNewIndexes(const size_t curr_vertical, const size_t curr_horizontal, const test_direction direction);
        test_direction GetReverseDirection(const test_direction curr_direction);
        std::vector<std::vector<char>> word_search_;
        std::vector<std::vector<char>> placeholder_search_;
        std::vector<char> word_to_find_;
        uint64_t num_of_matches_;
        std::mutex mutex_;
};

#endif
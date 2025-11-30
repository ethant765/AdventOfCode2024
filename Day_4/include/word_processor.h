#ifndef WORD_PROCESSOR_H_
#define WORD_PROCESSOR_H_

#include <vector>
#include <string>
#include <cstdint>
#include <mutex>
#include <utility>

class WordProcessor {
    public:
        WordProcessor() = default;
        ~WordProcessor() = default;
        void AddWordSearchRow(const std::string& row);
        uint64_t FindWord(const std::string& word);
        uint64_t FindCrossOfMAS();
        void PrintWordSearchSolution();

    private:
        enum test_direction {
            // cross directions
            UP_LEFT = 0,
            UP_RIGHT = 1,
            DOWN_RIGHT = 2,
            DOWN_LEFT = 3,
            // none-cross directions
            UP = 4,
            RIGHT = 5,
            DOWN = 6,
            LEFT = 7,
            END = 8
        };
        void TestSurroundingLettersForWord(const size_t vertical_pos, const size_t horizontal_pos, const size_t word_to_find_pos, const test_direction direction);
        bool TestForCharInDirection(const size_t curr_vertical_pos, const size_t curr_horizontal_pos, const char find, const test_direction direction);
        void TestEachDirectionForCross(const size_t curr_vertical_pos, const size_t curr_horizontal_pos);
        std::pair<size_t, size_t> GetNewIndexes(const size_t curr_vertical, const size_t curr_horizontal, const test_direction direction);
        test_direction GetReverseDirection(const test_direction curr_direction);
        std::vector<std::vector<char>> word_search_;
        std::vector<std::vector<char>> placeholder_search_;
        std::vector<char> word_to_find_;
        uint64_t num_of_matches_;
        std::mutex mutex_;
        const std::vector<char> kCrossWord{'M', 'A', 'S'};
};

#endif
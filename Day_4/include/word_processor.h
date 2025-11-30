#ifndef DAY_FOUR_WORD_PROCESSOR_H_
#define DAY_FOUR_WORD_PROCESSOR_H_

#include <vector>
#include <string>
#include <cstdint>
#include <mutex>
#include <utility>

namespace day_four {
    /**
     * @brief Processes the input and calculates the results to the day 4 challenege
     */
    class WordProcessor {
        public:
            /**
             * @brief Construct a new Word Processor object
             */
            WordProcessor() = default;

            /**
             * @brief Destroy the Word Processor object
             */
            ~WordProcessor() = default;

            /**
             * @brief Add a new row to the word search grid
             * 
             * @param row 
             */
            void AddWordSearchRow(const std::string& row);

            /**
             * @brief finds the number of occurances of the provided word in the current word search grid
             * 
             * @param word 
             * @return uint64_t 
             */
            uint64_t FindWord(const std::string& word);

            /**
             * @brief Counds the number of times a cross of the word MAS appears
             * 
             * @return uint64_t 
             */
            uint64_t FindCrossOfMAS();

            /**
             * @brief prints the word search with all the solutions found after the FindWord method is run
             */
            void PrintWordSearchSolution();

        private:
            /**
             * @brief Stores each different direction that can be searched in the word search
             */
            enum test_direction {
                UP_LEFT = 0,
                UP_RIGHT = 1,
                DOWN_RIGHT = 2,
                DOWN_LEFT = 3,
                UP = 4,
                RIGHT = 5,
                DOWN = 6,
                LEFT = 7,
                END = 8
            };

            /**
             * @brief Tests if the next letter in the word_to_find is present in the provided direction
             * 
             * @param vertical_pos 
             * @param horizontal_pos 
             * @param word_to_find_pos 
             * @param direction 
             */
            void TestSurroundingLettersForWord(const size_t vertical_pos, const size_t horizontal_pos, const size_t word_to_find_pos, const test_direction direction);

            /**
             * @brief Tests if the provided letter is present in the provided direction
             * 
             * @param curr_vertical_pos 
             * @param curr_horizontal_pos 
             * @param find 
             * @param direction 
             * @return true 
             * @return false 
             */
            bool TestForCharInDirection(const size_t curr_vertical_pos, const size_t curr_horizontal_pos, const char find, const test_direction direction);

            /**
             * @brief tests each direction for a cross of from the middle letter 'A' of MAS
             * 
             * @param curr_vertical_pos 
             * @param curr_horizontal_pos 
             */
            void TestEachDirectionForCross(const size_t curr_vertical_pos, const size_t curr_horizontal_pos);

            /**
             * @brief Based on provided positions and direction, returns the new vector indexies (returns std::string::npos if the index would be invalid in the case the bounds of the vector are hit)
             * 
             * @param curr_vertical 
             * @param curr_horizontal 
             * @param direction 
             * @return std::pair<size_t, size_t> 
             */
            std::pair<size_t, size_t> GetNewIndexes(const size_t curr_vertical, const size_t curr_horizontal, const test_direction direction);

            /**
             * @brief returns the reverse lookup direction to provided direction (if UP is provided, will return DOWN)
             * 
             * @param curr_direction 
             * @return test_direction 
             */
            test_direction GetReverseDirection(const test_direction curr_direction);

            /**
             * @brief stores the word search vector
             */
            std::vector<std::vector<char>> word_search_;

            /**
             * @brief an empty grid of matching size of the word search, stores positions of solutions when found
             */
            std::vector<std::vector<char>> placeholder_search_;

            /**
             * @brief the word that is to be found
             */
            std::vector<char> word_to_find_;

            /**
             * @brief continuous count of the number of word matches found
             */
            uint64_t num_of_matches_;

            /**
             * @brief thread safety mutex
             */
            std::mutex mutex_;

            /**
             * @brief vector of chars for MAS cross search
             */
            const std::vector<char> kCrossWord{'M', 'A', 'S'};
    };
} // namespace day_four

#endif
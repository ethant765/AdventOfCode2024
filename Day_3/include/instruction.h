#ifndef DAY_THREE_INSTRUCTION_H_
#define DAY_THREE_INSTRUCTION_H_

#include <cstdint>

namespace day_three {
    /**
     * @brief Stores the values and instructions for each pair
     */
    class Instruction {
        public:
            /**
             * @brief Construct a new Instruction
             * 
             * @param value_one 
             * @param value_two 
             * @param multiply 
             */
            explicit Instruction(uint16_t value_one, uint16_t value_two, bool multiply);

            /**
             * @brief Destroy the Instruction object
             */
            ~Instruction() = default;

            /**
             * @brief Returns if the values should be multiplied or not
             * 
             * @return true 
             * @return false 
             */
            bool DoWeMultiply();

            /**
             * @brief Returns the multiplied total of the values
             * 
             * @return uint32_t
             */
            uint32_t Mul();
        private:
            /**
             * @brief object to store value 1
             */
            uint16_t value_one_;

            /**
             * @brief object to store value 2
             */
            uint16_t value_two_;

            /**
             * @brief object to store multiply or not instruction
             */
            bool do_multiply_;
    };

} // namespace day_three

#endif
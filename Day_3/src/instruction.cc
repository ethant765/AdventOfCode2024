#include "../include/instruction.h"

#include <cstdint>

Instruction::Instruction(uint16_t value_one, uint16_t value_two, bool multiply) : value_one_(value_one), value_two_(value_two), do_multiply_(multiply) {
}

bool Instruction::DoWeMultiply() {
    return do_multiply_;
}

uint32_t Instruction::Mul() {
    return value_one_ * value_two_;
}
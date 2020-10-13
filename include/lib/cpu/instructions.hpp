#pragma once

#include "lib/cpu/instruction/instruction_builder.hpp"
#include "lib/memory/memory_location.hpp"

namespace gb_lib {

extern Instruction* instructions[2][256];
extern Instruction* interrupts[5];

}

#ifndef _CPU_INSTRUCTIONS_H_
#define _CPU_INSTRUCTIONS_H_

#include <cstdint>

#include "lib/cpu/instruction/op/affect_flags_type.hpp"
#include "lib/cpu/instruction/instruction_argument.hpp"
#include "lib/cpu/instruction/instruction.hpp"
#include "lib/cpu/instruction/instruction_builder.hpp"
#include "lib/memory/memory_location.hpp"

namespace gb_lib {

extern Instruction* instructions[2][256];
extern Instruction* interrupts[5];

}

#endif

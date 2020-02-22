#include "lib/cpu/instruction/op/alu/decrement.hpp"

namespace gb_lib {

int32_t Decrement::execute(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t context)
{
    return context - 1;
}

}

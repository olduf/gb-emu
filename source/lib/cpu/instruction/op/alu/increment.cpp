#include "lib/cpu/instruction/op/alu/increment.hpp"

namespace gb_lib {

int32_t Increment::execute(Registers* registers, MMU* mmu, int32_t opArgument, int32_t context)
{
    return context + 1;
}

}

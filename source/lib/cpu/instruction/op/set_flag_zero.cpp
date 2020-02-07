#include "lib/cpu/instruction/op/set_flag_zero.hpp"

namespace gb_lib {

SetFlagZero::SetFlagZero(bool value)
{
    this->value = value;
}

int32_t SetFlagZero::execute(Registers* registers, MMU* mmu, int32_t opArgument, int32_t context)
{
    registers->getFlags().setZero(this->value);

    return context;
}

}

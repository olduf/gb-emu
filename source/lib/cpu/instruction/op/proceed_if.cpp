#include "lib/cpu/instruction/op/proceed_if.hpp"

namespace gb_lib {

ProceedIf::ProceedIf(FlagCondition condition)
{
    this->ableToProceed = true;
    this->condition = condition;
}

bool ProceedIf::canProceed()
{
    return this->ableToProceed;
}

int32_t ProceedIf::execute(Registers* registers, MMU* mmu, int32_t opArgument, int32_t context)
{
    switch (this->condition)
    {
        case FlagCondition::CARRY: { this->ableToProceed = registers->getFlags().isCarry(); break; }
        case FlagCondition::NOT_CARRY: { this->ableToProceed = !registers->getFlags().isCarry(); break; }
        case FlagCondition::NOT_ZERO: { this->ableToProceed = !registers->getFlags().isZero(); break; }
        case FlagCondition::ZERO: { this->ableToProceed = registers->getFlags().isZero(); break; }
    }

    return context;
}

}

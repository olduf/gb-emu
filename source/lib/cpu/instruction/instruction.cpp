#include "lib/cpu/instruction/instruction.hpp"

namespace gb_lib {

Instruction::Instruction(Op** ops, std::string label, uint32_t code, uint32_t cpuCycle, uint32_t cpuCycleOverride, uint32_t lengthInBytes, uint32_t numberOfOperations)
{
    this->label = label;
    this->code = code;
    this->cpuCycle = cpuCycle;
    this->cpuCycleOverride = cpuCycleOverride;
    this->lengthInBytes = lengthInBytes;
    this->numberOfOperations = numberOfOperations;

    for (uint32_t i = 0; i < this->numberOfOperations; i++)
    {
        this->ops[i] = ops[i];
    }
}

Instruction::~Instruction()
{
    for (uint32_t i = 0; i < this->numberOfOperations; i++)
    {
        delete this->ops[i];
        this->ops[i] = nullptr;
    }
}

std::string Instruction::getLabel()
{
    return this->label;
}

uint32_t Instruction::getArgumentLength()
{
    return this->lengthInBytes - 1;
}

uint32_t Instruction::getLengthInBytes()
{
    return this->lengthInBytes;
}

uint32_t Instruction::getCpuCycle()
{
    return this->cpuCycle;
}

uint32_t Instruction::getCpuCycleOverride()
{
    return this->cpuCycleOverride;
}

uint32_t Instruction::getNumberOfOperations()
{
    return this->numberOfOperations;
}

uint32_t Instruction::getCode()
{
    return this->code;
}

Op** Instruction::getOps()
{
    return this->ops;
}

uint32_t Instruction::execute(Registers* registers, MMU* mmu, int32_t context)
{
    int32_t opArgument = this->getOpArgument(mmu, registers->getPC());
    registers->incrementPC(this->lengthInBytes);

    bool canProceed = true;

    for (uint32_t i = 0; i < this->numberOfOperations; i++)
    {
        if (!canProceed)
        {
            break;
        }

        Op* op = this->ops[i];
        context = op->execute(registers, mmu, opArgument, context);
        canProceed = op->canProceed();
    }

    if (canProceed)
    {
        return this->cpuCycle;
    }
    else
    {
        return this->cpuCycleOverride;
    }
}

int32_t Instruction::getOpArgument(MMU* mmu, uint16_t pc)
{
    int32_t opArgument = 0;

    if (this->lengthInBytes > 1)
    {
        opArgument = mmu->getByte(pc + 1);
    }

    if (this->lengthInBytes > 2)
    {
        opArgument = (opArgument & 0xFF) | ((mmu->getByte(pc + 2) << 8) & 0xFF00);
    }

    return opArgument;
}

}

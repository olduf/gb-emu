#ifndef _CPU_INSTRUCTION_INSTRUCTION_H_
#define _CPU_INSTRUCTION_INSTRUCTION_H_

#include <string>

#include "lib/cpu/instruction/op/op.hpp"

namespace gb_lib {

class Instruction
{
public:
    Instruction(Op** ops, std::string label, uint32_t code, uint32_t cpuCycle, uint32_t cpuCycleOverride, uint32_t lengthInBytes, uint32_t numberOfOperations);
    ~Instruction();

    std::string getLabel();
    uint32_t getArgumentLength();
    uint32_t getLengthInBytes();
    uint32_t getCpuCycle();
    uint32_t getCpuCycleOverride();
    uint32_t getNumberOfOperations();
    uint32_t getCode();
    Op** getOps();

    uint32_t execute(Registers* registers, MemorySpace* mmu, int32_t context);

private:
    Op* ops[8];
    std::string label;
    uint32_t code;
    uint32_t cpuCycle;
    uint32_t cpuCycleOverride;
    uint32_t lengthInBytes;
    uint32_t numberOfOperations;

private:
    int32_t getOpArgument(MemorySpace* mmu, uint16_t pc);
};

}

#endif

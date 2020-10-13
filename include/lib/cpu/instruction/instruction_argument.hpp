#pragma once

#include <functional>

#include "lib/cpu/registers.hpp"
#include "lib/memory/memory_space.hpp"

namespace gb_lib {

class InstructionArgument
{
public:
    static const InstructionArgument A;
    static const InstructionArgument B;
    static const InstructionArgument C;
    static const InstructionArgument D;
    static const InstructionArgument E;
    static const InstructionArgument H;
    static const InstructionArgument L;
    static const InstructionArgument AF;
    static const InstructionArgument BC;
    static const InstructionArgument DE;
    static const InstructionArgument HL;
    static const InstructionArgument SP;
    static const InstructionArgument PC;
    static const InstructionArgument N;
    static const InstructionArgument NN;
    static const InstructionArgument _BC;
    static const InstructionArgument _DE;
    static const InstructionArgument _HL;
    static const InstructionArgument _C;
    static const InstructionArgument _N;
    static const InstructionArgument _NN;

    int32_t get(Registers* registers, MemorySpace* mmu, int32_t opArgument) const;
    void set(Registers* registers, MemorySpace* mmu, int32_t opArgument, int32_t value) const;

    uint32_t getArgumentLengthInBytes() const;

    const InstructionArgument& operator= (const InstructionArgument& instructionArgument) { return instructionArgument; }

private:
    InstructionArgument(
        uint32_t argumentLengthInBytes,
        std::function<int32_t(Registers*, MemorySpace*, int32_t)> getOperation,
        std::function<void(Registers*, MemorySpace*, int32_t, int32_t)> setOperation);

    uint32_t argumentLengthInBytes;

    std::function<int32_t(Registers*, MemorySpace*, int32_t)> getOperation;
    std::function<void(Registers*, MemorySpace*, int32_t, int32_t)> setOperation;
};

}

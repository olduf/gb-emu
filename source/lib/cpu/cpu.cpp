#include "lib/cpu/cpu.hpp"

namespace gb_lib {

Cpu::Cpu(InterruptHandler* interruptHandler, MMU* mmu, Registers* registers, SpeedModeHandler* speedModeHandler)
{
    this->cpuState = CpuState::INSTRUCTION;
    this->interruptHandler = interruptHandler;
    this->mmu = mmu;
    this->registers = registers;
    this->speedModeHandler = speedModeHandler;
}

uint32_t Cpu::tick()
{
    Instruction* instruction = this->interruptHandler->getInterruptInstruction();
    uint32_t consumedCpuCycle = 4;

    if (instruction == nullptr && this->cpuState == CpuState::INSTRUCTION)
    {
        uint32_t prefixed = 0;
        uint8_t opCode = mmu->getByte(this->registers->getPC());

        switch (opCode)
        {
            case CB_PREFIX:
                prefixed = 1;
                break;

            // EI only enable interrupts after the next instruction, that's why we handle it differently
            case EI:
                this->interruptHandler->runEI();
                this->registers->incrementPC(1);
                return 4;
                break;

            case HALT:
                this->cpuState = CpuState::HALTED;
                break;

            case STOP:
                this->cpuState = CpuState::STOPPED;
                this->speedModeHandler->handleSpeedMode();
                break;
        }

        instruction = instructions[prefixed][opCode];
    }

    if (instruction != nullptr)
    {
        consumedCpuCycle = instruction->execute(this->registers, this->mmu, 0);

        this->interruptHandler->handleEI();

        // need to validate behavior with HALT/STOP
        this->cpuState = CpuState::INSTRUCTION;
    }

    return consumedCpuCycle;
}

// It takes 20 cycles to dispatch an interrupt. If CPU is in HALT mode, it takes an extra 4 cycles (TODO).

}

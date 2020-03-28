#include "lib/cpu/cpu.hpp"

namespace gb_lib {

Cpu::Cpu(InterruptHandler* interruptHandler, MemorySpace* mmu, Registers* registers, SpeedModeHandler* speedModeHandler)
{
    this->haltBug = false;
    this->cpuState = CpuState::INSTRUCTION;
    this->interruptHandler = interruptHandler;
    this->mmu = mmu;
    this->registers = registers;
    this->speedModeHandler = speedModeHandler;
}

uint32_t Cpu::tick()
{
    Instruction* instruction = nullptr;
    uint32_t consumedCpuCycle = 4;

    // https://github.com/AntonioND/giibiiadvance/blob/master/docs/TCAGBD.pdf
    // 4.10. The HALT Instruction Behaviour
    // HALT mode is entered. It works like the IME = 1 case, but when a IF flag is set and the corresponding IE flag is also set,
    // the CPU doesn't jump to the interrupt vector, it just continues executing instructions. The IF flags aren't cleared.
    //
    // Here we already have the next instruction, we emulate the bug by decrementing the PC
    if (this->cpuState == CpuState::HALTED && !this->registers->isIME() && this->interruptHandler->isInterruptRequested())
    {
        this->cpuState = CpuState::INSTRUCTION;
    }
    else
    {
        instruction = this->interruptHandler->getInterruptInstruction();
    }

    if (instruction == nullptr && this->cpuState == CpuState::INSTRUCTION)
    {
        uint32_t prefixed = 0;
        uint16_t pc = this->registers->getPC();
        uint8_t opCode = mmu->getByte(pc);

        switch (opCode)
        {
            case CB_PREFIX:
                prefixed = 1;
                opCode = mmu->getByte(pc + 1);
                break;

            // EI only enable interrupts after the next instruction, that's why we handle it differently
            case EI:
                this->interruptHandler->runEI();
                this->registers->incrementPC(1);
                return 4;

            case HALT:
                {
                    this->haltBug = this->interruptHandler->isHaltBugState();
                    this->registers->incrementPC(1);

                    if (!this->haltBug)
                    {
                        this->cpuState = CpuState::HALTED;
                    }
                }
                return 4;

            case STOP:
                this->cpuState = CpuState::STOPPED;
                this->speedModeHandler->handleSpeedMode();
                this->registers->incrementPC(1);
                return 4;
        }

        instruction = instructions[prefixed][opCode];
    }

    if (instruction != nullptr)
    {
        // https://github.com/AntonioND/giibiiadvance/blob/master/docs/TCAGBD.pdf
        // 4.10. The HALT Instruction Behaviour
        // HALT bug occurs. The CPU fails to increase PC when executing the next instruction.
        //
        // Here we already have the next instruction, we emulate the bug by decrementing the PC
        if (this->haltBug)
        {
            this->haltBug = false;
            this->registers->decrementPC(1);
        }

        consumedCpuCycle = instruction->execute(this->registers, this->mmu, 0);

        this->interruptHandler->handleEI();

        // https://github.com/AntonioND/giibiiadvance/blob/master/docs/TCAGBD.pdf
        // 4.9. Interrupt Handling
        // It takes 20 clocks to dispatch an interrupt. If CPU is in HALT mode, another extra 4 clocks are needed.
        if (this->cpuState == CpuState::HALTED)
        {
            consumedCpuCycle += 4;
        }

        // TODO - need to validate behavior with STOP
        this->cpuState = CpuState::INSTRUCTION;
    }

    return consumedCpuCycle;
}

}

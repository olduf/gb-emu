#pragma once

#include <string>

#include "lib/cpu/cpu.hpp"
#include "lib/cpu/interrupt_handler.hpp"
#include "lib/cpu/speedmode_handler.hpp"
#include "lib/graphic/lcd_handler.hpp"
#include "lib/memory/dma/dma_handler.hpp"
#include "lib/memory/dma/hdma_handler.hpp"
#include "lib/memory/mmu_factory.hpp"
#include "lib/timer/timer_handler.hpp"

// temporary
#include <cstdio>

namespace gb_lib {

class GameBoy
{
public:
    GameBoy(std::string romPath); // graphic, audio
    ~GameBoy();

    void stepFrame();
    void stepInstruction();

    void reset();
    void stop();

    void saveState(uint32_t stateId);
    void loadState(uint32_t stateId);

private:
    // audio processing unit
    Cpu* cpu;
    DMAHandler* dmaHandler;
    DMAMediator dmaMediator;
    DMAMediator hdmaMediator;
    HDMAHandler* hdmaHandler;
    InterruptHandler* interruptHandler;
    InterruptMediator interruptMediator;
    LCDHandler* lcdHandler;
    MemorySpace* mmu;
    PPU* ppu;
    // pixel processing unit
    Registers registers;
    SetTacAuditor* setTacAuditor;
    SpeedModeHandler* speedModeHandler;
    TimerHandler* timerHandler;
    TimerUtil timerUtil;
    uint32_t cpuCycle;

private:
    const uint32_t CPU_CYCLES_FOR_FRAME = 69905;

private:
    void initialize();

// temporary
private:
    uint8_t* rom;
    uint32_t loadFile(std::string romPath);

};

}

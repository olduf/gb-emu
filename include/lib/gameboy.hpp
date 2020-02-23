#ifndef _GAMEBOY_H_
#define _GAMEBOY_H_

#include "lib/cpu/cpu.hpp"
#include "lib/cpu/speedmode_handler.hpp"
#include "lib/graphic/lcd_handler.hpp"
#include "lib/memory/mmu_factory.hpp"
#include "lib/timer_handler.hpp"

namespace gb_lib {

class GameBoy
{
public:
    GameBoy(std::string romPath); // graphic, audio

    void stepFrame();

    void reset();
    void stop();

    void saveState(uint32_t stateId);
    void loadState(uint32_t stateId);

private:
    // audio processing unit
    Cpu* cpu;
    LCDHandler* lcdHandler;
    MemorySpace* mmu;
    // pixel processing unit
    Registers* registers;
    SpeedModeHandler* speedModeHandler;
    TimerHandler* timerHandler;
    uint32_t cpuCycle;

private:
    const uint32_t CPU_CYCLES_FOR_FRAME = 69905;

private:
    void initialize();
    void stepInstruction();

};

}

#endif

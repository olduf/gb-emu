#include "lib/gameboy.hpp"

namespace gb_lib {

GameBoy::GameBoy(std::string romPath)
{
    this->cpuCycle = 0;

    MMUFactory mmuFactory;
}

void GameBoy::stepFrame()
{
    while (this->cpuCycle < (CPU_CYCLES_FOR_FRAME * static_cast<uint32_t>(this->speedModeHandler->getSpeedMode())))
    {
        this->stepInstruction();
    }

    // render frame

    this->cpuCycle = 0;
}

void GameBoy::stepInstruction()
{
    // need to handle DMA
    uint32_t consumedCpuCycle = cpu->tick();
    this->cpuCycle += consumedCpuCycle;

    this->dmaHandler->tick(consumedCpuCycle);
    this->timerHandler->updateTimers(consumedCpuCycle);
    this->lcdHandler->updateLCD(consumedCpuCycle);
    // updateAudio(consumedCpuCycle);
}

void GameBoy::reset()
{
    //
}

void GameBoy::stop()
{
    //
}

void saveState(uint32_t stateId)
{
    //
}

void loadState(uint32_t stateId)
{
    //
}

void GameBoy::initialize()
{
    //
}

}

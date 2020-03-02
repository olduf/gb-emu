#include "lib/gameboy.hpp"

namespace gb_lib {

GameBoy::GameBoy(std::string romPath)
{
    this->cpuCycle = 0;

    MMUFactory mmuFactory;
}

GameBoy::~GameBoy()
{
  delete this->cpu;
  this->cpu = nullptr;

  delete this->dmaHandler;
  this->dmaHandler = nullptr;

  delete this->hdmaHandler;
  this->hdmaHandler = nullptr;

  delete this->lcdHandler;
  this->lcdHandler = nullptr;

  delete this->mmu;
  this->mmu = nullptr;

  delete this->registers;
  this->registers = nullptr;

  delete this->speedModeHandler;
  this->speedModeHandler = nullptr;

  delete this->timerHandler;
  this->timerHandler = nullptr;
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
    uint32_t consumedCpuCycle = 4;

    if (this->hdmaHandler->isTransferInProgress())
    {
        this->hdmaHandler->tick(consumedCpuCycle);
    }
    else
    {
        consumedCpuCycle = cpu->tick();
    }

    this->dmaHandler->tick(consumedCpuCycle);
    this->timerHandler->updateTimers(consumedCpuCycle);
    this->lcdHandler->updateLCD(consumedCpuCycle);
    // updateAudio(consumedCpuCycle);

    this->cpuCycle += consumedCpuCycle;
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

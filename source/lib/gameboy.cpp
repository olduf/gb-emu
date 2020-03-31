#include "lib/gameboy.hpp"

// debug
#include "lib/cpu/instructions.hpp"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>

namespace gb_lib {

GameBoy::GameBoy(const char* romPath)
{
    this->cpuCycle = 0;

    uint32_t romSize = this->loadFile(romPath);
    bool isCGB = false; // TODO

    MMUFactory mmuFactory;
    this->mmu = mmuFactory.create(rom, romSize, &(this->dmaMediator),  &(this->hdmaMediator), &(this->timerMediator), isCGB);

    this->interruptHandler = new InterruptHandler(this->mmu, &(this->registers));
    this->speedModeHandler = new SpeedModeHandler(this->mmu);

    this->dmaHandler = new DMAHandler(this->mmu, &(this->dmaMediator), this->speedModeHandler);
    this->hdmaHandler = new HDMAHandler(this->mmu, &(this->dmaMediator), this->speedModeHandler);
    this->cpu = new Cpu(this->interruptHandler, this->mmu, &(this->registers), this->speedModeHandler);
    this->ppu = new PPU(this->mmu, nullptr);

    this->lcdHandler = new LCDHandler(this->interruptHandler, this->mmu, this->ppu, isCGB);
    this->timerHandler = new TimerHandler(this->interruptHandler, this->mmu, &(this->timerMediator));
}

GameBoy::~GameBoy()
{
    // temporary
    delete this->rom;

    delete this->cpu;
    this->cpu = nullptr;

    delete this->dmaHandler;
    this->dmaHandler = nullptr;

    delete this->hdmaHandler;
    this->hdmaHandler = nullptr;

    delete this->interruptHandler;
    this->interruptHandler = nullptr;

    delete this->lcdHandler;
    this->lcdHandler = nullptr;

    delete this->mmu;
    this->mmu = nullptr;

    delete this->ppu;
    this->ppu = nullptr;

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
    //--------------------------------------------------------------------------
    // DEBUG
    //--------------------------------------------------------------------------
    Instruction* instruction;
    uint16_t cb = 0;
    uint16_t pc = this->registers.getPC();
    uint8_t code = this->mmu->getByte(pc);
    if (code == 0xCB) {
      instruction = gb_lib::instructions[1][mmu->getByte(pc) + 1];
      cb = 1;
    } else {
      instruction = gb_lib::instructions[0][code];
    }

    std::stringstream ss;
    ss << "PC: " << std::setw(4) << std::setfill('0') << std::hex << pc << ", operation: " << instruction->getLabel() << " ";
    if (instruction->getArgumentLength() == 1) {
      ss << "(n = " << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << (uint16_t)this->mmu->getByte(pc + cb + 1) << ")";
    } else if (instruction->getArgumentLength() == 2) {
      ss << "(nn = " << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << (uint16_t)this->mmu->getByte(pc + cb + 2);
      ss << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << (uint16_t)this->mmu->getByte(pc + cb + 1) << ")";
    }
    ss << "\n";
    std::cout << ss.str();
    //--------------------------------------------------------------------------

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

uint32_t GameBoy::loadFile(const char* romPath)
{
    FILE* file = fopen(romPath, "rb");
    uint32_t sizeOfFile = 0;

    if (file) {
        fseek(file, 0, SEEK_END);
        sizeOfFile = ftell(file);
        fseek(file, 0, SEEK_SET);

        this->rom = new uint8_t[sizeOfFile];

        fread(this->rom, 1, sizeOfFile, file);
        fclose(file);
      }

    return sizeOfFile;
}

}

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
    this->timerHandler = new TimerHandler(&(this->interruptMediator));
    this->mmu = mmuFactory.create(rom, romSize, &(this->dmaMediator),  &(this->hdmaMediator), &(this->interruptMediator), this->timerHandler, isCGB);

    this->interruptHandler = new InterruptHandler(&(this->interruptMediator), this->mmu, &(this->registers));
    this->speedModeHandler = new SpeedModeHandler(this->mmu);

    this->dmaHandler = new DMAHandler(this->mmu, &(this->dmaMediator), this->speedModeHandler);
    this->hdmaHandler = new HDMAHandler(this->mmu, &(this->dmaMediator), this->speedModeHandler);
    this->cpu = new Cpu(this->interruptHandler, this->mmu, &(this->registers), this->speedModeHandler);
    this->ppu = new PPU(this->mmu, nullptr);

    this->lcdHandler = new LCDHandler(this->interruptHandler, this->mmu, this->ppu, isCGB);
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
        uint16_t cb = 0;
        uint16_t pc = registers.getPC();
        uint8_t code = mmu->getByte(pc);
        Instruction* instruction = nullptr;

        if (code == 0xCB)
        {
            instruction = gb_lib::instructions[1][mmu->getByte(pc + 1)];
            cb = 1;
        }
        else
        {
            instruction = gb_lib::instructions[0][code];
        }

      std::stringstream ss;
      ss << "PC: " << std::setw(4) << std::setfill('0') << std::hex << pc << ", operation: " << instruction->getLabel();

      if (cb == 0) {
          if (instruction->getArgumentLength() == 1)
          {
              ss << " (n = " << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << (uint16_t)mmu->getByte(pc + cb + 1) << ")";
          }
          else if (instruction->getArgumentLength() == 2)
          {
                ss << " (nn = " << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << (uint16_t)mmu->getByte(pc + cb + 2);
                ss << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << (uint16_t)mmu->getByte(pc + cb + 1) << ")";
          }
      }

      // ss << " - LY: " << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << (uint16_t)mmu->getByteInternal(gb_lib::LY);
      // ss << " - LCDC: " << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << (uint16_t)mmu->getByteInternal(gb_lib::LCDC);
       ss << " - DIV: " << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << (uint16_t)mmu->getByte(gb_lib::DIV);
       ss << " " << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << (uint16_t)mmu->getByte(gb_lib::DIV - 1);
       ss << " - TIMA: " << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << (uint16_t)mmu->getByte(gb_lib::TIMA);
       ss << " - TMA: " << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << (uint16_t)mmu->getByte(gb_lib::TMA);
       ss << " - TAC: " << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << (uint16_t)mmu->getByte(gb_lib::TAC);
      // ss << " - IF: " << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << (uint16_t)mmu->getByteInternal(gb_lib::IF);
      // ss << " - IE: " << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << (uint16_t)mmu->getByteInternal(gb_lib::IE);
      // ss << " - FF80: " << std::setw(2) << std::setfill('0') << std::uppercase << std::hex << (uint16_t)mmu->getByteInternal(0xFF80);
      ss << " AF: " << std::setw(4) << std::setfill('0') << std::uppercase << std::hex << registers.getAF() << ", ";
      ss << "BC: " << std::setw(4) << std::setfill('0') << std::uppercase << std::hex << registers.getBC() << ", ";
      ss << "DE: " << std::setw(4) << std::setfill('0') << std::uppercase << std::hex << registers.getDE() << ", ";
      ss << "HL: " << std::setw(4) << std::setfill('0') << std::uppercase << std::hex << registers.getHL() << ", ";
      ss << "SP: " << std::setw(4) << std::setfill('0') << std::uppercase << std::hex << registers.getSP() << ", ";
      ss << "PC: " << std::setw(4) << std::setfill('0') << std::uppercase << std::hex << registers.getPC() << ", ";
      ss << "IME: " << registers.isIME();
      ss <<  "\n";
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
    this->timerHandler->update(consumedCpuCycle);
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

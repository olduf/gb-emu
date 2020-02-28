#include "lib/memory/mmu_factory.hpp"

namespace gb_lib {

MMU* MMUFactory::create(uint8_t* rom, uint32_t romSize, DMAMediator* dmaMediator, bool isCGB)
{
    MemorySpace* cartridge = this->cartridgeFactory.create(rom, romSize);
    MemorySpace* highRam = new HighRam();
    MemorySpace* ioRegisters = new IORegisters(dmaMediator, isCGB);
    MemorySpace* oam = new OAM(ioRegisters);

    MemorySpace* unusedMemoryFEA0_FEFF = nullptr;
    MemorySpace* videoRam = nullptr;
    MemorySpace* workingRam = nullptr;

    if (isCGB)
    {
        unusedMemoryFEA0_FEFF = new CGBUnusedMemoryFEA0_FEFF();
        videoRam = new CGBVideoRam(ioRegisters);
        workingRam = new CGBWorkingRam(ioRegisters);
    }
    else
    {
        unusedMemoryFEA0_FEFF = new UnusedMemoryFEA0_FEFF();
        videoRam = new VideoRam(ioRegisters);
        workingRam = new WorkingRam();
    }

    return new MMU(cartridge, highRam, ioRegisters, oam, unusedMemoryFEA0_FEFF, videoRam, workingRam);
}

}

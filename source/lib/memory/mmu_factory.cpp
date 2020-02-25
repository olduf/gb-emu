#include "lib/memory/mmu_factory.hpp"

namespace gb_lib {

MMU* MMUFactory::create(uint8_t* rom, uint32_t romSize, bool isCGB)
{
    MemorySpace* cartridge = this->cartridgeFactory.create(rom, romSize);
    MemorySpace* ioRegisters = new IORegisters(isCGB);

    MemorySpace* videoRam = nullptr;
    MemorySpace* workingRam = nullptr;

    if (isCGB)
    {
        videoRam = new CGBVideoRam(ioRegisters);
        workingRam = new CGBWorkingRam(ioRegisters);
    }
    else
    {
        videoRam = new VideoRam(ioRegisters);
        workingRam = new WorkingRam();
    }

    return new MMU(cartridge, ioRegisters, videoRam, workingRam);
}

}

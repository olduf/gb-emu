#include "lib/memory/mmu_factory.hpp"

namespace gb_lib {

MMU* MMUFactory::create(uint8_t* rom, uint32_t romSize, bool isCGB)
{
  MemorySpace* cartridge = this->cartridgeFactory.create(rom, romSize);
  MemorySpace* ioRegisters = new IORegisters(isCGB);
  MemorySpace* workingRam = new WorkingRam(ioRegisters);

  return new MMU(cartridge, ioRegisters, workingRam);
}

}

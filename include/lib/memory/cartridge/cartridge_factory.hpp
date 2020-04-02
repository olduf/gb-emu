#ifndef _MEMORY_CARTRIDGE_FACTORY_H_
#define _MEMORY_CARTRIDGE_FACTORY_H_

#include "lib/memory/cartridge/mbc1.hpp"
#include "lib/memory/cartridge/rom.hpp"

namespace gb_lib {

class CartridgeFactory
{
public:
    MemorySpace* create(uint8_t* rom, uint32_t romFileSize);

private:
    uint32_t getNumberOfRamBanks(uint8_t valueInHeader);
    uint32_t getNumberOfRomBanks(uint8_t valueInHeader);
};

}

#endif

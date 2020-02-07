#include "lib/memory/cartridge/rom.hpp"

namespace gb_lib {

Rom::Rom(uint8_t* data, uint32_t size)
{
    uint32_t actualSize = size < 0x8000 ? size : 0x8000;

    memcpy(this->rom, data, actualSize);
}

uint8_t Rom::getByte(uint16_t address)
{
    if (address < 0x8000) {
      return this->rom[address];
    } else {
      return 0;
    }
}

}

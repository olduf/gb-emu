#ifndef _MEMORY_IO_REGISTERS_H_
#define _MEMORY_IO_REGISTERS_H_

#include "lib/memory/dma/dma_mediator.hpp"
#include "lib/memory/memory_location.hpp"
#include "lib/memory/memory_space.hpp"
#include "lib/util/bit_util.hpp"

namespace gb_lib {

class IORegisters : public MemorySpace
{
public:
    IORegisters(DMAMediator* dmaMediator, DMAMediator* hdmaMediator, bool isCGB);

    uint8_t getByte(uint16_t address);
    uint8_t getByteInternal(uint16_t address);
    void setByte(uint16_t address, uint8_t value);
    void setByteInternal(uint16_t address, uint8_t value);

private:
    DMAMediator* dmaMediator;
    DMAMediator* hdmaMediator;
    uint8_t registers[0x80] = {};
    uint8_t FF55Mask = 0;
};

}

#endif

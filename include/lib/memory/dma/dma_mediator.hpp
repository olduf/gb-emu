#ifndef _MEMORY_DMA_MEDIATOR_H_
#define _MEMORY_DMA_MEDIATOR_H_

#include <cstdint>

namespace gb_lib {

class DMAMediator
{
public:
    DMAMediator();

    bool isTransferRequested();
    void requestTransfer(uint8_t source);

    uint16_t getSource();

private:
    bool transferRequested;
    uint16_t source;
};

}

#endif

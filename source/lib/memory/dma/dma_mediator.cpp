#include "lib/memory/dma/dma_mediator.hpp"

namespace gb_lib {

DMAMediator::DMAMediator()
{
    this->transferRequested = false;
    this->source = 0;
}

bool DMAMediator::isTransferRequested()
{
    return this->transferRequested;
}

void DMAMediator::requestTransfer(uint8_t source)
{
    if (!this->transferRequested)
    {
        this->transferRequested = true;
        this->source = static_cast<uint16_t>(source << 8);
    }
}

uint16_t DMAMediator::getSource()
{
    this->transferRequested = false;

    return this->source;
}

}

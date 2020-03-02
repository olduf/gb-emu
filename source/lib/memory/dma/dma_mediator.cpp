#include "lib/memory/dma/dma_mediator.hpp"

namespace gb_lib {

void DMAMediator::requestTransfer(bool transferRequested)
{
    this->transferRequested = transferRequested;
}

bool DMAMediator::isTransferRequested()
{
    return this->transferRequested;
}

bool DMAMediator::isTransferInProgress()
{
    return this->transferInProgress;
}

void DMAMediator::setTransferInProgress(bool transferInProgress)
{
    this->transferInProgress = transferInProgress;
}

}

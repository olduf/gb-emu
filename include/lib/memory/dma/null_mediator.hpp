#pragma once

#include "lib/memory/dma/dma_mediator.hpp"

namespace gb_lib {

class NullMediator : public DMAMediator
{
public:
    void requestTransfer(bool transferRequested);
};

}

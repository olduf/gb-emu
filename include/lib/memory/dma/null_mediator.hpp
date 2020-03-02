#ifndef _MEMORY_NULL_MEDIATOR_H_
#define _MEMORY_NULL_MEDIATOR_H_

#include "lib/memory/dma/dma_mediator.hpp"

namespace gb_lib {

class NullMediator : public DMAMediator
{
public:
    void requestTransfer(bool transferRequested);
};

}

#endif

#pragma once

#include <cstdint>

namespace gb_lib {

class DMAMediator
{
public:
    virtual void requestTransfer(bool transferRequested);
    bool isTransferRequested();

    bool isTransferInProgress();
    void setTransferInProgress(bool transferInProgress);

protected:
    bool transferRequested = false;
    bool transferInProgress = false;
};

}

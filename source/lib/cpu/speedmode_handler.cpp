#include "lib/cpu/speedmode_handler.hpp"

namespace gb_lib {

SpeedModeHandler::SpeedModeHandler(MemorySpace* mmu)
{
    this->mmu = mmu;
    this->speedMode = SpeedMode::NORMAL;
}

SpeedMode SpeedModeHandler::getSpeedMode()
{
    return this->speedMode;
}

void SpeedModeHandler::handleSpeedMode()
{
    uint8_t speedModeRegisterValue = this->mmu->getByte(KEY1);

    if ((speedModeRegisterValue & 1) == 1)
    {
        this->mmu->setByte(KEY1, BitUtil::toggleBit(speedModeRegisterValue, 7) & 0xFE);

        this->speedMode = ((speedModeRegisterValue & 0x80) == 1) ? SpeedMode::NORMAL : SpeedMode::DOUBLE;
    }
}

}

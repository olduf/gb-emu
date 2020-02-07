#include "lib/util/bit_util.hpp"

namespace gb_lib {

bool BitUtil::getBit(uint8_t byte, uint8_t n)
{
    return (byte >> n) & 1;
}

uint8_t BitUtil::setBit(uint8_t byte, uint8_t n)
{
    return byte | (1 << n);
}

uint8_t BitUtil::clearBit(uint8_t byte, uint8_t n)
{
    return byte & ~(1 << n);
}

uint8_t BitUtil::toggleBit(uint8_t byte, uint8_t n)
{
    return byte ^ (1 << n);
}

}

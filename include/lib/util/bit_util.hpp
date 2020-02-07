#ifndef _UTIL_BIT_UTIL_H_
#define _UTIL_BIT_UTIL_H_

#include <cstdint>

namespace gb_lib {

class BitUtil
{
public:
    static bool getBit(uint8_t byte, uint8_t n);
    static uint8_t setBit(uint8_t byte, uint8_t n);
    static uint8_t clearBit(uint8_t byte, uint8_t n);
    static uint8_t toggleBit(uint8_t byte, uint8_t n);
};

}

#endif

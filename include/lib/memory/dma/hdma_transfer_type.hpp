#pragma once

#include <cstdint>

namespace gb_lib {

enum class HDMATransferType : uint8_t
{
    GENERAL = 0,
    HBLANK = 0x80
};

}

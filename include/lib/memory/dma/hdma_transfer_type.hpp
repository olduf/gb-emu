#ifndef _MEMORY_HDMA_TRANSFER_TYPE_H_
#define _MEMORY_HDMA_TRANSFER_TYPE_H_

#include <cstdint>

namespace gb_lib {

enum class HDMATransferType : uint8_t
{
    GENERAL = 0,
    HBLANK = 0x80
};

}

#endif

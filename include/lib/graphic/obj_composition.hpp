#ifndef _GRAPHIC_OBJ_COMPOSITION_H_
#define _GRAPHIC_OBJ_COMPOSITION_H_

#include <cstdint>

namespace gb_lib {

enum class ObjComposition : uint8_t
{
    BLOCK_8_BY_8 = 0,
    BLOCK_8_BY_16 = 4
};

}

#endif

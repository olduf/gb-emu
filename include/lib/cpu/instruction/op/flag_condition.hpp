#ifndef _CPU_INSTRUCTION_OP_FLAG_CONDITION_H_
#define _CPU_INSTRUCTION_OP_FLAG_CONDITION_H_

namespace gb_lib {

enum class FlagCondition
{
    CARRY,
    NOT_CARRY,
    NOT_ZERO,
    ZERO
};

}

#endif

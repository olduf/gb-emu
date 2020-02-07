#ifndef _CPU_INSTRUCTION_BUILDER_H_
#define _CPU_INSTRUCTION_BUILDER_H_

#include <cstdint>
#include <stdexcept>
#include <string>

#include "lib/cpu/flags.hpp"
#include "lib/cpu/instruction/op/affect_flags_type.hpp"
#include "lib/cpu/instruction/op/alu/add.hpp"
#include "lib/cpu/instruction/op/alu/add_s8.hpp"
#include "lib/cpu/instruction/op/alu/add_u8.hpp"
#include "lib/cpu/instruction/op/alu/add_u16.hpp"
#include "lib/cpu/instruction/op/alu/add_u16_s8.hpp"
#include "lib/cpu/instruction/op/alu/add_with_carry.hpp"
#include "lib/cpu/instruction/op/alu/and_bytes.hpp"
#include "lib/cpu/instruction/op/alu/compare.hpp"
#include "lib/cpu/instruction/op/alu/complement.hpp"
#include "lib/cpu/instruction/op/alu/complement_carry_flag.hpp"
#include "lib/cpu/instruction/op/alu/decimal_adjust.hpp"
#include "lib/cpu/instruction/op/alu/decrement.hpp"
#include "lib/cpu/instruction/op/alu/decrement_d8.hpp"
#include "lib/cpu/instruction/op/alu/increment.hpp"
#include "lib/cpu/instruction/op/alu/increment_d8.hpp"
#include "lib/cpu/instruction/op/alu/or_bytes.hpp"
#include "lib/cpu/instruction/op/alu/reset_bit.hpp"
#include "lib/cpu/instruction/op/alu/rotate_left.hpp"
#include "lib/cpu/instruction/op/alu/rotate_left_and_carry.hpp"
#include "lib/cpu/instruction/op/alu/rotate_right.hpp"
#include "lib/cpu/instruction/op/alu/rotate_right_and_carry.hpp"
#include "lib/cpu/instruction/op/alu/set_bit.hpp"
#include "lib/cpu/instruction/op/alu/set_carry_flag.hpp"
#include "lib/cpu/instruction/op/alu/subtract.hpp"
#include "lib/cpu/instruction/op/alu/subtract_with_carry.hpp"
#include "lib/cpu/instruction/op/alu/shift_left_arithmetic.hpp"
#include "lib/cpu/instruction/op/alu/shift_right_arithmetic.hpp"
#include "lib/cpu/instruction/op/alu/shift_right_logical.hpp"
#include "lib/cpu/instruction/op/alu/swap_nibbles.hpp"
#include "lib/cpu/instruction/op/alu/test_bit.hpp"
#include "lib/cpu/instruction/op/alu/xor_bytes.hpp"
#include "lib/cpu/instruction/op/enable_interrupts.hpp"
#include "lib/cpu/instruction/op/flag_condition.hpp"
#include "lib/cpu/instruction/op/jump.hpp"
#include "lib/cpu/instruction/op/load.hpp"
#include "lib/cpu/instruction/op/load_sp_to_nn.hpp"
#include "lib/cpu/instruction/op/op.hpp"
#include "lib/cpu/instruction/op/pop.hpp"
#include "lib/cpu/instruction/op/proceed_if.hpp"
#include "lib/cpu/instruction/op/push.hpp"
#include "lib/cpu/instruction/op/scalar.hpp"
#include "lib/cpu/instruction/op/set_flag_zero.hpp"
#include "lib/cpu/instruction/op/store.hpp"
#include "lib/cpu/instruction/instruction_argument.hpp"
#include "lib/cpu/instruction/instruction.hpp"

namespace gb_lib {

class InstructionBuilder
{
public:
    InstructionBuilder(uint32_t code, uint32_t cpuCycle, uint32_t lengthInBytes, std::string label);

    Instruction* build();

    InstructionBuilder& add(const InstructionArgument* argument, AffectFlagsType affectFlagsType);
    InstructionBuilder& addWithCarry(const InstructionArgument* argument);
    InstructionBuilder& andBytes(const InstructionArgument* argument);
    InstructionBuilder& complementCarryFlag();
    InstructionBuilder& compareBytes(const InstructionArgument* argument);
    InstructionBuilder& complement();
    InstructionBuilder& decimalAdjust();
    InstructionBuilder& decrement(AffectFlagsType affectFlagsType);
    InstructionBuilder& enableInterrupts(bool value);
    InstructionBuilder& increment(AffectFlagsType affectFlagsType);
    InstructionBuilder& jump();
    InstructionBuilder& load(const InstructionArgument* source);
    InstructionBuilder& loadSPToNN();
    InstructionBuilder& orBytes(const InstructionArgument* argument);
    InstructionBuilder& pop();
    InstructionBuilder& proceedIf(FlagCondition condition, uint32_t cpuCycleOverride);
    InstructionBuilder& push();
    InstructionBuilder& resetBit(uint8_t n);
    InstructionBuilder& rotateLeft();
    InstructionBuilder& rotateLeftAndCarry();
    InstructionBuilder& rotateRight();
    InstructionBuilder& rotateRightAndCarry();
    InstructionBuilder& scalar(uint32_t value);
    InstructionBuilder& setCarryFlag();
    InstructionBuilder& setBit(uint8_t n);
    InstructionBuilder& setFlagZero(bool value);
    InstructionBuilder& shiftLeftArithmetic();
    InstructionBuilder& shiftRightArithmetic();
    InstructionBuilder& shiftRightLogical();
    InstructionBuilder& store(const InstructionArgument* destination);
    InstructionBuilder& subtract(const InstructionArgument* argument);
    InstructionBuilder& subtractWithCarry(const InstructionArgument* argument);
    InstructionBuilder& swapNibbles();
    InstructionBuilder& testBit(uint8_t n);
    InstructionBuilder& xorBytes(const InstructionArgument* argument);

private:
    Op* ops[8];
    std::string label;
    uint32_t cpuCycle;
    uint32_t cpuCycleOverride;
    uint32_t lengthInBytes;
    uint32_t numberOfOperations;
    uint32_t code;

    void addOperation(Op* op);
};

}

#endif

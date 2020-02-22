#include "lib/cpu/instruction/instruction_builder.hpp"

namespace gb_lib {

InstructionBuilder::InstructionBuilder(uint32_t code, uint32_t cpuCycle, uint32_t lengthInBytes, std::string label)
{
    this->code = code;
    this->cpuCycle = cpuCycle;
    this->cpuCycleOverride = 0;
    this->label = label;
    this->lengthInBytes = lengthInBytes;
    this->numberOfOperations = 0;
}

Instruction* InstructionBuilder::build()
{
    if (this->cpuCycleOverride == 0)
    {
        this->cpuCycleOverride = this->cpuCycle;
    }

    return new Instruction(this->ops, this->label, this->code, this->cpuCycle, this->cpuCycleOverride, this->lengthInBytes, this->numberOfOperations);
}

InstructionBuilder& InstructionBuilder::add(const InstructionArgument* argument, AffectFlagsType affectFlagsType)
{
    Op* operation = nullptr;

    switch (affectFlagsType)
    {
        case AffectFlagsType::S8 : { operation = new AddS8(argument); break;}
        case AffectFlagsType::U8 : { operation = new AddU8(argument); break;}
        case AffectFlagsType::U16 : { operation = new AddU16(argument); break;}
        case AffectFlagsType::U16_S8 : { operation = new AddU16S8(argument); break;}
        default: { operation = new Add(argument); }
    }

    addOperation(operation);
    return *this;
}

InstructionBuilder& InstructionBuilder::addWithCarry(const InstructionArgument* argument)
{
    addOperation(new AddWithCarry(argument));
    return *this;
}

InstructionBuilder& InstructionBuilder::andBytes(const InstructionArgument* argument)
{
    addOperation(new AndBytes(argument));
    return *this;
}

InstructionBuilder& InstructionBuilder::compareBytes(const InstructionArgument* argument)
{
    addOperation(new Compare(argument));
    return *this;
}

InstructionBuilder& InstructionBuilder::complement()
{
    addOperation(new Complement());
    return *this;
}

InstructionBuilder& InstructionBuilder::complementCarryFlag()
{
    addOperation(new ComplementCarryFlag());
    return *this;
}

InstructionBuilder& InstructionBuilder::decimalAdjust()
{
    addOperation(new DecimalAdjust());
    return *this;
}

InstructionBuilder& InstructionBuilder::decrement(AffectFlagsType affectFlagsType)
{
    if (affectFlagsType == AffectFlagsType::U8)
    {
        addOperation(new DecrementD8());
    }
    else
    {
        addOperation(new Decrement());
    }

    return *this;
}

InstructionBuilder& InstructionBuilder::enableInterrupts(bool value)
{
    addOperation(new EnableInterrupts(value));
    return *this;
}

InstructionBuilder& InstructionBuilder::increment(AffectFlagsType affectFlagsType)
{
    if (affectFlagsType == AffectFlagsType::U8)
    {
        addOperation(new IncrementD8());
    }
    else
    {
        addOperation(new Increment());
    }

    return *this;
}

InstructionBuilder& InstructionBuilder::jump()
{
    addOperation(new Jump());
    return *this;
}

InstructionBuilder& InstructionBuilder::load(const InstructionArgument* source)
{
    addOperation(new Load(source));
    return *this;
}

InstructionBuilder& InstructionBuilder::loadSPToNN()
{
    addOperation(new LoadSPToNN());
    return *this;
}

InstructionBuilder& InstructionBuilder::orBytes(const InstructionArgument* argument)
{
    addOperation(new OrBytes(argument));
    return *this;
}

InstructionBuilder& InstructionBuilder::pop()
{
    addOperation(new Pop());
    return *this;
}

InstructionBuilder& InstructionBuilder::proceedIf(FlagCondition condition, uint32_t cpuCycleOverride)
{
  this->cpuCycleOverride = cpuCycleOverride;
  addOperation(new ProceedIf(condition));
  return *this;
}

InstructionBuilder& InstructionBuilder::push()
{
    addOperation(new Push());
    return *this;
}

InstructionBuilder& InstructionBuilder::resetBit(uint8_t n)
{
    if (n < 8)
    {
        addOperation(new ResetBit(n));
    }

    return *this;
}

InstructionBuilder& InstructionBuilder::rotateLeft()
{
    addOperation(new RotateLeft());
    return *this;
}

InstructionBuilder& InstructionBuilder::rotateLeftAndCarry()
{
    addOperation(new RotateLeftAndCarry());
    return *this;
}

InstructionBuilder& InstructionBuilder::rotateRight()
{
    addOperation(new RotateRight());
    return *this;
}

InstructionBuilder& InstructionBuilder::rotateRightAndCarry()
{
    addOperation(new RotateRightAndCarry());
    return *this;
}

InstructionBuilder& InstructionBuilder::scalar(uint32_t value)
{
    addOperation(new Scalar(value));
    return *this;
}

InstructionBuilder& InstructionBuilder::setCarryFlag()
{
    addOperation(new SetCarryFlag());
    return *this;
}

InstructionBuilder& InstructionBuilder::setBit(uint8_t n)
{
    if (n < 8)
    {
        addOperation(new SetBit(n));
    }

    return *this;
}

InstructionBuilder& InstructionBuilder::setFlagZero(bool value)
{
    addOperation(new SetFlagZero(value));
    return *this;
}

InstructionBuilder& InstructionBuilder::shiftLeftArithmetic()
{
    addOperation(new ShiftLeftArithmetic());
    return *this;
}

InstructionBuilder& InstructionBuilder::shiftRightArithmetic()
{
    addOperation(new ShiftRightArithmetic());
    return *this;
}

InstructionBuilder& InstructionBuilder::shiftRightLogical()
{
    addOperation(new ShiftRightLogical());
    return *this;
}

InstructionBuilder& InstructionBuilder::store(const InstructionArgument* destination)
{
    addOperation(new Store(destination));
    return *this;
}

InstructionBuilder& InstructionBuilder::subtract(const InstructionArgument* argument)
{
    addOperation(new Subtract(argument));
    return *this;
}

InstructionBuilder& InstructionBuilder::subtractWithCarry(const InstructionArgument* argument)
{
    addOperation(new SubtractWithCarry(argument));
    return *this;
}

InstructionBuilder& InstructionBuilder::swapNibbles()
{
    addOperation(new SwapNibbles());
    return *this;
}

InstructionBuilder& InstructionBuilder::testBit(uint8_t n)
{
    if (n < 8)
    {
        addOperation(new TestBit(n));
    }

    return *this;
}

InstructionBuilder& InstructionBuilder::xorBytes(const InstructionArgument* argument)
{
    addOperation(new XorBytes(argument));
    return *this;
}

void InstructionBuilder::addOperation(Op* op)
{
    this->ops[this->numberOfOperations] = op;
    this->numberOfOperations++;
}

}

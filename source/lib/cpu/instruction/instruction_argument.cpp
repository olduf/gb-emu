#include "lib/cpu/instruction/instruction_argument.hpp"

namespace gb_lib {

InstructionArgument::InstructionArgument(
    uint32_t argumentLengthInBytes,
    std::function<int32_t(Registers*, MMU*, int32_t)> getOperation,
    std::function<void(Registers*, MMU*, int32_t, int32_t)> setOperation)
{
    this->argumentLengthInBytes = argumentLengthInBytes;
    this->getOperation = getOperation;
    this->setOperation = setOperation;
}

int32_t InstructionArgument::get(Registers* registers, MMU* mmu, int32_t opArgument) const
{
    return this->getOperation(registers, mmu, opArgument);
}

void InstructionArgument::set(Registers* registers, MMU* mmu, int32_t opArgument, int32_t value) const
{
    this->setOperation(registers, mmu, opArgument, value);
}

uint32_t InstructionArgument::getArgumentLengthInBytes() const
{
    return this->argumentLengthInBytes;
}

const InstructionArgument InstructionArgument::A(
    0,
    [] (Registers* registers, MMU* mmu, int32_t opArgument) -> int32_t {
        return static_cast<int32_t>(registers->getA());
    },
    [] (Registers* registers, MMU* mmu, int32_t opArgument, int32_t value) {
        registers->setA(static_cast<uint8_t>(value & 0xFF));
    }
);

const InstructionArgument InstructionArgument::B(
    0,
    [] (Registers* registers, MMU* mmu, int32_t opArgument) -> int32_t {
        return static_cast<int32_t>(registers->getB());
    },
    [] (Registers* registers, MMU* mmu, int32_t opArgument, int32_t value) {
        registers->setB(static_cast<uint8_t>(value & 0xFF));
    }
);

const InstructionArgument InstructionArgument::C(
    0,
    [] (Registers* registers, MMU* mmu, int32_t opArgument) -> int32_t {
        return static_cast<int32_t>(registers->getC());
    },
    [] (Registers* registers, MMU* mmu, int32_t opArgument, int32_t value) {
        registers->setC(static_cast<uint8_t>(value & 0xFF));
    }
);

const InstructionArgument InstructionArgument::D(
    0,
    [] (Registers* registers, MMU* mmu, int32_t opArgument) -> int32_t {
        return static_cast<int32_t>(registers->getD());
    },
    [] (Registers* registers, MMU* mmu, int32_t opArgument, int32_t value) {
        registers->setD(static_cast<uint8_t>(value & 0xFF));
    }
);

const InstructionArgument InstructionArgument::E(
    0,
    [] (Registers* registers, MMU* mmu, int32_t opArgument) -> int32_t {
        return static_cast<int32_t>(registers->getE());
    },
    [] (Registers* registers, MMU* mmu, int32_t opArgument, int32_t value) {
        registers->setE(static_cast<uint8_t>(value & 0xFF));
    }
);

const InstructionArgument InstructionArgument::H(
    0,
    [] (Registers* registers, MMU* mmu, int32_t opArgument) -> int32_t {
        return static_cast<int32_t>(registers->getH());
    },
    [] (Registers* registers, MMU* mmu, int32_t opArgument, int32_t value) {
        registers->setH(static_cast<uint8_t>(value & 0xFF));
    }
);

const InstructionArgument InstructionArgument::L(
    0,
    [] (Registers* registers, MMU* mmu, int32_t opArgument) -> int32_t {
        return static_cast<int32_t>(registers->getL());
    },
    [] (Registers* registers, MMU* mmu, int32_t opArgument, int32_t value) {
        registers->setL(static_cast<uint8_t>(value & 0xFF));
    }
);

const InstructionArgument InstructionArgument::AF(
    0,
    [] (Registers* registers, MMU* mmu, int32_t opArgument) -> int32_t {
        return static_cast<int32_t>(registers->getAF());
    },
    [] (Registers* registers, MMU* mmu, int32_t opArgument, int32_t value) {
        registers->setAF(static_cast<uint16_t>(value & 0xFFFF));
    }
);

const InstructionArgument InstructionArgument::BC(
    0,
    [] (Registers* registers, MMU* mmu, int32_t opArgument) -> int32_t {
        return static_cast<int32_t>(registers->getBC());
    },
    [] (Registers* registers, MMU* mmu, int32_t opArgument, int32_t value) {
        registers->setBC(static_cast<uint16_t>(value & 0xFFFF));
    }
);

const InstructionArgument InstructionArgument::DE(
    0,
    [] (Registers* registers, MMU* mmu, int32_t opArgument) -> int32_t {
        return static_cast<int32_t>(registers->getDE());
    },
    [] (Registers* registers, MMU* mmu, int32_t opArgument, int32_t value) {
        registers->setDE(static_cast<uint16_t>(value & 0xFFFF));
    }
);

const InstructionArgument InstructionArgument::HL(
    0,
    [] (Registers* registers, MMU* mmu, int32_t opArgument) -> int32_t {
        return static_cast<int32_t>(registers->getHL());
    },
    [] (Registers* registers, MMU* mmu, int32_t opArgument, int32_t value) {
        registers->setHL(static_cast<uint16_t>(value & 0xFFFF));
    }
);

const InstructionArgument InstructionArgument::SP(
    0,
    [] (Registers* registers, MMU* mmu, int32_t opArgument) -> int32_t {
        return static_cast<int32_t>(registers->getSP());
    },
    [] (Registers* registers, MMU* mmu, int32_t opArgument, int32_t value) {
        registers->setSP(static_cast<uint16_t>(value & 0xFFFF));
    }
);

const InstructionArgument InstructionArgument::PC(
    0,
    [] (Registers* registers, MMU* mmu, int32_t opArgument) -> int32_t {
        return static_cast<int32_t>(registers->getPC());
    },
    [] (Registers* registers, MMU* mmu, int32_t opArgument, int32_t value) {
        registers->setPC(static_cast<uint16_t>(value & 0xFFFF));
    }
);

const InstructionArgument InstructionArgument::N(
    1,
    [] (Registers* registers, MMU* mmu, int32_t opArgument) -> int32_t {
        return static_cast<int32_t>(opArgument & 0xFF);
    },
    [] (Registers* registers, MMU* mmu, int32_t opArgument, int32_t value)  { /*throw*/ }
);

const InstructionArgument InstructionArgument::NN(
    2,
    [] (Registers* registers, MMU* mmu, int32_t opArgument) -> int32_t {
        return static_cast<int32_t>(opArgument & 0xFFFF);
    },
    [] (Registers* registers, MMU* mmu, int32_t opArgument, int32_t value) { /*throw*/ }
);

const InstructionArgument InstructionArgument::_BC(
    0,
    [] (Registers* registers, MMU* mmu, int32_t opArgument) -> int32_t {
        return static_cast<int32_t>(mmu->getByte(registers->getBC()));
    },
    [] (Registers* registers, MMU* mmu, int32_t opArgument, int32_t value) {
        mmu->setByte(registers->getBC(), static_cast<uint8_t>(value & 0xFF));
    }
);

const InstructionArgument InstructionArgument::_DE(
    0,
    [] (Registers* registers, MMU* mmu, int32_t opArgument) -> int32_t {
        return static_cast<int32_t>(mmu->getByte(registers->getDE()));
    },
    [] (Registers* registers, MMU* mmu, int32_t opArgument, int32_t value) {
        mmu->setByte(registers->getDE(), static_cast<uint8_t>(value & 0xFF));
    }
);

const InstructionArgument InstructionArgument::_HL(
    0,
    [] (Registers* registers, MMU* mmu, int32_t opArgument) -> int32_t {
        return static_cast<int32_t>(mmu->getByte(registers->getHL()));
    },
    [] (Registers* registers, MMU* mmu, int32_t opArgument, int32_t value) {
        mmu->setByte(registers->getHL(), static_cast<uint8_t>(value & 0xFF));
    }
);

const InstructionArgument InstructionArgument::_C(
    0,
    [] (Registers* registers, MMU* mmu, int32_t opArgument) -> int32_t {
        return static_cast<int32_t>(mmu->getByte(0xFF00 | registers->getC()));
    },
    [] (Registers* registers, MMU* mmu, int32_t opArgument, int32_t value) {
        mmu->setByte(0xFF00 | registers->getC(), static_cast<uint8_t>(value & 0xFF));
    }
);

const InstructionArgument InstructionArgument::_N(
    1,
    [] (Registers* registers, MMU* mmu, int32_t opArgument) -> int32_t {
        return static_cast<int32_t>(mmu->getByte(0xFF00 | (opArgument & 0xFF)));
    },
    [] (Registers* registers, MMU* mmu, int32_t opArgument, int32_t value) {
        mmu->setByte(0xFF00 | (opArgument & 0xFF), static_cast<uint8_t>(value & 0xFF));
    }
);

const InstructionArgument InstructionArgument::_NN(
    2,
    [] (Registers* registers, MMU* mmu, int32_t opArgument) -> int32_t {
        return static_cast<int32_t>(mmu->getByte((opArgument & 0xFFFF)));
    },
    [] (Registers* registers, MMU* mmu, int32_t opArgument, int32_t value) {
        mmu->setByte((opArgument & 0xFFFF), static_cast<uint8_t>(value & 0xFF));
    }
);

}

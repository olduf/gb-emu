#include "lib/cpu/registers.hpp"

namespace gb_lib {

// registers initial values found in https://github.com/AntonioND/giibiiadvance/blob/master/docs/TCAGBD.pdf
Registers::Registers()
{
    // Classic GameBoy - GB mode
    this->setAF(0x01B0);
    this->setBC(0x0013);
    this->setDE(0X00D8);
    this->setHL(0X014D);
    this->setSP(0xFFFE);
    this->setPC(0x0100);
    this->setIME(true);

/*
    // GameBoy Color - GB mode
    this->setAF(0x1180);
    this->setBC(0x0000);
    this->setDE(0X0008);
    this->setHL(0X007C);
    this->setSP(0xFFFE);
    this->setPC(0x0000); // 0x0100
    this->setIME(true);

    // GameBoy Color - GBC mode
    this->setAF(0x1180);
    this->setBC(0x0000);
    this->setDE(0XFF56);
    this->setHL(0X000D);
    this->setSP(0xFFFE);
    this->setPC(0x0100);
    this->setIME(true);
*/
}

uint8_t Registers::getA()
{
    return this->a;
}

void Registers::setA(uint8_t a)
{
    this->a = a;
}

uint16_t Registers::getAF()
{
    return static_cast<uint16_t>(this->a << 8 | this->flags.getValue());
}

void Registers::setAF(uint16_t af)
{
    this->a = static_cast<uint8_t>((af & 0xFF00) >> 8);
    this->flags.setValue(static_cast<uint8_t>(af & 0x00FF));
}

uint8_t Registers::getB()
{
    return this->b;
}

void Registers::setB(uint8_t b)
{
    this->b = b;
}

uint8_t Registers::getC()
{
    return this->c;
}

void Registers::setC(uint8_t c)
{
    this->c = c;
}

uint16_t Registers::getBC()
{
    return static_cast<uint16_t>((this->b << 8) | this->c);
}

void Registers::setBC(uint16_t bc)
{
    this->b = static_cast<uint8_t>((bc & 0xFF00) >> 8);
    this->c = static_cast<uint8_t>(bc & 0x00FF);
}

uint8_t Registers::getD()
{
    return this->d;
}

void Registers::setD(uint8_t d)
{
    this->d = d;
}

uint8_t Registers::getE()
{
    return this->e;
}

void Registers::setE(uint8_t e)
{
    this->e = e;
}

uint16_t Registers::getDE()
{
    return static_cast<uint16_t>((this->d << 8) | this->e);
}

void Registers::setDE(uint16_t de)
{
    this->d = static_cast<uint8_t>((de & 0xFF00) >> 8);
    this->e = static_cast<uint8_t>(de & 0x00FF);
}

uint8_t Registers::getF()
{
    return this->flags.getValue();
}

Flags& Registers::getFlags()
{
    return this->flags;
}

uint8_t Registers::getH()
{
    return this->h;
}

void Registers::setH(uint8_t h)
{
    this->h = h;
}

uint8_t Registers::getL()
{
    return this->l;
}

void Registers::setL(uint8_t l)
{
    this->l = l;
}

uint16_t Registers::getHL()
{
    return static_cast<uint16_t>((this->h << 8) | this->l);
}

void Registers::setHL(uint16_t hl)
{
    this->h = static_cast<uint8_t>((hl & 0xFF00) >> 8);
    this->l = static_cast<uint8_t>(hl & 0x00FF);
}

uint16_t Registers::getSP()
{
    return this->sp;
}

void Registers::setSP(uint16_t sp)
{
    this->sp = sp;
}

void Registers::decrementSP()
{
    this->sp -= 1;
}
void Registers::incrementSP()
{
    this->sp += 1;
}

uint16_t Registers::getPC()
{
    return this->pc;
}

void Registers::setPC(uint16_t pc)
{
    this->pc = pc;
}

void Registers::decrementPC(uint16_t value)
{
    this->pc -= value;
}

void Registers::incrementPC(uint16_t value)
{
    this->pc += value;
}

bool Registers::isIME()
{
    return this->ime;
}

void Registers::setIME(bool ime)
{
    this->ime = ime;
}

}

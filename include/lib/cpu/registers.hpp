#pragma once

#include "lib/cpu/flags.hpp"

namespace gb_lib {

class Registers
{
public:
    Registers();

    uint8_t getA();
    void setA(uint8_t a);

    uint16_t getAF();
    void setAF(uint16_t af);

    uint8_t getB();
    void setB(uint8_t b);

    uint8_t getC();
    void setC(uint8_t c);

    uint16_t getBC();
    void setBC(uint16_t bc);

    uint8_t getD();
    void setD(uint8_t d);

    uint8_t getE();
    void setE(uint8_t e);

    uint16_t getDE();
    void setDE(uint16_t de);

    uint8_t getF();
    Flags& getFlags();

    uint8_t getH();
    void setH(uint8_t h);

    uint8_t getL();
    void setL(uint8_t l);

    uint16_t getHL();
    void setHL(uint16_t hl);

    uint16_t getSP();
    void setSP(uint16_t sp);
    void decrementSP();
    void incrementSP();

    uint16_t getPC();
    void setPC(uint16_t pc);
    void decrementPC(uint16_t value);
    void incrementPC(uint16_t value);

    bool isIME();
    void setIME(bool ime);

private:
    uint8_t a;
    uint8_t b;
    uint8_t c;
    uint8_t d;
    uint8_t e;
    Flags flags;
    uint8_t h;
    uint8_t l;
    uint16_t sp;
    uint16_t pc;
    bool ime;
};

}

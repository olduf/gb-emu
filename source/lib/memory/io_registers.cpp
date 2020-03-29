#include "lib/memory/io_registers.hpp"

namespace gb_lib {

IORegisters::IORegisters(DMAMediator* dmaMediator, DMAMediator* hdmaMediator, bool isCGB)
{
    this->dmaMediator = dmaMediator;
    this->hdmaMediator = hdmaMediator;

    // https://github.com/AntonioND/giibiiadvance/blob/master/docs/TCAGBD.pdf
    // 9.6. FF55H - HDMA5 - GBC Mode - HDMA Length/Mode/Start (R/W)
    // Returns FFh in DMG and GBC in DMG mode.
    // In GBC mode, returns 1 if DMA is in progress, 0 otherwise.
    // TODO - revisit, might split into 2 files
    if (!isCGB)
    {
        this->FF55Mask = 0xFF;
    }
}

uint8_t IORegisters::getByte(uint16_t address)
{
    uint16_t effectiveAddress = address & 0x00FF;

    switch (effectiveAddress)
    {
        case 0x00:
            return this->registers[effectiveAddress] | 0xC0;
            break;
        case 0x01:
        case 0x02:
        case 0x03:
        case 0x04:
        case 0x05:
        case 0x06:
            return this->registers[effectiveAddress];
            break;
        case 0x07:
            return this->registers[effectiveAddress] | 0xF8;
            break;
        case 0x08:
        case 0x09:
        case 0x0A:
        case 0x0B:
        case 0x0C:
        case 0x0D:
        case 0x0E:
            return this->registers[effectiveAddress];
            break;
        case 0x0F:
            return this->registers[effectiveAddress] | 0xE0;
            break;
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
        case 0x18:
        case 0x19:
        case 0x1A:
        case 0x1B:
        case 0x1C:
        case 0x1D:
        case 0x1E:
        case 0x1F:
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x26:
        case 0x27:
        case 0x28:
        case 0x29:
        case 0x2A:
        case 0x2B:
        case 0x2C:
        case 0x2D:
        case 0x2E:
        case 0x2F:
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
        case 0x3A:
        case 0x3B:
        case 0x3C:
        case 0x3D:
        case 0x3E:
        case 0x3F:
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
        case 0x44:
        case 0x45:
        case 0x46:
        case 0x47:
        case 0x48:
        case 0x49:
        case 0x4A:
        case 0x4B:
        case 0x4C:
        case 0x4D:
        case 0x4E:
        case 0x4F:
        case 0x50:
            return this->registers[effectiveAddress];
            break;
        case 0x51:
        case 0x52:
        case 0x53:
        case 0x54:
            return 0xFF;
            break;
        case 0x55:
            return (this->hdmaMediator->isTransferInProgress() ? 0x80 : 0) | this->FF55Mask;
            break;
        case 0x56:
        case 0x57:
        case 0x58:
        case 0x59:
        case 0x5A:
        case 0x5B:
        case 0x5C:
        case 0x5D:
        case 0x5E:
        case 0x5F:
        case 0x60:
        case 0x61:
        case 0x62:
        case 0x63:
        case 0x64:
        case 0x65:
        case 0x66:
        case 0x67:
        case 0x68:
        case 0x69:
        case 0x6A:
        case 0x6B:
        case 0x6C:
        case 0x6D:
        case 0x6E:
        case 0x6F:
        case 0x70:
        case 0x71:
        case 0x72:
        case 0x73:
        case 0x74:
        case 0x75:
        case 0x76:
        case 0x77:
        case 0x78:
        case 0x79:
        case 0x7A:
        case 0x7B:
        case 0x7C:
        case 0x7D:
        case 0x7E:
        case 0x7F:
            return this->registers[effectiveAddress];
            break;
    }
}

uint8_t IORegisters::getByteInternal(uint16_t address)
{
    return this->registers[address & 0x00FF];
}

void IORegisters::setByte(uint16_t address, uint8_t value)
{
    uint16_t effectiveAddress = address & 0x00FF;

    switch (effectiveAddress)
    {
        case 0x00:
        case 0x01:
        case 0x02:
        case 0x03:
            this->registers[effectiveAddress] = value;
            break;
        case 0x04: // DIV
            this->registers[effectiveAddress] = 0;
            break;
        case 0x05:
        case 0x06:
        case 0x07:
        case 0x08:
        case 0x09:
        case 0x0A:
        case 0x0B:
        case 0x0C:
        case 0x0D:
        case 0x0E:
            this->registers[effectiveAddress] = value;
            break;
        case 0x0F:
            this->registers[effectiveAddress] = (this->registers[effectiveAddress] & 0xE0) | (value & 0x1F);
            break;
        case 0x10:
        case 0x11:
        case 0x12:
        case 0x13:
        case 0x14:
        case 0x15:
        case 0x16:
        case 0x17:
        case 0x18:
        case 0x19:
        case 0x1A:
        case 0x1B:
        case 0x1C:
        case 0x1D:
        case 0x1E:
        case 0x1F:
        case 0x20:
        case 0x21:
        case 0x22:
        case 0x23:
        case 0x24:
        case 0x25:
        case 0x26:
        case 0x27:
        case 0x28:
        case 0x29:
        case 0x2A:
        case 0x2B:
        case 0x2C:
        case 0x2D:
        case 0x2E:
        case 0x2F:
        case 0x30:
        case 0x31:
        case 0x32:
        case 0x33:
        case 0x34:
        case 0x35:
        case 0x36:
        case 0x37:
        case 0x38:
        case 0x39:
        case 0x3A:
        case 0x3B:
        case 0x3C:
        case 0x3D:
        case 0x3E:
        case 0x3F:
        case 0x40:
        case 0x41:
        case 0x42:
        case 0x43:
            this->registers[effectiveAddress] = value;
            break;
        case 0x44: // LY
            {
                // http://forums.nesdev.com/viewtopic.php?f=20&t=16434&p=203762#p203762
                // Any writes to LY while the LCD is enabled are ignored.
                // When the LCD is disabled, LY is forcibly set to 0, and since it's read-only, the value never changes
                if (!BitUtil::getBit(this->registers[0x40], 7))
                {
                    this->registers[effectiveAddress] = 0;
                }
            }
            break;
        case 0x45:
            this->registers[effectiveAddress] = value;
            break;
        case 0x46: // DMA
            this->registers[effectiveAddress] = value;
            this->dmaMediator->requestTransfer(true);
            break;
        case 0x47:
        case 0x48:
        case 0x49:
        case 0x4A:
        case 0x4B:
        case 0x4C:
        case 0x4D:
        case 0x4E:
        case 0x4F:
        case 0x50:
        case 0x51:
        case 0x52:
        case 0x53:
        case 0x54:
        case 0x55:
            this->hdmaMediator->requestTransfer(true);
            this->registers[effectiveAddress] = value;
            break;
        case 0x56:
        case 0x57:
        case 0x58:
        case 0x59:
        case 0x5A:
        case 0x5B:
        case 0x5C:
        case 0x5D:
        case 0x5E:
        case 0x5F:
        case 0x60:
        case 0x61:
        case 0x62:
        case 0x63:
        case 0x64:
        case 0x65:
        case 0x66:
        case 0x67:
        case 0x68:
        case 0x69:
        case 0x6A:
        case 0x6B:
        case 0x6C:
        case 0x6D:
        case 0x6E:
        case 0x6F:
        case 0x70:
        case 0x71:
        case 0x72:
        case 0x73:
        case 0x74:
        case 0x75:
        case 0x76:
        case 0x77:
        case 0x78:
        case 0x79:
        case 0x7A:
        case 0x7B:
        case 0x7C:
        case 0x7D:
        case 0x7E:
        case 0x7F:
            this->registers[effectiveAddress] = value;
            break;
    }
}

void IORegisters::setByteInternal(uint16_t address, uint8_t value)
{
    this->registers[address & 0x00FF] = value;
}

}

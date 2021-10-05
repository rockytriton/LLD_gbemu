#include <bus.h>
#include <cart.h>
#include <ram.h>
#include <cpu.h>
#include <io.h>

// 0x0000 - 0x3FFF : ROM Bank 0
// 0x4000 - 0x7FFF : ROM Bank 1 - Switchable
// 0x8000 - 0x97FF : CHR RAM
// 0x9800 - 0x9BFF : BG Map 1
// 0x9C00 - 0x9FFF : BG Map 2
// 0xA000 - 0xBFFF : Cartridge RAM
// 0xC000 - 0xCFFF : RAM Bank 0
// 0xD000 - 0xDFFF : RAM Bank 1-7 - switchable - Color only
// 0xE000 - 0xFDFF : Reserved - Echo RAM
// 0xFE00 - 0xFE9F : Object Attribute Memory
// 0xFEA0 - 0xFEFF : Reserved - Unusable
// 0xFF00 - 0xFF7F : I/O Registers
// 0xFF80 - 0xFFFE : Zero Page

u8 bus_read(u16 address) {
    if (address < 0x8000) {
        //ROM Data
        return cart_read(address);
    } else if (address < 0xA000) {
        //Char/Map Data
        //TODO
        printf("UNSUPPORTED bus_read(%04X)\n", address);
        NO_IMPL
    } else if (address < 0xC000) {
        //Cartridge RAM
        return cart_read(address);
    } else if (address < 0xE000) {
        //WRAM (Working RAM)
        return wram_read(address);
    } else if (address < 0xFE00) {
        //reserved echo ram...
        return 0;
    } else if (address < 0xFEA0) {
        //OAM
        //TODO
        printf("UNSUPPORTED bus_read(%04X)\n", address);
        //NO_IMPL
        return 0x0;
    } else if (address < 0xFF00) {
        //reserved unusable...
        return 0;
    } else if (address < 0xFF80) {
        //IO Registers...
        //TODO
        
        //NO_IMPL
        return io_read(address);
    } else if (address == 0xFFFF) {
        //CPU ENABLE REGISTER...
        //TODO
        return cpu_get_ie_register();
    }

    //NO_IMPL
    return hram_read(address);
}

void bus_write(u16 address, u8 value) {
    if (address < 0x8000) {
        //ROM Data
        cart_write(address, value);
    } else if (address < 0xA000) {
        //Char/Map Data
        //TODO
        printf("UNSUPPORTED bus_write(%04X)\n", address);
        //NO_IMPL
    } else if (address < 0xC000) {
        //EXT-RAM
        cart_write(address, value);
    } else if (address < 0xE000) {
        //WRAM
        wram_write(address, value);
    } else if (address < 0xFE00) {
        //reserved echo ram
    } else if (address < 0xFEA0) {
        //OAM

        //TODO
        printf("UNSUPPORTED bus_write(%04X)\n", address);
       // NO_IMPL
    } else if (address < 0xFF00) {
        //unusable reserved
    } else if (address < 0xFF80) {
        //IO Registers...
        //TODO
        io_write(address, value);
        //NO_IMPL
    } else if (address == 0xFFFF) {
        //CPU SET ENABLE REGISTER
        
        cpu_set_ie_register(value);
    } else {
        hram_write(address, value);
    }
}

u16 bus_read16(u16 address) {
    u16 lo = bus_read(address);
    u16 hi = bus_read(address + 1);

    return lo | (hi << 8);
}

void bus_write16(u16 address, u16 value) {
    bus_write(address + 1, (value >> 8) & 0xFF);
    bus_write(address, value & 0xFF);
}

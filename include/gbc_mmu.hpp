#pragma once

#include "gbc_mbc.hpp"
#include "gbc_cpu_counter.hpp"
#include "utils.h"

// 0000-3FFF   16KB ROM Bank 00     (in cartridge, fixed at bank 00)
// 4000-7FFF   16KB ROM Bank 01..NN (in cartridge, switchable bank number)
// 8000-9FFF   8KB Video RAM (VRAM) (switchable bank 0-1 in CGB Mode)
// A000-BFFF   8KB External RAM     (in cartridge, switchable bank, if any)
// C000-CFFF   4KB Work RAM Bank 0 (WRAM)
// D000-DFFF   4KB Work RAM Bank 1 (WRAM)  (switchable bank 1-7 in CGB Mode)
// E000-FDFF   Same as C000-DDFF (ECHO)    (typically not used)
// FE00-FE9F   Sprite Attribute Table (OAM)
// FEA0-FEFF   Not Usable
// FF00-FF7F   I/O Ports
// FF80-FFFE   High RAM (HRAM)
// FFFF        Interrupt Enable Register
class gbc_mmu {
    private:
        bool oam_access, vram_access;
        u8 z; // for zram

    public:
        bool in_bios;

        u8 bios[0x100];
        u8 vram[0x2000]; // 8KB Video RAM (VRAM)	Only bank 0 in Non-CGB mode. Switchable bank 0/1 in CGB mode
        u8 eram[0x4000]; // 8KB External RAM	In cartridge, switchable bank if any
        u8 wram[0x4000]; // 4KB Work RAM * 2
        u8 oam[0xA0];
        u8 io[0x80];
        u8 hram[0x80];
        u8 zram[0xFFFF];

        gbc_counter *counter;
        gbc_mbc mbc;

        void init();
        u8* get_address_ptr(u16 address);

        void load_rom_file(const std::string& fname);

        u8 read_u8(u16 address);
        void write_u8(u16 address, u8 val);
        u16 read_u16(u16 address);
        void write_u16(u16 address, u16 val);

        bool read_bit(u16 address, u8 bit);
        void set_bit(u16 address, u8 bit);
        void unset_bit(u16 address, u8 bit);
};

#include <string>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "gbc_mmu.hpp"
#include "gbc_mbc.hpp"
#include "gbc_io.h"

void gbc_mmu::init() {
    in_bios = true;
    oam_access = true;
    vram_access = true;

    memset(bios, 0xFF, sizeof bios);
    memset(vram, 0xFF, sizeof vram);
    memset(wram, 0xFF, sizeof wram);
    memset(oam,  0xFF, sizeof oam);
    memset(io,   0x00, sizeof io);
    memset(hram, 0xFF, sizeof hram);
    memset(zram, 0xFF, sizeof zram);
}

u8* gbc_mmu::get_address_ptr(u16 address) {
    if (address < 0xA000) {
        return &vram[address & 0x1FFF];
    }
    if (address < 0xC000) {
        return &eram[address & 0x1FFF];
    }
    if (address < 0xE000) {
        return &wram[address & 0x1FFF];
    }
    if (address < 0xF000) {
        return &wram[address & 0x1FFF]; // echo
    }
    if (address < 0xFEA0) {
        return &oam[address & 0xFF];
    }
    if (address < 0xFF00) { // Not Usable
        z = 0;
        return &z;
    }
    if (address < 0xFF80) {
        return &io[address & 0xFF];
    }
    if (address <= 0xFFFF) {
        return &hram[address & 0xFF];
    }
    z = 0;
    return &z;
}

void gbc_mmu::load_rom_file(const std::string& fname) {
    std::ifstream t(fname);

    t.seekg(0, std::ios::end);
    mbc.rom.reserve(t.tellg());
    t.seekg(0, std::ios::beg);

    mbc.rom.assign((std::istreambuf_iterator<char>(t)),
                std::istreambuf_iterator<char>());

    mbc.rom_numbytes = mbc.rom.size();

    if (mbc.rom_numbytes == 0) {
        printf("ROM is tucked\n");
        return;
    }
    //mbc.rom = (u8*)malloc(mbc.rom_numbytes);

    //infile.read((char*)mbc.rom, mbc.rom_numbytes);
    mbc.init();
}

u8 gbc_mmu::read_u8(u16 address) {
    if (address < 0x100 && in_bios) {
        return bios[address];
    }
    if (address < 0x8000 ||
        (address >= 0xA000 && address <  0xC000)) {
        return mbc.read_u8(address);
    }

    u8 lcd_mode = io[IO_LCDSTAT & 0xFF] & MASK_LCDSTAT_MODE_FLAG;
    if (!oam_access) {
        if (address >= 0xFE00 && address < 0xFEA0) { // OAM
            return 0xFF;
        }
    }
    if (!vram_access) {
        if (address >= 0x8000 && address < 0xA000) { // VRAM
            return 0xFF;
        }
    }
    return *get_address_ptr(address);
}

void gbc_mmu::write_u8(u16 address, u8 val) {
    if (address < 0x8000 ||
        (address >= 0xA000 && address <  0xC000)) {
        return mbc.write_u8(address, val);
    }

    u8 *ptr = get_address_ptr(address);

    if (address == 0xFF50) {
        in_bios = false;
    }

    // https://gbdev.gg8.se/wiki/articles/Serial_Data_Transfer_(Link_Cable)#FF02_-_SC_-_Serial_Transfer_Control_.28R.2FW.29
    if (address == 0xFF02 && val & 0x81) {
        printf("%c", read_u8(0xFF01));
        fflush(stdout);
    }

    u8 lcd_mode = io[IO_LCDSTAT & 0xFF] & MASK_LCDSTAT_MODE_FLAG;
    // OAM is not accessible in Mode 2 or 3
    if (!vram_access) {
        if (address >= 0x8000 && address < 0xA000) { // VRAM
            return;
        }
    }
    if (!oam_access) {
        if (address >= 0xFE00 && address < 0xFEA0) // OAM
            return;
    }

    switch (address) {
        case IO_IFLAGS:
            *ptr = (val | 0b11100000);
            break;
        case IO_LCDCONT:
            *ptr = val;

            // fix LY to 0 when LCD is off
            if((*ptr & MASK_LCDCONT_LCD_Display_Enable) == 0) {
                // ensure LCD is on during vblank
                if (!read_bit(IO_LCDSTAT, OPT_MODE_VBLANK)) {
                    *ptr |= MASK_LCDCONT_LCD_Display_Enable;
                    return;
                }
                write_u8(IO_LCDSTAT, (read_u8(IO_LCDSTAT) & ~0x03) | OPT_MODE_VBLANK);
                write_u8(IO_CURLINE, 0);
            }
            break;
        case IO_DMACONT:
            *ptr = (val << 8);
            for(u8 i = 0; i < sizeof oam; i++) {
                oam[i] = read_u8(*ptr + i);
            }
            break;
        case IO_DIV:
            /* - When writing to DIV, the whole counter is reseted, so the timer
             *    is also affected. */
            counter->tima = 0;
            counter->div = 0;

            /* - When writing to DIV, if the current output is '1' and timer is
             *    enabled, as the new value after reseting DIV will be '0', the
             *    falling edge detector will detect a falling edge and TIMA will
             *    increase. */
            if (*ptr == 1 && (read_u8(IO_TAC) & MASK_TAC_ENABLE)) {
                write_u8(IO_TIMA, read_u8(IO_TIMA) + 1);
            }
            *ptr = 0x00;
            break;
        case IO_TAC: {
            /* When writing to TAC, if the previously selected multiplexer
             * input was '1' and the new input is '0', TIMA will increase too.
             * This doesn't happen when the timer is disabled, but it also
             * happens when disabling the timer (the same effect as writing to
             * DIV).
             * https://gbdev.gg8.se/wiki/articles/Timer_Obscure_Behaviour */
            u8 old_TAC = *ptr;
            u8 new_TAC = val;
            *ptr = val;

            bool glitch = false;
            u16 old_clocks = TAC_CYCLES[old_TAC & MASK_TAC_CYCLES];
            u16 new_clocks = TAC_CYCLES[new_TAC & MASK_TAC_CYCLES];
            u8 old_enable = old_TAC & MASK_TAC_ENABLE;
            u8 new_enable = new_TAC & MASK_TAC_ENABLE;

            if (old_enable == 0) {
                //TODO:
                //has a different behaviour in GBC (AGB and AGS seem to have
                //strange behaviour even in the other statements). When
                //enabling the timer and maintaining the same frequency it
                //doesn't glitch. When disabling the timer it doesn't glitch
                //either. When another change of value happens (so timer is
                //enabled after the write), the behaviour depends on a race
                //condition, so it cannot be predicted for every device.
                glitch = 0;
            } else {
                if (new_enable == 0) {
                    glitch = (counter->div & (old_clocks/2)) != 0;
                } else {
                    glitch = ((counter->div & (old_clocks/2)) != 0) && ((counter->div & (new_clocks/2)) == 0);
                }
            }

            if (glitch) {
                write_u8(IO_TIMA, read_u8(IO_TIMA) + 1);
            }
        }
        break;
        case IO_TIMA:
            //If you write to TIMA during the cycle that TMA is being loaded to it [B], the write will be ignored and TMA value will be written to TIMA instead.
            //write_io(mmu, IO_TIMA, read_u8(IO_TIMA) + 1);
            (*ptr) = val;
            break;
        case IO_JOYPAD:     // READ ONLY
            break;
        default:
            *ptr = val;
            break;
    }
}

u16 gbc_mmu::read_u16(u16 address) {
    // swap bytes for little-endian
    u16 temp = read_u8(address);
    temp |= read_u8(address+1) << 8;
    return temp;
}

void gbc_mmu::write_u16(u16 address, u16 val) {
    // swap bits for little-endian
    write_u8(address, val & 0xFF);
    write_u8(address+1, (u8)(val >> 8));
}

bool gbc_mmu::read_bit(u16 address, u8 bit) {
    return ((read_u8(address) & bit) > 0);
}

void gbc_mmu::set_bit(u16 address, u8 bit) {
    if (address == IO_LCDSTAT) {
        if (bit & OPT_MODE_OAM) {
            oam_access = false;
            vram_access = true;
        } else if (bit & OPT_MODE_OAM_VRAM) {
            oam_access = false;
            vram_access = false;
        }
    }
    u8 v = read_u8(address);
    write_u8(address, v | bit);
}

void gbc_mmu::unset_bit(u16 address, u8 bit) {
    if (address == IO_LCDSTAT) {
        if (bit & MASK_LCDSTAT_MODE_FLAG) {
            oam_access = true;
            vram_access = true;
        }
    }
    u8 v = read_u8(address);
    write_u8(address, v & ~bit);
}

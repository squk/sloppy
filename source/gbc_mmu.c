#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "gbc_mmu.h"
#include "gbc_mbc.h"
#include "gbc_io.h"

// from https://gist.github.com/domnikl/af00cc154e3da1c5d965k
void hex_dump(char *desc, void *addr, int len) {
    int i;
    unsigned char buff[17];
    unsigned char *pc = (unsigned char*)addr;

    // Output description if given.
    if (desc != NULL)
        printf ("%s:\n", desc);

    // Process every byte in the data.
    for (i = 0; i < len; i++) {
        // Multiple of 16 means new line (with line offset).

        if ((i % 16) == 0) {
            // Just don't print ASCII for the zeroth line.
            if (i != 0)
                printf("  %s\n", buff);

            // Output the offset.
            printf("  %04x ", i);
        }

        // Now the hex code for the specific character.
        printf(" %02x", pc[i]);

        // And store a printable ASCII character for later.
        if ((pc[i] < 0x20) || (pc[i] > 0x7e)) {
            buff[i % 16] = '.';
        } else {
            buff[i % 16] = pc[i];
        }

        buff[(i % 16) + 1] = '\0';
    }

    // Pad out last line if not exactly 16 characters.
    while ((i % 16) != 0) {
        printf("   ");
        i++;
    }

    // And print the final ASCII bit.
    printf("  %s\n", buff);
}

void gbc_mmu_init(gbc_mmu *mmu){
    mmu->in_bios = true;

    memset(mmu->bios, 0, sizeof mmu->bios);
    memset(mmu->vram, 0, sizeof mmu->vram);
    memset(mmu->wram, 0, sizeof mmu->wram);
    memset(mmu->oam, 0, sizeof mmu->oam);
    memset(mmu->io, 0, sizeof mmu->io);
    memset(mmu->hram, 0, sizeof mmu->hram);
    memset(mmu->zram, 0, sizeof mmu->zram);
}

u8* get_address_ptr(gbc_mmu *mmu , u16 address) {
    if (address < 0x8000) {
         printf("oh no invalid\n");
        // should never occurr, read_u8 or write_u8 should intercept before
        return &mmu->zram[0];
    }
    if (address < 0xA000) {
        return &mmu->vram[address & 0x1FFF];
    }
    if (address < 0xC000) {
        //return &mmu->eram[address & 0x1FFF];
        // should never occurr, read_u8 or write_u8 should intercept before
         printf("oh no invalid\n");
        return &mmu->zram[0];
    }
    if (address < 0xE000) {
        return &mmu->wram[address & 0x1FFF];
    }
    if (address < 0xF000) {
        return &mmu->wram[address & 0x1FFF]; // echo
    }
    if (address < 0xFEA0) {
        return &mmu->oam[address & 0xFF];
    }
    if (address < 0xFF00) { // Not Usable
        return &mmu->zram[address & 0xFF];
    }
    if (address < 0xFF80) {
        return &mmu->io[address & 0xFF];
    }
    if (address < 0xFFFF) {
        return &mmu->hram[address & 0xFF];
    }
    return &mmu->zram[address & 0x7F]; // zero page
}

u8 read_u8(gbc_mmu *mmu , u16 address) {
    if (address < 0x100 && mmu->in_bios) {
        return mmu->bios[address];
    }
    if (address < 0x8000) {
        return gbc_mbc_read_u8(mmu->cart->mbc, address);
    }
    if (address >= 0xA000 && address < 0xC000) { // cartridge RAM
        return gbc_mbc_read_u8(mmu->cart->mbc, address);
    }
    return *get_address_ptr(mmu, address);
}

void write_u8(gbc_mmu *mmu , u16 address, u8 val) {
    if (address < 0x100 && mmu->in_bios) {
        return;
    }
    if (address == 0xFF50) {
        mmu->in_bios = false;
        return;
    }
    if (address < 0x8000) {
        gbc_mbc_write_u8(mmu->cart->mbc, address, val);
        return;
    }
    if (address >= 0xA000 && address < 0xC000) { // cartridge RAM
        gbc_mbc_write_u8(mmu->cart->mbc, address, val);
        return;
    }

    // https://gbdev.gg8.se/wiki/articles/Serial_Data_Transfer_(Link_Cable)#FF02_-_SC_-_Serial_Transfer_Control_.28R.2FW.29
    if (address == 0xFF02 && val & 0x81) {
        printf("%c", read_u8(mmu, 0xFF01));
        fflush(stdout);
    }

    u8 *ptr = get_address_ptr(mmu, address);
    switch (address) {
        case IO_IFLAGS:
            *ptr = (val | 0b11100000);
            break;
        case IO_LCDCONT:
            *ptr = val;
            // fix LY to 0 when LCD is off
            if((*ptr & MASK_LCDCONT_LCD_Display_Enable) == 0) {
                // ensure LCD is on during vblank
                if (!read_bit(mmu, IO_LCDSTAT, OPT_MODE_VBLANK)) {
                    *ptr |= MASK_LCDCONT_LCD_Display_Enable;
                    return;
                }
                write_u8(mmu, IO_LCDSTAT, (read_u8(mmu, IO_LCDSTAT) & ~0x03) | OPT_MODE_VBLANK);
                write_u8(mmu, IO_CURLINE, 0);
                /*cpu->counter.lcd_count = 0;*/
            }
            break;
        case IO_DMACONT:
            *ptr = (val % 0xF1);

            for(u8 i = 0; i < sizeof mmu->oam; i++)
                mmu->oam[i] = read_u8(mmu, (*ptr << 8) + i);
            break;
        case IO_DIVIDER:
            *ptr = 0x00;
            break;
        case IO_JOYPAD: // READ ONLY
            break;
        default:
            *ptr = val;
            break;
    }
}

bool read_bit(gbc_mmu *mmu, u16 address, u8 bit) {
    return ((read_u8(mmu, address) & bit) > 0);
}

void set_bit(gbc_mmu *mmu, u16 address, u8 bit) {
    u8 v = read_u8(mmu, address);
    write_u8(mmu, address, v | bit);
}

void unset_bit(gbc_mmu *mmu, u16 address, u8 bit) {
    u8 v = read_u8(mmu, address);
    write_u8(mmu, address, v & ~bit);
}


u16 read_u16(gbc_mmu *mmu , u16 address) {
    // swap bytes for little-endian
    u16 temp = read_u8(mmu, address);
    temp |= read_u8(mmu, address+1) << 8;
    return temp;
}

void write_u16(gbc_mmu *mmu , u16 address, u16 val) {
    // swap bits for little-endian
    write_u8(mmu, address, val & 0xFF);
    write_u8(mmu, address+1, (u8)(val >> 8));
}

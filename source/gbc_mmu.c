#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "gbc_mmu.h"
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
    memset(mmu->rom, 0, sizeof mmu-> rom);
    memset(mmu->vram, 0, sizeof mmu->vram);
    memset(mmu->wram, 0, sizeof mmu->wram);
    memset(mmu->oam, 0, sizeof mmu->oam);
    memset(mmu->io, 0, sizeof mmu->io);
    memset(mmu->hram, 0, sizeof mmu->hram);
    memset(mmu->zram, 0, sizeof mmu->zram);
}

u8* get_address_ptr(gbc_mmu *mmu , u16 address) {
    if (address < 0x100 && mmu->in_bios) {
        return &mmu->bios[address];
    }
    if (address < 0x8000) {
        return &mmu->rom[address];
    }
    if (address < 0xA000) {
        return &mmu->vram[address & 0x1FFF];
    }
    if (address < 0xC000) {
        return &mmu->eram[address & 0x1FFF];
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
    return &mmu->nullish; // zero page
}

void gbc_load_rom(gbc_mmu *mmu, const void *src, size_t n) {
    memcpy(mmu->rom, src, n);
}

void gbc_load_rom_file(gbc_mmu *mmu, const char *fname) {
    char *buffer;
    long numbytes;

    FILE *infile = fopen(fname, "r");

    if(infile == NULL)
        return;

    // Get the number of bytes
    fseek(infile, 0L, SEEK_END);
    numbytes = ftell(infile);

    // reset the file position indicator to the beginning of the file
    fseek(infile, 0L, SEEK_SET);

    // grab sufficient memory for the buffer to hold the text
    buffer = (char*)calloc(numbytes, sizeof(char));

    // memory error
    if(buffer == NULL)
        return;

    // copy all the text into the buffer
    fread(buffer, sizeof(char), numbytes, infile);
    fclose(infile);

    memcpy(mmu->rom, buffer, numbytes);

     //free the memory we used for the buffer
    free(buffer);
}

u8 read_u8(gbc_mmu *mmu , u16 address) {
    /*if (address == 0xff44) return 0x90;*/
    return *get_address_ptr(mmu, address);
}

void write_u8(gbc_mmu *mmu , u16 address, u8 val) {
    u8 *ptr = get_address_ptr(mmu, address);
    if (address == 0xFF50) {
        mmu->in_bios = false;
    }

    // https://gbdev.gg8.se/wiki/articles/Serial_Data_Transfer_(Link_Cable)#FF02_-_SC_-_Serial_Transfer_Control_.28R.2FW.29
    if (address == 0xFF02 && val & 0x81) {
        printf("%c", read_u8(mmu, 0xFF01));
        fflush(stdout);
    }

    switch (address) {
        case IO_IFLAGS:
            *ptr = (val | 0b11100000);
            break;
        case IO_LCDCONT:
            *ptr = val;

            // fix LY to 0 when LCD is off
            if((*ptr & MASK_LCDCONT_LCD_Display_Enable) == 0)
            {
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

bool read_bit(gbc_mmu *mmu, u16 address, u8 bit) {
    return ((read_u8(mmu, address) & bit) > 0);
}

void set_bit(gbc_mmu *mmu, u16 address, u8 bit) {
    u8 *ptr = get_address_ptr(mmu, address);
    *ptr |= bit;
}

void unset_bit(gbc_mmu *mmu, u16 address, u8 bit) {
    u8 *ptr = get_address_ptr(mmu, address);
    *ptr &= ~bit;
}

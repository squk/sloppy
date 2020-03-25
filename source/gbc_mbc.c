#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "types.h"
#include "gbc_mmu.h"
#include "gbc_io.h"
#include "gbc_mbc.h"
#include "gbc_cartridge.h"

void gbc_mbc_init(gbc_mbc *mbc) {
    mbc->num_rom_banks = 0;
    mbc->num_ram_banks = 0;
    mbc->rom_size = 0;
    mbc->ram_size = 0;
    mbc->rom_bank = 1;
    mbc->ram_bank = 0;
    mbc->mode_select = 0;
    mbc->type = 0;
    mbc->cart_ram = 0;
    mbc->ram_enable = 0;
    /*memset(mbc->ram, 0, sizeof mbc->ram);*/
    mbc->rom = (u8*)malloc(0x8000000*sizeof(u8));
    mbc->ram = (u8*)malloc(RAM_128K*sizeof(u8));
}

u8 gbc_mbc_read_u8(gbc_mbc *mbc, u16 address) {
    if (address < 0x4000) {
        return mbc->rom[address];
    }

    switch (mbc->type) {
        case ROM_ONLY: case ROM_RAM: case ROM_RAM_BATTERY:
            return mbc->rom[address];
        case MBC1: case MBC1_RAM: case MBC1_RAM_BATTERY:
            return mbc1_read_u8(mbc, address);
        case MBC2:
            return mbc2_read_u8(mbc, address);
        case MBC3: case MBC3_RAM:
            return mbc3_read_u8(mbc, address);
        case MBC5: case MBC5_RAM:
            return mbc5_read_u8(mbc, address);
        default:
            printf("read unsupported MBC type %d\n", mbc->type);
            break;
    }
    return 0;
}

void gbc_mbc_write_u8(gbc_mbc *mbc, u16 address, u8 val) {
    switch (mbc->type) {
        case ROM_ONLY:
            break;
        case ROM_RAM: case ROM_RAM_BATTERY:
            break;
        case MBC1: case MBC1_RAM: case MBC1_RAM_BATTERY:
            mbc1_write_u8(mbc, address, val);
            break;
        case MBC2:
            mbc2_write_u8(mbc, address, val);
            break;
        case MBC3: case MBC3_RAM:
            mbc3_write_u8(mbc, address, val);
            break;
        case MBC5: case MBC5_RAM:
            mbc5_write_u8(mbc, address, val);
            break;
        default:
            printf("wrote unsupported MBC type %d\n", mbc->type);
            break;
    }
}

// MBC1 (max 2MByte ROM and/or 32KByte RAM)
u8 mbc1_read_u8(gbc_mbc *mbc, u16 address) {
    printf("read mbc1 : %x\n", address);;
    if (address == 0x8000) { // ROM Bank 01-7F (Read Only)
        /*This area may contain any of the further 16KByte banks of the ROM,
         * allowing to *address up to 125 ROM Banks (almost 2MByte).  Bank
         * numbers 20h, 40h, and 60h cannot be used, resulting in the odd
         * amount of *125 banks. */
        printf("read mbc1 lower : %x\n", (u16)(address + CART_ROM_BANK_SIZE * (mbc->rom_bank - 1)));
        return mbc->rom[address + CART_ROM_BANK_SIZE * (mbc->rom_bank - 1)];
    }
    if (address < 0xC000) { // RAM Bank 00-03, if any (Read/Write)
        /* This area is used to address external RAM in the cartridge (if any). External
         * RAM is often battery buffered, allowing to store game positions or high
         * score tables, even if the gameboy is turned off, or if the cartridge is
         * removed from the gameboy. Available RAM sizes are: 2KByte (at A000-A7FF),
         * 8KByte (at A000-BFFF), and 32KByte (in form of four 8K banks at *A000-BFFF). */
        printf("read mbc1 upper : %x\n", (u16)(address - 0xA000 + CART_RAM_BANK_SIZE * mbc->ram_bank));
		return mbc->ram[(u16)(address - 0xA000 + CART_RAM_BANK_SIZE * mbc->ram_bank)];
    }
    return 0x00;
}

void mbc1_write_u8(gbc_mbc *mbc, u16 address, u8 val) {
    if (address < 0x2000) { // RAM Enable (Write Only)
        mbc->ram_enable = val;
    }
    else if (address < 0x4000) { // ROM Bank Number (Write Only)
        /* Writing to this address space selects the lower 5 bits of the ROM
         * Bank Number (in range 01-1Fh). When 00h is written, the MBC
         * translates that to bank 01h also. That doesn't harm so far, because
         * ROM Bank 00h can be always directly accessed by reading from
         * 0000-3FFF. But (when using the register below to specify the upper
         * ROM Bank bits), the same happens for Bank 20h, 40h, and 60h. Any
         * attempt to address these ROM Banks will select Bank 21h, 41h, and
         * 61h instead.  */

        mbc->rom_bank = (val & 0x1F) | (mbc->rom_bank & 0xE0);
		if(mbc->rom_bank == 0x00) {
			mbc->rom_bank |= 1;
			//mbc->rom_bank = 1;
		}
    }
    else if (address < 0x6000) { // RAM Bank Number - or - Upper Bits of ROM Bank Number (Write Only)
        /*This 2bit register can be used to select a RAM Bank in range from
         *00-03h, or to *specify the upper two bits (Bit 5-6) of the ROM Bank
         *number, depending on *the current ROM/RAM Mode. (See below.) */
        /*val &= 0x03;*/
		if (mbc->mode_select) {
            mbc->rom_bank = (mbc->rom_bank & 0x1F) | (val << 5);
			//mbc->rom_bank = mbc->rom_bank % mbc->num_rom_banks;
            //mbc->rom_bank = ((val & 3) << 5);
		} else {
            mbc->ram_bank = (val & 3);
		}

    }
    else if (address < 0x8000) { // ROM/RAM Mode Select (Write Only)
        // 00h = ROM Banking Mode (up to 8KByte RAM, 2MByte ROM) (default)
        // 01h = RAM Banking Mode (up to 32KByte RAM, 512KByte ROM)
        mbc->mode_select = val;
    }
    else if (address >= 0xA000 && address < 0xC000) { // RAM Bank 00-03, if any (Read/Write)
        /* This area is used to address external RAM in the cartridge (if any).
         * External RAM is often battery buffered, allowing to store game
         * positions or high score tables, even if the gameboy is turned off,
         * or if the cartridge is removed from the gameboy. Available RAM sizes
         * are: 2KByte (at A000-A7FF), 8KByte (at A000-BFFF), and 32KByte (in
         * form of four 8K banks at *A000-BFFF). */
        if (mbc->ram_enable) {
            mbc->ram[address - 0xA000 + CART_RAM_BANK_SIZE * mbc->ram_bank] = val;
        }
    }
}

// MBC2 (max 256KByte ROM and 512x4 bits RAM)
u8 mbc2_read_u8(gbc_mbc *mbc, u16 address) {
    if (address <= 0x7FFF) { // ROM Bank 01-0F (Read Only)

    }
    if (address <= 0x9FFF) { // unmapped
        return 0x00;
    }
    if (address <= 0xA1FF) { // 512x4bits RAM, built-in into the MBC2 chip (Read/Write)

    }
    return 0x00;
}

void mbc2_write_u8(gbc_mbc *mbc, u16 address, u8 val) {
}


// MBC3 (max 2MByte ROM and/or 64KByte RAM and Timer)
u8 mbc3_read_u8(gbc_mbc *mbc, u16 address) {
    if (address <= 0x7FFF) { // ROM Bank 01-7F (Read Only)

    }
    if (address <= 0xBFFF) { // RAM Bank 00-03, if any (Read/Write)

    }
    if (address <= 0xBFFF) { // RTC Register 08-0C (Read/Write)

    }
    if (address <= 0xA1FF) { // 512x4bits RAM, built-in into the MBC2 chip (Read/Write)

    }
    return 0x00;
}

void mbc3_write_u8(gbc_mbc *mbc, u16 address, u8 val) {
}

u8 mbc5_read_u8(gbc_mbc *mbc, u16 address) {
    return 0x00;
}

void mbc5_write_u8(gbc_mbc *mbc, u16 address, u8 val) {
}

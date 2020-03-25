#pragma once
#include "types.h"

/*
 * Memory Bank Controller
 * https://gbdev.gg8.se/wiki/articles/Memory_Bank_Controllers
 *
 * None (32KByte ROM only)
 * MBC1 (max 2MByte ROM and/or 32KByte RAM)
 *   0000-3FFF - ROM Bank 00 (Read Only)
 *   4000-7FFF - ROM Bank 01-7F (Read Only)
 *   A000-BFFF - RAM Bank 00-03, if any (Read/Write)
 *   0000-1FFF - RAM Enable (Write Only)
 *   2000-3FFF - ROM Bank Number (Write Only)
 *   4000-5FFF - RAM Bank Number - or - Upper Bits of ROM Bank Number (Write Only)
 *   6000-7FFF - ROM/RAM Mode Select (Write Only)
 * MBC2 (max 256KByte ROM and 512x4 bits RAM)
 *   0000-3FFF - ROM Bank 00 (Read Only)
 *   4000-7FFF - ROM Bank 01-0F (Read Only)
 *   A000-A1FF - 512x4bits RAM, built-in into the MBC2 chip (Read/Write)
 *   0000-1FFF - RAM Enable (Write Only)
 *   2000-3FFF - ROM Bank Number (Write Only)
 * MBC3 (max 2MByte ROM and/or 64KByte RAM and Timer)
 *   0000-3FFF - ROM Bank 00 (Read Only)
 *   4000-7FFF - ROM Bank 01-7F (Read Only)
 *   A000-BFFF - RAM Bank 00-03, if any (Read/Write)
 *   A000-BFFF - RTC Register 08-0C (Read/Write)
 *   0000-1FFF - RAM and Timer Enable (Write Only)
 *   2000-3FFF - ROM Bank Number (Write Only)
 *   4000-5FFF - RAM Bank Number - or - RTC Register Select (Write Only)
 *   6000-7FFF - Latch Clock Data (Write Only)
 * MBC5 (max 8MByte ROM and/or 128KByte RAM)
 *   0000-3FFF - ROM Bank 00 (Read Only)
 *   4000-7FFF - ROM Bank 00-1FF (Read Only)
 *   A000-BFFF - RAM Bank 00-0F, if any (Read/Write)
 *   0000-1FFF - RAM Enable (Write Only)
 *   2000-2FFF - Low 8 bits of ROM Bank Number (Write Only)
 *   3000-3FFF - High bit of ROM Bank Number (Write Only)
 *   4000-5FFF - RAM Bank Number (Write Only)
 */
#define CART_RAM_DISABLE 0x00
#define CART_RAM_ENABLE  0x0A

#define CART_MODE_ROM 0x00
#define CART_MODE_RAM 0x01

#define CART_MODE_ROM 0x00
#define CART_MODE_RAM 0x01

#define CART_ROM_BANK_SIZE 0x4000
#define CART_RAM_BANK_SIZE 0x2000

typedef struct {
	u8 num_rom_banks; // number of ROM banks in cartridge
	u8 num_ram_banks; // number of RAM banks in cartridge
    u8 rom_size;
    u8 ram_size;

    u8 rom_bank;
    u8 ram_bank;
    u8 mode_select;
    u8 type;

	u8 cart_ram; // whether the MBC has internal RAM
    u8 ram_enable;
    u8 *ram;
    u8 *rom;

} gbc_mbc;

void gbc_mbc_init(gbc_mbc *mbc);

u8 gbc_mbc_read_u8(gbc_mbc *mbc, u16 address);
void gbc_mbc_write_u8(gbc_mbc *mbc, u16 address, u8 val);

u8 mbc1_read_u8(gbc_mbc *mbc, u16 address);
void mbc1_write_u8(gbc_mbc *mbc, u16 address, u8 val);

u8 mbc2_read_u8(gbc_mbc *mbc, u16 address);
void mbc2_write_u8(gbc_mbc *mbc, u16 address, u8 val);

u8 mbc3_read_u8(gbc_mbc *mbc, u16 address);
void mbc3_write_u8(gbc_mbc *mbc, u16 address, u8 val);

u8 mbc5_read_u8(gbc_mbc *mbc, u16 address);
void mbc5_write_u8(gbc_mbc *mbc, u16 address, u8 val);

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

#define CART_ROM_BANK_SIZE 0x4000
#define CART_RAM_BANK_SIZE 0x2000

enum MBC_TYPE {
    ROM_ONLY                       = 0x00,
    MBC1                           = 0x01,
    MBC1_RAM                       = 0x02,
    MBC1_RAM_BATTERY               = 0x03,
    MBC2                           = 0x05,
    MBC2_BATTERY                   = 0x06,
    ROM_RAM                        = 0x08,
    ROM_RAM_BATTERY                = 0x09,
    MMM01                          = 0x0B,
    MMM01_RAM                      = 0x0C,
    MMM01_RAM_BATTERY              = 0x0D,
    MBC3_TIMER_BATTERY             = 0x0F,
    MBC3_TIMER_RAM_BATTERY         = 0x10,
    MBC3                           = 0x11,
    MBC3_RAM                       = 0x12,
    MBC3_RAM_BATTERY               = 0x13,
    MBC5                           = 0x19,
    MBC5_RAM                       = 0x1A,
    MBC5_RAM_BATTERY               = 0x1B,
    MBC5_RUMBLE                    = 0x1C,
    MBC5_RUMBLE_RAM                = 0x1D,
    MBC5_RUMBLE_RAM_BATTERY        = 0x1E,
    MBC6                           = 0x20,
    MBC7_SENSOR_RUMBLE_RAM_BATTERY = 0x22,
    POCKET_CAMERA                  = 0xFC,
    BANDAI_TAMA5                   = 0xFD,
    HuC3                           = 0xFE,
    HuC1_RAM_BATTERY               = 0xFF
};

enum RAM_SIZE {
    RAM_32K = 0x00,
    RAM_64K = 0x01,
    RAM_128K = 0x02,
    RAM_256K = 0x03,
    RAM_512K = 0x04,
    RAM_1M = 0x05,
    RAM_2M = 0x06,
    RAM_4M = 0x07,
    RAM_8M = 0x08,

    RAM_1_1M = 0x52,
    RAM_1_2M = 0x53,
    RAM_1_5M = 0x54
};

#define BYTES_8K   8192
#define BYTES_32K  32768
#define BYTES_64K  65536
#define BYTES_128K 131072
#define BYTES_256K 262144
#define BYTES_512K 524288
#define BYTES_1M   1048576
#define BYTES_2M   2097152
#define BYTES_4M   4194304
#define BYTES_8M   8388608

typedef struct {
    u8 title[0x10];
} gbc_cartridge;

typedef struct {
    u8 num_rom_banks;     // number of ROM banks in cartridge
    u8 num_ram_banks;     // number of RAM banks in cartridge
    u8 rom_size;
    u8 ram_size;

    u8 RAMG, BANK1, BANK2, MODE;
    u8 type;

    u8 *ram;
    u8 *rom;
    long rom_numbytes;
    long ram_numbytes;

    gbc_cartridge cart;

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

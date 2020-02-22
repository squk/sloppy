#include <gba_base.h>

void mmu_init(gbc_mmu *mmu){
	mmu->in_bios = true;
}

u8* get_address_ptr(gbc_mmu *mmu , u16 address) {
    // BIOS (256b)/ROM0
    case 0x0000:
        if(mmu->in_bios)
        {
            if(address < 0x0100)
                &return mmu->bios[address];
            else if(Z80._r.pc == 0x0100)
                mmu->in_bios = false;
        }

        return &mmu->rom[address];

        // ROM0
    case 0x1000:
    case 0x2000:
    case 0x3000:
        return &mmu->rom[address];

        // ROM1 (unbanked) (16k)
    case 0x4000:
    case 0x5000:
    case 0x6000:
    case 0x7000:
        return &mmu->rom[address];

        // VRAM (8k)
    case 0x8000:
    case 0x9000:
        return &mmu->vram[address & 0x1FFF];

        // External RAM (8k)
    case 0xA000:
    case 0xB000:
        return &mmu->eram[address & 0x1FFF];

        // Working RAM (8k)
    case 0xC000:
    case 0xD000:
        return &mmu->wram[address & 0x1FFF];

        // Working RAM shadow
    case 0xE000:
        return &mmu->wram[address & 0x1FFF];

        // Working RAM shadow, I/O, Zero-page RAM
    case 0xF000:
        switch(address & 0x0F00){
            // Working RAM shadow
            case 0x000: case 0x100: case 0x200: case 0x300: case 0x400:
            case 0x500: case 0x600: case 0x700: case 0x800: case 0x900:
            case 0xA00: case 0xB00: case 0xC00: case 0xD00:
                return &mmu->wram[address & 0x1FFF];

                // Graphics: object attribute memory
                // OAM is 160 bytes, remaining bytes read as 0
            case 0xE00:
                if(address < 0xFEA0) {
                    return &GPU->oam[address & 0xFF];
                }
                return 0;

                // Zero-page
            case 0xF00:
                if(address >= 0xFF80) {
                    return &mmu->zram[address & 0x7F];
                }

                // I/O control handling
                // Currently unhandled
                return 0;
        }
	default:
		return 0;
}

u16 read_u16(gbc_mmu *mmu , u16 address) {
    u8 *ptr = get_address_ptr(mmu, address);
    u16 val;
    memcpy(&val, *ptr, sizeof(u16));

    return val;
}

u16 write_u16(gbc_mmu *mmu , u16 address, u16 val) {
    u8 *ptr = get_address_ptr(mmu, address);
    memcpy(ptr, val, sizeof(u16));

    return val;
}

u8 read_u8(gbc_mmu *mmu , u16 address) {
    u8 *ptr = get_address_ptr(mmu, address);
    return *ptr;
}

void write_u8(gbc_mmu *mmu , u16 address, u8 val) {
    u8 *ptr = get_address_ptr(mmu, address);
    *ptr = val;
}

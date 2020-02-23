#ifndef FONT_H
#define FONT_H

const u16 PALETTE_0[] = {
    RGB8(0x40,0x80,0xc0),
    RGB8(0xFF,0xFF,0xFF),
    RGB8(0xF5,0xFF,0xFF),
    RGB8(0xDF,0xFF,0xF2),
    RGB8(0xCA,0xFF,0xE2),
    RGB8(0xB7,0xFD,0xD8),
    RGB8(0x2C,0x4F,0x8B)
};

const u16 PALETTE_1[] = {
    RGB8(0x40,0x80,0xc0),
    RGB8(0xFF,0xFF,0xFF),
    RGB8(0xF5,0xFF,0xFF),
    RGB8(0xDF,0xFF,0xF2),
    RGB8(0xCA,0xFF,0xE2),
    RGB8(0xB7,0xFD,0xD8),
    RGB8(0x2C,0x4F,0x8B)
};

void set_pallete(const u16 palette[]);
void load_font();

#endif

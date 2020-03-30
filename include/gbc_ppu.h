#pragma once
#include "gbc_mmu.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>

// to display a sprite in the upper left corner of the screen set sprite X=8, Y=16.
#define SPRITE_INI_X 8
#define SPRITE_INI_Y 16
#define NUM_SPRITES         0x28

// pixels
#define SIZE_X 160
#define SIZE_Y 144

// sprite border
#define SPRITE_END_X SPRITE_INI_X + SIZE_X
#define SPRITE_END_Y SPRITE_INI_Y + SIZE_Y
#define LCD_VERT_LINES 154

/* Bit mask for the shade of pixel to display */
#define LCD_COLOUR      0x03
/**
 * Bit mask for whether a pixel is OBJ0, OBJ1, or BG. Each may have a different
 * palette when playing a DMG game on CGB.
 */
#define LCD_PALETTE_OBJ 0x10
#define LCD_PALETTE_BG  0x20
/**
 * Bit mask for the two bits listed above.
 * LCD_PALETTE_ALL == 0b00 --> OBJ0
 * LCD_PALETTE_ALL == 0b01 --> OBJ1
 * LCD_PALETTE_ALL == 0b10 --> BG
 * LCD_PALETTE_ALL == 0b11 --> NOT POSSIBLE
 */
#define LCD_PALETTE_ALL 0x30

// duration of each screen state
#define LCD_MODE_0_CYCLES   0
#define LCD_MODE_2_CYCLES   204
#define LCD_MODE_3_CYCLES   284
#define LCD_LINE_CYCLES     456

#define DUR_FRAME 70224
#define END_OAM 80
#define END_OAM_VRAM 252
#define DUR_LINE 456 // 80 + 172 + 204
#define DUR_VBLANK 4560

// start of each screen state in each line / frame
#define TL_OAM 0
#define TL_OAM_VRAM TL_OAM + DUR_OAM
#define TL_HBLANK TL_OAM_VRAM + DUR_OAM_VRAM
#define TF_VBLANK DUR_LINE * SIZE_Y

#define FPS 59.73

#define MASK_OBJ_PRIORITY (0x01 << 7)
#define MASK_OBJ_Y_FLIP   (0x01 << 6)
#define MASK_OBJ_X_FLIP   (0x01 << 5)
#define MASK_OBJ_PALETTE  (0x01 << 4)

#define TRANSPARENT 8

#define RGB5(r,g,b)     ((r)|((g)<<5)|((b)<<10))
#define RGB8(r,g,b)     ( (((b)>>3)<<10) | (((g)>>3)<<5) | ((r)>>3) )

typedef struct {
    u8 id;
    u8 x;
    u8 y;

    /*
     * Specifies the sprites Tile Number (00-FF). This (unsigned) value selects
     a tile *from memory at 8000h-8FFFh. In CGB Mode this could be either in
     VRAM Bank 0 *or 1, depending on Bit 3 of the following byte. In 8x16 mode,
     the lower bit *of the tile number is ignored. IE: the upper 8x8 tile is
     "NN AND FEh", and *the lower 8x8 tile is "NN OR 01h".
     */
    u8 pat;

    /*
     * Bit7   OBJ-to-BG Priority (0=OBJ Above BG, 1=OBJ Behind BG color 1-3)
     *       (Used for both BG and Window. BG color 0 is always behind OBJ)
     * Bit6   Y flip          (0=Normal, 1=Vertically mirrored)
     * Bit5   X flip          (0=Normal, 1=Horizontally mirrored)
     * Bit4   Palette number  **Non CGB Mode Only** (0=OBP0, 1=OBP1)
     * Bit3   Tile VRAM-Bank  **CGB Mode Only**     (0=Bank 0, 1=Bank 1)
     * Bit2-0 Palette number  **CGB Mode Only**     (OBP0-7)
     */
    u8 flags;
} ppu_obj;

typedef struct {
    gbc_mmu *mmu;
    SDL_Renderer *renderer;
    SDL_Window *window;

    u8 fb[SIZE_X * SIZE_Y];
    u8 bg_disp[512*512];
    u8 win_disp[512*512];
    u8 obj_disp[512*512];

    u16 mode_clock; // Object Attribute Memory

    bool quit;
} gbc_ppu;

/*
 * FF47 - BGP - BG Palette Data (R/W) - Non CGB Mode Only
 * FF48 - OBP0 - Object Palette 0 Data (R/W) - Non CGB Mode Only
 * FF49 - OBP1 - Object Palette 1 Data (R/W) - Non CGB Mode Only
 */

/*
 * Bit 7-6 - Shade for Color Number 3
 * Bit 5-4 - Shade for Color Number 2
 * Bit 3-2 - Shade for Color Number 1
 * Bit 1-0 - Shade for Color Number 0
 *
 * The four possible gray shades are:
 *  0  White
 *  1  Light gray
 *  2  Dark gray
 *  3  Black
 */
void set_palette(u8* p, u8 v);

void ppu_write_u8(gbc_ppu *ppu, u16 address, u8 v);

void ppu_init(gbc_ppu *ppu);
u8 ppu_get_palette_color(gbc_ppu *ppu, u16 palette_addr, u8 color);
void ppu_start_frame(gbc_ppu *ppu);
void ppu_draw_line_fb(gbc_ppu *ppu, u8 line);
void ppu_draw_line_bg(gbc_ppu *ppu, u8 line);
void ppu_draw_line_obj(gbc_ppu *ppu, u8 line);
void ppu_draw_line(gbc_ppu *ppu, u8 line);
u8 ppu_run(gbc_ppu *ppu, int cycles);

unsigned long gbcToRgb32(unsigned const bgr15);
u16 rgb32ToRgb16(u32 rgb32);
u16 color_dmg_to_gba(unsigned const bgr15);

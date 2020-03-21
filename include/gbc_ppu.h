#pragma once
#include "gbc_mmu.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>

// to display a sprite in the upper left corner of the screen set sprite X=8, Y=16.
#define SPRITE_INI_X 8
#define SPRITE_INI_Y 16

// pixels
#define SIZE_X 160
#define SIZE_Y 144

// sprite border
#define SPRITE_END_X SPRITE_INI_X + SIZE_X
#define SPRITE_END_Y SPRITE_INI_Y + SIZE_Y

#define LCD_VERT_LINES 154

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

#define RGB5(r,g,b)	((r)|((g)<<5)|((b)<<10))
#define RGB8(r,g,b)	( (((b)>>3)<<10) | (((g)>>3)<<5) | ((r)>>3) )

typedef struct {
    uint8_t id;
    uint8_t x;
    uint8_t y;
    uint8_t pat;
    uint8_t flags;
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
    u8 bg_palette[4], obj0_palette[4], obj1_palette[4];

    bool quit;
} gbc_ppu;

void set_palette(u8* p, u8 v);

void ppu_write_u8(gbc_ppu *ppu, u16 address, u8 v);

void ppu_init(gbc_ppu *ppu);
void ppu_start_frame(gbc_ppu *ppu);
void ppu_draw_line_fb(gbc_ppu *ppu, u8 line);
void ppu_draw_line_bg(gbc_ppu *ppu, u8 line);
void ppu_draw_line_obj(gbc_ppu *ppu, u8 line);
void ppu_draw_line(gbc_ppu *ppu, u8 line);
u8 ppu_run(gbc_ppu *ppu, int cycles);

unsigned long gbcToRgb32(unsigned const bgr15);
u16 rgb32ToRgb16(u32 rgb32);
u16 color_dmg_to_gba(unsigned const bgr15);

#pragma once
#include "gbc_mmu.h"

// to display a sprite in the upper left corner of the screen set sprite X=8, Y=16.
#define SPRITE_INI_X 8
#define SPRITE_INI_Y 16

// pixels
#define SIZE_X 160
#define SIZE_Y 144

// sprite border
#define SPRITE_END_X SPRITE_INI_X + SIZE_X
#define SPRITE_END_Y SPRITE_INI_Y + SIZE_Y

#define LINES 154

// duration of each screen state
#define DUR_FRAME 70224
#define DUR_OAM 80
#define DUR_OAM_VRAM 172
#define DUR_HBLANK 204
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

typedef struct {
	uint8_t id;
	uint8_t x;
	uint8_t y;
	uint8_t pat;
	uint8_t flags;
} gpu_obj;

typedef struct {
    gbc_mmu *mmu;
    u8 fb[SIZE_X * SIZE_Y];
    u8 bg_disp[512*512];
    u8 win_disp[512*512];
    u8 obj_disp[512*512];

    int oam, oam_vram; // Object Attribute Memory
    int hblank, vblank;
    u8 cur_line, cmp_line;
    u8 reset;
    u8 bg_palette[4], obj0_palette[4], obj1_palette[4];

    // registers
    u8 BGP, OBP0, OBP1;
    u8 lcd_stat;
    u8 scroll_x, scroll_y, wndpos_x, wndpos_y;
} gbc_gpu;

void set_palette(u8* p, u8 v);

void gpu_write_u8(gbc_gpu *gpu, u16 address, u8 v);
u8 gpu_read_u8(gbc_gpu *gpu, u16 address);

void gpu_start_frame(gbc_gpu *gpu);
void gpu_draw_line_fb(gbc_gpu *gpu, u8 line);
void gpu_draw_line_bg(gbc_gpu *gpu, u8 line);
void gpu_draw_line_obj(gbc_gpu *gpu, u8 line);
void gpu_draw_line(gbc_gpu *gpu, u8 line);
u8 gpu_run(gbc_gpu *gpu, int cycles);

/**
FF41 - STAT - LCDC Status (R/W)
  Bit 6 - LYC=LY Coincidence Interrupt (1=Enable) (Read/Write)
  Bit 5 - Mode 2 OAM Interrupt         (1=Enable) (Read/Write)
  Bit 4 - Mode 1 V-Blank Interrupt     (1=Enable) (Read/Write)
  Bit 3 - Mode 0 H-Blank Interrupt     (1=Enable) (Read/Write)
  Bit 2 - Coincidence Flag  (0:LYC<>LY, 1:LYC=LY) (Read Only)
  Bit 1-0 - Mode Flag       (Mode 0-3, see below) (Read Only)
			0: During H-Blank
			1: During V-Blank
			2: During Searching OAM-RAM
			3: During Transfering Data to LCD Driver
The two lower STAT bits show the current status of the LCD controller.
  Mode 0: The LCD controller is in the H-Blank period and
		  the CPU can access both the display RAM (8000h-9FFFh)
		  and OAM (FE00h-FE9Fh)
  Mode 1: The LCD contoller is in the V-Blank period (or the
		  display is disabled) and the CPU can access both the
		  display RAM (8000h-9FFFh) and OAM (FE00h-FE9Fh)
  Mode 2: The LCD controller is reading from OAM memory.
		  The CPU <cannot> access OAM memory (FE00h-FE9Fh)
		  during this period.
  Mode 3: The LCD controller is reading from both OAM and VRAM,
		  The CPU <cannot> access OAM and VRAM during this period.
		  CGB Mode: Cannot access Palette Data (FF69,FF6B) either.
The following are typical when the display is enabled:
  Mode 2  2_____2_____2_____2_____2_____2___________________2____
  Mode 3  _33____33____33____33____33____33__________________3___
  Mode 0  ___000___000___000___000___000___000________________000
  Mode 1  ____________________________________11111111111111_____
The Mode Flag goes through the values 0, 2, and 3 at a cycle of about 109uS. 0 is present about 48.6uS, 2 about 19uS, and 3 about 41uS. This is interrupted every 16.6ms by the VBlank (1). The mode flag stays set at 1 for about 1.08 ms.
Mode 0 is present between 201-207 clks, 2 about 77-83 clks, and 3 about 169-175 clks. A complete cycle through these states takes 456 clks. VBlank lasts 4560 clks. A complete screen refresh occurs every 70224 clks.)
*/

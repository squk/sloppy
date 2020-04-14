/*#include <gba_base.h>*/
/*#include <gba_systemcalls.h>*/
/*#include <gba_video.h>*/

#include <signal.h>
#include <string>
#include <stdio.h>

#include "types.h"
#include "gbc_ppu.hpp"
#include "gbc_io.h"
#include "gbc_mmu.hpp"

void gbc_ppu::init() {
    quit = false;
    vblank = true;
    mode_clock = 0;
    memset(fb, 0, sizeof fb);
    memset(bg_disp, 0, sizeof bg_disp);
    memset(win_disp, 0, sizeof win_disp);
    memset(obj_disp, 0, sizeof obj_disp);

    start_frame();
}

void insertion_sort(void *array, int length,
                    int compare(void*, int, int), void swap(void *, int, int)) {
    int i, j; // loop indexes

    for (j = 1; j < length; j++) {// index to insert array
        for (i = j-1; 0 <= i; i--) {
            // compare to previous index and swap if needed
            // else if previous index is smaller, this is my place
            if (!compare(array, i, i+1)) {
                swap(array, i, i+1);
            } else {
                i = 0;
            }
        }
    }
}

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
u8 gbc_ppu::get_palette_color(u16 palette_addr, u8 color) {
    u8 p = 0;
    switch (palette_addr) {
        case IO_BGRDPAL:
        case IO_OBJ0PAL:
        case IO_OBJ1PAL:
            p = mmu->read_u8(palette_addr);
            break;
        default:
            printf("invalid PPU palette address: %x\n", palette_addr);
            return 0;
    }

    u8 bits = 0;
    switch (color) {
        case 0:
            bits = p & 0x03;
            if (palette_addr == IO_OBJ0PAL || palette_addr == IO_OBJ1PAL) {
                return 0;
            }
            break;
        case 1:
            bits = (p & 0x0C) >> 2;
            break;
        case 2:
            bits = (p & 0x30) >> 4;
            break;
        case 3:
            bits = (p & 0xC0) >> 6;
            break;
        default:
            printf("invalid color %x\n", color);
            return 0;
    }

    return bits;
}

void gbc_ppu::start_frame() {
    int i, j;

    // set win and obj to transparent
    for (i = 0; i < 256; i++) {
        for (j = 0; j < 256; j++) {
            bg_disp[i * 256 + 1] = 0;
            win_disp[i * 256 + j] = TRANSPARENT;
            obj_disp[i * 256 + j] = TRANSPARENT;
        }
    }
    u8 r = run(0);
}

void gbc_ppu::dump() {
    printf("BG: \n");
    int i, j;
    for (j = 0; j < 128; j++) {
        for (i = 0; i < 256; i++) {
            printf("%d", bg_disp[j * 256 + i]);
        }
        printf("\n");
    }
    printf("\n");

    printf("WIN: \n");
    for (j = 0; j < 128; j++) {
        for (i = 0; i < 256; i++) {
            printf("%d", win_disp[j * 256 + i]);
        }
        printf("\n");
    }
    printf("\n");

    printf("OBJ: \n");
    for (j = 0; j < 128; j++) {
        for (i = 0; i < 256; i++) {
            printf("%d", obj_disp[j * 256 + i]);
        }
        printf("\n");
    }
    printf("\n");
}

// TODO: cleanup and optimize
void gbc_ppu::draw_line_fb(u8 line) {
    for (int i = 0; i < SIZE_X; i++) {
        int px_index = line * SIZE_X + i;
        fb[px_index] = bg_disp[line * 256 + i];
        // check non painted
        if (win_disp[line * 256 + i] < 8) {
            fb[px_index] = win_disp[line * 256 + i];
        }

        int obj_index = (line + SPRITE_INI_Y) * 256 + i + SPRITE_INI_X;

        //OBJ-to-BG Priority (0=OBJ Above BG, 1=OBJ Behind BG color 1-3)
        //(Used for both BG and Window. BG color 0 is always behind OBJ)
        if ((fb[px_index] != 0 && obj_disp[obj_index] >= 4)) {
            continue;
        }
        if (obj_disp[obj_index] == 0) {
            continue;
        }
        fb[px_index] = obj_disp[obj_index] & 0x03;
    }
}

void gbc_ppu::draw_line_bg(u8 line) {
    u16 bg_tile_map, tile_data;
    u8 oam_row, py;
    u8 py_a, py_b;
    s16 obj;

    if (mmu->read_bit(IO_LCDCONT, MASK_LCDCONT_BG_Tile_Map_Display_Select)) {
        bg_tile_map = 0x9C00;
    } else {
        bg_tile_map = 0x9800;
    }

    if (mmu->read_bit(IO_LCDCONT, MASK_LCDCONT_BGWindow_Tile_Data_Select)) {
        tile_data = 0x8000;
    } else {
        tile_data = 0x9000;
    }

    // optimization for GBA. it's ARM CPU struggled with div and mod operators
    /*oam_row = (u8)Div(line + mmu->read_u8(IO_SCROLLY), 8);*/
    /*py = (u8)DivMod(line + mmu->read_u8(IO_SCROLLY), 8);*/
    oam_row = (u8)((line + mmu->read_u8(IO_SCROLLY)) / 8);
    py = (u8)((line + mmu->read_u8(IO_SCROLLY)) % 8);

    u8 i, j;
    for (i = 0; i < 32; i++) {
        if (tile_data == 0x9000) {
            obj = (s8)mmu->read_u8(bg_tile_map + oam_row * 32 + i);
        } else {
            obj = (u8)mmu->read_u8(bg_tile_map + oam_row * 32 + i);
        }
        py_a = mmu->read_u8(tile_data + obj * 16 + py * 2);
        py_b = mmu->read_u8(tile_data + obj * 16 + py * 2 + 1);
        for (j = 0; j < 8; j++) {
            bg_disp[line * 256 + (u8)(i * 8 - mmu->read_u8(IO_SCROLLX) + j)] =
                get_palette_color(IO_BGRDPAL,
                                      ((py_a & (1 << (7 - j))) ? 1 : 0) +
                                      ((py_b & (1 << (7 - j))) ? 2 : 0)
                                      );
        }
    }
}

void gbc_ppu::draw_line_win(u8 line) {
    u16 win_tile_map, tile_data;
    u8 oam_row, py;
    u8 py_a, py_b;
    s16 obj;

    if (mmu->read_u8(IO_WNDPOSY)  > line || mmu->read_u8(IO_WNDPOSX) > SIZE_X) {
        return;
    }

    if (mmu->read_bit(IO_LCDCONT, MASK_LCDCONT_Window_Tile_Map_Display_Select)) {
        win_tile_map = 0x9C00;
    } else {
        win_tile_map = 0x9800;
    }

    if (mmu->read_bit(IO_LCDCONT, MASK_LCDCONT_BGWindow_Tile_Data_Select)) {
        tile_data = 0x8000;
    } else {
        tile_data = 0x9000;
    }

    // optimization for GBA. it's ARM CPU struggled with div and mod operators
    /*oam_row = Div((u8)(line - mmu->read_u8(IO_WNDPOSY)), 8);*/
    /*py = DivMod((u8)(line - mmu->read_u8(IO_WNDPOSY)), 8);*/
    oam_row = (u8)((line - mmu->read_u8(IO_WNDPOSY)) / 8);
    py = (u8)((line - mmu->read_u8(IO_WNDPOSY)) % 8);
    u8 i, j;
    for (i = 0; i < (SIZE_X - (mmu->read_u8(IO_WNDPOSX) - 8)) / 8 + 1; i++) {
        if (tile_data == 0x9000) {
            obj = (s8)mmu->read_u8(win_tile_map + oam_row * 32 + i);
        } else {
            obj = (u8)mmu->read_u8(win_tile_map + oam_row * 32 + i);
        }
        py_a = mmu->read_u8(tile_data + obj * 16 + py * 2);
        py_b = mmu->read_u8(tile_data + obj * 16 + py * 2 + 1);
        for (j = 0; j < 8; j++) {
            win_disp[line * 256 + (u8)(i * 8 + mmu->read_u8(IO_WNDPOSX) - 7 + j)] =
                get_palette_color(IO_BGRDPAL,
                                      ((py_a & (1 << (7 - j))) ? 1 : 0) +
                                      ((py_b & (1 << (7 - j))) ? 2 : 0)
                                      );
        }
    }
}

int obj_comp(void *array, int i, int j) {
    ppu_obj a = ((ppu_obj*)array)[i];
    ppu_obj b = ((ppu_obj*)array)[j];

    if (a.x < b.x) {
        return 0;
    }
    if (a.x > b.x) {
        return 1;
    }

    if (a.id < b.id) {
        return 0;
    }
    if (a.id > b.id) {
        return 1;
    }
    // this should never be reached
    return 0;
}

void obj_swap(void *array, int i, int j) {
    ppu_obj a = ((ppu_obj*)array)[i];
    ppu_obj b = ((ppu_obj*)array)[j];

    ((ppu_obj*)array)[i] = b;
    ((ppu_obj*)array)[j] = a;
}

// 8x8 or 8x16
// Object Pattern Table = 8000 - 8FFF
// Object Atribute Table = FE00 - FE9F
// 10 sprites per scan line
// higher X -> draw first (lower X -> draw above others)
// same X -> FE00 highest, FE04 next highest
// Y = 0 or Y => 144+16, discard sprite
//
// During each scanline's OAM scan, the LCD controller compares LY to each
// sprite's Y position to find the 10 sprites on that line that appear first in
// OAM ($FE00-$FE03 being the first). It discards the rest, allowing only 10
// sprites to be displayed on any one line. When this limit is exceeded,
// sprites appearing later in OAM won't be displayed. To keep unused sprites
// from affecting onscreen sprites, set their Y coordinate to Y = 0 or Y >= 160
// (144 + 16) (Note : Y <= 8 also works if sprite size is set to 8x8). Just
// setting the X coordinate to X = 0 or X >= 168 (160 + 8) on a sprite will
// hide it, but it will still affect other sprites sharing the same lines.
//
// When these 10 sprites overlap, the highest priority one will appear above
// all others, etc. (Thus, no Z-fighting.) In CGB mode, the first sprite in OAM
// ($FE00-$FE03) has the highest priority, and so on. In Non-CGB mode, the
// smaller the X coordinate, the higher the priority. The tie breaker (same X
// coordinates) is the same priority as in CGB mode.
//
// The priority calculation between sprites disregards OBJ-to-BG Priority
// (attribute bit 7). Only the highest-priority nonzero sprite pixel at any
// given point is compared against the background. Thus if a sprite with a
// higher priority (based on OAM index) but with OBJ-to-BG Priority turned on
// overlaps a sprite with a lower priority and a nonzero background pixel, the
// background pixel is displayed regardless of the lower-priority sprite's
// OBJ-to-BG Priority.
void gbc_ppu::draw_line_obj(u8 line) {
    u8 obj_height, py;
    line += SPRITE_INI_Y;

    switch (mmu->read_bit(IO_LCDCONT, MASK_LCDCONT_OBJ_Size)) {
        case OPT_OBJ_Size_8x8:
            obj_height = 8;
            break;
        case OPT_OBJ_Size_8x16:
            obj_height = 16;
            break;
    }

    u8 i, j;
    u16 addr, pos;
    // read sprites in reverse order so we don't have to sort
    for (i = NUM_SPRITES-1; i != 0xFF; i--) {
        addr = MEM_OAM + i * 4;

        ppu_obj obj;
        obj.id = i;
        obj.y = mmu->read_u8(addr++);
        obj.x = mmu->read_u8(addr++);
        obj.pat = mmu->read_u8(addr++);
        obj.flags = mmu->read_u8(addr);

        // Take the candidate objects to be drawn in the line
        if(!((obj.y != 0)
             && (obj.y < SPRITE_END_Y)
             && (obj.y <= line)
             && ((obj.y + obj_height) > line))) { // does the sprite intercept the scanline?
            continue;
        }

        u8 x_flip = (obj.flags & OPT_OBJ_Flag_xflip) ? 1 : 0;
        u8 y_flip = (obj.flags & OPT_OBJ_Flag_yflip) ? 1 : 0;
        py = (line - obj.y) % obj_height;
        if (y_flip) {
            py = obj_height - 1 - py;
        }

        // fetch the tile
        u8 t1 = mmu->read_u8(0x8000 + obj.pat * 16 + py * 2);
        u8 t2 = mmu->read_u8(0x8000 + obj.pat * 16 + py * 2 + 1);

        for (j = 0; j < 8; j++) {
            pos = line * 256 + (obj.x + (x_flip ? 7 - j : j)) % 256;

            u8 color;
            u8 color_index = ((t1 & (1 << (7 - j))) ? 1 : 0) +
                             ((t2 & (1 << (7 - j))) ? 2 : 0);

            if (obj.flags & OPT_OBJ_Flag_palette) {
                color = get_palette_color(IO_OBJ1PAL, color_index);
            } else {
                color = get_palette_color(IO_OBJ0PAL, color_index);
            }

            obj_disp[pos] = color;

            //OBJ-to-BG Priority (0=OBJ Above BG, 1=OBJ Behind BG color 1-3)
            //(Used for both BG and Window. BG color 0 is always behind OBJ)
            if (!(obj.flags & OPT_OBJ_Flag_priority)) {
                obj_disp[pos] |= 4;
            }
        }
    }
}

void gbc_ppu::draw_line(u8 line) {
    if (mmu->read_bit(IO_LCDCONT, MASK_LCDCONT_LCD_Display_Enable)) {
        if (mmu->read_bit(IO_LCDCONT, MASK_LCDCONT_BG_Display_Enable)) {
            draw_line_bg(line);
        }
        if (mmu->read_bit(IO_LCDCONT, MASK_LCDCONT_Window_Display_Enable)) {
            draw_line_win(line);
        }
        if (mmu->read_bit(IO_LCDCONT, MASK_LCDCONT_OBJ_Display_Enable)) {
            draw_line_obj(line);
        }
    }

    draw_line_fb(line);
}

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
u8 gbc_ppu::run(int cycles) {
    mode_clock += cycles;

    if (mode_clock >= LCD_LINE_CYCLES) {
        mode_clock -= LCD_LINE_CYCLES;

        // next line
        mmu->write_u8(IO_CURLINE, (mmu->read_u8(IO_CURLINE) + 1) % LCD_VERT_LINES);

        // LYC Update
        if (mmu->read_u8(IO_CURLINE) == mmu->read_u8(IO_CMPLINE)) {
            mmu->set_bit(IO_LCDSTAT, MASK_LCDSTAT_COINCIDENCE_FLAG);
            if (mmu->read_bit(IO_LCDSTAT, MASK_LCDSTAT_LYC_LY_COINCIDENCE_INTERRUPT)) {
                mmu->set_bit(IO_IFLAGS, MASK_INT_LCDSTAT_INT);
            }
        } else {
            mmu->unset_bit(IO_LCDSTAT, MASK_LCDSTAT_COINCIDENCE_FLAG);
        }

        // VBLANK
        if (mmu->read_u8(IO_CURLINE) == SIZE_Y) {
            // Set Mode Flag to VBLANK at LCDSTAT
            mmu->unset_bit(IO_LCDSTAT, MASK_LCDSTAT_MODE_FLAG);
            mmu->set_bit(IO_LCDSTAT, OPT_MODE_VBLANK);

            // Interrupt VBlank
            mmu->set_bit(IO_IFLAGS, MASK_INT_VBLANK);
            if (mmu->read_bit(IO_LCDSTAT, MASK_LCDSTAT_MODE_1_VBLANK_INTERRUPT)) {
                mmu->set_bit(IO_IFLAGS, MASK_INT_LCDSTAT_INT);
            }

            if (mmu->read_bit(IO_LCDSTAT, MASK_LCDSTAT_MODE_2_OAM_INTERRUPT)) {
                mmu->set_bit(IO_IFLAGS, MASK_INT_LCDSTAT_INT);
            }
            /*ppu_dump();*/
            vblank = true;
        }
        // Normal line
        else if (mmu->read_u8(IO_CURLINE) < SIZE_Y) {
            mmu->unset_bit(IO_LCDSTAT, MASK_LCDSTAT_MODE_FLAG);
            mmu->set_bit(IO_LCDSTAT, OPT_MODE_OAM);

            if (mmu->read_bit(IO_LCDSTAT, MASK_LCDSTAT_MODE_2_OAM_INTERRUPT)) {
                mmu->set_bit(IO_IFLAGS, MASK_INT_LCDSTAT_INT);
            }
        }
    } else if (((mmu->read_u8(IO_LCDSTAT) & MASK_LCDSTAT_MODE_FLAG) == OPT_MODE_OAM) && mode_clock >= END_OAM) {
        mmu->unset_bit(IO_LCDSTAT, MASK_LCDSTAT_MODE_FLAG);
        mmu->set_bit(IO_LCDSTAT, OPT_MODE_OAM_VRAM);
    } else if (((mmu->read_u8(IO_LCDSTAT) & MASK_LCDSTAT_MODE_FLAG) == OPT_MODE_OAM_VRAM) && mode_clock >= END_OAM_VRAM) {
        mmu->unset_bit(IO_LCDSTAT, MASK_LCDSTAT_MODE_FLAG);
        mmu->set_bit(IO_LCDSTAT, OPT_MODE_HBLANK);
        draw_line(mmu->read_u8(IO_CURLINE));

        if (mmu->read_bit(IO_LCDSTAT, MASK_LCDSTAT_MODE_0_HBLANK_INTERRUPT)) {
            mmu->set_bit(IO_IFLAGS, MASK_INT_LCDSTAT_INT);
        }
    }
    return 0;
}

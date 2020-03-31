/*#include <gba_base.h>*/
/*#include <gba_systemcalls.h>*/
/*#include <gba_video.h>*/

#include <signal.h>
#include <string.h>
#include <stdio.h>

#include "types.h"
#include "gbc_ppu.h"
#include "gbc_io.h"
#include "gbc_mmu.h"


void ppu_init(gbc_ppu *ppu) {
    ppu->quit = false;
    ppu->mode_clock = 0;
    memset(ppu->fb, 0, sizeof ppu->fb);
    memset(ppu->bg_disp, 0, sizeof ppu->bg_disp);
    memset(ppu->win_disp, 0, sizeof ppu->win_disp);
    memset(ppu->obj_disp, 0, sizeof ppu->obj_disp);

    ppu_start_frame(ppu);
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
u8 ppu_get_palette_color(gbc_ppu *ppu, u16 palette_addr, u8 color) {
    u8 p = 0;
    switch (palette_addr) {
        case IO_BGRDPAL:
        case IO_OBJ0PAL:
        case IO_OBJ1PAL:
            p = read_u8(ppu->mmu, palette_addr);
            break;
        default:
            printf("invalid PPU palette address: %x\n", palette_addr);
            return 0;
    }

    u8 bits = 0;
    switch (color) {
        case 0:
            bits = p & 0x03;
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

void ppu_start_frame(gbc_ppu *ppu) {
    int i, j;

    // set win and obj to transparent
    for (i = 0; i < 256; i++) {
        for (j = 0; j < 256; j++) {
            ppu->bg_disp[i * 256 + 1] = 0;
            ppu->win_disp[i * 256 + j] = TRANSPARENT;
            ppu->obj_disp[i * 256 + j] = TRANSPARENT;
        }
    }
    u8 r = ppu_run(ppu, 0);
}

void ppu_dump(gbc_ppu *ppu) {
    printf("BG: \n");
    int i, j;
    for (j = 0; j < 128; j++) {
        for (i = 0; i < 256; i++) {
            printf("%d", ppu->bg_disp[j * 256 + i]);
        }
        printf("\n");
    }
    printf("\n");

    printf("WIN: \n");
    for (j = 0; j < 128; j++) {
        for (i = 0; i < 256; i++) {
            printf("%d", ppu->win_disp[j * 256 + i]);
        }
        printf("\n");
    }
    printf("\n");

    printf("OBJ: \n");
    for (j = 0; j < 128; j++) {
        for (i = 0; i < 256; i++) {
            printf("%d", ppu->obj_disp[j * 256 + i]);
        }
        printf("\n");
    }
    printf("\n");
}

// TODO: cleanup and optimize
void ppu_draw_line_fb(gbc_ppu *ppu, u8 line) {
    for (int i = 0; i < SIZE_X; i++) {
        int px_index = line * SIZE_X + i;
        ppu->fb[px_index] = ppu->bg_disp[line * 256 + i];
        // check non painted
        if (ppu->win_disp[line * 256 + i] < 8) {
            ppu->fb[px_index] = ppu->win_disp[line * 256 + i];
        }

        int obj_index = (line + SPRITE_INI_Y) * 256 + i + SPRITE_INI_X;

        if (ppu->fb[px_index] != 0 && ppu->obj_disp[obj_index] >= 4) {
            continue;
        }
        ppu->fb[px_index] = ppu->obj_disp[obj_index] & 0x03;
    }
}

void ppu_draw_line_bg(gbc_ppu *ppu, u8 line) {
    u16 bg_tile_map, tile_data;
    u8 oam_row, py;
    u8 py_a, py_b;
    s16 obj;

    if (read_bit(ppu->mmu, IO_LCDCONT, MASK_LCDCONT_BG_Tile_Map_Display_Select)) {
        bg_tile_map = 0x9C00;
    } else {
        bg_tile_map = 0x9800;
    }

    if (read_bit(ppu->mmu, IO_LCDCONT, MASK_LCDCONT_BGWindow_Tile_Data_Select)) {
        tile_data = 0x8000;
    } else {
        tile_data = 0x9000;
    }

    // optimization for GBA. it's ARM CPU struggled with div and mod operators
    /*oam_row = (u8)Div(line + read_u8(ppu->mmu, IO_SCROLLY), 8);*/
    /*py = (u8)DivMod(line + read_u8(ppu->mmu, IO_SCROLLY), 8);*/
    oam_row = (u8)((line + read_u8(ppu->mmu, IO_SCROLLY)) / 8);
    py = (u8)((line + read_u8(ppu->mmu, IO_SCROLLY)) % 8);

    u8 i, j;
    for (i = 0; i < 32; i++) {
        if (tile_data == 0x9000) {
            obj = (s8)read_u8(ppu->mmu, bg_tile_map + oam_row * 32 + i);
        } else {
            obj = (u8)read_u8(ppu->mmu, bg_tile_map + oam_row * 32 + i);
        }
        py_a = read_u8(ppu->mmu, tile_data + obj * 16 + py * 2);
        py_b = read_u8(ppu->mmu, tile_data + obj * 16 + py * 2 + 1);
        for (j = 0; j < 8; j++) {
            ppu->bg_disp[line * 256 + (u8)(i * 8 - read_u8(ppu->mmu, IO_SCROLLX) + j)] =
                ppu_get_palette_color(ppu, IO_BGRDPAL,
                                      ((py_a & (1 << (7 - j))) ? 1 : 0) +
                                      ((py_b & (1 << (7 - j))) ? 2 : 0)
                                      );
        }
    }
}

void ppu_draw_line_win(gbc_ppu *ppu, u8 line) {
    u16 win_tile_map, tile_data;
    u8 oam_row, py;
    u8 py_a, py_b;
    s16 obj;

    if (read_u8(ppu->mmu, IO_WNDPOSY)  > line || read_u8(ppu->mmu, IO_WNDPOSX) > SIZE_X) {
        return;
    }

    if (read_bit(ppu->mmu, IO_LCDCONT, MASK_LCDCONT_Window_Tile_Map_Display_Select)) {
        win_tile_map = 0x9C00;
    } else {
        win_tile_map = 0x9800;
    }

    if (read_bit(ppu->mmu, IO_LCDCONT, MASK_LCDCONT_BGWindow_Tile_Data_Select)) {
        tile_data = 0x8000;
    } else {
        tile_data = 0x9000;
    }

    // optimization for GBA. it's ARM CPU struggled with div and mod operators
    /*oam_row = Div((u8)(line - read_u8(ppu->mmu, IO_WNDPOSY)), 8);*/
    /*py = DivMod((u8)(line - read_u8(ppu->mmu, IO_WNDPOSY)), 8);*/
    oam_row = (u8)((line - read_u8(ppu->mmu, IO_WNDPOSY)) / 8);
    py = (u8)((line - read_u8(ppu->mmu, IO_WNDPOSY)) % 8);
    u8 i, j;
    for (i = 0; i < (SIZE_X - (read_u8(ppu->mmu, IO_WNDPOSX) - 8)) / 8 + 1; i++) {
        if (tile_data == 0x9000) {
            obj = (s8)read_u8(ppu->mmu, win_tile_map + oam_row * 32 + i);
        } else {
            obj = (u8)read_u8(ppu->mmu, win_tile_map + oam_row * 32 + i);
        }
        py_a = read_u8(ppu->mmu, tile_data + obj * 16 + py * 2);
        py_b = read_u8(ppu->mmu, tile_data + obj * 16 + py * 2 + 1);
        for (j = 0; j < 8; j++) {
            ppu->win_disp[line * 256 + (u8)(i * 8 + read_u8(ppu->mmu, IO_WNDPOSX) - 7 + j)] =
                ppu_get_palette_color(ppu, IO_BGRDPAL,
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
void ppu_draw_line_obj(gbc_ppu *ppu, u8 line) {
    u8 obj_height, py;
    line += SPRITE_INI_Y;

    switch (read_bit(ppu->mmu, IO_LCDCONT, MASK_LCDCONT_OBJ_Size)) {
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
        obj.y = read_u8(ppu->mmu, addr++);
        obj.x = read_u8(ppu->mmu, addr++);
        obj.pat = read_u8(ppu->mmu, addr++);
        obj.flags = read_u8(ppu->mmu, addr);

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
        u8 t1 = read_u8(ppu->mmu, 0x8000 + obj.pat * 16 + py * 2);
        u8 t2 = read_u8(ppu->mmu, 0x8000 + obj.pat * 16 + py * 2 + 1);

        for (j = 0; j < 8; j++) {
            pos = line * 256 + (obj.x + (x_flip ? 7 - j : j)) % 256;

            u8 color;
            u8 color_index = ((t1 & (1 << (7 - j))) ? 1 : 0) +
                             ((t2 & (1 << (7 - j))) ? 2 : 0);
            if (obj.flags & OPT_OBJ_Flag_palette) {
                color = ppu_get_palette_color(ppu, IO_OBJ1PAL, color_index);
            } else {
                color = ppu_get_palette_color(ppu, IO_OBJ0PAL, color_index);
            }

            ppu->obj_disp[pos] = color;
            if (!(obj.flags & OPT_OBJ_Flag_priority)) {
                ppu->obj_disp[pos] |= 4;
            }
        }
    }
}

void ppu_draw_line(gbc_ppu *ppu, u8 line) {
    if (read_bit(ppu->mmu, IO_LCDCONT, MASK_LCDCONT_LCD_Display_Enable)) {
        if (read_bit(ppu->mmu, IO_LCDCONT, MASK_LCDCONT_BG_Display_Enable)) {
            ppu_draw_line_bg(ppu, line);
        }
        if (read_bit(ppu->mmu, IO_LCDCONT, MASK_LCDCONT_Window_Display_Enable)) {
            ppu_draw_line_win(ppu, line);
        }
        if (read_bit(ppu->mmu, IO_LCDCONT, MASK_LCDCONT_OBJ_Display_Enable)) {
            ppu_draw_line_obj(ppu, line);
        }
    }

    ppu_draw_line_fb(ppu, line);
}

void sdl_run(gbc_ppu *ppu) {
#if defined(SLOPPY_RENDER)
#endif
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
u8 ppu_run(gbc_ppu *ppu, int cycles) {
    ppu->mode_clock += cycles;

    if (ppu->mode_clock >= LCD_LINE_CYCLES) {
        ppu->mode_clock -= LCD_LINE_CYCLES;

        // next line
        write_u8(ppu->mmu, IO_CURLINE, (read_u8(ppu->mmu, IO_CURLINE) + 1) % LCD_VERT_LINES);

        // LYC Update
        if (read_u8(ppu->mmu, IO_CURLINE) == read_u8(ppu->mmu, IO_CMPLINE)) {
            set_bit(ppu->mmu, IO_LCDSTAT, MASK_LCDSTAT_COINCIDENCE_FLAG);
            if (read_bit(ppu->mmu, IO_LCDSTAT, MASK_LCDSTAT_LYC_LY_COINCIDENCE_INTERRUPT)) {
                set_bit(ppu->mmu, IO_IFLAGS, MASK_INT_LCDSTAT_INT);
            }
        } else {
            unset_bit(ppu->mmu, IO_LCDSTAT, MASK_LCDSTAT_COINCIDENCE_FLAG);
        }

        // VBLANK
        if (read_u8(ppu->mmu, IO_CURLINE) == SIZE_Y) {
            // Set Mode Flag to VBLANK at LCDSTAT
            unset_bit(ppu->mmu, IO_LCDSTAT, MASK_LCDSTAT_MODE_FLAG);
            set_bit(ppu->mmu, IO_LCDSTAT, OPT_MODE_VBLANK);

            // Interrupt VBlank
            set_bit(ppu->mmu, IO_IFLAGS, MASK_INT_VBLANK);
            if (read_bit(ppu->mmu, IO_LCDSTAT, MASK_LCDSTAT_MODE_1_VBLANK_INTERRUPT)) {
                set_bit(ppu->mmu, IO_IFLAGS, MASK_INT_LCDSTAT_INT);
            }

            if (read_bit(ppu->mmu, IO_LCDSTAT, MASK_LCDSTAT_MODE_2_OAM_INTERRUPT)) {
                set_bit(ppu->mmu, IO_IFLAGS, MASK_INT_LCDSTAT_INT);
            }
            sdl_run(ppu);
            ppu_dump(ppu);
        }
        // Normal line
        else if (read_u8(ppu->mmu, IO_CURLINE) < SIZE_Y) {
            unset_bit(ppu->mmu, IO_LCDSTAT, MASK_LCDSTAT_MODE_FLAG);
            set_bit(ppu->mmu, IO_LCDSTAT, OPT_MODE_OAM);

            if (read_bit(ppu->mmu, IO_LCDSTAT, MASK_LCDSTAT_MODE_2_OAM_INTERRUPT)) {
                set_bit(ppu->mmu, IO_IFLAGS, MASK_INT_LCDSTAT_INT);
            }
        }
    } else if (((read_u8(ppu->mmu, IO_LCDSTAT) & MASK_LCDSTAT_MODE_FLAG) == OPT_MODE_OAM) && ppu->mode_clock >= END_OAM) {
        unset_bit(ppu->mmu, IO_LCDSTAT, MASK_LCDSTAT_MODE_FLAG);
        set_bit(ppu->mmu, IO_LCDSTAT, OPT_MODE_OAM_VRAM);
    } else if (((read_u8(ppu->mmu, IO_LCDSTAT) & MASK_LCDSTAT_MODE_FLAG) == OPT_MODE_OAM_VRAM) && ppu->mode_clock >= END_OAM_VRAM) {
        unset_bit(ppu->mmu, IO_LCDSTAT, MASK_LCDSTAT_MODE_FLAG);
        set_bit(ppu->mmu, IO_LCDSTAT, OPT_MODE_HBLANK);
        ppu_draw_line(ppu, read_u8(ppu->mmu, IO_CURLINE));

        if (read_bit(ppu->mmu, IO_LCDSTAT, MASK_LCDSTAT_MODE_0_HBLANK_INTERRUPT)) {
            set_bit(ppu->mmu, IO_IFLAGS, MASK_INT_LCDSTAT_INT);
        }
    }
    return 0;
}

unsigned long gbcToRgb32(unsigned const bgr15) {
    unsigned long const r = bgr15       & 0x1F;
    unsigned long const g = bgr15 >>  5 & 0x1F;
    unsigned long const b = bgr15 >> 10 & 0x1F;

    return ((r * 13 + g * 2 + b) >> 1) << 16
           | (g * 3 + b) << 9
           | (r * 3 + g * 2 + b * 11) >> 1;
}

/*u16 rgb32ToRgb16(u32 rgb32) {*/
/*int red = red / 8;*/
/*int green = green / 4;*/
/*int blue = blue / 8;*/
/*return RGB8(red, green, blue);*/
/*}*/

/*u16 color_dmg_to_gba(unsigned const bgr15) {*/
/*return rgb32ToRgb16(gbcToRgb32(bgr15));*/
/*//return gbcToRgb32(bgr15);*/
/*}*/

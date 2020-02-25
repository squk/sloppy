#include <gba_systemcalls.h>
#include <gba_video.h>
#include <string.h>
#include <stdio.h>

#include "gbc_gpu.h"
#include "gbc_io.h"
#include "gbc_mmu.h"
#include "text.h"

// Bit 7-6 - Shade for Color Number 3
// Bit 5-4 - Shade for Color Number 2
// Bit 3-2 - Shade for Color Number 1
// Bit 1-0 - Shade for Color Number 0
void set_palette(u8* p, u8 v)  {
	p[0] = v & 0x03;
	p[1] = (v & 0x0C) >> 2;
	p[2] = (v & 0x30) >> 4;
	p[3] = (v & 0xC0) >> 6;
}

void gpu_write_u8(gbc_gpu *gpu, u16 address, u8 v) {
	switch (address) {
	    case IO_CURLINE:
		    gpu->reset = 1;
		    break;
	    case IO_CMPLINE:
		    gpu->cmp_line = v;
		    break;
	    case IO_BGRDPAL:
		    gpu->BGP = v;
		    set_palette(gpu->bg_palette, v);
		    break;
	    case IO_OBJ0PAL:
		    gpu->OBP0 = v;
		    set_palette(gpu->obj0_palette, v);
            // color 0 should always be transparency for OBJ layers
		    gpu->obj0_palette[0] = TRANSPARENT;
		    break;
	    case IO_OBJ1PAL:
		    gpu->OBP1 = v;
		    set_palette(gpu->obj1_palette, v);
            // color 0 should always be transparency for OBJ layers
		    gpu->obj1_palette[0] = TRANSPARENT;
		    break;
	    case IO_SCROLLY:
		    gpu->scroll_y = v;
		    break;
	    case IO_SCROLLX:
		    gpu->scroll_x = v;
		    break;
	    case IO_WNDPOSY:
		    gpu->wndpos_y = v;
		    break;
	    case IO_WNDPOSX:
		    gpu->wndpos_x = v;
		    break;
	    case IO_LCDSTAT:
		    gpu->lcd_stat = (gpu->lcd_stat & 0x07) | (v & 0xF8);
	    default:
		    break;
	}
}

u8 gpu_read_u8(gbc_gpu *gpu, u16 address) {
	switch (address) {
		case IO_CURLINE:
			return gpu->cur_line;
		case IO_CMPLINE:
			return gpu->cmp_line;
		case IO_BGRDPAL:
			return gpu->BGP;
		case IO_OBJ0PAL:
			return gpu->OBP0;
		case IO_OBJ1PAL:
			return gpu->OBP1;
		case IO_SCROLLY:
			return gpu->scroll_y;
		case IO_SCROLLX:
			return gpu->scroll_x;
		case IO_WNDPOSY:
			return gpu->wndpos_y;
		case IO_WNDPOSX:
			return gpu->wndpos_x;
		case IO_LCDSTAT:
			return gpu->lcd_stat;
		default:
			return 0;
	}
}

void gpu_start_frame(gbc_gpu *gpu) {
	int i, j;
	gpu->oam = TL_OAM;
	gpu->oam_vram = TL_OAM_VRAM;
	gpu->hblank = TL_HBLANK;
	gpu->vblank = TF_VBLANK;

	gpu->cur_line = -1;
	// set win and obj to transparent
	for (i = 0; i < 256; i++) {
		for (j = 0; j < 256; j++) {
			gpu->bg_disp[i * 256 + 1] = 0;
			gpu->win_disp[i * 256 + j] = TRANSPARENT;
			gpu->obj_disp[i * 256 + j] = TRANSPARENT;

            /*if (i > 200) {*/
                /*char s[80];*/
                /*sprintf(s, "i:%d     j: %d", i, j);*/
                /*put_l(s);*/
            /*}*/
		}
	}
    /*put_l("bop");*/
	u8 r = gpu_run(gpu, 0);
    /*char s[80];*/
    /*sprintf(s, "r:%d", r);*/
    /*put_l(s);*/
}

// TODO: cleanup and optimize
void gpu_draw_line_fb(gbc_gpu *gpu, u8 line) {
	for (u8 x = 0; x < SIZE_X; x++) {
        u8 row_index = line * SIZE_X;

        u8 *px_ptr = &gpu->fb[row_index + x];
		u8 px = gpu->bg_disp[line * 256 + x];

		u16 cpx = RGB8(px, px, px);

		if (gpu->win_disp[line * 256 + x] < 8) {
			px = gpu->win_disp[line * 256 + x];
		}

		if (gpu->obj_disp[(line + SPRITE_INI_Y) * 256 + x + SPRITE_INI_X] < 8) {
			if (px != 0 && gpu->obj_disp[(line + SPRITE_INI_Y) * 256 + x + SPRITE_INI_X] >= 4) {
				continue;
			}
			px = gpu->obj_disp[(line + SPRITE_INI_Y) * 256 + x + SPRITE_INI_X] & 0x03;
		}

        char s[80];
        sprintf(s, "PX: %x, CPX: %x", px, cpx);
        put_l(s);

        *px_ptr = px;
	}
    /*memcpy(MODE3_FB, &gpu->fb, SIZE_X*SIZE_Y);*/
}

void gpu_draw_line_bg(gbc_gpu *gpu, u8 line) {
	u16 bg_tile_map, tile_data;
	u8 oam_row, obj_line;
	u8 obj_line_a, obj_line_b;
	int16_t obj;
	/*int16_t obj;*/

	switch (read_bit(gpu->mmu, IO_LCDCONT,
	            MASK_LCDCONT_BG_Tile_Map_Display_Select)) {
        case OPT_BG_Tile_Map_0:
            bg_tile_map = 0x9800;
            break;
        case OPT_BG_Tile_Map_1:
            bg_tile_map = 0x9C00;
            break;
	}

	switch (read_bit(gpu->mmu, IO_LCDCONT,
	            MASK_LCDCONT_BGWindow_Tile_Data_Select)) {
        case OPT_BGWindow_Tile_Data_0:
            tile_data = 0x9000;
            break;
        case OPT_BGWindow_Tile_Data_1:
            tile_data = 0x8000;
            break;
	}

	oam_row = (u8)Div(line + gpu->scroll_y, 8);
	obj_line = (u8)DivMod(line + gpu->scroll_y, 8);

	u8 i, j;
	for (i = 0; i < 32; i++) {
		if (tile_data == 0x9000) {
			obj = (int8_t)gpu_read_u8(gpu, bg_tile_map + oam_row * 32 + i);
		} else {
			obj = (u8)gpu_read_u8(gpu, bg_tile_map + oam_row * 32 + i);
		}
		obj_line_a = gpu_read_u8(gpu, tile_data + obj * 16 + obj_line * 2);
		obj_line_b = gpu_read_u8(gpu, tile_data + obj * 16 + obj_line * 2 + 1);
		for (j = 0; j < 8; j++) {
			gpu->bg_disp[line * 256 + (u8)(i * 8 - gpu->scroll_x + j)] =
				gpu->bg_palette[
				((obj_line_a & (1 << (7 - j))) ? 1 : 0) +
				    ((obj_line_b & (1 << (7 - j))) ? 2 : 0)
				];
		}
	}
}

void gpu_draw_line_win(gbc_gpu *gpu, u8 line) {
	u16 win_tile_map, tile_data;
	u8 oam_row, obj_line;
	u8 obj_line_a, obj_line_b;
	int16_t obj;

	if (gpu->wndpos_y > line || gpu->wndpos_x > SIZE_X) {
		return;
	}

	switch (read_bit(gpu->mmu, IO_LCDCONT, MASK_LCDCONT_Window_Tile_Map_Display_Select)) {
	    case OPT_Window_Tile_Map_0:
		    win_tile_map = 0x9800;
		    break;
	    case OPT_Window_Tile_Map_1:
		    win_tile_map = 0x9C00;
		    break;
	}

	switch (read_bit(gpu->mmu, IO_LCDCONT, MASK_LCDCONT_BGWindow_Tile_Data_Select)) {
	    case OPT_BGWindow_Tile_Data_0:
		    tile_data = 0x9000;
		    break;
	    case OPT_BGWindow_Tile_Data_1:
		    tile_data = 0x8000;
		    break;
	}

	// TODO
	oam_row = Div((u8)(line - gpu->wndpos_y), 8);
	obj_line = DivMod((u8)(line - gpu->wndpos_y), 8);
	u8 i, j;
	for (i = 0; i < (SIZE_X - (gpu->wndpos_x - 8)) / 8 + 1; i++) {
		if (tile_data == 0x9000) {
			obj = (int8_t)gpu_read_u8(gpu, win_tile_map + oam_row * 32 + i);
		} else {
			obj = (u8)gpu_read_u8(gpu, win_tile_map + oam_row * 32 + i);
		}
		obj_line_a = gpu_read_u8(gpu, tile_data + obj * 16 + obj_line * 2);
		obj_line_b = gpu_read_u8(gpu, tile_data + obj * 16 + obj_line * 2 + 1);
		for (j = 0; j < 8; j++) {
			gpu->win_disp[line * 256 + (u8)(i * 8 + gpu->wndpos_x - 7 + j)] =
				gpu->bg_palette[
				((obj_line_a & (1 << (7 - j))) ? 1 : 0) +
				    ((obj_line_b & (1 << (7 - j))) ? 2 : 0)
				];
		}
	}
}

int obj_comp(void *array, int i, int j) {
	gpu_obj *a = ((gpu_obj**)array)[i];
	gpu_obj *b = ((gpu_obj**)array)[j];

	if (a->x < b->x) {
		return 0;
	}
	if (a->x > b->x) {
		return 1;
	}

	if (a->id < b->id) {
		return 0;
	}
	if (a->id > b->id) {
		return 1;
	}
	// this should never be reached
	return 0;
}

void obj_swap(void *array, int i, int j) {
	gpu_obj *a = ((gpu_obj**)array)[i];
	gpu_obj *b = ((gpu_obj**)array)[j];

	((gpu_obj**)array)[i] = b;
	((gpu_obj**)array)[j] = a;
}

// 8x8 or 8x16
// Object Pattern Table = 8000 - 8FFF
// Object Atribute Table = FE00 - FE9F
// 10 sprites per scan line
// higher X -> draw first (lower X -> draw above others)
// same X -> FE00 highest, FE04 next highest
// Y = 0 or Y => 144+16, discard sprite
void gpu_draw_line_obj(gbc_gpu *gpu, u8 line) {
	int i, j, first;
	uint16_t addr, pos;
	u8 obj_height, objs_line_len, obj_line;
	u8 obj_line_a, obj_line_b, color;
	u8 x_flip, y_flip, behind;
	u8 *pal;
	gpu_obj objs[40];
	gpu_obj *objs_line[40];

	line += SPRITE_INI_Y;

	switch (read_bit(gpu->mmu, IO_LCDCONT, MASK_LCDCONT_OBJ_Size)) {
	    case OPT_OBJ_Size_8x8:
		    obj_height = 8;
		    break;
	    case OPT_OBJ_Size_8x16:
		    obj_height = 16;
		    break;
	}
	// Read all the obj attributes
	for (i = 0; i < 40; i++) {
		addr = MEM_OAM + i * 4;

		objs[i].id = i;
		objs[i].y = read_u8(gpu->mmu, addr++);
		objs[i].x = read_u8(gpu->mmu, addr++);
		objs[i].pat = read_u8(gpu->mmu, addr++);
		objs[i].flags = read_u8(gpu->mmu, addr);
	}

	// Take the candidate objects to be drawn in the line
	objs_line_len = 0;
	for (i = 0; i < 40; i++) {
		if((objs[i].y != 0) && (objs[i].y < SPRITE_END_Y) &&
				(objs[i].y <= line) && ((objs[i].y + obj_height) > line)) {
			objs_line[objs_line_len++] = &objs[i];
			/*
			   printf("Object %d:\n", objs[i].id);
			   printf("x: %02X, y: %02X, pat: %02X\n",
			   objs[i].x, objs[i].y, objs[i].pat);
			   printf("\n");
			   */
			//return;
		}
	}

	// Sort the candidate objects by priority
	/*insertion_sort(objs_line, objs_line_len, obj_comp, obj_swap);*/

	// Draw objects by order of priority
	if (objs_line_len > 10) {
		first = objs_line_len - 10;
	} else {
		first = 0;
	}

	for (i = first; i < objs_line_len; i++) {
		x_flip = (objs_line[i]->flags & OPT_OBJ_Flag_xflip) ? 1 : 0;
		y_flip = (objs_line[i]->flags & OPT_OBJ_Flag_yflip) ? 1 : 0;
		obj_line = (line - objs_line[i]->y) % obj_height;
		if (y_flip) {
			obj_line = obj_height - 1 - obj_line;
		}
		obj_line_a = read_u8(gpu->mmu, 0x8000 + objs_line[i]->pat * 16 +
				obj_line * 2);
		obj_line_b = read_u8(gpu->mmu, 0x8000 + objs_line[i]->pat * 16 +
				obj_line * 2 + 1);
		if (objs_line[i]->flags & OPT_OBJ_Flag_palette) {
			pal = gpu->obj1_palette;
		} else {
			pal = gpu->obj0_palette;
		}
		if (objs_line[i]->flags & OPT_OBJ_Flag_priority) {
			behind = 1;
		} else {
			behind = 0;
		}
		for (j = 0; j < 8; j++) {
			pos = line * 256 +
				(objs_line[i]->x + (x_flip ? 7 - j : j)) % 256;
			color = pal[
				((obj_line_a & (1 << (7 - j))) ? 1 : 0) +
				    ((obj_line_b & (1 << (7 - j))) ? 2 : 0)
			];
			if (color < 8) {
				gpu->obj_disp[pos] = color;
				if (behind) {
					gpu->obj_disp[pos] |= 4;
				}
			}
		}
	}
}

void gpu_draw_line(gbc_gpu *gpu, u8 line) {
	if (read_bit(gpu->mmu, IO_LCDCONT, MASK_LCDCONT_BG_Display_Enable)) {
		gpu_draw_line_bg(gpu, line);
	}
	if (read_bit(gpu->mmu, IO_LCDCONT, MASK_LCDCONT_Window_Display_Enable)) {
		gpu_draw_line_win(gpu, line);
	}
    if (read_bit(gpu->mmu, IO_LCDCONT, MASK_LCDCONT_OBJ_Display_Enable)) {
        gpu_draw_line_obj(gpu, line);
    }
    gpu_draw_line_fb(gpu, line);
}

u8 gpu_run(gbc_gpu *gpu, int cycles) {
    /*char s[80];*/
    /*sprintf(s, "LCDCONT: %0b", read_u8(gpu->mmu, IO_LCDCONT));*/
    /*put_l(s);*/

	if (!read_bit(gpu->mmu, IO_LCDCONT, MASK_LCDCONT_LCD_Display_Enable)) {
		gpu->reset = 1;
        return 0;
	}
	if (gpu->reset) {
        /*put_l("RESET");*/
		gpu->reset = 0;
        return 1;
	}

    put_l("pre-");
	gpu->oam -= cycles;
	gpu->oam_vram -= cycles;
	gpu->hblank -= cycles;
	gpu->vblank -= cycles;
    put_l("cycles-");

	// OAM mode 2
	if (gpu->oam <= 0) {
        put_l("oam mode 2");
		// update CURLINE REG
		gpu->cur_line = (gpu->cur_line + 1);// % LINES;
		if (gpu->cur_line == gpu->cmp_line) {
			set_bit(gpu->mmu, gpu->lcd_stat, MASK_LCDSTAT_COINCIDENCE_FLAG);
			if (read_bit(gpu->mmu, gpu->lcd_stat,
					    MASK_LCDSTAT_LYC_LY_COINCIDENCE_INTERRUPT)) {
				set_bit(gpu->mmu, IO_IFLAGS, MASK_INT_LCDSTAT_INT);
			}
		} else {
			unset_bit(gpu->mmu, gpu->lcd_stat, MASK_LCDSTAT_COINCIDENCE_FLAG);
		}

		if (gpu->cur_line < SIZE_Y) {
			gpu->lcd_stat = (gpu->lcd_stat & 0xF3) | 0x02;
			// Set Mode Flag to OAM at LCDSTAT
			unset_bit(gpu->mmu, gpu->lcd_stat, MASK_LCDSTAT_MODE_FLAG);
			set_bit(gpu->mmu, gpu->lcd_stat, OPT_MODE_OAM);
			// Interrupt OAM
			if (read_bit(gpu->mmu, gpu->lcd_stat,
					    MASK_LCDSTAT_MODE_2_OAM_INTERRUPT)) {
				set_bit(gpu->mmu, IO_IFLAGS, MASK_INT_LCDSTAT_INT);
			}
		}

		gpu->oam += DUR_LINE;

	}
	// OAM VRAM mode 3
	if (gpu->oam_vram <= 0) {
        put_l("oam vram mode 3");
		if (gpu->cur_line < SIZE_Y) {
			gpu->lcd_stat = (gpu->lcd_stat & 0xF3) | 0x03;
			// Set Mode Flag to OAM VRAM at LCDSTAT
			unset_bit(gpu->mmu, gpu->lcd_stat, MASK_LCDSTAT_MODE_FLAG);
			set_bit(gpu->mmu, gpu->lcd_stat, OPT_MODE_OAM_VRAM);
		}
		gpu->oam_vram += DUR_LINE;
	}
	// HBLANK mode 0
	if (gpu->hblank <= 0) {
        put_l("hblank mode 0");
		if (gpu->cur_line < SIZE_Y) {
			gpu->lcd_stat = (gpu->lcd_stat & 0xF3) | 0x00;
			// Set Mode Flag to HBLANK at LCDSTAT
			unset_bit(gpu->mmu, gpu->lcd_stat, MASK_LCDSTAT_MODE_FLAG);
			set_bit(gpu->mmu, gpu->lcd_stat, OPT_MODE_HBLANK);
			// Interrupt HBlank
			if (read_bit(gpu->mmu, gpu->lcd_stat, MASK_LCDSTAT_MODE_0_HBLANK_INTERRUPT)) {
				set_bit(gpu->mmu, IO_IFLAGS, MASK_INT_LCDSTAT_INT);
			}
			gpu_draw_line(gpu, gpu->cur_line);
		}
		gpu->hblank += DUR_LINE;
	}
	// VBLANK mode 1
	if (gpu->vblank <= 0) {
        put_l("vblank mode 1");
		gpu->lcd_stat = (gpu->lcd_stat & 0xF3) | 0x01;
		// Set Mode Flag to VBLANK at LCDSTAT
		unset_bit(gpu->mmu, gpu->lcd_stat, MASK_LCDSTAT_MODE_FLAG);
		set_bit(gpu->mmu, gpu->lcd_stat, OPT_MODE_VBLANK);
		// Interrupt VBlank
		set_bit(gpu->mmu, IO_IFLAGS, MASK_INT_VBLANK);
		if (read_bit(gpu->mmu, gpu->lcd_stat, MASK_LCDSTAT_MODE_1_VBLANK_INTERRUPT)) {
			set_bit(gpu->mmu, IO_IFLAGS, MASK_INT_LCDSTAT_INT);
		}
		gpu->vblank += DUR_FRAME;
	}
}

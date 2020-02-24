#include "gbc_gpu.h"
#include "gbc_io.h"

// Bit 7-6 - Shade for Color Number 3
// Bit 5-4 - Shade for Color Number 2
// Bit 3-2 - Shade for Color Number 1
// Bit 1-0 - Shade for Color Number 0
void set_palette(u8* p, u8 v)  {
	pal[0] = v & 0x03;
	pal[1] = (v & 0x0C) >> 2;
	pal[2] = (v & 0x30) >> 4;
	pal[3] = (v & 0xC0) >> 6;
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
		    set_pal(gpu->bg_palette, v);
		    break;
	    case IO_OBJ0PAL:
		    gpu->OBP0 = v;
		    set_pal(gpu->obj0_palette, v);
            // color 0 should always be transparency for OBJ layers
		    gpu->obj0_pal[0] = TRANSPARENT;
		    break;
	    case IO_OBJ1PAL:
		    gpu->obp1 = v;
		    set_pal(obj1_palette, v);
            // color 0 should always be transparency for OBJ layers
		    gpu->obj1_pal[0] = TRANSPARENT;
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

u8 gpu_read_u8(gbc_gpu *gpu, u8 address) {
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
	gpu->t_oam = SCREEN_TL_OAM;
	gpu->t_oam_vram = SCREEN_TL_OAM_VRAM;
	gpu->t_hblank = SCREEN_TL_HBLANK;
	gpu->t_vblank = SCREEN_TF_VBLANK;

	gpu->cur_line = -1;
	// set win and obj to transparent
	for (j = 0; j < 256; j++) {
		for (i = 0; i < 256; i++) {
			gpu->bg_disp[j * 256 + 1] = 0;
			gpu->win_disp[j * 256 + i] = TRANSPARENT;
			gpu->obj_disp[j * 256 + i] = TRANSPARENT;
		}
	}
	gpu_run(0);
}

void gpu_run(int cycles) {

}

#include <gba_console.h>
#include <gba_video.h>

#include <gba_interrupt.h>
#include <gba_systemcalls.h>

#include <stdio.h>
#include "r6502_portfont_bin.h"

void set_pallete(const u16 palette[]) {
	u16 *temppointer;

	// load the palette for the background, 7 colors
	temppointer = BG_COLORS;
	for(u8 i=0; i<7; i++) {
		*temppointer++ = palette[i];
	}
}

void load_font() {
	CpuFastSet(r6502_portfont_bin, (u16*)VRAM, (r6502_portfont_bin_size / 4) | COPY32);
}

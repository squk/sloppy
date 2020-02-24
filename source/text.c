#include <gba_base.h>
#include <gba_video.h>
#include <gba_systemcalls.h>
#include <gba_interrupt.h>
#include <stdio.h>
#include <string.h>

#include "text.h"

#define MAPADDRESS		MAP_BASE_ADR(31)	// our base map address

void put_c(int x, int y, char c) {
	// write a character - we subtract 32, because the font graphics
	// start at tile 0, but our text is in ascii (starting at 32 and up)
    *((u16 *)MAPADDRESS + x + (y * 32)) = c - 32;
}

void put_s(int row, const char *text) {
	for(int i=0; i<strlen(text); i++) {
        put_c(i, row, text[i]);
    }
}

int screen_line = 0;
void put_l(const char *text) {
    put_s(screen_line++, text);

    if (screen_line > 10) {
        clear();
    }
}

void clear() {
    screen_line = 0;
    *((u32 *)MAP_BASE_ADR(31)) = 0;
    CpuFastSet( MAP_BASE_ADR(31), MAP_BASE_ADR(31), FILL | COPY32 | (0x800/4));
}

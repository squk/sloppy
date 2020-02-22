#include <gba_base.h>
#include <gba_video.h>
#include <gba_systemcalls.h>
#include <gba_interrupt.h>
#include <stdio.h>
#include <string.h>

#define MAPADDRESS		MAP_BASE_ADR(31)	// our base map address

void put_s(int row, const char *text) {
	for(int i=0; i<strlen(text); i++) {
        put_c(i, row, text[i]);
    }
}

void put_c(int x, int y, char c) {
	// write a character - we subtract 32, because the font graphics
	// start at tile 0, but our text is in ascii (starting at 32 and up)
    *((u16 *)MAPADDRESS + x + (y * 32)) = c - 32;
}

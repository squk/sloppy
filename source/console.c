#include <gba_console.h>
#include <gba_video.h>

#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include<string.h>

#include <stdio.h>

u8 cli_line = 0;

void cli_clear() {
    cli_line = 0;
	// ansi escape sequence to clear screen and home cursor
	// /x1b[line;columnH
    iprintf("\x1b[2J");
    /**((u32 *)MAP_BASE_ADR(31)) = 0;*/
    /*CpuFastSet( MAP_BASE_ADR(31), MAP_BASE_ADR(31), FILL | COPY32 | (0x800/4));*/
}


void cli_print(int x, int y, const char *msg) {
    char s[80];
	sprintf(s, "\x1b[%d;%dH%s", y, x, msg);
	iprintf(s);
}

void cli_printl(const char *text) {
    cli_print(0, cli_line++, text);

    if (cli_line > 18) {
        cli_clear();
    }
}

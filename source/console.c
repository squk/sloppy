#include <gba_console.h>
#include <gba_video.h>

#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include<string.h>

#include <stdio.h>

void cli_clear() {
	// ansi escape sequence to clear screen and home cursor
	// /x1b[line;columnH
	iprintf("\x1b[2J");
}


u8 line = 0;

void cli_print(int x, int y, const char *msg) {
    char s[80];
	sprintf(s, "\x1b[%d;%dH%s", x, y, msg);
	iprintf(s);
}

// print on current line and move cursor to next line
void cli_n(const char msg[]) {
    if (line > 9) {
        cli_clear();
    }
    cli_print(0, line, msg);
    line++;
}

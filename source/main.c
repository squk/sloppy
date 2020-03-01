#include <gba_base.h>
#include <gba_video.h>
#include <gba_console.h>
#include <gba_systemcalls.h>
#include <gba_interrupt.h>
#include <stdio.h>

#include "font.h"
#include "text.h"
#include "gbc_emu.h"

#define MAPADDRESS        MAP_BASE_ADR(31)    // our base map address

int main(void) {
    // Set up the interrupt handlers
    irqInit();
    // Enable Vblank Interrupt to allow VblankIntrWait
    irqEnable(IRQ_VBLANK);

    bool debug = true;
	if (debug) {
	    consoleDemoInit();

        REG_IME = 1;

        set_pallete(PALETTE_0);
        emu_test();

    } else {
        SetMode( MODE_4 | BG3_ON );
        emu_run();
    }

    // screen mode & background to display
}

#include <gba_base.h>
#include <gba_video.h>
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

    REG_IME = 1;

    set_pallete(PALETTE_0);
    load_font();

    // clear screen map with tile 0 ('space' tile) (256x256 halfwords)
    *((u32 *)MAP_BASE_ADR(31)) =0;
    CpuFastSet( MAP_BASE_ADR(31), MAP_BASE_ADR(31), FILL | COPY32 | (0x800/4));

    // set screen H and V scroll positions
    /*BG_OFFSET[0].x = 0; BG_OFFSET[0].y = 0;*/

    put_l("TEMW - this emu might work");
    // set the screen base to 31 (0x600F800) and char base to 0 (0x6000000)
    BGCTRL[0] = SCREEN_BASE(31);

    // screen mode & background to display
    emu_test();
}

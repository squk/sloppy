#include <stdio.h>
#include "gbc_emu.h"

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO);
    printf("starting CPU loop\n");

    emu_test();

   return 0;
}

#include <stdio.h>
#include "gbc_emu.h"

int main(int argc, char *argv[]) {
    printf("starting CPU loop\n");

    /*SDL_Init(SDL_INIT_VIDEO);*/
    emu_test();

   return 0;
}

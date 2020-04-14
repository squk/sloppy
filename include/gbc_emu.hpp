#pragma once

#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

#include "types.h"
#include "gbc_cpu.h"
#include "gbc_ops.h"
#include "gbc_ppu.h"
#include "gbc_mmu.h"

class gbc_emu {
    public:
        gbc_cpu cpu;
        gbc_ppu ppu;
        gbc_mmu mmu;
        gbc_mbc mbc;

        SDL_Renderer *renderer;
        SDL_Window *window;

        gbc_emu();
        void run();
        void test();
};

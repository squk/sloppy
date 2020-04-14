#pragma once

#include <string>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

#include "types.h"
#include "gbc_cpu.hpp"
//#include "gbc_ops.hpp"
#include "gbc_ppu.hpp"
#include "gbc_mmu.hpp"

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

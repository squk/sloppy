#pragma once

#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

#include "types.h"
#include "gbc_cpu.h"
#include "gbc_ppu.h"
#include "gbc_cartridge.h"
#include "gbc_mbc.h"
#include "gbc_mmu.h"

#include "01_special.h"
#include "02_interrupts.h"
#include "03_op_sp_hl.h"
#include "04_op_r_imm.h"
#include "05_op_rp.h"
#include "06_ld_r_r.h"
#include "07_jr_jp_call_ret_rst.h"
#include "08_misc_instr.h"
#include "09_op_r_r.h"
#include "10_bit_ops.h"
#include "11_op_a_mhl.h"

#include "DMG_ROM.h"

void emu_run() {
    gbc_cpu cpu;
    gbc_ppu ppu;
    gbc_mmu mmu;
    cpu.mmu = &mmu;
    ppu.mmu = &mmu;

    cpu.ppu = &ppu;

    gbc_mmu_init(&mmu);
    gbc_cpu_reset(&cpu);
    gbc_cpu_set_boot_state(&cpu);
    //CpuFastSet(tetris_gb_bin, (u8*)mmu.rom, (tetris_gb_bin_size / 4) | COPY32);
    //CpuFastSet(cpu_instrs_gb_bin, (u8*)mmu.rom, (cpu_instrs_gb_bin_size / 4) | COPY32);

    gbc_cpu_loop(&cpu);
}

void emu_test() {

#if defined(SLOPPY_RENDER)
    SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Renderer *renderer;
    SDL_Window *window;
    float scale = 2.0f;
    SDL_CreateWindowAndRenderer(SIZE_X*scale, SIZE_Y*scale, 0, &window, &renderer);
    SDL_RenderSetScale(renderer, scale, scale);
    SDL_GL_SetSwapInterval(1);
    // Check that the window was successfully created
    if (window == NULL) {
        // In the case that the window could not be made...
        printf("Could not create window: %s\n", SDL_GetError());
        return;
    }
#endif

    gbc_cpu cpu;
    gbc_ppu ppu;
    gbc_mmu mmu;
    gbc_cartridge cart;

    cpu.mmu = &mmu;
    ppu.mmu = &mmu;
    mmu.cart = &cart;
#if defined(SLOPPY_RENDER)
    ppu.renderer = renderer;
#endif

    cpu.ppu = &ppu;

    gbc_mmu_init(&mmu);
    gbc_cpu_reset(&cpu);

    //memcpy(mmu.bios, DMG_ROM_bin, DMG_ROM_bin_len); mmu.in_bios = true;
    gbc_cpu_set_boot_state(&cpu);
    cpu.mmu->io[0x00] = 0xFF;

    //gbc_cartridge_load_rom(&cart, "./Tetris.gb");
    gbc_cartridge_load_rom(&cart, "./MarioLand.gb");
    //gbc_cartridge_load_rom(&cart, "./DrMario.gb");
    //gbc_cartridge_load_rom(&cart, "./data/sprite_priority.gb");
    //gbc_cartridge_load_rom(&cart, "data/tests/cpu_instrs/cpu_instrs.gb");
    //gbc_cartridge_load_rom(&cart, "data/mbc1/bits_bank1.gb");
    //gbc_cartridge_load_rom(&cart, "data/mbc1/bits_bank2.gb");
    //gbc_cartridge_load_rom(&cart, "data/mbc1/bits_mode.gb");
    //gbc_cartridge_load_rom(&cart, "data/mbc1/bits_ramg.gb");
    //gbc_cartridge_load_rom(&cart, "data/tests/interrupt_time/interrupt_time.gb");

    //gbc_cartridge_load_rom(&cart, "data/tests/cpu_instrs/individual/01-special.gb");
    //gbc_cartridge_load_rom(&cart, "data/tests/cpu_instrs/individual/07-jr,jp,call,ret,rst.gb");

    gbc_cpu_loop(&cpu);

#if defined(SLOPPY_RENDER)
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
#endif
}

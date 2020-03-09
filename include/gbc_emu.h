#pragma once

#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

#include "types.h"
#include "gbc_cpu.h"
#include "gbc_gpu.h"
#include "gbc_mmu.h"
#include "dmg_rom.h"

#include "tetris_gb.h"
#include "cpu_instrs_gb.h"
#include "01_special.h"
#include "08_misc_instr.h"
#include "07_jr_jp_call_ret_rst.h"

void emu_run() {
    gbc_cpu cpu;
    gbc_gpu gpu;
    gbc_mmu mmu;
    cpu.mmu = &mmu;
    gpu.mmu = &mmu;

    cpu.gpu = &gpu;

    gbc_mmu_init(&mmu);
    gbc_cpu_reset(&cpu);
    gbc_cpu_set_boot_state(&cpu);
    //CpuFastSet(tetris_gb_bin, (u8*)mmu.rom, (tetris_gb_bin_size / 4) | COPY32);
    //CpuFastSet(cpu_instrs_gb_bin, (u8*)mmu.rom, (cpu_instrs_gb_bin_size / 4) | COPY32);

    gbc_cpu_loop(&cpu);
}

void emu_test() {
    int i;

    //SDL_Renderer *renderer;
    //SDL_Window *window;
    //SDL_CreateWindowAndRenderer(SIZE_X, SIZE_Y, 0, &window, &renderer);

    gbc_cpu cpu;
    gbc_gpu gpu;
    gbc_mmu mmu;
    cpu.mmu = &mmu;
    gpu.mmu = &mmu;
    //gpu.renderer = renderer;

    cpu.gpu = &gpu;

    gbc_mmu_init(&mmu);
    gbc_cpu_reset(&cpu);

    memcpy(mmu.bios, DMG_ROM_bin, DMG_ROM_bin_len);
    mmu.in_bios = true;

    //mmu.in_bios = false;
    //cpu.registers.pc = 0x100;

    //gbc_cpu_set_boot_state(&cpu);
    gbc_load_rom(&mmu, data_tetris_gb_bin, data_tetris_gb_bin_len);
    //gbc_load_rom(&mmu, data_cpu_instrs_gb_bin, data_cpu_instrs_gb_bin_len);
    //gbc_load_rom(&mmu, __01_special_gb, __01_special_gb_len);
    //gbc_load_rom(&mmu, __08_misc_instrs_gb, __08_misc_instrs_gb_len);
    //gbc_load_rom(&mmu, __07_jr_jp_call_ret_rst_gb, __07_jr_jp_call_ret_rst_gb_len);

    printf("emulator initialized\n");
    gbc_cpu_loop(&cpu);

    //SDL_DestroyRenderer(renderer);
    //SDL_DestroyWindow(window);
    SDL_Quit();
}

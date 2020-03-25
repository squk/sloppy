#pragma once

#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>

#include "types.h"
#include "gbc_cpu.h"
#include "gbc_ppu.h"
#include "gbc_mmu.h"
#include "dmg_rom.h"

#include "tetris_gb.h"
#include "cpu_instrs_gb.h"

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

#include "mario.h"

void emu_run() {
    gbc_cpu cpu;
    gbc_ppu ppu;
    gbc_mmu mmu;
    cpu.mmu = &mmu;
    ppu.mmu = &mmu;

    cpu.ppu = &ppu;

    gbc_mmu_init(&mmu);
    gbc_cpu_reset(&cpu);
    ppu_init(&cpu);
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
    SDL_SetWindowTitle(window, "sloppy emu");
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
    cpu.mmu = &mmu;
    ppu.mmu = &mmu;
#if defined(SLOPPY_RENDER)
    ppu.renderer = renderer;
#endif

    cpu.ppu = &ppu;

    gbc_mmu_init(&mmu);
    gbc_cpu_reset(&cpu);

    //memcpy(mmu.bios, DMG_ROM_bin, DMG_ROM_bin_len); mmu.in_bios = true;
    //gbc_cpu_set_boot_state(&cpu);
    cpu.mmu->io[0x00] = 0xFF;

    //gbc_load_rom_file(&mmu, "data/sprite_priority.gb");
    //gbc_load_rom_file(&mmu, "data/tests/instr_timing/instr_timing.gb");
    //gbc_load_rom_file(&mmu, "data/tests/mem_timing/individual/01-read_timing.gb");
    //gbc_load_rom_file(&mmu, "./Tetris.gb");
    //gbc_load_rom_file(&mmu, "./vblank_stat_intr-C.gb");
    gbc_load_rom_file(&mmu, "./DrMario.gb");
    //gbc_load_rom_file(&mmu, "./MarioLand.gb"); // required mapper
    //gbc_load_rom_file(&mmu, "data/tests/oam_bug/rom_singles/4-scanline_timing.gb");

    //gbc_load_rom(&mmu, __01_special_gb, __01_special_gb_len); // PASSED
    //gbc_load_rom(&mmu, __02_interrupts_gb, __02_interrupts_gb_len); // PASSED
    //gbc_load_rom(&mmu, __03_op_sp_hl_gb, __03_op_sp_hl_gb_len); // PASSED
    //gbc_load_rom(&mmu, __04_op_r_imm_gb, __04_op_r_imm_gb_len); // PASSED
    //gbc_load_rom(&mmu, __05_op_rp_gb, __05_op_rp_gb_len); // PASSED
    //gbc_load_rom(&mmu, __06_ld_r_r_gb, __06_ld_r_r_gb_len); // PASSED
    //gbc_load_rom(&mmu, __07_jr_jp_call_ret_rst_gb, __07_jr_jp_call_ret_rst_gb_len); // PASSED
    //gbc_load_rom(&mmu, __08_misc_instrs_gb, __08_misc_instrs_gb_len); // PASSED
    //gbc_load_rom(&mmu, __09_op_r_r_gb, __09_op_r_r_gb_len); // PASSED
    //gbc_load_rom(&mmu, __10_bit_ops_gb, __10_bit_ops_gb_len); // PASSED
    //gbc_load_rom(&mmu, __11_op_a__hl__gb, __11_op_a__hl__gb_len); // PASSED

    //printf("emulator initialized\n");
    gbc_cpu_loop(&cpu);

#if defined(SLOPPY_RENDER)
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
#endif
}

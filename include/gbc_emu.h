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
#include "dmg_rom.h"

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

void emu_run() {
    gbc_cpu cpu;
    gbc_ppu ppu;
    gbc_mmu mmu;

    cpu.mmu = &mmu;
    ppu.mmu = &mmu;

    cpu.ppu = &ppu;

    gbc_mmu_init(&mmu);
    gbc_cpu_reset(&cpu);
    ppu_init(&ppu);
    gbc_cpu_set_boot_state(&cpu);

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
    gbc_mbc mbc;

    mmu.mbc = &mbc;
    cpu.mmu = &mmu;
    ppu.mmu = &mmu;

#if defined(SLOPPY_RENDER)
    ppu.renderer = renderer;
#endif

    cpu.ppu = &ppu;

    gbc_mmu_init(&mmu);
    gbc_cpu_reset(&cpu);

    //memcpy(mmu.bios, DMG_ROM_bin, DMG_ROM_bin_len); mmu.in_bios = true;
    gbc_cpu_set_boot_state(&cpu);
    cpu.mmu->io[0x00] = 0xFF;

    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/ei_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/instr/daa.gb"); // PASSED

    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/oam_dma/basic.gb"); // PASSED
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/oam_dma/reg_read.gb"); // PASSED
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/oam_dma/sources-GS.gb");

    // instr timing tests
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/add_sp_e_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/boot_div-dmgABCmgb.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/boot_div2-S.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/boot_hwio-S.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/boot_hwio-dmg0.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/boot_hwio-dmgABCmgb.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/boot_regs-dmg0.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/boot_regs-dmgABC.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/boot_regs-mgb.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/boot_regs-sgb.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/boot_regs-sgb2.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/call_cc_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/call_cc_timing2.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/call_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/call_timing2.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/di_timing-GS.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/ei_sequence.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/ei_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/halt_ime0_ei.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/halt_ime0_nointr_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/halt_ime1_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/halt_ime1_timing2-GS.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/if_ie_registers.gb"); // PASSED
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/intr_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/jp_cc_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/jp_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/ld_hl_sp_e_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/oam_dma_restart.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/oam_dma_start.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/oam_dma_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/pop_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/push_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/rapid_di_ei.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/ret_cc_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/ret_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/reti_intr_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/reti_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/rst_timing.gb");

    // timer tests
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/div_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/timer/div_write.gb"); // PASSED
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/timer/rapid_toggle.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/timer/tim00.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/timer/tim01.gb"); // PASS
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/timer/tim10.gb"); // PASS
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/timer/tim11.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/timer/tim00_div_trigger.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/timer/tim01_div_trigger.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/timer/tim10_div_trigger.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/timer/tim11_div_trigger.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/timer/tima_reload.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/timer/tima_write_reloading.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/timer/tma_write_reloading.gb");

    // mbc tests
    //gbc_load_rom_file(&mmu, "./data/mbc1/bits_bank1.gb"); // PASSED
    gbc_load_rom_file(&mmu, "./data/mbc1/bits_bank2.gb");
    //gbc_load_rom_file(&mmu, "./data/pokemon_blue_gb.bin");
    //gbc_load_rom_file(&mmu, "./data/mbc1/bits_mode.gb"); // PASSED
    //gbc_load_rom_file(&mmu, "./data/mbc1/bits_ramg.gb");
    //gbc_load_rom_file(&mmu, "./data/mbc1/multicart_rom_8Mb.gb");
    //gbc_load_rom_file(&mmu, "./data/mbc1/ram_64kb.gb");
    //gbc_load_rom_file(&mmu, "./data/mbc1/ram_256kb.gb");

    //gbc_load_rom_file(&mmu, "./data/mbc1/rom_512kb.gb"); // PASSED
    //gbc_load_rom_file(&mmu, "./data/mbc1/rom_1Mb.gb"); // PASSED
    //gbc_load_rom_file(&mmu, "./data/mbc1/rom_2Mb.gb"); // PASSED
    //gbc_load_rom_file(&mmu, "./data/mbc1/rom_4Mb.gb"); // PASSED
    //gbc_load_rom_file(&mmu, "./data/mbc1/rom_8Mb.gb"); // PASSED
    //gbc_load_rom_file(&mmu, "./data/mbc1/rom_16Mb.gb"); // PASSED

    // ppu tests
    //gbc_load_rom_file(&mmu, "data/m2_win_en_toggle.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/ppu/intr_2_mode0_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/ppu/intr_2_mode4_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/ppu/intr_2_oam_ok_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/ppu/intr_2_0_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/ppu/intr_2_mode0_timing.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/ppu/intr_2_mode0_timing_sprites.gb");
    //gbc_load_rom_file(&mmu, "data/mooneye-gb_hwtests/acceptance/ppu/intr_2_mode3_timing.gb");

    // interrupts
    //gbc_load_rom_file(&mmu, "./data/mooneye-gb_hwtests/acceptance/interrupts/ie_push.gb");
    //gbc_load_rom_file(&mmu, "./data/tests/interrupt_time/interrupt_time.gb");

    // mem-timing  - do this before interrupt timing?
    //gbc_load_rom_file(&mmu, "./data/tests/mem_timing/individual/01-read_timing.gb");
    //gbc_load_rom_file(&mmu, "./data/tests/mem_timing/individual/02-write_timing.gb");
    //gbc_load_rom_file(&mmu, "./data/tests/mem_timing/individual/03-modify_timing.gb");

    //gbc_load_rom_file(&mmu, "./DrMario.gb");
    //gbc_load_rom_file(&mmu, "./Tetris.gb");
    //gbc_load_rom_file(&mmu, "DK.gb");
    //gbc_load_rom_file(&mmu, "./MarioLand.gb"); // required mapper
    //gbc_load_rom_file(&mmu, "data/sprite_priority.gb");
    //gbc_load_rom_file(&mmu, "data/tests/instr_timing/instr_timing.gb");
    //gbc_load_rom_file(&mmu, "data/tests/oam_bug/rom_singles/4-scanline_timing.gb");

    // CPU instruction tests
    //gbc_load_rom_file(&mmu, "data/tests/cpu_instrs/cpu_instrs.gb");
    //gbc_load_rom_file(&mmu, "data/tests/oam_bug/oam_bug.gb");
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
    //

    //printf("OPCODE CYCLES (m): \n");
    //for (int i=0; i<0x100; i++) {
        //if ((i % 0x10) == 0) {
            //printf("\n");
        //}
        //execute_op(&cpu, i);
        //printf("%x,", cpu.registers.clk.m);
    //}
    //printf("\n");
    //printf("END OPCODE CYCLES\n");

    //printf("emulator initialized\n");
    gbc_cpu_loop(&cpu);

#if defined(SLOPPY_RENDER)
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
#endif
}

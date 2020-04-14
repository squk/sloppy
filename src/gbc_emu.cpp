#include "gbc_emu.hpp"

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

gbc_emu::gbc_emu() {
    cpu.mmu = &mmu;
    ppu.mmu = &mmu;
    cpu.ppu = &ppu;

#if defined(SLOPPY_RENDER)
    // gui init
#endif

    cpu.reset();
    mmu.init();
    ppu.init();
}

void gbc_emu::run() {
    cpu.set_boot_state();
    cpu.loop();
}

void gbc_emu::test() {
    memcpy(mmu.bios, DMG_ROM_bin, DMG_ROM_bin_len); mmu.in_bios = true;
    //gbc_cpu_set_boot_state(&cpu);
    cpu.mmu->io[0x00] = 0xFF;

    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ei_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/instr/daa.gb"); // PASSED

    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/oam_dma/basic.gb"); // PASSED
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/oam_dma/reg_read.gb"); // PASSED
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/oam_dma/sources-GS.gb");

    // instr timing tests
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/add_sp_e_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/boot_div-dmgABCmgb.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/boot_div2-S.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/boot_hwio-S.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/boot_hwio-dmgABCmgb.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/boot_regs-dmgABC.gb"); // PASS
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/boot_regs-mgb.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/boot_regs-sgb.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/boot_regs-sgb2.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/call_cc_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/call_cc_timing2.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/call_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/call_timing2.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/di_timing-GS.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ei_sequence.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ei_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/halt_ime0_ei.gb"); // PASS
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/halt_ime0_nointr_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/halt_ime1_timing.gb"); // PASS
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/halt_ime1_timing2-GS.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/if_ie_registers.gb"); // PASSED
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/intr_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/jp_cc_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/jp_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ld_hl_sp_e_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/oam_dma_restart.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/oam_dma_start.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/oam_dma_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/pop_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/push_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/rapid_di_ei.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ret_cc_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ret_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/reti_intr_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/reti_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/rst_timing.gb");

    // timer tests
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/div_timing.gb"); // PASS
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/div_write.gb"); // PASS
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/rapid_toggle.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/tim00.gb"); // PASS
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/tim01.gb"); // PASS
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/tim10.gb"); // PASS
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/tim11.gb"); // PASS
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/tim00_div_trigger.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/tim01_div_trigger.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/tim10_div_trigger.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/tim11_div_trigger.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/tima_reload.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/tima_write_reloading.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/timer/tma_write_reloading.gb");

    // mbc tests
    //mmu.load_rom_file("./data/mbc1/bits_bank1.gb"); // PASSED
    //mmu.load_rom_file("./data/mbc1/bits_bank2.gb"); // PASSED
    //mmu.load_rom_file("./data/pokemon_blue_gb.bin");
    //mmu.load_rom_file("./data/mbc1/bits_mode.gb"); // PASSED
    //mmu.load_rom_file("./data/mbc1/bits_ramg.gb"); // PASSED
    //mmu.load_rom_file("./data/mbc1/multicart_rom_8Mb.gb");
    //mmu.load_rom_file("./data/mbc1/ram_64kb.gb");
    //mmu.load_rom_file("./data/mbc1/ram_256kb.gb"); // PASSED

    //mmu.load_rom_file("./data/mbc1/rom_512kb.gb"); // PASSED
    //mmu.load_rom_file("./data/mbc1/rom_1Mb.gb"); // PASSED
    //mmu.load_rom_file("./data/mbc1/rom_2Mb.gb"); // PASSED
    //mmu.load_rom_file("./data/mbc1/rom_4Mb.gb"); // PASSED
    //mmu.load_rom_file("./data/mbc1/rom_8Mb.gb"); // PASSED
    //mmu.load_rom_file("./data/mbc1/rom_16Mb.gb"); // PASSED

    // ppu tests
    //mmu.load_rom_file("data/m2_win_en_toggle.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ppu/intr_2_mode0_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ppu/intr_2_mode4_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ppu/intr_2_oam_ok_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ppu/intr_2_0_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ppu/intr_2_mode0_timing.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ppu/intr_2_mode0_timing_sprites.gb");
    //mmu.load_rom_file("data/mooneye-gb_hwtests/acceptance/ppu/intr_2_mode3_timing.gb");

    // interrupts
    //mmu.load_rom_file("./data/mooneye-gb_hwtests/acceptance/interrupts/ie_push.gb");
    //mmu.load_rom_file("./data/tests/interrupt_time/interrupt_time.gb");

    // mem-timing  - do this before interrupt timing?
    //mmu.load_rom_file("./data/tests/mem_timing/individual/01-read_timing.gb");
    //mmu.load_rom_file("./data/tests/mem_timing/individual/02-write_timing.gb");
    //mmu.load_rom_file("./data/tests/mem_timing/individual/03-modify_timing.gb");

    //mmu.load_rom_file("./DrMario.gb");
    mmu.load_rom_file("./Tetris.gb");
    //mmu.load_rom_file("DK.gb");
    //mmu.load_rom_file("./MarioLand.gb"); // required mapper
    //mmu.load_rom_file("data/sprite_priority.gb");
    //mmu.load_rom_file("data/tests/oam_bug/rom_singles/4-scanline_timing.gb");

    // CPU instruction tests
    //mmu.load_rom_file("data/tests/oam_bug/oam_bug.gb");
    //mmu.load_rom_file("data/tests/cpu_instrs/cpu_instrs.gb");
    //mmu.load_rom_file("data/tests/instr_timing/instr_timing.gb");
    cpu.loop();

#if defined(SLOPPY_RENDER)
    // gui quit
#endif
}

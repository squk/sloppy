#pragma once

#include <gba_base.h>
#include <gba_video.h>
#include <gba_systemcalls.h>

#include <stdio.h>
#include <string.h>

#include "gbc_cpu.h"
#include "gbc_gpu.h"
#include "gbc_mmu.h"
#include "gbc_cpu_test.h"

#include "cpu_instrs_gb_bin.h"
#include "tetris_gb_bin.h"
#include "DMG_ROM_bin.h"

void emu_run() {
    SetMode( MODE_4 | BG3_ON );
    gbc_cpu cpu;
    gbc_gpu gpu;
    gbc_mmu mmu;
    cpu.mmu = &mmu;
    gpu.mmu = &mmu;

    cpu.gpu = &gpu;

    gbc_mmu_init(&mmu);
    //CpuFastSet(tetris_gb_bin, (u8*)mmu.rom, (tetris_gb_bin_size / 4) | COPY32);
    //CpuFastSet(cpu_instrs_gb_bin, (u8*)mmu.rom, (cpu_instrs_gb_bin_size / 4) | COPY32);
    //memcpy(mmu.rom, cpu_instrs_gb_bin, cpu_instrs_gb_bin_size);
    memcpy(mmu.rom, DMG_ROM_bin, DMG_ROM_bin_size);
    gbc_cpu_reset(&cpu);
    gbc_cpu_set_boot_state(&cpu);

    gbc_cpu_loop(&cpu);
}

void emu_test() {
    SetMode( MODE_0 | BG0_ON );
    gbc_cpu cpu;
    gbc_gpu gpu;
    gbc_mmu mmu;
    cpu.mmu = &mmu;
    gpu.mmu = &mmu;

    cpu.gpu = &gpu;

    gbc_mmu_init(&mmu);
    gbc_cpu_reset(&cpu);

    test_gbc_cpu_loop(&cpu);
}

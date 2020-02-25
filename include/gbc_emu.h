#pragma once
#include <gba_base.h>
#include <gba_video.h>
#include <gba_systemcalls.h>

#include <stdio.h>
#include <string.h>
#include "gbc_cpu.h"
#include "gbc_gpu.h"
#include "gbc_mmu.h"
#include "cpu_instrs_gb_bin.h"

void emu_run() {
    gbc_cpu cpu;
    gbc_gpu gpu;
    gbc_mmu mmu;
	//CpuFastSet(cpu_instrs_gb_bin, (u8*)mmu.rom0, (cpu_instrs_gb_bin_size / 4) | COPY32);
    //memcpy(mmu.rom0, cpu_instrs_gb_bin, cpu_instrs_gb_bin_size);
    memcpy(mmu.rom, kInitialValuesForFFXX, 256);
    cpu.mmu = &mmu;
    gpu.mmu = &mmu;

    cpu.gpu = &gpu;

    gbc_mmu_init(&mmu);
    gbc_cpu_reset(&cpu);

    gbc_cpu_loop(&cpu);
}

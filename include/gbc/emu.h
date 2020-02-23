#pragma once

#include "gbc/cpu.h"
#include "gbc/mmu.h"

void emu_run() {
    gbc_cpu cpu;
    gbc_mmu mmu;
    cpu.mmu = &mmu;

    gbc_mmu_init(&mmu);
    gbc_cpu_reset(&cpu);
    gbc_cpu_loop(&cpu);
}

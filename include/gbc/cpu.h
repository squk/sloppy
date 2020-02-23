#pragma once
#include "gbc/mmu.h"

typedef struct {
    // two types of timeclocks in the Z80
    int m;
    int t;
} gbc_clock;

/*
 * 16bit Hi   Lo   Name/Function
 * AF    A    -    Accumulator & Flags
 * BC    B    C    BC
 * DE    D    E    DE
 * HL    H    L    HL
 * SP    -    -    Stack Pointer
 * PC    -    -    Program Counter/Pointer
 * As shown above, most registers can be accessed either as one 16bit
 * register, or as two separate 8bit registers.
 */
typedef struct {
    u16 pc, sp;
    u8 a, b, c, d, e, h, l, f; // 8-bit registers
    //u8 t, m; // Clock for last instruction
    gbc_clock clk;
} gbc_cpu_registers;

// save register set
typedef struct {
    u8 a, b, c, d, e, h, l, f;
} gbc_cpu_rsv;

typedef struct {
    gbc_clock clk;
    gbc_cpu_registers registers;
    gbc_cpu_rsv rsv;

    gbc_mmu *mmu;
} gbc_cpu;

void gbc_cpu_reset(gbc_cpu *cpu);
void gbc_cpu_loop(gbc_cpu *cpu);

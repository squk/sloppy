#pragma once
#include "gbc/memory.h"

typedef struct {
	// two types of timeclocks in the Z80
	struct {
		int m;
		int t;
	} clock;

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
	struct {
		u16 pc, sp;
		u8 a, b, c, d, e, h, l, f;    // 8-bit registers
		//u8 m, t;                      // Clock for last instruction
	    clock c
	} registers;

	struct {
		u8 a, b, c, d, e, h, l, f;
	} rsv; // saved register set

	gmc_mmu* mmu;

} gba_cpu;

void gbc_cpu_reset(gbc_cpu *cpu);
void gbc_cpu_loop(gbc_cpu *cpu);

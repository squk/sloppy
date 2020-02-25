#include <stdio.h>
#include <gba_systemcalls.h>

#include "gbc_cpu.h"
#include "gbc_ops.h"
#include "gbc_io.h"
#include "text.h"
#include "console.h"

void gbc_cpu_reset(gbc_cpu *cpu) {
    cpu->registers.a = 0;
    cpu->registers.b = 0;
    cpu->registers.c = 0;
    cpu->registers.d = 0;
    cpu->registers.e = 0;
    cpu->registers.h = 0;
    cpu->registers.l = 0;
    cpu->registers.f = 0;

    cpu->registers.pc = 0;
    cpu->registers.sp = 0;
    cpu->registers.clk.m = 0;
    cpu->registers.clk.t = 0;

    cpu->clk.m = 0;
    cpu->clk.t = 0;
}

void gbc_cpu_set_boot_state(gbc_cpu *cpu) {
    cpu->registers.pc = 0x100;
    cpu->registers.a = 0x01;
    cpu->registers.f = 0xB0;
    cpu->registers.b = 0x00;
    cpu->registers.c = 0x13;
    cpu->registers.d = 0x00;
    cpu->registers.e = 0xD8;
    cpu->registers.h = 0x01;
    cpu->registers.l = 0x4D;
    cpu->registers.sp = 0xFFFE;

    cpu->mmu->in_bios = false;
}

void gbc_registers_debug(gbc_cpu *cpu, u8 opcode, int instr) {
    char s[80];
    cli_clear();
    sprintf(s, "i: %d   OP: %x", instr, opcode);
    cli_printl(s);
    sprintf(s, "A: %x    B: %x    C: %x", cpu->registers.a, cpu->registers.b, cpu->registers.c);
    cli_printl(s);
    sprintf(s, "D: %x    E: %x    F: %x", cpu->registers.d, cpu->registers.e, cpu->registers.f);
    cli_printl(s);
    sprintf(s, "H: %x    L: %x    M: %x", cpu->registers.h, cpu->registers.e, cpu->registers.clk.m);
    cli_printl(s);
    sprintf(s, "T: %x    SP: %x    PC: %x", cpu->registers.clk.t, cpu->registers.sp, cpu->registers.pc);
    cli_printl(s);
    sprintf(s, "ROM: %x     fb[0]: %x", &cpu->mmu->rom, cpu->gpu->fb[0]);
    cli_printl(s);
    sprintf(s, "LCDCONT: %x", read_u8(cpu->mmu, IO_LCDCONT));
    cli_printl(s);
}

void gbc_cpu_loop(gbc_cpu *cpu) {
    execute_init(cpu);

    char s[80];
    int max = 100;
    int instr = 0;

    gbc_registers_debug(cpu, -1, instr);
    while(1) {
        instr++;
        // Fetch and execute instruction
        u8 opcode = read_u8(cpu->mmu, cpu->registers.pc++);
        void (*funcPtr)(gbc_cpu*) = *OPS[opcode];
        (funcPtr)(cpu);
        if (instr % 500 == 0 || (instr > 2000 && instr % 50 == 0)) {
            gbc_registers_debug(cpu, opcode, instr);
        }

        /*put_c(screen_line-1, 5, 'E');*/

        // Add execution time to the CPU clk
        cpu->clk.m += cpu->registers.clk.m;
        cpu->clk.t += cpu->registers.clk.t;
        gpu_start_frame(cpu->gpu);
    }
}


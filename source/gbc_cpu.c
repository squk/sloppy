#include <stdio.h>
#include <gba_systemcalls.h>

#include "gbc_cpu.h"
#include "gbc_ops.h"
#include "text.h"

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

void gbc_cpu_loop(gbc_cpu *cpu) {
    execute_init(cpu);

    char s[80];
    int max = 5;
    int instr = 0;
    while(1) {
        instr++;
        put_l(s);
        // Fetch and execute instruction
        u8 opcode = read_u8(cpu->mmu, cpu->registers.pc++);
        void (*funcPtr)(gbc_cpu*) = *OPS[opcode];
        (funcPtr)(cpu);

        if (instr % 10000 == 0) {
            clear();
            sprintf(s, "I#:%d     PC: %d", instr, cpu->registers.pc);
            sprintf(s, "OP: %x", opcode);
            put_l(s);
            sprintf(s, "A: %x    B: %x    C: %x", cpu->registers.a, cpu->registers.b, cpu->registers.c);
            put_l(s);
            sprintf(s, "D: %x    E: %x    F: %x", cpu->registers.d, cpu->registers.e, cpu->registers.f);
            put_l(s);
            sprintf(s, "H: %x    L: %x    M: %x", cpu->registers.h, cpu->registers.e, cpu->registers.clk.m);
            put_l(s);
            sprintf(s, "T: %x    SP: %x    PC: %x", cpu->registers.clk.t, cpu->registers.sp, cpu->registers.pc);
            put_l(s);
        }

        /*put_c(screen_line-1, 5, 'E');*/

        // Add execution time to the CPU clk
        cpu->clk.m += cpu->registers.clk.m;
        cpu->clk.t += cpu->registers.clk.t;
        /*VBlankIntrWait();*/
    }
}

#include "gbc/cpu.h"
#include "gbc/ops.h"

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

    u8 i = 0;
    while(true) {
        // Fetch and execute instruction
        u8 opcode = read_u8(cpu->mmu, cpu->registers.pc++);
        OPS[opcode](cpu);
        /*char s[80];*/
        /*sprintf(s, "%x", opcode);*/
        /*put_s(i++, s);*/
        /*if (i > 12) {*/
            /*i = 0;*/
        /*}*/

        // Add execution time to the CPU clk
        cpu->clk.m += cpu->registers.clk.m;
        cpu->clk.t += cpu->registers.clk.t;
    }
}

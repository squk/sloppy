#pragma once

#include "gbc_cpu.h"
#include "gbc_gpu.h"
#include "gbc_mmu.h"
#include "gbc_ops.h"
#include "gbc_io.h"

u8 testbytes[] = {

};

void test_gbc_cpu_loop(gbc_cpu *cpu) {
    char s[80];
    int max = 100;
    int instr = 0;

    while(1) {
        instr++;
        // Fetch and execute instruction
        u8 opcode = read_u8(cpu->mmu, cpu->registers.pc++);
        for(u8 i=0; i<60; i++) {VBlankIntrWait();}
        void (*funcPtr)(gbc_cpu*) = *OPS[opcode];
        void (*debugFuncPtr)(gbc_cpu*) = *DEBUG_OPS[opcode];
        (funcPtr)(cpu);
        (debugFuncPtr)(cpu);
        //if (instr % 100 == 0) {
            clear();
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
            sprintf(s, "ROM: %x", &cpu->mmu->rom);
            put_l(s);
            sprintf(s, "LCDCONT: %x", read_u8(cpu->mmu, IO_LCDCONT));
            put_l(s);
        //}

        /*put_c(screen_line-1, 5, 'E');*/

        // Add execution time to the CPU clk
        cpu->clk.m += cpu->registers.clk.m;
        cpu->clk.t += cpu->registers.clk.t;
        gpu_start_frame(cpu->gpu);
    }
}

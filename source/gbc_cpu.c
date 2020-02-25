#include <stdio.h>
#include <gba_systemcalls.h>

#include "gbc_cpu.h"
#include "gbc_ops.h"
#include "gbc_io.h"
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

void gbc_cpu_loop(gbc_cpu *cpu) {
    execute_init(cpu);

    char s[80];
    int max = 100;
    int instr = 0;
    /*sprintf(s, "LCDCONT: %x", get_address_ptr(cpu->mmu, IO_LCDCONT));*/
    /*put_l(s);*/
    /*sprintf(s, "ROM: %x", &cpu->mmu->rom);*/
    /*put_l(s);*/

    while(1) {
        instr++;
        // Fetch and execute instruction
        u8 opcode = read_u8(cpu->mmu, cpu->registers.pc++);
        for(u8 i=0; i<60; i++) {VBlankIntrWait();}
        void (*funcPtr)(gbc_cpu*) = *OPS[opcode];
        (funcPtr)(cpu);

        /*if (instr % 101 == 0) {*/
            sprintf(s, "op: %x    &fb:%x    fb: %x", opcode, &cpu->gpu->fb, cpu->gpu->fb[0]);
            put_l(s);
        /*}*/

        /*if (instr % 100 == 0) {*/
            /*clear();*/
            /*sprintf(s, "OP: %x", opcode);*/
            /*put_l(s);*/
            /*sprintf(s, "A: %x    B: %x    C: %x", cpu->registers.a, cpu->registers.b, cpu->registers.c);*/
            /*put_l(s);*/
            /*sprintf(s, "D: %x    E: %x    F: %x", cpu->registers.d, cpu->registers.e, cpu->registers.f);*/
            /*put_l(s);*/
            /*sprintf(s, "H: %x    L: %x    M: %x", cpu->registers.h, cpu->registers.e, cpu->registers.clk.m);*/
            /*put_l(s);*/
            /*sprintf(s, "T: %x    SP: %x    PC: %x", cpu->registers.clk.t, cpu->registers.sp, cpu->registers.pc);*/
            /*put_l(s);*/
            /*sprintf(s, "ROM: %x", &cpu->mmu->rom);*/
            /*put_l(s);*/
            /*sprintf(s, "LCDCONT: %x", read_u8(cpu->mmu, IO_LCDCONT));*/
            /*put_l(s);*/
        /*}*/

        /*put_c(screen_line-1, 5, 'E');*/

        // Add execution time to the CPU clk
        cpu->clk.m += cpu->registers.clk.m;
        cpu->clk.t += cpu->registers.clk.t;
        gpu_start_frame(cpu->gpu);
    }
}

#include <stdio.h>
#include <gba.h>

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

    write_u8(cpu->mmu, 0xFF05, 0x00);
	write_u8(cpu->mmu, 0xFF06, 0x00);
	write_u8(cpu->mmu, 0xFF07, 0x00);
	write_u8(cpu->mmu, 0xFF10, 0x80);
	write_u8(cpu->mmu, 0xFF11, 0xBF);
	write_u8(cpu->mmu, 0xFF12, 0xF3);
	write_u8(cpu->mmu, 0xFF14, 0xBF);
	write_u8(cpu->mmu, 0xFF16, 0x3F);
	write_u8(cpu->mmu, 0xFF17, 0x00);
	write_u8(cpu->mmu, 0xFF19, 0xBF);
	write_u8(cpu->mmu, 0xFF1A, 0x7F);
	write_u8(cpu->mmu, 0xFF1B, 0xFF);
	write_u8(cpu->mmu, 0xFF1C, 0x9F);
	write_u8(cpu->mmu, 0xFF1E, 0xBF);
	write_u8(cpu->mmu, 0xFF20, 0xFF);
	write_u8(cpu->mmu, 0xFF21, 0x00);
	write_u8(cpu->mmu, 0xFF22, 0x00);
	write_u8(cpu->mmu, 0xFF23, 0xBF);
	write_u8(cpu->mmu, 0xFF24, 0x77);
	write_u8(cpu->mmu, 0xFF25, 0xF3);
	write_u8(cpu->mmu, 0xFF26, 0xF1);
	write_u8(cpu->mmu, 0xFF40, 0x91);
	write_u8(cpu->mmu, 0xFF42, 0x00);
	write_u8(cpu->mmu, 0xFF43, 0x00);
	write_u8(cpu->mmu, 0xFF45, 0x00);
	write_u8(cpu->mmu, 0xFF47, 0xFC);
	write_u8(cpu->mmu, 0xFF48, 0xFF);
	write_u8(cpu->mmu, 0xFF49, 0xFF);
	write_u8(cpu->mmu, 0xFF4A, 0x00);
	write_u8(cpu->mmu, 0xFF4B, 0x00);
	write_u8(cpu->mmu, 0xFFFF, 0x00);    

    cpu->mmu->in_bios = false;
}

void gbc_registers_debug(gbc_cpu *cpu, u8 opcode, int instr) {
    char s[80];
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
    sprintf(s, "ROM: %x     fb[]: %x", &cpu->mmu->rom, cpu->gpu->fb[SIZE_X/2]);
    cli_printl(s);
    /*sprintf(s, "LCDCONT: %x", read_u8(cpu->mmu, IO_LCDCONT));*/
    /*cli_printl(s);*/
    sprintf(s, "$FF00+$47: %x", read_u8(cpu->mmu, 0xFF00+0x47));
    cli_printl(s);
}

void gbc_cpu_loop(gbc_cpu *cpu) {
    execute_init(cpu);
    gpu_start_frame(cpu->gpu);

    char s[80];
    int max = 100;
    int instr = 0;

    gbc_registers_debug(cpu, -1, instr);
    //SetMode(MODE_3 | BG2_ON); for(u8 y=0; y<160; y++) { for(u8 x=0; x<240; x++) { MODE3_FB[y][x] = RGB8(40, 40, 40); } }
    while(1) {
        instr++;
        // Fetch and execute instruction
        u8 opcode = read_u8(cpu->mmu, cpu->registers.pc++);
        void (*funcPtr)(gbc_cpu*) = *OPS[opcode];
        (funcPtr)(cpu);

        //gbc_registers_debug(cpu, opcode, instr);

        //if (DivMod(instr, 500) == 0) {
        //}
        if (cpu->gpu->fb[0] != 0) {
            sprintf(s, "%d: fb[]: %x", instr, cpu->gpu->fb[0]);
            cli_printl(s);
        }

        // Add execution time to the CPU clk
        cpu->clk.m += cpu->registers.clk.m;
        cpu->clk.t += cpu->registers.clk.t;
        gpu_run(cpu->gpu, cpu->registers.clk.m);
        //for(u8 i=0; i<80; i++) { VBlankIntrWait(); }
    }
}


#include "gbc/cpu.h"
#include "gbc/mmu.h"
#include "gbc/ops.h"

#include "font.h"
#include "text.h"
#include "cpu.h"

#define BIT_RANGE(x, lsb, msb) (x >> lsb) & ~(~0 << (msb-lsb+1))

void gbc_cpu_reset(gbc_cpu *cpu) {
    cpu.registers.a = 0;
    cpu.registers.b = 0;
    cpu.registers.c = 0;
    cpu.registers.d = 0;
    cpu.registers.e = 0;
    cpu.registers.h = 0;
    cpu.registers.l = 0;
    cpu.registers.f = 0;

    cpu.registers.pc = 0;
    cpu.registers.sp = 0;
    cpu.registers.clk.m = 0;
    cpu.registers.clk.t = 0;

    cpu.clk.m = 0;
    cpu.clk.t = 0;
}

void gbc_cpu_loop(gbc_cpu *cpu) {
    execute_init(cpu);

    u8 i = 0;
    while(true) {
        // Fetch and execute instruction
        u8 opcode = read_u8(cpu->mmu, cpu->registers.pc++);
        OPS[opcode](cpu);
        char s[80];
        sprintf(s, "%x", opcode);
        put_s(i++, s);
        if (i > 12) {
            i = 0;
        }

        // Add execution time to the CPU clk
        cpu->clk.m += cpu->registers.m;
        cpu->clk.t += cpu->registers.t;
    }
}

// x = the opcode's 1st octal digit (i.e. bits 7-6)
// y = the opcode's 2nd octal digit (i.e. bits 5-3)
// z = the opcode's 3rd octal digit (i.e. bits 2-0)
// p = y rightshifted one position (i.e. bits 5-4)
// q = y modulo 2 (i.e. bit 3)
// implementation of the decode strategy descrubed here:
// https://gb-archive.github.io/salvage/decoding_gbz80_opcodes/Decoding%20Gamboy%20Z80%20Opcodes.html
void execute_smart(gbc_cpu *cpu, u8 opcode) {
    x = BIT_RANGE(opcode, 6, 7);
    y = BIT_RANGE(opcode, 3, 5);
    z = BIT_RANGE(opcode, 0, 2);
    p = BIT_RANGE(opcode, 4, 5);
    q - y % 3;

    switch (x) {
        case 0:
            switch (z) {
                case 0: relative_jumps_and_assorted_ops(y)
                case 1: (y)
            }
            break;
    }
}

void relative_jumps_and_assorted_ops(u8 y) {

}

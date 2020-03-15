#include <stdio.h>
#include "gbc_ops.h"

#define min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define half_carry(a, b)  (((a & 0xF) + (b & 0xF)) & 0x10) == 0x10

/*
 * d8  means immediate 8 bit data
 * d16 means immediate 16 bit data
 * a8  means 8 bit unsigned data, which are added to $FF00 in certain instructions (replacement for missing IN and OUT instructions)
 * a16 means 16 bit address
 * r8  means 8 bit signed data, which are added to program counter
 * https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
 */

// load n into register (n = 8-bit immediate value)
// checked
void LD_A_d8(gbc_cpu *cpu) {
    cpu->registers.a = read_u8(cpu->mmu, cpu->registers.pc);
    cpu->registers.pc++;
    cpu->registers.clk.m = 2;
}
void LD_B_d8(gbc_cpu *cpu) {
    cpu->registers.b = read_u8(cpu->mmu, cpu->registers.pc);
    cpu->registers.pc++;
    cpu->registers.clk.m = 2;
}
void LD_C_d8(gbc_cpu *cpu) {
    cpu->registers.c = read_u8(cpu->mmu, cpu->registers.pc);
    cpu->registers.pc++;
    cpu->registers.clk.m = 2;
}
void LD_D_d8(gbc_cpu *cpu) {
    cpu->registers.d = read_u8(cpu->mmu, cpu->registers.pc);
    cpu->registers.pc++;
    cpu->registers.clk.m = 2;
}
void LD_E_d8(gbc_cpu *cpu) {
    cpu->registers.e = read_u8(cpu->mmu, cpu->registers.pc);
    cpu->registers.pc++;
    cpu->registers.clk.m = 2;
}
void LD_H_d8(gbc_cpu *cpu) {
    cpu->registers.h = read_u8(cpu->mmu, cpu->registers.pc);
    cpu->registers.pc++;
    cpu->registers.clk.m = 2;
}
void LD_L_d8(gbc_cpu *cpu) {
    cpu->registers.l = read_u8(cpu->mmu, cpu->registers.pc);
    cpu->registers.pc++;
    cpu->registers.clk.m = 2;
}

// LD r1, r2 funcs
void LD_A_A(gbc_cpu *cpu) {
    cpu->registers.a = cpu->registers.a;
    cpu->registers.clk.m = 1;
}
void LD_A_B(gbc_cpu *cpu) {
    cpu->registers.a = cpu->registers.b;
    cpu->registers.clk.m = 1;
}
void LD_A_C(gbc_cpu *cpu) {
    cpu->registers.a = cpu->registers.c;
    cpu->registers.clk.m = 1;
}
void LD_A_D(gbc_cpu *cpu) {
    cpu->registers.a = cpu->registers.d;
    cpu->registers.clk.m = 1;
}
void LD_A_E(gbc_cpu *cpu) {
    cpu->registers.a = cpu->registers.e;
    cpu->registers.clk.m = 1;
}
void LD_A_H(gbc_cpu *cpu) {
    cpu->registers.a = cpu->registers.h;
    cpu->registers.clk.m = 1;
}
void LD_A_L(gbc_cpu *cpu) {
    cpu->registers.a = cpu->registers.l;
    cpu->registers.clk.m = 1;
}

void LD_B_A(gbc_cpu *cpu) {
    cpu->registers.b = cpu->registers.a;
    cpu->registers.clk.m = 1;
}
void LD_B_B(gbc_cpu *cpu) {
    cpu->registers.b = cpu->registers.b;
    cpu->registers.clk.m = 1;
}
void LD_B_C(gbc_cpu *cpu) {
    cpu->registers.b = cpu->registers.c;
    cpu->registers.clk.m = 1;
}
void LD_B_D(gbc_cpu *cpu) {
    cpu->registers.b = cpu->registers.d;
    cpu->registers.clk.m = 1;
}
void LD_B_E(gbc_cpu *cpu) {
    cpu->registers.b = cpu->registers.e;
    cpu->registers.clk.m = 1;
}
void LD_B_H(gbc_cpu *cpu) {
    cpu->registers.b = cpu->registers.h;
    cpu->registers.clk.m = 1;
}
void LD_B_L(gbc_cpu *cpu) {
    cpu->registers.b = cpu->registers.l;
    cpu->registers.clk.m = 1;
}

void LD_C_A(gbc_cpu *cpu) {
    cpu->registers.c = cpu->registers.a;
    cpu->registers.clk.m = 1;
}
void LD_C_B(gbc_cpu *cpu) {
    cpu->registers.c = cpu->registers.b;
    cpu->registers.clk.m = 1;
}
void LD_C_C(gbc_cpu *cpu) {
    cpu->registers.c = cpu->registers.c;
    cpu->registers.clk.m = 1;
}
void LD_C_D(gbc_cpu *cpu) {
    cpu->registers.c = cpu->registers.d;
    cpu->registers.clk.m = 1;
}
void LD_C_E(gbc_cpu *cpu) {
    cpu->registers.c = cpu->registers.e;
    cpu->registers.clk.m = 1;
}
void LD_C_H(gbc_cpu *cpu) {
    cpu->registers.c = cpu->registers.h;
    cpu->registers.clk.m = 1;
}
void LD_C_L(gbc_cpu *cpu) {
    cpu->registers.c = cpu->registers.l;
    cpu->registers.clk.m = 1;
}

void LD_D_A(gbc_cpu *cpu) {
    cpu->registers.d = cpu->registers.a;
    cpu->registers.clk.m = 1;
}
void LD_D_B(gbc_cpu *cpu) {
    cpu->registers.d = cpu->registers.b;
    cpu->registers.clk.m = 1;
}
void LD_D_C(gbc_cpu *cpu) {
    cpu->registers.d = cpu->registers.c;
    cpu->registers.clk.m = 1;
}
void LD_D_D(gbc_cpu *cpu) {
    cpu->registers.d = cpu->registers.d;
    cpu->registers.clk.m = 1;
}
void LD_D_E(gbc_cpu *cpu) {
    cpu->registers.d = cpu->registers.e;
    cpu->registers.clk.m = 1;
}
void LD_D_H(gbc_cpu *cpu) {
    cpu->registers.d = cpu->registers.h;
    cpu->registers.clk.m = 1;
}
void LD_D_L(gbc_cpu *cpu) {
    cpu->registers.d = cpu->registers.l;
    cpu->registers.clk.m = 1;
}

void LD_E_A(gbc_cpu *cpu) {
    cpu->registers.e = cpu->registers.a;
    cpu->registers.clk.m = 1;
}
void LD_E_B(gbc_cpu *cpu) {
    cpu->registers.e = cpu->registers.b;
    cpu->registers.clk.m = 1;
}
void LD_E_C(gbc_cpu *cpu) {
    cpu->registers.e = cpu->registers.c;
    cpu->registers.clk.m = 1;
}
void LD_E_D(gbc_cpu *cpu) {
    cpu->registers.e = cpu->registers.d;
    cpu->registers.clk.m = 1;
}
void LD_E_E(gbc_cpu *cpu) {
    cpu->registers.e = cpu->registers.e;
    cpu->registers.clk.m = 1;
}
void LD_E_H(gbc_cpu *cpu) {
    cpu->registers.e = cpu->registers.h;
    cpu->registers.clk.m = 1;
}
void LD_E_L(gbc_cpu *cpu) {
    cpu->registers.e = cpu->registers.l;
    cpu->registers.clk.m = 1;
}

void LD_H_A(gbc_cpu *cpu) {
    cpu->registers.h = cpu->registers.a;
    cpu->registers.clk.m = 1;
}
void LD_H_B(gbc_cpu *cpu) {
    cpu->registers.h = cpu->registers.b;
    cpu->registers.clk.m = 1;
}
void LD_H_C(gbc_cpu *cpu) {
    cpu->registers.h = cpu->registers.c;
    cpu->registers.clk.m = 1;
}
void LD_H_D(gbc_cpu *cpu) {
    cpu->registers.h = cpu->registers.d;
    cpu->registers.clk.m = 1;
}
void LD_H_E(gbc_cpu *cpu) {
    cpu->registers.h = cpu->registers.e;
    cpu->registers.clk.m = 1;
}
void LD_H_H(gbc_cpu *cpu) {
    cpu->registers.h = cpu->registers.h;
    cpu->registers.clk.m = 1;
}
void LD_H_L(gbc_cpu *cpu) {
    cpu->registers.h = cpu->registers.l;
    cpu->registers.clk.m = 1;
}

void LD_L_A(gbc_cpu *cpu) {
    cpu->registers.l = cpu->registers.a;
    cpu->registers.clk.m = 1;
}
void LD_L_B(gbc_cpu *cpu) {
    cpu->registers.l = cpu->registers.b;
    cpu->registers.clk.m = 1;
}
void LD_L_C(gbc_cpu *cpu) {
    cpu->registers.l = cpu->registers.c;
    cpu->registers.clk.m = 1;
}
void LD_L_D(gbc_cpu *cpu) {
    cpu->registers.l = cpu->registers.d;
    cpu->registers.clk.m = 1;
}
void LD_L_E(gbc_cpu *cpu) {
    cpu->registers.l = cpu->registers.e;
    cpu->registers.clk.m = 1;
}
void LD_L_H(gbc_cpu *cpu) {
    cpu->registers.l = cpu->registers.h;
    cpu->registers.clk.m = 1;
}
void LD_L_L(gbc_cpu *cpu) {
    cpu->registers.l = cpu->registers.l;
    cpu->registers.clk.m = 1;
}

// load memory value at address HL into register
void LD_A_mHL(gbc_cpu *cpu) {
    cpu->registers.a = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    cpu->registers.clk.m = 2;
}
void LD_B_mHL(gbc_cpu *cpu) {
    cpu->registers.b = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    cpu->registers.clk.m = 2;
}
void LD_C_mHL(gbc_cpu *cpu) {
    cpu->registers.c = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    cpu->registers.clk.m = 2;
}
void LD_D_mHL(gbc_cpu *cpu) {
    cpu->registers.d = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    cpu->registers.clk.m = 2;
}
void LD_E_mHL(gbc_cpu *cpu) {
    cpu->registers.e = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    cpu->registers.clk.m = 2;
}
void LD_H_mHL(gbc_cpu *cpu) {
    cpu->registers.h = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    cpu->registers.clk.m = 2;
}
void LD_L_mHL(gbc_cpu *cpu) {
    cpu->registers.l = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    cpu->registers.clk.m = 2;
}

// load register value into memory at address HL
void LD_mHL_A(gbc_cpu *cpu) {
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,cpu->registers.a);
    cpu->registers.clk.m = 2;
}
void LD_mHL_B(gbc_cpu *cpu) {
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,cpu->registers.b);
    cpu->registers.clk.m = 2;
}
void LD_mHL_C(gbc_cpu *cpu) {
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,cpu->registers.c);
    cpu->registers.clk.m = 2;
}
void LD_mHL_D(gbc_cpu *cpu) {
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,cpu->registers.d);
    cpu->registers.clk.m = 2;
}
void LD_mHL_E(gbc_cpu *cpu) {
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,cpu->registers.e);
    cpu->registers.clk.m = 2;
}
void LD_mHL_H(gbc_cpu *cpu) {
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,cpu->registers.h);
    cpu->registers.clk.m = 2;
}
void LD_mBC_A(gbc_cpu *cpu) {
    write_u8(cpu->mmu,(cpu->registers.b<<8)+cpu->registers.c, cpu->registers.a);
    cpu->registers.clk.m = 2;
}
void LD_mDE_A(gbc_cpu *cpu) {
    write_u8(cpu->mmu,(cpu->registers.d<<8)+cpu->registers.e, cpu->registers.a);
    cpu->registers.clk.m = 2;
}
void LD_mHL_L(gbc_cpu *cpu) {
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,cpu->registers.l);
    cpu->registers.clk.m = 2;
}
void LD_mHLI_A(gbc_cpu *cpu) {
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l, cpu->registers.a);
    cpu->registers.l=(cpu->registers.l+1)&255;
    if(!cpu->registers.l) cpu->registers.h=(cpu->registers.h+1)&255;
    cpu->registers.clk.m = 2;
}
void LD_mC_A(gbc_cpu *cpu) {
    write_u8(cpu->mmu,0xFF00+cpu->registers.c,cpu->registers.a);
    cpu->registers.clk.m = 2;
}

void LD_mHLD_A(gbc_cpu *cpu) {
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l, cpu->registers.a);
    cpu->registers.l=(cpu->registers.l-1)&255;
    if(cpu->registers.l==255) cpu->registers.h=(cpu->registers.h-1)&255;
    cpu->registers.clk.m = 2;
}

void LD_HL_d8(gbc_cpu *cpu) {
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l, read_u8(cpu->mmu, cpu->registers.pc));
    cpu->registers.pc++;
    cpu->registers.clk.m = 3;
}


/*void LD_d16_A(gbc_cpu *cpu) {
  write_u8(cpu->mmu, read_u16(cpu->mmu, cpu->registers.pc), cpu->registers.a);
  cpu->registers.pc += 2;
 cpu->registers.clk.m = 4;
 }*/
/*void LD_A_d16(gbc_cpu *cpu) {
 cpu->registers.a = read_u8(cpu->mmu, read_u16(cpu->mmu, cpu->registers.pc));
 cpu->registers.pc += 2;
 cpu->registers.clk.m = 4;
 }*/

void LD_A_mBC(gbc_cpu *cpu) {
    cpu->registers.a = read_u8(cpu->mmu,(cpu->registers.b<<8)+cpu->registers.c);
    cpu->registers.clk.m = 2;
}
void LD_A_mDE(gbc_cpu *cpu) {
    cpu->registers.a = read_u8(cpu->mmu,(cpu->registers.d<<8)+cpu->registers.e);
    cpu->registers.clk.m = 2;
}

void LD_A_a16(gbc_cpu *cpu) {
    u16 addr = read_u8(cpu->mmu, cpu->registers.pc++);
    addr |= read_u8(cpu->mmu, cpu->registers.pc++) << 8;
    cpu->registers.a = read_u8(cpu->mmu, addr);
    cpu->registers.clk.m = 4;
}

void LD_a16_A(gbc_cpu *cpu) {
    u16 addr = read_u8(cpu->mmu, cpu->registers.pc++);
    addr |= read_u8(cpu->mmu, cpu->registers.pc++) << 8;
    write_u8(cpu->mmu, addr, cpu->registers.a);
}
void LD_a16_SP(gbc_cpu *cpu) {
    u16 temp = read_u8(cpu->mmu, cpu->registers.pc++);
    temp |= read_u8(cpu->mmu, cpu->registers.pc++) << 8;
    write_u8(cpu->mmu, temp++, cpu->registers.sp & 0xFF);
    write_u8(cpu->mmu, temp, cpu->registers.sp >> 8);
    /*write_u8(cpu->mmu,read_u16(cpu->mmu,cpu->registers.pc), cpu->registers.sp);
    */
    cpu->registers.clk.m = 5;
}

void LD_BC_d16(gbc_cpu *cpu) {
    cpu->registers.c = read_u8(cpu->mmu, cpu->registers.pc++);
    cpu->registers.b = read_u8(cpu->mmu, cpu->registers.pc++);
    cpu->registers.clk.m = 3;
}
void LD_DE_d16(gbc_cpu *cpu) {
    cpu->registers.e = read_u8(cpu->mmu, cpu->registers.pc++);
    cpu->registers.d = read_u8(cpu->mmu, cpu->registers.pc++);
    cpu->registers.clk.m = 3;
}
void LD_HL_d16(gbc_cpu *cpu) {
    cpu->registers.l = read_u8(cpu->mmu, cpu->registers.pc++);
    cpu->registers.h = read_u8(cpu->mmu, cpu->registers.pc++);
    cpu->registers.clk.m = 3;
}

void LD_SP_d16(gbc_cpu *cpu) {
    cpu->registers.sp = read_u16(cpu->mmu, cpu->registers.pc);
    cpu->registers.pc += 2;
    cpu->registers.clk.m = 3;
}

void LD_A_mHLI(gbc_cpu *cpu) {
    cpu->registers.a = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    cpu->registers.l=(cpu->registers.l+1)&255;
    if(!cpu->registers.l) cpu->registers.h=(cpu->registers.h+1)&255;
    cpu->registers.clk.m = 2;
}

void LD_A_mHLD(gbc_cpu *cpu) {
    cpu->registers.a = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    cpu->registers.l=(cpu->registers.l-1)&255;
    if(cpu->registers.l==255) cpu->registers.h=(cpu->registers.h-1)&255;
    cpu->registers.clk.m = 2;
}

void LDH_a8_A(gbc_cpu *cpu) {
    write_u8(cpu->mmu, 0xFF00 + read_u8(cpu->mmu, cpu->registers.pc++), cpu->registers.a);
    cpu->registers.clk.m = 3;
}
void LDH_A_a8(gbc_cpu *cpu) {
    cpu->registers.a = read_u8(cpu->mmu, 0xFF00 + read_u8(cpu->mmu, cpu->registers.pc++));
    cpu->registers.clk.m = 3;
}
void LD_HL_SP_r8(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,cpu->registers.pc);
    if(i>127) i=-((~i+1)&255);
    cpu->registers.pc++;
    i+=cpu->registers.sp;
    cpu->registers.h=(i>>8)&255;
    cpu->registers.l = i&255;
    cpu->registers.clk.m = 3;
}
void LD_A_mC(gbc_cpu *cpu) {
    cpu->registers.a = read_u8(cpu->mmu,0xFF00+cpu->registers.c);
    cpu->registers.clk.m = 2;
}

void SWAP_A(gbc_cpu *cpu) {
    u8 tr = cpu->registers.a;
    cpu->registers.a=((tr&0xF)<<4)|((tr&0xF0)>>4);
    cpu->registers.f = cpu->registers.a?0:FLAG_Z;
    cpu->registers.clk.m = 1;
}
void SWAP_B(gbc_cpu *cpu) {
    u8 tr = cpu->registers.b;
    cpu->registers.b=((tr&0xF)<<4)|((tr&0xF0)>>4);
    cpu->registers.f = cpu->registers.b?0:FLAG_Z;
    cpu->registers.clk.m = 1;
}
void SWAP_C(gbc_cpu *cpu) {
    u8 tr = cpu->registers.c;
    cpu->registers.c=((tr&0xF)<<4)|((tr&0xF0)>>4);
    cpu->registers.f = cpu->registers.c?0:FLAG_Z;
    cpu->registers.clk.m = 1;
}
void SWAP_D(gbc_cpu *cpu) {
    u8 tr = cpu->registers.d;
    cpu->registers.d=((tr&0xF)<<4)|((tr&0xF0)>>4);
    cpu->registers.f = cpu->registers.d?0:FLAG_Z;
    cpu->registers.clk.m = 1;
}
void SWAP_E(gbc_cpu *cpu) {
    u8 tr = cpu->registers.e;
    cpu->registers.e=((tr&0xF)<<4)|((tr&0xF0)>>4);
    cpu->registers.f = cpu->registers.e?0:FLAG_Z;
    cpu->registers.clk.m = 1;
}
void SWAP_H(gbc_cpu *cpu) {
    u8 tr = cpu->registers.h;
    cpu->registers.h=((tr&0xF)<<4)|((tr&0xF0)>>4);
    cpu->registers.f = cpu->registers.h?0:FLAG_Z;
    cpu->registers.clk.m = 1;
}
void SWAP_L(gbc_cpu *cpu) {
    u8 tr = cpu->registers.l;
    cpu->registers.l=((tr&0xF)<<4)|((tr&0xF0)>>4);
    cpu->registers.f = cpu->registers.l?0:FLAG_Z;
    cpu->registers.clk.m = 1;
}

void ADD_A(gbc_cpu *cpu) {
	u16 temp = cpu->registers.a + cpu->registers.a;
	set_flag_z(cpu, (temp & 0xFF) == 0x00);
	set_flag_n(cpu, 0);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.a ^ temp) & 0x10);
	set_flag_c(cpu, temp & 0xFF00);
	cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 1;
}
void ADD_B(gbc_cpu *cpu) {
	u16 temp = cpu->registers.a + cpu->registers.b;
	set_flag_z(cpu, (temp & 0xFF) == 0x00);
	set_flag_n(cpu, 0);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.b ^ temp) & 0x10);
	set_flag_c(cpu, temp & 0xFF00);
	cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 1;
}
void ADD_C(gbc_cpu *cpu) {
	u16 temp = cpu->registers.a + cpu->registers.c;
	set_flag_z(cpu, (temp & 0xFF) == 0x00);
	set_flag_n(cpu, 0);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.c ^ temp) & 0x10);
	set_flag_c(cpu, temp & 0xFF00);
	cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 1;
}
void ADD_D(gbc_cpu *cpu) {
	u16 temp = cpu->registers.a + cpu->registers.d;
	set_flag_z(cpu, (temp & 0xFF) == 0x00);
	set_flag_n(cpu, 0);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.d ^ temp) & 0x10);
	set_flag_c(cpu, temp & 0xFF00);
	cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 1;
}
void ADD_E(gbc_cpu *cpu) {
	u16 temp = cpu->registers.a + cpu->registers.e;
	set_flag_z(cpu, (temp & 0xFF) == 0x00);
	set_flag_n(cpu, 0);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.e ^ temp) & 0x10);
	set_flag_c(cpu, temp & 0xFF00);
	cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 1;
}
void ADD_H(gbc_cpu *cpu) {
	u16 temp = cpu->registers.a + cpu->registers.h;
	set_flag_z(cpu, (temp & 0xFF) == 0x00);
	set_flag_n(cpu, 0);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.h ^ temp) & 0x10);
	set_flag_c(cpu, temp & 0xFF00);
	cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 1;
}
void ADD_L(gbc_cpu *cpu) {
	u16 temp = cpu->registers.a + cpu->registers.l;
	set_flag_z(cpu, (temp & 0xFF) == 0x00);
	set_flag_n(cpu, 0);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.l ^ temp) & 0x10);
	set_flag_c(cpu, temp & 0xFF00);
	cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 1;
}
void ADD_A_mHL(gbc_cpu *cpu) {
    u8 hl = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    u16 temp = cpu->registers.a + hl;
	set_flag_z(cpu, (temp & 0xFF) == 0x00);
	set_flag_n(cpu, 0);
	set_flag_h(cpu, (cpu->registers.a ^ hl ^ temp) & 0x10);
	set_flag_c(cpu, temp & 0xFF00);
	cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 2;
}

void ADD_d8(gbc_cpu *cpu) {
	u8 value = read_u8(cpu, cpu->registers.pc++);
	u16 calc = cpu->registers.a + value;
	set_flag_z(cpu, ((u8)calc == 0));
	set_flag_n(cpu, 0);
	set_flag_h(cpu, ((cpu->registers.a & 0xF) + (value & 0xF) > 0x0F));
	set_flag_c(cpu, calc > 0xFF);
	cpu->registers.a = (u8)calc;
    cpu->registers.clk.m = 2;
}

void ADD_HL_BC(gbc_cpu *cpu) {
	u32 temp = get_hl(cpu) + get_bc(cpu);
	set_flag_n(cpu, 0);
	set_flag_h(cpu, (temp ^ get_hl(cpu) ^ get_bc(cpu)) & 0x1000);
	set_flag_c(cpu, temp & 0xFFFF0000);
	set_hl(cpu, temp & 0x0000FFFF);
    cpu->registers.clk.m = 3;
}
void ADD_HL_DE(gbc_cpu *cpu) {
	u32 temp = get_hl(cpu) + get_de(cpu);
	set_flag_n(cpu, 0);
	set_flag_h(cpu, (temp ^ get_hl(cpu) ^ get_de(cpu)) & 0x1000);
	set_flag_c(cpu, temp & 0xFFFF0000);
	set_hl(cpu, temp & 0x0000FFFF);
    cpu->registers.clk.m = 3;
}
void ADD_HL_HL(gbc_cpu *cpu) {
    u32 temp = get_hl(cpu) + get_hl(cpu);
	set_flag_n(cpu, 0);
    set_flag_h(cpu, temp & 0x1000);
    set_flag_c(cpu, temp & 0xFFFF0000);
    set_hl(cpu, temp & 0x0000FFFF);
}
void ADD_HL_SP(gbc_cpu *cpu) {
	u32 temp = get_hl(cpu) + cpu->registers.sp;
	set_flag_n(cpu, 0);
	set_flag_h(cpu, ((get_hl(cpu) & 0xFFF) + (cpu->registers.sp & 0xFFF)) & 0x1000);
	set_flag_c(cpu, temp & 0x10000);
	set_hl(cpu, (u16)temp);
    cpu->registers.clk.m = 3;
}
void ADD_SP_d8(gbc_cpu *cpu) {
    s8 offset = (s8)read_u8(cpu->mmu, cpu->registers.pc++);
	set_flag_z(cpu, 0);
	set_flag_n(cpu, 0);
    set_flag_h(cpu, (cpu->registers.sp & 0xF) + (offset & 0xF) > 0xF);
    set_flag_c(cpu, (cpu->registers.sp & 0xFF) + (offset & 0xFF) > 0xFF);
    cpu->registers.sp += offset;
    cpu->registers.clk.m = 4;
}

void ADC_A(gbc_cpu *cpu) {
    cpu->registers.clk.m = 1;
}
void ADC_B(gbc_cpu *cpu) {
	u16 temp = cpu->registers.a + cpu->registers.b + flag_c(cpu);
	set_flag_z(cpu, (temp & 0xFF) == 0x00);
	set_flag_n(cpu, 0);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.b ^ temp) & 0x10);
	set_flag_c(cpu, temp & 0xFF00);
	cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 1;
}
void ADC_C(gbc_cpu *cpu) {
	u16 temp = cpu->registers.a + cpu->registers.c + flag_c(cpu);
	set_flag_z(cpu, (temp & 0xFF) == 0x00);
	set_flag_n(cpu, 0);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.c ^ temp) & 0x10);
	set_flag_c(cpu, temp & 0xFF00);
	cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 1;
}
void ADC_D(gbc_cpu *cpu) {
	u16 temp = cpu->registers.a + cpu->registers.d + flag_c(cpu);
	set_flag_z(cpu, (temp & 0xFF) == 0x00);
	set_flag_n(cpu, 0);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.d ^ temp) & 0x10);
	set_flag_c(cpu, temp & 0xFF00);
	cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 1;
}
void ADC_E(gbc_cpu *cpu) {
	u16 temp = cpu->registers.a + cpu->registers.e + flag_c(cpu);
	set_flag_z(cpu, (temp & 0xFF) == 0x00);
	set_flag_n(cpu, 0);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.e ^ temp) & 0x10);
	set_flag_c(cpu, temp & 0xFF00);
	cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 1;
}
void ADC_H(gbc_cpu *cpu) {
	u16 temp = cpu->registers.a + cpu->registers.h + flag_c(cpu);
	set_flag_z(cpu, (temp & 0xFF) == 0x00);
	set_flag_n(cpu, 0);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.h ^ temp) & 0x10);
	set_flag_c(cpu, temp & 0xFF00);
	cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 1;
}
void ADC_L(gbc_cpu *cpu) {
	u16 temp = cpu->registers.a + cpu->registers.l + flag_c(cpu);
	set_flag_z(cpu, (temp & 0xFF) == 0x00);
	set_flag_n(cpu, 0);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.l ^ temp) & 0x10);
	set_flag_c(cpu, temp & 0xFF00);
	cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 1;
}
void ADC_mHL(gbc_cpu *cpu) {
    u8 i = cpu->registers.a;
    u8 r = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    (cpu->registers.a)+=r;
    (cpu->registers.a)+=(cpu->registers.f&FLAG_C)?1:0;
    (cpu->registers.f) = (cpu->registers.a>255)?0x10:0;
    if(!cpu->registers.a) cpu->registers.f|=FLAG_Z;
    if((cpu->registers.a^r^i)&0x10) cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void ADC_d8(gbc_cpu *cpu) {
    u8 i = cpu->registers.a;
    u8 r = read_u8(cpu->mmu,cpu->registers.pc);
    (cpu->registers.a)+=r;
    cpu->registers.pc++;
    (cpu->registers.a)+=(cpu->registers.f&FLAG_C)?1:0;
    (cpu->registers.f) = (cpu->registers.a>255)?0x10:0;
    if(!cpu->registers.a) cpu->registers.f|=FLAG_Z;
    if((cpu->registers.a^r^i)&0x10) cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}

void SUB_A(gbc_cpu *cpu) {
    u8 i = cpu->registers.a;
    cpu->registers.a-=cpu->registers.a;
    cpu->registers.f=(cpu->registers.a<0)?0x50:FLAG_N;
    if(!cpu->registers.a) cpu->registers.f|=FLAG_Z;
    if((cpu->registers.a^cpu->registers.a^i)&FLAG_C) cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 1;
}
void SUB_B(gbc_cpu *cpu) {
    u8 i = cpu->registers.a;
    cpu->registers.a-=cpu->registers.b;
    cpu->registers.f=(cpu->registers.a<0)?0x50:FLAG_N;
    if(!cpu->registers.a) cpu->registers.f|=FLAG_Z;
    if((cpu->registers.a^cpu->registers.b^i)&FLAG_C) cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 1;
}
void SUB_C(gbc_cpu *cpu) {
    u8 i = cpu->registers.a;
    cpu->registers.a-=cpu->registers.c;
    cpu->registers.f=(cpu->registers.a<0)?0x50:FLAG_N;
    if(!cpu->registers.a) cpu->registers.f|=FLAG_Z;
    if((cpu->registers.a^cpu->registers.c^i)&FLAG_C) cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 1;
}
void SUB_D(gbc_cpu *cpu) {
    u8 i = cpu->registers.a;
    cpu->registers.a-=cpu->registers.d;
    cpu->registers.f=(cpu->registers.a<0)?0x50:FLAG_N;
    if(!cpu->registers.a) cpu->registers.f|=FLAG_Z;
    if((cpu->registers.a^cpu->registers.d^i)&FLAG_C) cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 1;
}
void SUB_E(gbc_cpu *cpu) {
    u8 i = cpu->registers.a;
    cpu->registers.a-=cpu->registers.e;
    cpu->registers.f=(cpu->registers.a<0)?0x50:FLAG_N;
    if(!cpu->registers.a) cpu->registers.f|=FLAG_Z;
    if((cpu->registers.a^cpu->registers.e^i)&FLAG_C) cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 1;
}
void SUB_H(gbc_cpu *cpu) {
    u8 i = cpu->registers.a;
    cpu->registers.a-=cpu->registers.h;
    cpu->registers.f=(cpu->registers.a<0)?0x50:FLAG_N;
    if(!cpu->registers.a) cpu->registers.f|=FLAG_Z;
    if((cpu->registers.a^cpu->registers.h^i)&FLAG_C) cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 1;
}
void SUB_L(gbc_cpu *cpu) {
    u8 i = cpu->registers.a;
    cpu->registers.a-=cpu->registers.l;
    cpu->registers.f=(cpu->registers.a<0)?0x50:FLAG_N;
    if(!cpu->registers.a) cpu->registers.f|=FLAG_Z;
    if((cpu->registers.a^cpu->registers.l^i)&FLAG_C) cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 1;
}
void SUB_mHL(gbc_cpu *cpu) {
    u8 i = cpu->registers.a;
    u8 r = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    cpu->registers.a-=r;
    cpu->registers.f=(cpu->registers.a<0)?0x50:FLAG_N;
    if(!cpu->registers.a) cpu->registers.f|=FLAG_Z;
    if((cpu->registers.a^r^i)&FLAG_C) cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void SUB_d8(gbc_cpu *cpu) {
    u8 i = cpu->registers.a;
    u8 r = read_u8(cpu->mmu,cpu->registers.pc);
    cpu->registers.a-=r;
    cpu->registers.pc++;
    cpu->registers.f=(cpu->registers.a<0)?0x50:FLAG_N;
    if(!cpu->registers.a) cpu->registers.f|=FLAG_Z;
    if((cpu->registers.a^r^i)&FLAG_C) cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}

void SBC_A(gbc_cpu *cpu) {
	cpu->registers.a = flag_c(cpu) ? 0xFF : 0x00;
	set_flag_z(cpu, !flag_c(cpu));
	set_flag_n(cpu, 1);
	set_flag_h(cpu, flag_c(cpu));
    cpu->registers.clk.m = 1;
}
void SBC_B(gbc_cpu *cpu) {
    u16 temp = cpu->registers.a - cpu->registers.b - flag_c(cpu);
	set_flag_z(cpu, (temp & 0xFF) == 0x00);
	set_flag_n(cpu, 1);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.b ^ temp) & 0x10);
	set_flag_c(cpu, temp & 0xFF00);
	cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 1;
}
void SBC_C(gbc_cpu *cpu) {
    u16 temp = cpu->registers.a - cpu->registers.c - flag_c(cpu);
	set_flag_z(cpu, (temp & 0xFF) == 0x00);
	set_flag_n(cpu, 1);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.c ^ temp) & 0x10);
	set_flag_c(cpu, temp & 0xFF00);
	cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 1;
}
void SBC_D(gbc_cpu *cpu) {
    u16 temp = cpu->registers.a - cpu->registers.d - flag_c(cpu);
	set_flag_z(cpu, (temp & 0xFF) == 0x00);
	set_flag_n(cpu, 1);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.d ^ temp) & 0x10);
	set_flag_c(cpu, temp & 0xFF00);
	cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 1;
}
void SBC_E(gbc_cpu *cpu) {
    u16 temp = cpu->registers.a - cpu->registers.e - flag_c(cpu);
	set_flag_z(cpu, (temp & 0xFF) == 0x00);
	set_flag_n(cpu, 1);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.e ^ temp) & 0x10);
	set_flag_c(cpu, temp & 0xFF00);
	cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 1;
}
void SBC_H(gbc_cpu *cpu) {
    u16 temp = cpu->registers.a - cpu->registers.h - flag_c(cpu);
	set_flag_z(cpu, (temp & 0xFF) == 0x00);
	set_flag_n(cpu, 1);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.h ^ temp) & 0x10);
	set_flag_c(cpu, temp & 0xFF00);
	cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 1;
}
void SBC_L(gbc_cpu *cpu) {
    u16 temp = cpu->registers.a - cpu->registers.l - flag_c(cpu);
	set_flag_z(cpu, (temp & 0xFF) == 0x00);
	set_flag_n(cpu, 1);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.l ^ temp) & 0x10);
	set_flag_c(cpu, temp & 0xFF00);
	cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 1;
}
void SBC_mHL(gbc_cpu *cpu) {
	u8 val = read_u8(cpu, get_hl(cpu));
	u16 temp = cpu->registers.a - val - flag_c(cpu);
	set_flag_z(cpu, (temp & 0xFF) == 0x00);
	set_flag_n(cpu, 1);
	set_flag_h(cpu, (cpu->registers.a ^ val ^ temp) & 0x10);
	set_flag_c(cpu, temp & 0xFF00);
	cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 2;
}

void SBC_d8(gbc_cpu *cpu) {
	u8 temp_8 = read_u8(cpu, cpu->registers.pc++);
	u16 temp_16 = cpu->registers.a - temp_8 - flag_c(cpu);
	set_flag_z(cpu, (temp_16 & 0xFF) == 0x00);
	set_flag_n(cpu, 1);
	set_flag_h(cpu, (cpu->registers.a ^ temp_8 ^ temp_16) & 0x10);
	set_flag_c(cpu, temp_16 & 0xFF00);
	cpu->registers.a = (temp_16 & 0xFF);
    cpu->registers.clk.m = 2;
}

void CP_A(gbc_cpu *cpu) {
    cpu->registers.f = FLAG_Z;
    cpu->registers.clk.m=1;
}
void CP_B(gbc_cpu *cpu) {
	u16 temp = cpu->registers.a - cpu->registers.b;
    set_flag_z(cpu, (temp & 0xFF) == 0x00);
    set_flag_n(cpu, 1);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.b ^ temp) & 0x10);
    set_flag_c(cpu, temp & 0xFF00);
    cpu->registers.clk.m=1;
}
void CP_C(gbc_cpu *cpu) {
	u16 temp = cpu->registers.a - cpu->registers.c;
    set_flag_z(cpu, (temp & 0xFF) == 0x00);
    set_flag_n(cpu, 1);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.c ^ temp) & 0x10);
    set_flag_c(cpu, temp & 0xFF00);
    cpu->registers.clk.m=1;
}
void CP_D(gbc_cpu *cpu) {
	u16 temp = cpu->registers.a - cpu->registers.d;
    set_flag_z(cpu, (temp & 0xFF) == 0x00);
    set_flag_n(cpu, 1);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.d ^ temp) & 0x10);
    set_flag_c(cpu, temp & 0xFF00);
    cpu->registers.clk.m=1;
}
void CP_E(gbc_cpu *cpu) {
	u16 temp = cpu->registers.a - cpu->registers.e;
    set_flag_z(cpu, (temp & 0xFF) == 0x00);
    set_flag_n(cpu, 1);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.e ^ temp) & 0x10);
    set_flag_c(cpu, temp & 0xFF00);
    cpu->registers.clk.m=1;
}
void CP_H(gbc_cpu *cpu) {
	u16 temp = cpu->registers.a - cpu->registers.h;
    set_flag_z(cpu, (temp & 0xFF) == 0x00);
    set_flag_n(cpu, 1);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.h ^ temp) & 0x10);
    set_flag_c(cpu, temp & 0xFF00);
    cpu->registers.clk.m=1;
}
void CP_L(gbc_cpu *cpu) {
	u16 temp = cpu->registers.a - cpu->registers.l;
    set_flag_z(cpu, (temp & 0xFF) == 0x00);
    set_flag_n(cpu, 1);
	set_flag_h(cpu, (cpu->registers.a ^ cpu->registers.l ^ temp) & 0x10);
    set_flag_c(cpu, temp & 0xFF00);
    cpu->registers.clk.m=1;
}
void CP_mHL(gbc_cpu *cpu) {
	u8 temp_8 = read_u8(cpu->mmu, (cpu->registers.h<<8)+cpu->registers.l);
    u16 temp_16 = cpu->registers.a - temp_8;
    set_flag_z(cpu, (temp_16 & 0xFF) == 0x00);
    set_flag_n(cpu, 1);
	set_flag_h(cpu, (cpu->registers.a ^ temp_8^ temp_16) & 0x10);
    set_flag_c(cpu, temp_16 & 0xFF00);
    cpu->registers.clk.m = 2;
}
void CP_d8(gbc_cpu *cpu) {
    u8 temp_8 = read_u8(cpu->mmu, cpu->registers.pc++);
    u16 temp_16 = cpu->registers.a - temp_8;
    set_flag_z(cpu, (temp_16 & 0xFF) == 0x00);
    set_flag_n(cpu, 1);
	set_flag_h(cpu, (cpu->registers.a ^ temp_8^ temp_16) & 0x10);
    set_flag_c(cpu, temp_16 & 0xFF00);
    cpu->registers.clk.m = 2;
}

void DAA(gbc_cpu *cpu) {
    u8 i = cpu->registers.a;
    if((cpu->registers.f&FLAG_H)||((cpu->registers.a&15)>9)) cpu->registers.a += 6;
    cpu->registers.f &= 0xEF;
    if((cpu->registers.f&FLAG_H)||(i>0x99)) {
        cpu->registers.a += 0x60;
        cpu->registers.f|=FLAG_C;
    } cpu->registers.clk.m = 1;
}

void AND_A(gbc_cpu *cpu) {
    cpu->registers.a&=cpu->registers.a;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 1);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}
void AND_B(gbc_cpu *cpu) {
    cpu->registers.a&=cpu->registers.b;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 1);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}
void AND_C(gbc_cpu *cpu) {
    cpu->registers.a&=cpu->registers.c;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 1);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}
void AND_D(gbc_cpu *cpu) {
    cpu->registers.a&=cpu->registers.d;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 1);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}
void AND_E(gbc_cpu *cpu) {
    cpu->registers.a&=cpu->registers.e;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 1);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}
void AND_H(gbc_cpu *cpu) {
    cpu->registers.a&=cpu->registers.h;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 1);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}
void AND_L(gbc_cpu *cpu) {
    cpu->registers.a&=cpu->registers.l;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 1);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}
void AND_mHL(gbc_cpu *cpu) {
    cpu->registers.a&=read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 1);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 2;
}
void AND_d8(gbc_cpu *cpu) {
    cpu->registers.a&=read_u8(cpu->mmu,cpu->registers.pc);
    cpu->registers.pc++;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 1);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 2;
}

void OR_A(gbc_cpu *cpu) {
    cpu->registers.a|=cpu->registers.a;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}
void OR_B(gbc_cpu *cpu) {
    cpu->registers.a|=cpu->registers.b;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}
void OR_C(gbc_cpu *cpu) {
    cpu->registers.a|=cpu->registers.c;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}
void OR_D(gbc_cpu *cpu) {
    cpu->registers.a|=cpu->registers.d;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}
void OR_E(gbc_cpu *cpu) {
    cpu->registers.a|=cpu->registers.e;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}
void OR_H(gbc_cpu *cpu) {
    cpu->registers.a|=cpu->registers.h;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}
void OR_L(gbc_cpu *cpu) {
    cpu->registers.a|=cpu->registers.l;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}
void OR_mHL(gbc_cpu *cpu) {
    cpu->registers.a|=read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 2;
}
void OR_d8(gbc_cpu *cpu) {
    cpu->registers.a|=read_u8(cpu->mmu,cpu->registers.pc);
    cpu->registers.pc++;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 2;
}

void XOR_A(gbc_cpu *cpu) {
    cpu->registers.a = 0;
    set_flag_z(cpu, 0);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}
void XOR_B(gbc_cpu *cpu) {
    cpu->registers.a^=cpu->registers.b;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}
void XOR_C(gbc_cpu *cpu) {
    cpu->registers.a^=cpu->registers.c;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}
void XOR_D(gbc_cpu *cpu) {
    cpu->registers.a^=cpu->registers.d;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}
void XOR_E(gbc_cpu *cpu) {
    cpu->registers.a^=cpu->registers.e;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}
void XOR_H(gbc_cpu *cpu) {
    cpu->registers.a^=cpu->registers.h;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}
void XOR_L(gbc_cpu *cpu) {
    cpu->registers.a^=cpu->registers.l;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}
void XOR_mHL(gbc_cpu *cpu) {
    cpu->registers.a^=read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 2;
}
void XOR_d8(gbc_cpu *cpu) {
    cpu->registers.a^=read_u8(cpu->mmu,cpu->registers.pc);
    cpu->registers.pc++;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 2;
}

void INC_A(gbc_cpu *cpu) {
    u8 i = cpu->registers.a;
    cpu->registers.a++;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
    set_flag_h(cpu, half_carry(i, 1));
    cpu->registers.clk.m = 1;
}
void INC_B(gbc_cpu *cpu) {
    u8 i = cpu->registers.b;
    cpu->registers.b++;
    set_flag_z(cpu, cpu->registers.b == 0x00);
    set_flag_n(cpu, 0);
    set_flag_h(cpu, half_carry(i, 1));
    cpu->registers.clk.m = 1;
}
void INC_C(gbc_cpu *cpu) {
    u8 i = cpu->registers.c;
    cpu->registers.c++;
    set_flag_z(cpu, cpu->registers.c == 0x00);
    set_flag_n(cpu, 0);
    set_flag_h(cpu, half_carry(i, 1));
    cpu->registers.clk.m = 1;
}
void INC_D(gbc_cpu *cpu) {
    u8 i = cpu->registers.d;
    cpu->registers.d++;
    set_flag_z(cpu, cpu->registers.d == 0x00);
    set_flag_n(cpu, 0);
    set_flag_h(cpu, half_carry(i, 1));
    cpu->registers.clk.m = 1;
}
void INC_E(gbc_cpu *cpu) {
    u8 i = cpu->registers.e;
    cpu->registers.e++;
    set_flag_z(cpu, cpu->registers.e == 0x00);
    set_flag_n(cpu, 0);
    set_flag_h(cpu, half_carry(i, 1));
    cpu->registers.clk.m = 1;
}
void INC_H(gbc_cpu *cpu) {
    u8 i = cpu->registers.h;
    cpu->registers.h++;
    set_flag_z(cpu, cpu->registers.h == 0x00);
    set_flag_n(cpu, 0);
    set_flag_h(cpu, half_carry(i, 1));
    cpu->registers.clk.m = 1;
}
void INC_L(gbc_cpu *cpu) {
    u8 i = cpu->registers.l;
    cpu->registers.l++;
    set_flag_z(cpu, cpu->registers.l == 0x00);
    set_flag_n(cpu, 0);
    set_flag_h(cpu, half_carry(i, 1));
    cpu->registers.clk.m = 1;
}
void INC_mHL(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu, (cpu->registers.h<<8)+cpu->registers.l)+1;
    i&=255;
    write_u8(cpu->mmu, (cpu->registers.h<<8)+cpu->registers.l, i);
    cpu->registers.f = (cpu->registers.f & ~FLAG_Z) | ((i & 0xFF) == 0x00) ? FLAG_Z : 0;
    cpu->registers.clk.m = 3;
}

void INC_BC(gbc_cpu *cpu) {
    cpu->registers.c=(cpu->registers.c+1)&255;
    if(!cpu->registers.c) cpu->registers.b=(cpu->registers.b+1)&255;
    cpu->registers.clk.m = 1;
}
void INC_DE(gbc_cpu *cpu) {
    cpu->registers.e=(cpu->registers.e+1)&255;
    if(!cpu->registers.e) cpu->registers.d=(cpu->registers.d+1)&255;
    cpu->registers.clk.m = 1;
}
void INC_HL(gbc_cpu *cpu) {
    cpu->registers.l=(cpu->registers.l+1)&255;
    if(!cpu->registers.l) cpu->registers.h=(cpu->registers.h+1)&255;
    cpu->registers.clk.m = 1;
}
void INC_SP(gbc_cpu *cpu) {
    cpu->registers.sp=(cpu->registers.sp+1)&65535;
    cpu->registers.clk.m = 1;
}

void DEC_B(gbc_cpu *cpu) {
    u8 i = cpu->registers.b;
    cpu->registers.b--;
    set_flag_z(cpu, cpu->registers.b == 0x00);
    set_flag_n(cpu, 1);
    set_flag_h(cpu, (cpu->registers.b & 0x0F) == 0x0F);
    cpu->registers.clk.m = 1;
}
void DEC_C(gbc_cpu *cpu) {
    u8 i = cpu->registers.c;
    cpu->registers.c--;
    set_flag_z(cpu, cpu->registers.c == 0x00);
    set_flag_n(cpu, 1);
    set_flag_h(cpu, (cpu->registers.c & 0x0F) == 0x0F);
    cpu->registers.clk.m = 1;
}
void DEC_D(gbc_cpu *cpu) {
    u8 i = cpu->registers.d;
    cpu->registers.d--;
    set_flag_z(cpu, cpu->registers.d == 0x00);
    set_flag_n(cpu, 1);
    set_flag_h(cpu, (cpu->registers.d & 0x0F) == 0x0F);
    cpu->registers.clk.m = 1;
}
void DEC_E(gbc_cpu *cpu) {
    u8 i = cpu->registers.e;
    cpu->registers.e--;
    set_flag_z(cpu, cpu->registers.e == 0x00);
    set_flag_n(cpu, 1);
    set_flag_h(cpu, (cpu->registers.e & 0x0F) == 0x0F);
    cpu->registers.clk.m = 1;
}
void DEC_H(gbc_cpu *cpu) {
    u8 i = cpu->registers.h;
    cpu->registers.h--;
    set_flag_z(cpu, cpu->registers.h == 0x00);
    set_flag_n(cpu, 1);
    set_flag_h(cpu, (cpu->registers.h & 0x0F) == 0x0F);
    cpu->registers.clk.m = 1;
}
void DEC_L(gbc_cpu *cpu) {
    u8 i = cpu->registers.l;
    cpu->registers.l--;
    set_flag_z(cpu, cpu->registers.l == 0x00);
    set_flag_n(cpu, 1);
    set_flag_h(cpu, (cpu->registers.l & 0x0F) == 0x0F);
    cpu->registers.clk.m = 1;
}
void DEC_A(gbc_cpu *cpu) {
    u8 i = cpu->registers.a;
    cpu->registers.a--;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 1);
    set_flag_h(cpu, (cpu->registers.a & 0x0F) == 0x0F);
    cpu->registers.clk.m = 1;
}
void DEC_mHL(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l)-1;
    i&=255;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.f = i?0:FLAG_Z;
    cpu->registers.f |= FLAG_N;
    cpu->registers.clk.m = 3;
}

void DEC_BC(gbc_cpu *cpu) {
    cpu->registers.c=(cpu->registers.c-1)&255;
    if(cpu->registers.c==255) cpu->registers.b=(cpu->registers.b-1)&255;
    cpu->registers.clk.m = 1;
}
void DEC_DE(gbc_cpu *cpu) {
    cpu->registers.e=(cpu->registers.e-1)&255;
    if(cpu->registers.e==255) cpu->registers.d=(cpu->registers.d-1)&255;
    cpu->registers.clk.m = 1;
}
void DEC_HL(gbc_cpu *cpu) {
    cpu->registers.l=(cpu->registers.l-1)&255;
    if(cpu->registers.l==255) cpu->registers.h=(cpu->registers.h-1)&255;
    cpu->registers.clk.m = 1;
}
void DEC_SP(gbc_cpu *cpu) {
    cpu->registers.sp=(cpu->registers.sp-1)&65535;
    cpu->registers.clk.m = 1;
}

void BIT_0_A(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.a&0x01)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_0_B(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.b&0x01)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_0_C(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.c&0x01)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_0_D(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.d&0x01)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_0_E(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.e&0x01)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_0_H(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.h&0x01)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_0_L(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.l&0x01)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_0_M(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l)&0x01)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 3;
}

void RES_0_A(gbc_cpu *cpu) {
    cpu->registers.a &= 0xFE;
    cpu->registers.clk.m = 2;
}
void RES_0_B(gbc_cpu *cpu) {
    cpu->registers.b &= 0xFE;
    cpu->registers.clk.m = 2;
}
void RES_0_C(gbc_cpu *cpu) {
    cpu->registers.c &= 0xFE;
    cpu->registers.clk.m = 2;
}
void RES_0_D(gbc_cpu *cpu) {
    cpu->registers.d &= 0xFE;
    cpu->registers.clk.m = 2;
}
void RES_0_E(gbc_cpu *cpu) {
    cpu->registers.e &= 0xFE;
    cpu->registers.clk.m = 2;
}
void RES_0_H(gbc_cpu *cpu) {
    cpu->registers.h &= 0xFE;
    cpu->registers.clk.m = 2;
}
void RES_0_L(gbc_cpu *cpu) {
    cpu->registers.l &= 0xFE;
    cpu->registers.clk.m = 2;
}
void RES_0_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i &= 0xFE;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void SET_0_B(gbc_cpu *cpu) {
    cpu->registers.b |= 0x01;
    cpu->registers.clk.m = 2;
}
void SET_0_C(gbc_cpu *cpu) {
    cpu->registers.b |= 0x01;
    cpu->registers.clk.m = 2;
}
void SET_0_D(gbc_cpu *cpu) {
    cpu->registers.b |= 0x01;
    cpu->registers.clk.m = 2;
}
void SET_0_E(gbc_cpu *cpu) {
    cpu->registers.b |= 0x01;
    cpu->registers.clk.m = 2;
}
void SET_0_H(gbc_cpu *cpu) {
    cpu->registers.b |= 0x01;
    cpu->registers.clk.m = 2;
}
void SET_0_L(gbc_cpu *cpu) {
    cpu->registers.b |= 0x01;
    cpu->registers.clk.m = 2;
}
void SET_0_A(gbc_cpu *cpu) {
    cpu->registers.b |= 0x01;
    cpu->registers.clk.m = 2;
}
void SET_0_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i |= 0x01;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void BIT_1_B(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.b&0x02)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_1_C(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.c&0x02)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_1_D(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.d&0x02)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_1_E(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.e&0x02)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_1_H(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.h&0x02)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_1_L(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.l&0x02)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_1_A(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.a&0x02)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_1_M(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l)&0x02)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 3;
}

void RES_1_B(gbc_cpu *cpu) {
    cpu->registers.b &= 0xFD;
    cpu->registers.clk.m = 2;
}
void RES_1_C(gbc_cpu *cpu) {
    cpu->registers.c &= 0xFD;
    cpu->registers.clk.m = 2;
}
void RES_1_D(gbc_cpu *cpu) {
    cpu->registers.d &= 0xFD;
    cpu->registers.clk.m = 2;
}
void RES_1_E(gbc_cpu *cpu) {
    cpu->registers.e &= 0xFD;
    cpu->registers.clk.m = 2;
}
void RES_1_H(gbc_cpu *cpu) {
    cpu->registers.h &= 0xFD;
    cpu->registers.clk.m = 2;
}
void RES_1_L(gbc_cpu *cpu) {
    cpu->registers.l &= 0xFD;
    cpu->registers.clk.m = 2;
}
void RES_1_A(gbc_cpu *cpu) {
    cpu->registers.a &= 0xFD;
    cpu->registers.clk.m = 2;
}
void RES_1_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i &= 0xFD;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void SET_1_B(gbc_cpu *cpu) {
    cpu->registers.b |= 0x02;
    cpu->registers.clk.m = 2;
}
void SET_1_C(gbc_cpu *cpu) {
    cpu->registers.b |= 0x02;
    cpu->registers.clk.m = 2;
}
void SET_1_D(gbc_cpu *cpu) {
    cpu->registers.b |= 0x02;
    cpu->registers.clk.m = 2;
}
void SET_1_E(gbc_cpu *cpu) {
    cpu->registers.b |= 0x02;
    cpu->registers.clk.m = 2;
}
void SET_1_H(gbc_cpu *cpu) {
    cpu->registers.b |= 0x02;
    cpu->registers.clk.m = 2;
}
void SET_1_L(gbc_cpu *cpu) {
    cpu->registers.b |= 0x02;
    cpu->registers.clk.m = 2;
}
void SET_1_A(gbc_cpu *cpu) {
    cpu->registers.b |= 0x02;
    cpu->registers.clk.m = 2;
}
void SET_1_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i |= 0x02;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void BIT_2_B(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.b&0x04)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_2_C(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.c&0x04)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_2_D(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.d&0x04)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_2_E(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.e&0x04)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_2_H(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.h&0x04)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_2_L(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.l&0x04)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_2_A(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.a&0x04)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_2_M(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l)&0x04)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 3;
}

void RES_2_B(gbc_cpu *cpu) {
    cpu->registers.b &= 0xFB;
    cpu->registers.clk.m = 2;
}
void RES_2_C(gbc_cpu *cpu) {
    cpu->registers.c &= 0xFB;
    cpu->registers.clk.m = 2;
}
void RES_2_D(gbc_cpu *cpu) {
    cpu->registers.d &= 0xFB;
    cpu->registers.clk.m = 2;
}
void RES_2_E(gbc_cpu *cpu) {
    cpu->registers.e &= 0xFB;
    cpu->registers.clk.m = 2;
}
void RES_2_H(gbc_cpu *cpu) {
    cpu->registers.h &= 0xFB;
    cpu->registers.clk.m = 2;
}
void RES_2_L(gbc_cpu *cpu) {
    cpu->registers.l &= 0xFB;
    cpu->registers.clk.m = 2;
}
void RES_2_A(gbc_cpu *cpu) {
    cpu->registers.a &= 0xFB;
    cpu->registers.clk.m = 2;
}
void RES_2_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i &= 0xFB;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void SET_2_B(gbc_cpu *cpu) {
    cpu->registers.b |= 0x04;
    cpu->registers.clk.m = 2;
}
void SET_2_C(gbc_cpu *cpu) {
    cpu->registers.b |= 0x04;
    cpu->registers.clk.m = 2;
}
void SET_2_D(gbc_cpu *cpu) {
    cpu->registers.b |= 0x04;
    cpu->registers.clk.m = 2;
}
void SET_2_E(gbc_cpu *cpu) {
    cpu->registers.b |= 0x04;
    cpu->registers.clk.m = 2;
}
void SET_2_H(gbc_cpu *cpu) {
    cpu->registers.b |= 0x04;
    cpu->registers.clk.m = 2;
}
void SET_2_L(gbc_cpu *cpu) {
    cpu->registers.b |= 0x04;
    cpu->registers.clk.m = 2;
}
void SET_2_A(gbc_cpu *cpu) {
    cpu->registers.b |= 0x04;
    cpu->registers.clk.m = 2;
}
void SET_2_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i |= 0x04;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void BIT_3_B(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.b&0x08)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_3_C(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.c&0x08)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_3_D(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.d&0x08)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_3_E(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.e&0x08)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_3_H(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.h&0x08)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_3_L(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.l&0x08)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_3_A(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.a&0x08)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_3_M(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l)&0x08)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 3;
}

void RES_3_B(gbc_cpu *cpu) {
    cpu->registers.b &= 0xF7;
    cpu->registers.clk.m = 2;
}
void RES_3_C(gbc_cpu *cpu) {
    cpu->registers.c &= 0xF7;
    cpu->registers.clk.m = 2;
}
void RES_3_D(gbc_cpu *cpu) {
    cpu->registers.d &= 0xF7;
    cpu->registers.clk.m = 2;
}
void RES_3_E(gbc_cpu *cpu) {
    cpu->registers.e &= 0xF7;
    cpu->registers.clk.m = 2;
}
void RES_3_H(gbc_cpu *cpu) {
    cpu->registers.h &= 0xF7;
    cpu->registers.clk.m = 2;
}
void RES_3_L(gbc_cpu *cpu) {
    cpu->registers.l &= 0xF7;
    cpu->registers.clk.m = 2;
}
void RES_3_A(gbc_cpu *cpu) {
    cpu->registers.a &= 0xF7;
    cpu->registers.clk.m = 2;
}
void RES_3_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i &= 0xF7;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void SET_3_B(gbc_cpu *cpu) {
    cpu->registers.b |= 0x08;
    cpu->registers.clk.m = 2;
}
void SET_3_C(gbc_cpu *cpu) {
    cpu->registers.b |= 0x08;
    cpu->registers.clk.m = 2;
}
void SET_3_D(gbc_cpu *cpu) {
    cpu->registers.b |= 0x08;
    cpu->registers.clk.m = 2;
}
void SET_3_E(gbc_cpu *cpu) {
    cpu->registers.b |= 0x08;
    cpu->registers.clk.m = 2;
}
void SET_3_H(gbc_cpu *cpu) {
    cpu->registers.b |= 0x08;
    cpu->registers.clk.m = 2;
}
void SET_3_L(gbc_cpu *cpu) {
    cpu->registers.b |= 0x08;
    cpu->registers.clk.m = 2;
}
void SET_3_A(gbc_cpu *cpu) {
    cpu->registers.b |= 0x08;
    cpu->registers.clk.m = 2;
}
void SET_3_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i |= 0x08;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void BIT_4_B(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.b&0x10)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_4_C(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.c&0x10)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_4_D(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.d&0x10)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_4_E(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.e&0x10)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_4_H(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.h&0x10)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_4_L(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.l&0x10)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_4_A(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.a&0x10)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_4_M(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l)&0x10)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 3;
}

void RES_4_B(gbc_cpu *cpu) {
    cpu->registers.b &= 0xEF;
    cpu->registers.clk.m = 2;
}
void RES_4_C(gbc_cpu *cpu) {
    cpu->registers.c &= 0xEF;
    cpu->registers.clk.m = 2;
}
void RES_4_D(gbc_cpu *cpu) {
    cpu->registers.d &= 0xEF;
    cpu->registers.clk.m = 2;
}
void RES_4_E(gbc_cpu *cpu) {
    cpu->registers.e &= 0xEF;
    cpu->registers.clk.m = 2;
}
void RES_4_H(gbc_cpu *cpu) {
    cpu->registers.h &= 0xEF;
    cpu->registers.clk.m = 2;
}
void RES_4_L(gbc_cpu *cpu) {
    cpu->registers.l &= 0xEF;
    cpu->registers.clk.m = 2;
}
void RES_4_A(gbc_cpu *cpu) {
    cpu->registers.a &= 0xEF;
    cpu->registers.clk.m = 2;
}
void RES_4_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i &= 0xEF;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void SET_4_B(gbc_cpu *cpu) {
    cpu->registers.b |= 0x10;
    cpu->registers.clk.m = 2;
}
void SET_4_C(gbc_cpu *cpu) {
    cpu->registers.b |= 0x10;
    cpu->registers.clk.m = 2;
}
void SET_4_D(gbc_cpu *cpu) {
    cpu->registers.b |= 0x10;
    cpu->registers.clk.m = 2;
}
void SET_4_E(gbc_cpu *cpu) {
    cpu->registers.b |= 0x10;
    cpu->registers.clk.m = 2;
}
void SET_4_H(gbc_cpu *cpu) {
    cpu->registers.b |= 0x10;
    cpu->registers.clk.m = 2;
}
void SET_4_L(gbc_cpu *cpu) {
    cpu->registers.b |= 0x10;
    cpu->registers.clk.m = 2;
}
void SET_4_A(gbc_cpu *cpu) {
    cpu->registers.b |= 0x10;
    cpu->registers.clk.m = 2;
}
void SET_4_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i|=FLAG_C;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void BIT_5_B(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.b&FLAG_H)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_5_C(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.c&0x20)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_5_D(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.d&0x20)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_5_E(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.e&0x20)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_5_H(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.h&0x20)?0:FLAG_Z;
    cpu->registers.clk.m = 2;
    cpu->registers.f|=FLAG_H;
}
void BIT_5_L(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.l&0x20)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_5_A(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.a&0x20)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_5_M(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l)&0x20)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 3;
}

void RES_5_B(gbc_cpu *cpu) {
    cpu->registers.b &= 0xDF;
    cpu->registers.clk.m = 2;
}
void RES_5_C(gbc_cpu *cpu) {
    cpu->registers.c &= 0xDF;
    cpu->registers.clk.m = 2;
}
void RES_5_D(gbc_cpu *cpu) {
    cpu->registers.d &= 0xDF;
    cpu->registers.clk.m = 2;
}
void RES_5_E(gbc_cpu *cpu) {
    cpu->registers.e &= 0xDF;
    cpu->registers.clk.m = 2;
}
void RES_5_H(gbc_cpu *cpu) {
    cpu->registers.h &= 0xDF;
    cpu->registers.clk.m = 2;
}
void RES_5_L(gbc_cpu *cpu) {
    cpu->registers.l &= 0xDF;
    cpu->registers.clk.m = 2;
}
void RES_5_A(gbc_cpu *cpu) {
    cpu->registers.a &= 0xDF;
    cpu->registers.clk.m = 2;
}
void RES_5_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i &= 0xDF;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void SET_5_B(gbc_cpu *cpu) {
    cpu->registers.b |= 0x20;
    cpu->registers.clk.m = 2;
}
void SET_5_C(gbc_cpu *cpu) {
    cpu->registers.b |= 0x20;
    cpu->registers.clk.m = 2;
}
void SET_5_D(gbc_cpu *cpu) {
    cpu->registers.b |= 0x20;
    cpu->registers.clk.m = 2;
}
void SET_5_E(gbc_cpu *cpu) {
    cpu->registers.b |= 0x20;
    cpu->registers.clk.m = 2;
}
void SET_5_H(gbc_cpu *cpu) {
    cpu->registers.b |= 0x20;
    cpu->registers.clk.m = 2;
}
void SET_5_L(gbc_cpu *cpu) {
    cpu->registers.b |= 0x20;
    cpu->registers.clk.m = 2;
}
void SET_5_A(gbc_cpu *cpu) {
    cpu->registers.b |= 0x20;
    cpu->registers.clk.m = 2;
}
void SET_5_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i |= 0x20;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void BIT_6_B(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.b&0x40)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_6_C(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.c&0x40)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_6_D(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.d&0x40)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_6_E(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.e&0x40)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_6_H(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.h&0x40)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_6_L(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.l&0x40)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_6_A(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.a&0x40)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_6_M(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l)&0x40)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 3;
}

void RES_6_B(gbc_cpu *cpu) {
    cpu->registers.b &= 0xBF;
    cpu->registers.clk.m = 2;
}
void RES_6_C(gbc_cpu *cpu) {
    cpu->registers.c &= 0xBF;
    cpu->registers.clk.m = 2;
}
void RES_6_D(gbc_cpu *cpu) {
    cpu->registers.d &= 0xBF;
    cpu->registers.clk.m = 2;
}
void RES_6_E(gbc_cpu *cpu) {
    cpu->registers.e &= 0xBF;
    cpu->registers.clk.m = 2;
}
void RES_6_H(gbc_cpu *cpu) {
    cpu->registers.h &= 0xBF;
    cpu->registers.clk.m = 2;
}
void RES_6_L(gbc_cpu *cpu) {
    cpu->registers.l &= 0xBF;
    cpu->registers.clk.m = 2;
}
void RES_6_A(gbc_cpu *cpu) {
    cpu->registers.a &= 0xBF;
    cpu->registers.clk.m = 2;
}
void RES_6_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i &= 0xBF;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void SET_6_B(gbc_cpu *cpu) {
    cpu->registers.b |= 0x40;
    cpu->registers.clk.m = 2;
}
void SET_6_C(gbc_cpu *cpu) {
    cpu->registers.b |= 0x40;
    cpu->registers.clk.m = 2;
}
void SET_6_D(gbc_cpu *cpu) {
    cpu->registers.b |= 0x40;
    cpu->registers.clk.m = 2;
}
void SET_6_E(gbc_cpu *cpu) {
    cpu->registers.b |= 0x40;
    cpu->registers.clk.m = 2;
}
void SET_6_H(gbc_cpu *cpu) {
    cpu->registers.b |= 0x40;
    cpu->registers.clk.m = 2;
}
void SET_6_L(gbc_cpu *cpu) {
    cpu->registers.b |= 0x40;
    cpu->registers.clk.m = 2;
}
void SET_6_A(gbc_cpu *cpu) {
    cpu->registers.b |= 0x40;
    cpu->registers.clk.m = 2;
}
void SET_6_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i |= 0x40;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void BIT_7_B(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.b&0x80)?0:FLAG_Z;
    cpu->registers.clk.m = 2;
    cpu->registers.f|=FLAG_H;
}
void BIT_7_C(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.c&0x80)?0:FLAG_Z;
    cpu->registers.clk.m = 2;
    cpu->registers.f|=FLAG_H;
}
void BIT_7_D(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.d&0x80)?0:FLAG_Z;
    cpu->registers.clk.m = 2;
    cpu->registers.f|=FLAG_H;
}
void BIT_7_E(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.e&0x80)?0:FLAG_Z;
    cpu->registers.clk.m = 2;
    cpu->registers.f|=FLAG_H;
}
void BIT_7_H(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.h&0x80)?0:FLAG_Z;
    cpu->registers.clk.m = 2;
    cpu->registers.f|=FLAG_H;
}
void BIT_7_L(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.l&0x80)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_7_A(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.a&0x80)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_7_M(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l)&0x80)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 3;
}

void RES_7_B(gbc_cpu *cpu) {
    cpu->registers.b &= 0x7F;
    cpu->registers.clk.m = 2;
}
void RES_7_C(gbc_cpu *cpu) {
    cpu->registers.c &= 0x7F;
    cpu->registers.clk.m = 2;
}
void RES_7_D(gbc_cpu *cpu) {
    cpu->registers.d &= 0x7F;
    cpu->registers.clk.m = 2;
}
void RES_7_E(gbc_cpu *cpu) {
    cpu->registers.e &= 0x7F;
    cpu->registers.clk.m = 2;
}
void RES_7_H(gbc_cpu *cpu) {
    cpu->registers.h &= 0x7F;
    cpu->registers.clk.m = 2;
}
void RES_7_L(gbc_cpu *cpu) {
    cpu->registers.l &= 0x7F;
    cpu->registers.clk.m = 2;
}
void RES_7_A(gbc_cpu *cpu) {
    cpu->registers.a &= 0x7F;
    cpu->registers.clk.m = 2;
}
void RES_7_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i &= 0x7F;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void SET_7_B(gbc_cpu *cpu) {
    cpu->registers.b |= 0x80;
    cpu->registers.clk.m = 2;
}
void SET_7_C(gbc_cpu *cpu) {
    cpu->registers.b |= 0x80;
    cpu->registers.clk.m = 2;
}
void SET_7_D(gbc_cpu *cpu) {
    cpu->registers.b |= 0x80;
    cpu->registers.clk.m = 2;
}
void SET_7_E(gbc_cpu *cpu) {
    cpu->registers.b |= 0x80;
    cpu->registers.clk.m = 2;
}
void SET_7_H(gbc_cpu *cpu) {
    cpu->registers.b |= 0x80;
    cpu->registers.clk.m = 2;
}
void SET_7_L(gbc_cpu *cpu) {
    cpu->registers.b |= 0x80;
    cpu->registers.clk.m = 2;
}
void SET_7_A(gbc_cpu *cpu) {
    cpu->registers.b |= 0x80;
    cpu->registers.clk.m = 2;
}
void SET_7_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i |= 0x80;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void RLA(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?1:0;
    u8 co = cpu->registers.a&FLAG_Z?0x10:0;
    cpu->registers.a=(cpu->registers.a<<1)+ci;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 1;
}
void RLCA(gbc_cpu *cpu) {
    u8 ci = cpu->registers.a&FLAG_Z?1:0;
    u8 co = cpu->registers.a&FLAG_Z?FLAG_C:0;
    cpu->registers.a=(cpu->registers.a<<1)+ci;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 1;
}
void RRA(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?FLAG_Z:0;
    u8 co = cpu->registers.a&1?0x10:0;
    cpu->registers.a=(cpu->registers.a>>1)+ci;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 1;
}
void RRCA(gbc_cpu *cpu) {
    u8 ci = cpu->registers.a&1?FLAG_Z:0;
    u8 co = cpu->registers.a&1?FLAG_C:0;
    cpu->registers.a=(cpu->registers.a>>1)+ci;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 1;
}

void RL_B(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?1:0;
    u8 co = cpu->registers.b&FLAG_Z?0x10:0;
    cpu->registers.b=(cpu->registers.b<<1)+ci;
    cpu->registers.f=(cpu->registers.b)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RL_C(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?1:0;
    u8 co = cpu->registers.c&FLAG_Z?0x10:0;
    cpu->registers.c=(cpu->registers.c<<1)+ci;
    cpu->registers.f=(cpu->registers.c)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RL_D(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?1:0;
    u8 co = cpu->registers.d&FLAG_Z?0x10:0;
    cpu->registers.d=(cpu->registers.d<<1)+ci;
    cpu->registers.f=(cpu->registers.d)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RL_E(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?1:0;
    u8 co = cpu->registers.e&FLAG_Z?0x10:0;
    cpu->registers.e=(cpu->registers.e<<1)+ci;
    cpu->registers.f=(cpu->registers.e)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RL_H(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?1:0;
    u8 co = cpu->registers.h&FLAG_Z?0x10:0;
    cpu->registers.h=(cpu->registers.h<<1)+ci;
    cpu->registers.f=(cpu->registers.h)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RL_L(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?1:0;
    u8 co = cpu->registers.l&FLAG_Z?0x10:0;
    cpu->registers.l=(cpu->registers.l<<1)+ci;
    cpu->registers.f=(cpu->registers.l)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RL_A(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?1:0;
    u8 co = cpu->registers.a&FLAG_Z?0x10:0;
    cpu->registers.a=(cpu->registers.a<<1)+ci;
    cpu->registers.f=(cpu->registers.a)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RL_mHL(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    u8 ci = cpu->registers.f&FLAG_C?1:0;
    u8 co = i&FLAG_Z?0x10:0;
    i=(i<<1)+ci;
    i&=255;
    cpu->registers.f=(i)?0:FLAG_Z;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 4;
}

void RLC_B(gbc_cpu *cpu) {
    u8 ci = cpu->registers.b&FLAG_Z?1:0;
    u8 co = cpu->registers.b&FLAG_Z?FLAG_C:0;
    cpu->registers.b=(cpu->registers.b<<1)+ci;
    cpu->registers.f=(cpu->registers.b)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RLC_C(gbc_cpu *cpu) {
    u8 ci = cpu->registers.c&FLAG_Z?1:0;
    u8 co = cpu->registers.c&FLAG_Z?FLAG_C:0;
    cpu->registers.c=(cpu->registers.c<<1)+ci;
    cpu->registers.f=(cpu->registers.c)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RLC_D(gbc_cpu *cpu) {
    u8 ci = cpu->registers.d&FLAG_Z?1:0;
    u8 co = cpu->registers.d&FLAG_Z?FLAG_C:0;
    cpu->registers.d=(cpu->registers.d<<1)+ci;
    cpu->registers.f=(cpu->registers.d)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RLC_E(gbc_cpu *cpu) {
    u8 ci = cpu->registers.e&FLAG_Z?1:0;
    u8 co = cpu->registers.e&FLAG_Z?FLAG_C:0;
    cpu->registers.e=(cpu->registers.e<<1)+ci;
    cpu->registers.f=(cpu->registers.e)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RLC_H(gbc_cpu *cpu) {
    u8 ci = cpu->registers.h&FLAG_Z?1:0;
    u8 co = cpu->registers.h&FLAG_Z?FLAG_C:0;
    cpu->registers.h=(cpu->registers.h<<1)+ci;
    cpu->registers.f=(cpu->registers.h)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RLC_L(gbc_cpu *cpu) {
    u8 ci = cpu->registers.l&FLAG_Z?1:0;
    u8 co = cpu->registers.l&FLAG_Z?FLAG_C:0;
    cpu->registers.l=(cpu->registers.l<<1)+ci;
    cpu->registers.f=(cpu->registers.l)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RLC_A(gbc_cpu *cpu) {
    u8 ci = cpu->registers.a&FLAG_Z?1:0;
    u8 co = cpu->registers.a&FLAG_Z?FLAG_C:0;
    cpu->registers.a=(cpu->registers.a<<1)+ci;
    cpu->registers.f=(cpu->registers.a)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RLC_mHL(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    u8 ci = i&FLAG_Z?1:0;
    u8 co = i&FLAG_Z?FLAG_C:0;
    i=(i<<1)+ci;
    i&=255;
    cpu->registers.f=(i)?0:FLAG_Z;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 4;
}

void RR_B(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?FLAG_Z:0;
    u8 co = cpu->registers.b&1?0x10:0;
    cpu->registers.b=(cpu->registers.b>>1)+ci;
    cpu->registers.f=(cpu->registers.b)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RR_C(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?FLAG_Z:0;
    u8 co = cpu->registers.c&1?0x10:0;
    cpu->registers.c=(cpu->registers.c>>1)+ci;
    cpu->registers.f=(cpu->registers.c)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RR_D(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?FLAG_Z:0;
    u8 co = cpu->registers.d&1?0x10:0;
    cpu->registers.d=(cpu->registers.d>>1)+ci;
    cpu->registers.f=(cpu->registers.d)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RR_E(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?FLAG_Z:0;
    u8 co = cpu->registers.e&1?0x10:0;
    cpu->registers.e=(cpu->registers.e>>1)+ci;
    cpu->registers.f=(cpu->registers.e)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RR_H(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?FLAG_Z:0;
    u8 co = cpu->registers.h&1?0x10:0;
    cpu->registers.h=(cpu->registers.h>>1)+ci;
    cpu->registers.f=(cpu->registers.h)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RR_L(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?FLAG_Z:0;
    u8 co = cpu->registers.l&1?0x10:0;
    cpu->registers.l=(cpu->registers.l>>1)+ci;
    cpu->registers.f=(cpu->registers.l)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RR_A(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?FLAG_Z:0;
    u8 co = cpu->registers.a&1?0x10:0;
    cpu->registers.a=(cpu->registers.a>>1)+ci;
    cpu->registers.f=(cpu->registers.a)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RR_mHL(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    u8 ci = cpu->registers.f&FLAG_C?FLAG_Z:0;
    u8 co = i&1?0x10:0;
    i=(i>>1)+ci;
    i&=255;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.f=(i)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 4;
}

void RRC_B(gbc_cpu *cpu) {
    u8 ci = cpu->registers.b&1?FLAG_Z:0;
    u8 co = cpu->registers.b&1?FLAG_C:0;
    cpu->registers.b=(cpu->registers.b>>1)+ci;
    cpu->registers.f=(cpu->registers.b)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RRC_C(gbc_cpu *cpu) {
    u8 ci = cpu->registers.c&1?FLAG_Z:0;
    u8 co = cpu->registers.c&1?FLAG_C:0;
    cpu->registers.c=(cpu->registers.c>>1)+ci;
    cpu->registers.f=(cpu->registers.c)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RRC_D(gbc_cpu *cpu) {
    u8 ci = cpu->registers.d&1?FLAG_Z:0;
    u8 co = cpu->registers.d&1?FLAG_C:0;
    cpu->registers.d=(cpu->registers.d>>1)+ci;
    cpu->registers.f=(cpu->registers.d)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RRC_E(gbc_cpu *cpu) {
    u8 ci = cpu->registers.e&1?FLAG_Z:0;
    u8 co = cpu->registers.e&1?FLAG_C:0;
    cpu->registers.e=(cpu->registers.e>>1)+ci;
    cpu->registers.f=(cpu->registers.e)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RRC_H(gbc_cpu *cpu) {
    u8 ci = cpu->registers.h&1?FLAG_Z:0;
    u8 co = cpu->registers.h&1?FLAG_C:0;
    cpu->registers.h=(cpu->registers.h>>1)+ci;
    cpu->registers.f=(cpu->registers.h)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RRC_L(gbc_cpu *cpu) {
    u8 ci = cpu->registers.l&1?FLAG_Z:0;
    u8 co = cpu->registers.l&1?FLAG_C:0;
    cpu->registers.l=(cpu->registers.l>>1)+ci;
    cpu->registers.f=(cpu->registers.l)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RRC_A(gbc_cpu *cpu) {
    u8 ci = cpu->registers.a&1?FLAG_Z:0;
    u8 co = cpu->registers.a&1?FLAG_C:0;
    cpu->registers.a=(cpu->registers.a>>1)+ci;
    cpu->registers.f=(cpu->registers.a)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RRC_mHL(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    u8 ci = i&1?FLAG_Z:0;
    u8 co = i&1?FLAG_C:0;
    i=(i>>1)+ci;
    i&=255;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.f=(i)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 4;
}

void SLA_B(gbc_cpu *cpu) {
    u8 co = cpu->registers.b&FLAG_Z?FLAG_C:0;
    cpu->registers.b=(cpu->registers.b<<1)&255;
    cpu->registers.f=(cpu->registers.b)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLA_C(gbc_cpu *cpu) {
    u8 co = cpu->registers.c&FLAG_Z?FLAG_C:0;
    cpu->registers.c=(cpu->registers.c<<1)&255;
    cpu->registers.f=(cpu->registers.c)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLA_D(gbc_cpu *cpu) {
    u8 co = cpu->registers.d&FLAG_Z?FLAG_C:0;
    cpu->registers.d=(cpu->registers.d<<1)&255;
    cpu->registers.f=(cpu->registers.d)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLA_E(gbc_cpu *cpu) {
    u8 co = cpu->registers.e&FLAG_Z?FLAG_C:0;
    cpu->registers.e=(cpu->registers.e<<1)&255;
    cpu->registers.f=(cpu->registers.e)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLA_H(gbc_cpu *cpu) {
    u8 co = cpu->registers.h&FLAG_Z?FLAG_C:0;
    cpu->registers.h=(cpu->registers.h<<1)&255;
    cpu->registers.f=(cpu->registers.h)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLA_L(gbc_cpu *cpu) {
    u8 co = cpu->registers.l&FLAG_Z?FLAG_C:0;
    cpu->registers.l=(cpu->registers.l<<1)&255;
    cpu->registers.f=(cpu->registers.l)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLA_A(gbc_cpu *cpu) {
    u8 co = cpu->registers.a&FLAG_Z?FLAG_C:0;
    cpu->registers.a=(cpu->registers.a<<1)&255;
    cpu->registers.f=(cpu->registers.a)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}

void SLL_B(gbc_cpu *cpu) {
    u8 co = cpu->registers.b&FLAG_Z?FLAG_C:0;
    cpu->registers.b=(cpu->registers.b<<1)&255+1;
    cpu->registers.f=(cpu->registers.b)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLL_C(gbc_cpu *cpu) {
    u8 co = cpu->registers.c&FLAG_Z?FLAG_C:0;
    cpu->registers.c=(cpu->registers.c<<1)&255+1;
    cpu->registers.f=(cpu->registers.c)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLL_D(gbc_cpu *cpu) {
    u8 co = cpu->registers.d&FLAG_Z?FLAG_C:0;
    cpu->registers.d=(cpu->registers.d<<1)&255+1;
    cpu->registers.f=(cpu->registers.d)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLL_E(gbc_cpu *cpu) {
    u8 co = cpu->registers.e&FLAG_Z?FLAG_C:0;
    cpu->registers.e=(cpu->registers.e<<1)&255+1;
    cpu->registers.f=(cpu->registers.e)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLL_H(gbc_cpu *cpu) {
    u8 co = cpu->registers.h&FLAG_Z?FLAG_C:0;
    cpu->registers.h=(cpu->registers.h<<1)&255+1;
    cpu->registers.f=(cpu->registers.h)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLL_L(gbc_cpu *cpu) {
    u8 co = cpu->registers.l&FLAG_Z?FLAG_C:0;
    cpu->registers.l=(cpu->registers.l<<1)&255+1;
    cpu->registers.f=(cpu->registers.l)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLL_A(gbc_cpu *cpu) {
    u8 co = cpu->registers.a&FLAG_Z?FLAG_C:0;
    cpu->registers.a=(cpu->registers.a<<1)&255+1;
    cpu->registers.f=(cpu->registers.a)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}

void SRA_B(gbc_cpu *cpu) {
    u8 ci = cpu->registers.b&FLAG_Z;
    u8 co = cpu->registers.b&1?FLAG_C:0;
    cpu->registers.b=((cpu->registers.b>>1)+ci)&255;
    cpu->registers.f=(cpu->registers.b)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRA_C(gbc_cpu *cpu) {
    u8 ci = cpu->registers.c&FLAG_Z;
    u8 co = cpu->registers.c&1?FLAG_C:0;
    cpu->registers.c=((cpu->registers.c>>1)+ci)&255;
    cpu->registers.f=(cpu->registers.c)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRA_D(gbc_cpu *cpu) {
    u8 ci = cpu->registers.d&FLAG_Z;
    u8 co = cpu->registers.d&1?FLAG_C:0;
    cpu->registers.d=((cpu->registers.d>>1)+ci)&255;
    cpu->registers.f=(cpu->registers.d)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRA_E(gbc_cpu *cpu) {
    u8 ci = cpu->registers.e&FLAG_Z;
    u8 co = cpu->registers.e&1?FLAG_C:0;
    cpu->registers.e=((cpu->registers.e>>1)+ci)&255;
    cpu->registers.f=(cpu->registers.e)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRA_H(gbc_cpu *cpu) {
    u8 ci = cpu->registers.h&FLAG_Z;
    u8 co = cpu->registers.h&1?FLAG_C:0;
    cpu->registers.h=((cpu->registers.h>>1)+ci)&255;
    cpu->registers.f=(cpu->registers.h)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRA_L(gbc_cpu *cpu) {
    u8 ci = cpu->registers.l&FLAG_Z;
    u8 co = cpu->registers.l&1?FLAG_C:0;
    cpu->registers.l=((cpu->registers.l>>1)+ci)&255;
    cpu->registers.f=(cpu->registers.l)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRA_A(gbc_cpu *cpu) {
    u8 ci = cpu->registers.a&FLAG_Z;
    u8 co = cpu->registers.a&1?FLAG_C:0;
    cpu->registers.a=((cpu->registers.a>>1)+ci)&255;
    cpu->registers.f=(cpu->registers.a)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}

void SRL_B(gbc_cpu *cpu) {
    u8 co = cpu->registers.b&1?FLAG_C:0;
    cpu->registers.b=(cpu->registers.b>>1)&255;
    cpu->registers.f=(cpu->registers.b)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRL_C(gbc_cpu *cpu) {
    u8 co = cpu->registers.c&1?FLAG_C:0;
    cpu->registers.c=(cpu->registers.c>>1)&255;
    cpu->registers.f=(cpu->registers.c)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRL_D(gbc_cpu *cpu) {
    u8 co = cpu->registers.d&1?FLAG_C:0;
    cpu->registers.d=(cpu->registers.d>>1)&255;
    cpu->registers.f=(cpu->registers.d)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRL_E(gbc_cpu *cpu) {
    u8 co = cpu->registers.e&1?FLAG_C:0;
    cpu->registers.e=(cpu->registers.e>>1)&255;
    cpu->registers.f=(cpu->registers.e)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRL_H(gbc_cpu *cpu) {
    u8 co = cpu->registers.h&1?FLAG_C:0;
    cpu->registers.h=(cpu->registers.h>>1)&255;
    cpu->registers.f=(cpu->registers.h)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRL_L(gbc_cpu *cpu) {
    u8 co = cpu->registers.l&1?FLAG_C:0;
    cpu->registers.l=(cpu->registers.l>>1)&255;
    cpu->registers.f=(cpu->registers.l)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRL_A(gbc_cpu *cpu) {
    u8 co = cpu->registers.a&1?FLAG_C:0;
    cpu->registers.a=(cpu->registers.a>>1)&255;
    cpu->registers.f=(cpu->registers.a)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}

void CPL(gbc_cpu *cpu) {
    cpu->registers.a ^= 255;
    cpu->registers.f = cpu->registers.a?0:FLAG_Z;
    cpu->registers.clk.m = 1;
}
void NEG(gbc_cpu *cpu) {
    cpu->registers.a = 0-cpu->registers.a;
    cpu->registers.f=(cpu->registers.a<0)?FLAG_C:0;
    if(!cpu->registers.a) cpu->registers.f|=FLAG_Z;
    cpu->registers.clk.m = 2;
}

void CCF(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?0:0x10;
    cpu->registers.f=(cpu->registers.f&0xEF)+ci;
    cpu->registers.clk.m = 1;
}
void SCF(gbc_cpu *cpu) {
    cpu->registers.f|=FLAG_C;
    cpu->registers.clk.m = 1;
}

void PUSH_BC(gbc_cpu *cpu) {
    cpu->registers.sp--;
    write_u8(cpu->mmu,cpu->registers.sp,cpu->registers.b);
    cpu->registers.sp--;
    write_u8(cpu->mmu,cpu->registers.sp,cpu->registers.c);
    cpu->registers.clk.m = 3;
}
void PUSH_DE(gbc_cpu *cpu) {
    cpu->registers.sp--;
    write_u8(cpu->mmu,cpu->registers.sp,cpu->registers.d);
    cpu->registers.sp--;
    write_u8(cpu->mmu,cpu->registers.sp,cpu->registers.e);
    cpu->registers.clk.m = 3;
}
void PUSH_HL(gbc_cpu *cpu) {
    cpu->registers.sp--;
    write_u8(cpu->mmu,cpu->registers.sp,cpu->registers.h);
    cpu->registers.sp--;
    write_u8(cpu->mmu,cpu->registers.sp,cpu->registers.l);
    cpu->registers.clk.m = 3;
}
void PUSH_AF(gbc_cpu *cpu) {
    cpu->registers.sp--;
    write_u8(cpu->mmu,cpu->registers.sp,cpu->registers.a);
    cpu->registers.sp--;
    write_u8(cpu->mmu,cpu->registers.sp,cpu->registers.f);
    cpu->registers.clk.m = 3;
}

void POP_BC(gbc_cpu *cpu) {
    cpu->registers.c = read_u8(cpu->mmu,cpu->registers.sp++);
    cpu->registers.b = read_u8(cpu->mmu,cpu->registers.sp++);
    cpu->registers.clk.m = 3;
}
void POP_DE(gbc_cpu *cpu) {
    cpu->registers.e = read_u8(cpu->mmu,cpu->registers.sp++);
    cpu->registers.d = read_u8(cpu->mmu,cpu->registers.sp++);
    cpu->registers.clk.m = 3;
}
void POP_HL(gbc_cpu *cpu) {
    cpu->registers.l = read_u8(cpu->mmu,cpu->registers.sp++);
    cpu->registers.h = read_u8(cpu->mmu,cpu->registers.sp++);
    cpu->registers.clk.m = 3;
}
void POP_AF(gbc_cpu *cpu) {
    cpu->registers.f = read_u8(cpu->mmu,cpu->registers.sp++);
    cpu->registers.a = read_u8(cpu->mmu,cpu->registers.sp++);
    cpu->registers.clk.m = 3;
}

void JP_a16(gbc_cpu *cpu) {
    cpu->registers.pc = read_u16(cpu->mmu,cpu->registers.pc);
    cpu->registers.clk.m = 3;
}
void JP_HL(gbc_cpu *cpu) {
    cpu->registers.pc=(cpu->registers.h<<8)+cpu->registers.l;
    cpu->registers.clk.m = 1;
}
void JP_NZ_a16(gbc_cpu *cpu) {
    cpu->registers.clk.m = 3;
    if(!flag_z(cpu)) {
        cpu->registers.pc = read_u16(cpu->mmu,cpu->registers.pc);
        cpu->registers.clk.m++;
    } else cpu->registers.pc += 2;
}
void JP_Cnn(gbc_cpu *cpu) {
    cpu->registers.clk.m = 3;
    if(flag_c(cpu)) {
        cpu->registers.pc = read_u16(cpu->mmu,cpu->registers.pc);
        cpu->registers.clk.m++;
    } else cpu->registers.pc += 2;
}
void JR_r8(gbc_cpu *cpu) {
    s8 temp = read_u8(cpu->mmu, cpu->registers.pc++);
    cpu->registers.pc += temp;
    cpu->registers.clk.m += 4;
}
void JR_NZ_r8(gbc_cpu *cpu) {
    if(!flag_z(cpu)) {
    /*if(flag_nz(cpu)) {*/
        s8 temp = read_u8(cpu->mmu,cpu->registers.pc);
        cpu->registers.pc++;
        cpu->registers.pc += temp;
        cpu->registers.clk.m += 4;
    } else {
        cpu->registers.pc++;
    }
}
void JR_Z_r8(gbc_cpu *cpu)  {
    if(flag_z(cpu)){
        s8 temp = read_u8(cpu->mmu, cpu->registers.pc++);
        cpu->registers.pc += temp;
        cpu->registers.clk.m += 4;
    } else {
        cpu->registers.pc++;
    }
}
void JR_NC_r8(gbc_cpu *cpu) {
    s8 i = read_u8(cpu->mmu,cpu->registers.pc);
    /*if(i>127) i=-((~i+1)&255);*/

    cpu->registers.pc++;
    cpu->registers.clk.m = 2;

    if(!flag_c(cpu)) {
        cpu->registers.pc+=i;
        cpu->registers.clk.m++;
    }
}

void JR_C_r8(gbc_cpu *cpu)  {
    s8 i = read_u8(cpu->mmu,cpu->registers.pc);
    /*if(i>127) i=-((~i+1)&255);*/
    cpu->registers.pc++;
    cpu->registers.clk.m = 2;

    if(flag_c(cpu)) {
        cpu->registers.pc += i;
        cpu->registers.clk.m++;
    }
}

void CALL_a16(gbc_cpu *cpu) {
    u16 addr = read_u8(cpu->mmu, cpu->registers.pc++);
    addr |= read_u8(cpu->mmu, cpu->registers.pc++) << 8;
    write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc >> 8);
    write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc & 0xFF);
    cpu->registers.pc = addr;
}

void CALL_NZ_a16(gbc_cpu *cpu) {
    cpu->registers.clk.m = 3;
    if(!flag_z(cpu)) {
        u16 temp = read_u8(cpu->mmu, cpu->registers.pc++);
        temp |= read_u8(cpu->mmu, cpu->registers.pc++) << 8;
        write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc >> 8);
        write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc & 0xFF);
        cpu->registers.pc = temp;
        cpu->registers.clk.m += 12;
    } else cpu->registers.pc += 2;
}

void CALL_Z_a16(gbc_cpu *cpu) {
    cpu->registers.clk.m = 3;

    if(flag_z(cpu)) {
        u16 temp = read_u8(cpu->mmu, cpu->registers.pc++);
        temp |= read_u8(cpu->mmu, cpu->registers.pc++) << 8;
        write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc >> 8);
        write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc & 0xFF);
        cpu->registers.pc = temp;
        cpu->registers.clk.m += 12;

    } else cpu->registers.pc += 2;
}

void CALL_NC_a16(gbc_cpu *cpu) {
    cpu->registers.clk.m = 3;
    if(!flag_c(cpu)) {
        u16 temp = read_u8(cpu->mmu, cpu->registers.pc++);
        temp |= read_u8(cpu->mmu, cpu->registers.pc++) << 8;
        write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc >> 8);
        write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc & 0xFF);
        cpu->registers.pc = temp;
        cpu->registers.clk.m += 12;
    } else cpu->registers.pc += 2;
}

void CALL_C_a16(gbc_cpu *cpu) {
    cpu->registers.clk.m = 3;
    if(flag_c(cpu)) {
        u16 temp = read_u8(cpu->mmu, cpu->registers.pc++);
        temp |= read_u8(cpu->mmu, cpu->registers.pc++) << 8;
        write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc >> 8);
        write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc & 0xFF);
        cpu->registers.pc = temp;
        cpu->registers.clk.m += 12;
    } else cpu->registers.pc += 2;
}

void RET(gbc_cpu *cpu) {
    u16 temp = read_u8(cpu->mmu, cpu->registers.sp++);
    temp |= read_u8(cpu->mmu, cpu->registers.sp++) << 8;

    cpu->registers.pc = temp;
    cpu->registers.clk.m = 3;
}

void JP_C_a16(gbc_cpu *cpu) {
    cpu->registers.clk.m = 3;
    if(flag_c(cpu)) {
        cpu->registers.pc = read_u16(cpu->mmu,cpu->registers.pc);
        cpu->registers.clk.m++;
    } else cpu->registers.pc += 2;
}
void JP_Z_a16(gbc_cpu *cpu) {
    cpu->registers.clk.m = 3;
    if(flag_z(cpu)) {
        cpu->registers.pc = read_u16(cpu->mmu,cpu->registers.pc);
        cpu->registers.clk.m++;
    } else cpu->registers.pc += 2;
}

void JP_NC_a16(gbc_cpu *cpu) {
    if(!flag_c(cpu)) {
        u16 temp = read_u8(cpu->mmu, cpu->registers.pc++);
        temp |=  read_u8(cpu->mmu, cpu->registers.pc++) << 8;
        cpu->registers.pc = temp;
        cpu->registers.clk.m += 4;
    }
    else
        cpu->registers.pc += 2;
}

void RET_I(gbc_cpu *cpu) {
    rrs(cpu);
    cpu->registers.pc = read_u16(cpu->mmu,cpu->registers.sp);
    cpu->IME = 1;
    cpu->registers.sp+=2;
    cpu->registers.clk.m = 3;
}
void RET_NZ(gbc_cpu *cpu) {
    cpu->registers.clk.m = 1;
    if (!flag_z(cpu)) {
        cpu->registers.pc = read_u16(cpu->mmu,cpu->registers.sp);
        cpu->registers.sp+=2;
        cpu->registers.clk.m+=2;
    } }
void RET_Z(gbc_cpu *cpu) {
    cpu->registers.clk.m = 1;
    if (flag_z(cpu)) {
        cpu->registers.pc = read_u16(cpu->mmu,cpu->registers.sp);
        cpu->registers.sp+=2;
        cpu->registers.clk.m+=2;
    } }
void RET_NC(gbc_cpu *cpu) {
    cpu->registers.clk.m = 1;
    if (!flag_c(cpu)) {
        cpu->registers.pc = read_u16(cpu->mmu,cpu->registers.sp);
        cpu->registers.sp+=2;
        cpu->registers.clk.m+=2;
    } }
void RET_C(gbc_cpu *cpu) {
    cpu->registers.clk.m = 1;
    if (flag_c(cpu)) {
        cpu->registers.pc = read_u16(cpu->mmu,cpu->registers.sp);
        cpu->registers.sp+=2;
        cpu->registers.clk.m+=2;
    } }

void RST_00H(gbc_cpu *cpu) {
    rsv(cpu);
    cpu->registers.sp-=2;
    write_u16(cpu->mmu,cpu->registers.sp,cpu->registers.pc);
    cpu->registers.pc = 0x00;
    cpu->registers.clk.m = 3;
}
void RST_08H(gbc_cpu *cpu) {
    rsv(cpu);
    cpu->registers.sp-=2;
    write_u16(cpu->mmu,cpu->registers.sp,cpu->registers.pc);
    cpu->registers.pc = 0x08;
    cpu->registers.clk.m = 3;
}
void RST_10H(gbc_cpu *cpu) {
    rsv(cpu);
    cpu->registers.sp-=2;
    write_u16(cpu->mmu,cpu->registers.sp,cpu->registers.pc);
    cpu->registers.pc = 0x10;
    cpu->registers.clk.m = 3;
}
void RST_18H(gbc_cpu *cpu) {
    rsv(cpu);
    cpu->registers.sp-=2;
    write_u16(cpu->mmu,cpu->registers.sp,cpu->registers.pc);
    cpu->registers.pc = 0x18;
    cpu->registers.clk.m = 3;
}
void RST_20H(gbc_cpu *cpu) {
    rsv(cpu);
    cpu->registers.sp-=2;
    write_u16(cpu->mmu,cpu->registers.sp,cpu->registers.pc);
    cpu->registers.pc = 0x20;
    cpu->registers.clk.m = 3;
}
void RST_28H(gbc_cpu *cpu) {
    rsv(cpu);
    cpu->registers.sp-=2;
    write_u16(cpu->mmu,cpu->registers.sp,cpu->registers.pc);
    cpu->registers.pc = 0x28;
    cpu->registers.clk.m = 3;
}
void RST_30H(gbc_cpu *cpu) {
    rsv(cpu);
    cpu->registers.sp-=2;
    write_u16(cpu->mmu,cpu->registers.sp,cpu->registers.pc);
    cpu->registers.pc = 0x30;
    cpu->registers.clk.m = 3;
}
void RST_38H(gbc_cpu *cpu) {
    rsv(cpu);
    cpu->registers.sp -= 2;
    write_u16(cpu->mmu,cpu->registers.sp,cpu->registers.pc);
    cpu->registers.pc = 0x38;
    cpu->registers.clk.m = 3;
}

void NOP(gbc_cpu *cpu) {
    cpu->registers.clk.m = 1;
}

void HALT(gbc_cpu *cpu) {
    cpu->HALT =1;
    cpu->registers.clk.m = 1;
}
void DI(gbc_cpu *cpu) {
    cpu->IME = 0;
    cpu->registers.clk.m = 1;
}
void EI(gbc_cpu *cpu) {
    cpu->IME = 1;
    cpu->registers.clk.m = 1;
}

void rsv(gbc_cpu *cpu) {
    cpu->rsv.a = cpu->registers.a;
    cpu->rsv.b = cpu->registers.b;
    cpu->rsv.c = cpu->registers.c;
    cpu->rsv.d = cpu->registers.d;
    cpu->rsv.e = cpu->registers.e;
    cpu->rsv.f = cpu->registers.f;
    cpu->rsv.h = cpu->registers.h;
    cpu->rsv.l = cpu->registers.l;
}

void rrs(gbc_cpu *cpu) {
    cpu->registers.a = cpu->rsv.a;
    cpu->registers.b = cpu->rsv.b;
    cpu->registers.c = cpu->rsv.c;
    cpu->registers.d = cpu->rsv.d;
    cpu->registers.e = cpu->rsv.e;
    cpu->registers.f = cpu->rsv.f;
    cpu->registers.h = cpu->rsv.h;
    cpu->registers.l = cpu->rsv.l;
}

void MAPcb(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu, cpu->registers.pc++);
    cpu->registers.pc &= 65535;
    if(CB_OPS[i]) CB_OPS[i](cpu);
}

void XX(gbc_cpu *cpu) {
    /*u8 opcode = read_u8(cpu->mmu, cpu->registers.pc-1);
    */
    /*printf("ERROR: OPCODE UNIMPLEMETED %x?\n", opcode);
    */
}

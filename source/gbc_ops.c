#include <stdio.h>

#include "gbc_ops.h"
#include "text.h"
#include "console.h"

// pointers to make the ops more concise
u8 *a, *b, *c, *d, *e, *f, *h, *l;
u8 *pc, *sp;
int *m;

void execute_init(gbc_cpu *cpu) { //
    a = &cpu->registers.a;
    b = &cpu->registers.b;
    c = &cpu->registers.c;
    d = &cpu->registers.d;
    e = &cpu->registers.e;
    f = &cpu->registers.f;
    h = &cpu->registers.h;
    l = &cpu->registers.l;
    m = &cpu->registers.clk.m;

    pc = &cpu->registers.pc;
    sp = &cpu->registers.sp;
}

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
void LD_A_d8(gbc_cpu *cpu) { *a=read_u8(cpu->mmu, *pc); (*pc)++; *m=2; };
void LD_B_d8(gbc_cpu *cpu) { *b=read_u8(cpu->mmu, *pc); (*pc)++; *m=2; };
void LD_C_d8(gbc_cpu *cpu) { *c=read_u8(cpu->mmu, *pc); (*pc)++; *m=2; };
void LD_D_d8(gbc_cpu *cpu) { *d=read_u8(cpu->mmu, *pc); (*pc)++; *m=2; };
void LD_E_d8(gbc_cpu *cpu) { *e=read_u8(cpu->mmu, *pc); (*pc)++; *m=2; };
void LD_H_d8(gbc_cpu *cpu) { *h=read_u8(cpu->mmu, *pc); (*pc)++; *m=2; };
void LD_L_d8(gbc_cpu *cpu) { *l=read_u8(cpu->mmu, *pc); (*pc)++; *m=2; };

// LD r1, r2 funcs
void LD_A_A(gbc_cpu *cpu) { *a = *a; *m=1; };
void LD_A_B(gbc_cpu *cpu) { *a = *b; *m=1; };
void LD_A_C(gbc_cpu *cpu) { *a = *c; *m=1; };
void LD_A_D(gbc_cpu *cpu) { *a = *d; *m=1; };
void LD_A_E(gbc_cpu *cpu) { *a = *e; *m=1; };
void LD_A_H(gbc_cpu *cpu) { *a = *h; *m=1; };
void LD_A_L(gbc_cpu *cpu) { *a = *l; *m=1; };

void LD_B_A(gbc_cpu *cpu) { *b = *a; *m=1; };
void LD_B_B(gbc_cpu *cpu) { *b = *b; *m=1; };
void LD_B_C(gbc_cpu *cpu) { *b = *c; *m=1; };
void LD_B_D(gbc_cpu *cpu) { *b = *d; *m=1; };
void LD_B_E(gbc_cpu *cpu) { *b = *e; *m=1; };
void LD_B_H(gbc_cpu *cpu) { *b = *h; *m=1; };
void LD_B_L(gbc_cpu *cpu) { *b = *l; *m=1; };

void LD_C_A(gbc_cpu *cpu) { *c = *a; *m=1; };
void LD_C_B(gbc_cpu *cpu) { *c = *b; *m=1; };
void LD_C_C(gbc_cpu *cpu) { *c = *c; *m=1; };
void LD_C_D(gbc_cpu *cpu) { *c = *d; *m=1; };
void LD_C_E(gbc_cpu *cpu) { *c = *e; *m=1; };
void LD_C_H(gbc_cpu *cpu) { *c = *h; *m=1; };
void LD_C_L(gbc_cpu *cpu) { *c = *l; *m=1; };

void LD_D_A(gbc_cpu *cpu) { *d = *a; *m=1; };
void LD_D_B(gbc_cpu *cpu) { *d = *b; *m=1; };
void LD_D_C(gbc_cpu *cpu) { *d = *c; *m=1; };
void LD_D_D(gbc_cpu *cpu) { *d = *d; *m=1; };
void LD_D_E(gbc_cpu *cpu) { *d = *e; *m=1; };
void LD_D_H(gbc_cpu *cpu) { *d = *h; *m=1; };
void LD_D_L(gbc_cpu *cpu) { *d = *l; *m=1; };

void LD_E_A(gbc_cpu *cpu) { *e = *a; *m=1; };
void LD_E_B(gbc_cpu *cpu) { *e = *b; *m=1; };
void LD_E_C(gbc_cpu *cpu) { *e = *c; *m=1; };
void LD_E_D(gbc_cpu *cpu) { *e = *d; *m=1; };
void LD_E_E(gbc_cpu *cpu) { *e = *e; *m=1; };
void LD_E_H(gbc_cpu *cpu) { *e = *h; *m=1; };
void LD_E_L(gbc_cpu *cpu) { *e = *l; *m=1; };

void LD_H_A(gbc_cpu *cpu) { *h = *a; *m=1; };
void LD_H_B(gbc_cpu *cpu) { *h = *b; *m=1; };
void LD_H_C(gbc_cpu *cpu) { *h = *c; *m=1; };
void LD_H_D(gbc_cpu *cpu) { *h = *d; *m=1; };
void LD_H_E(gbc_cpu *cpu) { *h = *e; *m=1; };
void LD_H_H(gbc_cpu *cpu) { *h = *h; *m=1; };
void LD_H_L(gbc_cpu *cpu) { *h = *l; *m=1; };

void LD_L_A(gbc_cpu *cpu) { *l = *a; *m=1; };
void LD_L_B(gbc_cpu *cpu) { *l = *b; *m=1; };
void LD_L_C(gbc_cpu *cpu) { *l = *c; *m=1; };
void LD_L_D(gbc_cpu *cpu) { *l = *d; *m=1; };
void LD_L_E(gbc_cpu *cpu) { *l = *e; *m=1; };
void LD_L_H(gbc_cpu *cpu) { *l = *h; *m=1; };
void LD_L_L(gbc_cpu *cpu) { *l = *l; *m=1; };

// load memory value at address HL into register
void LD_A_mHL(gbc_cpu *cpu) { *a=read_u8(cpu->mmu,(*h<<8)+*l); *m=2; };
void LD_B_mHL(gbc_cpu *cpu) { *b=read_u8(cpu->mmu,(*h<<8)+*l); *m=2; };
void LD_C_mHL(gbc_cpu *cpu) { *c=read_u8(cpu->mmu,(*h<<8)+*l); *m=2; };
void LD_D_mHL(gbc_cpu *cpu) { *d=read_u8(cpu->mmu,(*h<<8)+*l); *m=2; };
void LD_E_mHL(gbc_cpu *cpu) { *e=read_u8(cpu->mmu,(*h<<8)+*l); *m=2; };
void LD_H_mHL(gbc_cpu *cpu) { *h=read_u8(cpu->mmu,(*h<<8)+*l); *m=2; };
void LD_L_mHL(gbc_cpu *cpu) { *l=read_u8(cpu->mmu,(*h<<8)+*l); *m=2; };

// load register value into memory at address HL
void LD_mHL_A(gbc_cpu *cpu) { write_u8(cpu->mmu,(*h<<8)+*l,*a); *m=2; };
void LD_mHL_B(gbc_cpu *cpu) { write_u8(cpu->mmu,(*h<<8)+*l,*b); *m=2; };
void LD_mHL_C(gbc_cpu *cpu) { write_u8(cpu->mmu,(*h<<8)+*l,*c); *m=2; };
void LD_mHL_D(gbc_cpu *cpu) { write_u8(cpu->mmu,(*h<<8)+*l,*d); *m=2; };
void LD_mHL_E(gbc_cpu *cpu) { write_u8(cpu->mmu,(*h<<8)+*l,*e); *m=2; };
void LD_mHL_H(gbc_cpu *cpu) { write_u8(cpu->mmu,(*h<<8)+*l,*h); *m=2; };
void LD_mBC_A(gbc_cpu *cpu) { write_u8(cpu->mmu,(*b<<8)+*c, *a); *m=2; };
void LD_mDE_A(gbc_cpu *cpu) { write_u8(cpu->mmu,(*d<<8)+*e, *a); *m=2; };
void LD_mHL_L(gbc_cpu *cpu) { write_u8(cpu->mmu,(*h<<8)+*l,*l); *m=2; };
void LD_mHLI_A(gbc_cpu *cpu) { write_u8(cpu->mmu,(*h<<8)+*l, *a); *l=(*l+1)&255; if(!*l) *h=(*h+1)&255; *m=2; }
void LD_mHLD_A(gbc_cpu *cpu) { write_u8(cpu->mmu,(*h<<8)+*l, *a); *l=(*l-1)&255; if(*l==255) *h=(*h-1)&255; *m=2; };
void LD_mC_A(gbc_cpu *cpu) { write_u8(cpu->mmu,0xFF00+*c,*a); *m=2; };

void LD_HL_d8(gbc_cpu *cpu) { write_u8(cpu->mmu,(*h<<8)+*l, read_u8(cpu->mmu, *pc)); (*pc)++; *m=3; };


/*void LD_d16_A(gbc_cpu *cpu) { write_u8(cpu->mmu, read_u16(cpu->mmu, *pc), *a); (*pc)+=2; *m=4; };*/
/*void LD_A_d16(gbc_cpu *cpu) { *a=read_u8(cpu->mmu, read_u16(cpu->mmu, *pc)); (*pc)+=2; *m=4; };*/

void LD_A_mBC(gbc_cpu *cpu) { *a=read_u8(cpu->mmu,(*b<<8)+*c); *m=2; };
void LD_A_mDE(gbc_cpu *cpu) { *a=read_u8(cpu->mmu,(*d<<8)+*e); *m=2; };

void LD_A_a16(gbc_cpu *cpu) {
	u16 addr = read_u8(cpu, (*pc)++);
	addr |= read_u8(cpu, (*pc)++) << 8;
	*a = read_u8(cpu, addr);
    *m=4;
};

void LD_a16_A(gbc_cpu *cpu) {
	u16 addr = read_u8(cpu->mmu, (*pc)++);
	addr |= read_u8(cpu->mmu, (*pc)++) << 8;
	write_u8(cpu->mmu, addr, *a);
};
void LD_a16_SP(gbc_cpu *cpu) { 
	u16 temp = read_u8(cpu->mmu, (*pc)++);
	temp |= read_u8(cpu->mmu, (*pc)++) << 8;
	write_u8(cpu->mmu, temp++, *sp & 0xFF);
	write_u8(cpu->mmu, temp, *sp >> 8);

    /*write_u8(cpu->mmu,read_u16(cpu->mmu,*pc), *sp);*/
    *m=5;
 };


void LD_BC_d16(gbc_cpu *cpu) { *c=read_u8(cpu->mmu, (*pc)++); *b=read_u8(cpu->mmu, (*pc)++); *m=3; };
void LD_DE_d16(gbc_cpu *cpu) { *e=read_u8(cpu->mmu, (*pc)++); *d=read_u8(cpu->mmu, (*pc)++); *m=3; };
void LD_HL_d16(gbc_cpu *cpu) { *l=read_u8(cpu->mmu, (*pc)++); *h=read_u8(cpu->mmu, (*pc)++); *m=3; };

void LD_SP_d16(gbc_cpu *cpu) { *sp=read_u16(cpu->mmu, *pc); *pc +=2; *m=3; };

void LD_A_mHLI(gbc_cpu *cpu) { *a=read_u8(cpu->mmu,(*h<<8)+*l); *l=(*l+1)&255; if(!*l) *h=(*h+1)&255; *m=2; };

void LD_A_mHLD(gbc_cpu *cpu) { *a=read_u8(cpu->mmu,(*h<<8)+*l); *l=(*l-1)&255; if(*l==255) *h=(*h-1)&255; *m=2; };

void LDH_a8_A(gbc_cpu *cpu) { write_u8(cpu->mmu,0xFF00+read_u8(cpu->mmu,*pc),*a); (*pc)++; *m=3; };
void LDH_A_a8(gbc_cpu *cpu) { *a=read_u8(cpu->mmu,0xFF00+read_u8(cpu->mmu,*pc)); (*pc)++; *m=3; };
void LD_HL_SP_r8(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,*pc); if(i>127) i=-((~i+1)&255); (*pc)++; i+=*sp; *h=(i>>8)&255; *l=i&255; *m=3; };
void LD_A_mC(gbc_cpu *cpu) { *a=read_u8(cpu->mmu,0xFF00+*c); *m=2; };

void SWAP_A(gbc_cpu *cpu) { u8 tr=*a; *a=((tr&0xF)<<4)|((tr&0xF0)>>4); *f=*a?0:FLAG_Z; *m=1; };
void SWAP_B(gbc_cpu *cpu) { u8 tr=*b; *b=((tr&0xF)<<4)|((tr&0xF0)>>4); *f=*b?0:FLAG_Z; *m=1; };
void SWAP_C(gbc_cpu *cpu) { u8 tr=*c; *c=((tr&0xF)<<4)|((tr&0xF0)>>4); *f=*c?0:FLAG_Z; *m=1; };
void SWAP_D(gbc_cpu *cpu) { u8 tr=*d; *d=((tr&0xF)<<4)|((tr&0xF0)>>4); *f=*d?0:FLAG_Z; *m=1; };
void SWAP_E(gbc_cpu *cpu) { u8 tr=*e; *e=((tr&0xF)<<4)|((tr&0xF0)>>4); *f=*e?0:FLAG_Z; *m=1; };
void SWAP_H(gbc_cpu *cpu) { u8 tr=*h; *h=((tr&0xF)<<4)|((tr&0xF0)>>4); *f=*h?0:FLAG_Z; *m=1; };
void SWAP_L(gbc_cpu *cpu) { u8 tr=*l; *l=((tr&0xF)<<4)|((tr&0xF0)>>4); *f=*l?0:FLAG_Z; *m=1; };

void ADD_A(gbc_cpu *cpu) { u8 i=*a; *a+=*a; *f=(*a>255)?FLAG_C:0; if(!*a) *f|=FLAG_Z; if((*a^*a^i)&0x10) *f|=FLAG_H; *m=1; };
void ADD_B(gbc_cpu *cpu) { u8 i=*a; *a+=*b; *f=(*a>255)?FLAG_C:0; if(!*a) *f|=FLAG_Z; if((*a^*b^i)&0x10) *f|=FLAG_H; *m=1; };
void ADD_C(gbc_cpu *cpu) { u8 i=*a; *a+=*c; *f=(*a>255)?FLAG_C:0; if(!*a) *f|=FLAG_Z; if((*a^*c^i)&0x10) *f|=FLAG_H; *m=1; };
void ADD_D(gbc_cpu *cpu) { u8 i=*a; *a+=*d; *f=(*a>255)?FLAG_C:0; if(!*a) *f|=FLAG_Z; if((*a^*d^i)&0x10) *f|=FLAG_H; *m=1; };
void ADD_E(gbc_cpu *cpu) { u8 i=*a; *a+=*e; *f=(*a>255)?FLAG_C:0; if(!*a) *f|=FLAG_Z; if((*a^*e^i)&0x10) *f|=FLAG_H; *m=1; };
void ADD_H(gbc_cpu *cpu) { u8 i=*a; *a+=*h; *f=(*a>255)?FLAG_C:0; if(!*a) *f|=FLAG_Z; if((*a^*h^i)&0x10) *f|=FLAG_H; *m=1; };
void ADD_L(gbc_cpu *cpu) { u8 i=*a; *a+=*l; *f=(*a>255)?FLAG_C:0; if(!*a) *f|=FLAG_Z; if((*a^*l^i)&0x10) *f|=FLAG_H; *m=1; };
void ADD_A_mHL(gbc_cpu *cpu) {
	u8 hl = read_u8(cpu->mmu, (*h<<8)+*l);

	u16 temp = *a + hl;
	put_f(cpu, FLAG_Z, ((temp & 0xFF) == 0x00));
	unset_f(cpu, FLAG_N);
    put_f(cpu, FLAG_H, (*a ^ hl ^ temp) & 0x10);
    put_f(cpu, FLAG_C, (temp & 0xFF00));
	*a = (temp & 0xFF);
    /*u8 i=*a;*/
    /*u8 r=read_u8(cpu->mmu,(*h<<8)+*l);*/
    /**a+=r;*/
    /**f=(*a>255)?FLAG_C:0;*/
    /*if(!*a) *f|=FLAG_Z;*/
    /*if((*a^i^r)&0x10) *f|=FLAG_H;*/
    *m=2;
};

void ADD_d8(gbc_cpu *cpu) { u8 i=*a; u8 r=read_u8(cpu->mmu,*pc); *a+=r; (*pc)++; *f=(*a>255)?FLAG_C:0; if(!*a) *f|=FLAG_Z; if((*a^i^r)&0x10) *f|=FLAG_H; *m=2; };

void ADD_HL_BC(gbc_cpu *cpu) { u16 hl=(*h<<8)+*l; hl+=(*b<<8)+*c; if(hl>65535) *f|=FLAG_C; else *f&=0xEF; *h=(hl>>8)&255; *l=hl&255; *m=3; };
void ADD_HL_DE(gbc_cpu *cpu) { u16 hl=(*h<<8)+*l; hl+=(*d<<8)+*e; if(hl>65535) *f|=FLAG_C; else *f&=0xEF; *h=(hl>>8)&255; *l=hl&255; *m=3; };
void ADD_HL_HL(gbc_cpu *cpu) { u16 hl=(*h<<8)+*l; hl+=(*h<<8)+*l; if(hl>65535) *f|=FLAG_C; else *f&=0xEF; *h=(hl>>8)&255; *l=hl&255; *m=3; };
void ADD_HL_SP(gbc_cpu *cpu) { u16 hl=(*h<<8)+*l; hl+=*sp; if(hl>65535) *f|=FLAG_C; else *f&=0xEF; *h=(hl>>8)&255; *l=hl&255; *m=3; };
void ADD_SP_d8(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,*pc); if(i>127) i=-((~i+1)&255); (*pc)++; (*sp)+=i; *m=4; };

// ADC_A_X
void ADC_A(gbc_cpu *cpu) { u8 i=*a; *a+=*a; *a+=(*f&FLAG_C)?1:0; *f=(*a>255)?0x10:0; if(!*a) *f|=FLAG_Z; if((*a^*a^i)&0x10) *f|=FLAG_H; *m=1; };
void ADC_B(gbc_cpu *cpu) { u8 i=*a; *a+=*b; *a+=(*f&FLAG_C)?1:0; *f=(*a>255)?0x10:0; if(!*a) *f|=FLAG_Z; if((*a^*b^i)&0x10) *f|=FLAG_H; *m=1; };
void ADC_C(gbc_cpu *cpu) { u8 i=*a; *a+=*c; *a+=(*f&FLAG_C)?1:0; *f=(*a>255)?0x10:0; if(!*a) *f|=FLAG_Z; if((*a^*c^i)&0x10) *f|=FLAG_H; *m=1; };
void ADC_D(gbc_cpu *cpu) { u8 i=*a; *a+=*d; *a+=(*f&FLAG_C)?1:0; *f=(*a>255)?0x10:0; if(!*a) *f|=FLAG_Z; if((*a^*d^i)&0x10) *f|=FLAG_H; *m=1; };
void ADC_E(gbc_cpu *cpu) { u8 i=*a; *a+=*e; *a+=(*f&FLAG_C)?1:0; *f=(*a>255)?0x10:0; if(!*a) *f|=FLAG_Z; if((*a^*e^i)&0x10) *f|=FLAG_H; *m=1; };
void ADC_H(gbc_cpu *cpu) { u8 i=*a; *a+=*h; *a+=(*f&FLAG_C)?1:0; *f=(*a>255)?0x10:0; if(!*a) *f|=FLAG_Z; if((*a^*h^i)&0x10) *f|=FLAG_H; *m=1; };
void ADC_L(gbc_cpu *cpu) { u8 i=*a; *a+=*l; *a+=(*f&FLAG_C)?1:0; *f=(*a>255)?0x10:0; if(!*a) *f|=FLAG_Z; if((*a^*l^i)&0x10) *f|=FLAG_H; *m=1; };
void ADC_mHL(gbc_cpu *cpu) { u8 i=*a; u8 r=read_u8(cpu->mmu,(*h<<8)+*l); *a+=r; *a+=(*f&FLAG_C)?1:0; *f=(*a>255)?0x10:0; if(!*a) *f|=FLAG_Z; if((*a^r^i)&0x10) *f|=FLAG_H; *m=2; };
void ADC_d8(gbc_cpu *cpu) { u8 i=*a; u8 r=read_u8(cpu->mmu,*pc); *a+=r; (*pc)++; *a+=(*f&FLAG_C)?1:0; *f=(*a>255)?0x10:0; if(!*a) *f|=FLAG_Z; if((*a^r^i)&0x10) *f|=FLAG_H; *m=2; };

void SUB_A(gbc_cpu *cpu) { u8 i=*a; *a-=*a; *f=(*a<0)?0x50:FLAG_N; if(!*a) *f|=FLAG_Z; if((*a^*a^i)&FLAG_C) *f|=FLAG_H; *m=1; };
void SUB_B(gbc_cpu *cpu) { u8 i=*a; *a-=*b; *f=(*a<0)?0x50:FLAG_N; if(!*a) *f|=FLAG_Z; if((*a^*b^i)&FLAG_C) *f|=FLAG_H; *m=1; };
void SUB_C(gbc_cpu *cpu) { u8 i=*a; *a-=*c; *f=(*a<0)?0x50:FLAG_N; if(!*a) *f|=FLAG_Z; if((*a^*c^i)&FLAG_C) *f|=FLAG_H; *m=1; };
void SUB_D(gbc_cpu *cpu) { u8 i=*a; *a-=*d; *f=(*a<0)?0x50:FLAG_N; if(!*a) *f|=FLAG_Z; if((*a^*d^i)&FLAG_C) *f|=FLAG_H; *m=1; };
void SUB_E(gbc_cpu *cpu) { u8 i=*a; *a-=*e; *f=(*a<0)?0x50:FLAG_N; if(!*a) *f|=FLAG_Z; if((*a^*e^i)&FLAG_C) *f|=FLAG_H; *m=1; };
void SUB_H(gbc_cpu *cpu) { u8 i=*a; *a-=*h; *f=(*a<0)?0x50:FLAG_N; if(!*a) *f|=FLAG_Z; if((*a^*h^i)&FLAG_C) *f|=FLAG_H; *m=1; };
void SUB_L(gbc_cpu *cpu) { u8 i=*a; *a-=*l; *f=(*a<0)?0x50:FLAG_N; if(!*a) *f|=FLAG_Z; if((*a^*l^i)&FLAG_C) *f|=FLAG_H; *m=1; };
void SUB_mHL(gbc_cpu *cpu) { u8 i=*a; u8 r=read_u8(cpu->mmu,(*h<<8)+*l); *a-=r; *f=(*a<0)?0x50:FLAG_N; if(!*a) *f|=FLAG_Z; if((*a^r^i)&FLAG_C) *f|=FLAG_H; *m=2; };
void SUB_d8(gbc_cpu *cpu) { u8 i=*a; u8 r=read_u8(cpu->mmu,*pc); *a-=r; (*pc)++; *f=(*a<0)?0x50:FLAG_N; if(!*a) *f|=FLAG_Z; if((*a^r^i)&FLAG_C) *f|=FLAG_H; *m=2; };

void SBC_A(gbc_cpu *cpu) { u8 i=*a; *a-=*a; *a-=(*f&FLAG_C)?1:0; *f=(*a<0)?0x50:FLAG_N; if(!*a) *f|=FLAG_Z; if((*a^*a^i)&0x10) *f|=FLAG_H; *m=1; };
void SBC_B(gbc_cpu *cpu) { u8 i=*a; *a-=*b; *a-=(*f&FLAG_C)?1:0; *f=(*a<0)?0x50:FLAG_N; if(!*a) *f|=FLAG_Z; if((*a^*b^i)&0x10) *f|=FLAG_H; *m=1; };
void SBC_C(gbc_cpu *cpu) { u8 i=*a; *a-=*c; *a-=(*f&FLAG_C)?1:0; *f=(*a<0)?0x50:FLAG_N; if(!*a) *f|=FLAG_Z; if((*a^*c^i)&0x10) *f|=FLAG_H; *m=1; };
void SBC_D(gbc_cpu *cpu) { u8 i=*a; *a-=*d; *a-=(*f&FLAG_C)?1:0; *f=(*a<0)?0x50:FLAG_N; if(!*a) *f|=FLAG_Z; if((*a^*d^i)&0x10) *f|=FLAG_H; *m=1; };
void SBC_E(gbc_cpu *cpu) { u8 i=*a; *a-=*e; *a-=(*f&FLAG_C)?1:0; *f=(*a<0)?0x50:FLAG_N; if(!*a) *f|=FLAG_Z; if((*a^*e^i)&0x10) *f|=FLAG_H; *m=1; };
void SBC_H(gbc_cpu *cpu) { u8 i=*a; *a-=*h; *a-=(*f&FLAG_C)?1:0; *f=(*a<0)?0x50:FLAG_N; if(!*a) *f|=FLAG_Z; if((*a^*h^i)&0x10) *f|=FLAG_H; *m=1; };
void SBC_L(gbc_cpu *cpu) { u8 i=*a; *a-=*l; *a-=(*f&FLAG_C)?1:0; *f=(*a<0)?0x50:FLAG_N; if(!*a) *f|=FLAG_Z; if((*a^*l^i)&0x10) *f|=FLAG_H; *m=1; };
void SBC_mHL(gbc_cpu *cpu) { u8 ra=*a; u8 rm=read_u8(cpu->mmu,(*h<<8)+*l); *a-=rm; *a-=(*f&FLAG_C)?1:0; *f=(*a<0)?0x50:FLAG_N; if(!*a) *f|=FLAG_Z; if((*a^rm^ra)&0x10) *f|=FLAG_H; *m=2; };

void SBC_d8(gbc_cpu *cpu) { u8 i=*a; u8 r=read_u8(cpu->mmu,*pc); *a-=r; (*pc)++; *a-=(*f&FLAG_C)?1:0; *f=(*a<0)?0x50:FLAG_N; if(!*a) *f|=FLAG_Z; if((*a^*f^i)&0x10) *f|=FLAG_H; *m=2; };

void CP_A(gbc_cpu *cpu) { u8 i=*a; i-=*a; *f=(i<0)?0x50:FLAG_N; i&=255; if(!i) *f|=FLAG_Z; if((*a^*a^i)&FLAG_C) *f|=FLAG_H; *m=1; };
void CP_B(gbc_cpu *cpu) { u8 i=*a; i-=*b; *f=(i<0)?0x50:FLAG_N; i&=255; if(!i) *f|=FLAG_Z; if((*a^*b^i)&FLAG_C) *f|=FLAG_H; *m=1; };
void CP_C(gbc_cpu *cpu) { u8 i=*a; i-=*c; *f=(i<0)?0x50:FLAG_N; i&=255; if(!i) *f|=FLAG_Z; if((*a^*c^i)&FLAG_C) *f|=FLAG_H; *m=1; };
void CP_D(gbc_cpu *cpu) { u8 i=*a; i-=*d; *f=(i<0)?0x50:FLAG_N; i&=255; if(!i) *f|=FLAG_Z; if((*a^*d^i)&FLAG_C) *f|=FLAG_H; *m=1; };
void CP_E(gbc_cpu *cpu) { u8 i=*a; i-=*e; *f=(i<0)?0x50:FLAG_N; i&=255; if(!i) *f|=FLAG_Z; if((*a^*e^i)&FLAG_C) *f|=FLAG_H; *m=1; };
void CP_H(gbc_cpu *cpu) { u8 i=*a; i-=*h; *f=(i<0)?0x50:FLAG_N; i&=255; if(!i) *f|=FLAG_Z; if((*a^*h^i)&FLAG_C) *f|=FLAG_H; *m=1; };
void CP_L(gbc_cpu *cpu) { u8 i=*a; i-=*l; *f=(i<0)?0x50:FLAG_N; i&=255; if(!i) *f|=FLAG_Z; if((*a^*l^i)&FLAG_C) *f|=FLAG_H; *m=1; };
void CP_mHL(gbc_cpu *cpu) { u8 i=*a; u8 r=read_u8(cpu->mmu,(*h<<8)+*l); i-=r; *f=(i<0)?0x50:FLAG_N; i&=255; if(!i) *f|=FLAG_Z; if((*a^i^r)&FLAG_C) *f|=FLAG_H; *m=2; };
void CP_d8(gbc_cpu *cpu) { u8 i=*a; u8 r=read_u8(cpu->mmu,*pc); i-=r; (*pc)++; *f=(i<0)?0x50:FLAG_N; i&=255; if(!i) *f|=FLAG_Z; if((*a^i^r)&FLAG_C) *f|=FLAG_H; *m=2; };


void DAA(gbc_cpu *cpu) { u8 i=*a; if((*f&FLAG_H)||((*a&15)>9)) *a+=6; *f&=0xEF; if((*f&FLAG_H)||(i>0x99)) { *a+=0x60; *f|=FLAG_C; } *m=1; };

void AND_A(gbc_cpu *cpu) { *a&=*a; *f=*a?0:FLAG_Z; *m=1; };
void AND_B(gbc_cpu *cpu) { *a&=*b; *f=*a?0:FLAG_Z; *m=1; };
void AND_C(gbc_cpu *cpu) { *a&=*c; *f=*a?0:FLAG_Z; *m=1; };
void AND_D(gbc_cpu *cpu) { *a&=*d; *f=*a?0:FLAG_Z; *m=1; };
void AND_E(gbc_cpu *cpu) { *a&=*e; *f=*a?0:FLAG_Z; *m=1; };
void AND_H(gbc_cpu *cpu) { *a&=*h; *f=*a?0:FLAG_Z; *m=1; };
void AND_L(gbc_cpu *cpu) { *a&=*l; *f=*a?0:FLAG_Z; *m=1; };
void AND_mHL(gbc_cpu *cpu) { *a&=read_u8(cpu->mmu,(*h<<8)+*l); *f=*a?0:FLAG_Z; *m=2; };
void AND_d8(gbc_cpu *cpu) { *a&=read_u8(cpu->mmu,*pc); (*pc)++; *f=*a?0:FLAG_Z; *m=2; };

void OR_A(gbc_cpu *cpu) { *a|=*a; *f=*a?0:FLAG_Z; *m=1; };
void OR_B(gbc_cpu *cpu) { *a|=*b; *f=*a?0:FLAG_Z; *m=1; };
void OR_C(gbc_cpu *cpu) { *a|=*c; *f=*a?0:FLAG_Z; *m=1; };
void OR_D(gbc_cpu *cpu) { *a|=*d; *f=*a?0:FLAG_Z; *m=1; };
void OR_E(gbc_cpu *cpu) { *a|=*e; *f=*a?0:FLAG_Z; *m=1; };
void OR_H(gbc_cpu *cpu) { *a|=*h; *f=*a?0:FLAG_Z; *m=1; };
void OR_L(gbc_cpu *cpu) { *a|=*l; *f=*a?0:FLAG_Z; *m=1; };
void OR_mHL(gbc_cpu *cpu) { *a|=read_u8(cpu->mmu,(*h<<8)+*l); *f=*a?0:FLAG_Z; *m=2; };
void OR_d8(gbc_cpu *cpu) { *a|=read_u8(cpu->mmu,*pc); (*pc)++; *f=*a?0:FLAG_Z; *m=2; };

// checked
void XOR_A(gbc_cpu *cpu) { *a=0; set_f(cpu, FLAG_Z); *m=1; };
void XOR_B(gbc_cpu *cpu) { *a^=*b; *f=*a?0:FLAG_Z; *m=1; };
void XOR_C(gbc_cpu *cpu) { *a^=*c; *f=*a?0:FLAG_Z; *m=1; };
void XOR_D(gbc_cpu *cpu) { *a^=*d; *f=*a?0:FLAG_Z; *m=1; };
void XOR_E(gbc_cpu *cpu) { *a^=*e; *f=*a?0:FLAG_Z; *m=1; };
void XOR_H(gbc_cpu *cpu) { *a^=*h; *f=*a?0:FLAG_Z; *m=1; };
void XOR_L(gbc_cpu *cpu) { *a^=*l; *f=*a?0:FLAG_Z; *m=1; };
void XOR_mHL(gbc_cpu *cpu) { *a^=read_u8(cpu->mmu,(*h<<8)+*l); *f=*a?0:FLAG_Z; *m=2; };
void XOR_d8(gbc_cpu *cpu) { *a^=read_u8(cpu->mmu,*pc); (*pc)++; *f=*a?0:FLAG_Z; *m=2; };

void INC_A(gbc_cpu *cpu) { (*a)++;  *f=*a?0:FLAG_Z; *m=1; *a=12; };
void INC_B(gbc_cpu *cpu) { (*b)++; *f=*b?0:FLAG_Z; *m=1; };
void INC_C(gbc_cpu *cpu) { (*c)++; *f=*c?0:FLAG_Z;  *m=1; };
void INC_D(gbc_cpu *cpu) { (*d)++; *f=*d?0:FLAG_Z; *m=1; };
void INC_E(gbc_cpu *cpu) { (*e)++; *f=*e?0:FLAG_Z; *m=1; };
void INC_H(gbc_cpu *cpu) { (*h)++; *f=*h?0:FLAG_Z; *m=1; };
void INC_L(gbc_cpu *cpu) { (*l)++; *f=*l?0:FLAG_Z; *m=1; };
void INC_mHL(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,(*h<<8)+*l)+1; i&=255; write_u8(cpu->mmu,(*h<<8)+*l,i); *f=i?0:FLAG_Z; *m=3; };

void INC_BC(gbc_cpu *cpu) { *c=(*c+1)&255; if(!*c) *b=(*b+1)&255; *m=1; };
void INC_DE(gbc_cpu *cpu) { *e=(*e+1)&255; if(!*e) *d=(*d+1)&255; *m=1; };
void INC_HL(gbc_cpu *cpu) { *l=(*l+1)&255; if(!*l) *h=(*h+1)&255; *m=1; };
void INC_SP(gbc_cpu *cpu) { *sp=(*sp+1)&65535; *m=1; };

void DEC_B(gbc_cpu *cpu) { (*b)--; *f=*b?0:FLAG_Z; *m=1; };
void DEC_C(gbc_cpu *cpu) { (*c)--; *f=*c?0:FLAG_Z; *m=1; };
void DEC_D(gbc_cpu *cpu) { (*d)--; *f=*d?0:FLAG_Z; *m=1; };
void DEC_E(gbc_cpu *cpu) { (*e)--; *f=*e?0:FLAG_Z; *m=1; };
void DEC_H(gbc_cpu *cpu) { (*h)--; *f=*h?0:FLAG_Z; *m=1; };
void DEC_L(gbc_cpu *cpu) { (*l)--; *f=*l?0:FLAG_Z; *m=1; };
void DEC_A(gbc_cpu *cpu) { (*a)--; *f=*a?0:FLAG_Z; *m=1; };
void DEC_mHL(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,(*h<<8)+*l)-1; i&=255; write_u8(cpu->mmu,(*h<<8)+*l,i); *f=i?0:FLAG_Z; *m=3; };

void DEC_BC(gbc_cpu *cpu) { *c=(*c-1)&255; if(*c==255) *b=(*b-1)&255; *m=1; };
void DEC_DE(gbc_cpu *cpu) { *e=(*e-1)&255; if(*e==255) *d=(*d-1)&255; *m=1; };
void DEC_HL(gbc_cpu *cpu) { *l=(*l-1)&255; if(*l==255) *h=(*h-1)&255; *m=1; };
void DEC_SP(gbc_cpu *cpu) { *sp=(*sp-1)&65535; *m=1; };

void BIT_0_A(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*a&0x01)?0:FLAG_Z; *m=2; };
void BIT_0_B(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*b&0x01)?0:FLAG_Z; *m=2; };
void BIT_0_C(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*c&0x01)?0:FLAG_Z; *m=2; };
void BIT_0_D(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*d&0x01)?0:FLAG_Z; *m=2; };
void BIT_0_E(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*e&0x01)?0:FLAG_Z; *m=2; };
void BIT_0_H(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*h&0x01)?0:FLAG_Z; *m=2; };
void BIT_0_L(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*l&0x01)?0:FLAG_Z; *m=2; };
void BIT_0_M(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(read_u8(cpu->mmu,(*h<<8)+*l)&0x01)?0:FLAG_Z; *m=3; };

void RES_0_A(gbc_cpu *cpu) { *a&=0xFE; *m=2; };
void RES_0_B(gbc_cpu *cpu) { *b&=0xFE; *m=2; };
void RES_0_C(gbc_cpu *cpu) { *c&=0xFE; *m=2; };
void RES_0_D(gbc_cpu *cpu) { *d&=0xFE; *m=2; };
void RES_0_E(gbc_cpu *cpu) { *e&=0xFE; *m=2; };
void RES_0_H(gbc_cpu *cpu) { *h&=0xFE; *m=2; };
void RES_0_L(gbc_cpu *cpu) { *l&=0xFE; *m=2; };
void RES_0_M(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,(*h<<8)+*l); i&=0xFE; write_u8(cpu->mmu,(*h<<8)+*l,i); *m=4; };

void SET_0_B(gbc_cpu *cpu) { *b|=0x01; *m=2; };
void SET_0_C(gbc_cpu *cpu) { *b|=0x01; *m=2; };
void SET_0_D(gbc_cpu *cpu) { *b|=0x01; *m=2; };
void SET_0_E(gbc_cpu *cpu) { *b|=0x01; *m=2; };
void SET_0_H(gbc_cpu *cpu) { *b|=0x01; *m=2; };
void SET_0_L(gbc_cpu *cpu) { *b|=0x01; *m=2; };
void SET_0_A(gbc_cpu *cpu) { *b|=0x01; *m=2; };
void SET_0_M(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,(*h<<8)+*l); i|=0x01; write_u8(cpu->mmu,(*h<<8)+*l,i); *m=4; };

void BIT_1_B(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*b&0x02)?0:FLAG_Z; *m=2; };
void BIT_1_C(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*c&0x02)?0:FLAG_Z; *m=2; };
void BIT_1_D(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*d&0x02)?0:FLAG_Z; *m=2; };
void BIT_1_E(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*e&0x02)?0:FLAG_Z; *m=2; };
void BIT_1_H(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*h&0x02)?0:FLAG_Z; *m=2; };
void BIT_1_L(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*l&0x02)?0:FLAG_Z; *m=2; };
void BIT_1_A(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*a&0x02)?0:FLAG_Z; *m=2; };
void BIT_1_M(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(read_u8(cpu->mmu,(*h<<8)+*l)&0x02)?0:FLAG_Z; *m=3; };

void RES_1_B(gbc_cpu *cpu) { *b&=0xFD; *m=2; };
void RES_1_C(gbc_cpu *cpu) { *c&=0xFD; *m=2; };
void RES_1_D(gbc_cpu *cpu) { *d&=0xFD; *m=2; };
void RES_1_E(gbc_cpu *cpu) { *e&=0xFD; *m=2; };
void RES_1_H(gbc_cpu *cpu) { *h&=0xFD; *m=2; };
void RES_1_L(gbc_cpu *cpu) { *l&=0xFD; *m=2; };
void RES_1_A(gbc_cpu *cpu) { *a&=0xFD; *m=2; };
void RES_1_M(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,(*h<<8)+*l); i&=0xFD; write_u8(cpu->mmu,(*h<<8)+*l,i); *m=4; };

void SET_1_B(gbc_cpu *cpu) { *b|=0x02; *m=2; };
void SET_1_C(gbc_cpu *cpu) { *b|=0x02; *m=2; };
void SET_1_D(gbc_cpu *cpu) { *b|=0x02; *m=2; };
void SET_1_E(gbc_cpu *cpu) { *b|=0x02; *m=2; };
void SET_1_H(gbc_cpu *cpu) { *b|=0x02; *m=2; };
void SET_1_L(gbc_cpu *cpu) { *b|=0x02; *m=2; };
void SET_1_A(gbc_cpu *cpu) { *b|=0x02; *m=2; };
void SET_1_M(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,(*h<<8)+*l); i|=0x02; write_u8(cpu->mmu,(*h<<8)+*l,i); *m=4; };

void BIT_2_B(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*b&0x04)?0:FLAG_Z; *m=2; };
void BIT_2_C(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*c&0x04)?0:FLAG_Z; *m=2; };
void BIT_2_D(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*d&0x04)?0:FLAG_Z; *m=2; };
void BIT_2_E(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*e&0x04)?0:FLAG_Z; *m=2; };
void BIT_2_H(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*h&0x04)?0:FLAG_Z; *m=2; };
void BIT_2_L(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*l&0x04)?0:FLAG_Z; *m=2; };
void BIT_2_A(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*a&0x04)?0:FLAG_Z; *m=2; };
void BIT_2_M(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(read_u8(cpu->mmu,(*h<<8)+*l)&0x04)?0:FLAG_Z; *m=3; };

void RES_2_B(gbc_cpu *cpu) { *b&=0xFB; *m=2; };
void RES_2_C(gbc_cpu *cpu) { *c&=0xFB; *m=2; };
void RES_2_D(gbc_cpu *cpu) { *d&=0xFB; *m=2; };
void RES_2_E(gbc_cpu *cpu) { *e&=0xFB; *m=2; };
void RES_2_H(gbc_cpu *cpu) { *h&=0xFB; *m=2; };
void RES_2_L(gbc_cpu *cpu) { *l&=0xFB; *m=2; };
void RES_2_A(gbc_cpu *cpu) { *a&=0xFB; *m=2; };
void RES_2_M(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,(*h<<8)+*l); i&=0xFB; write_u8(cpu->mmu,(*h<<8)+*l,i); *m=4; };

void SET_2_B(gbc_cpu *cpu) { *b|=0x04; *m=2; };
void SET_2_C(gbc_cpu *cpu) { *b|=0x04; *m=2; };
void SET_2_D(gbc_cpu *cpu) { *b|=0x04; *m=2; };
void SET_2_E(gbc_cpu *cpu) { *b|=0x04; *m=2; };
void SET_2_H(gbc_cpu *cpu) { *b|=0x04; *m=2; };
void SET_2_L(gbc_cpu *cpu) { *b|=0x04; *m=2; };
void SET_2_A(gbc_cpu *cpu) { *b|=0x04; *m=2; };
void SET_2_M(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,(*h<<8)+*l); i|=0x04; write_u8(cpu->mmu,(*h<<8)+*l,i); *m=4; };

void BIT_3_B(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*b&0x08)?0:FLAG_Z; *m=2; };
void BIT_3_C(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*c&0x08)?0:FLAG_Z; *m=2; };
void BIT_3_D(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*d&0x08)?0:FLAG_Z; *m=2; };
void BIT_3_E(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*e&0x08)?0:FLAG_Z; *m=2; };
void BIT_3_H(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*h&0x08)?0:FLAG_Z; *m=2; };
void BIT_3_L(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*l&0x08)?0:FLAG_Z; *m=2; };
void BIT_3_A(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*a&0x08)?0:FLAG_Z; *m=2; };
void BIT_3_M(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(read_u8(cpu->mmu,(*h<<8)+*l)&0x08)?0:FLAG_Z; *m=3; };

void RES_3_B(gbc_cpu *cpu) { *b&=0xF7; *m=2; };
void RES_3_C(gbc_cpu *cpu) { *c&=0xF7; *m=2; };
void RES_3_D(gbc_cpu *cpu) { *d&=0xF7; *m=2; };
void RES_3_E(gbc_cpu *cpu) { *e&=0xF7; *m=2; };
void RES_3_H(gbc_cpu *cpu) { *h&=0xF7; *m=2; };
void RES_3_L(gbc_cpu *cpu) { *l&=0xF7; *m=2; };
void RES_3_A(gbc_cpu *cpu) { *a&=0xF7; *m=2; };
void RES_3_M(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,(*h<<8)+*l); i&=0xF7; write_u8(cpu->mmu,(*h<<8)+*l,i); *m=4; };

void SET_3_B(gbc_cpu *cpu) { *b|=0x08; *m=2; };
void SET_3_C(gbc_cpu *cpu) { *b|=0x08; *m=2; };
void SET_3_D(gbc_cpu *cpu) { *b|=0x08; *m=2; };
void SET_3_E(gbc_cpu *cpu) { *b|=0x08; *m=2; };
void SET_3_H(gbc_cpu *cpu) { *b|=0x08; *m=2; };
void SET_3_L(gbc_cpu *cpu) { *b|=0x08; *m=2; };
void SET_3_A(gbc_cpu *cpu) { *b|=0x08; *m=2; };
void SET_3_M(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,(*h<<8)+*l); i|=0x08; write_u8(cpu->mmu,(*h<<8)+*l,i); *m=4; };

void BIT_4_B(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*b&FLAG_C)?0:FLAG_Z; *m=2; };
void BIT_4_C(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*c&FLAG_C)?0:FLAG_Z; *m=2; };
void BIT_4_D(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*d&FLAG_C)?0:FLAG_Z; *m=2; };
void BIT_4_E(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*e&FLAG_C)?0:FLAG_Z; *m=2; };
void BIT_4_H(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*h&FLAG_C)?0:FLAG_Z; *m=2; };
void BIT_4_L(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*l&FLAG_C)?0:FLAG_Z; *m=2; };
void BIT_4_A(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*a&FLAG_C)?0:FLAG_Z; *m=2; };
void BIT_4_M(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(read_u8(cpu->mmu,(*h<<8)+*l)&FLAG_C)?0:FLAG_Z; *m=3; };

void RES_4_B(gbc_cpu *cpu) { *b&=0xEF; *m=2; };
void RES_4_C(gbc_cpu *cpu) { *c&=0xEF; *m=2; };
void RES_4_D(gbc_cpu *cpu) { *d&=0xEF; *m=2; };
void RES_4_E(gbc_cpu *cpu) { *e&=0xEF; *m=2; };
void RES_4_H(gbc_cpu *cpu) { *h&=0xEF; *m=2; };
void RES_4_L(gbc_cpu *cpu) { *l&=0xEF; *m=2; };
void RES_4_A(gbc_cpu *cpu) { *a&=0xEF; *m=2; };
void RES_4_M(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,(*h<<8)+*l); i&=0xEF; write_u8(cpu->mmu,(*h<<8)+*l,i); *m=4; };

void SET_4_B(gbc_cpu *cpu) { *b|=FLAG_C; *m=2; };
void SET_4_C(gbc_cpu *cpu) { *b|=FLAG_C; *m=2; };
void SET_4_D(gbc_cpu *cpu) { *b|=FLAG_C; *m=2; };
void SET_4_E(gbc_cpu *cpu) { *b|=FLAG_C; *m=2; };
void SET_4_H(gbc_cpu *cpu) { *b|=FLAG_C; *m=2; };
void SET_4_L(gbc_cpu *cpu) { *b|=FLAG_C; *m=2; };
void SET_4_A(gbc_cpu *cpu) { *b|=FLAG_C; *m=2; };
void SET_4_M(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,(*h<<8)+*l); i|=FLAG_C; write_u8(cpu->mmu,(*h<<8)+*l,i); *m=4; };

void BIT_5_B(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*b&FLAG_H)?0:FLAG_Z; *m=2; };
void BIT_5_C(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*c&FLAG_H)?0:FLAG_Z; *m=2; };
void BIT_5_D(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*d&FLAG_H)?0:FLAG_Z; *m=2; };
void BIT_5_E(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*e&FLAG_H)?0:FLAG_Z; *m=2; };
void BIT_5_H(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*h&FLAG_H)?0:FLAG_Z; *m=2; };
void BIT_5_L(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*l&FLAG_H)?0:FLAG_Z; *m=2; };
void BIT_5_A(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*a&FLAG_H)?0:FLAG_Z; *m=2; };
void BIT_5_M(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(read_u8(cpu->mmu,(*h<<8)+*l)&FLAG_H)?0:FLAG_Z; *m=3; };

void RES_5_B(gbc_cpu *cpu) { *b&=0xDF; *m=2; };
void RES_5_C(gbc_cpu *cpu) { *c&=0xDF; *m=2; };
void RES_5_D(gbc_cpu *cpu) { *d&=0xDF; *m=2; };
void RES_5_E(gbc_cpu *cpu) { *e&=0xDF; *m=2; };
void RES_5_H(gbc_cpu *cpu) { *h&=0xDF; *m=2; };
void RES_5_L(gbc_cpu *cpu) { *l&=0xDF; *m=2; };
void RES_5_A(gbc_cpu *cpu) { *a&=0xDF; *m=2; };
void RES_5_M(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,(*h<<8)+*l); i&=0xDF; write_u8(cpu->mmu,(*h<<8)+*l,i); *m=4; };

void SET_5_B(gbc_cpu *cpu) { *b|=FLAG_H; *m=2; };
void SET_5_C(gbc_cpu *cpu) { *b|=FLAG_H; *m=2; };
void SET_5_D(gbc_cpu *cpu) { *b|=FLAG_H; *m=2; };
void SET_5_E(gbc_cpu *cpu) { *b|=FLAG_H; *m=2; };
void SET_5_H(gbc_cpu *cpu) { *b|=FLAG_H; *m=2; };
void SET_5_L(gbc_cpu *cpu) { *b|=FLAG_H; *m=2; };
void SET_5_A(gbc_cpu *cpu) { *b|=FLAG_H; *m=2; };
void SET_5_M(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,(*h<<8)+*l); i|=FLAG_H; write_u8(cpu->mmu,(*h<<8)+*l,i); *m=4; };

void BIT_6_B(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*b&FLAG_N)?0:FLAG_Z; *m=2; };
void BIT_6_C(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*c&FLAG_N)?0:FLAG_Z; *m=2; };
void BIT_6_D(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*d&FLAG_N)?0:FLAG_Z; *m=2; };
void BIT_6_E(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*e&FLAG_N)?0:FLAG_Z; *m=2; };
void BIT_6_H(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*h&FLAG_N)?0:FLAG_Z; *m=2; };
void BIT_6_L(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*l&FLAG_N)?0:FLAG_Z; *m=2; };
void BIT_6_A(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*a&FLAG_N)?0:FLAG_Z; *m=2; };
void BIT_6_M(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(read_u8(cpu->mmu,(*h<<8)+*l)&FLAG_N)?0:FLAG_Z; *m=3; };

void RES_6_B(gbc_cpu *cpu) { *b&=0xBF; *m=2; };
void RES_6_C(gbc_cpu *cpu) { *c&=0xBF; *m=2; };
void RES_6_D(gbc_cpu *cpu) { *d&=0xBF; *m=2; };
void RES_6_E(gbc_cpu *cpu) { *e&=0xBF; *m=2; };
void RES_6_H(gbc_cpu *cpu) { *h&=0xBF; *m=2; };
void RES_6_L(gbc_cpu *cpu) { *l&=0xBF; *m=2; };
void RES_6_A(gbc_cpu *cpu) { *a&=0xBF; *m=2; };
void RES_6_M(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,(*h<<8)+*l); i&=0xBF; write_u8(cpu->mmu,(*h<<8)+*l,i); *m=4; };

void SET_6_B(gbc_cpu *cpu) { *b|=FLAG_N; *m=2; };
void SET_6_C(gbc_cpu *cpu) { *b|=FLAG_N; *m=2; };
void SET_6_D(gbc_cpu *cpu) { *b|=FLAG_N; *m=2; };
void SET_6_E(gbc_cpu *cpu) { *b|=FLAG_N; *m=2; };
void SET_6_H(gbc_cpu *cpu) { *b|=FLAG_N; *m=2; };
void SET_6_L(gbc_cpu *cpu) { *b|=FLAG_N; *m=2; };
void SET_6_A(gbc_cpu *cpu) { *b|=FLAG_N; *m=2; };
void SET_6_M(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,(*h<<8)+*l); i|=FLAG_N; write_u8(cpu->mmu,(*h<<8)+*l,i); *m=4; };

void BIT_7_B(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*b&FLAG_Z)?0:FLAG_Z; *m=2; };
void BIT_7_C(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*c&FLAG_Z)?0:FLAG_Z; *m=2; };
void BIT_7_D(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*d&FLAG_Z)?0:FLAG_Z; *m=2; };
void BIT_7_E(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*e&FLAG_Z)?0:FLAG_Z; *m=2; };
void BIT_7_H(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*h&FLAG_Z)?0:FLAG_Z; *m=2; };
void BIT_7_L(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*l&FLAG_Z)?0:FLAG_Z; *m=2; };
void BIT_7_A(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(*a&FLAG_Z)?0:FLAG_Z; *m=2; };
void BIT_7_M(gbc_cpu *cpu) { *f&=0x1F; *f|=FLAG_H; *f=(read_u8(cpu->mmu,(*h<<8)+*l)&FLAG_Z)?0:FLAG_Z; *m=3; };

void RES_7_B(gbc_cpu *cpu) { *b&=0x7F; *m=2; };
void RES_7_C(gbc_cpu *cpu) { *c&=0x7F; *m=2; };
void RES_7_D(gbc_cpu *cpu) { *d&=0x7F; *m=2; };
void RES_7_E(gbc_cpu *cpu) { *e&=0x7F; *m=2; };
void RES_7_H(gbc_cpu *cpu) { *h&=0x7F; *m=2; };
void RES_7_L(gbc_cpu *cpu) { *l&=0x7F; *m=2; };
void RES_7_A(gbc_cpu *cpu) { *a&=0x7F; *m=2; };
void RES_7_M(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,(*h<<8)+*l); i&=0x7F; write_u8(cpu->mmu,(*h<<8)+*l,i); *m=4; };

void SET_7_B(gbc_cpu *cpu) { *b|=FLAG_Z; *m=2; };
void SET_7_C(gbc_cpu *cpu) { *b|=FLAG_Z; *m=2; };
void SET_7_D(gbc_cpu *cpu) { *b|=FLAG_Z; *m=2; };
void SET_7_E(gbc_cpu *cpu) { *b|=FLAG_Z; *m=2; };
void SET_7_H(gbc_cpu *cpu) { *b|=FLAG_Z; *m=2; };
void SET_7_L(gbc_cpu *cpu) { *b|=FLAG_Z; *m=2; };
void SET_7_A(gbc_cpu *cpu) { *b|=FLAG_Z; *m=2; };
void SET_7_M(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,(*h<<8)+*l); i|=FLAG_Z; write_u8(cpu->mmu,(*h<<8)+*l,i); *m=4; };

void RLA(gbc_cpu *cpu) { u8 ci=*f&FLAG_C?1:0; u8 co=*a&FLAG_Z?0x10:0; *a=(*a<<1)+ci; *f=(*f&0xEF)+co; *m=1; };
void RLCA(gbc_cpu *cpu) { u8 ci=*a&FLAG_Z?1:0; u8 co=*a&FLAG_Z?FLAG_C:0; *a=(*a<<1)+ci; *f=(*f&0xEF)+co; *m=1; };
void RRA(gbc_cpu *cpu) { u8 ci=*f&FLAG_C?FLAG_Z:0; u8 co=*a&1?0x10:0; *a=(*a>>1)+ci; *f=(*f&0xEF)+co; *m=1; };
void RRCA(gbc_cpu *cpu) { u8 ci=*a&1?FLAG_Z:0; u8 co=*a&1?FLAG_C:0; *a=(*a>>1)+ci; *f=(*f&0xEF)+co; *m=1; };

void RL_B(gbc_cpu *cpu) { u8 ci=*f&FLAG_C?1:0; u8 co=*b&FLAG_Z?0x10:0; *b=(*b<<1)+ci; *f=(*b)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RL_C(gbc_cpu *cpu) { u8 ci=*f&FLAG_C?1:0; u8 co=*c&FLAG_Z?0x10:0; *c=(*c<<1)+ci; *f=(*c)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RL_D(gbc_cpu *cpu) { u8 ci=*f&FLAG_C?1:0; u8 co=*d&FLAG_Z?0x10:0; *d=(*d<<1)+ci; *f=(*d)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RL_E(gbc_cpu *cpu) { u8 ci=*f&FLAG_C?1:0; u8 co=*e&FLAG_Z?0x10:0; *e=(*e<<1)+ci; *f=(*e)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RL_H(gbc_cpu *cpu) { u8 ci=*f&FLAG_C?1:0; u8 co=*h&FLAG_Z?0x10:0; *h=(*h<<1)+ci; *f=(*h)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RL_L(gbc_cpu *cpu) { u8 ci=*f&FLAG_C?1:0; u8 co=*l&FLAG_Z?0x10:0; *l=(*l<<1)+ci; *f=(*l)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RL_A(gbc_cpu *cpu) { u8 ci=*f&FLAG_C?1:0; u8 co=*a&FLAG_Z?0x10:0; *a=(*a<<1)+ci; *f=(*a)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RL_mHL(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,(*h<<8)+*l); u8 ci=*f&FLAG_C?1:0; u8 co=i&FLAG_Z?0x10:0; i=(i<<1)+ci; i&=255; *f=(i)?0:FLAG_Z; write_u8(cpu->mmu,(*h<<8)+*l,i); *f=(*f&0xEF)+co; *m=4; };

void RLC_B(gbc_cpu *cpu) { u8 ci=*b&FLAG_Z?1:0; u8 co=*b&FLAG_Z?FLAG_C:0; *b=(*b<<1)+ci; *f=(*b)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RLC_C(gbc_cpu *cpu) { u8 ci=*c&FLAG_Z?1:0; u8 co=*c&FLAG_Z?FLAG_C:0; *c=(*c<<1)+ci; *f=(*c)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RLC_D(gbc_cpu *cpu) { u8 ci=*d&FLAG_Z?1:0; u8 co=*d&FLAG_Z?FLAG_C:0; *d=(*d<<1)+ci; *f=(*d)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RLC_E(gbc_cpu *cpu) { u8 ci=*e&FLAG_Z?1:0; u8 co=*e&FLAG_Z?FLAG_C:0; *e=(*e<<1)+ci; *f=(*e)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RLC_H(gbc_cpu *cpu) { u8 ci=*h&FLAG_Z?1:0; u8 co=*h&FLAG_Z?FLAG_C:0; *h=(*h<<1)+ci; *f=(*h)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RLC_L(gbc_cpu *cpu) { u8 ci=*l&FLAG_Z?1:0; u8 co=*l&FLAG_Z?FLAG_C:0; *l=(*l<<1)+ci; *f=(*l)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RLC_A(gbc_cpu *cpu) { u8 ci=*a&FLAG_Z?1:0; u8 co=*a&FLAG_Z?FLAG_C:0; *a=(*a<<1)+ci; *f=(*a)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RLC_mHL(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,(*h<<8)+*l); u8 ci=i&FLAG_Z?1:0; u8 co=i&FLAG_Z?FLAG_C:0; i=(i<<1)+ci; i&=255; *f=(i)?0:FLAG_Z; write_u8(cpu->mmu,(*h<<8)+*l,i); *f=(*f&0xEF)+co; *m=4; };

void RR_B(gbc_cpu *cpu) { u8 ci=*f&FLAG_C?FLAG_Z:0; u8 co=*b&1?0x10:0; *b=(*b>>1)+ci; *f=(*b)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RR_C(gbc_cpu *cpu) { u8 ci=*f&FLAG_C?FLAG_Z:0; u8 co=*c&1?0x10:0; *c=(*c>>1)+ci; *f=(*c)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RR_D(gbc_cpu *cpu) { u8 ci=*f&FLAG_C?FLAG_Z:0; u8 co=*d&1?0x10:0; *d=(*d>>1)+ci; *f=(*d)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RR_E(gbc_cpu *cpu) { u8 ci=*f&FLAG_C?FLAG_Z:0; u8 co=*e&1?0x10:0; *e=(*e>>1)+ci; *f=(*e)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RR_H(gbc_cpu *cpu) { u8 ci=*f&FLAG_C?FLAG_Z:0; u8 co=*h&1?0x10:0; *h=(*h>>1)+ci; *f=(*h)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RR_L(gbc_cpu *cpu) { u8 ci=*f&FLAG_C?FLAG_Z:0; u8 co=*l&1?0x10:0; *l=(*l>>1)+ci; *f=(*l)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RR_A(gbc_cpu *cpu) { u8 ci=*f&FLAG_C?FLAG_Z:0; u8 co=*a&1?0x10:0; *a=(*a>>1)+ci; *f=(*a)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RR_mHL(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,(*h<<8)+*l); u8 ci=*f&FLAG_C?FLAG_Z:0; u8 co=i&1?0x10:0; i=(i>>1)+ci; i&=255; write_u8(cpu->mmu,(*h<<8)+*l,i); *f=(i)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=4; };

void RRC_B(gbc_cpu *cpu) { u8 ci=*b&1?FLAG_Z:0; u8 co=*b&1?FLAG_C:0; *b=(*b>>1)+ci; *f=(*b)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RRC_C(gbc_cpu *cpu) { u8 ci=*c&1?FLAG_Z:0; u8 co=*c&1?FLAG_C:0; *c=(*c>>1)+ci; *f=(*c)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RRC_D(gbc_cpu *cpu) { u8 ci=*d&1?FLAG_Z:0; u8 co=*d&1?FLAG_C:0; *d=(*d>>1)+ci; *f=(*d)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RRC_E(gbc_cpu *cpu) { u8 ci=*e&1?FLAG_Z:0; u8 co=*e&1?FLAG_C:0; *e=(*e>>1)+ci; *f=(*e)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RRC_H(gbc_cpu *cpu) { u8 ci=*h&1?FLAG_Z:0; u8 co=*h&1?FLAG_C:0; *h=(*h>>1)+ci; *f=(*h)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RRC_L(gbc_cpu *cpu) { u8 ci=*l&1?FLAG_Z:0; u8 co=*l&1?FLAG_C:0; *l=(*l>>1)+ci; *f=(*l)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RRC_A(gbc_cpu *cpu) { u8 ci=*a&1?FLAG_Z:0; u8 co=*a&1?FLAG_C:0; *a=(*a>>1)+ci; *f=(*a)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void RRC_mHL(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,(*h<<8)+*l); u8 ci=i&1?FLAG_Z:0; u8 co=i&1?FLAG_C:0; i=(i>>1)+ci; i&=255; write_u8(cpu->mmu,(*h<<8)+*l,i); *f=(i)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=4; };

void SLA_B(gbc_cpu *cpu) { u8 co=*b&FLAG_Z?FLAG_C:0; *b=(*b<<1)&255; *f=(*b)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SLA_C(gbc_cpu *cpu) { u8 co=*c&FLAG_Z?FLAG_C:0; *c=(*c<<1)&255; *f=(*c)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SLA_D(gbc_cpu *cpu) { u8 co=*d&FLAG_Z?FLAG_C:0; *d=(*d<<1)&255; *f=(*d)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SLA_E(gbc_cpu *cpu) { u8 co=*e&FLAG_Z?FLAG_C:0; *e=(*e<<1)&255; *f=(*e)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SLA_H(gbc_cpu *cpu) { u8 co=*h&FLAG_Z?FLAG_C:0; *h=(*h<<1)&255; *f=(*h)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SLA_L(gbc_cpu *cpu) { u8 co=*l&FLAG_Z?FLAG_C:0; *l=(*l<<1)&255; *f=(*l)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SLA_A(gbc_cpu *cpu) { u8 co=*a&FLAG_Z?FLAG_C:0; *a=(*a<<1)&255; *f=(*a)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };

void SLL_B(gbc_cpu *cpu) { u8 co=*b&FLAG_Z?FLAG_C:0; *b=(*b<<1)&255+1; *f=(*b)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SLL_C(gbc_cpu *cpu) { u8 co=*c&FLAG_Z?FLAG_C:0; *c=(*c<<1)&255+1; *f=(*c)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SLL_D(gbc_cpu *cpu) { u8 co=*d&FLAG_Z?FLAG_C:0; *d=(*d<<1)&255+1; *f=(*d)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SLL_E(gbc_cpu *cpu) { u8 co=*e&FLAG_Z?FLAG_C:0; *e=(*e<<1)&255+1; *f=(*e)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SLL_H(gbc_cpu *cpu) { u8 co=*h&FLAG_Z?FLAG_C:0; *h=(*h<<1)&255+1; *f=(*h)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SLL_L(gbc_cpu *cpu) { u8 co=*l&FLAG_Z?FLAG_C:0; *l=(*l<<1)&255+1; *f=(*l)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SLL_A(gbc_cpu *cpu) { u8 co=*a&FLAG_Z?FLAG_C:0; *a=(*a<<1)&255+1; *f=(*a)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };

void SRA_B(gbc_cpu *cpu) { u8 ci=*b&FLAG_Z; u8 co=*b&1?FLAG_C:0; *b=((*b>>1)+ci)&255; *f=(*b)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SRA_C(gbc_cpu *cpu) { u8 ci=*c&FLAG_Z; u8 co=*c&1?FLAG_C:0; *c=((*c>>1)+ci)&255; *f=(*c)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SRA_D(gbc_cpu *cpu) { u8 ci=*d&FLAG_Z; u8 co=*d&1?FLAG_C:0; *d=((*d>>1)+ci)&255; *f=(*d)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SRA_E(gbc_cpu *cpu) { u8 ci=*e&FLAG_Z; u8 co=*e&1?FLAG_C:0; *e=((*e>>1)+ci)&255; *f=(*e)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SRA_H(gbc_cpu *cpu) { u8 ci=*h&FLAG_Z; u8 co=*h&1?FLAG_C:0; *h=((*h>>1)+ci)&255; *f=(*h)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SRA_L(gbc_cpu *cpu) { u8 ci=*l&FLAG_Z; u8 co=*l&1?FLAG_C:0; *l=((*l>>1)+ci)&255; *f=(*l)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SRA_A(gbc_cpu *cpu) { u8 ci=*a&FLAG_Z; u8 co=*a&1?FLAG_C:0; *a=((*a>>1)+ci)&255; *f=(*a)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };

void SRL_B(gbc_cpu *cpu) { u8 co=*b&1?FLAG_C:0; *b=(*b>>1)&255; *f=(*b)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SRL_C(gbc_cpu *cpu) { u8 co=*c&1?FLAG_C:0; *c=(*c>>1)&255; *f=(*c)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SRL_D(gbc_cpu *cpu) { u8 co=*d&1?FLAG_C:0; *d=(*d>>1)&255; *f=(*d)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SRL_E(gbc_cpu *cpu) { u8 co=*e&1?FLAG_C:0; *e=(*e>>1)&255; *f=(*e)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SRL_H(gbc_cpu *cpu) { u8 co=*h&1?FLAG_C:0; *h=(*h>>1)&255; *f=(*h)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SRL_L(gbc_cpu *cpu) { u8 co=*l&1?FLAG_C:0; *l=(*l>>1)&255; *f=(*l)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };
void SRL_A(gbc_cpu *cpu) { u8 co=*a&1?FLAG_C:0; *a=(*a>>1)&255; *f=(*a)?0:FLAG_Z; *f=(*f&0xEF)+co; *m=2; };

void CPL(gbc_cpu *cpu) { *a ^= 255; *f=*a?0:FLAG_Z; *m=1; };
void NEG(gbc_cpu *cpu) { *a=0-*a; *f=(*a<0)?FLAG_C:0; if(!*a) *f|=FLAG_Z; *m=2; };

void CCF(gbc_cpu *cpu) { u8 ci=*f&FLAG_C?0:0x10; *f=(*f&0xEF)+ci; *m=1; };
void SCF(gbc_cpu *cpu) { *f|=FLAG_C; *m=1; };

void PUSH_BC(gbc_cpu *cpu) { (*sp)--; write_u8(cpu->mmu,*sp,*b); (*sp)--; write_u8(cpu->mmu,*sp,*c); *m=3; };
void PUSH_DE(gbc_cpu *cpu) { (*sp)--; write_u8(cpu->mmu,*sp,*d); (*sp)--; write_u8(cpu->mmu,*sp,*e); *m=3; };
void PUSH_HL(gbc_cpu *cpu) { (*sp)--; write_u8(cpu->mmu,*sp,*h); (*sp)--; write_u8(cpu->mmu,*sp,*l); *m=3; };
void PUSH_AF(gbc_cpu *cpu) { (*sp)--; write_u8(cpu->mmu,*sp,*a); (*sp)--; write_u8(cpu->mmu,*sp,*f); *m=3; };

void POP_BC(gbc_cpu *cpu) { *c=read_u8(cpu->mmu,*sp++); *b=read_u8(cpu->mmu,*sp); (*sp)++; *m=3; };
void POP_DE(gbc_cpu *cpu) { *e=read_u8(cpu->mmu,*sp++); *d=read_u8(cpu->mmu,*sp); (*sp)++; *m=3; };
void POP_HL(gbc_cpu *cpu) { *l=read_u8(cpu->mmu,*sp++); *h=read_u8(cpu->mmu,*sp); (*sp)++; *m=3; };
void POP_AF(gbc_cpu *cpu) { *f=read_u8(cpu->mmu,*sp++); *a=read_u8(cpu->mmu,*sp); (*sp)++; *m=3; };

void JP_a16(gbc_cpu *cpu) { *pc = read_u16(cpu->mmu,*pc); *m=3; };
void JP_HL(gbc_cpu *cpu) { *pc=(*h<<8)+*l; *m=1; };
void JP_NZ_a16(gbc_cpu *cpu) { *m=3; if((*f&FLAG_Z)==0x00) { *pc=read_u16(cpu->mmu,*pc); (*m)++; } else (*pc)+=2; };
void JP_Znn(gbc_cpu *cpu) { *m=3; if((*f&FLAG_Z)==FLAG_Z) { *pc=read_u16(cpu->mmu,*pc); (*m)++; } else (*pc)+=2; };
void JP_NC_a16(gbc_cpu *cpu) { *m=3; if((*f&FLAG_C)==0x00) { *pc=read_u16(cpu->mmu,*pc); (*m)++; } else (*pc)+=2; };
void JP_Cnn(gbc_cpu *cpu) { *m=3; if((*f&FLAG_C)==0x10) { *pc=read_u16(cpu->mmu,*pc); (*m)++; } else (*pc)+=2; };

void JR_r8(gbc_cpu *cpu) { u8 i=read_u8(cpu->mmu,*pc); if(i>127) i=-((~i+1)&255); (*pc)++; *m=2; (*pc)+=i; (*m)++; };
/*if(!gb->cpu_reg.f_bits.z)*/
/*{*/
/*int8_t temp = (int8_t) __gb_read(gb, gb->cpu_reg.pc++);*/
/*gb->cpu_reg.pc += temp;*/
/*inst_cycles += 4;*/
/*}*/
/*else*/
/*gb->cpu_reg.pc++;*/

/*break;*/
// checked
void JR_NZ_r8(gbc_cpu *cpu) {
    if(!FZ()) {
        u8 temp=read_u8(cpu->mmu,*pc);
        (*pc)++;
        *pc+=temp;
        *m+=4;
    } else {
        (*pc)++;
    }
}
void JR_Z_r8(gbc_cpu *cpu)  {
    u8 i=read_u8(cpu->mmu,*pc);
    if(FZ()){
        int8_t temp = (int8_t) read_u8(cpu, (*pc)++);
        (*pc) += temp;
        *m += 4;
    } else {
        (*pc)++;
    }
};

void JR_NC_r8(gbc_cpu *cpu) {
    u8 i=read_u8(cpu->mmu,*pc);
    if(i>127) i=-((~i+1)&255);
    (*pc)++;
    *m=2;
    if((*f&FLAG_C)==0x00) {
        (*pc)+=i;
        (*m)++;
    } };

void JR_C_r8(gbc_cpu *cpu)  {
    u8 i=read_u8(cpu->mmu,*pc);
    if(i>127) i=-((~i+1)&255);
    (*pc)++;
    *m=2;
    if((*f&FLAG_C)==0x10) {
        (*pc)+=i;
        (*m)++;
    } };


void CALL_a16(gbc_cpu *cpu) {
    (*sp)-=2;
    write_u16(cpu->mmu,*sp,*pc+2);
    *pc=read_u16(cpu->mmu,*pc);
    *m=5;
};

void CALL_NZ_a16(gbc_cpu *cpu) {
    *m=3;
    if((*f&FLAG_Z)==0x00) {
        (*sp)-=2;
        write_u16(cpu->mmu,*sp,*pc+2);
        *pc=read_u16(cpu->mmu,*pc);
        (*m)+=2;
    } else (*pc)+=2;
};

void CALL_Z_a16(gbc_cpu *cpu) {
    *m=3;
    if((*f&FLAG_Z)==FLAG_Z) {
        (*sp)-=2;
        write_u16(cpu->mmu,*sp,*pc+2);
        *pc=read_u16(cpu->mmu,*pc);
        (*m)+=2;
    } else (*pc)+=2;
};

void CALL_NC_a16(gbc_cpu *cpu) {
    *m=3;
    if((*f&FLAG_C)==0x00) {
        (*sp)-=2;
        write_u16(cpu->mmu,*sp,*pc+2);
        *pc=read_u16(cpu->mmu,*pc);
        (*m)+=2;
    } else (*pc)+=2;
};

void CALL_C_a16(gbc_cpu *cpu) {
    *m=3;
    if((*f&FLAG_C)==0x10) {
        (*sp)-=2;
        write_u16(cpu->mmu,*sp,*pc+2);
        *pc=read_u16(cpu->mmu,*pc);
        (*m)+=2;
    } else (*pc)+=2;
};

void RET(gbc_cpu *cpu) {
    char s[80]; sprintf(s, "ret PC: %x", *pc); cli_printl(s);
    u16 temp = read_u8(cpu, (*sp)++);
    temp |= read_u8(cpu, (*sp)++) << 8;
    (*pc) = temp;
    (*sp)+=2;
    *m=3;
};
void RET_I(gbc_cpu *cpu) { /*rrs(cpu);*/ *pc=read_u16(cpu->mmu,*sp); cpu->IME = 1; (*sp)+=2; *m=3; };
void RET_NZ(gbc_cpu *cpu) { *m=1; if((*f&FLAG_Z)==0x00) { *pc=read_u16(cpu->mmu,*sp); (*sp)+=2; (*m)+=2; } };
void RET_Z(gbc_cpu *cpu) { *m=1; if((*f&FLAG_Z)==FLAG_Z) { *pc=read_u16(cpu->mmu,*sp); (*sp)+=2; (*m)+=2; } };
void RET_NC(gbc_cpu *cpu) { *m=1; if((*f&FLAG_C)==0x00) { *pc=read_u16(cpu->mmu,*sp); (*sp)+=2; (*m)+=2; } };
void RET_C(gbc_cpu *cpu) { *m=1; if((*f&FLAG_C)==0x10) { *pc=read_u16(cpu->mmu,*sp); (*sp)+=2; (*m)+=2; } };

void RST_00H(gbc_cpu *cpu) { rsv(cpu); (*sp)-=2; write_u16(cpu->mmu,*sp,*pc); *pc=0x00; *m=3; };
void RST_08H(gbc_cpu *cpu) { rsv(cpu); (*sp)-=2; write_u16(cpu->mmu,*sp,*pc); *pc=0x08; *m=3; };
void RST_10H(gbc_cpu *cpu) { rsv(cpu); (*sp)-=2; write_u16(cpu->mmu,*sp,*pc); *pc=FLAG_C; *m=3; };
void RST_18H(gbc_cpu *cpu) { rsv(cpu); (*sp)-=2; write_u16(cpu->mmu,*sp,*pc); *pc=0x18; *m=3; };
void RST_20H(gbc_cpu *cpu) { rsv(cpu); (*sp)-=2; write_u16(cpu->mmu,*sp,*pc); *pc=FLAG_H; *m=3; };
void RST_28H(gbc_cpu *cpu) { rsv(cpu); (*sp)-=2; write_u16(cpu->mmu,*sp,*pc); *pc=0x28; *m=3; };
void RST_30H(gbc_cpu *cpu) { rsv(cpu); (*sp)-=2; write_u16(cpu->mmu,*sp,*pc); *pc=0x30; *m=3; };
void RST_38H(gbc_cpu *cpu) { rsv(cpu); (*sp)-=2; write_u16(cpu->mmu,*sp,*pc); *pc=0x38; *m=3; };

void NOP(gbc_cpu *cpu) { *m=1; };

void HALT(gbc_cpu *cpu) { cpu->HALT =1; *m=1; };
void DI(gbc_cpu *cpu) { cpu->IME = 0; *m=1; };
void EI(gbc_cpu *cpu) { cpu->IME = 1; *m=1; };

void rsv(gbc_cpu *cpu) {
	cpu->rsv.a = *a;
	cpu->rsv.b = *b;
	cpu->rsv.c = *c;
	cpu->rsv.d = *d;
	cpu->rsv.e = *e;
	cpu->rsv.f = *f;
	cpu->rsv.h = *h;
	cpu->rsv.l = *l;
};

void rrs(gbc_cpu *cpu) {
	*a = cpu->rsv.a;
	*b = cpu->rsv.b;
	*c = cpu->rsv.c;
	*d = cpu->rsv.d;
	*e = cpu->rsv.e;
	*f = cpu->rsv.f;
	*h = cpu->rsv.h;
	*l = cpu->rsv.l;
};

void MAPcb(gbc_cpu *cpu) {
	u8 i=read_u8(cpu->mmu, (*pc)++);
	*pc &= 65535;
    char s[80];
    /*sprintf(s, "MAPcb: %x", i);*/
    /*cli_printl(s);*/
	if(CB_OPS[i]) CB_OPS[i](cpu);
};

void XX(gbc_cpu *cpu) {
    u8 opcode = read_u8(cpu->mmu, *pc-1);
    char s[80];
    sprintf(s, "ERROR: OPCODE UNIMPLEMETED %x?", opcode);
    cli_printl(s);
}

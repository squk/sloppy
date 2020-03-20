#pragma once

#include "types.h"
#include "gbc_ppu.h"
#include "gbc_mmu.h"

#define FLAG_Z 0x80
#define FLAG_N 0x40
#define FLAG_H 0x20
#define FLAG_C 0x10

// http://bgb.bircd.org/pandocs.htm#timeranddividerregisters
static const u16 TAC_CYCLES[4] = {1024, 16, 64, 256};

typedef struct {
    // two types of timeclocks in the Z80
    int m;
    int t;
} gbc_clock;

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
typedef struct {
    u16 pc, sp;
    u8 a, b, c, d, e, h, l, f; // 8-bit registers
    //u8 t, m; // Clock for last instruction
    gbc_clock clk;
} gbc_cpu_registers;

// save register set
typedef struct {
    u8 a, b, c, d, e, h, l, f;
} gbc_cpu_rsv;

typedef struct
{
    u16 lcd_count; // LCD Timing
    u16 div_count; // Divider Register Counter
    u16 tima_count;    // Timer Counter
    u16 serial_count; // Serial Counter
} gbc_timer;

typedef struct {
    gbc_clock clk;
    gbc_cpu_registers registers;
    gbc_cpu_rsv rsv;
    gbc_timer timer;

    u8 HALT;
    bool quit;

    // interrupts
    u8 IME; // IME - Interrupt Master Enable Flag (Write Only)
    u8 IE; // IE - Interrupt Enable (R/W)
    u8 IF; // IF - Interrupt Flag (R/W)

    gbc_mmu *mmu;
    gbc_ppu *ppu;
} gbc_cpu;

u16 get_hl(gbc_cpu *cpu);
void set_hl(gbc_cpu *cpu, u16 hl);
u16 get_bc(gbc_cpu *cpu);
void set_bc(gbc_cpu *cpu, u16 bc);
u16 get_de(gbc_cpu *cpu);
void set_de(gbc_cpu *cpu, u16 de);

bool flag_z(gbc_cpu *cpu);
bool flag_n(gbc_cpu *cpu);
bool flag_h(gbc_cpu *cpu);
bool flag_c(gbc_cpu *cpu);
bool flag_nz(gbc_cpu *cpu);
bool flag_nn(gbc_cpu *cpu);
bool flag_nh(gbc_cpu *cpu);
bool flag_nc(gbc_cpu *cpu);

void set_flag_z(gbc_cpu *cpu, bool val);
void set_flag_n(gbc_cpu *cpu, bool val);
void set_flag_h(gbc_cpu *cpu, bool val);
void set_flag_c(gbc_cpu *cpu, bool val);

void unset_f(gbc_cpu *cpu, u8 flag);
void set_f(gbc_cpu *cpu, u8 flag);
void put_f(gbc_cpu *cpu, u8 flag, bool val);

void gbc_cpu_reset(gbc_cpu *cpu);
void gbc_cpu_set_boot_state(gbc_cpu *cpu);

void debug_dmg_bootrom(gbc_cpu *cpu, u16 old_pc, u8 opcode);
void gbc_cpu_step(gbc_cpu *cpu);
void gbc_cpu_loop(gbc_cpu *cpu);

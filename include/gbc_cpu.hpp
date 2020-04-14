#pragma once

#include "types.h"
#include "gbc_ppu.hpp"
#include "gbc_mmu.hpp"

#define FLAG_Z 0x80
#define FLAG_N 0x40
#define FLAG_H 0x20
#define FLAG_C 0x10

class gbc_clock {
    public:
        int m; // machine cycles
        int t; // ticks
};

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
class gbc_cpu_registers {
    public:
        u16 pc, sp;
        u8 a, b, c, d, e, h, l, f; // 8-bit registers
        gbc_clock clk;
};

class gbc_cpu {
    private:
        void trace(u8 opcode);
        void handle_interrupts();
        void timer_run();

    public:
        void set_hl(u16 hl);
        void set_bc(u16 bc);
        void set_de(u16 de);

        void set_flag_z(bool val);
        void set_flag_n(bool val);
        void set_flag_h(bool val);
        void set_flag_c(bool val);


        gbc_clock clk;
        gbc_cpu_registers registers;
        gbc_counter counter;

        u8 IME; // Interrupt Master Enable Flag (Write Only)
        u8 HALT;
        bool quit;

        gbc_mmu *mmu;
        gbc_ppu *ppu;

        gbc_cpu();

        u16 get_hl();
        u16 get_bc();
        u16 get_de();

        bool flag_z();
        bool flag_n();
        bool flag_h();
        bool flag_c();

        void reset();
        void set_boot_state();
        void registers_debug(u8 opcode);
        void validate_memory();
        void print_opcode_timing();

        void step();
        void loop();
};

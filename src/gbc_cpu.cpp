#include <string>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>

#include "gbc_cpu.hpp"
#include "gbc_ops.h"
//#include "gbc_ops.hpp"
#include "gbc_io.h"

gbc_cpu::gbc_cpu() {
    reset();
}

u16 gbc_cpu::get_hl() { return (registers.h<<8)+registers.l; }
u16 gbc_cpu::get_bc() { return (registers.b<<8)+registers.c; }
u16 gbc_cpu::get_de() { return (registers.d<<8)+registers.e; }
void gbc_cpu::set_hl(u16 hl) { registers.h=(hl>>8)&255; registers.l = hl&255; }
void gbc_cpu::set_bc(u16 bc) { registers.b=(bc>>8)&255; registers.c = bc&255; }
void gbc_cpu::set_de(u16 de) { registers.d=(de>>8)&255; registers.e = de&255; }

bool gbc_cpu::flag_z() { return (registers.f & FLAG_Z) == FLAG_Z; }
bool gbc_cpu::flag_n() { return (registers.f & FLAG_N) == FLAG_N; }
bool gbc_cpu::flag_h() { return (registers.f & FLAG_H) == FLAG_H; }
bool gbc_cpu::flag_c() { return (registers.f & FLAG_C) == FLAG_C; }

void gbc_cpu::set_flag_z(bool val) { registers.f = (registers.f & ~FLAG_Z) | (val ? FLAG_Z : 0); }
void gbc_cpu::set_flag_n(bool val) { registers.f = (registers.f & ~FLAG_N) | (val ? FLAG_N : 0); }
void gbc_cpu::set_flag_h(bool val) { registers.f = (registers.f & ~FLAG_H) | (val ? FLAG_H : 0); }
void gbc_cpu::set_flag_c(bool val) { registers.f = (registers.f & ~FLAG_C) | (val ? FLAG_C : 0); }

void gbc_cpu::reset() {
    counter.tima = 0;
    counter.div = 0;
    counter.serial = 0;

    registers.a = 0;
    registers.b = 0;
    registers.c = 0;
    registers.d = 0;
    registers.e = 0;
    registers.h = 0;
    registers.l = 0;
    registers.f = 0;

    registers.pc = 0;
    registers.sp = 0;
    registers.clk.m = 0;
    registers.clk.t = 0;

    clk.m = 0;
    clk.t = 0;

    HALT = 0;
    IME = 0;
}

void gbc_cpu::set_boot_state() {
    registers.pc = 0x100;
    registers.a = 0x01;
    registers.f = 0xB0;
    registers.b = 0x00;
    registers.c = 0x13;
    registers.d = 0x00;
    registers.e = 0xD8;
    registers.h = 0x01;
    registers.l = 0x4D;
    registers.sp = 0xFFFE;
    IME = 1;

    mmu->io[0x05] = 0x00;
    mmu->io[0x06] = 0x00;
    mmu->io[0x07] = 0x00;
    mmu->io[0x10] = 0x80;
    mmu->io[0x11] = 0xBF;
    mmu->io[0x12] = 0xF3;
    mmu->io[0x14] = 0xBF;
    mmu->io[0x16] = 0x3F;
    mmu->io[0x17] = 0x00;
    mmu->io[0x19] = 0xBF;
    mmu->io[0x1A] = 0x7F;
    mmu->io[0x1B] = 0xFF;
    mmu->io[0x1C] = 0x9F;
    mmu->io[0x1E] = 0xBF;
    mmu->io[0x20] = 0xFF;
    mmu->io[0x21] = 0x00;
    mmu->io[0x22] = 0x00;
    mmu->io[0x23] = 0xBF;
    mmu->io[0x24] = 0x77;
    mmu->io[0x25] = 0xF3;
    mmu->io[0x26] = 0xF1;
    mmu->io[0x40] = 0x91;
    mmu->io[0x42] = 0x00;
    mmu->io[0x43] = 0x00;
    mmu->io[0x45] = 0x00;
    mmu->io[0x47] = 0xFC;
    mmu->io[0x48] = 0xFF;
    mmu->io[0x49] = 0xFF;
    mmu->io[0x4A] = 0x00;
    mmu->io[0x4B] = 0x00;

    mmu->write_u8(0xFFFF, 0x00);
}

void gbc_cpu::registers_debug(u8 opcode) {
    gbc_cpu_registers *r = &registers;
    char flags[] = "----";
    if (r->f & FLAG_Z) flags[0] = 'Z';
    if (r->f & FLAG_N) flags[1] = 'N';
    if (r->f & FLAG_H) flags[2] = 'H';
    if (r->f & FLAG_C) flags[3] = 'C';

    u8 temp = mmu->read_u8(registers.pc+1);
    printf("A:%02hX F:%s BC:%02hx%02hx DE:%02hx%02hx HL:%02hx%02hx SP:%04hx PC:%04hx    %02hx %s, %x",
            r->a, flags, r->b, r->c, r->d, r->e, r->h, r->l, r->sp, r->pc, opcode, op_string(opcode), temp);
    printf("  M: %d  TIMA: %d  DIV: %d  TAC: %X\n", registers.clk.m, mmu->read_u8(IO_TIMA), mmu->read_u8(IO_DIV), mmu->read_u8(IO_TAC));
    /*printf("\tJOYPAD: %x\n", mmu->read_u8(IO_JOYPAD));*/
}

void gbc_cpu::trace(u8 opcode) {
    registers.pc--;
    registers_debug(opcode);
    registers.pc++;
}

void gbc_cpu::handle_interrupts() {
    u8 IF = mmu->read_u8(IO_IFLAGS);
    u8 IE = mmu->read_u8(IO_IENABLE);
    if((IME || HALT) && (IF & IE & ANY_INTR)) {
        HALT = 0;
        if(IME) {
            // disable interrupts
            IME = 0;

            // push program counter
            mmu->write_u8(--registers.sp, registers.pc >> 8);
            mmu->write_u8(--registers.sp, registers.pc & 0xFF);

            // Call interrupt handler if required
            if(IF & IE & VBLANK_INTR) {
                registers.pc = VBLANK_INTR_ADDR;
                mmu->write_u8(IO_IFLAGS, IF ^ VBLANK_INTR);
                registers.clk.m = 5;
            }
            else if(IF & IE & LCDC_INTR) {
                registers.pc = LCDC_INTR_ADDR;
                mmu->write_u8(IO_IFLAGS, IF ^ LCDC_INTR);
                registers.clk.m = 5;
            }
            else if(IF & IE & TIMER_INTR) {
                registers.pc = TIMER_INTR_ADDR;
                mmu->write_u8(IO_IFLAGS, IF ^ TIMER_INTR);
                registers.clk.m = 5;
            }
            else if(IF & IE & SERIAL_INTR) {
                registers.pc = SERIAL_INTR_ADDR;
                mmu->write_u8(IO_IFLAGS, IF ^ SERIAL_INTR);
                registers.clk.m = 5;
            }
            else if(IF & IE & CONTROL_INTR) {
                registers.pc = CONTROL_INTR_ADDR;
                mmu->write_u8(IO_IFLAGS, IF ^ CONTROL_INTR);
                registers.clk.m = 5;
            }
        }
    }
}

/*
 * Bit  2   - Timer Enable
 * Bits 1-0 - Input Clock Select
 *            00: CPU Clock / 1024 (DMG, CGB:   4096 Hz, SGB:   ~4194 Hz)
 *            01: CPU Clock / 16   (DMG, CGB: 262144 Hz, SGB: ~268400 Hz)
 *            10: CPU Clock / 64   (DMG, CGB:  65536 Hz, SGB:  ~67110 Hz)
 *            11: CPU Clock / 256  (DMG, CGB:  16384 Hz, SGB:  ~16780 Hz)
 *
 * Note: The "Timer Enable" bit only affects the timer, the divider is ALWAYS counting
 */
void gbc_cpu::timer_run() {
    // DIV register timing
    //The divider register increments at a fixed frequency (1 per 256 clock cycles = 1 per 64 machine cycles)
    counter.div += registers.clk.m;
    if (counter.div >= DIV_M_CYCLES) {
        counter.div -= DIV_M_CYCLES;
        (*mmu->get_address_ptr(IO_DIV))++;
    }

    // TIMA register timing
    u8 TAC = mmu->read_u8(IO_TAC);
    if (TAC & MASK_TAC_ENABLE) {
        u8 IF = mmu->read_u8(IO_IFLAGS);
        counter.tima  += registers.clk.m * 4; // *4 since we clk.m is in machine cycles

        if(counter.tima >= TAC_CYCLES[TAC & MASK_TAC_CYCLES]) {
            counter.tima -= TAC_CYCLES[TAC & MASK_TAC_CYCLES];
            u8 temp = mmu->read_u8(IO_TIMA) + 1;

            // For one cycle, after overflowing TIMA, the value in TIMA is 00h, not TMA
            if(temp == 0x00) { // overflow
                mmu->write_u8(IO_TIMA, mmu->read_u8(IO_TMA));
                mmu->write_u8(IO_IFLAGS, IF | TIMER_INTR); // request interrupt
            } else {
                mmu->write_u8(IO_TIMA, temp);
            }
        }
    }
}

void gbc_cpu::step() {
    handle_interrupts();

    // fetch and execute instruction
    u8 opcode = (HALT ? 0x00 : mmu->read_u8(registers.pc++));
    //gbc_cpu_trace(opcode);

    u16 old_pc = registers.pc;
    execute_op(this, opcode);
    timer_run();

    //debug_dmg_bootrom(cpu, old_pc, opcode);

    // Add execution time to the CPU clk
    clk.m += registers.clk.m;
    clk.t += registers.clk.t;

    ppu->run(registers.clk.m);
}

// 0x014D is the header checksum.
// Contains an 8 bit checksum across the cartridge header bytes 0134-014C.
// Formula: x=0: for i=0x134 TO 0x14C: x=x-MEM[i]-1
// The lower 8 bits of the result must match the value at address 0X14D
void gbc_cpu::validate_memory() {
    // nintendo logo checksum
    size_t logo_size = 0x30;
    u16 bios_start = 0x00A8;
    u16 rom_start = 0x0104;

    for (u8 i=0; i < logo_size; i++) {
        u8 bios_val = mmu->read_u8(bios_start+i);
        u8 rom_val = mmu->read_u8(rom_start+i);
        if (bios_val != rom_val) {
            printf("lock up will occur at pc=0x00e9.  mismatch 0x%x bios:0x%x rom:0x%x\n", i, bios_val, rom_val);
        }
    }

    // header checksum
    u16 checksum_start = 0x0134;
    u16 checksum_end = 0x014C;

    int sum = 0;
    for (u16 i=checksum_start; i <= checksum_end; i++) {
        u8 v = mmu->read_u8(i);
        sum = sum - v -1;
        printf("%x  v:%x  sum:%x\n", i, v, sum);
    }
    sum &= 255; // mask to lower 8 bits
    u8 expected = mmu->read_u8(0x14D);
    if (sum != expected) {
        printf("checksum failed at 0x%x   sum: %x    expected: %x\n", checksum_start, sum, expected);
    }
}

void gbc_cpu::loop() {
    /*validate_memory(cpu);*/
    while(!quit) {
        step();
        if (ppu->quit) {
            quit = true;
        }
    }
#if defined(SLOPPY_RENDER)
    atexit(SDL_Quit);
    SDL_Quit();
#endif
}

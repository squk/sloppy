#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>

#include "gbc_cpu.h"
#include "gbc_ops.h"
#include "gbc_io.h"

u16 get_hl(gbc_cpu *cpu) { return (cpu->registers.h<<8)+cpu->registers.l; }
void set_hl(gbc_cpu *cpu, u16 hl) { cpu->registers.h=(hl>>8)&255; cpu->registers.l = hl&255; }
u16 get_bc(gbc_cpu *cpu) { return (cpu->registers.b<<8)+cpu->registers.c; }
void set_bc(gbc_cpu *cpu, u16 bc) { cpu->registers.b=(bc>>8)&255; cpu->registers.c = bc&255; }
u16 get_de(gbc_cpu *cpu) { return (cpu->registers.d<<8)+cpu->registers.e; }
void set_de(gbc_cpu *cpu, u16 de) { cpu->registers.d=(de>>8)&255; cpu->registers.e = de&255; }

bool flag_z(gbc_cpu *cpu) { return (cpu->registers.f & FLAG_Z) == FLAG_Z; }
bool flag_n(gbc_cpu *cpu) { return (cpu->registers.f & FLAG_N) == FLAG_N; }
bool flag_h(gbc_cpu *cpu) { return (cpu->registers.f & FLAG_H) == FLAG_H; }
bool flag_c(gbc_cpu *cpu) { return (cpu->registers.f & FLAG_C) == FLAG_C; }

void set_flag_z(gbc_cpu *cpu, bool val) { cpu->registers.f = (cpu->registers.f & ~FLAG_Z) | (val ? FLAG_Z : 0); }
void set_flag_n(gbc_cpu *cpu, bool val) { cpu->registers.f = (cpu->registers.f & ~FLAG_N) | (val ? FLAG_N : 0); }
void set_flag_h(gbc_cpu *cpu, bool val) { cpu->registers.f = (cpu->registers.f & ~FLAG_H) | (val ? FLAG_H : 0); }
void set_flag_c(gbc_cpu *cpu, bool val) { cpu->registers.f = (cpu->registers.f & ~FLAG_C) | (val ? FLAG_C : 0); }


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

    cpu->HALT = 0;
    cpu->IME = 0;
    cpu->IE = 0;
    cpu->IF = 0;
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
    cpu->IME = 1;

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

void gbc_registers_debug(gbc_cpu *cpu, u8 opcode) {
    gbc_cpu_registers *r = &cpu->registers;
    char flags[] = "----";
    if (r->f & FLAG_Z) flags[0] = 'Z';
    if (r->f & FLAG_N) flags[1] = 'N';
    if (r->f & FLAG_H) flags[2] = 'H';
    if (r->f & FLAG_C) flags[3] = 'C';

    u8 temp = read_u8(cpu->mmu,cpu->registers.pc+1);
    printf("A:%02hX F:%s BC:%02hx%02hx DE:%02hx%02hx HL:%02hx%02hx SP:%04hx PC:%04hx    %02hx %s, %x\n", r->a, flags, r->b, r->c, r->d, r->e, r->h, r->l, r->sp, r->pc, opcode, op_string(opcode), temp);
}

bool setup_stack = false;
bool vram_cleared = false;
bool hit_at = false;
bool init_tile_map = false;
bool hit_screen_frame = false;
bool started_logo_scroll = false;
int hit_cp = 0;
bool hit_gfx_routine = false;
bool wrote_fb_dump = false;

void debug_dmg_bootrom(gbc_cpu *cpu, u16 old_pc, u8 opcode) {
    old_pc--;

    if (old_pc == 0x0000 && !setup_stack) {
        printf("%s: setup stack: sp(%x), expected sp(fffe)\n", op_string(opcode), cpu->registers.sp);
        setup_stack = true;
    }
    if (old_pc == 0x000a && !vram_cleared) {
        bool done = true;
        for (int i=0x9FFF; i>=0x8000; i--) {
            u8 b = read_u8(cpu->mmu, i);
            if (b != 0x0) {
                done = false;
                break;
            }
        }
        if (done) {
            printf("vram cleared %s\n", op_string(opcode));
            vram_cleared = true;
        }
    }
    if (old_pc == 0x001d && !hit_at) {
        printf("%s: setup BG palette\n", op_string(opcode));
    }
    if (old_pc == 0x003e && !hit_at) {
        printf("%s: load bytes into vram for @\n", op_string(opcode));
        hit_at = true;
    }
    if (old_pc == 0x0053 && !init_tile_map) {
        printf("%s: initializing tile map\n", op_string(opcode));
        init_tile_map = true;
    }
    if (old_pc == 0x0055) {
        printf("initializing logo scrolling\n");
    }
    if (old_pc == 0x0068 && !hit_screen_frame) {
        printf("wait for screen frame...\n");
        hit_screen_frame = true;
    }
    if (old_pc == 0x0072 && !started_logo_scroll) {
        printf("starting logo scroll\n");
        started_logo_scroll = true;
    }
    if (old_pc == 0x0095 && !hit_gfx_routine) {
        printf("Graphic routine\n");
        hit_gfx_routine = true;
    }
    if (old_pc == 0x00e0) {
        printf("Nintendo logo comparison routine\n");
        FILE *fp;
        fp = fopen("fb.bin", "w" );
        fwrite(&cpu->ppu->fb, 1, sizeof cpu->ppu->fb, fp);
        fclose(fp);
        printf("dumped framebuffer to file\n");
        //hex_dump("bg_disp", &cpu->ppu->bg_disp, 512*512);
    }
    if (old_pc == 0x00f9) {
        printf("\nlock up?\n");
    }
    if (old_pc >= 0x500 && !wrote_fb_dump) {
        wrote_fb_dump = true;
    }
}

void gbc_cpu_trace(gbc_cpu *cpu, u8 opcode) {
    cpu->registers.pc--;
    gbc_registers_debug(cpu, opcode);
    cpu->registers.pc++;
}
void gbc_interrupt_handler(gbc_cpu *cpu) {
    u8 IF = read_u8(cpu->mmu, IO_IFLAGS);
    u8 IE = read_u8(cpu->mmu, IO_IENABLE);
    if((cpu->IME || cpu->HALT) && (IF & IE & ANY_INTR)) {
        cpu->HALT = 0;
        if(cpu->IME) {
            // disable interrupts
            cpu->IME = 0;

            // push program counter
            write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc >> 8);
            write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc & 0xFF);

            // Call interrupt handler if required
            if(IF & IE & VBLANK_INTR) {
                cpu->registers.pc = VBLANK_INTR_ADDR;
                write_u8(cpu->mmu, IO_IFLAGS, IF ^ VBLANK_INTR);
                cpu->registers.clk.m = 5;
            }
            else if(IF & IE & LCDC_INTR) {
                cpu->registers.pc = LCDC_INTR_ADDR;
                write_u8(cpu->mmu, IO_IFLAGS, IF ^ LCDC_INTR);
                cpu->registers.clk.m = 5;
            }
            else if(IF & IE & TIMER_INTR) {
                cpu->registers.pc = TIMER_INTR_ADDR;
                write_u8(cpu->mmu, IO_IFLAGS, IF ^ TIMER_INTR);
                cpu->registers.clk.m = 5;
            }
            else if(IF & IE & SERIAL_INTR) {
                cpu->registers.pc = SERIAL_INTR_ADDR;
                write_u8(cpu->mmu, IO_IFLAGS, IF ^ SERIAL_INTR);
                cpu->registers.clk.m = 5;
            }
            else if(IF & IE & CONTROL_INTR) {
                cpu->registers.pc = CONTROL_INTR_ADDR;
                write_u8(cpu->mmu, IO_IFLAGS, IF ^ CONTROL_INTR);
                cpu->registers.clk.m = 5;
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
void gbc_cpu_timer_run(gbc_cpu *cpu) {
    // DIV register timing
    cpu->counter.div += cpu->registers.clk.m;
    if (cpu->counter.div >= DIV_CYCLES) {
        cpu->mmu->io[IO_DIV & 0xFF]++;
        cpu->counter.div -= DIV_CYCLES;
    }

    // TIMA register timing
    u8 TAC = read_u8(cpu->mmu, IO_TAC);
    if (TAC & 0x4) {
        u8 IF = read_u8(cpu->mmu, IO_IFLAGS);

        cpu->counter.tima  += cpu->registers.clk.m;
        TAC &= 0x3; // TAC_CYCLES are determined by lower 2 bits

        if(cpu->counter.tima >= TAC_CYCLES[TAC]) {
            cpu->counter.tima -= TAC_CYCLES[TAC];

            u8 temp = read_u8(cpu->mmu, IO_TIMA);
            if(temp == 0xFF) { // overflow
                write_u8(cpu->mmu, IO_TIMA, read_u8(cpu->mmu, IO_TMA)); // reset to value in TMA
                write_u8(cpu->mmu, IO_IFLAGS, IF | TIMER_INTR); // request interrupt
            } else {
                write_u8(cpu->mmu, IO_TIMA, temp + 1);
            }
        }
    }
}

void gbc_cpu_step(gbc_cpu *cpu) {
    gbc_interrupt_handler(cpu);

    // fetch and execute instruction
    u8 opcode = (cpu->HALT ? 0x00 : read_u8(cpu->mmu, cpu->registers.pc++));
    /*gbc_cpu_trace(cpu, opcode);*/

    u16 old_pc = cpu->registers.pc;
    execute_op(cpu, opcode);
    //debug_dmg_bootrom(cpu, old_pc, opcode);

    // Add execution time to the CPU clk
    cpu->clk.m += cpu->registers.clk.m;
    cpu->clk.t += cpu->registers.clk.t;

    gbc_cpu_timer_run(cpu);
    ppu_run(cpu->ppu, cpu->registers.clk.m);
}

// 0x014D is the header checksum.
// Contains an 8 bit checksum across the cartridge header bytes 0134-014C.
// Formula: x=0: for i=0x134 TO 0x14C: x=x-MEM[i]-1
// The lower 8 bits of the result must match the value at address 0X14D
void validate_memory(gbc_cpu *cpu) {
    // nintendo logo checksum
    size_t logo_size = 0x30;
    u16 bios_start = 0x00A8;
    u16 rom_start = 0x0104;

    for (u8 i=0; i < logo_size; i++) {
        u8 bios_val = read_u8(cpu->mmu, bios_start+i);
        u8 rom_val = read_u8(cpu->mmu, rom_start+i);
        if (bios_val != rom_val) {
            printf("lock up will occur at pc=0x00e9.  mismatch 0x%x bios:0x%x rom:0x%x\n", i, bios_val, rom_val);
        }
    }

    // header checksum
    u16 checksum_start = 0x0134;
    u16 checksum_end = 0x014C;

    int sum = 0;
    for (u16 i=checksum_start; i <= checksum_end; i++) {
        u8 v = read_u8(cpu->mmu, i);
        sum = sum - v -1;
        printf("%x  v:%x  sum:%x\n", i, v, sum);
    }
    sum &= 255; // mask to lower 8 bits
    u8 expected = read_u8(cpu->mmu, 0x14D);
    if (sum != expected) {
        printf("checksum failed at 0x%x   sum: %x    expected: %x\n", checksum_start, sum, expected);
    }
}

void gbc_cpu_loop(gbc_cpu *cpu) {
    ppu_init(cpu->ppu);
    /*validate_memory(cpu);*/
    while(!cpu->quit) {
        gbc_cpu_step(cpu);
        if (cpu->ppu->quit) {
            cpu->quit = true;
        }
    }
#if defined(SLOPPY_RENDER)
    atexit(SDL_Quit);
    SDL_Quit();
#endif
}

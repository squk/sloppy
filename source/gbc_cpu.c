#include <stdio.h>
#include <string.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_events.h>

#include "gbc_cpu.h"
#include "gbc_ops.h"
#include "gbc_io.h"

bool FZ(gbc_cpu *cpu) { return (cpu->registers.f & FLAG_Z) == FLAG_Z; }
bool FN(gbc_cpu *cpu) { return (cpu->registers.f & FLAG_N) == FLAG_N; }
bool FH(gbc_cpu *cpu) { return (cpu->registers.f & FLAG_Z) == FLAG_Z; }
bool FC(gbc_cpu *cpu) { return (cpu->registers.f & FLAG_C) == FLAG_C; }

void set_f(gbc_cpu *cpu, u8 flag) {
    cpu->registers.f |= flag;
}

void unset_f(gbc_cpu *cpu, u8 flag) {
    cpu->registers.f &= ~flag;
}

void put_f(gbc_cpu *cpu, u8 flag, bool val) {
    if (val) set_f(cpu, flag);
    else unset_f(cpu, flag);
}

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

void gbc_registers_debug(gbc_cpu *cpu, u8 opcode) {
    printf("OP: %x   %s\n", opcode, OPS_STR[opcode]);
    printf("A: %x    B: %x    C: %x\n", cpu->registers.a, cpu->registers.b, cpu->registers.c);
    printf("D: %x    E: %x    F: %x\n", cpu->registers.d, cpu->registers.e, cpu->registers.f);
    printf("H: %x    L: %x    M: %x\n", cpu->registers.h, cpu->registers.l, cpu->registers.clk.m);
    printf("T: %x    SP: %x    PC: %x\n", cpu->registers.clk.t, cpu->registers.sp, cpu->registers.pc);
    printf("press enter\n");
    getchar();
}

void d_pc_eq(gbc_cpu *cpu, u8 opcode, u8 eq) {
    if (opcode == 0)
        return;
    u8 pc = cpu->registers.pc;
    pc--;
    if (cpu->mmu->in_bios && pc == eq) {
         printf("OP: %s, PC:%x\n", OPS_STR[opcode], pc);
    }
}

void d_pc_eq_v(gbc_cpu *cpu, u8 opcode, u8 eq) {
    if (opcode == 0)
        return;
    u8 pc = cpu->registers.pc;
    pc--;
    if (cpu->mmu->in_bios && pc == eq) {
        gbc_registers_debug(cpu, opcode);
    }
}

void d_pc_r(gbc_cpu *cpu, u16 pc, u8 opcode, u8 low, u8 high) {
    pc--;
    if (cpu->mmu->in_bios && pc >= low && pc <= high) {
        gbc_registers_debug(cpu, opcode);
        /*printf("OP: %s, PC:%x\n", OPS_STR[opcode], pc);*/
    }
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
    /*gbc_registers_debug(cpu, opcode);*/
    old_pc--;

    if (old_pc == 0x0000 && !setup_stack) {
        printf("%s: setup stack: sp(%x), expected sp(fffe)\n", OPS_STR[opcode], cpu->registers.sp);
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
            printf("vram cleared %s\n", OPS_STR[opcode]);
            vram_cleared = true;
        }
    }
    if (old_pc == 0x001d && !hit_at) {
        printf("%s: setup BG palette\n", OPS_STR[opcode]);
    }
    if (old_pc == 0x003e && !hit_at) {
        printf("%s: load bytes into vram for @\n", OPS_STR[opcode]);
        hit_at = true;
    }
    if (old_pc == 0x0053 && !init_tile_map) {
        printf("%s: initializing tile map\n", OPS_STR[opcode]);
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
        fp = fopen("fb.bin" , "w" );
        fwrite(&cpu->gpu->fb, 1, sizeof cpu->gpu->fb, fp);
        fclose(fp);
        printf("dumped framebuffer to file\n");
    }
    if (old_pc == 0x00f9) {
        printf("\nlock up?\n");
    }
    if (old_pc >= 0x500 && !wrote_fb_dump) {
        wrote_fb_dump = true;
    }
}

void gbc_cpu_step(gbc_cpu *cpu) {
	if((cpu->IME || cpu->HALT) && (cpu->IF & cpu->IE & ANY_INTR)) {
		cpu->HALT = 0;

		if(cpu->IME) {
			printf("Interrupt Master Enable\n");
			/* Disable interrupts */
			cpu->IME = 0;

			/* Push Program Counter */
			write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc >> 8);
			write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc & 0xFF);

			/* Call interrupt handler if required. */
			if(cpu->IF & cpu->IE & VBLANK_INTR) {
				cpu->registers.pc = VBLANK_INTR_ADDR;
				cpu->IF ^= VBLANK_INTR;
			}
			else if(cpu->IF & cpu->IE & LCDC_INTR) {
				cpu->registers.pc = LCDC_INTR_ADDR;
				cpu->IF ^= LCDC_INTR;
			}
			else if(cpu->IF & cpu->IE & TIMER_INTR) {
				cpu->registers.pc = TIMER_INTR_ADDR;
				cpu->IF ^= TIMER_INTR;
			}
			else if(cpu->IF & cpu->IE & SERIAL_INTR) {
				cpu->registers.pc = SERIAL_INTR_ADDR;
				cpu->IF ^= SERIAL_INTR;
			}
			else if(cpu->IF & cpu->IE & CONTROL_INTR) {
				cpu->registers.pc = CONTROL_INTR_ADDR;
				cpu->IF ^= CONTROL_INTR;
			}
		}
	}

    // Fetch and execute instruction
    u8 opcode = (cpu->HALT ? 0x00 : read_u8(cpu->mmu, cpu->registers.pc++));

    u16 old_pc = cpu->registers.pc;

    void (*funcPtr)(gbc_cpu*) = *OPS[opcode];
    (funcPtr)(cpu);

    debug_dmg_bootrom(cpu, old_pc, opcode);
    if (!cpu->mmu->in_bios) {
        /*hex_dump("framebuffer2", cpu->gpu->fb, 0x200);*/
    }

    // Add execution time to the CPU clk
    cpu->clk.m += cpu->registers.clk.m;
    cpu->clk.t += cpu->registers.clk.t;
    gpu_run(cpu->gpu, cpu->registers.clk.m);
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
    size_t checksum_size = 0x19;
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

    hex_dump("BIOS", cpu->mmu->bios, 0x100);
    hex_dump("ROM", cpu->mmu->rom, 0x200);
}

void gbc_cpu_loop(gbc_cpu *cpu) {
    printf("init cpu loop\n");

    execute_init(cpu);
    gpu_init(cpu->gpu);
    printf("begin cpu loop\n");

    validate_memory(cpu);
    while(!cpu->gpu->quit) {
        gbc_cpu_step(cpu);
    }
    atexit(SDL_Quit);
}

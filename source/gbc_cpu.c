#include <stdio.h>
#include <time.h>
#include <string.h>

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
    printf("OP: %x   %s\n", cpu->registers.clk.m, OPS_STR[opcode]);
    printf("A: %x    B: %x    C: %x\n", cpu->registers.a, cpu->registers.b, cpu->registers.c);
    printf("D: %x    E: %x    F: %x\n", cpu->registers.d, cpu->registers.e, cpu->registers.f);
    printf("H: %x    L: %x    M: %x\n", cpu->registers.h, cpu->registers.e, cpu->registers.clk.m);
    printf("T: %x    SP: %x    PC: %x\n", cpu->registers.clk.t, cpu->registers.sp, cpu->registers.pc);
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

void d_pc_r(gbc_cpu *cpu, u8 opcode, u8 low, u8 high) {
    if (opcode == 0)
        return;
    u8 pc = cpu->registers.pc;
    pc--;
    if (cpu->mmu->in_bios && pc > low && pc < high) {
        printf("OP: %s, PC:%x\n", OPS_STR[opcode], pc);
    }
}

void debug_dmg_bootrom(gbc_cpu *cpu, u8 opcode) {
    u16 pc = cpu->registers.pc;
    pc--;
    if (pc == 0x0003) {
        printf("%s: setup stack: sp(%x), expected sp(fffe)", OPS_STR[opcode], cpu->registers.sp);
    }
    if (pc == 0x0034) {
        printf("%s: load bytes into vram for @", OPS_STR[opcode]);
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
    /*u8 lcdcont = read_u8(cpu->mmu, IO_LCDCONT);*/

    gbc_cpu cpu_clone = *cpu;

    void (*funcPtr)(gbc_cpu*) = *OPS[opcode];
    (funcPtr)(cpu);
    debug_dmg_bootrom(&cpu_clone, opcode);

    // Add execution time to the CPU clk
    cpu->clk.m += cpu->registers.clk.m;
    cpu->clk.t += cpu->registers.clk.t;
    gpu_run(cpu->gpu, cpu->registers.clk.m);
}

void gbc_cpu_loop(gbc_cpu *cpu) {
    execute_init(cpu);
    gpu_start_frame(cpu->gpu);


    /*u8 logo[0x30] = {0};*/
    /*int l_start = 0x104;*/
    /*int l_end = 0x134;*/
    /*for (int i=l_start; i<l_end; i++) {*/
        /*logo[i-l_start] = read_u8(cpu->mmu, i);*/
    /*}*/
    printf("started loop");
    while(1) {
        gbc_cpu_step(cpu);

        if (cpu->gpu->fb[5] != 0) {
            printf("fb: %x\n", cpu->gpu->fb[5]);
        }
    }
}

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
    cpu.registers.clock.m = 0;
    cpu.registers.clock.t = 0;

    cpu.clock.m = 0;
    cpu.clock.t = 0;
}

void gba_cpu_loop(gbc_cpu Icpu) {

}

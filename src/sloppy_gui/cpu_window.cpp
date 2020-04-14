#include <iostream>
#include "gbc_emu.hpp"
#include "gbc_io.h"

void gbc_emu::cpu_window() {
    ImGui::Begin("CPU");
    char flags[] = "----";
    if (cpu.registers.f & FLAG_Z) flags[0] = 'Z';
    if (cpu.registers.f & FLAG_N) flags[1] = 'N';
    if (cpu.registers.f & FLAG_H) flags[2] = 'H';
    if (cpu.registers.f & FLAG_C) flags[3] = 'C';
    ImGui::Text("AF:%02hx%02hx BC:%02hx%02hx DE:%02hx%02hx HL:%02hx%02hx SP:%04hx PC:%04hx",
            cpu.registers.a, cpu.registers.f, cpu.registers.b, cpu.registers.c, cpu.registers.d, cpu.registers.e, cpu.registers.h, cpu.registers.l, cpu.registers.sp, cpu.registers.pc);
    ImGui::Text("Flags: %s", flags);
    ImGui::End();
}

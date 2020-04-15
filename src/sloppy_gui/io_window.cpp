#include <iostream>
#include "gbc_emu.hpp"
#include "gbc_io.h"
bool io_window_open = true;

void gbc_emu::io_window() {

    ImGui::SetNextWindowSize(ImVec2(200, 372));
    ImGui::Begin("IO", &io_window_open, ImGuiWindowFlags_NoResize);
    //ImVec2 s = ImGui::GetWindowSize();
    //printf("w: %f h:%f\n", s.x, s.y);
    ImGui::Text("0xFF00\t[JOYP]: %d", mmu.read_u8(IO_JOYPAD));
    ImGui::Text("0xFF01\t[SB]: %d", mmu.read_u8(0xFF01));
    ImGui::Text("0xFF02\t[SC]: %d", mmu.read_u8(0xFF02));
    ImGui::Text("0xFF04\t[DIV]: %d", mmu.read_u8(IO_DIV));
    ImGui::Text("0xFF05\t[TIMA]: %d", mmu.read_u8(IO_TIMA));
    ImGui::Text("0xFF06\t[TMA]: %d", mmu.read_u8(IO_TMA));
    ImGui::Text("0xFF07\t[TAC]: %d", mmu.read_u8(IO_TAC));
    ImGui::Text("0xFF0F\t[1f]: %d", mmu.read_u8(0xFF0F));
    ImGui::Text("0xFF40\t[LCDC]: %d", mmu.read_u8(IO_LCDCONT));
    ImGui::Text("0xFF41\t[STAT]: %d", mmu.read_u8(IO_LCDSTAT));
    ImGui::Text("0xFF42\t[SCY]: %d", mmu.read_u8(IO_SCROLLY));
    ImGui::Text("0xFF43\t[SCX]: %d", mmu.read_u8(IO_SCROLLX));
    ImGui::Text("0xFF44\t[LY]: %d", mmu.read_u8(IO_CURLINE));
    ImGui::Text("0xFF45\t[LYC]: %d", mmu.read_u8(IO_CMPLINE));
    ImGui::Text("0xFF47\t[BGP]: %d", mmu.read_u8(IO_BGRDPAL));
    ImGui::Text("0xFF48\t[OBP0]: %d", mmu.read_u8(IO_OBJ0PAL));
    ImGui::Text("0xFF49\t[OBP1]: %d", mmu.read_u8(IO_OBJ1PAL));
    ImGui::Text("0xFF4A\t[WY]: %d", mmu.read_u8(IO_WNDPOSY));
    ImGui::Text("0xFF4B\t[WX]: %d", mmu.read_u8(IO_WNDPOSX));
    ImGui::Text("0xFFFF\t[IE]: %d", mmu.read_u8(IO_IENABLE));
    ImGui::End();
}

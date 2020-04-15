#include <iostream>
#include "gbc_emu.hpp"
#include "gbc_io.h"

bool mbc_window_open = true;

void gbc_emu::mbc_window() {
    ImGui::Begin("MBC", &mbc_window_open, ImGuiWindowFlags_NoResize);
    ImGui::Text("TITLE %s", mbc.title.c_str());
    ImGui::Text("TYPE %s", mbc.TYPE_STR().c_str());
    ImGui::Text("ROM SIZE: 0x%x  BANKS: %d\n", mbc.rom_size, mbc.num_rom_banks);
    ImGui::Text("RAM SIZE: %d    BYTES: %d   BANKS: %d\n", mbc.ram_size, mbc.ram_numbytes, mbc.num_ram_banks);
    ImGui::End();
}

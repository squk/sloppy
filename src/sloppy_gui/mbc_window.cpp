#include <iostream>
#include "gbc_emu.hpp"
#include "gbc_io.h"

bool mbc_window_open = true;

void mbcText(std::string title, u8 val) {
#if defined(SLOPPY_RENDER)
    const ImVec4 c(1.f, 0.5f, 0.2f, 1.f);
    ImGui::Text("%s:", title.c_str());
    ImGui::SameLine();
    ImGui::TextColored(c, "%02X", val);
    ImGui::SameLine();
#endif
}

void gbc_emu::mbc_window() {
#if defined(SLOPPY_RENDER)
    ImGui::Begin("MBC", &mbc_window_open);
    ImGui::Text("TITLE: %s\tCGB_FLAG: ", mmu.mbc.title.c_str());
    ImGui::SameLine();
    ImVec4 color = ImVec4(1.0f, 1.0f, 1.0f, 1.f);
    if (mmu.mbc.cgb_flag == 0x80) {
        color = ImVec4(1.f, 0.5f, 0.2f, 1.f);
    } else if (mmu.mbc.cgb_flag == 0xC0) {
        color = ImVec4(1.f, 0.0f, 0.2f, 1.f);
    }
    ImGui::TextColored(color, "%02X", mmu.mbc.cgb_flag);

    ImGui::Text("TYPE: %s", mmu.mbc.TYPE_STR().c_str());
    ImGui::Text("ROM SIZE: 0x%x\tBANKS: %d\n", mmu.mbc.rom_size, mmu.mbc.num_rom_banks);
    ImGui::Text("RAM SIZE: %d\tBYTES: %ld\tBANKS: %d\n", mmu.mbc.ram_size, mmu.mbc.ram_numbytes, mmu.mbc.num_ram_banks);
    mbcText("RAMG", mmu.mbc.RAMG);
    mbcText("BANK1", mmu.mbc.BANK1);
    mbcText("BANK2", mmu.mbc.BANK2);
    mbcText("MODE", mmu.mbc.MODE);
    ImGui::End();
#endif
}

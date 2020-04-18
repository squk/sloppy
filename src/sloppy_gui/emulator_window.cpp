#include <iostream>
#include "gbc_emu.hpp"
#include "gbc_io.h"

bool emulator_window_open = true;
u8 lcd_fb[SIZE_X * SIZE_Y * 3]; // 3 bytes per pixel
int emu_scale = 1;

void gbc_emu::emulator_menubar() {
#if defined(SLOPPY_RENDER)
    if (ImGui::BeginMenuBar()) {
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem("Exit")) {
                cpu.quit = true;
            }
            ImGui::EndMenu();
        }
        if (ImGui::BeginMenu("Window")) {
            for (int scale = 1; scale <= 4; ++scale) {
                char label[3];
                snprintf(label, sizeof(label), "%dx", scale);
                if (ImGui::MenuItem(label)) {
                    // This is pretty cheesy, seems like there must be a better way.
                    ImGuiStyle& style = ImGui::GetStyle();
                    ImVec2 size = ImVec2(SIZE_X, SIZE_Y);
                    ImGui::SetWindowSize(size);
                }
            }
            //ImGui::Separator();
            //ImGui::MenuItem("TileData", NULL, &tiledata_window.is_open);
            //ImGui::MenuItem("Obj", NULL, &obj_window.is_open);
            //ImGui::MenuItem("Map", NULL, &map_window.is_open);
            //ImGui::MenuItem("Memory", NULL, &memory_window.is_open);
            //ImGui::MenuItem("ROM", NULL, &rom_window.is_open);
            //ImGui::MenuItem("IO", NULL, &io_window.is_open);
            ImGui::EndMenu();
        }
        ImGui::EndMenuBar();
    }
#endif
}

void gbc_emu::emulator_window() {
#if defined(SLOPPY_RENDER)
    ImGui::Begin(("EMU: " + mmu.mbc.title).c_str(), &emulator_window_open, ImGuiWindowFlags_NoResize);
    glBindTexture(GL_TEXTURE_2D, lcd_tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

    glEnable(GL_TEXTURE_2D);

    u8 *fb_px = &lcd_fb[0];
    for (int y = 0; y < SIZE_Y; y++) {
        for (int x = 0; x < SIZE_X; x++) {
            int px_index = y * SIZE_X + x;
            u8 color = ppu.fb[px_index];
            u32 fb_color = get_paletted_color(ppu.fb[px_index]);
            *fb_px++ = (fb_color >> 16) & 0xFF; *fb_px++ = (fb_color >> 8) & 0xFF; *fb_px++ = (fb_color & 0xFF);
        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, SIZE_X, SIZE_Y, 0, GL_RGB, GL_UNSIGNED_BYTE, lcd_fb);

    ImGui::Image((void*)(intptr_t)lcd_tex, ImVec2(SIZE_X*1.5f, SIZE_Y*1.5f));
    ImGui::End();
#endif
}

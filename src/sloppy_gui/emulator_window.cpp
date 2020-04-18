#include <iostream>
#include "gbc_emu.hpp"
#include "gbc_io.h"

bool emulator_window_open = true;
u8 lcd_fb[SIZE_X * SIZE_Y * 3]; // 3 bytes per pixel

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

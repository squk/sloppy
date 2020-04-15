#include <iostream>
#include "gbc_emu.hpp"
#include "gbc_io.h"

bool emulator_window_open = true;
u8 lcd_fb[SIZE_X * SIZE_Y * 3]; // 3 bytes per pixel

void gbc_emu::emulator_window() {
    ImGui::Begin(("EMU: " + mmu.mbc.title).c_str(), &emulator_window_open, ImGuiWindowFlags_NoResize);
    glBindTexture(GL_TEXTURE_2D, lcd_tex);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);

	glEnable(GL_TEXTURE_2D);

    u8 *fb_px = &lcd_fb[0];
    for (int y = 0; y < SIZE_Y; y++) {
        for (int x = 0; x < SIZE_X; x++) {
            int px_index = y * SIZE_X + x;
            u8 color = ppu.fb[px_index];
            u8 r,g,b;
            switch(color) {
                case 0:             // 332c50
                    r = 0x33; g = 0x2c; b = 0x50;
                    break;
                case 1:             // 46878f
                    r = 0x46; g = 0x87; b = 0x8f;
                    break;
                case 2:             // 94e344
                    r = 0x94; g = 0xe3; b = 0x44;
                    break;
                case 3:             // e2f3e4
                    r = 0xe2; g = 0xf3; b = 0xe4;
                    break;
            }
            *fb_px++ = r;
            *fb_px++ = g;
            *fb_px++ = b;
        }
    }
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, SIZE_X, SIZE_Y, 0, GL_RGB, GL_UNSIGNED_BYTE, lcd_fb);

    ImGui::Image((void*)(intptr_t)lcd_tex, ImVec2(SIZE_X*1.5f, SIZE_Y*1.5f));
    ImGui::End();
}

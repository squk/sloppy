#include <iostream>
#include "gbc_emu.hpp"
#include "gbc_io.h"

bool map_window_open = true;
u8 bg_fb[512 * 512 * 3]; // 3 bytes per pixel
u8 win_fb[512 * 512 * 3]; // 3 bytes per pixel
u8 obj_fb[512 * 512 * 3]; // 3 bytes per pixel

u32 get_paletted_color(u8 color) {
    u8 r=0, g=0, b=0;
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
    return (r << 16) | (g << 8) | (b << 0);
}

void gbc_emu::map_window() {
    ImGui::Begin("MAP", &map_window_open, ImGuiWindowFlags_None);

    u8 *bg_px = &bg_fb[0];
    u8 *win_px = &win_fb[0];
    u8 *obj_px = &obj_fb[0];
    for (int y = 0; y < 512; y++) {
        for (int x = 0; x < 512; x++) {
            int px_index = y * 512 + x;
            u32 bg_color = get_paletted_color(ppu.bg_disp[px_index]);
            u8 win_color = get_paletted_color(ppu.win_disp[px_index]);
            u8 obj_color = get_paletted_color(ppu.obj_disp[px_index]);

            *bg_px++ = (bg_color >> 16) & 0xFF; *bg_px++ = (bg_color >> 8) & 0xFF; *bg_px++ = (bg_color & 0xFF);
            *win_px++ = (win_color >> 16) & 0xFF; *win_px++ = (win_color >> 8) & 0xFF; *win_px++ = (win_color & 0xFF);
            *obj_px++ = (obj_color >> 16) & 0xFF; *obj_px++ = (obj_color >> 8) & 0xFF; *obj_px++ = (obj_color & 0xFF);
        }
    }
    glBindTexture(GL_TEXTURE_2D, bg_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, bg_fb);
    ImGui::Text("BG:");
    ImGui::Image((void*)(intptr_t)bg_tex, ImVec2(256, 256));

    glBindTexture(GL_TEXTURE_2D, win_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, win_fb);
    ImGui::Text("WIN:");
    ImGui::Image((void*)(intptr_t)win_tex, ImVec2(256, 256));

    glBindTexture(GL_TEXTURE_2D, obj_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 512, 512, 0, GL_RGB, GL_UNSIGNED_BYTE, obj_fb);
    ImGui::Text("OBJ:");
    ImGui::Image((void*)(intptr_t)obj_tex, ImVec2(256, 256));

    ImGui::End();
}

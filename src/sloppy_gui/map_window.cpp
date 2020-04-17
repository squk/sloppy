#include <iostream>
#include "gbc_emu.hpp"
#include "gbc_io.h"

bool map_window_open = true;
u8 bg_fb[256 * 256 * 3]; // 3 bytes per pixel
u8 win_fb[256 * 256 * 3]; // 3 bytes per pixel
u8 obj_fb[256 * 256 * 3]; // 3 bytes per pixel

void gbc_emu::map_window() {
#if defined(SLOPPY_RENDER)
    ImGui::Begin("MAP", &map_window_open);

    u8 *bg_px = &bg_fb[0];
    u8 *win_px = &win_fb[0];
    u8 *obj_px = &obj_fb[0];
    for (int y = 0; y < 256; y++) {
        for (int x = 0; x < 256; x++) {
            int px_index = y * 256 + x;
            u32 bg_color = get_paletted_color(ppu.bg_disp[px_index] & 0x3);
            u32 win_color = get_paletted_color(ppu.win_disp[px_index] & 0x3);
            u32 obj_color = get_paletted_color(ppu.obj_disp[px_index] & 0x3);

            *bg_px++ = (bg_color >> 16) & 0xFF; *bg_px++ = (bg_color >> 8) & 0xFF; *bg_px++ = (bg_color & 0xFF);
            *win_px++ = (win_color >> 16) & 0xFF; *win_px++ = (win_color >> 8) & 0xFF; *win_px++ = (win_color & 0xFF);
            *obj_px++ = (obj_color >> 16) & 0xFF; *obj_px++ = (obj_color >> 8) & 0xFF; *obj_px++ = (obj_color & 0xFF);
        }
    }

    //ImDrawList* draw_list = ImGui::GetWindowDrawList();
    //draw_list->AddRect(ImVec2(x, y), ImVec2(x+sz, y+sz), col32, 10.0f, ImDrawCornerFlags_TopLeft|ImDrawCornerFlags_BotRight, th);
    //x += sz+spacing;
    //draw_list->AddTriangle(ImVec2(x+sz*0.5f, y), ImVec2(x+sz,y+sz-0.5f), ImVec2(x,y+sz-0.5f), col32, th);
    //x += sz+spacing;

    glBindTexture(GL_TEXTURE_2D, bg_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, bg_fb);
    ImGui::Text("BG:\t");
    ImGui::Image((void*)(intptr_t)bg_tex, ImVec2(256, 256));

    glBindTexture(GL_TEXTURE_2D, win_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, win_fb);
    ImGui::Text("WIN:\t:");
    ImGui::Image((void*)(intptr_t)win_tex, ImVec2(256, 256));

    glBindTexture(GL_TEXTURE_2D, obj_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
    glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 256, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, obj_fb);
    ImGui::Text("OBJ:\t");
    ImGui::Image((void*)(intptr_t)obj_tex, ImVec2(256, 256));

    ImGui::End();
#endif
}

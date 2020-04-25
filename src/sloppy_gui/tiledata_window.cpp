#include <iostream>
#include "gbc_emu.hpp"
#include "gbc_io.h"

bool tiledata_window_open = true;
u8 tiles_fb[256 * 256 * 3]; // 3 bytes per pixel

void gbc_emu::tiledata_window() {
#if defined(SLOPPY_RENDER)
    ImGui::Begin("TILE DATA", &tiledata_window_open);

    u8 *px = &tiles_fb[0];
    for (int y=0; y < 32; y++) { // 32 tiles high
        for (int x=0; x < 16; x++) { // 16 tiles wide
            int tile_num = (y * 16 + x) * 16;
            u8 t1 = mmu.read_u8(0x9c00 + tile_num);
            u8 t2 = mmu.read_u8(0x9c00 + tile_num + 1);
            //printf("%x\n", 0x8000 + tile_num);

            for (int j = 0; j < 8; j++) {
                u32 color = 0;
                u8 color_index = ((t1 & (1 << (7 - j))) ? 1 : 0) +
                    ((t2 & (1 << (7 - j))) ? 2 : 0);
                color = get_paletted_color(color_index & 0x3);
                *px++ = (color >> 16) & 0xFF; *px++ = (color >> 8) & 0xFF; *px++ = (color & 0xFF);
            }
        }
    }
    //ImDrawList* draw_list = ImGui::GetWindowDrawList();
    //draw_list->AddRect(ImVec2(x, y), ImVec2(x+sz, y+sz), col32, 10.0f, ImDrawCornerFlags_TopLeft|ImDrawCornerFlags_BotRight, th);
    //x += sz+spacing;
    //draw_list->AddTriangle(ImVec2(x+sz*0.5f, y), ImVec2(x+sz,y+sz-0.5f), ImVec2(x,y+sz-0.5f), col32, th);
    //x += sz+spacing;

    glBindTexture(GL_TEXTURE_2D, tiledata_tex);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	glEnable(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, 128, 256, 0, GL_RGB, GL_UNSIGNED_BYTE, tiles_fb);
    ImGui::Image((void*)(intptr_t)tiledata_tex, ImVec2(128, 256));

    ImGui::End();
#endif
}

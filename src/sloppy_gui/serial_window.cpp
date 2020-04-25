#include <iostream>
#include "gbc_emu.hpp"
#include "gbc_io.h"

bool serial_window_open = true;

static ImGuiTextBuffer textbuf;
void gbc_emu::serial_window() {
    ImGui::Begin("SERIAL", &serial_window_open, ImGuiWindowFlags_None);
    ImGui::End();
}

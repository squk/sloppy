#include <stdio.h>
#include "gbc_emu.hpp"

int main() {
    /*gui_init();*/
    gbc_emu emu = gbc_emu();
    emu.test();
   return 0;
}

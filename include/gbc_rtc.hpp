#pragma once

#include "types.h"

class gbc_rtc {
    public:
        u8 seconds; // 08h  RTC S   Seconds   0-59 (0-3Bh)
        u8 minutes; // 09h  RTC M   Minutes   0-59 (0-3Bh)
        u8 hours;   // 0Ah  RTC H   Hours     0-23 (0-17h)
        u8 DL;      // 0Bh  RTC DL  Lower 8 bits of Day Counter (0-FFh)
        u8 DH;      // 0Ch  RTC DH  Upper 1 bit of Day Counter, Carry Bit, Halt Flag
                    //       Bit 0  Most significant bit of Day Counter (Bit 8)
                    //       Bit 6  Halt (0=Active, 1=Stop Timer)
                    //       Bit 7  Day Counter Carry Bit (1=Counter Overflow)
};

#pragma once

#include "types.h"

typedef struct {
    u16 div;      // Divider Register Counter
    u16 tima;     // Timer Counter
    u16 serial;   // Serial Counter
    bool enabled;
} gbc_counter;

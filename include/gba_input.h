#pragma once

unsigned short input_cur = 0x03FF;
unsigned short input_prev = 0x03FF;

#define REG_KEYINPUT  (* (volatile unsigned short*) 0x4000130)

#define KEY_A        0x0001
#define KEY_B        0x0002
#define KEY_SELECT   0x0004
#define KEY_START    0x0008
#define KEY_RIGHT    0x0010
#define KEY_LEFT     0x0020
#define KEY_UP       0x0040
#define KEY_DOWN     0x0080
#define KEY_R        0x0100
#define KEY_L        0x0200

#define KEY_MASK     0xFC00

inline void key_poll()
{
    input_prev = input_cur;
    input_cur = REG_KEYINPUT | KEY_MASK;
}

inline unsigned short key_pressed(unsigned short key_code)
{
    return (key_code) & (~input_cur & input_prev);
}

inline unsigned short key_released(unsigned short key_code)
{
    return  (key_code) & (input_cur & ~input_prev);
}

inline unsigned short key_state(unsigned short key_code)
{
    return !(key_code & (input_cur) );
}

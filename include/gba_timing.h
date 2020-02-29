#pragma once

#define TIMESYSTEM 0x0
#define TIME64 0x1
#define TIME256 0x2
#define TIME1024 0x3

#define TIMEOVERFLOW 0x4
#define TIMEIRQ 0x40
#define TIMEENABLE 0x80

int iMilliSecs, iSecs;

// DECLARE AN ARRAY POINTER TO THE FOUR TIMER CONTROL REGISTERS //
volatile u8* REG_TMCNT[4] = {
    (u8*)0x4000102,
    (u8*)0x4000106,
    (u8*)0x400010A,
    (u8*)0x400010E
};

// DECLARE AN ARRAY POINTER TO THE FOUR TIMER COUNTER REGISTERS //
volatile u8* REG_TMD[4] = {
    (u8*)0x4000100,
    (u8*)0x4000104,
    (u8*)0x4000108,
    (u8*)0x400010C
};

void reset_timer() {
    /// Reset The Timers To 0 So Any Previous Use Of The Timers Are Cleared //
    REG_TMD[2] = REG_TMD[3] = 0;
}

void start_timer() {
    // Enable Timer #2 And Set The Increment Frequency To 256 Cycles //
    REG_TMCNT[2] = (TIMEENABLE | TIME256);

    // Enable Timer #3 And Set It To Increment When Timer #2 Overflows //
    REG_TMCNT[3] = (TIMEOVERFLOW | TIMEENABLE);

    reset_timer();
}

void stop_timer() {
    reset_timer();

    // Clear The Control Register For Timer #2 And Timer #3 – Disable It //
    REG_TMCNT[2] = REG_TMCNT[3] = 0;
}

#pragma once

// IO ports
#define IO_JOYPAD  0xFF00
#define IO_SIODATA 0xFF01
#define IO_SIOCONT 0xFF02
#define IO_DIVIDER 0xFF04 // DIV - Divider Register (R/W)
#define IO_TIMECNT 0xFF05 // TIMA - Timer counter (R/W)
#define IO_TIMEMOD 0xFF06 // TMA - Timer Modulo (R/W
#define IO_TIMCONT 0xFF07 // TAC - Timer Control (R/W)
#define IO_TACRATE 0x0002
/*
 * INT 50 - Timer Interrupt
 * Each time when the timer overflows (ie. when TIMA gets bigger than FFh), then
 * an interrupt is requested by setting Bit 2 in the IF Register (FF0F). When that
 * interrupt is enabled, then the CPU will execute it by calling the timer
 * interrupt vector at 0050h.
 */

#define IO_IFLAGS  0xFF0F

// video registers
#define IO_LCDCONT 0xFF40
#define IO_LCDSTAT 0xFF41

#define IO_SCROLLY 0xFF42
#define IO_SCROLLX 0xFF43

#define IO_CURLINE 0xFF44 // LY
#define IO_CMPLINE 0xFF45 // LYC

#define IO_BGRDPAL 0xFF47
#define IO_OBJ0PAL 0xFF48
#define IO_OBJ1PAL 0xFF49

#define IO_WNDPOSY 0xFF4A
#define IO_WNDPOSX 0xFF4B

#define IO_DMACONT 0xFF46
#define IO_IENABLE 0xFFFF

// sound registers
#define IO_SNDREG10 0xFF10
#define IO_SNDREG11 0xFF11
#define IO_SNDREG12 0xFF12
#define IO_SNDREG13 0xFF13
#define IO_SNDREG14 0xFF14
#define IO_SNDREG21 0xFF16
#define IO_SNDREG22 0xFF17
#define IO_SNDREG23 0xFF18
#define IO_SNDREG24 0xFF19
#define IO_SNDREG30 0xFF1A
#define IO_SNDREG31 0xFF1B
#define IO_SNDREG32 0xFF1C
#define IO_SNDREG33 0xFF1D
#define IO_SNDREG34 0xFF1E
#define IO_SNDREG41 0xFF20
#define IO_SNDREG42 0xFF21
#define IO_SNDREG43 0xFF22
#define IO_SNDREG44 0xFF23
#define IO_SNDREG50 0xFF24
#define IO_SNDREG51 0xFF25
#define IO_SNDREG52 0xFF26

// LCDCONT
#define OPT_Window_Tile_Map_0     0
#define OPT_Window_Tile_Map_1     1
#define OPT_BGWindow_Tile_Data_0  0
#define OPT_BGWindow_Tile_Data_1  1
#define OPT_BG_Tile_Map_0         0
#define OPT_BG_Tile_Map_1         1
#define OPT_OBJ_Size_8x8                  0
#define OPT_OBJ_Size_8x16                 1


// OBJ
#define OPT_OBJ_Flag_priority (0x01 << 7)
#define OPT_OBJ_Flag_yflip    (0x01 << 6)
#define OPT_OBJ_Flag_xflip    (0x01 << 5)
#define OPT_OBJ_Flag_palette  (0x01 << 4)

#define OPT_LYC_NEQ_LY    0
#define OPT_LYC_EQ_LY     1
#define OPT_MODE_HBLANK   0
#define OPT_MODE_VBLANK   1
#define OPT_MODE_OAM      2
#define OPT_MODE_OAM_VRAM 3

#define MASK_IO_BGRDPAL_Shade_Color_3 ((0x01 << 7) + (0x01 << 6))
#define MASK_IO_BGRDPAL_Shade_Color_2 ((0x01 << 5) + (0x01 << 4))
#define MASK_IO_BGRDPAL_Shade_Color_1 ((0x01 << 3) + (0x01 << 2))
#define MASK_IO_BGRDPAL_Shade_Color_0 ((0x01 << 1) + (0x01 << 0))

#define OPT_Color_White      0
#define OPT_Color_Light_Gray 1
#define OPT_Color_Dark_Gray  2
#define OPT_Color_Black      3

#define MASK_INT_High_to_Low_P10_P13    (0x01 << 4)
#define MASK_INT_End_Serial_IO_Transfer (0x01 << 3)
#define MASK_INT_Timer_Overflow         (0x01 << 2)

#define MASK_IO_SIOCONT_Start_Flag (0x01 << 7)
#define MASK_IO_SIOCONT_IO_Select  (0x01 << 0)

#define MASK_IO_TIMCONT_Start  (0x01 << 2)
#define MASK_IO_TIMCONT_clock ((0x01 << 1) + (0x01 << 0))

#define OPT_Timer_clock_4096   0
#define OPT_Timer_clock_262144 1
#define OPT_Timer_clock_65536  2
#define OPT_Timer_clock_16384  3

// from: https://github.com/Dhole/miniBoy/blob/461697a267648391fe78897ac83daa54df080810/io_regs.h
#define MASK_LCDCONT_LCD_Display_Enable             (0x01 << 7)
#define MASK_LCDCONT_Window_Tile_Map_Display_Select (0x01 << 6)
#define MASK_LCDCONT_Window_Display_Enable          (0x01 << 5)
#define MASK_LCDCONT_BGWindow_Tile_Data_Select      (0x01 << 4)
#define MASK_LCDCONT_BG_Tile_Map_Display_Select     (0x01 << 3)
#define MASK_LCDCONT_OBJ_Size                       (0x01 << 2)
#define MASK_LCDCONT_OBJ_Display_Enable             (0x01 << 1)
#define MASK_LCDCONT_BG_Display_Enable              (0x01 << 0)

#define MASK_INT_LCDSTAT_INT            (0x01 << 1)
#define MASK_INT_VBLANK                 (0x01 << 0)

#define MASK_LCDSTAT_LYC_LY_COINCIDENCE_INTERRUPT (0x01 << 6)
#define MASK_LCDSTAT_MODE_2_OAM_INTERRUPT         (0x01 << 5)
#define MASK_LCDSTAT_MODE_1_VBLANK_INTERRUPT      (0x01 << 4)
#define MASK_LCDSTAT_MODE_0_HBLANK_INTERRUPT      (0x01 << 3)
#define MASK_LCDSTAT_COINCIDENCE_FLAG             (0x01 << 2)
#define MASK_LCDSTAT_MODE_FLAG                   ((0x01 << 1) + (0x01 << 0))

/* Interrupt masks */
#define VBLANK_INTR	0x01
#define LCDC_INTR	0x02
#define TIMER_INTR	0x04
#define SERIAL_INTR	0x08
#define CONTROL_INTR	0x10
#define ANY_INTR	0x1F

/* Interrupt jump addresses */
#define VBLANK_INTR_ADDR    0x0040
#define LCDC_INTR_ADDR      0x0048
#define TIMER_INTR_ADDR     0x0050
#define SERIAL_INTR_ADDR    0x0058
#define CONTROL_INTR_ADDR   0x0060

sloppy emu
=======================

A Gameboy Color emulator for the Gameboy Advance. 

Work in progress. Currently debugging emulator opcodes on a computer's CLI. 

# Tests
## Blargg's tests

| cpu instrs test         |  pass/fail |
| ----------------------- | ---------- |
| 01-special              | :+1:       |
| 02-interrupts           | :x:       |
| 03-op sp,hl             | :+1:       |
| 04-op r,imm             | :+1:       |
| 04_op_r_imm.h           | :+1:       |
| 05-op rp                | :+1:       |
| 06-ld r,r               | :+1:       |
| 07-jr,jp,call,ret,rst   | :+1:       |
| 08-misc instrs          | :+1:       |
| 09-op r,r               | :+1:       |
| 10-bit ops              | :+1:       |
| 11-op a,(hl)            | :+1:       |

# deps
https://devkitpro.org/
https://github.com/devkitPro/libgba

# resources
https://www.cl.cam.ac.uk/~pv273/slides/emulation.pdf  
http://marc.rawer.de/Gameboy/Docs/GBCPUman.pdf  
http://www.meditronik.com.pl/doc/plus/um0080.pdf  
https://mgba.io/2015/06/27/cycle-counting-prefetch/  
https://cturt.github.io/cinoop.html  
https://github.com/drhelius/Gearboy  
https://github.com/mattrubin/Gambit  
https://gb-archive.github.io/salvage/decoding_gbz80_opcodes/Decoding%20Gamboy%20Z80%20Opcodes.html  
http://www.devrs.com/gba/files/gbadevfaqs.php  

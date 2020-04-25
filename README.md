sloppy emu
=======================

Multiplatform Gameboy Color emulator

DMG: in progress
CGB: not started


dmg-acid2 test passing: 
![dmg-acid2 test passing image](/screenshots/dmg-acid2.png?raw=true)

Work in progress. Currently debugging emulator opcodes on a computer's CLI. 

# Tests
## Blargg's tests

| cpu instrs test         |  pass/fail |
| ----------------------- | ---------- |
| 01-special              | :+1:       |
| 02-interrupts           | :+1:        |
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

## mooneye-gb tests
### Acceptance Tests
| Test                    | pass/fail  |
| ----------------------- | ---------- |
| add sp e timing         | :x:        |
| boot div dmg0           | :x:        |
| boot div dmgABCmgb      | :x:        |
| boot div S              | :x:        |
| boot div2 S             | :x:        |
| boot hwio dmg0          | :x:        |
| boot hwio dmgABCmgb     | :x:        |
| boot hwio S             | :x:        |
| boot regs dmg0          | :x:        |
| boot regs dmgABC        | :x:        |
| boot regs mgb           | :x:        |
| boot regs sgb           | :x:        |
| boot regs sgb2          | :x:        |
| call timing             | :x:        |
| call timing2            | :x:        |
| call cc_timing          | :x:        |
| call cc_timing2         | :x:        |
| di timing GS            | :x:        |
| div timing              | :x:        |
| ei sequence             | :x:        |
| ei timing               | :x:        |
| halt ime0 ei            | :x:        |
| halt ime0 nointr_timing | :x:        |
| halt ime1 timing        | :x:        |
| halt ime1 timing2 GS    | :x:        |
| if ie registers         | :x:        |
| intr timing             | :x:        |
| jp timing               | :x:        |
| jp cc timing            | :x:        |
| ld hl sp e timing       | :x:        |
| oam dma_restart         | :x:        |
| oam dma start           | :x:        |
| oam dma timing          | :x:        |
| pop timing              | :x:        |
| push timing             | :x:        |
| rapid di ei             | :x:        |
| ret timing              | :x:        |
| ret cc timing           | :x:        |
| reti timing             | :x:        |
| reti intr timing        | :x:        |
| rst timing              | :x:        |

### Timer
| Test                 | pass/fail |
| -------------------- | ---------- |
| div write            | :+1:       |
| rapid toggle         | :x:        |
| tim00 div trigger    | :x:        |
| tim00                | :+1:       |
| tim01 div trigger    | :x:        |
| tim01                | :+1:       |
| tim10 div trigger    | :x:        |
| tim10                | :+1:       |
| tim11 div trigger    | :+1:       |
| tim11                | :+1:       |
| tima reload          | :x:        |
| tima write reloading | :x:        |
| tma write reloading  | :x:        |

### Memory Bank Controllers
#### MBC1

| Test              | pass/fail |
| ----------------- | ---------- |
| bits bank1        | :+1:       |
| bits bank2        | :+1:       |
| bits mode         | :+1:       |
| bits ramg         | :+1:       |
| rom 512kb         | :+1:       |
| rom 1Mb           | :+1:       |
| rom 2Mb           | :+1:       |
| rom 4Mb           | :+1:       |
| rom 8Mb           | :+1:       |
| rom 16Mb          | :+1:       |
| ram 64kb          | :x:       |
| ram 256kb         | :+1:       |
| multicart rom 8Mb | :x:       |

#### MBC2

| Test              | pass/fail |
| ----------------- | ---------- |
| bits ramg         | :x:       |
| bits romb         | :x:       |
| bits unused       | :x:       |
| rom 512kb         | :x:       |
| rom 1Mb           | :x:       |
| rom 2Mb           | :x:       |
| ram               | :x:       |

#### MBC5

| Test              | pass/fail |
| ----------------- | ---------- |
| rom 512kb         | :x:       |
| rom 1Mb           | :x:       |
| rom 2Mb           | :x:       |
| rom 4Mb           | :x:       |
| rom 8Mb           | :x:       |
| rom 16Mb          | :x:       |
| rom 32Mb          | :x:       |
| rom 64Mb          | :x:       |

### Mooneye GB manual tests

| Test            | pass/fail |
| --------------- | ---------- |
| sprite priority | :+1:       |

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

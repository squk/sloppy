wget http://www.neviksti.com/DMG/DMG_ROM.bin
xxd -i DMG_ROM.bin > include/dmg_rom.h
wget https://gbdev.gg8.se/files/roms/bootroms/cgb_bios.bin
xxd -i cgb_bios.bin > include/cgb_bios.h

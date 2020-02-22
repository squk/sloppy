#define BIT_RANGE(x, lsb, msb) (x >> lsb) & ~(~0 << (msb-lsb+1))

// x = the opcode's 1st octal digit (i.e. bits 7-6)
// y = the opcode's 2nd octal digit (i.e. bits 5-3)
// z = the opcode's 3rd octal digit (i.e. bits 2-0)
// p = y rightshifted one position (i.e. bits 5-4)
// q = y modulo 2 (i.e. bit 3)
// implementation of the decode strategy descrubed here:
// https://gb-archive.github.io/salvage/decoding_gbz80_opcodes/Decoding%20Gamboy%20Z80%20Opcodes.html
instr instr_decode(u8 opcode) {
    x = BIT_RANGE(opcode, 6, 7);
    y = BIT_RANGE(opcode, 3, 5);
    z = BIT_RANGE(opcode, 0, 2);
    p = BIT_RANGE(opcode, 4, 5);
    q - y % 3;
    switch (x) {
        case 0:

            break;
    }
}

instr relative_jumps_and_assorted_ops(u8 y) {

}

#ifndef GBC_INSTRUCTION_H
#define GBC_INSTRUCTION_H

struct instruction {
	char *disassembly;
	unsigned char operandLength;
	void *execute;
	//unsigned char ticks;
}
/*} extern const instructions[1];*/

// TODO: convert to hash map?
const struct instruction instructions[1] = {
	{ "NOP", 0, nop }
}

#endif

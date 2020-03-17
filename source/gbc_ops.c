#include <stdio.h>
#include "gbc_ops.h"

#define min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define half_carry(a, b)  (((a & 0xF) + (b & 0xF)) & 0x10) == 0x10

void execute_op(gbc_cpu *cpu, u8 opcode) {
    switch(opcode) {
        case 0x00: // NOP
            cpu->registers.clk.m = 1;
            break;
        case 0x01: // LD BC,d16
            LD_BC_d16(cpu);
            break;
        case 0x02: // LD (BC),A
            LD_mBC_A(cpu);
            break;
        case 0x03: // INC BC
            INC_BC(cpu);
            break;
        case 0x04: // INC B
            INC_r8(cpu, &cpu->registers.b);
            break;
        case 0x05: // DEC B
            DEC_r8(cpu, &cpu->registers.b);
            break;
        case 0x06: // LD B,d8
            LD_r8_u8(cpu, &cpu->registers.b, read_u8(cpu->mmu,cpu->registers.pc++));
            break;
        case 0x07: // RLCA
            RLCA(cpu);
            break;
        case 0x08: // LD (a16),SP
            LD_A_a16(cpu);
            break;
        case 0x09: // ADD HL BC
            ADD_HL_BC(cpu);
            break;
        case 0x0A: // LD A,(BC)
            LD_A_mBC(cpu); // TODO: refactor
            break;
        case 0x0B: // DEC BC
            DEC_BC(cpu);
            break;
        case 0x0C: // INC C
            INC_r8(cpu, &cpu->registers.c);
            break;
        case 0x0D: // DEC C
            DEC_r8(cpu, &cpu->registers.c);
            break;
        case 0x0E: // LD C,d8
            LD_r8_u8(cpu, &cpu->registers.c, read_u8(cpu->mmu,cpu->registers.pc++));
            break;
        case 0x0F: // /RRCA
            RRCA(cpu);
            break;
        case 0x10: // STOP 0
            printf("unimplemented STOP 0");
            break;
        case 0x11: // LD DE,d16
            LD_DE_d16(cpu);
            break;
        case 0x12: // LD (DE),A
            LD_mDE_A(cpu);
            break;
        case 0x13: // INC DE
            INC_DE(cpu);
            break;
        case 0x14: // INC D
            INC_r8(cpu, &cpu->registers.d);
            break;
        case 0x15: // DEC D
            DEC_r8(cpu, &cpu->registers.d);
            break;
        case 0x16: // LD D,d8
            LD_r8_u8(cpu, &cpu->registers.e, read_u8(cpu->mmu,cpu->registers.pc++));
            break;
        case 0x17: // RLA
            RLA(cpu);
            break;
        case 0x18: // JR r8
            JR_r8(cpu);
            break;
        case 0x19: // ADD HL DE
            ADD_HL_DE(cpu);
            break;
        case 0x1A: // LD A,(DE)
            LD_A_mDE(cpu);
            break;
        case 0x1B: // DEC DE
            DEC_DE(cpu);
            break;
        case 0x1C: // INC E
            INC_r8(cpu, &cpu->registers.e);
            break;
        case 0x1D: // DEC E
            DEC_r8(cpu, &cpu->registers.e);
            break;
        case 0x1E: // LD E,d8
            LD_r8_u8(cpu, &cpu->registers.e, read_u8(cpu->mmu,cpu->registers.pc++));
            break;
        case 0x1F: // RRA
            RRA(cpu);
            break;
        case 0x20: // JR NZ,r8
            JR_NZ_r8(cpu);
            break;
        case 0x21: // LD HL,d16
            LD_HL_d16(cpu);
            break;
        case 0x22: // LD (HL+),A
            LD_mHLI_A(cpu);
            break;
        case 0x23: // INC HL
            INC_HL(cpu);
            break;
        case 0x24: // INC H
            INC_r8(cpu, &cpu->registers.b);
            break;
        case 0x25: // DEC H
            DEC_r8(cpu, &cpu->registers.b);
            break;
        case 0x26: // LD H,d8
            LD_r8_u8(cpu, &cpu->registers.h, read_u8(cpu->mmu,cpu->registers.pc++));
            break;
        case 0x27: // DAA
            DAA(cpu);
            break;
        case 0x28: // JR Z,r8
            JR_Z_r8(cpu);
            break;
        case 0x29: // ADD HL,HL
            ADD_HL_HL(cpu);
            break;
        case 0x2A: // LD A,(HL+)
            LD_A_mHLI(cpu);
            break;
        case 0x2B: // DEC HL
            DEC_HL(cpu);
            break;
        case 0x2C: // INC L
            INC_r8(cpu, &cpu->registers.l);
            break;
        case 0x2D: // DEC L
            DEC_r8(cpu, &cpu->registers.l);
            break;
        case 0x2E: // LD L,d8
            LD_r8_u8(cpu, &cpu->registers.l, read_u8(cpu->mmu,cpu->registers.pc++));
            break;
        case 0x2F: // CPL
            CPL(cpu);
            break;
        case 0x30: // JR NC,r8
            JR_NC_r8(cpu);
            break;
        case 0x31: // LD SP,d16
            LD_SP_d16(cpu);
            break;
        case 0x32: // LD (HL-),A
            LD_mHLD_A(cpu);
            break;
        case 0x33: // INC SP
            INC_SP(cpu);
            break;
        case 0x34: // INC (HL)
            INC_mHL(cpu);
            break;
        case 0x35: // DEC (HL)
            DEC_mHL(cpu);
            break;
        case 0x36: // LD (HL),d8
            LD_mHL_u8(cpu, read_u8(cpu->mmu, cpu->registers.pc++));
            break;
        case 0x37: // SCF
            set_flag_c(cpu, 1);
            cpu->registers.clk.m = 1;
            break;
        case 0x38: // JR C,r8
            JR_C_r8(cpu);
            break;
        case 0x39: // ADD HL SP
            ADD_HL_SP(cpu);
            break;
        case 0x3A: // LD A,(HL-)
            LD_A_mHLD(cpu);
            break;
        case 0x3B: // DEC SP
            DEC_SP(cpu);
            break;
        case 0x3C: // INC A
            INC_r8(cpu, &cpu->registers.a);
            break;
        case 0x3D: // DEC A
            DEC_r8(cpu, &cpu->registers.a);
            break;
        case 0x3E: // LD A,d8
            LD_r8_u8(cpu, &cpu->registers.a, read_u8(cpu->mmu,cpu->registers.pc++));
            break;
        case 0x3F: // CCF
            CCF(cpu);
            break;
        case 0x40: // LD B,B
            LD_r8_r8(cpu, &cpu->registers.b, &cpu->registers.b);
            break;
        case 0x41: // LD B,C
            LD_r8_r8(cpu, &cpu->registers.b, &cpu->registers.c);
            break;
        case 0x42: // LD B,D
            LD_r8_r8(cpu, &cpu->registers.b, &cpu->registers.d);
            break;
        case 0x43: // LD B,E
            LD_r8_r8(cpu, &cpu->registers.b, &cpu->registers.e);
            break;
        case 0x44: // LD B,H
            LD_r8_r8(cpu, &cpu->registers.b, &cpu->registers.h);
            break;
        case 0x45: // LD B,L
            LD_r8_r8(cpu, &cpu->registers.b, &cpu->registers.l);
            break;
        case 0x46: // LD B,(HL)
            LD_r8_mHL(cpu, &cpu->registers.b);
            break;
        case 0x47: // LD B,A
            LD_r8_r8(cpu, &cpu->registers.b, &cpu->registers.a);
            break;
        case 0x48: // LD C,B
            LD_r8_r8(cpu, &cpu->registers.c, &cpu->registers.b);
            break;
        case 0x49: // LD C,C
            LD_r8_r8(cpu, &cpu->registers.c, &cpu->registers.c);
            break;
        case 0x4A: // LD C,D
            LD_r8_r8(cpu, &cpu->registers.c, &cpu->registers.d);
            break;
        case 0x4B: // LD C,E
            LD_r8_r8(cpu, &cpu->registers.c, &cpu->registers.e);
            break;
        case 0x4C: // LD C,H
            LD_r8_r8(cpu, &cpu->registers.c, &cpu->registers.h);
            break;
        case 0x4D: // LD C,L
            LD_r8_r8(cpu, &cpu->registers.c, &cpu->registers.l);
            break;
        case 0x4E: // LD C,(HL)
            LD_r8_mHL(cpu, &cpu->registers.b);
            break;
        case 0x4F: //LD C,A
            LD_r8_r8(cpu, &cpu->registers.c, &cpu->registers.a);
            break;
        case 0x50: // LD D,B
            LD_r8_r8(cpu, &cpu->registers.d, &cpu->registers.b);
            break;
        case 0x51: // LD D,C
            LD_r8_r8(cpu, &cpu->registers.d, &cpu->registers.c);
            break;
        case 0x52: // LD D,D
            LD_r8_r8(cpu, &cpu->registers.d, &cpu->registers.d);
            break;
        case 0x53: // LD D,E
            LD_r8_r8(cpu, &cpu->registers.d, &cpu->registers.e);
            break;
        case 0x54: // LD D,H
            LD_r8_r8(cpu, &cpu->registers.d, &cpu->registers.h);
            break;
        case 0x55: // LD D,L
            LD_r8_r8(cpu, &cpu->registers.d, &cpu->registers.l);
            break;
        case 0x56: // LD D,(HL)
            LD_r8_mHL(cpu, &cpu->registers.d);
            break;
        case 0x57: // LD D,A
            LD_r8_r8(cpu, &cpu->registers.d, &cpu->registers.a);
            break;
        case 0x58: // LD E,B
            LD_r8_r8(cpu, &cpu->registers.e, &cpu->registers.b);
            break;
        case 0x59: // LD E,C
            LD_r8_r8(cpu, &cpu->registers.e, &cpu->registers.c);
            break;
        case 0x5A: // LD E,D
            LD_r8_r8(cpu, &cpu->registers.e, &cpu->registers.d);
            break;
        case 0x5B: // LD E,E
            LD_r8_r8(cpu, &cpu->registers.e, &cpu->registers.e);
            break;
        case 0x5C: // LD E,H
            LD_r8_r8(cpu, &cpu->registers.e, &cpu->registers.h);
            break;
        case 0x5D: // LD E,L
            LD_r8_r8(cpu, &cpu->registers.e, &cpu->registers.l);
            break;
        case 0x5E: // LD E,(HL)
            LD_r8_mHL(cpu, &cpu->registers.e);
            break;
        case 0x5F: // LD E,A
            LD_r8_r8(cpu, &cpu->registers.e, &cpu->registers.a);
            break;
        case 0x60: // LD H,B
            LD_r8_r8(cpu, &cpu->registers.h, &cpu->registers.b);
            break;
        case 0x61: // LD H,C
            LD_r8_r8(cpu, &cpu->registers.h, &cpu->registers.c);
            break;
        case 0x62: // LD H,D
            LD_r8_r8(cpu, &cpu->registers.h, &cpu->registers.d);
            break;
        case 0x63: // LD H,E
            LD_r8_r8(cpu, &cpu->registers.h, &cpu->registers.e);
            break;
        case 0x64: // LD H,H
            LD_r8_r8(cpu, &cpu->registers.h, &cpu->registers.h);
            break;
        case 0x65: // LD H,L
            LD_r8_r8(cpu, &cpu->registers.h, &cpu->registers.l);
            break;
        case 0x66: // LD H, (HL)
            LD_r8_mHL(cpu, &cpu->registers.h);
            break;
        case 0x67: // LD H,A
            LD_r8_r8(cpu, &cpu->registers.h, &cpu->registers.a);
            break;
        case 0x68: // LD L,B
            LD_r8_r8(cpu, &cpu->registers.l, &cpu->registers.b);
            break;
        case 0x69: // LD L,C
            LD_r8_r8(cpu, &cpu->registers.l, &cpu->registers.c);
            break;
        case 0x6A: // LD L,D
            LD_r8_r8(cpu, &cpu->registers.l, &cpu->registers.d);
            break;
        case 0x6B: // LD L,E
            LD_r8_r8(cpu, &cpu->registers.l, &cpu->registers.e);
            break;
        case 0x6C: // LD L,H
            LD_r8_r8(cpu, &cpu->registers.l, &cpu->registers.h);
            break;
        case 0x6D: // LD L,L
            LD_r8_r8(cpu, &cpu->registers.l, &cpu->registers.l);
            break;
        case 0x6E: // LD L,(HL)
            LD_r8_mHL(cpu, &cpu->registers.l);
            break;
        case 0x6F: // LD L,A
            LD_r8_r8(cpu, &cpu->registers.l, &cpu->registers.a);
            break;
        case 0x70: // LD (HL),B
            LD_mHL_u8(cpu, cpu->registers.b);
            break;
        case 0x71: // LD (HL),C
            LD_mHL_u8(cpu, cpu->registers.c);
            break;
        case 0x72: // LD (HL),D
            LD_mHL_u8(cpu, cpu->registers.d);
            break;
        case 0x73: // LD (HL),E
            LD_mHL_u8(cpu, cpu->registers.e);
            break;
        case 0x74: // LD (HL),H
            LD_mHL_u8(cpu, cpu->registers.h);
            break;
        case 0x75: // LD (HL),L
            LD_mHL_u8(cpu, cpu->registers.l);
            break;
        case 0x76: // HALT
            HALT(cpu);
            break;
        case 0x77: // LD (HL),A
            LD_mHL_u8(cpu, cpu->registers.a);
            break;
        case 0x78: // LD A,B
            LD_r8_r8(cpu, &cpu->registers.a, &cpu->registers.b);
            break;
        case 0x79: // LD A,C
            LD_r8_r8(cpu, &cpu->registers.a, &cpu->registers.c);
            break;
        case 0x7A: // LD A,D
            LD_r8_r8(cpu, &cpu->registers.a, &cpu->registers.d);
            break;
        case 0x7B: // LD A,E
            LD_r8_r8(cpu, &cpu->registers.a, &cpu->registers.e);
            break;
        case 0x7C: // LD A,H
            LD_r8_r8(cpu, &cpu->registers.a, &cpu->registers.h);
            break;
        case 0x7D: // LD A,L
            LD_r8_r8(cpu, &cpu->registers.a, &cpu->registers.l);
            break;
        case 0x7E: // LD A,(HL)
            LD_r8_mHL(cpu, &cpu->registers.a);
            break;
        case 0x7F: // LD A,A
            LD_r8_r8(cpu, &cpu->registers.a, &cpu->registers.a);
            break;
        case 0x80: // ADD A,B
            ADD_u8(cpu, cpu->registers.b);
            break;
        case 0x81: // ADD A,C
            ADD_u8(cpu, cpu->registers.c);
            break;
        case 0x82: // ADD A,D
            ADD_u8(cpu, cpu->registers.d);
            break;
        case 0x83: // ADD A,E
            ADD_u8(cpu, cpu->registers.e);
            break;
        case 0x84: // ADD A,H
            ADD_u8(cpu, cpu->registers.h);
            break;
        case 0x85: // ADD A,L
            ADD_u8(cpu, cpu->registers.l);
            break;
        case 0x86: // ADD A,(HL)
            ADD_u8(cpu, read_u8(cpu->mmu, get_hl(cpu)));
            break;
        case 0x87: // ADD A,A
            ADD_u8(cpu, cpu->registers.a);
            break;
        case 0x88: // ADC A,B
            ADC_A_u8(cpu, cpu->registers.b);
            break;
        case 0x89: // ADC A,C
            ADC_A_u8(cpu, cpu->registers.c);
            break;
        case 0x8A: // ADC A,D
            ADC_A_u8(cpu, cpu->registers.d);
            break;
        case 0x8B: // ADC A,E
            ADC_A_u8(cpu, cpu->registers.e);
            break;
        case 0x8C: // ADC A,H
            ADC_A_u8(cpu, cpu->registers.h);
            break;
        case 0x8D: // ADC A,L
            ADC_A_u8(cpu, cpu->registers.l);
            break;
        case 0x8E: // ADC A,(HL)
            ADC_A_u8(cpu, read_u8(cpu->mmu, get_hl(cpu)));
            break;
        case 0x8F: // ADC A,A   optimized
            cpu->registers.clk.m = 1;
            break;
        case 0x90: // SUB B
            SUB_u8(cpu, cpu->registers.b);
            break;
        case 0x91: // SUB C
            SUB_u8(cpu, cpu->registers.c);
            break;
        case 0x92: // SUB D
            SUB_u8(cpu, cpu->registers.d);
            break;
        case 0x93: // SUB E
            SUB_u8(cpu, cpu->registers.e);
            break;
        case 0x94: // SUB H
            SUB_u8(cpu, cpu->registers.h);
            break;
        case 0x95: // SUB L
            SUB_u8(cpu, cpu->registers.l);
            break;
        case 0x96: // SUB (HL)
            SUB_u8(cpu, read_u8(cpu->mmu, get_hl(cpu)));
            break;
        case 0x97: // SUB A
            SUB_u8(cpu, cpu->registers.a);
            break;
        case 0x98: // SBC A,B
            SBC_A_u8(cpu, cpu->registers.b);
            break;
        case 0x99: // SBC A,C
            SBC_A_u8(cpu, cpu->registers.c);
            break;
        case 0x9A: // SBC A,D
            SBC_A_u8(cpu, cpu->registers.d);
            break;
        case 0x9B: // SBC A,E
            SBC_A_u8(cpu, cpu->registers.e);
            break;
        case 0x9C: // SBC A,H
            SBC_A_u8(cpu, cpu->registers.h);
            break;
        case 0x9D: // SBC A,L
            SBC_A_u8(cpu, cpu->registers.l);
            break;
        case 0x9E: // SBC A,(HL)
            SBC_A_u8(cpu, read_u8(cpu->mmu, get_hl(cpu)));
            break;
        case 0x9F: // SBC A,A  slightly optimized
            cpu->registers.a = flag_c(cpu) ? 0xFF : 0x00;
            set_flag_z(cpu, !flag_c(cpu));
            set_flag_n(cpu, 1);
            set_flag_h(cpu, flag_c(cpu));
            cpu->registers.clk.m = 1;
            break;
        case 0xA0: // AND B
            AND_u8(cpu, cpu->registers.b);
            break;
        case 0xA1: // AND C
            AND_u8(cpu, cpu->registers.c);
            break;
        case 0xA2: // AND D
            AND_u8(cpu, cpu->registers.d);
            break;
        case 0xA3: // AND E
            AND_u8(cpu, cpu->registers.e);
            break;
        case 0xA4: // AND H
            AND_u8(cpu, cpu->registers.h);
            break;
        case 0xA5: // AND L
            AND_u8(cpu, cpu->registers.l);
            break;
        case 0xA6: // AND (HL)
            AND_u8(cpu, read_u8(cpu->mmu, get_hl(cpu)));
            break;
        case 0xA7: // AND A
            AND_u8(cpu, cpu->registers.a);
            break;
        case 0xA8: // XOR B
            XOR_u8(cpu, cpu->registers.b);
            break;
        case 0xA9: // XOR C
            XOR_u8(cpu, cpu->registers.c);
            break;
        case 0xAA: // XOR D
            XOR_u8(cpu, cpu->registers.d);
            break;
        case 0xAB: // XOR E
            XOR_u8(cpu, cpu->registers.e);
            break;
        case 0xAC: // XOR H
            XOR_u8(cpu, cpu->registers.h);
            break;
        case 0xAD: // XOR L
            XOR_u8(cpu, cpu->registers.l);
            break;
        case 0xAE: // XOR (HL)
            XOR_u8(cpu, read_u8(cpu->mmu, get_hl(cpu)));
            break;
        case 0xAF: // XOR A   slightly optimized
            cpu->registers.a = 0;
            set_flag_z(cpu, 0);
            set_flag_n(cpu, 0);
            set_flag_h(cpu, 0);
            set_flag_c(cpu, 0);
            cpu->registers.clk.m = 1;
            break;
        case 0xB0: // OR B
            OR_u8(cpu, cpu->registers.b);
            break;
        case 0xB1: // OR C
            OR_u8(cpu, cpu->registers.c);
            break;
        case 0xB2: // OR D
            OR_u8(cpu, cpu->registers.d);
            break;
        case 0xB3: // OR E
            OR_u8(cpu, cpu->registers.e);
            break;
        case 0xB4: // OR H
            OR_u8(cpu, cpu->registers.h);
            break;
        case 0xB5: // OR L
            OR_u8(cpu, cpu->registers.l);
            break;
        case 0xB6: // OR (HL)
            OR_u8(cpu, read_u8(cpu->mmu, get_hl(cpu)));
            break;
        case 0xB7: // OR A
            OR_u8(cpu, cpu->registers.a);
            break;
        case 0xB8: // CP B
            CP_u8(cpu, cpu->registers.b);
            break;
        case 0xB9: // CP C
            CP_u8(cpu, cpu->registers.c);
            break;
        case 0xBA: // CP D
            CP_u8(cpu, cpu->registers.d);
            break;
        case 0xBB: // CP E
            CP_u8(cpu, cpu->registers.e);
            break;
        case 0xBC: // CP H
            CP_u8(cpu, cpu->registers.h);
            break;
        case 0xBD: // CP L
            CP_u8(cpu, cpu->registers.l);
            break;
        case 0xBE: // CP (HL)
            CP_u8(cpu, read_u8(cpu->mmu, get_hl(cpu)));
            break;
        case 0xBF: // CP A   slightly optimized
            cpu->registers.f = FLAG_Z;
            cpu->registers.clk.m=1;
            break;
        case 0xC0: // RET NZ
            RET_NZ(cpu);
            break;
        case 0xC1: // POP BC
            POP_BC(cpu);
            break;
        case 0xC2: // JP NZ,a16
            JP_NZ_a16(cpu);
            break;
        case 0xC3: // JP a16
            JP_a16(cpu);
            break;
        case 0xC4: // CALL NZ,a16
            CALL_NZ_a16(cpu);
            break;
        case 0xC5: // PUSH BC
            PUSH_BC(cpu);
            break;
        case 0xC6: // ADD A,d8
            ADD_u8(cpu, read_u8(cpu->mmu, cpu->registers.pc++));
            break;
        case 0xC7: // RST 00H
            RST_u8(cpu, 0x00);
            break;
        case 0xC8: // RET Z
            RET_Z(cpu);
            break;
        case 0xC9: //RET
            RET(cpu);
            break;
        case 0xCA: // JP Z,a16
            JP_Z_a16(cpu);
            break;
        case 0xCB: // PREFIX CB
            MAPcb(cpu);
            break;
        case 0xCC: // CALL Z,a16
            CALL_Z_a16(cpu);
            break;
        case 0xCD: // CALL a16
            CALL_a16(cpu);
            break;
        case 0xCE: // ADC A,d8
            ADC_A_u8(cpu, read_u8(cpu->mmu, cpu->registers.pc++));
            break;
        case 0xCF: // RST 08H
            RST_u8(cpu, 0x08);
            break;
        case 0xD0: // RET NC
            RET_NC(cpu);
            break;
        case 0xD1: // POP DE
            POP_DE(cpu);
            break;
        case 0xD2: // JP NC,a16
            JP_NC_a16(cpu); // TODO: refector all JP instrs to use a single JP_a16 func
            break;
        case 0xD3: // BLANK
            printf("non-existant GB opcode: DB");
            break;
        case 0xD4: // CALL NC,a16
            CALL_NC_a16(cpu);
            break;
        case 0xD5: // PUSH DE
            PUSH_DE(cpu);
            break;
        case 0xD6: // SUB d8
            SUB_u8(cpu, read_u8(cpu, cpu->registers.pc++));
            break;
        case 0xD7: // RST 10H
            RST_u8(cpu, 0x10);
            break;
        case 0xD8: // RET C
            RET_C(cpu);
            break;
        case 0xD9: // RET I
            RET_I(cpu);
            break;
        case 0xDA: // JP C,a16
            JP_C_a16(cpu);
            break;
        case 0xDB: // BLANK
            printf("non-existant GB opcode: DB");
            break;
        case 0xDC: // CALL C,a16
            CALL_C_a16(cpu);
            break;
        case 0xDD: // BLANK
            printf("non-existant GB opcode: DD");
            break;
        case 0xDE: // SBC A,d8
            SBC_A_u8(cpu, read_u8(cpu, cpu->registers.pc++));
            break;
        case 0xDF: // RST 18H
            RST_u8(cpu, 0x18);
            break;
        case 0xE0: // LDH (a8),A
            LDH_a8_A(cpu);
            break;
        case 0xE1: // POP HL
            POP_HL(cpu);
            break;
        case 0xE2: // LD (C),A
            LD_mC_A(cpu);
            break;
        case 0xE3: // BLANK
        case 0xE4:
            printf("non-existant GB opcode: %d", opcode);
            break;
        case 0xE5: // PUSH HL
            PUSH_HL(cpu);
            break;
        case 0xE6: // AND d8
            AND_u8(cpu, read_u8(cpu->mmu,cpu->registers.pc++));
            break;
        case 0xE7: // RST 20H
            RST_u8(cpu, 0x20);
            break;
        case 0xE8: // ADD SP,r8
            ADD_SP_d8(cpu);
            break;
        case 0xE9: // JP (HL)
            JP_mHL(cpu);
            break;
        case 0xEA: // LD (a16),A
            LD_a16_A(cpu);
            break;
        case 0xEB: // BLANK
        case 0xEC:
        case 0xED:
            printf("non-existant GB opcode: %d", opcode);
            break;
        case 0xEE: // XOR d8
            XOR_u8(cpu, read_u8(cpu->mmu,cpu->registers.pc++));
            break;
        case 0xEF: // RST 28H
            RST_u8(cpu, 0x28);
            break;
        case 0xF0: // LDH A,(a8)
            LDH_a8_A(cpu);
            break;
        case 0xF1: // POP AF
            POP_AF(cpu);
            break;
        case 0xF2: // LD A,(C)
            LD_A_mC(cpu);
            break;
        case 0xF3: // DI
            DI(cpu);
            break;
        case 0xF4: //BLANK
            printf("non-existant GB opcode: F4");
            break;
        case 0xF5: // PUSH AF
            PUSH_AF(cpu);
            break;
        case 0xF6: // OR d8
            OR_u8(cpu, read_u8(cpu->mmu, cpu->registers.pc++));
            break;
        case 0xF7: // RST 30H
            RST_u8(cpu, 0x30);
            break;
        case 0xF8: // LD HL,SP+r8
            LD_HL_SP_r8(cpu);
            break;
        case 0xF9: // LD SP,HL
            LD_SP_HL(cpu);
            break;
        case 0xFA: // LD A,(a16)
            LD_A_a16(cpu);
            break;
        case 0xFB: // EI
            EI(cpu);
            break;
        case 0xFC: // BLANK
        case 0xFD:
            printf("non-existant GB opcode: FD");
            break;
        case 0xFE: // CP d8
            CP_u8(cpu, read_u8(cpu->mmu, cpu->registers.pc++));
            break;
        case 0xFF: // RST 38H
            RST_u8(cpu, 0x38);
            break;
    }
}

void LD_r8_r8(gbc_cpu *cpu, u8 *r1, u8 *r2) {
    *r1 = *r2;
    cpu->registers.clk.m = 1;
}
void LD_r8_u8(gbc_cpu *cpu, u8 *r1, u8 v) {
    *r1 = v;
    cpu->registers.clk.m = 1;
}

void LD_r8_mHL(gbc_cpu *cpu, u8 *r) {
    cpu->registers.a = read_u8(cpu->mmu, get_hl(cpu));
    cpu->registers.clk.m = 2;
}

void LD_mHL_u8(gbc_cpu *cpu, u8 v) {
    write_u8(cpu->mmu, get_hl(cpu), v);
    cpu->registers.clk.m = 2;
}

void LD_mBC_A(gbc_cpu *cpu) {
    write_u8(cpu->mmu, get_bc(cpu), cpu->registers.a);
    cpu->registers.clk.m = 2;
}
void LD_mDE_A(gbc_cpu *cpu) {
    write_u8(cpu->mmu, get_de(cpu), cpu->registers.a);
    cpu->registers.clk.m = 2;
}
void LD_mHLI_A(gbc_cpu *cpu) {
    write_u8(cpu->mmu, get_hl(cpu), cpu->registers.a);
    cpu->registers.l=(cpu->registers.l+1)&255;
    if(!cpu->registers.l) cpu->registers.h=(cpu->registers.h+1)&255;
    cpu->registers.clk.m = 2;
}
void LD_mC_A(gbc_cpu *cpu) {
    write_u8(cpu->mmu,0xFF00+cpu->registers.c,cpu->registers.a);
    cpu->registers.clk.m = 2;
}

void LD_mHLD_A(gbc_cpu *cpu) {
    write_u8(cpu->mmu, get_hl(cpu), cpu->registers.a);
    cpu->registers.l=(cpu->registers.l-1)&255;
    if(cpu->registers.l==255) cpu->registers.h=(cpu->registers.h-1)&255;
    cpu->registers.clk.m = 2;
}

void LD_HL_d8(gbc_cpu *cpu) {
    write_u8(cpu->mmu, get_hl(cpu), read_u8(cpu->mmu, cpu->registers.pc));
    cpu->registers.pc++;
    cpu->registers.clk.m = 3;
}


/*void LD_d16_A(gbc_cpu *cpu) {
  write_u8(cpu->mmu, read_u16(cpu->mmu, cpu->registers.pc), cpu->registers.a);
  cpu->registers.pc += 2;
 cpu->registers.clk.m = 4;
 }*/
/*void LD_A_d16(gbc_cpu *cpu) {
 cpu->registers.a = read_u8(cpu->mmu, read_u16(cpu->mmu, cpu->registers.pc));
 cpu->registers.pc += 2;
 cpu->registers.clk.m = 4;
 }*/

void LD_A_mBC(gbc_cpu *cpu) {
    cpu->registers.a = read_u8(cpu->mmu,(cpu->registers.b<<8)+cpu->registers.c);
    cpu->registers.clk.m = 2;
}
void LD_A_mDE(gbc_cpu *cpu) {
    cpu->registers.a = read_u8(cpu->mmu,(cpu->registers.d<<8)+cpu->registers.e);
    cpu->registers.clk.m = 2;
}

void LD_A_a16(gbc_cpu *cpu) {
    u16 addr = read_u8(cpu->mmu, cpu->registers.pc++);
    addr |= read_u8(cpu->mmu, cpu->registers.pc++) << 8;
    cpu->registers.a = read_u8(cpu->mmu, addr);
    cpu->registers.clk.m = 4;
}

void LD_a16_A(gbc_cpu *cpu) {
    u16 addr = read_u8(cpu->mmu, cpu->registers.pc++);
    addr |= read_u8(cpu->mmu, cpu->registers.pc++) << 8;
    write_u8(cpu->mmu, addr, cpu->registers.a);
}
void LD_a16_SP(gbc_cpu *cpu) {
    u16 temp = read_u8(cpu->mmu, cpu->registers.pc++);
    temp |= read_u8(cpu->mmu, cpu->registers.pc++) << 8;
    write_u8(cpu->mmu, temp++, cpu->registers.sp & 0xFF);
    write_u8(cpu->mmu, temp, cpu->registers.sp >> 8);
    /*write_u8(cpu->mmu,read_u16(cpu->mmu,cpu->registers.pc), cpu->registers.sp);
    */
    cpu->registers.clk.m = 5;
}

void LD_BC_d16(gbc_cpu *cpu) {
    cpu->registers.c = read_u8(cpu->mmu, cpu->registers.pc++);
    cpu->registers.b = read_u8(cpu->mmu, cpu->registers.pc++);
    cpu->registers.clk.m = 3;
}
void LD_DE_d16(gbc_cpu *cpu) {
    cpu->registers.e = read_u8(cpu->mmu, cpu->registers.pc++);
    cpu->registers.d = read_u8(cpu->mmu, cpu->registers.pc++);
    cpu->registers.clk.m = 3;
}
void LD_HL_d16(gbc_cpu *cpu) {
    cpu->registers.l = read_u8(cpu->mmu, cpu->registers.pc++);
    cpu->registers.h = read_u8(cpu->mmu, cpu->registers.pc++);
    cpu->registers.clk.m = 3;
}

void LD_SP_HL(gbc_cpu *cpu) {
    cpu->registers.sp = get_hl(cpu);
    cpu->registers.clk.m = 2;
}
void LD_SP_d16(gbc_cpu *cpu) {
    cpu->registers.sp = read_u16(cpu->mmu, cpu->registers.pc);
    cpu->registers.pc += 2;
    cpu->registers.clk.m = 3;
}

void LD_A_mHLI(gbc_cpu *cpu) {
    cpu->registers.a = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    cpu->registers.l=(cpu->registers.l+1)&255;
    if(!cpu->registers.l) cpu->registers.h=(cpu->registers.h+1)&255;
    cpu->registers.clk.m = 2;
}

void LD_A_mHLD(gbc_cpu *cpu) {
    cpu->registers.a = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    cpu->registers.l=(cpu->registers.l-1)&255;
    if(cpu->registers.l==255) cpu->registers.h=(cpu->registers.h-1)&255;
    cpu->registers.clk.m = 2;
}

void LDH_a8_A(gbc_cpu *cpu) {
    write_u8(cpu->mmu, 0xFF00 | read_u8(cpu->mmu, cpu->registers.pc++), cpu->registers.a);
    cpu->registers.clk.m = 3;
}
void LDH_A_a8(gbc_cpu *cpu) {
    cpu->registers.a = read_u8(cpu->mmu, 0xFF00 | read_u8(cpu->mmu, cpu->registers.pc++));
    cpu->registers.clk.m = 3;
}
void LD_HL_SP_r8(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,cpu->registers.pc);
    if(i>127) i=-((~i+1)&255);
    cpu->registers.pc++;
    i+=cpu->registers.sp;
    cpu->registers.h=(i>>8)&255;
    cpu->registers.l = i&255;
    cpu->registers.clk.m = 3;
}
void LD_A_mC(gbc_cpu *cpu) {
    cpu->registers.a = read_u8(cpu->mmu,0xFF00+cpu->registers.c);
    cpu->registers.clk.m = 2;
}

void SWAP_A(gbc_cpu *cpu) {
    u8 tr = cpu->registers.a;
    cpu->registers.a=((tr&0xF)<<4)|((tr&0xF0)>>4);
    cpu->registers.f = cpu->registers.a?0:FLAG_Z;
    cpu->registers.clk.m = 1;
}
void SWAP_B(gbc_cpu *cpu) {
    u8 tr = cpu->registers.b;
    cpu->registers.b=((tr&0xF)<<4)|((tr&0xF0)>>4);
    cpu->registers.f = cpu->registers.b?0:FLAG_Z;
    cpu->registers.clk.m = 1;
}
void SWAP_C(gbc_cpu *cpu) {
    u8 tr = cpu->registers.c;
    cpu->registers.c=((tr&0xF)<<4)|((tr&0xF0)>>4);
    cpu->registers.f = cpu->registers.c?0:FLAG_Z;
    cpu->registers.clk.m = 1;
}
void SWAP_D(gbc_cpu *cpu) {
    u8 tr = cpu->registers.d;
    cpu->registers.d=((tr&0xF)<<4)|((tr&0xF0)>>4);
    cpu->registers.f = cpu->registers.d?0:FLAG_Z;
    cpu->registers.clk.m = 1;
}
void SWAP_E(gbc_cpu *cpu) {
    u8 tr = cpu->registers.e;
    cpu->registers.e=((tr&0xF)<<4)|((tr&0xF0)>>4);
    cpu->registers.f = cpu->registers.e?0:FLAG_Z;
    cpu->registers.clk.m = 1;
}
void SWAP_H(gbc_cpu *cpu) {
    u8 tr = cpu->registers.h;
    cpu->registers.h=((tr&0xF)<<4)|((tr&0xF0)>>4);
    cpu->registers.f = cpu->registers.h?0:FLAG_Z;
    cpu->registers.clk.m = 1;
}
void SWAP_L(gbc_cpu *cpu) {
    u8 tr = cpu->registers.l;
    cpu->registers.l=((tr&0xF)<<4)|((tr&0xF0)>>4);
    cpu->registers.f = cpu->registers.l?0:FLAG_Z;
    cpu->registers.clk.m = 1;
}

void ADD_u8(gbc_cpu *cpu, u8 v) {
    u16 temp = cpu->registers.a + v;
    set_flag_z(cpu, (temp & 0xFF) == 0x00);
    set_flag_n(cpu, 0);
    set_flag_h(cpu, (cpu->registers.a ^ v ^ temp) & 0x10);
    set_flag_c(cpu, temp & 0xFF00);
    cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 1;
}

void ADD_HL_BC(gbc_cpu *cpu) {
    u32 temp = get_hl(cpu) + get_bc(cpu);
    set_flag_n(cpu, 0);
    set_flag_h(cpu, (temp ^ get_hl(cpu) ^ get_bc(cpu)) & 0x1000);
    set_flag_c(cpu, temp & 0xFFFF0000);
    set_hl(cpu, temp & 0x0000FFFF);
    cpu->registers.clk.m = 3;
}
void ADD_HL_DE(gbc_cpu *cpu) {
    u32 temp = get_hl(cpu) + get_de(cpu);
    set_flag_n(cpu, 0);
    set_flag_h(cpu, (temp ^ get_hl(cpu) ^ get_de(cpu)) & 0x1000);
    set_flag_c(cpu, temp & 0xFFFF0000);
    set_hl(cpu, temp & 0x0000FFFF);
    cpu->registers.clk.m = 3;
}
void ADD_HL_HL(gbc_cpu *cpu) {
    u32 temp = get_hl(cpu) + get_hl(cpu);
    set_flag_n(cpu, 0);
    set_flag_h(cpu, temp & 0x1000);
    set_flag_c(cpu, temp & 0xFFFF0000);
    set_hl(cpu, temp & 0x0000FFFF);
}
void ADD_HL_SP(gbc_cpu *cpu) {
    u32 temp = get_hl(cpu) + cpu->registers.sp;
    set_flag_n(cpu, 0);
    set_flag_h(cpu, ((get_hl(cpu) & 0xFFF) + (cpu->registers.sp & 0xFFF)) & 0x1000);
    set_flag_c(cpu, temp & 0x10000);
    set_hl(cpu, (u16)temp);
    cpu->registers.clk.m = 3;
}
void ADD_SP_d8(gbc_cpu *cpu) {
    s8 offset = (s8)read_u8(cpu->mmu, cpu->registers.pc++);
    set_flag_z(cpu, 0);
    set_flag_n(cpu, 0);
    set_flag_h(cpu, (cpu->registers.sp & 0xF) + (offset & 0xF) > 0xF);
    set_flag_c(cpu, (cpu->registers.sp & 0xFF) + (offset & 0xFF) > 0xFF);
    cpu->registers.sp += offset;
    cpu->registers.clk.m = 4;
}
void ADC_A_u8(gbc_cpu *cpu, u8 v) {
    u16 temp = cpu->registers.a + v + flag_c(cpu);
    set_flag_z(cpu, (temp & 0xFF) == 0x00);
    set_flag_n(cpu, 0);
    set_flag_h(cpu, (cpu->registers.a ^ v ^ temp) & 0x10);
    set_flag_c(cpu, temp & 0xFF00);
    cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 1;
}
void SUB_u8(gbc_cpu *cpu, u8 v) {
    u16 temp = cpu->registers.a - v;
    set_flag_z(cpu, (temp & 0xFF) == 0x00);
    set_flag_n(cpu, 1);
    set_flag_h(cpu, (cpu->registers.a ^ v ^ temp) & 0x10);
    set_flag_c(cpu, temp & 0xFF00);
    cpu->registers.a = (temp & 0xFF);
}

void SBC_A_u8(gbc_cpu *cpu, u8 v) {
    u16 temp = cpu->registers.a - v - flag_c(cpu);
    set_flag_z(cpu, (temp & 0xFF) == 0x00);
    set_flag_n(cpu, 1);
    set_flag_h(cpu, (cpu->registers.a ^ v ^ temp) & 0x10);
    set_flag_c(cpu, temp & 0xFF00);
    cpu->registers.a = (temp & 0xFF);
    cpu->registers.clk.m = 1;
}

void AND_u8(gbc_cpu *cpu, u8 v) {
    cpu->registers.a &= v;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
    set_flag_h(cpu, 1);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}

void DAA(gbc_cpu *cpu) {
    u8 i = cpu->registers.a;
    if((cpu->registers.f&FLAG_H)||((cpu->registers.a&15)>9)) cpu->registers.a += 6;
    cpu->registers.f &= 0xEF;
    if((cpu->registers.f&FLAG_H)||(i>0x99)) {
        cpu->registers.a += 0x60;
        cpu->registers.f|=FLAG_C;
    } cpu->registers.clk.m = 1;
}

void XOR_u8(gbc_cpu *cpu, u8 v) {
    cpu->registers.a ^= v;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
    set_flag_h(cpu, 0);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}

void OR_u8(gbc_cpu *cpu, u8 v) {
    cpu->registers.a |= v;
    set_flag_z(cpu, cpu->registers.a == 0x00);
    set_flag_n(cpu, 0);
    set_flag_h(cpu, 0);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 1;
}

void CP_u8(gbc_cpu *cpu, u8 v) {
    u16 temp = cpu->registers.a - v;
    set_flag_z(cpu, (temp & 0xFF) == 0x00);
    set_flag_n(cpu, 1);
    set_flag_h(cpu, (cpu->registers.a ^ v ^ temp) & 0x10);
    set_flag_c(cpu, temp & 0xFF00);
    cpu->registers.clk.m=1;
}

void INC_r8(gbc_cpu *cpu, u8 *r) {
    (*r)++;
    set_flag_z(cpu, *r == 0x00);
    set_flag_n(cpu, 0);
    /*set_flag_h(cpu, half_carry(*r, 1));*/
    set_flag_h(cpu, (*r & 0x0F) == 0x00);

    cpu->registers.clk.m = 1;
}
void INC_mHL(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu, get_hl(cpu))+1;
    i&=255;
    write_u8(cpu->mmu, get_hl(cpu), i);
    cpu->registers.f = (cpu->registers.f & ~FLAG_Z) | ((i & 0xFF) == 0x00) ? FLAG_Z : 0;
    cpu->registers.clk.m = 3;
}

void INC_BC(gbc_cpu *cpu) {
    cpu->registers.c=(cpu->registers.c+1)&255;
    if(!cpu->registers.c) cpu->registers.b=(cpu->registers.b+1)&255;
    cpu->registers.clk.m = 1;
}
void INC_DE(gbc_cpu *cpu) {
    cpu->registers.e=(cpu->registers.e+1)&255;
    if(!cpu->registers.e) cpu->registers.d=(cpu->registers.d+1)&255;
    cpu->registers.clk.m = 1;
}
void INC_HL(gbc_cpu *cpu) {
    cpu->registers.l=(cpu->registers.l+1)&255;
    if(!cpu->registers.l) cpu->registers.h=(cpu->registers.h+1)&255;
    cpu->registers.clk.m = 1;
}
void INC_SP(gbc_cpu *cpu) {
    cpu->registers.sp=(cpu->registers.sp+1)&65535;
    cpu->registers.clk.m = 1;
}

void DEC_r8(gbc_cpu *cpu, u8 *r) {
    (*r)--;
    set_flag_z(cpu, *r == 0x00);
    set_flag_n(cpu, 1);
    set_flag_h(cpu, (*r & 0x0F) == 0x0F);
    cpu->registers.clk.m = 1;
}
void DEC_mHL(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu, get_hl(cpu))-1;
    i&=255;
    write_u8(cpu->mmu, get_hl(cpu), i);
    cpu->registers.f = i?0:FLAG_Z;
    cpu->registers.f |= FLAG_N;
    cpu->registers.clk.m = 3;
}

void DEC_BC(gbc_cpu *cpu) {
    cpu->registers.c=(cpu->registers.c-1)&255;
    if(cpu->registers.c==255) cpu->registers.b=(cpu->registers.b-1)&255;
    cpu->registers.clk.m = 1;
}
void DEC_DE(gbc_cpu *cpu) {
    cpu->registers.e=(cpu->registers.e-1)&255;
    if(cpu->registers.e==255) cpu->registers.d=(cpu->registers.d-1)&255;
    cpu->registers.clk.m = 1;
}
void DEC_HL(gbc_cpu *cpu) {
    cpu->registers.l=(cpu->registers.l-1)&255;
    if(cpu->registers.l==255) cpu->registers.h=(cpu->registers.h-1)&255;
    cpu->registers.clk.m = 1;
}
void DEC_SP(gbc_cpu *cpu) {
    cpu->registers.sp=(cpu->registers.sp-1)&65535;
    cpu->registers.clk.m = 1;
}

void BIT_0_A(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.a&0x01)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_0_B(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.b&0x01)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_0_C(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.c&0x01)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_0_D(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.d&0x01)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_0_E(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.e&0x01)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_0_H(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.h&0x01)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_0_L(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.l&0x01)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_0_M(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l)&0x01)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 3;
}

void RES_0_A(gbc_cpu *cpu) {
    cpu->registers.a &= 0xFE;
    cpu->registers.clk.m = 2;
}
void RES_0_B(gbc_cpu *cpu) {
    cpu->registers.b &= 0xFE;
    cpu->registers.clk.m = 2;
}
void RES_0_C(gbc_cpu *cpu) {
    cpu->registers.c &= 0xFE;
    cpu->registers.clk.m = 2;
}
void RES_0_D(gbc_cpu *cpu) {
    cpu->registers.d &= 0xFE;
    cpu->registers.clk.m = 2;
}
void RES_0_E(gbc_cpu *cpu) {
    cpu->registers.e &= 0xFE;
    cpu->registers.clk.m = 2;
}
void RES_0_H(gbc_cpu *cpu) {
    cpu->registers.h &= 0xFE;
    cpu->registers.clk.m = 2;
}
void RES_0_L(gbc_cpu *cpu) {
    cpu->registers.l &= 0xFE;
    cpu->registers.clk.m = 2;
}
void RES_0_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i &= 0xFE;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void SET_0_B(gbc_cpu *cpu) {
    cpu->registers.b |= 0x01;
    cpu->registers.clk.m = 2;
}
void SET_0_C(gbc_cpu *cpu) {
    cpu->registers.b |= 0x01;
    cpu->registers.clk.m = 2;
}
void SET_0_D(gbc_cpu *cpu) {
    cpu->registers.b |= 0x01;
    cpu->registers.clk.m = 2;
}
void SET_0_E(gbc_cpu *cpu) {
    cpu->registers.b |= 0x01;
    cpu->registers.clk.m = 2;
}
void SET_0_H(gbc_cpu *cpu) {
    cpu->registers.b |= 0x01;
    cpu->registers.clk.m = 2;
}
void SET_0_L(gbc_cpu *cpu) {
    cpu->registers.b |= 0x01;
    cpu->registers.clk.m = 2;
}
void SET_0_A(gbc_cpu *cpu) {
    cpu->registers.b |= 0x01;
    cpu->registers.clk.m = 2;
}
void SET_0_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i |= 0x01;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void BIT_1_B(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.b&0x02)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_1_C(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.c&0x02)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_1_D(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.d&0x02)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_1_E(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.e&0x02)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_1_H(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.h&0x02)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_1_L(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.l&0x02)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_1_A(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.a&0x02)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_1_M(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l)&0x02)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 3;
}

void RES_1_B(gbc_cpu *cpu) {
    cpu->registers.b &= 0xFD;
    cpu->registers.clk.m = 2;
}
void RES_1_C(gbc_cpu *cpu) {
    cpu->registers.c &= 0xFD;
    cpu->registers.clk.m = 2;
}
void RES_1_D(gbc_cpu *cpu) {
    cpu->registers.d &= 0xFD;
    cpu->registers.clk.m = 2;
}
void RES_1_E(gbc_cpu *cpu) {
    cpu->registers.e &= 0xFD;
    cpu->registers.clk.m = 2;
}
void RES_1_H(gbc_cpu *cpu) {
    cpu->registers.h &= 0xFD;
    cpu->registers.clk.m = 2;
}
void RES_1_L(gbc_cpu *cpu) {
    cpu->registers.l &= 0xFD;
    cpu->registers.clk.m = 2;
}
void RES_1_A(gbc_cpu *cpu) {
    cpu->registers.a &= 0xFD;
    cpu->registers.clk.m = 2;
}
void RES_1_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i &= 0xFD;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void SET_1_B(gbc_cpu *cpu) {
    cpu->registers.b |= 0x02;
    cpu->registers.clk.m = 2;
}
void SET_1_C(gbc_cpu *cpu) {
    cpu->registers.b |= 0x02;
    cpu->registers.clk.m = 2;
}
void SET_1_D(gbc_cpu *cpu) {
    cpu->registers.b |= 0x02;
    cpu->registers.clk.m = 2;
}
void SET_1_E(gbc_cpu *cpu) {
    cpu->registers.b |= 0x02;
    cpu->registers.clk.m = 2;
}
void SET_1_H(gbc_cpu *cpu) {
    cpu->registers.b |= 0x02;
    cpu->registers.clk.m = 2;
}
void SET_1_L(gbc_cpu *cpu) {
    cpu->registers.b |= 0x02;
    cpu->registers.clk.m = 2;
}
void SET_1_A(gbc_cpu *cpu) {
    cpu->registers.b |= 0x02;
    cpu->registers.clk.m = 2;
}
void SET_1_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i |= 0x02;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void BIT_2_B(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.b&0x04)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_2_C(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.c&0x04)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_2_D(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.d&0x04)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_2_E(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.e&0x04)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_2_H(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.h&0x04)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_2_L(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.l&0x04)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_2_A(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.a&0x04)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_2_M(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l)&0x04)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 3;
}

void RES_2_B(gbc_cpu *cpu) {
    cpu->registers.b &= 0xFB;
    cpu->registers.clk.m = 2;
}
void RES_2_C(gbc_cpu *cpu) {
    cpu->registers.c &= 0xFB;
    cpu->registers.clk.m = 2;
}
void RES_2_D(gbc_cpu *cpu) {
    cpu->registers.d &= 0xFB;
    cpu->registers.clk.m = 2;
}
void RES_2_E(gbc_cpu *cpu) {
    cpu->registers.e &= 0xFB;
    cpu->registers.clk.m = 2;
}
void RES_2_H(gbc_cpu *cpu) {
    cpu->registers.h &= 0xFB;
    cpu->registers.clk.m = 2;
}
void RES_2_L(gbc_cpu *cpu) {
    cpu->registers.l &= 0xFB;
    cpu->registers.clk.m = 2;
}
void RES_2_A(gbc_cpu *cpu) {
    cpu->registers.a &= 0xFB;
    cpu->registers.clk.m = 2;
}
void RES_2_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i &= 0xFB;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void SET_2_B(gbc_cpu *cpu) {
    cpu->registers.b |= 0x04;
    cpu->registers.clk.m = 2;
}
void SET_2_C(gbc_cpu *cpu) {
    cpu->registers.b |= 0x04;
    cpu->registers.clk.m = 2;
}
void SET_2_D(gbc_cpu *cpu) {
    cpu->registers.b |= 0x04;
    cpu->registers.clk.m = 2;
}
void SET_2_E(gbc_cpu *cpu) {
    cpu->registers.b |= 0x04;
    cpu->registers.clk.m = 2;
}
void SET_2_H(gbc_cpu *cpu) {
    cpu->registers.b |= 0x04;
    cpu->registers.clk.m = 2;
}
void SET_2_L(gbc_cpu *cpu) {
    cpu->registers.b |= 0x04;
    cpu->registers.clk.m = 2;
}
void SET_2_A(gbc_cpu *cpu) {
    cpu->registers.b |= 0x04;
    cpu->registers.clk.m = 2;
}
void SET_2_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i |= 0x04;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void BIT_3_B(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.b&0x08)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_3_C(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.c&0x08)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_3_D(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.d&0x08)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_3_E(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.e&0x08)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_3_H(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.h&0x08)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_3_L(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.l&0x08)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_3_A(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.a&0x08)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_3_M(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l)&0x08)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 3;
}

void RES_3_B(gbc_cpu *cpu) {
    cpu->registers.b &= 0xF7;
    cpu->registers.clk.m = 2;
}
void RES_3_C(gbc_cpu *cpu) {
    cpu->registers.c &= 0xF7;
    cpu->registers.clk.m = 2;
}
void RES_3_D(gbc_cpu *cpu) {
    cpu->registers.d &= 0xF7;
    cpu->registers.clk.m = 2;
}
void RES_3_E(gbc_cpu *cpu) {
    cpu->registers.e &= 0xF7;
    cpu->registers.clk.m = 2;
}
void RES_3_H(gbc_cpu *cpu) {
    cpu->registers.h &= 0xF7;
    cpu->registers.clk.m = 2;
}
void RES_3_L(gbc_cpu *cpu) {
    cpu->registers.l &= 0xF7;
    cpu->registers.clk.m = 2;
}
void RES_3_A(gbc_cpu *cpu) {
    cpu->registers.a &= 0xF7;
    cpu->registers.clk.m = 2;
}
void RES_3_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i &= 0xF7;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void SET_3_B(gbc_cpu *cpu) {
    cpu->registers.b |= 0x08;
    cpu->registers.clk.m = 2;
}
void SET_3_C(gbc_cpu *cpu) {
    cpu->registers.b |= 0x08;
    cpu->registers.clk.m = 2;
}
void SET_3_D(gbc_cpu *cpu) {
    cpu->registers.b |= 0x08;
    cpu->registers.clk.m = 2;
}
void SET_3_E(gbc_cpu *cpu) {
    cpu->registers.b |= 0x08;
    cpu->registers.clk.m = 2;
}
void SET_3_H(gbc_cpu *cpu) {
    cpu->registers.b |= 0x08;
    cpu->registers.clk.m = 2;
}
void SET_3_L(gbc_cpu *cpu) {
    cpu->registers.b |= 0x08;
    cpu->registers.clk.m = 2;
}
void SET_3_A(gbc_cpu *cpu) {
    cpu->registers.b |= 0x08;
    cpu->registers.clk.m = 2;
}
void SET_3_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i |= 0x08;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void BIT_4_B(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.b&0x10)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_4_C(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.c&0x10)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_4_D(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.d&0x10)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_4_E(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.e&0x10)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_4_H(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.h&0x10)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_4_L(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.l&0x10)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_4_A(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.a&0x10)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_4_M(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l)&0x10)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 3;
}

void RES_4_B(gbc_cpu *cpu) {
    cpu->registers.b &= 0xEF;
    cpu->registers.clk.m = 2;
}
void RES_4_C(gbc_cpu *cpu) {
    cpu->registers.c &= 0xEF;
    cpu->registers.clk.m = 2;
}
void RES_4_D(gbc_cpu *cpu) {
    cpu->registers.d &= 0xEF;
    cpu->registers.clk.m = 2;
}
void RES_4_E(gbc_cpu *cpu) {
    cpu->registers.e &= 0xEF;
    cpu->registers.clk.m = 2;
}
void RES_4_H(gbc_cpu *cpu) {
    cpu->registers.h &= 0xEF;
    cpu->registers.clk.m = 2;
}
void RES_4_L(gbc_cpu *cpu) {
    cpu->registers.l &= 0xEF;
    cpu->registers.clk.m = 2;
}
void RES_4_A(gbc_cpu *cpu) {
    cpu->registers.a &= 0xEF;
    cpu->registers.clk.m = 2;
}
void RES_4_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i &= 0xEF;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void SET_4_B(gbc_cpu *cpu) {
    cpu->registers.b |= 0x10;
    cpu->registers.clk.m = 2;
}
void SET_4_C(gbc_cpu *cpu) {
    cpu->registers.b |= 0x10;
    cpu->registers.clk.m = 2;
}
void SET_4_D(gbc_cpu *cpu) {
    cpu->registers.b |= 0x10;
    cpu->registers.clk.m = 2;
}
void SET_4_E(gbc_cpu *cpu) {
    cpu->registers.b |= 0x10;
    cpu->registers.clk.m = 2;
}
void SET_4_H(gbc_cpu *cpu) {
    cpu->registers.b |= 0x10;
    cpu->registers.clk.m = 2;
}
void SET_4_L(gbc_cpu *cpu) {
    cpu->registers.b |= 0x10;
    cpu->registers.clk.m = 2;
}
void SET_4_A(gbc_cpu *cpu) {
    cpu->registers.b |= 0x10;
    cpu->registers.clk.m = 2;
}
void SET_4_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i|=FLAG_C;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void BIT_5_B(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.b&FLAG_H)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_5_C(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.c&0x20)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_5_D(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.d&0x20)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_5_E(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.e&0x20)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_5_H(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.h&0x20)?0:FLAG_Z;
    cpu->registers.clk.m = 2;
    cpu->registers.f|=FLAG_H;
}
void BIT_5_L(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.l&0x20)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_5_A(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.a&0x20)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_5_M(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l)&0x20)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 3;
}

void RES_5_B(gbc_cpu *cpu) {
    cpu->registers.b &= 0xDF;
    cpu->registers.clk.m = 2;
}
void RES_5_C(gbc_cpu *cpu) {
    cpu->registers.c &= 0xDF;
    cpu->registers.clk.m = 2;
}
void RES_5_D(gbc_cpu *cpu) {
    cpu->registers.d &= 0xDF;
    cpu->registers.clk.m = 2;
}
void RES_5_E(gbc_cpu *cpu) {
    cpu->registers.e &= 0xDF;
    cpu->registers.clk.m = 2;
}
void RES_5_H(gbc_cpu *cpu) {
    cpu->registers.h &= 0xDF;
    cpu->registers.clk.m = 2;
}
void RES_5_L(gbc_cpu *cpu) {
    cpu->registers.l &= 0xDF;
    cpu->registers.clk.m = 2;
}
void RES_5_A(gbc_cpu *cpu) {
    cpu->registers.a &= 0xDF;
    cpu->registers.clk.m = 2;
}
void RES_5_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i &= 0xDF;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void SET_5_B(gbc_cpu *cpu) {
    cpu->registers.b |= 0x20;
    cpu->registers.clk.m = 2;
}
void SET_5_C(gbc_cpu *cpu) {
    cpu->registers.b |= 0x20;
    cpu->registers.clk.m = 2;
}
void SET_5_D(gbc_cpu *cpu) {
    cpu->registers.b |= 0x20;
    cpu->registers.clk.m = 2;
}
void SET_5_E(gbc_cpu *cpu) {
    cpu->registers.b |= 0x20;
    cpu->registers.clk.m = 2;
}
void SET_5_H(gbc_cpu *cpu) {
    cpu->registers.b |= 0x20;
    cpu->registers.clk.m = 2;
}
void SET_5_L(gbc_cpu *cpu) {
    cpu->registers.b |= 0x20;
    cpu->registers.clk.m = 2;
}
void SET_5_A(gbc_cpu *cpu) {
    cpu->registers.b |= 0x20;
    cpu->registers.clk.m = 2;
}
void SET_5_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i |= 0x20;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void BIT_6_B(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.b&0x40)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_6_C(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.c&0x40)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_6_D(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.d&0x40)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_6_E(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.e&0x40)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_6_H(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.h&0x40)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_6_L(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.l&0x40)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_6_A(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.a&0x40)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_6_M(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l)&0x40)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 3;
}

void RES_6_B(gbc_cpu *cpu) {
    cpu->registers.b &= 0xBF;
    cpu->registers.clk.m = 2;
}
void RES_6_C(gbc_cpu *cpu) {
    cpu->registers.c &= 0xBF;
    cpu->registers.clk.m = 2;
}
void RES_6_D(gbc_cpu *cpu) {
    cpu->registers.d &= 0xBF;
    cpu->registers.clk.m = 2;
}
void RES_6_E(gbc_cpu *cpu) {
    cpu->registers.e &= 0xBF;
    cpu->registers.clk.m = 2;
}
void RES_6_H(gbc_cpu *cpu) {
    cpu->registers.h &= 0xBF;
    cpu->registers.clk.m = 2;
}
void RES_6_L(gbc_cpu *cpu) {
    cpu->registers.l &= 0xBF;
    cpu->registers.clk.m = 2;
}
void RES_6_A(gbc_cpu *cpu) {
    cpu->registers.a &= 0xBF;
    cpu->registers.clk.m = 2;
}
void RES_6_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i &= 0xBF;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void SET_6_B(gbc_cpu *cpu) {
    cpu->registers.b |= 0x40;
    cpu->registers.clk.m = 2;
}
void SET_6_C(gbc_cpu *cpu) {
    cpu->registers.b |= 0x40;
    cpu->registers.clk.m = 2;
}
void SET_6_D(gbc_cpu *cpu) {
    cpu->registers.b |= 0x40;
    cpu->registers.clk.m = 2;
}
void SET_6_E(gbc_cpu *cpu) {
    cpu->registers.b |= 0x40;
    cpu->registers.clk.m = 2;
}
void SET_6_H(gbc_cpu *cpu) {
    cpu->registers.b |= 0x40;
    cpu->registers.clk.m = 2;
}
void SET_6_L(gbc_cpu *cpu) {
    cpu->registers.b |= 0x40;
    cpu->registers.clk.m = 2;
}
void SET_6_A(gbc_cpu *cpu) {
    cpu->registers.b |= 0x40;
    cpu->registers.clk.m = 2;
}
void SET_6_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i |= 0x40;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void BIT_7_B(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.b&0x80)?0:FLAG_Z;
    cpu->registers.clk.m = 2;
    cpu->registers.f|=FLAG_H;
}
void BIT_7_C(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.c&0x80)?0:FLAG_Z;
    cpu->registers.clk.m = 2;
    cpu->registers.f|=FLAG_H;
}
void BIT_7_D(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.d&0x80)?0:FLAG_Z;
    cpu->registers.clk.m = 2;
    cpu->registers.f|=FLAG_H;
}
void BIT_7_E(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.e&0x80)?0:FLAG_Z;
    cpu->registers.clk.m = 2;
    cpu->registers.f|=FLAG_H;
}
void BIT_7_H(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.h&0x80)?0:FLAG_Z;
    cpu->registers.clk.m = 2;
    cpu->registers.f|=FLAG_H;
}
void BIT_7_L(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.l&0x80)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_7_A(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(cpu->registers.a&0x80)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 2;
}
void BIT_7_M(gbc_cpu *cpu) {
    cpu->registers.f &= 0x1F;
    cpu->registers.f=(read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l)&0x80)?0:FLAG_Z;
    cpu->registers.f|=FLAG_H;
    cpu->registers.clk.m = 3;
}

void RES_7_B(gbc_cpu *cpu) {
    cpu->registers.b &= 0x7F;
    cpu->registers.clk.m = 2;
}
void RES_7_C(gbc_cpu *cpu) {
    cpu->registers.c &= 0x7F;
    cpu->registers.clk.m = 2;
}
void RES_7_D(gbc_cpu *cpu) {
    cpu->registers.d &= 0x7F;
    cpu->registers.clk.m = 2;
}
void RES_7_E(gbc_cpu *cpu) {
    cpu->registers.e &= 0x7F;
    cpu->registers.clk.m = 2;
}
void RES_7_H(gbc_cpu *cpu) {
    cpu->registers.h &= 0x7F;
    cpu->registers.clk.m = 2;
}
void RES_7_L(gbc_cpu *cpu) {
    cpu->registers.l &= 0x7F;
    cpu->registers.clk.m = 2;
}
void RES_7_A(gbc_cpu *cpu) {
    cpu->registers.a &= 0x7F;
    cpu->registers.clk.m = 2;
}
void RES_7_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i &= 0x7F;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void SET_7_B(gbc_cpu *cpu) {
    cpu->registers.b |= 0x80;
    cpu->registers.clk.m = 2;
}
void SET_7_C(gbc_cpu *cpu) {
    cpu->registers.b |= 0x80;
    cpu->registers.clk.m = 2;
}
void SET_7_D(gbc_cpu *cpu) {
    cpu->registers.b |= 0x80;
    cpu->registers.clk.m = 2;
}
void SET_7_E(gbc_cpu *cpu) {
    cpu->registers.b |= 0x80;
    cpu->registers.clk.m = 2;
}
void SET_7_H(gbc_cpu *cpu) {
    cpu->registers.b |= 0x80;
    cpu->registers.clk.m = 2;
}
void SET_7_L(gbc_cpu *cpu) {
    cpu->registers.b |= 0x80;
    cpu->registers.clk.m = 2;
}
void SET_7_A(gbc_cpu *cpu) {
    cpu->registers.b |= 0x80;
    cpu->registers.clk.m = 2;
}
void SET_7_M(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    i |= 0x80;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.clk.m = 4;
}

void RLA(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?1:0;
    u8 co = cpu->registers.a&FLAG_Z?0x10:0;
    cpu->registers.a=(cpu->registers.a<<1)+ci;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 1;
}
void RLCA(gbc_cpu *cpu) {
    u8 ci = cpu->registers.a&FLAG_Z?1:0;
    u8 co = cpu->registers.a&FLAG_Z?FLAG_C:0;
    cpu->registers.a=(cpu->registers.a<<1)+ci;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 1;
}
void RRA(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?FLAG_Z:0;
    u8 co = cpu->registers.a&1?0x10:0;
    cpu->registers.a=(cpu->registers.a>>1)+ci;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 1;
}
void RRCA(gbc_cpu *cpu) {
    u8 ci = cpu->registers.a&1?FLAG_Z:0;
    u8 co = cpu->registers.a&1?FLAG_C:0;
    cpu->registers.a=(cpu->registers.a>>1)+ci;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 1;
}

void RL_B(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?1:0;
    u8 co = cpu->registers.b&FLAG_Z?0x10:0;
    cpu->registers.b=(cpu->registers.b<<1)+ci;
    cpu->registers.f=(cpu->registers.b)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RL_C(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?1:0;
    u8 co = cpu->registers.c&FLAG_Z?0x10:0;
    cpu->registers.c=(cpu->registers.c<<1)+ci;
    cpu->registers.f=(cpu->registers.c)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RL_D(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?1:0;
    u8 co = cpu->registers.d&FLAG_Z?0x10:0;
    cpu->registers.d=(cpu->registers.d<<1)+ci;
    cpu->registers.f=(cpu->registers.d)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RL_E(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?1:0;
    u8 co = cpu->registers.e&FLAG_Z?0x10:0;
    cpu->registers.e=(cpu->registers.e<<1)+ci;
    cpu->registers.f=(cpu->registers.e)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RL_H(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?1:0;
    u8 co = cpu->registers.h&FLAG_Z?0x10:0;
    cpu->registers.h=(cpu->registers.h<<1)+ci;
    cpu->registers.f=(cpu->registers.h)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RL_L(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?1:0;
    u8 co = cpu->registers.l&FLAG_Z?0x10:0;
    cpu->registers.l=(cpu->registers.l<<1)+ci;
    cpu->registers.f=(cpu->registers.l)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RL_A(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?1:0;
    u8 co = cpu->registers.a&FLAG_Z?0x10:0;
    cpu->registers.a=(cpu->registers.a<<1)+ci;
    cpu->registers.f=(cpu->registers.a)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RL_mHL(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    u8 ci = cpu->registers.f&FLAG_C?1:0;
    u8 co = i&FLAG_Z?0x10:0;
    i=(i<<1)+ci;
    i&=255;
    cpu->registers.f=(i)?0:FLAG_Z;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 4;
}

void RLC_B(gbc_cpu *cpu) {
    u8 ci = cpu->registers.b&FLAG_Z?1:0;
    u8 co = cpu->registers.b&FLAG_Z?FLAG_C:0;
    cpu->registers.b=(cpu->registers.b<<1)+ci;
    cpu->registers.f=(cpu->registers.b)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RLC_C(gbc_cpu *cpu) {
    u8 ci = cpu->registers.c&FLAG_Z?1:0;
    u8 co = cpu->registers.c&FLAG_Z?FLAG_C:0;
    cpu->registers.c=(cpu->registers.c<<1)+ci;
    cpu->registers.f=(cpu->registers.c)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RLC_D(gbc_cpu *cpu) {
    u8 ci = cpu->registers.d&FLAG_Z?1:0;
    u8 co = cpu->registers.d&FLAG_Z?FLAG_C:0;
    cpu->registers.d=(cpu->registers.d<<1)+ci;
    cpu->registers.f=(cpu->registers.d)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RLC_E(gbc_cpu *cpu) {
    u8 ci = cpu->registers.e&FLAG_Z?1:0;
    u8 co = cpu->registers.e&FLAG_Z?FLAG_C:0;
    cpu->registers.e=(cpu->registers.e<<1)+ci;
    cpu->registers.f=(cpu->registers.e)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RLC_H(gbc_cpu *cpu) {
    u8 ci = cpu->registers.h&FLAG_Z?1:0;
    u8 co = cpu->registers.h&FLAG_Z?FLAG_C:0;
    cpu->registers.h=(cpu->registers.h<<1)+ci;
    cpu->registers.f=(cpu->registers.h)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RLC_L(gbc_cpu *cpu) {
    u8 ci = cpu->registers.l&FLAG_Z?1:0;
    u8 co = cpu->registers.l&FLAG_Z?FLAG_C:0;
    cpu->registers.l=(cpu->registers.l<<1)+ci;
    cpu->registers.f=(cpu->registers.l)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RLC_A(gbc_cpu *cpu) {
    u8 ci = cpu->registers.a&FLAG_Z?1:0;
    u8 co = cpu->registers.a&FLAG_Z?FLAG_C:0;
    cpu->registers.a=(cpu->registers.a<<1)+ci;
    cpu->registers.f=(cpu->registers.a)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RLC_mHL(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    u8 ci = i&FLAG_Z?1:0;
    u8 co = i&FLAG_Z?FLAG_C:0;
    i=(i<<1)+ci;
    i&=255;
    cpu->registers.f=(i)?0:FLAG_Z;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 4;
}

void RR_B(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?FLAG_Z:0;
    u8 co = cpu->registers.b&1?0x10:0;
    cpu->registers.b=(cpu->registers.b>>1)+ci;
    cpu->registers.f=(cpu->registers.b)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RR_C(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?FLAG_Z:0;
    u8 co = cpu->registers.c&1?0x10:0;
    cpu->registers.c=(cpu->registers.c>>1)+ci;
    cpu->registers.f=(cpu->registers.c)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RR_D(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?FLAG_Z:0;
    u8 co = cpu->registers.d&1?0x10:0;
    cpu->registers.d=(cpu->registers.d>>1)+ci;
    cpu->registers.f=(cpu->registers.d)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RR_E(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?FLAG_Z:0;
    u8 co = cpu->registers.e&1?0x10:0;
    cpu->registers.e=(cpu->registers.e>>1)+ci;
    cpu->registers.f=(cpu->registers.e)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RR_H(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?FLAG_Z:0;
    u8 co = cpu->registers.h&1?0x10:0;
    cpu->registers.h=(cpu->registers.h>>1)+ci;
    cpu->registers.f=(cpu->registers.h)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RR_L(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?FLAG_Z:0;
    u8 co = cpu->registers.l&1?0x10:0;
    cpu->registers.l=(cpu->registers.l>>1)+ci;
    cpu->registers.f=(cpu->registers.l)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RR_A(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?FLAG_Z:0;
    u8 co = cpu->registers.a&1?0x10:0;
    cpu->registers.a=(cpu->registers.a>>1)+ci;
    cpu->registers.f=(cpu->registers.a)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RR_mHL(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    u8 ci = cpu->registers.f&FLAG_C?FLAG_Z:0;
    u8 co = i&1?0x10:0;
    i=(i>>1)+ci;
    i&=255;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.f=(i)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 4;
}

void RRC_B(gbc_cpu *cpu) {
    u8 ci = cpu->registers.b&1?FLAG_Z:0;
    u8 co = cpu->registers.b&1?FLAG_C:0;
    cpu->registers.b=(cpu->registers.b>>1)+ci;
    cpu->registers.f=(cpu->registers.b)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RRC_C(gbc_cpu *cpu) {
    u8 ci = cpu->registers.c&1?FLAG_Z:0;
    u8 co = cpu->registers.c&1?FLAG_C:0;
    cpu->registers.c=(cpu->registers.c>>1)+ci;
    cpu->registers.f=(cpu->registers.c)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RRC_D(gbc_cpu *cpu) {
    u8 ci = cpu->registers.d&1?FLAG_Z:0;
    u8 co = cpu->registers.d&1?FLAG_C:0;
    cpu->registers.d=(cpu->registers.d>>1)+ci;
    cpu->registers.f=(cpu->registers.d)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RRC_E(gbc_cpu *cpu) {
    u8 ci = cpu->registers.e&1?FLAG_Z:0;
    u8 co = cpu->registers.e&1?FLAG_C:0;
    cpu->registers.e=(cpu->registers.e>>1)+ci;
    cpu->registers.f=(cpu->registers.e)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RRC_H(gbc_cpu *cpu) {
    u8 ci = cpu->registers.h&1?FLAG_Z:0;
    u8 co = cpu->registers.h&1?FLAG_C:0;
    cpu->registers.h=(cpu->registers.h>>1)+ci;
    cpu->registers.f=(cpu->registers.h)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RRC_L(gbc_cpu *cpu) {
    u8 ci = cpu->registers.l&1?FLAG_Z:0;
    u8 co = cpu->registers.l&1?FLAG_C:0;
    cpu->registers.l=(cpu->registers.l>>1)+ci;
    cpu->registers.f=(cpu->registers.l)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RRC_A(gbc_cpu *cpu) {
    u8 ci = cpu->registers.a&1?FLAG_Z:0;
    u8 co = cpu->registers.a&1?FLAG_C:0;
    cpu->registers.a=(cpu->registers.a>>1)+ci;
    cpu->registers.f=(cpu->registers.a)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void RRC_mHL(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l);
    u8 ci = i&1?FLAG_Z:0;
    u8 co = i&1?FLAG_C:0;
    i=(i>>1)+ci;
    i&=255;
    write_u8(cpu->mmu,(cpu->registers.h<<8)+cpu->registers.l,i);
    cpu->registers.f=(i)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 4;
}

void SLA_B(gbc_cpu *cpu) {
    u8 co = cpu->registers.b&FLAG_Z?FLAG_C:0;
    cpu->registers.b=(cpu->registers.b<<1)&255;
    cpu->registers.f=(cpu->registers.b)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLA_C(gbc_cpu *cpu) {
    u8 co = cpu->registers.c&FLAG_Z?FLAG_C:0;
    cpu->registers.c=(cpu->registers.c<<1)&255;
    cpu->registers.f=(cpu->registers.c)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLA_D(gbc_cpu *cpu) {
    u8 co = cpu->registers.d&FLAG_Z?FLAG_C:0;
    cpu->registers.d=(cpu->registers.d<<1)&255;
    cpu->registers.f=(cpu->registers.d)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLA_E(gbc_cpu *cpu) {
    u8 co = cpu->registers.e&FLAG_Z?FLAG_C:0;
    cpu->registers.e=(cpu->registers.e<<1)&255;
    cpu->registers.f=(cpu->registers.e)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLA_H(gbc_cpu *cpu) {
    u8 co = cpu->registers.h&FLAG_Z?FLAG_C:0;
    cpu->registers.h=(cpu->registers.h<<1)&255;
    cpu->registers.f=(cpu->registers.h)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLA_L(gbc_cpu *cpu) {
    u8 co = cpu->registers.l&FLAG_Z?FLAG_C:0;
    cpu->registers.l=(cpu->registers.l<<1)&255;
    cpu->registers.f=(cpu->registers.l)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLA_A(gbc_cpu *cpu) {
    u8 co = cpu->registers.a&FLAG_Z?FLAG_C:0;
    cpu->registers.a=(cpu->registers.a<<1)&255;
    cpu->registers.f=(cpu->registers.a)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}

void SLL_B(gbc_cpu *cpu) {
    u8 co = cpu->registers.b&FLAG_Z?FLAG_C:0;
    cpu->registers.b=(cpu->registers.b<<1)&255+1;
    cpu->registers.f=(cpu->registers.b)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLL_C(gbc_cpu *cpu) {
    u8 co = cpu->registers.c&FLAG_Z?FLAG_C:0;
    cpu->registers.c=(cpu->registers.c<<1)&255+1;
    cpu->registers.f=(cpu->registers.c)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLL_D(gbc_cpu *cpu) {
    u8 co = cpu->registers.d&FLAG_Z?FLAG_C:0;
    cpu->registers.d=(cpu->registers.d<<1)&255+1;
    cpu->registers.f=(cpu->registers.d)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLL_E(gbc_cpu *cpu) {
    u8 co = cpu->registers.e&FLAG_Z?FLAG_C:0;
    cpu->registers.e=(cpu->registers.e<<1)&255+1;
    cpu->registers.f=(cpu->registers.e)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLL_H(gbc_cpu *cpu) {
    u8 co = cpu->registers.h&FLAG_Z?FLAG_C:0;
    cpu->registers.h=(cpu->registers.h<<1)&255+1;
    cpu->registers.f=(cpu->registers.h)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLL_L(gbc_cpu *cpu) {
    u8 co = cpu->registers.l&FLAG_Z?FLAG_C:0;
    cpu->registers.l=(cpu->registers.l<<1)&255+1;
    cpu->registers.f=(cpu->registers.l)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SLL_A(gbc_cpu *cpu) {
    u8 co = cpu->registers.a&FLAG_Z?FLAG_C:0;
    cpu->registers.a=(cpu->registers.a<<1)&255+1;
    cpu->registers.f=(cpu->registers.a)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}

void SRA_B(gbc_cpu *cpu) {
    u8 ci = cpu->registers.b&FLAG_Z;
    u8 co = cpu->registers.b&1?FLAG_C:0;
    cpu->registers.b=((cpu->registers.b>>1)+ci)&255;
    cpu->registers.f=(cpu->registers.b)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRA_C(gbc_cpu *cpu) {
    u8 ci = cpu->registers.c&FLAG_Z;
    u8 co = cpu->registers.c&1?FLAG_C:0;
    cpu->registers.c=((cpu->registers.c>>1)+ci)&255;
    cpu->registers.f=(cpu->registers.c)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRA_D(gbc_cpu *cpu) {
    u8 ci = cpu->registers.d&FLAG_Z;
    u8 co = cpu->registers.d&1?FLAG_C:0;
    cpu->registers.d=((cpu->registers.d>>1)+ci)&255;
    cpu->registers.f=(cpu->registers.d)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRA_E(gbc_cpu *cpu) {
    u8 ci = cpu->registers.e&FLAG_Z;
    u8 co = cpu->registers.e&1?FLAG_C:0;
    cpu->registers.e=((cpu->registers.e>>1)+ci)&255;
    cpu->registers.f=(cpu->registers.e)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRA_H(gbc_cpu *cpu) {
    u8 ci = cpu->registers.h&FLAG_Z;
    u8 co = cpu->registers.h&1?FLAG_C:0;
    cpu->registers.h=((cpu->registers.h>>1)+ci)&255;
    cpu->registers.f=(cpu->registers.h)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRA_L(gbc_cpu *cpu) {
    u8 ci = cpu->registers.l&FLAG_Z;
    u8 co = cpu->registers.l&1?FLAG_C:0;
    cpu->registers.l=((cpu->registers.l>>1)+ci)&255;
    cpu->registers.f=(cpu->registers.l)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRA_A(gbc_cpu *cpu) {
    u8 ci = cpu->registers.a&FLAG_Z;
    u8 co = cpu->registers.a&1?FLAG_C:0;
    cpu->registers.a=((cpu->registers.a>>1)+ci)&255;
    cpu->registers.f=(cpu->registers.a)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}

void SRL_B(gbc_cpu *cpu) {
    u8 co = cpu->registers.b&1?FLAG_C:0;
    cpu->registers.b=(cpu->registers.b>>1)&255;
    cpu->registers.f=(cpu->registers.b)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRL_C(gbc_cpu *cpu) {
    u8 co = cpu->registers.c&1?FLAG_C:0;
    cpu->registers.c=(cpu->registers.c>>1)&255;
    cpu->registers.f=(cpu->registers.c)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRL_D(gbc_cpu *cpu) {
    u8 co = cpu->registers.d&1?FLAG_C:0;
    cpu->registers.d=(cpu->registers.d>>1)&255;
    cpu->registers.f=(cpu->registers.d)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRL_E(gbc_cpu *cpu) {
    u8 co = cpu->registers.e&1?FLAG_C:0;
    cpu->registers.e=(cpu->registers.e>>1)&255;
    cpu->registers.f=(cpu->registers.e)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRL_H(gbc_cpu *cpu) {
    u8 co = cpu->registers.h&1?FLAG_C:0;
    cpu->registers.h=(cpu->registers.h>>1)&255;
    cpu->registers.f=(cpu->registers.h)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRL_L(gbc_cpu *cpu) {
    u8 co = cpu->registers.l&1?FLAG_C:0;
    cpu->registers.l=(cpu->registers.l>>1)&255;
    cpu->registers.f=(cpu->registers.l)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}
void SRL_A(gbc_cpu *cpu) {
    u8 co = cpu->registers.a&1?FLAG_C:0;
    cpu->registers.a=(cpu->registers.a>>1)&255;
    cpu->registers.f=(cpu->registers.a)?0:FLAG_Z;
    cpu->registers.f=(cpu->registers.f&0xEF)+co;
    cpu->registers.clk.m = 2;
}

void CPL(gbc_cpu *cpu) {
    cpu->registers.a ^= 255;
    cpu->registers.f = cpu->registers.a?0:FLAG_Z;
    cpu->registers.clk.m = 1;
}
void NEG(gbc_cpu *cpu) {
    cpu->registers.a = 0-cpu->registers.a;
    cpu->registers.f=(cpu->registers.a<0)?FLAG_C:0;
    if(!cpu->registers.a) cpu->registers.f|=FLAG_Z;
    cpu->registers.clk.m = 2;
}

void CCF(gbc_cpu *cpu) {
    u8 ci = cpu->registers.f&FLAG_C?0:0x10;
    cpu->registers.f=(cpu->registers.f&0xEF)+ci;
    cpu->registers.clk.m = 1;
}

void PUSH_BC(gbc_cpu *cpu) {
    cpu->registers.sp--;
    write_u8(cpu->mmu,cpu->registers.sp,cpu->registers.b);
    cpu->registers.sp--;
    write_u8(cpu->mmu,cpu->registers.sp,cpu->registers.c);
    cpu->registers.clk.m = 3;
}
void PUSH_DE(gbc_cpu *cpu) {
    cpu->registers.sp--;
    write_u8(cpu->mmu,cpu->registers.sp,cpu->registers.d);
    cpu->registers.sp--;
    write_u8(cpu->mmu,cpu->registers.sp,cpu->registers.e);
    cpu->registers.clk.m = 3;
}
void PUSH_HL(gbc_cpu *cpu) {
    cpu->registers.sp--;
    write_u8(cpu->mmu,cpu->registers.sp,cpu->registers.h);
    cpu->registers.sp--;
    write_u8(cpu->mmu,cpu->registers.sp,cpu->registers.l);
    cpu->registers.clk.m = 3;
}
void PUSH_AF(gbc_cpu *cpu) {
    cpu->registers.sp--;
    write_u8(cpu->mmu,cpu->registers.sp,cpu->registers.a);
    cpu->registers.sp--;
    write_u8(cpu->mmu,cpu->registers.sp,cpu->registers.f);
    cpu->registers.clk.m = 3;
}

void POP_BC(gbc_cpu *cpu) {
    cpu->registers.c = read_u8(cpu->mmu,cpu->registers.sp++);
    cpu->registers.b = read_u8(cpu->mmu,cpu->registers.sp++);
    cpu->registers.clk.m = 3;
}
void POP_DE(gbc_cpu *cpu) {
    cpu->registers.e = read_u8(cpu->mmu,cpu->registers.sp++);
    cpu->registers.d = read_u8(cpu->mmu,cpu->registers.sp++);
    cpu->registers.clk.m = 3;
}
void POP_HL(gbc_cpu *cpu) {
    cpu->registers.l = read_u8(cpu->mmu,cpu->registers.sp++);
    cpu->registers.h = read_u8(cpu->mmu,cpu->registers.sp++);
    cpu->registers.clk.m = 3;
}
void POP_AF(gbc_cpu *cpu) {
    cpu->registers.f = read_u8(cpu->mmu,cpu->registers.sp++);
    cpu->registers.a = read_u8(cpu->mmu,cpu->registers.sp++);
    cpu->registers.clk.m = 3;
}

void JP_a16(gbc_cpu *cpu) {
    cpu->registers.pc = read_u16(cpu->mmu,cpu->registers.pc);
    cpu->registers.clk.m = 3;
}
void JP_mHL(gbc_cpu *cpu) {
    cpu->registers.pc=(cpu->registers.h<<8)+cpu->registers.l;
    cpu->registers.clk.m = 1;
}
void JP_NZ_a16(gbc_cpu *cpu) {
    cpu->registers.clk.m = 3;
    if(!flag_z(cpu)) {
        cpu->registers.pc = read_u16(cpu->mmu,cpu->registers.pc);
        cpu->registers.clk.m++;
    } else cpu->registers.pc += 2;
}
void JP_Cnn(gbc_cpu *cpu) {
    cpu->registers.clk.m = 3;
    if(flag_c(cpu)) {
        cpu->registers.pc = read_u16(cpu->mmu,cpu->registers.pc);
        cpu->registers.clk.m++;
    } else cpu->registers.pc += 2;
}
void JR_r8(gbc_cpu *cpu) {
    s8 temp = read_u8(cpu->mmu, cpu->registers.pc++);
    cpu->registers.pc += temp;
    cpu->registers.clk.m += 4;
}
void JR_NZ_r8(gbc_cpu *cpu) {
    if(!flag_z(cpu)) {
        s8 temp = read_u8(cpu->mmu,cpu->registers.pc);
        cpu->registers.pc++;
        cpu->registers.pc += temp;
        cpu->registers.clk.m += 4;
    } else {
        cpu->registers.pc++;
    }
}
void JR_Z_r8(gbc_cpu *cpu)  {
    if(flag_z(cpu)){
        s8 temp = read_u8(cpu->mmu, cpu->registers.pc++);
        cpu->registers.pc += temp;
        cpu->registers.clk.m += 4;
    } else {
        cpu->registers.pc++;
    }
}
void JR_NC_r8(gbc_cpu *cpu) {
    s8 i = read_u8(cpu->mmu,cpu->registers.pc);
    /*if(i>127) i=-((~i+1)&255);*/

    cpu->registers.pc++;
    cpu->registers.clk.m = 2;

    if(!flag_c(cpu)) {
        cpu->registers.pc+=i;
        cpu->registers.clk.m++;
    }
}

void JR_C_r8(gbc_cpu *cpu)  {
    s8 i = read_u8(cpu->mmu,cpu->registers.pc);
    /*if(i>127) i=-((~i+1)&255);*/
    cpu->registers.pc++;
    cpu->registers.clk.m = 2;

    if(flag_c(cpu)) {
        cpu->registers.pc += i;
        cpu->registers.clk.m++;
    }
}

void CALL_a16(gbc_cpu *cpu) {
    u16 addr = read_u8(cpu->mmu, cpu->registers.pc++);
    addr |= read_u8(cpu->mmu, cpu->registers.pc++) << 8;
    write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc >> 8);
    write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc & 0xFF);
    cpu->registers.pc = addr;
}

void CALL_NZ_a16(gbc_cpu *cpu) {
    cpu->registers.clk.m = 3;
    if(!flag_z(cpu)) {
        u16 temp = read_u8(cpu->mmu, cpu->registers.pc++);
        temp |= read_u8(cpu->mmu, cpu->registers.pc++) << 8;
        write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc >> 8);
        write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc & 0xFF);
        cpu->registers.pc = temp;
        cpu->registers.clk.m += 12;
    } else cpu->registers.pc += 2;
}

void CALL_Z_a16(gbc_cpu *cpu) {
    cpu->registers.clk.m = 3;
    if(flag_z(cpu)) {
        u16 temp = read_u8(cpu->mmu, cpu->registers.pc++);
        temp |= read_u8(cpu->mmu, cpu->registers.pc++) << 8;
        write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc >> 8);
        write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc & 0xFF);
        cpu->registers.pc = temp;
        cpu->registers.clk.m += 12;

    } else cpu->registers.pc += 2;
}

void CALL_NC_a16(gbc_cpu *cpu) {
    cpu->registers.clk.m = 3;
    if(!flag_c(cpu)) {
        u16 temp = read_u8(cpu->mmu, cpu->registers.pc++);
        temp |= read_u8(cpu->mmu, cpu->registers.pc++) << 8;
        write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc >> 8);
        write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc & 0xFF);
        cpu->registers.pc = temp;
        cpu->registers.clk.m += 12;
    } else cpu->registers.pc += 2;
}

void CALL_C_a16(gbc_cpu *cpu) {
    cpu->registers.clk.m = 3;
    if(flag_c(cpu)) {
        u16 temp = read_u8(cpu->mmu, cpu->registers.pc++);
        temp |= read_u8(cpu->mmu, cpu->registers.pc++) << 8;
        write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc >> 8);
        write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc & 0xFF);
        cpu->registers.pc = temp;
        cpu->registers.clk.m += 12;
    } else cpu->registers.pc += 2;
}

void RET(gbc_cpu *cpu) {
    u16 temp = read_u8(cpu->mmu, cpu->registers.sp++);
    temp |= read_u8(cpu->mmu, cpu->registers.sp++) << 8;

    cpu->registers.pc = temp;
    cpu->registers.clk.m = 3;
}

void RET_I(gbc_cpu *cpu) {
    rrs(cpu);
    cpu->registers.pc = read_u16(cpu->mmu,cpu->registers.sp);
    cpu->IME = 1;
    cpu->registers.sp+=2;
    cpu->registers.clk.m = 3;
}
void RET_NZ(gbc_cpu *cpu) {
    cpu->registers.clk.m = 1;
    if (!flag_z(cpu)) {
        cpu->registers.pc = read_u16(cpu->mmu,cpu->registers.sp);
        cpu->registers.sp+=2;
        cpu->registers.clk.m+=2;
    }
}
void RET_Z(gbc_cpu *cpu) {
    cpu->registers.clk.m = 1;
    if (flag_z(cpu)) {
        cpu->registers.pc = read_u16(cpu->mmu,cpu->registers.sp);
        cpu->registers.sp+=2;
        cpu->registers.clk.m+=2;
    }
}
void RET_NC(gbc_cpu *cpu) {
    cpu->registers.clk.m = 1;
    if (!flag_c(cpu)) {
        cpu->registers.pc = read_u16(cpu->mmu,cpu->registers.sp);
        cpu->registers.sp+=2;
        cpu->registers.clk.m+=2;
    }
}
void RET_C(gbc_cpu *cpu) {
    cpu->registers.clk.m = 1;
    if (flag_c(cpu)) {
        cpu->registers.pc = read_u16(cpu->mmu,cpu->registers.sp);
        cpu->registers.sp+=2;
        cpu->registers.clk.m+=2;
    }
}


void JP_C_a16(gbc_cpu *cpu) {
    cpu->registers.clk.m = 3;
    if(flag_c(cpu)) {
        cpu->registers.pc = read_u16(cpu->mmu,cpu->registers.pc);
        cpu->registers.clk.m++;
    } else cpu->registers.pc += 2;
}
void JP_Z_a16(gbc_cpu *cpu) {
    cpu->registers.clk.m = 3;
    if(flag_z(cpu)) {
        cpu->registers.pc = read_u16(cpu->mmu,cpu->registers.pc);
        cpu->registers.clk.m++;
    } else cpu->registers.pc += 2;
}

void JP_NC_a16(gbc_cpu *cpu) {
    if(!flag_c(cpu)) {
        u16 temp = read_u8(cpu->mmu, cpu->registers.pc++);
        temp |=  read_u8(cpu->mmu, cpu->registers.pc++) << 8;
        cpu->registers.pc = temp;
        cpu->registers.clk.m += 4;
    }
    else
        cpu->registers.pc += 2;
}


void RST_u8(gbc_cpu *cpu, u8 v) {
    rsv(cpu);
    cpu->registers.sp-=2;
    write_u16(cpu->mmu,cpu->registers.sp,cpu->registers.pc);
    cpu->registers.pc = v;
    cpu->registers.clk.m = 3;
}

void RST_00H(gbc_cpu *cpu) {
    rsv(cpu);
    cpu->registers.sp-=2;
    write_u16(cpu->mmu,cpu->registers.sp,cpu->registers.pc);
    cpu->registers.pc = 0x00;
    cpu->registers.clk.m = 3;
}
void RST_08H(gbc_cpu *cpu) {
    rsv(cpu);
    cpu->registers.sp-=2;
    write_u16(cpu->mmu,cpu->registers.sp,cpu->registers.pc);
    cpu->registers.pc = 0x08;
    cpu->registers.clk.m = 3;
}
void RST_10H(gbc_cpu *cpu) {
    rsv(cpu);
    cpu->registers.sp-=2;
    write_u16(cpu->mmu,cpu->registers.sp,cpu->registers.pc);
    cpu->registers.pc = 0x10;
    cpu->registers.clk.m = 3;
}
void RST_18H(gbc_cpu *cpu) {
    rsv(cpu);
    cpu->registers.sp-=2;
    write_u16(cpu->mmu,cpu->registers.sp,cpu->registers.pc);
    cpu->registers.pc = 0x18;
    cpu->registers.clk.m = 3;
}
void RST_20H(gbc_cpu *cpu) {
    rsv(cpu);
    cpu->registers.sp-=2;
    write_u16(cpu->mmu,cpu->registers.sp,cpu->registers.pc);
    cpu->registers.pc = 0x20;
    cpu->registers.clk.m = 3;
}
void RST_28H(gbc_cpu *cpu) {
    rsv(cpu);
    cpu->registers.sp-=2;
    write_u16(cpu->mmu,cpu->registers.sp,cpu->registers.pc);
    cpu->registers.pc = 0x28;
    cpu->registers.clk.m = 3;
}
void RST_30H(gbc_cpu *cpu) {
    rsv(cpu);
    cpu->registers.sp-=2;
    write_u16(cpu->mmu,cpu->registers.sp,cpu->registers.pc);
    cpu->registers.pc = 0x30;
    cpu->registers.clk.m = 3;
}
void RST_38H(gbc_cpu *cpu) {
    rsv(cpu);
    cpu->registers.sp -= 2;
    write_u16(cpu->mmu,cpu->registers.sp,cpu->registers.pc);
    cpu->registers.pc = 0x38;
    cpu->registers.clk.m = 3;
}

void NOP(gbc_cpu *cpu) {
    cpu->registers.clk.m = 1;
}

void HALT(gbc_cpu *cpu) {
    cpu->HALT =1;
    cpu->registers.clk.m = 1;
}
void DI(gbc_cpu *cpu) {
    cpu->IME = 0;
    cpu->registers.clk.m = 1;
}
void EI(gbc_cpu *cpu) {
    cpu->IME = 1;
    cpu->registers.clk.m = 1;
}

void rsv(gbc_cpu *cpu) {
    cpu->rsv.a = cpu->registers.a;
    cpu->rsv.b = cpu->registers.b;
    cpu->rsv.c = cpu->registers.c;
    cpu->rsv.d = cpu->registers.d;
    cpu->rsv.e = cpu->registers.e;
    cpu->rsv.f = cpu->registers.f;
    cpu->rsv.h = cpu->registers.h;
    cpu->rsv.l = cpu->registers.l;
}

void rrs(gbc_cpu *cpu) {
    cpu->registers.a = cpu->rsv.a;
    cpu->registers.b = cpu->rsv.b;
    cpu->registers.c = cpu->rsv.c;
    cpu->registers.d = cpu->rsv.d;
    cpu->registers.e = cpu->rsv.e;
    cpu->registers.f = cpu->rsv.f;
    cpu->registers.h = cpu->rsv.h;
    cpu->registers.l = cpu->rsv.l;
}

void MAPcb(gbc_cpu *cpu) {
    u8 i = read_u8(cpu->mmu, cpu->registers.pc++);
    cpu->registers.pc &= 65535;
    if(CB_OPS[i]) CB_OPS[i](cpu);
}

void XX(gbc_cpu *cpu) {
    /*u8 opcode = read_u8(cpu->mmu, cpu->registers.pc-1);
    */
    /*printf("ERROR: OPCODE UNIMPLEMETED %x?\n", opcode);
    */
}

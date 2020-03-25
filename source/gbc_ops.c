#include <stdio.h>
#include "gbc_ops.h"

#define min(X, Y)  ((X) < (Y) ? (X) : (Y))
#define half_carry(a, b)  (((a & 0xF) + (b & 0xF)) & 0x10) == 0x10

void execute_op(gbc_cpu *cpu, u8 opcode) {
    cpu->registers.clk.m = 0;
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
            LD_a16_SP(cpu);
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
            LD_r8_u8(cpu, &cpu->registers.d, read_u8(cpu->mmu,cpu->registers.pc++));
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
            INC_r8(cpu, &cpu->registers.h);
            break;
        case 0x25: // DEC H
            DEC_r8(cpu, &cpu->registers.h);
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
            set_flag_n(cpu, 0);
            set_flag_h(cpu, 0);
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
            LD_r8_mHL(cpu, &cpu->registers.c);
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
        case 0x8F: // ADC A,A
            ADC_A_u8(cpu, cpu->registers.a);
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
            cpu->registers.clk.m = 2;
            break;
        case 0xAF: // XOR A   slightly optimized
            cpu->registers.a = 0;
            set_flag_z(cpu, 1);
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
            cpu->registers.clk.m = 2;
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
            set_flag_z(cpu, 1);
            set_flag_n(cpu, 1);
            set_flag_h(cpu, 0);
            set_flag_c(cpu, 0);
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
            execute_cb_op(cpu, read_u8(cpu->mmu, cpu->registers.pc++));
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
            printf("non-existant GB opcode: D3\n");
            break;
        case 0xD4: // CALL NC,a16
            CALL_NC_a16(cpu);
            break;
        case 0xD5: // PUSH DE
            PUSH_DE(cpu);
            break;
        case 0xD6: // SUB d8
            SUB_u8(cpu, read_u8(cpu->mmu, cpu->registers.pc++));
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
            printf("non-existant GB opcode: DB\n");
            break;
        case 0xDC: // CALL C,a16
            CALL_C_a16(cpu);
            break;
        case 0xDD: // BLANK
            printf("non-existant GB opcode: DD\n");
            break;
        case 0xDE: // SBC A,d8
            SBC_A_u8(cpu, read_u8(cpu->mmu, cpu->registers.pc++));
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
            printf("non-existant GB opcode: %d\n", opcode);
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
            printf("non-existant GB opcode: %d\n", opcode);
            break;
        case 0xEE: // XOR d8
            XOR_u8(cpu, read_u8(cpu->mmu,cpu->registers.pc++));
            break;
        case 0xEF: // RST 28H
            RST_u8(cpu, 0x28);
            break;
        case 0xF0: // LDH A,(a8)
            LDH_A_a8(cpu);
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
            printf("non-existant GB opcode: F4\n");
            break;
        case 0xF5: // PUSH AF
            PUSH_AF(cpu);
            break;
        case 0xF6: // OR d8
            OR_u8(cpu, read_u8(cpu->mmu, cpu->registers.pc++));
            cpu->registers.clk.m = 2;
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
            printf("non-existant GB opcode: FC\n");
            break;
        case 0xFD:
            printf("non-existant GB opcode: FD\n");
            break;
        case 0xFE: // CP d8
            CP_u8(cpu, read_u8(cpu->mmu, cpu->registers.pc++));
            break;
        case 0xFF: // RST 38H
            RST_u8(cpu, 0x38);
            break;
    }
}

const char* op_string(u8 opcode) {
    switch(opcode) {
        case 0x00: return "NOP";
        case 0x01: return "LD BC,d16";
        case 0x02: return "LD (BC),A";
        case 0x03: return "INC BC";
        case 0x04: return "INC B";
        case 0x05: return "DEC B";
        case 0x06: return "LD B,d8";
        case 0x07: return "RLCA";
        case 0x08: return "LD (a16),SP";
        case 0x09: return "ADD HL BC";
        case 0x0A: return "LD A,(BC)";
        case 0x0B: return "DEC BC";
        case 0x0C: return "INC C";
        case 0x0D: return "DEC C";
        case 0x0E: return "LD C,d8";
        case 0x0F: return "RRCA";
        case 0x10: return "STOP 0";
        case 0x11: return "LD DE,d16";
        case 0x12: return "LD (DE),A";
        case 0x13: return "INC DE";
        case 0x14: return "INC D";
        case 0x15: return "DEC D";
        case 0x16: return "LD D,d8";
        case 0x17: return "RLA";
        case 0x18: return "JR r8";
        case 0x19: return "ADD HL DE";
        case 0x1A: return "LD A,(DE)";
        case 0x1B: return "DEC DE";
        case 0x1C: return "INC E";
        case 0x1D: return "DEC E";
        case 0x1E: return "LD E,d8";
        case 0x1F: return "RRA";
        case 0x20: return "JR NZ,r8";
        case 0x21: return "LD HL,d16";
        case 0x22: return "LD (HL+),A";
        case 0x23: return "INC HL";
        case 0x24: return "INC H";
        case 0x25: return "DEC H";
        case 0x26: return "LD H,d8";
        case 0x27: return "DAA";
        case 0x28: return "JR Z,r8";
        case 0x29: return "ADD HL,HL";
        case 0x2A: return "LD A,(HL+)";
        case 0x2B: return "DEC HL";
        case 0x2C: return "INC L";
        case 0x2D: return "DEC L";
        case 0x2E: return "LD L,d8";
        case 0x2F: return "CPL";
        case 0x30: return "JR NC,r8";
        case 0x31: return "LD SP,d16";
        case 0x32: return "LD (HL-),A";
        case 0x33: return "INC SP";
        case 0x34: return "INC (HL)";
        case 0x35: return "DEC (HL)";
        case 0x36: return "LD (HL),d8";
        case 0x37: return "SCF";
        case 0x38: return "JR C,r8";
        case 0x39: return "ADD HL SP";
        case 0x3A: return "LD A,(HL-)";
        case 0x3B: return "DEC SP";
        case 0x3C: return "INC A";
        case 0x3D: return "DEC A";
        case 0x3E: return "LD A,d8";
        case 0x3F: return "CCF";
        case 0x40: return "LD B,B";
        case 0x41: return "LD B,C";
        case 0x42: return "LD B,D";
        case 0x43: return "LD B,E";
        case 0x44: return "LD B,H";
        case 0x45: return "LD B,L";
        case 0x46: return "LD B,(HL)";
        case 0x47: return "LD B,A";
        case 0x48: return "LD C,B";
        case 0x49: return "LD C,C";
        case 0x4A: return "LD C,D";
        case 0x4B: return "LD C,E";
        case 0x4C: return "LD C,H";
        case 0x4D: return "LD C,L";
        case 0x4E: return "LD C,(HL)";
        case 0x4F: return "LD C,A";
        case 0x50: return "LD D,B";
        case 0x51: return "LD D,C";
        case 0x52: return "LD D,D";
        case 0x53: return "LD D,E";
        case 0x54: return "LD D,H";
        case 0x55: return "LD D,L";
        case 0x56: return "LD D,(HL)";
        case 0x57: return "LD D,A";
        case 0x58: return "LD E,B";
        case 0x59: return "LD E,C";
        case 0x5A: return "LD E,D";
        case 0x5B: return "LD E,E";
        case 0x5C: return "LD E,H";
        case 0x5D: return "LD E,L";
        case 0x5E: return "LD E,(HL)";
        case 0x5F: return "LD E,A";
        case 0x60: return "LD H,B";
        case 0x61: return "LD H,C";
        case 0x62: return "LD H,D";
        case 0x63: return "LD H,E";
        case 0x64: return "LD H,H";
        case 0x65: return "LD H,L";
        case 0x66: return "LD H, (HL)";
        case 0x67: return "LD H,A";
        case 0x68: return "LD L,B";
        case 0x69: return "LD L,C";
        case 0x6A: return "LD L,D";
        case 0x6B: return "LD L,E";
        case 0x6C: return "LD L,H";
        case 0x6D: return "LD L,L";
        case 0x6E: return "LD L,(HL)";
        case 0x6F: return "LD L,A";
        case 0x70: return "LD (HL),B";
        case 0x71: return "LD (HL),C";
        case 0x72: return "LD (HL),D";
        case 0x73: return "LD (HL),E";
        case 0x74: return "LD (HL),H";
        case 0x75: return "LD (HL),L";
        case 0x76: return "HALT";
        case 0x77: return "LD (HL),A";
        case 0x78: return "LD A,B";
        case 0x79: return "LD A,C";
        case 0x7A: return "LD A,D";
        case 0x7B: return "LD A,E";
        case 0x7C: return "LD A,H";
        case 0x7D: return "LD A,L";
        case 0x7E: return "LD A,(HL)";
        case 0x7F: return "LD A,A";
        case 0x80: return "ADD A,B";
        case 0x81: return "ADD A,C";
        case 0x82: return "ADD A,D";
        case 0x83: return "ADD A,E";
        case 0x84: return "ADD A,H";
        case 0x85: return "ADD A,L";
        case 0x86: return "ADD A,(HL)";
        case 0x87: return "ADD A,A";
        case 0x88: return "ADC A,B";
        case 0x89: return "ADC A,C";
        case 0x8A: return "ADC A,D";
        case 0x8B: return "ADC A,E";
        case 0x8C: return "ADC A,H";
        case 0x8D: return "ADC A,L";
        case 0x8E: return "ADC A,(HL)";
        case 0x8F: return "ADC A,A   optimized";
        case 0x90: return "SUB B";
        case 0x91: return "SUB C";
        case 0x92: return "SUB D";
        case 0x93: return "SUB E";
        case 0x94: return "SUB H";
        case 0x95: return "SUB L";
        case 0x96: return "SUB (HL)";
        case 0x97: return "SUB A";
        case 0x98: return "SBC A,B";
        case 0x99: return "SBC A,C";
        case 0x9A: return "SBC A,D";
        case 0x9B: return "SBC A,E";
        case 0x9C: return "SBC A,H";
        case 0x9D: return "SBC A,L";
        case 0x9E: return "SBC A,(HL)";
        case 0x9F: return "SBC A,A  slightly optimized";
        case 0xA0: return "AND B";
        case 0xA1: return "AND C";
        case 0xA2: return "AND D";
        case 0xA3: return "AND E";
        case 0xA4: return "AND H";
        case 0xA5: return "AND L";
        case 0xA6: return "AND (HL)";
        case 0xA7: return "AND A";
        case 0xA8: return "XOR B";
        case 0xA9: return "XOR C";
        case 0xAA: return "XOR D";
        case 0xAB: return "XOR E";
        case 0xAC: return "XOR H";
        case 0xAD: return "XOR L";
        case 0xAE: return "XOR (HL)";
        case 0xAF: return "XOR A   slightly optimized";
        case 0xB0: return "OR B";
        case 0xB1: return "OR C";
        case 0xB2: return "OR D";
        case 0xB3: return "OR E";
        case 0xB4: return "OR H";
        case 0xB5: return "OR L";
        case 0xB6: return "OR (HL)";
        case 0xB7: return "OR A";
        case 0xB8: return "CP B";
        case 0xB9: return "CP C";
        case 0xBA: return "CP D";
        case 0xBB: return "CP E";
        case 0xBC: return "CP H";
        case 0xBD: return "CP L";
        case 0xBE: return "CP (HL)";
        case 0xBF: return "CP A   slightly optimized";
        case 0xC0: return "RET NZ";
        case 0xC1: return "POP BC";
        case 0xC2: return "JP NZ,a16";
        case 0xC3: return "JP a16";
        case 0xC4: return "CALL NZ,a16";
        case 0xC5: return "PUSH BC";
        case 0xC6: return "ADD A,d8";
        case 0xC7: return "RST 00H";
        case 0xC8: return "RET Z";
        case 0xC9: return "RET";
        case 0xCA: return "JP Z,a16";
        case 0xCB: return "PREFIX CB";
        case 0xCC: return "CALL Z,a16";
        case 0xCD: return "CALL a16";
        case 0xCE: return "ADC A,d8";
        case 0xCF: return "RST 08H";
        case 0xD0: return "RET NC";
        case 0xD1: return "POP DE";
        case 0xD2: return "JP NC,a16";
        case 0xD3: return "XX";
        case 0xD4: return "CALL NC,a16";
        case 0xD5: return "PUSH DE";
        case 0xD6: return "SUB d8";
        case 0xD7: return "RST 10H";
        case 0xD8: return "RET C";
        case 0xD9: return "RET I";
        case 0xDA: return "JP C,a16";
        case 0xDB: return "BLANK";
        case 0xDC: return "CALL C,a16";
        case 0xDD: return "BLANK";
        case 0xDE: return "SBC A,d8";
        case 0xDF: return "RST 18H";
        case 0xE0: return "LDH (a8),A";
        case 0xE1: return "POP HL";
        case 0xE2: return "LD (C),A";
        case 0xE3: return "BLANK";
        case 0xE4: return "BLANK";
        case 0xE5: return "PUSH HL";
        case 0xE6: return "AND d8";
        case 0xE7: return "RST 20H";
        case 0xE8: return "ADD SP,r8";
        case 0xE9: return "JP (HL)";
        case 0xEA: return "LD (a16),A";
        case 0xEB: return "BLANK";
        case 0xEC: return "BLANK";
        case 0xED: return "BLANK";
        case 0xEE: return "XOR d8";
        case 0xEF: return "RST 28H";
        case 0xF0: return "LDH A,(a8)";
        case 0xF1: return "POP AF";
        case 0xF2: return "LD A,(C)";
        case 0xF3: return "DI";
        case 0xF4: return "BLANK";
        case 0xF5: return "PUSH AF";
        case 0xF6: return "OR d8";
        case 0xF7: return "RST 30H";
        case 0xF8: return "LD HL,SP+r8";
        case 0xF9: return "LD SP,HL";
        case 0xFA: return "LD A,(a16)";
        case 0xFB: return "EI";
        case 0xFC: return "BLANK";
        case 0xFD: return "BLANK";
        case 0xFE: return "CP d8";
        case 0xFF: return "RST 38H";
    }
    return "XX";
}

void execute_cb_op(gbc_cpu *cpu, u8 opcode) {
    /*printf("execute_cb_op(%x)\n", opcode);*/
    switch(opcode) {
        case 0x00: // RLC B
        case 0x01: // RLC C
        case 0x02: // RLC D
        case 0x03: // RLC E
        case 0x04: // RLC H
        case 0x05: // RLC L
        case 0x06: // RLC (HL)
        case 0x07: // RLC A
            RL_RLC(cpu, opcode);
            break;
        case 0x08: // RRC B
        case 0x09: // RRC C
        case 0x0A: // RRC D
        case 0x0B: // RRC E
        case 0x0C: // RRC H
        case 0x0D: // RRC L
        case 0x0E: // RRC (HL)
            RRC(cpu, opcode);
            break;
        case 0x0F: // RRC A
            RRC(cpu, opcode);
            break;
        case 0x10: // RL B
        case 0x11: // RL C
        case 0x12: // RL D
        case 0x13: // RL E
        case 0x14: // RL H
        case 0x15: // RL L
        case 0x16: // RL (HL)
        case 0x17: // RL A
            RL_RLC(cpu, opcode);
            break;
        case 0x18: // RR B
        case 0x19: // RR C
        case 0x1a: // RR D
        case 0x1b: // RR E
        case 0x1c: // RR H
        case 0x1d: // RR L
        case 0x1e: // RR (HL)
        case 0x1f: // RR A
            RR(cpu, opcode);
            break;
        case 0x20: // SLA B
        case 0x21: // SLA C
        case 0x22: // SLA D
        case 0x23: // SLA E
        case 0x24: // SLA H
        case 0x25: // SLA L
        case 0x26: // SLA (HL)
        case 0x27: // SLA A
            SLA(cpu, opcode);
            break;
        case 0x28: // SRA B
        case 0x29: // SRA C
        case 0x2a: // SRA D
        case 0x2b: // SRA E
        case 0x2c: // SRA H
        case 0x2d: // SRA L
        case 0x2e: // SRA (HL)
        case 0x2f: // SRA A
            SRA(cpu, opcode);
            break;
        case 0x30: // SWAP B
        case 0x31: // SWAP C
        case 0x32: // SWAP D
        case 0x33: // SWAP E
        case 0x34: // SWAP H
        case 0x35: // SWAP L
        case 0x36: // SWAP (HL)
        case 0x37: // SWAP A
            SWAP(cpu, opcode);
            break;
        case 0x38: // SRL B
        case 0x39: // SRL C
        case 0x3a: // SRL D
        case 0x3b: // SRL E
        case 0x3c: // SRL H
        case 0x3d: // SRL L
        case 0x3e: // SRL (HL)
        case 0x3f: // SRL A
            SRL(cpu, opcode);
            break;
        case 0x40: // BIT 0,B
        case 0x41: // BIT 0,C
        case 0x42: // BIT 0,D
        case 0x43: // BIT 0,E
        case 0x44: // BIT 0,H
        case 0x45: // BIT 0,L
        case 0x46: // BIT 0,(HL)
        case 0x47: // BIT 0,A
        case 0x48: // BIT 1,B
        case 0x49: // BIT 1,C
        case 0x4a: // BIT 1,D
        case 0x4b: // BIT 1,E
        case 0x4c: // BIT 1,H
        case 0x4d: // BIT 1,L
        case 0x4e: // BIT 1,(HL)
        case 0x4f: // BIT 1,A
            BIT_RES_SET(cpu, opcode);
            break;
        case 0x50: // BIT 2,B
        case 0x51: // BIT 2,C
        case 0x52: // BIT 2,D
        case 0x53: // BIT 2,E
        case 0x54: // BIT 2,H
        case 0x55: // BIT 2,L
        case 0x56: // BIT 2,(HL)
        case 0x57: // BIT 2,A
        case 0x58: // BIT 3,B
        case 0x59: // BIT 3,C
        case 0x5a: // BIT 3,D
        case 0x5b: // BIT 3,E
        case 0x5c: // BIT 3,H
        case 0x5d: // BIT 3,L
        case 0x5e: // BIT 3,(HL)
        case 0x5f: // BIT 3,A
            BIT_RES_SET(cpu, opcode);
            break;
        case 0x60: // BIT 4,B
        case 0x61: // BIT 4,C
        case 0x62: // BIT 4,D
        case 0x63: // BIT 4,E
        case 0x64: // BIT 4,H
        case 0x65: // BIT 4,L
        case 0x66: // BIT 4,(HL)
        case 0x67: // BIT 4,A
        case 0x68: // BIT 5,B
        case 0x69: // BIT 5,C
        case 0x6a: // BIT 5,D
        case 0x6b: // BIT 5,E
        case 0x6c: // BIT 5,H
        case 0x6d: // BIT 5,L
        case 0x6e: // BIT 5,(HL)
        case 0x6f: // BIT 5,A
            BIT_RES_SET(cpu, opcode);
            break;
        case 0x70: // BIT 6,B
        case 0x71: // BIT 6,C
        case 0x72: // BIT 6,D
        case 0x73: // BIT 6,E
        case 0x74: // BIT 6,H
        case 0x75: // BIT 6,L
        case 0x76: // BIT 6,(HL)
        case 0x77: // BIT 6,A
        case 0x78: // BIT 7,B
        case 0x79: // BIT 7,C
        case 0x7a: // BIT 7,D
        case 0x7b: // BIT 7,E
        case 0x7c: // BIT 7,H
        case 0x7d: // BIT 7,L
        case 0x7e: // BIT 7,(HL)
        case 0x7f: // BIT 7,A
            BIT_RES_SET(cpu, opcode);
            break;
        case 0x80: // RES 0,B
        case 0x81: // RES 0,C
        case 0x82: // RES 0,D
        case 0x83: // RES 0,E
        case 0x84: // RES 0,H
        case 0x85: // RES 0,L
        case 0x86: // RES 0,(HL)
        case 0x87: // RES 0,A
        case 0x88: // RES 1,B
        case 0x89: // RES 1,C
        case 0x8a: // RES 1,D
        case 0x8b: // RES 1,E
        case 0x8c: // RES 1,H
        case 0x8d: // RES 1,L
        case 0x8e: // RES 1,(HL)
        case 0x8f: // RES 1,A
            BIT_RES_SET(cpu, opcode);
            break;
        case 0x90: // RES 2,B
        case 0x91: // RES 2,C
        case 0x92: // RES 2,D
        case 0x93: // RES 2,E
        case 0x94: // RES 2,H
        case 0x95: // RES 2,L
        case 0x96: // RES 2,(HL)
        case 0x97: // RES 2,A
        case 0x98: // RES 3,B
        case 0x99: // RES 3,C
        case 0x9a: // RES 3,D
        case 0x9b: // RES 3,E
        case 0x9c: // RES 3,H
        case 0x9d: // RES 3,L
        case 0x9e: // RES 3,(HL)
        case 0x9f: // RES 3,A
            BIT_RES_SET(cpu, opcode);
            break;
        case 0xa0: // RES 4,B
        case 0xa1: // RES 4,C
        case 0xa2: // RES 4,D
        case 0xa3: // RES 4,E
        case 0xa4: // RES 4,H
        case 0xa5: // RES 4,L
        case 0xa6: // RES 4,(HL)
        case 0xa7: // RES 4,A
        case 0xa8: // RES 5,B
        case 0xa9: // RES 5,C
        case 0xaa: // RES 5,D
        case 0xab: // RES 5,E
        case 0xac: // RES 5,H
        case 0xad: // RES 5,L
        case 0xae: // RES 5,(HL)
        case 0xaf: // RES 5,A
            BIT_RES_SET(cpu, opcode);
            break;
        case 0xb0: // RES 6,B
        case 0xb1: // RES 6,C
        case 0xb2: // RES 6,D
        case 0xb3: // RES 6,E
        case 0xb4: // RES 6,H
        case 0xb5: // RES 6,L
        case 0xb6: // RES 6,(HL)
        case 0xb7: // RES 6,A
        case 0xb8: // RES 7,B
        case 0xb9: // RES 7,C
        case 0xba: // RES 7,D
        case 0xbb: // RES 7,E
        case 0xbc: // RES 7,H
        case 0xbd: // RES 7,L
        case 0xbe: // RES 7,(HL)
        case 0xbf: // RES 7,A
            BIT_RES_SET(cpu, opcode);
            break;
        case 0xc0: // SET 0,B
        case 0xc1: // SET 0,C
        case 0xc2: // SET 0,D
        case 0xc3: // SET 0,E
        case 0xc4: // SET 0,H
        case 0xc5: // SET 0,L
        case 0xc6: // SET 0,(HL)
        case 0xc7: // SET 0,A
        case 0xc8: // SET 1,B
        case 0xc9: // SET 1,C
        case 0xca: // SET 1,D
        case 0xcb: // SET 1,E
        case 0xcc: // SET 1,H
        case 0xcd: // SET 1,L
        case 0xce: // SET 1,(HL)
        case 0xcf: // SET 1,A
            BIT_RES_SET(cpu, opcode);
            break;
        case 0xd0: // SET 2,B
        case 0xd1: // SET 2,C
        case 0xd2: // SET 2,D
        case 0xd3: // SET 2,E
        case 0xd4: // SET 2,H
        case 0xd5: // SET 2,L
        case 0xd6: // SET 2,(HL)
        case 0xd7: // SET 2,A
        case 0xd8: // SET 3,B
        case 0xd9: // SET 3,C
        case 0xda: // SET 3,D
        case 0xdb: // SET 3,E
        case 0xdc: // SET 3,H
        case 0xdd: // SET 3,L
        case 0xde: // SET 3,(HL)
        case 0xdf: // SET 3,A
            BIT_RES_SET(cpu, opcode);
            break;
        case 0xe0: // SET 4,B
        case 0xe1: // SET 4,C
        case 0xe2: // SET 4,D
        case 0xe3: // SET 4,E
        case 0xe4: // SET 4,H
        case 0xe5: // SET 4,L
        case 0xe6: // SET 4,(HL)
        case 0xe7: // SET 4,A
        case 0xe8: // SET 5,B
        case 0xe9: // SET 5,C
        case 0xea: // SET 5,D
        case 0xeb: // SET 5,E
        case 0xec: // SET 5,H
        case 0xed: // SET 5,L
        case 0xee: // SET 5,(HL)
        case 0xef: // SET 5,A
            BIT_RES_SET(cpu, opcode);
            break;
        case 0xf0: // SET 6,B
        case 0xf1: // SET 6,C
        case 0xf2: // SET 6,D
        case 0xf3: // SET 6,E
        case 0xf4: // SET 6,H
        case 0xf5: // SET 6,L
        case 0xf6: // SET 6,(HL)
        case 0xf7: // SET 6,A
        case 0xf8: // SET 7,B
        case 0xf9: // SET 7,C
        case 0xfa: // SET 7,D
        case 0xfb: // SET 7,E
        case 0xfc: // SET 7,H
        case 0xfd: // SET 7,L
        case 0xfe: // SET 7,(HL)
        case 0xff: // SET 7,A
            BIT_RES_SET(cpu, opcode);
            break;
    }
}

u8* prefix_cb_target(gbc_cpu *cpu, u8 opcode) {
    switch(opcode & 0xF) {
        case 0x0: return &cpu->registers.b;
        case 0x1: return &cpu->registers.c;
        case 0x2: return &cpu->registers.d;
        case 0x3: return &cpu->registers.e;
        case 0x4: return &cpu->registers.h;
        case 0x5: return &cpu->registers.l;
                  // case 0x6: HL
        case 0x7: return &cpu->registers.a;
        case 0x8: return &cpu->registers.b;
        case 0x9: return &cpu->registers.c;
        case 0xA: return &cpu->registers.d;
        case 0xB: return &cpu->registers.e;
        case 0xC: return &cpu->registers.h;
        case 0xD: return &cpu->registers.l;
                  // case 0xE: HL
        case 0xF: return &cpu->registers.a;
    }
    return &cpu->mmu->zram[0];
}

// swap upper 4 bits in register r8 and the lower ones.
void SWAP(gbc_cpu *cpu, u8 opcode) {
    bool mHL = ((opcode & 0xF) == 0x6 || (opcode & 0xF) == 0xE);
    if (mHL) {
        u8 v = read_u8(cpu->mmu, get_hl(cpu));
        v = ((v & 0xF) << 4) | ((v & 0xF0) >> 4);
        write_u8(cpu->mmu, get_hl(cpu), v);
        set_flag_z(cpu, v == 0x00);
    } else {
        u8 *r8 = prefix_cb_target(cpu, opcode);
        *r8 = ((*r8 & 0xF) << 4) | ((*r8 & 0xF0) >> 4);
        set_flag_z(cpu, *r8 == 0x00);
    }
    set_flag_n(cpu, 0);
    set_flag_h(cpu, 0);
    set_flag_c(cpu, 0);
    cpu->registers.clk.m = 2;
}

void SLA(gbc_cpu *cpu, u8 opcode) {
    bool mHL = ((opcode & 0xF) == 0x6 || (opcode & 0xF) == 0xE);
    u8 b7;

    if (mHL) {
        u8 v = read_u8(cpu->mmu, get_hl(cpu));
	    b7 = (v & 0x80) >> 7;
	    v = v << 1;
	    set_flag_z(cpu, v == 0x00);
        write_u8(cpu->mmu, get_hl(cpu), v);
    } else {
        u8 *r8 = prefix_cb_target(cpu, opcode);
	    b7 = (*r8 & 0x80) >> 7;
	    *r8 = *r8 << 1;
	    set_flag_z(cpu, *r8 == 0x00);
    }
	set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
	set_flag_c(cpu, b7);
}

void SRA(gbc_cpu* cpu, u8 opcode) {
    bool mHL = ((opcode & 0xF) == 0x6 || (opcode & 0xF) == 0xE);

    u8 b0;

    if (mHL) {
        u8 v = read_u8(cpu->mmu, get_hl(cpu));
	    b0 = v & 0x01;
	    u8 b7 = (v & 0x80) >> 7;
	    v = v >> 1;
	    v += b7 << 7;
	    write_u8(cpu->mmu, get_hl(cpu), v);
	    set_flag_z(cpu, (v == 0x00));
    } else {
        u8 *r8 = prefix_cb_target(cpu, opcode);
	    b0 = *r8 & 0x01;
	    u8 b7 = (*r8 & 0x80) >> 7;
	    *r8 = *r8 >> 1;
	    *r8 += b7 << 7;
	    set_flag_z(cpu, (*r8 == 0x00));
    }

	set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
	set_flag_c(cpu, b0);
    cpu->registers.clk.m = 2;
}

void SRL(gbc_cpu *cpu, u8 opcode) {
    bool mHL = ((opcode & 0xF) == 0x6 || (opcode & 0xF) == 0xE);

    if (mHL) {
        u8 v = read_u8(cpu->mmu, get_hl(cpu));
	    u8 b0 = v & 0x01;
	    v = v >> 1;
	    set_flag_z(cpu, (v == 0x00));
	    set_flag_c(cpu, b0);
	    write_u8(cpu->mmu, get_hl(cpu), v);
    } else {
        u8 *r8 = prefix_cb_target(cpu, opcode);
	    u8 b0 = *r8 & 0x01;
	    *r8 = *r8 >> 1;
	    set_flag_z(cpu, (*r8 == 0x00));
	    set_flag_c(cpu, b0);
    }
	set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
    cpu->registers.clk.m = 2;
}

void RL_RLC(gbc_cpu *cpu, u8 opcode) {
    bool mHL = ((opcode & 0xF) == 0x6 || (opcode & 0xF) == 0xE);

    if (mHL) {
        u8 val = read_u8(cpu->mmu, get_hl(cpu));
        u8 temp = val;
	    val = (val << 1);
        opcode = (opcode >> 4) & 0x3;
	    val |= opcode ? flag_c(cpu) : (temp >> 7);
	    set_flag_z(cpu, (val == 0));
        set_flag_c(cpu, temp >> 7);
        write_u8(cpu->mmu, get_hl(cpu), val);
    } else {
        u8 *r8 = prefix_cb_target(cpu, opcode);
        u8 val = *r8;
        u8 temp = val;
	    val = (val << 1);
        opcode = (opcode >> 4) & 0x3;
	    val |= opcode ? flag_c(cpu) : (temp >> 7);
	    set_flag_z(cpu, (val == 0));
        set_flag_c(cpu, temp >> 7);
        *r8 = val;
    }

	set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);


    cpu->registers.clk.m = 2;
}

void RR(gbc_cpu *cpu, u8 opcode) {
    bool mHL = ((opcode & 0xF) == 0x6 || (opcode & 0xF) == 0xE);
    u8 temp;

    if (mHL) {
        u8 val = read_u8(cpu->mmu, get_hl(cpu));
	    temp = val;
	    val = temp >> 1 | (flag_c(cpu) << 7);
	    set_flag_z(cpu, val == 0x00);
        write_u8(cpu->mmu, get_hl(cpu), val);
    } else {
        u8 *r8 = prefix_cb_target(cpu, opcode);
	    temp = *r8;
	    *r8 = temp >> 1 | (flag_c(cpu) << 7);
	    set_flag_z(cpu, *r8 == 0x00);
	}
	set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
	set_flag_c(cpu, temp & 0x1);
    cpu->registers.clk.m = 2;
}

void RRC(gbc_cpu *cpu, u8 opcode) {
    bool mHL = ((opcode & 0xF) == 0x6 || (opcode & 0xF) == 0xE);
    if (mHL) {
        u8 v = read_u8(cpu->mmu, get_hl(cpu));
	    set_flag_c(cpu, v & 0x01);
	    v = (v >> 1) | (v << 7);
	    set_flag_z(cpu, v == 0x00);
	    write_u8(cpu->mmu, get_hl(cpu), v);
    } else {
        u8 *r8 = prefix_cb_target(cpu, opcode);
	    set_flag_c(cpu, *r8 & 0x01);
	    *r8 = (*r8 >> 1) | (*r8 << 7);
	    set_flag_z(cpu, *r8 == 0x00);
	}

	set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
    cpu->registers.clk.m = 2;
}

void RLA(gbc_cpu *cpu) {
    u8 temp = cpu->registers.a;
	cpu->registers.a = (cpu->registers.a << 1) | flag_c(cpu);
	set_flag_z(cpu, 0);
	set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
	set_flag_c(cpu, (temp >> 7) & 0x01);
    cpu->registers.clk.m = 1;
}
void RLCA(gbc_cpu *cpu) {
	cpu->registers.a = (cpu->registers.a << 1) | (cpu->registers.a >> 7);
	set_flag_z(cpu, 0);
	set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
	set_flag_c(cpu, cpu->registers.a & 0x01);
    cpu->registers.clk.m = 1;
}
void RRA(gbc_cpu *cpu) {
	u8 temp = cpu->registers.a;
	cpu->registers.a = cpu->registers.a >> 1 | (flag_c(cpu) << 7);
	set_flag_z(cpu, 0);
	set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
	set_flag_c(cpu, temp & 0x1);
    cpu->registers.clk.m = 1;
}
void RRCA(gbc_cpu *cpu) {
	set_flag_c(cpu, cpu->registers.a & 0x01);
	cpu->registers.a = (cpu->registers.a >> 1) | (cpu->registers.a << 7);
	set_flag_z(cpu, 0);
	set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
    cpu->registers.clk.m = 1;
}

void BIT_RES_SET(gbc_cpu *cpu, u8 opcode) {
    u8 *r8 = prefix_cb_target(cpu, opcode);
    u8 bit = 1 << ((opcode >> 3) & 7);
    bool mHL = ((opcode & 0xF) == 0x6 || (opcode & 0xF) == 0xE);
    if ((opcode & 0xC0) == 0x40) { // BIT
        if (mHL) set_flag_z(cpu, ((bit & read_u8(cpu->mmu, get_hl(cpu))) == 0x00));
        else set_flag_z(cpu, ((bit & *r8) == 0x00));

        set_flag_n(cpu, 0);
        set_flag_h(cpu, 1);
    }
    else if ((opcode & 0xC0) == 0x80) { // RES
        if (mHL) write_u8(cpu->mmu, get_hl(cpu), read_u8(cpu->mmu, get_hl(cpu)) & ~bit); // sets the selected bit to 0
        else *r8 = (*r8 & ~bit); // sets the selected bit to 0
    }
    else if ((opcode & 0xC0) == 0xC0) { // SET
        if (mHL) write_u8(cpu->mmu, get_hl(cpu), read_u8(cpu->mmu, get_hl(cpu)) | bit); // sets the selected bit to 0
        else *r8 = (*r8 | bit); // sets the selected bit to 1
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
    *r = read_u8(cpu->mmu, get_hl(cpu));
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

void LD_A_mBC(gbc_cpu *cpu) {
    cpu->registers.a = read_u8(cpu->mmu, get_bc(cpu));
    cpu->registers.clk.m = 2;
}
void LD_A_mDE(gbc_cpu *cpu) {
    cpu->registers.a = read_u8(cpu->mmu,get_de(cpu));
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
    s8 offset = read_u8(cpu->mmu, cpu->registers.pc++);
    set_hl(cpu, cpu->registers.sp + offset);
    set_flag_z(cpu, 0);
    set_flag_n(cpu, 0);
    set_flag_h(cpu, ((cpu->registers.sp & 0xF) + (offset & 0xF) > 0xF));
    set_flag_c(cpu, ((cpu->registers.sp & 0xFF) + (offset & 0xFF) > 0xFF));
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
    u16 a = cpu->registers.a;

	if (flag_n(cpu)) {
		if(flag_h(cpu)) a = (a - 0x06) & 0xFF;
		if(flag_c(cpu)) a -= 0x60;
	} else {
		if(flag_h(cpu) || (a & 0x0F) > 9) a += 0x06;
		if(flag_c(cpu) || a > 0x9F) a += 0x60;
	}

	if((a & 0x100) == 0x100) set_flag_c(cpu, 1);
	cpu->registers.a = a;
	set_flag_z(cpu, cpu->registers.a == 0);
	set_flag_h(cpu, 0);
    cpu->registers.clk.m = 1;
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
    u8 temp = read_u8(cpu->mmu, get_hl(cpu))+1;
	set_flag_z(cpu, temp == 0x00);
	set_flag_n(cpu, 0);
	set_flag_h(cpu, (temp & 0x0F) == 0x00);
    write_u8(cpu->mmu, get_hl(cpu), temp);
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
    u8 temp = read_u8(cpu->mmu, get_hl(cpu))-1;
	set_flag_z(cpu, temp == 0x00);
	set_flag_n(cpu, 1);
	set_flag_h(cpu, (temp & 0x0F) == 0x0F);
    write_u8(cpu->mmu, get_hl(cpu), temp);
}

void DEC_BC(gbc_cpu *cpu) {
    cpu->registers.c=(cpu->registers.c-1)&255;
    if(cpu->registers.c==255) cpu->registers.b=(cpu->registers.b-1)&255;
    cpu->registers.clk.m = 2;
}
void DEC_DE(gbc_cpu *cpu) {
    cpu->registers.e=(cpu->registers.e-1)&255;
    if(cpu->registers.e==255) cpu->registers.d=(cpu->registers.d-1)&255;
    cpu->registers.clk.m = 2;
}
void DEC_HL(gbc_cpu *cpu) {
    cpu->registers.l=(cpu->registers.l-1)&255;
    if(cpu->registers.l==255) cpu->registers.h=(cpu->registers.h-1)&255;
    cpu->registers.clk.m = 2;
}
void DEC_SP(gbc_cpu *cpu) {
    cpu->registers.sp=(cpu->registers.sp-1)&65535;
    cpu->registers.clk.m = 2;
}

void CPL(gbc_cpu *cpu) {
    cpu->registers.a = ~cpu->registers.a;
	set_flag_n(cpu, 1);
	set_flag_h(cpu, 1);
    cpu->registers.clk.m = 1;
}
void NEG(gbc_cpu *cpu) {
    cpu->registers.a = 0-cpu->registers.a;
    cpu->registers.f=(cpu->registers.a<0)?FLAG_C:0;
    if(!cpu->registers.a) cpu->registers.f|=FLAG_Z;
    cpu->registers.clk.m = 2;
}

void CCF(gbc_cpu *cpu) {
	set_flag_n(cpu, 0);
	set_flag_h(cpu, 0);
	set_flag_c(cpu, !flag_c(cpu));
    cpu->registers.clk.m = 1;
}

void PUSH_BC(gbc_cpu *cpu) {
    write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.b);
    write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.c);
    cpu->registers.clk.m = 3;
}
void PUSH_DE(gbc_cpu *cpu) {
    write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.d);
    write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.e);
    cpu->registers.clk.m = 3;
}
void PUSH_HL(gbc_cpu *cpu) {
    write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.h);
    write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.l);
    cpu->registers.clk.m = 3;
}
void PUSH_AF(gbc_cpu *cpu) {
    write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.a);
    write_u8(cpu->mmu, --cpu->registers.sp,
			flag_z(cpu) << 7 | flag_n(cpu)<< 6 |
			flag_h(cpu)<< 5 | flag_c(cpu)<< 4);
    cpu->registers.clk.m = 3;
}

void POP_BC(gbc_cpu *cpu) {
    cpu->registers.c = read_u8(cpu->mmu, cpu->registers.sp++);
    cpu->registers.b = read_u8(cpu->mmu, cpu->registers.sp++);
    cpu->registers.clk.m = 3;
}
void POP_DE(gbc_cpu *cpu) {
    cpu->registers.e = read_u8(cpu->mmu, cpu->registers.sp++);
    cpu->registers.d = read_u8(cpu->mmu, cpu->registers.sp++);
    cpu->registers.clk.m = 3;
}
void POP_HL(gbc_cpu *cpu) {
    cpu->registers.l = read_u8(cpu->mmu, cpu->registers.sp++);
    cpu->registers.h = read_u8(cpu->mmu, cpu->registers.sp++);
    cpu->registers.clk.m = 3;
}
void POP_AF(gbc_cpu *cpu) {
    u8 temp_8 = read_u8(cpu->mmu, cpu->registers.sp++);
	set_flag_z(cpu, (temp_8 >> 7) & 1);
	set_flag_n(cpu, (temp_8 >> 6) & 1);
	set_flag_h(cpu, (temp_8 >> 5) & 1);
	set_flag_c(cpu, (temp_8 >> 4) & 1);
    cpu->registers.a = read_u8(cpu->mmu, cpu->registers.sp++);
    cpu->registers.clk.m = 3;
}
void JR_r8(gbc_cpu *cpu) {
    s8 i = read_u8(cpu->mmu,cpu->registers.pc++);
    cpu->registers.pc += i;
    cpu->registers.clk.m = 4;
}
void JR_NZ_r8(gbc_cpu *cpu) {
    if (!flag_z(cpu)) JR_r8(cpu);
    else cpu->registers.pc++;
}
void JR_Z_r8(gbc_cpu *cpu)  {
    if (flag_z(cpu)) JR_r8(cpu);
    else cpu->registers.pc++;
}
void JR_NC_r8(gbc_cpu *cpu) {
    if (!flag_c(cpu)) JR_r8(cpu);
    else cpu->registers.pc++;
}

void JR_C_r8(gbc_cpu *cpu)  {
    if (flag_c(cpu)) JR_r8(cpu);
    else cpu->registers.pc++;
}

void CALL_a16(gbc_cpu *cpu) {
    u16 addr = read_u8(cpu->mmu, cpu->registers.pc++);
    addr |= read_u8(cpu->mmu, cpu->registers.pc++) << 8;
    write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc >> 8);
    write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc & 0xFF);
    cpu->registers.pc = addr;
    cpu->registers.clk.m = 12;
}

void CALL_NZ_a16(gbc_cpu *cpu) {
    if (!flag_z(cpu)) CALL_a16(cpu);
     else cpu->registers.pc += 2;
}

void CALL_Z_a16(gbc_cpu *cpu) {
    if (flag_z(cpu)) CALL_a16(cpu);
    else cpu->registers.pc += 2;
}

void CALL_NC_a16(gbc_cpu *cpu) {
    if (!flag_c(cpu)) CALL_a16(cpu);
    else cpu->registers.pc += 2;
}

void CALL_C_a16(gbc_cpu *cpu) {
    if (flag_c(cpu)) CALL_a16(cpu);
    else cpu->registers.pc += 2;
}

void RET(gbc_cpu *cpu) {
    u16 temp = read_u8(cpu->mmu, cpu->registers.sp++);
    temp |= read_u8(cpu->mmu, cpu->registers.sp++) << 8;

    cpu->registers.pc = temp;
    cpu->registers.clk.m = 3;
}

void RET_I(gbc_cpu *cpu) {
    u16 temp = read_u8(cpu->mmu, cpu->registers.sp++);
    temp |= read_u8(cpu->mmu, cpu->registers.sp++) << 8;
    cpu->registers.pc = temp;
    cpu->IME = 1;
    cpu->registers.clk.m = 3;
}
void RET_NZ(gbc_cpu *cpu) {
    cpu->registers.clk.m = 1;
    if (!flag_z(cpu)) RET(cpu);
}
void RET_Z(gbc_cpu *cpu) {
    cpu->registers.clk.m = 1;
    if (flag_z(cpu)) RET(cpu);
}
void RET_NC(gbc_cpu *cpu) {
    cpu->registers.clk.m = 1;
    if (!flag_c(cpu)) RET(cpu);
}
void RET_C(gbc_cpu *cpu) {
    cpu->registers.clk.m = 1;
    if (flag_c(cpu)) RET(cpu);
}
void JP_a16(gbc_cpu *cpu) {
    cpu->registers.pc = read_u16(cpu->mmu ,cpu->registers.pc);
    cpu->registers.clk.m = 3;
}
void JP_mHL(gbc_cpu *cpu) {
    cpu->registers.pc = get_hl(cpu);
    cpu->registers.clk.m = 1;
}
void JP_C_a16(gbc_cpu *cpu) {
    cpu->registers.clk.m = 3;
    if(flag_c(cpu)) JP_a16(cpu);
    else cpu->registers.pc += 2;
}
void JP_Z_a16(gbc_cpu *cpu) {
    cpu->registers.clk.m = 3;
    if(flag_z(cpu)) JP_a16(cpu);
    else cpu->registers.pc += 2;
}
void JP_NZ_a16(gbc_cpu *cpu) {
    cpu->registers.clk.m = 3;
    if (!flag_z(cpu)) JP_a16(cpu);
    else cpu->registers.pc += 2;
}
void JP_NC_a16(gbc_cpu *cpu) {
    if(!flag_c(cpu)) JP_a16(cpu);
    else cpu->registers.pc += 2;
}

void RST_u8(gbc_cpu *cpu, u8 v) {
    write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc >> 8);
    write_u8(cpu->mmu, --cpu->registers.sp, cpu->registers.pc & 0xFF);
    cpu->registers.pc = v;
    cpu->registers.clk.m = 3;
}

void NOP(gbc_cpu *cpu) {
    cpu->registers.clk.m = 1;
}

void HALT(gbc_cpu *cpu) {
    cpu->HALT = 1;
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

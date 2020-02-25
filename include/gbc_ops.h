#pragma once

#include "gbc_cpu.h"

typedef void (*gbc_operator)(gbc_cpu *cpu);

void execute_init(gbc_cpu *cpu);

/*
 * d8  means immediate 8 bit data
 * d16 means immediate 16 bit data
 * a8  means 8 bit unsigned data, which are added to $FF00 in certain instructions (replacement for missing IN and OUT instructions)
 * a16 means 16 bit address
 * r8  means 8 bit signed data, which are added to program counter
 * https://www.pastraiser.com/cpu/gameboy/gameboy_opcodes.html
 */

void LD_A_d8(gbc_cpu *cpu);
void LD_B_d8(gbc_cpu *cpu);
void LD_C_d8(gbc_cpu *cpu);
void LD_D_d8(gbc_cpu *cpu);
void LD_E_d8(gbc_cpu *cpu);
void LD_H_d8(gbc_cpu *cpu);
void LD_L_d8(gbc_cpu *cpu);

void LD_A_A(gbc_cpu *cpu);
void LD_A_B(gbc_cpu *cpu);
void LD_A_C(gbc_cpu *cpu);
void LD_A_D(gbc_cpu *cpu);
void LD_A_E(gbc_cpu *cpu);
void LD_A_H(gbc_cpu *cpu);
void LD_A_L(gbc_cpu *cpu);

void LD_B_A(gbc_cpu *cpu);
void LD_B_B(gbc_cpu *cpu);
void LD_B_C(gbc_cpu *cpu);
void LD_B_D(gbc_cpu *cpu);
void LD_B_E(gbc_cpu *cpu);
void LD_B_H(gbc_cpu *cpu);
void LD_B_L(gbc_cpu *cpu);

void LD_C_A(gbc_cpu *cpu);
void LD_C_B(gbc_cpu *cpu);
void LD_C_C(gbc_cpu *cpu);
void LD_C_D(gbc_cpu *cpu);
void LD_C_E(gbc_cpu *cpu);
void LD_C_H(gbc_cpu *cpu);
void LD_C_L(gbc_cpu *cpu);

void LD_D_A(gbc_cpu *cpu);
void LD_D_B(gbc_cpu *cpu);
void LD_D_C(gbc_cpu *cpu);
void LD_D_D(gbc_cpu *cpu);
void LD_D_E(gbc_cpu *cpu);
void LD_D_H(gbc_cpu *cpu);
void LD_D_L(gbc_cpu *cpu);

void LD_E_A(gbc_cpu *cpu);
void LD_E_B(gbc_cpu *cpu);
void LD_E_C(gbc_cpu *cpu);
void LD_E_D(gbc_cpu *cpu);
void LD_E_E(gbc_cpu *cpu);
void LD_E_H(gbc_cpu *cpu);
void LD_E_L(gbc_cpu *cpu);

void LD_H_A(gbc_cpu *cpu);
void LD_H_B(gbc_cpu *cpu);
void LD_H_C(gbc_cpu *cpu);
void LD_H_D(gbc_cpu *cpu);
void LD_H_E(gbc_cpu *cpu);
void LD_H_H(gbc_cpu *cpu);
void LD_H_L(gbc_cpu *cpu);

void LD_L_A(gbc_cpu *cpu);
void LD_L_B(gbc_cpu *cpu);
void LD_L_C(gbc_cpu *cpu);
void LD_L_D(gbc_cpu *cpu);
void LD_L_E(gbc_cpu *cpu);
void LD_L_H(gbc_cpu *cpu);
void LD_L_L(gbc_cpu *cpu);

void LD_A_mHL(gbc_cpu *cpu);
void LD_B_mHL(gbc_cpu *cpu);
void LD_C_mHL(gbc_cpu *cpu);
void LD_D_mHL(gbc_cpu *cpu);
void LD_E_mHL(gbc_cpu *cpu);
void LD_H_mHL(gbc_cpu *cpu);
void LD_L_mHL(gbc_cpu *cpu);

void LD_mHL_A(gbc_cpu *cpu);
void LD_mHL_B(gbc_cpu *cpu);
void LD_mHL_C(gbc_cpu *cpu);
void LD_mHL_D(gbc_cpu *cpu);
void LD_mHL_E(gbc_cpu *cpu);
void LD_mHL_H(gbc_cpu *cpu);
void LD_mHL_L(gbc_cpu *cpu);

void LD_HL_d8(gbc_cpu *cpu);

void LD_mBC_A(gbc_cpu *cpu);
void LD_mDE_A(gbc_cpu *cpu);

void LD_d16_A(gbc_cpu *cpu);
void D_A_d16(gbc_cpu *cpu);

void LD_A_mBC(gbc_cpu *cpu);
void LD_A_mDE(gbc_cpu *cpu);

void LD_A_a16(gbc_cpu* cpu);
void LD_a16_A(gbc_cpu* cpu);
void LD_a16_SP(gbc_cpu* cpu);

void LD_BC_d16(gbc_cpu *cpu);
void LD_DE_d16(gbc_cpu *cpu);
void LD_HL_d16(gbc_cpu *cpu);
void LD_SP_d16(gbc_cpu *cpu);

void LD_mHLI_A(gbc_cpu* cpu);
void LD_A_mHLI(gbc_cpu* cpu);

void LD_mHLD_A(gbc_cpu* cpu);
void LD_A_mHLD(gbc_cpu* cpu);

void LD_A_mC(gbc_cpu* cpu);
void LD_mC_A(gbc_cpu* cpu);

void LDH_a8_A(gbc_cpu* cpu);
void LDH_A_a8(gbc_cpu* cpu);
void LD_HL_SP_r8(gbc_cpu* cpu);

void SWAP_A(gbc_cpu* cpu);
void SWAP_B(gbc_cpu* cpu);
void SWAP_C(gbc_cpu* cpu);
void SWAP_D(gbc_cpu* cpu);
void SWAP_E(gbc_cpu* cpu);
void SWAP_H(gbc_cpu* cpu);
void SWAP_L(gbc_cpu* cpu);

void ADD_A(gbc_cpu* cpu);
void ADD_B(gbc_cpu* cpu);
void ADD_C(gbc_cpu* cpu);
void ADD_D(gbc_cpu* cpu);
void ADD_E(gbc_cpu* cpu);
void ADD_H(gbc_cpu* cpu);
void ADD_L(gbc_cpu* cpu);
void ADD_mHL(gbc_cpu* cpu);
void ADD_d8(gbc_cpu* cpu);

void ADD_HL_BC(gbc_cpu* cpu);
void ADD_HL_DE(gbc_cpu* cpu);
void ADD_HL_HL(gbc_cpu* cpu);
void ADD_HL_SP(gbc_cpu* cpu);
void ADD_SP_d8(gbc_cpu* cpu);

void ADC_A(gbc_cpu* cpu);
void ADC_B(gbc_cpu* cpu);
void ADC_C(gbc_cpu* cpu);
void ADC_D(gbc_cpu* cpu);
void ADC_E(gbc_cpu* cpu);
void ADC_H(gbc_cpu* cpu);
void ADC_L(gbc_cpu* cpu);
void ADC_mHL(gbc_cpu* cpu);
void ADC_d8(gbc_cpu* cpu);

void SUB_A(gbc_cpu* cpu);
void SUB_B(gbc_cpu* cpu);
void SUB_C(gbc_cpu* cpu);
void SUB_D(gbc_cpu* cpu);
void SUB_E(gbc_cpu* cpu);
void SUB_H(gbc_cpu* cpu);
void SUB_L(gbc_cpu* cpu);
void SUB_mHL(gbc_cpu* cpu);
void SUB_d8(gbc_cpu* cpu);

void SBC_A(gbc_cpu* cpu);
void SBC_B(gbc_cpu* cpu);
void SBC_C(gbc_cpu* cpu);
void SBC_D(gbc_cpu* cpu);
void SBC_E(gbc_cpu* cpu);
void SBC_H(gbc_cpu* cpu);
void SBC_L(gbc_cpu* cpu);
void SBC_mHL(gbc_cpu* cpu);
void SBC_d8(gbc_cpu* cpu);

void CP_A(gbc_cpu* cpu);
void CP_B(gbc_cpu* cpu);
void CP_C(gbc_cpu* cpu);
void CP_D(gbc_cpu* cpu);
void CP_E(gbc_cpu* cpu);
void CP_H(gbc_cpu* cpu);
void CP_L(gbc_cpu* cpu);
void CP_mHL(gbc_cpu* cpu);
void CP_d8(gbc_cpu* cpu);

void DAA(gbc_cpu* cpu);

void AND_A(gbc_cpu* cpu);
void AND_B(gbc_cpu* cpu);
void AND_C(gbc_cpu* cpu);
void AND_D(gbc_cpu* cpu);
void AND_E(gbc_cpu* cpu);
void AND_H(gbc_cpu* cpu);
void AND_L(gbc_cpu* cpu);
void AND_mHL(gbc_cpu* cpu);
void AND_d8(gbc_cpu* cpu);

void OR_A(gbc_cpu* cpu);
void OR_B(gbc_cpu* cpu);
void OR_C(gbc_cpu* cpu);
void OR_D(gbc_cpu* cpu);
void OR_E(gbc_cpu* cpu);
void OR_H(gbc_cpu* cpu);
void OR_L(gbc_cpu* cpu);
void OR_mHL(gbc_cpu* cpu);
void OR_d8(gbc_cpu* cpu);

void XOR_A(gbc_cpu* cpu);
void XOR_B(gbc_cpu* cpu);
void XOR_C(gbc_cpu* cpu);
void XOR_D(gbc_cpu* cpu);
void XOR_E(gbc_cpu* cpu);
void XOR_H(gbc_cpu* cpu);
void XOR_L(gbc_cpu* cpu);
void XOR_mHL(gbc_cpu* cpu);
void XOR_d8(gbc_cpu* cpu);

void INC_A(gbc_cpu* cpu);
void INC_B(gbc_cpu* cpu);
void INC_C(gbc_cpu* cpu);
void INC_D(gbc_cpu* cpu);
void INC_E(gbc_cpu* cpu);
void INC_H(gbc_cpu* cpu);
void INC_L(gbc_cpu* cpu);
void INC_mHL(gbc_cpu* cpu);
void INC_BC(gbc_cpu* cpu);
void INC_DE(gbc_cpu* cpu);
void INC_HL(gbc_cpu* cpu);
void INC_SP(gbc_cpu* cpu);

void DEC_B(gbc_cpu* cpu);
void DEC_C(gbc_cpu* cpu);
void DEC_D(gbc_cpu* cpu);
void DEC_E(gbc_cpu* cpu);
void DEC_H(gbc_cpu* cpu);
void DEC_L(gbc_cpu* cpu);
void DEC_A(gbc_cpu* cpu);
void DEC_mHL(gbc_cpu* cpu);
void DEC_BC(gbc_cpu* cpu);
void DEC_DE(gbc_cpu* cpu);
void DEC_HL(gbc_cpu* cpu);
void DEC_SP(gbc_cpu* cpu);

void BIT_0_A(gbc_cpu* cpu);
void BIT_0_B(gbc_cpu* cpu);
void BIT_0_C(gbc_cpu* cpu);
void BIT_0_D(gbc_cpu* cpu);
void BIT_0_E(gbc_cpu* cpu);
void BIT_0_H(gbc_cpu* cpu);
void BIT_0_L(gbc_cpu* cpu);
void BIT_0_M(gbc_cpu* cpu);

void RES_0_A(gbc_cpu* cpu);
void RES_0_B(gbc_cpu* cpu);
void RES_0_C(gbc_cpu* cpu);
void RES_0_D(gbc_cpu* cpu);
void RES_0_E(gbc_cpu* cpu);
void RES_0_H(gbc_cpu* cpu);
void RES_0_L(gbc_cpu* cpu);
void RES_0_M(gbc_cpu* cpu);

void BIT_1_A(gbc_cpu* cpu);
void BIT_1_B(gbc_cpu* cpu);
void BIT_1_C(gbc_cpu* cpu);
void BIT_1_D(gbc_cpu* cpu);
void BIT_1_E(gbc_cpu* cpu);
void BIT_1_H(gbc_cpu* cpu);
void BIT_1_L(gbc_cpu* cpu);

void BIT_1_M(gbc_cpu* cpu);
void BIT_2_A(gbc_cpu* cpu);
void BIT_2_B(gbc_cpu* cpu);
void BIT_2_C(gbc_cpu* cpu);
void BIT_2_D(gbc_cpu* cpu);
void BIT_2_E(gbc_cpu* cpu);
void BIT_2_H(gbc_cpu* cpu);
void BIT_2_L(gbc_cpu* cpu);
void BIT_2_M(gbc_cpu* cpu);

void BIT_3_A(gbc_cpu* cpu);
void BIT_3_B(gbc_cpu* cpu);
void BIT_3_C(gbc_cpu* cpu);
void BIT_3_D(gbc_cpu* cpu);
void BIT_3_E(gbc_cpu* cpu);
void BIT_3_H(gbc_cpu* cpu);
void BIT_3_L(gbc_cpu* cpu);
void BIT_3_M(gbc_cpu* cpu);

void BIT_4_A(gbc_cpu* cpu);
void BIT_4_B(gbc_cpu* cpu);
void BIT_4_C(gbc_cpu* cpu);
void BIT_4_D(gbc_cpu* cpu);
void BIT_4_E(gbc_cpu* cpu);
void BIT_4_H(gbc_cpu* cpu);
void BIT_4_L(gbc_cpu* cpu);
void BIT_4_M(gbc_cpu* cpu);

void BIT_5_A(gbc_cpu* cpu);
void BIT_5_B(gbc_cpu* cpu);
void BIT_5_C(gbc_cpu* cpu);
void BIT_5_D(gbc_cpu* cpu);
void BIT_5_E(gbc_cpu* cpu);
void BIT_5_H(gbc_cpu* cpu);
void BIT_5_L(gbc_cpu* cpu);
void BIT_5_M(gbc_cpu* cpu);

void BIT_6_A(gbc_cpu* cpu);
void BIT_6_B(gbc_cpu* cpu);
void BIT_6_C(gbc_cpu* cpu);
void BIT_6_D(gbc_cpu* cpu);
void BIT_6_E(gbc_cpu* cpu);
void BIT_6_H(gbc_cpu* cpu);
void BIT_6_L(gbc_cpu* cpu);
void BIT_6_M(gbc_cpu* cpu);

void BIT_7_A(gbc_cpu* cpu);
void BIT_7_B(gbc_cpu* cpu);
void BIT_7_C(gbc_cpu* cpu);
void BIT_7_D(gbc_cpu* cpu);
void BIT_7_E(gbc_cpu* cpu);
void BIT_7_H(gbc_cpu* cpu);
void BIT_7_L(gbc_cpu* cpu);
void BIT_7_M(gbc_cpu* cpu);

void RES_1_A(gbc_cpu* cpu);
void RES_1_B(gbc_cpu* cpu);
void RES_1_C(gbc_cpu* cpu);
void RES_1_D(gbc_cpu* cpu);
void RES_1_E(gbc_cpu* cpu);
void RES_1_H(gbc_cpu* cpu);
void RES_1_L(gbc_cpu* cpu);
void RES_1_M(gbc_cpu* cpu);

void RES_2_A(gbc_cpu* cpu);
void RES_2_B(gbc_cpu* cpu);
void RES_2_C(gbc_cpu* cpu);
void RES_2_D(gbc_cpu* cpu);
void RES_2_E(gbc_cpu* cpu);
void RES_2_H(gbc_cpu* cpu);
void RES_2_L(gbc_cpu* cpu);
void RES_2_M(gbc_cpu* cpu);

void RES_3_A(gbc_cpu* cpu);
void RES_3_B(gbc_cpu* cpu);
void RES_3_C(gbc_cpu* cpu);
void RES_3_D(gbc_cpu* cpu);
void RES_3_E(gbc_cpu* cpu);
void RES_3_H(gbc_cpu* cpu);
void RES_3_L(gbc_cpu* cpu);
void RES_3_M(gbc_cpu* cpu);

void RES_4_A(gbc_cpu* cpu);
void RES_4_B(gbc_cpu* cpu);
void RES_4_C(gbc_cpu* cpu);
void RES_4_D(gbc_cpu* cpu);
void RES_4_E(gbc_cpu* cpu);
void RES_4_H(gbc_cpu* cpu);
void RES_4_L(gbc_cpu* cpu);
void RES_4_M(gbc_cpu* cpu);

void RES_5_A(gbc_cpu* cpu);
void RES_5_B(gbc_cpu* cpu);
void RES_5_C(gbc_cpu* cpu);
void RES_5_D(gbc_cpu* cpu);
void RES_5_E(gbc_cpu* cpu);
void RES_5_H(gbc_cpu* cpu);
void RES_5_L(gbc_cpu* cpu);
void RES_5_M(gbc_cpu* cpu);

void RES_6_A(gbc_cpu* cpu);
void RES_6_B(gbc_cpu* cpu);
void RES_6_C(gbc_cpu* cpu);
void RES_6_D(gbc_cpu* cpu);
void RES_6_E(gbc_cpu* cpu);
void RES_6_H(gbc_cpu* cpu);
void RES_6_L(gbc_cpu* cpu);
void RES_6_M(gbc_cpu* cpu);

void RES_7_A(gbc_cpu* cpu);
void RES_7_B(gbc_cpu* cpu);
void RES_7_C(gbc_cpu* cpu);
void RES_7_D(gbc_cpu* cpu);
void RES_7_E(gbc_cpu* cpu);
void RES_7_H(gbc_cpu* cpu);
void RES_7_L(gbc_cpu* cpu);
void RES_7_M(gbc_cpu* cpu);

void SET_0_A(gbc_cpu* cpu);
void SET_0_B(gbc_cpu* cpu);
void SET_0_C(gbc_cpu* cpu);
void SET_0_D(gbc_cpu* cpu);
void SET_0_E(gbc_cpu* cpu);
void SET_0_H(gbc_cpu* cpu);
void SET_0_L(gbc_cpu* cpu);
void SET_0_M(gbc_cpu* cpu);

void SET_1_A(gbc_cpu* cpu);
void SET_1_B(gbc_cpu* cpu);
void SET_1_C(gbc_cpu* cpu);
void SET_1_D(gbc_cpu* cpu);
void SET_1_E(gbc_cpu* cpu);
void SET_1_H(gbc_cpu* cpu);
void SET_1_L(gbc_cpu* cpu);
void SET_1_M(gbc_cpu* cpu);

void SET_2_A(gbc_cpu* cpu);
void SET_2_B(gbc_cpu* cpu);
void SET_2_C(gbc_cpu* cpu);
void SET_2_D(gbc_cpu* cpu);
void SET_2_E(gbc_cpu* cpu);
void SET_2_H(gbc_cpu* cpu);
void SET_2_L(gbc_cpu* cpu);
void SET_2_M(gbc_cpu* cpu);

void SET_3_A(gbc_cpu* cpu);
void SET_3_B(gbc_cpu* cpu);
void SET_3_C(gbc_cpu* cpu);
void SET_3_D(gbc_cpu* cpu);
void SET_3_E(gbc_cpu* cpu);
void SET_3_H(gbc_cpu* cpu);
void SET_3_L(gbc_cpu* cpu);
void SET_3_M(gbc_cpu* cpu);

void SET_4_A(gbc_cpu* cpu);
void SET_4_B(gbc_cpu* cpu);
void SET_4_C(gbc_cpu* cpu);
void SET_4_D(gbc_cpu* cpu);
void SET_4_E(gbc_cpu* cpu);
void SET_4_H(gbc_cpu* cpu);
void SET_4_L(gbc_cpu* cpu);
void SET_4_M(gbc_cpu* cpu);

void SET_5_A(gbc_cpu* cpu);
void SET_5_B(gbc_cpu* cpu);
void SET_5_C(gbc_cpu* cpu);
void SET_5_D(gbc_cpu* cpu);
void SET_5_E(gbc_cpu* cpu);
void SET_5_H(gbc_cpu* cpu);
void SET_5_L(gbc_cpu* cpu);
void SET_5_M(gbc_cpu* cpu);

void SET_6_A(gbc_cpu* cpu);
void SET_6_B(gbc_cpu* cpu);
void SET_6_C(gbc_cpu* cpu);
void SET_6_D(gbc_cpu* cpu);
void SET_6_E(gbc_cpu* cpu);
void SET_6_H(gbc_cpu* cpu);
void SET_6_L(gbc_cpu* cpu);
void SET_6_M(gbc_cpu* cpu);

void SET_7_A(gbc_cpu* cpu);
void SET_7_B(gbc_cpu* cpu);
void SET_7_C(gbc_cpu* cpu);
void SET_7_D(gbc_cpu* cpu);
void SET_7_E(gbc_cpu* cpu);
void SET_7_H(gbc_cpu* cpu);
void SET_7_L(gbc_cpu* cpu);
void SET_7_M(gbc_cpu* cpu);

void RLA(gbc_cpu* cpu);
void RLCA(gbc_cpu* cpu);
void RRA(gbc_cpu* cpu);
void RRCA(gbc_cpu* cpu);

void RL_A(gbc_cpu* cpu);
void RL_B(gbc_cpu* cpu);
void RL_C(gbc_cpu* cpu);
void RL_D(gbc_cpu* cpu);
void RL_E(gbc_cpu* cpu);
void RL_H(gbc_cpu* cpu);
void RL_L(gbc_cpu* cpu);
void RL_mHL(gbc_cpu* cpu);

void RLC_A(gbc_cpu* cpu);
void RLC_B(gbc_cpu* cpu);
void RLC_C(gbc_cpu* cpu);
void RLC_D(gbc_cpu* cpu);
void RLC_E(gbc_cpu* cpu);
void RLC_H(gbc_cpu* cpu);
void RLC_L(gbc_cpu* cpu);
void RLC_mHL(gbc_cpu* cpu);

void RR_A(gbc_cpu* cpu);
void RR_B(gbc_cpu* cpu);
void RR_C(gbc_cpu* cpu);
void RR_D(gbc_cpu* cpu);
void RR_E(gbc_cpu* cpu);
void RR_H(gbc_cpu* cpu);
void RR_L(gbc_cpu* cpu);
void RR_mHL(gbc_cpu* cpu);

void RRC_A(gbc_cpu* cpu);
void RRC_B(gbc_cpu* cpu);
void RRC_C(gbc_cpu* cpu);
void RRC_D(gbc_cpu* cpu);
void RRC_E(gbc_cpu* cpu);
void RRC_H(gbc_cpu* cpu);
void RRC_L(gbc_cpu* cpu);
void RRC_mHL(gbc_cpu* cpu);

void SLA_A(gbc_cpu* cpu);
void SLA_B(gbc_cpu* cpu);
void SLA_C(gbc_cpu* cpu);
void SLA_D(gbc_cpu* cpu);
void SLA_E(gbc_cpu* cpu);
void SLA_H(gbc_cpu* cpu);
void SLA_L(gbc_cpu* cpu);

void SLL_A(gbc_cpu* cpu);
void SLL_B(gbc_cpu* cpu);
void SLL_C(gbc_cpu* cpu);
void SLL_D(gbc_cpu* cpu);
void SLL_E(gbc_cpu* cpu);
void SLL_H(gbc_cpu* cpu);
void SLL_L(gbc_cpu* cpu);

void SRA_A(gbc_cpu* cpu);
void SRA_B(gbc_cpu* cpu);
void SRA_C(gbc_cpu* cpu);
void SRA_D(gbc_cpu* cpu);
void SRA_E(gbc_cpu* cpu);
void SRA_H(gbc_cpu* cpu);
void SRA_L(gbc_cpu* cpu);

void SRL_A(gbc_cpu* cpu);
void SRL_B(gbc_cpu* cpu);
void SRL_C(gbc_cpu* cpu);
void SRL_D(gbc_cpu* cpu);
void SRL_E(gbc_cpu* cpu);
void SRL_H(gbc_cpu* cpu);
void SRL_L(gbc_cpu* cpu);

void CPL(gbc_cpu* cpu);
void NEG(gbc_cpu* cpu);
void CCF(gbc_cpu* cpu);
void SCF(gbc_cpu* cpu);

void PUSH_BC(gbc_cpu* cpu);
void PUSH_DE(gbc_cpu* cpu);
void PUSH_HL(gbc_cpu* cpu);
void PUSH_AF(gbc_cpu* cpu);

void POP_BC(gbc_cpu* cpu);
void POP_DE(gbc_cpu* cpu);
void POP_HL(gbc_cpu* cpu);
void POP_AF(gbc_cpu* cpu);

void JP_a16(gbc_cpu* cpu);
void JP_HL(gbc_cpu* cpu);
void JP_NZ_a16(gbc_cpu* cpu);
void JP_Znn(gbc_cpu* cpu) ;
void JP_NC_a16(gbc_cpu* cpu);
void JP_Cnn(gbc_cpu* cpu) ;

void JR_r8(gbc_cpu* cpu);
void JR_NZ_r8(gbc_cpu* cpu);
void JR_Z_r8(gbc_cpu* cpu) ;
void JR_NC_r8(gbc_cpu* cpu);
void JR_C_r8(gbc_cpu* cpu) ;

void CALL_a16(gbc_cpu* cpu);
void CALL_NZ_a16(gbc_cpu* cpu);
void CALL_Z_a16(gbc_cpu* cpu);
void CALL_NC_a16(gbc_cpu* cpu);
void CALL_C_a16(gbc_cpu* cpu);

void RET(gbc_cpu* cpu);
void RET_I(gbc_cpu* cpu);
void RET_NZ(gbc_cpu* cpu);
void RET_Z(gbc_cpu* cpu);
void RET_NC(gbc_cpu* cpu);
void RET_C(gbc_cpu* cpu);

void RST_00H(gbc_cpu* cpu);
void RST_08H(gbc_cpu* cpu);
void RST_10H(gbc_cpu* cpu);
void RST_18H(gbc_cpu* cpu);
void RST_20H(gbc_cpu* cpu);
void RST_28H(gbc_cpu* cpu);
void RST_30H(gbc_cpu* cpu);
void RST_38H(gbc_cpu* cpu);

void NOP(gbc_cpu* cpu);
void HALT(gbc_cpu* cpu);
void DI(gbc_cpu* cpu);
void EI(gbc_cpu* cpu);
void rsv(gbc_cpu* cpu);
void rrs(gbc_cpu* cpu);
void MAPcb(gbc_cpu* cpu);
void XX(gbc_cpu* cpu);

static const gbc_operator OPS[256] = {
	// 00
	&NOP,		&LD_BC_d16,	&LD_mBC_A,	&INC_BC,		&INC_B,	&DEC_B,	&LD_B_d8,	&RLCA,
	&LD_a16_SP,	&ADD_HL_BC,	&LD_A_mBC,	&DEC_BC,		&INC_C,	&DEC_C,	&LD_C_d8,	&RRCA,
	// 10
	&XX/*DJNZn, STOP*/,		&LD_DE_d16,	&LD_mDE_A,	&INC_DE,		&INC_D,	&DEC_D,	&LD_D_d8,	&RLA,
	&JR_r8,		&ADD_HL_DE,	&LD_A_mDE,	&DEC_DE,		&INC_E,	&DEC_E,	&LD_E_d8,	&RRA,
	// 20
	&JR_NZ_r8,		&LD_HL_d16,	&LD_mHLI_A,	&INC_mHL,		&INC_H,	&DEC_H,	&LD_H_d8,	&DAA,
	&JR_Z_r8,		&ADD_HL_HL,	&LD_A_mHLI,	&DEC_HL,		&INC_L,	&DEC_L,	&LD_L_d8,	&CPL,
	// 30
	&JR_NC_r8,		&LD_SP_d16,	&LD_mHLD_A,	&INC_SP,		&INC_mHL,	&DEC_mHL,	&LD_HL_d8,	&SCF,
	&JR_C_r8,		&ADD_HL_SP,	&LD_A_mHLD,	&DEC_SP,		&INC_A,	&DEC_A,	&LD_A_d8,	&CCF,
	// 40
	&LD_B_B,	&LD_B_C,	&LD_B_D,	&LD_B_E,	&LD_B_H,	&LD_B_L,	&LD_B_mHL,	&LD_B_A,
	&LD_C_B,	&LD_C_C,	&LD_C_D,	&LD_C_E,	&LD_C_H,	&LD_C_L,	&LD_C_mHL,	&LD_C_A,
	// 50
	&LD_D_B,	&LD_D_C,	&LD_D_D,	&LD_D_E,	&LD_D_H,	&LD_D_L,	&LD_D_mHL,	&LD_D_A,
	&LD_E_B,	&LD_E_C,	&LD_E_D,	&LD_E_E,	&LD_E_H,	&LD_E_L,	&LD_E_mHL,	&LD_E_A,
	// 60
	&LD_H_B,	&LD_H_C,	&LD_H_D,	&LD_H_E,	&LD_H_H,	&LD_H_L,	&LD_H_mHL,	&LD_H_A,
	&LD_L_B,	&LD_L_C,	&LD_L_C,	&LD_L_E,	&LD_L_H,	&LD_L_L,	&LD_L_mHL,	&LD_L_A,
	// 70
	&LD_mHL_B,	&LD_mHL_C,	&LD_mHL_D,	&LD_mHL_D,	&LD_mHL_H,	&LD_mHL_L,	&HALT,		&LD_mHL_A,
	&LD_A_B,	&LD_A_C,	&LD_A_D,	&LD_A_E,	&LD_A_H,	&LD_A_L,	&LD_A_mHL,	&LD_A_A,
	// 80
	&ADD_B,	&ADD_C,	&ADD_D,	&ADD_E,	&ADD_H,	&ADD_L,	&ADD_mHL,		&ADD_A,
	&ADC_B,	&ADC_C,	&ADC_D,	&ADC_E,	&ADC_H,	&ADC_L,	&ADC_mHL,		&ADC_A,
	// 90
	&SUB_B,	&SUB_C,	&SUB_D,	&SUB_E,	&SUB_H,	&SUB_L,	&SUB_mHL,		&SUB_A,
	&SBC_B,	&SBC_C,	&SBC_D,	&SBC_E,	&SBC_H,	&SBC_L,	&SBC_mHL,		&SBC_A,
	// A0
	&AND_B,	&AND_C,	&AND_D,	&AND_E,	&AND_H,	&AND_L,	&AND_mHL,		&AND_A,
	&XOR_B,	&XOR_C,	&XOR_D,	&XOR_E,	&XOR_H,	&XOR_L,	&XOR_mHL,		&XOR_A,
	// B0
	&OR_B,		&OR_C,		&OR_D,		&OR_E,		&OR_H,		&OR_L,		&OR_mHL,		&OR_A,
	&CP_B,		&CP_C,		&CP_D,		&CP_E,		&CP_H,		&CP_L,		&CP_mHL,		&CP_A,
	// C0
	&RET_NZ,		&POP_BC,		&JP_NZ_a16,	&JP_a16,		&CALL_NZ_a16,	&PUSH_BC,	&ADD_d8,		&RST_00H,
	&RET_Z,		&RET,		&JP_Znn,		&MAPcb,		&CALL_Z_a16,	&CALL_a16,	&ADC_d8,		&RST_08H,
	// D0
	&RET_NC,		&POP_DE,		&JP_NC_a16,	&XX,		&CALL_NC_a16,	&PUSH_DE,	&SUB_d8,		&RST_10H,
	&RET_C,		&RET_I,		&JP_Cnn,		&XX,		&CALL_C_a16,	&XX,		&SBC_d8,		&RST_18H,
	// E0
	&LDH_a8_A,	&POP_HL,		&LD_mC_A,	&XX,		&XX,		&PUSH_HL,	&AND_d8,		&RST_20H,
	&ADD_SP_d8,	&JP_HL,		&LD_a16_A,		&XX,		&XX,		&XX,		&XOR_d8,		&RST_28H,
	// F0
	&LDH_A_a8,	&POP_AF,		&LD_A_mC,	&DI,		&XX,		&PUSH_AF,	&OR_d8,		&RST_30H,
	&LD_HL_SP_r8,	&XX,		&LD_A_a16,		&EI,		&XX,		&XX,		&CP_d8,		&RST_38H
};

static const gbc_operator CB_OPS[256] = {
    //CB00
    &RLC_B,  &RLC_C,  &RLC_D,  &RLC_E,  &RLC_H,  &RLC_L,  &RLC_mHL,  &RLC_A,
    &RRC_B,  &RRC_C,  &RRC_D,  &RRC_E,  &RRC_H,  &RRC_L,  &RRC_mHL,  &RRC_A,
    //CB10
    &RL_B,  &RL_C,  &RL_D,  &RL_E,  &RL_H,  &RL_L,  &RL_mHL,  &RL_A,
    &RR_B,  &RR_C,  &RR_D,  &RR_E,  &RR_H,  &RR_L,  &RR_mHL,  &RR_A,
    //CB20
    &SLA_B,  &SLA_C,  &SLA_D,  &SLA_E,  &SLA_H,  &SLA_L,  &XX,  &SLA_A,
    &SRA_B,  &SRA_C,  &SRA_D,  &SRA_E,  &SRA_H,  &SRA_L,  &XX,  &SRA_A,
    //CB30
    &SWAP_B,  &SWAP_C,  &SWAP_D,  &SWAP_E,  &SWAP_H,  &SWAP_L,  &XX,  &SWAP_A,
    &SRL_B,   &SRL_C,   &SRL_D,   &SRL_E,   &SRL_H,   &SRL_L,   &XX,   &SRL_A,
    //CB40
    &BIT_0_B, &BIT_0_C, &BIT_0_D, &BIT_0_E, &BIT_0_H, &BIT_0_L, &BIT_0_M, &BIT_0_A,
    &BIT_1_B, &BIT_1_C, &BIT_1_D, &BIT_1_E, &BIT_1_H, &BIT_1_L, &BIT_1_M, &BIT_1_A,
    //CB50
    &BIT_2_B, &BIT_2_C, &BIT_2_D, &BIT_2_E, &BIT_2_H, &BIT_2_L, &BIT_2_M, &BIT_2_A,
    &BIT_3_B, &BIT_3_C, &BIT_3_D, &BIT_3_E, &BIT_3_H, &BIT_3_L, &BIT_3_M, &BIT_3_A,
    //CB60
    &BIT_4_B, &BIT_4_C, &BIT_4_D, &BIT_4_E, &BIT_4_H, &BIT_4_L, &BIT_4_M, &BIT_4_A,
    &BIT_5_B, &BIT_5_C, &BIT_5_D, &BIT_5_E, &BIT_5_H, &BIT_5_L, &BIT_5_M, &BIT_5_A,
    //CB70
    &BIT_6_B, &BIT_6_C, &BIT_6_D, &BIT_6_E, &BIT_6_H, &BIT_6_L, &BIT_6_M, &BIT_6_A,
    &BIT_7_B, &BIT_7_C, &BIT_7_D, &BIT_7_E, &BIT_7_H, &BIT_7_L, &BIT_7_M, &BIT_7_A,
    //CB80
    &RES_0_B, &RES_0_C, &RES_0_D, &RES_0_E, &RES_0_H, &RES_0_L, &RES_0_M, &RES_0_A,
    &RES_1_B, &RES_1_C, &RES_1_D, &RES_1_E, &RES_1_H, &RES_1_L, &RES_1_M, &RES_1_A,
    //CB90
    &RES_2_B, &RES_2_C, &RES_2_D, &RES_2_E, &RES_2_H, &RES_2_L, &RES_2_M, &RES_2_A,
    &RES_3_B, &RES_3_C, &RES_3_D, &RES_3_E, &RES_3_H, &RES_3_L, &RES_3_M, &RES_3_A,
    //CBA0
    &RES_4_B, &RES_4_C, &RES_4_D, &RES_4_E, &RES_4_H, &RES_4_L, &RES_4_M, &RES_4_A,
    &RES_5_B, &RES_5_C, &RES_5_D, &RES_5_E, &RES_5_H, &RES_5_L, &RES_5_M, &RES_5_A,
    //CBB0
    &RES_6_B, &RES_6_C, &RES_6_D, &RES_6_E, &RES_6_H, &RES_6_L, &RES_6_M, &RES_6_A,
    &RES_7_B, &RES_7_C, &RES_7_D, &RES_7_E, &RES_7_H, &RES_7_L, &RES_7_M, &RES_7_A,
    //CBC0
    &SET_0_B, &SET_0_C, &SET_0_D, &SET_0_E, &SET_0_H, &SET_0_L, &SET_0_M, &SET_0_A,
    &SET_1_B, &SET_1_C, &SET_1_D, &SET_1_E, &SET_1_H, &SET_1_L, &SET_1_M, &SET_1_A,
    //CBD0
    &SET_2_B, &SET_2_C, &SET_2_D, &SET_2_E, &SET_2_H, &SET_2_L, &SET_2_M, &SET_2_A,
    &SET_3_B, &SET_3_C, &SET_3_D, &SET_3_E, &SET_3_H, &SET_3_L, &SET_3_M, &SET_3_A,
    //CBE0
    &SET_4_B, &SET_4_C, &SET_4_D, &SET_4_E, &SET_4_H, &SET_4_L, &SET_4_M, &SET_4_A,
    &SET_5_B, &SET_5_C, &SET_5_D, &SET_5_E, &SET_5_H, &SET_5_L, &SET_5_M, &SET_5_A,
    //CBF0
    &SET_6_B, &SET_6_C, &SET_6_D, &SET_6_E, &SET_6_H, &SET_6_L, &SET_6_M, &SET_6_A,
    &SET_7_B, &SET_7_C, &SET_7_D, &SET_7_E, &SET_7_H, &SET_7_L, &SET_7_M, &SET_7_A,
};

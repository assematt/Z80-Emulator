#pragma once

#include <SFML/Config.hpp>

// Normal instruction
enum TOpCodesMainInstruction : sf::Uint16
{
	/// 8-Bit Load Group
	#pragma region 8-Bit Load Group
	LD_A_INDIRECT_ADR = 0x003a,
	LD_A_n = 0x003e,
	LD_B_B = 0x0040,
	LD_B_C = 0x0041,
	LD_B_D = 0x0042,
	LD_B_E = 0x0043,
	LD_B_H = 0x0044,
	LD_B_L = 0x0045,
	LD_B_INDIRECT_HL = 0x0046,
	LD_B_A = 0x0047,
	LD_C_B = 0x0048,
	LD_C_C = 0x0049,
	LD_C_D = 0x004a,
	LD_C_E = 0x004b,
	LD_C_H = 0x004c,
	LD_C_L = 0x004d,
	LD_C_INDIRECT_HL = 0x004e,
	LD_C_A = 0x004f,
	LD_D_B = 0x0050,
	LD_D_C = 0x0051,
	LD_D_D = 0x0052,
	LD_D_E = 0x0053,
	LD_D_H = 0x0054,
	LD_D_L = 0x0055,
	LD_D_INDIRECT_HL = 0x0056,
	LD_D_A = 0x0057,
	LD_E_B = 0x0058,
	LD_E_C = 0x0059,
	LD_E_D = 0x005a,
	LD_E_E = 0x005b,
	LD_E_H = 0x005c,
	LD_E_L = 0x005d,
	LD_E_INDIRECT_HL = 0x005e,
	LD_E_A = 0x005f,
	LD_H_B = 0x0060,
	LD_H_C = 0x0061,
	LD_H_D = 0x0062,
	LD_H_E = 0x0063,
	LD_H_H = 0x0064,
	LD_H_L = 0x0065,
	LD_H_INDIRECT_HL = 0x0066,
	LD_H_A = 0x0067,
	LD_L_B = 0x0068,
	LD_L_C = 0x0069,
	LD_L_D = 0x006a,
	LD_L_E = 0x006b,
	LD_L_H = 0x006c,
	LD_L_L = 0x006d,
	LD_L_INDIRECT_HL = 0x006e,
	LD_L_A = 0x006f,
	LD_A_B = 0x0078,
	LD_A_C = 0x0079,
	LD_A_D = 0x007a,
	LD_A_E = 0x007b,
	LD_A_H = 0x007c,
	LD_A_L = 0x007d,
	LD_A_INDIRECT_HL = 0x007e,
	LD_A_A = 0x007f,
	LD_B_n = 0x0006,
	LD_A_INDIRECT_BC = 0x000a,
	LD_C_n = 0x000e,
	LD_D_n = 0x0016,
	LD_A_INDIRECT_DE = 0x001a,
	LD_E_n = 0x001e,
	LD_H_n = 0x0026,
	LD_L_n = 0x002e,
#pragma endregion

	/// 16-Bit Load Group
	#pragma region 16-Bit Load Group
	LD_BC_n = 0x0001,
	LD_INDIRECT_BC_A = 0x0002,
	LD_DE_n = 0x0011,
	LD_INDIRECT_DE_A = 0x0012,
	LD_HL_n = 0x0021,
	LD_INDIRECT_ADR_HL = 0x0022,
	LD_HL_INDIRECT_ADR = 0x002a,
	LD_SP_n = 0x0031,
	LD_INDIRECT_ADR_A = 0x0032,
	LD_INDIRECT_HL_n = 0x0036,
	LD_INDIRECT_HL_B = 0x0070,
	LD_INDIRECT_HL_C = 0x0071,
	LD_INDIRECT_HL_D = 0x0072,
	LD_INDIRECT_HL_E = 0x0073,
	LD_INDIRECT_HL_H = 0x0074,
	LD_INDIRECT_HL_L = 0x0075,
	LD_INDIRECT_HL_A = 0x0077,
	LD_SP_HL = 0x00f9,
	PUSH_BC = 0x00c5,
	PUSH_DE = 0x00d5,
	PUSH_HL = 0x00e5,
	PUSH_AF = 0x00f5,
	POP_BC = 0x00c1,
	POP_DE = 0x00d1,
	POP_HL = 0x00e1,
	POP_AF = 0x00f1,
	#pragma endregion
	
	/// Exchange, Block Transfer, and Search Group
	#pragma region Exchange, Block Transfer, and Search Group
	EX_AF_AF = 0x0008,
	EXX = 0x00d9,
	EX_INDIRECT_SP_HL = 0x00e3,
	EX_DE_HL = 0x00eb,
	#pragma endregion


	/// 8-Bit Arithmetic Group
	#pragma region 8-Bit Arithmetic Group
	ADD_A_B = 0x0080,
	ADD_A_C = 0x0081,
	ADD_A_D = 0x0082,
	ADD_A_E = 0x0083,
	ADD_A_H = 0x0084,
	ADD_A_L = 0x0085,
	ADD_A_INDIRECT_HL = 0x0086,
	ADD_A_A = 0x0087,
	ADD_A_n = 0x00c6,
	ADC_A_B = 0x0088,
	ADC_A_C = 0x0089,
	ADC_A_D = 0x008a,
	ADC_A_E = 0x008b,
	ADC_A_H = 0x008c,
	ADC_A_L = 0x008d,
	ADC_A_INDIRECT_HL = 0x008e,
	ADC_A_A = 0x008f,
	ADC_A_n = 0x00ce,
	SBC_A_B = 0x0098,
	SBC_A_C = 0x0099,
	SBC_A_D = 0x009a,
	SBC_A_E = 0x009b,
	SBC_A_H = 0x009c,
	SBC_A_L = 0x009d,
	SBC_A_INDIRECT_HL = 0x009e,
	SBC_A_A = 0x009f,
	SBC_A_n = 0x00de,
	INC_B = 0x0004,
	INC_C = 0x000c,
	INC_D = 0x0014,
	INC_E = 0x001c,
	INC_H = 0x0024,
	INC_L = 0x002c,
	INC_A = 0x003c,
	DEC_B = 0x0005,
	DEC_C = 0x000d,
	DEC_D = 0x0015,
	DEC_E = 0x001d,
	DEC_H = 0x0025,
	DEC_L = 0x002d,
	DEC_A = 0x003d,
	SUB_B = 0x0090,
	SUB_C = 0x0091,
	SUB_D = 0x0092,
	SUB_E = 0x0093,
	SUB_H = 0x0094,
	SUB_L = 0x0095,
	SUB_INDIRECT_HL = 0x0096,
	SUB_A = 0x0097,
	SUB_n = 0x00d6,
	AND_B = 0x00a0,
	AND_C = 0x00a1,
	AND_D = 0x00a2,
	AND_E = 0x00a3,
	AND_H = 0x00a4,
	AND_L = 0x00a5,
	AND_INDIRECT_HL = 0x00a6,
	AND_A = 0x00a7,
	AND_n = 0x00e6,
	OR_B = 0x00b0,
	OR_C = 0x00b1,
	OR_D = 0x00b2,
	OR_E = 0x00b3,
	OR_H = 0x00b4,
	OR_L = 0x00b5,
	OR_INDIRECT_HL = 0x00b6,
	OR_A = 0x00b7,
	OR_n = 0x00f6,
	XOR_B = 0x00a8,
	XOR_C = 0x00a9,
	XOR_D = 0x00aa,
	XOR_E = 0x00ab,
	XOR_H = 0x00ac,
	XOR_L = 0x00ad,
	XOR_INDIRECT_HL = 0x00ae,
	XOR_A = 0x00af,
	XOR_n = 0x00ee,
	CP_B = 0x00b8,
	CP_C = 0x00b9,
	CP_D = 0x00ba,
	CP_E = 0x00bb,
	CP_H = 0x00bc,
	CP_L = 0x00bd,
	CP_INDIRECT_HL = 0x00be,
	CP_A = 0x00bf,
	CP_n = 0x00fe,
#pragma endregion

	/// General-Purpose Arithmetic and CPU Control Groups
	#pragma region General-Purpose Arithmetic and CPU Control Groups
	DAA = 0x0027,
	CPL = 0x002f,
	CCF = 0x003f,
	SCF = 0x0037,
	NOP = 0x0000,
	HALT = 0x0076,
	DI = 0x00f3,
	EI = 0x00fb,
	#pragma endregion

	/// 16-Bit Arithmetic Group
	#pragma region 16-Bit Arithmetic Group
	ADD_HL_BC = 0x0009,
	ADD_HL_DE = 0x0019,
	ADD_HL_HL = 0x0029,
	ADD_HL_SP = 0x0039,
	INC_BC = 0x0003,	
	INC_DE = 0x0013,	
	INC_HL = 0x0023,	
	INC_SP = 0x0033,
	INC_INDIRECT_HL = 0x0034,	
	DEC_BC = 0x000b,	
	DEC_DE = 0x001b,	
	DEC_HL = 0x002b,	
	DEC_INDIRECT_HL = 0x0035,
	DEC_SP = 0x003b,	
	#pragma endregion
	

	/// Rotate and Shift Group
	#pragma region Rotate and Shift Group
	RLCA = 0x0007,
	RLA = 0x0017,
	RRCA = 0x000f,
	RRA = 0x001f,
	#pragma endregion

	/// Bit Set, Reset, and Test Group
	/// ----------------
	BITS = 0x00cb, // see TOpCodesBitInstructions

	/// Jump Group
	#pragma region Jump Group
	JP_NZ_ADR = 0x00c2,
	JP_ADR = 0x00c3,
	JP_Z_ADR = 0x00ca,
	JP_NC_ADR = 0x00d2,
	JP_C_ADR = 0x00da,
	JP_PO_ADR = 0x00e2,
	JP_INDIRECT_HL = 0x00e9,
	JP_PE_ADR = 0x00ea,
	JP_P_ADR = 0x00f2,
	JP_M_ADR = 0x00fa,
	JR_dis = 0x0018,
	JR_NZ_dis = 0x0020,
	JR_Z_dis = 0x0028,
	JR_NC_dis = 0x0030,
	JR_C_dis = 0x0038,
	DJNZ_dis = 0x0010,
#pragma endregion

	/// Call and Return Group
	#pragma region Call and Return Group
	CALL_NZ_ADR = 0x00c4,
	CALL_Z_ADR = 0x00cc,
	CALL_ADR = 0x00cd,
	CALL_NC_ADR = 0x00d4,
	CALL_C_ADR = 0x00dc,
	CALL_PO_ADR = 0x00e4,
	CALL_PE_ADR = 0x00ec,
	CALL_P_ADR = 0x00f4,
	CALL_M_ADR = 0x00fc,
	RET_NZ = 0x00c0,
	RET_Z = 0x00c8,
	RET = 0x00c9,
	RET_NC = 0x00d0,
	RET_C = 0x00d8,
	RET_PO = 0x00e0,
	RET_PE = 0x00e8,
	RET_P = 0x00f0,
	RET_M = 0x00f8,
	RST_0H = 0x00c7,
	RST_08H = 0x00cf,
	RST_10H = 0x00d7,
	RST_18H = 0x00df,
	RST_20H = 0x00e7,
	RST_28H = 0x00ef,
	RST_30H = 0x00f7,
	RST_38H = 0x00ff,
	#pragma endregion

	/// Input and Output Group
	#pragma region Input and Output Group
	IN_A_INDIRECT_port = 0x00db,
	OUT_INDIRECT_port_A = 0x00d3,
	#pragma endregion

	IX_INSTRUCTIONS = 0x00dd, // see TOpCodesIXInstructions

	EXTENDED_INSTRUCTIONS = 0x00ed,	// see TOpCodesExtendedInstruction
	
	IY_INSTRUCTIONS = 0x00fd, // see TOpCodesIYInstructions	
};

// Extended instructions (ED)
enum TOpCodesExtendedInstruction : sf::Uint16
{
	/// Exchange, Block Transfer, and Search Group
	/// ----------------
	LDI = 0xeda0,
	LDIR = 0xedb0,
	LDD = 0xeda8,
	LDDR = 0xedb8,
	CPI = 0xeda1,
	CPIR = 0xedb1,
	CPD = 0xeda9,
	CPDR = 0xedb9,


	/// General-Purpose Arithmetic and CPU Control Groups
	/// ----------------
	NEG = 0xed44,
	IM_0 = 0xed46,
	IM_1 = 0xed56,
	IM_2 = 0xed5e,


	/// 16-Bit Arithmetic Group
	/// ----------------
	ADC_HL_BC = 0xed4a,
	ADC_HL_DE = 0xed5a,
	ADC_HL_HL = 0xed6a,
	ADC_HL_SP = 0xed7a,
	SBC_HL_BC = 0xed42,
	SBC_HL_DE = 0xed52,
	SBC_HL_HL = 0xed62,
	SBC_HL_SP = 0xed72,


	/// Rotate and Shift Group
	/// ----------------
	RLD = 0xed6f,
	RRD = 0xed67,


	/// Call and Return Group
	/// ----------------
	RETI = 0xed4d,
	RETN = 0xed45,

	/// Input and Output Group
	/// ----------------
	IN_B_INDIRECT_C = 0xed40,
	IN_C_INDIRECT_C = 0xed48,
	IN_D_INDIRECT_C = 0xed50,
	IN_E_INDIRECT_C = 0xed58,
	IN_H_INDIRECT_C = 0xed60,
	IN_L_INDIRECT_C = 0xed68,
	IN_A_INDIRECT_C = 0xed78,
	INI = 0xeda2,
	INIR = 0xedb2,
	IND = 0xedaa,
	INDR = 0xedba,
	OUT_INDIRECT_C_B = 0xed41,
	OUT_INDIRECT_C_C = 0xed49,
	OUT_INDIRECT_C_D = 0xed51,
	OUT_INDIRECT_C_E = 0xed59,
	OUT_INDIRECT_C_H = 0xed61,
	OUT_INDIRECT_C_L = 0xed69,
	OUT_INDIRECT_C_A = 0xed79,
	OUTI = 0xeda3,
	OTIR = 0xedb3,
	OUTD = 0xedab,
	OTDR = 0xedbb,
	

	
	LD_INDIRECT_ADR_BC = 0xed43,
	LD_I_A = 0xed47,	
	LD_BC_INDIRECT_ADR = 0xed4b,	
	LD_R_A = 0xed4f,		
	LD_INDIRECT_ADR_DE = 0xed53,	
	LD_A_I = 0xed57,	
	LD_DE_INDIRECT_ADR = 0xed5b,	
	LD_A_R = 0xed5f,	
	LD_INDIRECT_ADR_SP = 0xed73,	
	LD_SP_INDIRECT_ADR = 0xed7b,
};

// Bit instructions (CB)
enum TOpCodesBitInstructions : sf::Uint16
{
	/// Rotate and Shift Group
	/// ----------------
	RLC_B = 0xcb00,
	RLC_C = 0xcb01,
	RLC_D = 0xcb02,
	RLC_E = 0xcb03,
	RLC_H = 0xcb04,
	RLC_L = 0xcb05,
	RLC_INDIRECT_HL = 0xcb06,
	RLC_A = 0xcb07,
	RL_B = 0xcb10,
	RL_C = 0xcb11,
	RL_D = 0xcb12,
	RL_E = 0xcb13,
	RL_H = 0xcb14,
	RL_L = 0xcb15,
	RL_INDIRECT_HL = 0xcb16,
	RL_A = 0xcb17,
	SLA_B = 0xcb20,
	SLA_C = 0xcb21,
	SLA_D = 0xcb22,
	SLA_E = 0xcb23,
	SLA_H = 0xcb24,
	SLA_L = 0xcb25,
	SLA_INDIRECT_HL = 0xcb26,
	SLA_A = 0xcb27,
	SRA_B = 0xcb28,
	SRA_C = 0xcb29,
	SRA_D = 0xcb2a,
	SRA_E = 0xcb2b,
	SRA_H = 0xcb2c,
	SRA_L = 0xcb2d,
	SRA_INDIRECT_HL = 0xcb2e,
	SRA_A = 0xcb2f,
	SRL_B = 0xcb38,
	SRL_C = 0xcb39,
	SRL_D = 0xcb3a,
	SRL_E = 0xcb3b,
	SRL_H = 0xcb3c,
	SRL_L = 0xcb3d,
	SRL_INDIRECT_HL = 0xcb3e,
	SRL_A = 0xcb3f,

	/// Bit Set, Reset, and Test Group
	/// ----------------
	BIT_0_B = 0xcb40,
	BIT_0_C = 0xcb41,
	BIT_0_D = 0xcb42,
	BIT_0_E = 0xcb43,
	BIT_0_H = 0xcb44,
	BIT_0_L = 0xcb45,
	BIT_0_INDIRECT_HL = 0xcb46,
	BIT_0_A = 0xcb47,
	BIT_1_B = 0xcb48,
	BIT_1_C = 0xcb49,
	BIT_1_D = 0xcb4a,
	BIT_1_E = 0xcb4b,
	BIT_1_H = 0xcb4c,
	BIT_1_L = 0xcb4d,
	BIT_1_INDIRECT_HL = 0xcb4e,
	BIT_1_A = 0xcb4f,
	BIT_2_B = 0xcb50,
	BIT_2_C = 0xcb51,
	BIT_2_D = 0xcb52,
	BIT_2_E = 0xcb53,
	BIT_2_H = 0xcb54,
	BIT_2_L = 0xcb55,
	BIT_2_INDIRECT_HL = 0xcb56,
	BIT_2_A = 0xcb57,
	BIT_3_B = 0xcb58,
	BIT_3_C = 0xcb59,
	BIT_3_D = 0xcb5a,
	BIT_3_E = 0xcb5b,
	BIT_3_H = 0xcb5c,
	BIT_3_L = 0xcb5d,
	BIT_3_INDIRECT_HL = 0xcb5e,
	BIT_3_A = 0xcb5f,
	BIT_4_B = 0xcb60,
	BIT_4_C = 0xcb61,
	BIT_4_D = 0xcb62,
	BIT_4_E = 0xcb63,
	BIT_4_H = 0xcb64,
	BIT_4_L = 0xcb65,
	BIT_4_INDIRECT_HL = 0xcb66,
	BIT_4_A = 0xcb67,
	BIT_5_B = 0xcb68,
	BIT_5_C = 0xcb69,
	BIT_5_D = 0xcb6a,
	BIT_5_E = 0xcb6b,
	BIT_5_H = 0xcb6c,
	BIT_5_L = 0xcb6d,
	BIT_5_INDIRECT_HL = 0xcb6e,
	BIT_5_A = 0xcb6f,
	BIT_6_B = 0xcb70,
	BIT_6_C = 0xcb71,
	BIT_6_D = 0xcb72,
	BIT_6_E = 0xcb73,
	BIT_6_H = 0xcb74,
	BIT_6_L = 0xcb75,
	BIT_6_INDIRECT_HL = 0xcb76,
	BIT_6_A = 0xcb77,
	BIT_7_B = 0xcb78,
	BIT_7_C = 0xcb79,
	BIT_7_D = 0xcb7a,
	BIT_7_E = 0xcb7b,
	BIT_7_H = 0xcb7c,
	BIT_7_L = 0xcb7d,
	BIT_7_INDIRECT_HL = 0xcb7e,
	BIT_7_A = 0xcb7f,

	SET_0_B = 0xcbc0,
	SET_0_C = 0xcbc1,
	SET_0_D = 0xcbc2,
	SET_0_E = 0xcbc3,
	SET_0_H = 0xcbc4,
	SET_0_L = 0xcbc5,
	SET_0_INDIRECT_HL = 0xcbc6,
	SET_0_A = 0xcbc7,
	SET_1_B = 0xcbc8,
	SET_1_C = 0xcbc9,
	SET_1_D = 0xcbca,
	SET_1_E = 0xcbcb,
	SET_1_H = 0xcbcc,
	SET_1_L = 0xcbcd,
	SET_1_INDIRECT_HL = 0xcbce,
	SET_1_A = 0xcbcf,
	SET_2_B = 0xcbd0,
	SET_2_C = 0xcbd1,
	SET_2_D = 0xcbd2,
	SET_2_E = 0xcbd3,
	SET_2_H = 0xcbd4,
	SET_2_L = 0xcbd5,
	SET_2_INDIRECT_HL = 0xcbd6,
	SET_2_A = 0xcbd7,
	SET_3_B = 0xcbd8,
	SET_3_C = 0xcbd9,
	SET_3_D = 0xcbda,
	SET_3_E = 0xcbdb,
	SET_3_H = 0xcbdc,
	SET_3_L = 0xcbdd,
	SET_3_INDIRECT_HL = 0xcbde,
	SET_3_A = 0xcbdf,
	SET_4_B = 0xcbe0,
	SET_4_C = 0xcbe1,
	SET_4_D = 0xcbe2,
	SET_4_E = 0xcbe3,
	SET_4_H = 0xcbe4,
	SET_4_L = 0xcbe5,
	SET_4_INDIRECT_HL = 0xcbe6,
	SET_4_A = 0xcbe7,
	SET_5_B = 0xcbe8,
	SET_5_C = 0xcbe9,
	SET_5_D = 0xcbea,
	SET_5_E = 0xcbeb,
	SET_5_H = 0xcbec,
	SET_5_L = 0xcbed,
	SET_5_INDIRECT_HL = 0xcbee,
	SET_5_A = 0xcbef,
	SET_6_B = 0xcbf0,
	SET_6_C = 0xcbf1,
	SET_6_D = 0xcbf2,
	SET_6_E = 0xcbf3,
	SET_6_H = 0xcbf4,
	SET_6_L = 0xcbf5,
	SET_6_INDIRECT_HL = 0xcbf6,
	SET_6_A = 0xcbf7,
	SET_7_B = 0xcbf8,
	SET_7_C = 0xcbf9,
	SET_7_D = 0xcbfa,
	SET_7_E = 0xcbfb,
	SET_7_H = 0xcbfc,
	SET_7_L = 0xcbfd,
	SET_7_INDIRECT_HL = 0xcbfe,
	SET_7_A = 0xcbff,

	RES_0_B = 0xcb80,
	RES_0_C = 0xcb81,
	RES_0_D = 0xcb82,
	RES_0_E = 0xcb83,
	RES_0_H = 0xcb84,
	RES_0_L = 0xcb85,
	RES_0_INDIRECT_HL = 0xcb86,
	RES_0_A = 0xcb87,
	RES_1_B = 0xcb88,
	RES_1_C = 0xcb89,
	RES_1_D = 0xcb8a,
	RES_1_E = 0xcb8b,
	RES_1_H = 0xcb8c,
	RES_1_L = 0xcb8d,
	RES_1_INDIRECT_HL = 0xcb8e,
	RES_1_A = 0xcb8f,
	RES_2_B = 0xcb90,
	RES_2_C = 0xcb91,
	RES_2_D = 0xcb92,
	RES_2_E = 0xcb93,
	RES_2_H = 0xcb94,
	RES_2_L = 0xcb95,
	RES_2_INDIRECT_HL = 0xcb96,
	RES_2_A = 0xcb97,
	RES_3_B = 0xcb98,
	RES_3_C = 0xcb99,
	RES_3_D = 0xcb9a,
	RES_3_E = 0xcb9b,
	RES_3_H = 0xcb9c,
	RES_3_L = 0xcb9d,
	RES_3_INDIRECT_HL = 0xcb9e,
	RES_3_A = 0xcb9f,
	RES_4_B = 0xcba0,
	RES_4_C = 0xcba1,
	RES_4_D = 0xcba2,
	RES_4_E = 0xcba3,
	RES_4_H = 0xcba4,
	RES_4_L = 0xcba5,
	RES_4_INDIRECT_HL = 0xcba6,
	RES_4_A = 0xcba7,
	RES_5_B = 0xcba8,
	RES_5_C = 0xcba9,
	RES_5_D = 0xcbaa,
	RES_5_E = 0xcbab,
	RES_5_H = 0xcbac,
	RES_5_L = 0xcbad,
	RES_5_INDIRECT_HL = 0xcbae,
	RES_5_A = 0xcbaf,
	RES_6_B = 0xcbb0,
	RES_6_C = 0xcbb1,
	RES_6_D = 0xcbb2,
	RES_6_E = 0xcbb3,
	RES_6_H = 0xcbb4,
	RES_6_L = 0xcbb5,
	RES_6_INDIRECT_HL = 0xcbb6,
	RES_6_A = 0xcbb7,
	RES_7_B = 0xcbb8,
	RES_7_C = 0xcbb9,
	RES_7_D = 0xcbba,
	RES_7_E = 0xcbbb,
	RES_7_H = 0xcbbc,
	RES_7_L = 0xcbbd,
	RES_7_INDIRECT_HL = 0xcbbe,
	RES_7_A = 0xcbbf,


	
	RC_B = 0xcb08,
	RC_C = 0xcb09,
	RC_D = 0xcb0a,
	RC_E = 0xcb0b,
	RC_H = 0xcb0c,
	RC_L = 0xcb0d,
	RC_INDIRECT_HL = 0xcb0e,
	RC_A = 0xcb0f,
	
	R_B = 0xcb18,
	R_C = 0xcb19,
	R_D = 0xcb1a,
	R_E = 0xcb1b,
	R_H = 0xcb1c,
	R_L = 0xcb1d,
	R_INDIRECT_HL = 0xcb1e,
	R_A = 0xcb1f,	
};

// IX instructions (DD)
enum TOpCodesIXInstructions : sf::Uint16
{
	/// 16-Bit Load Group
	/// -----------------
	PUSH_IX = 0xdde5,
	POP_IX = 0xdde1,


	/// Exchange, Block Transfer, and Search Group
	/// ----------------
	EX_INDIRECT_SP_IX = 0xdde3,


	/// 8-Bit Arithmetic Group
	/// ----------------
	AND_INDIRECT_IX_dis = 0xdda6,
	OR_INDIRECT_IX_dis = 0xddb6,
	XOR_INDIRECT_IX_dis = 0xddae,
	CP_INDIRECT_IX_dis = 0xddbe,


	/// 16-Bit Arithmetic Group
	/// ----------------
	ADD_IX_BC = 0xdd09,
	ADD_IX_DE = 0xdd19,
	ADD_IX_IX = 0xdd29,
	ADD_IX_SP = 0xdd39,
	ADD_A_INDIRECT_IX_dis = 0xdd86,
	ADC_A_INDIRECT_IX_dis = 0xdd8e,
	SBC_A_INDIRECT_IX_dis = 0xdd9e,
	INC_IX = 0xdd23,
	INC_INDIRECT_IX_dis = 0xdd34,
	DEC_IX = 0xdd2b,
	DEC_INDIRECT_IX_dis = 0xdd35,


	/// Bit Set, Reset, and Test Group
	/// ----------------
	IX_BIT_INSTRUCTIONS = 0x00dd, // see TOpCodesIXBitInstructions


	/// Jump Group
	/// ----------------
	JP_INDIRECT_IX = 0xdde9,

	
	LD_IX_n = 0xdd21,
	LD_INDIRECT_ADR_IX = 0xdd22,	
	LD_IX_INDIRECT_ADR = 0xdd2a,	
	LD_INDIRECT_IX_dis_n = 0xdd36,	
	LD_B_INDIRECT_IX_dis = 0xdd46,
	LD_C_INDIRECT_IX_dis = 0xdd4e,
	LD_D_INDIRECT_IX_dis = 0xdd56,
	LD_E_INDIRECT_IX_dis = 0xdd5e,
	LD_H_INDIRECT_IX_dis = 0xdd66,
	LD_L_INDIRECT_IX_dis = 0xdd6e,
	LD_INDIRECT_IX_dis_B = 0xdd70,
	LD_INDIRECT_IX_dis_C = 0xdd71,
	LD_INDIRECT_IX_dis_D = 0xdd72,
	LD_INDIRECT_IX_dis_E = 0xdd73,
	LD_INDIRECT_IX_dis_H = 0xdd74,
	LD_INDIRECT_IX_dis_L = 0xdd75,
	LD_INDIRECT_IX_dis_A = 0xdd77,
	LD_A_INDIRECT_IX_dis = 0xdd7e,	
	SUB_INDIRECT_IX_dis = 0xdd96,
	
	LD_SP_IX = 0xddf9,
};

// IX bit instructions (DDCB)
/*
enum BackupTOpCodesIXBitInstructions : sf::Uint16
{
	/// Rotate and Shift Group
	/// ----------------
	RLC_INDIRECT_IX_dis = 0x0006,


	/// Bit Set, Reset, and Test Group
	/// ----------------
	BIT_0_INDIRECT_IX_dis = 0x0046,
	BIT_1_INDIRECT_IX_dis = 0x004e,
	BIT_2_INDIRECT_IX_dis = 0x0056,
	BIT_3_INDIRECT_IX_dis = 0x005e,
	BIT_4_INDIRECT_IX_dis = 0x0066,
	BIT_5_INDIRECT_IX_dis = 0x006e,
	BIT_6_INDIRECT_IX_dis = 0x0076,
	BIT_7_INDIRECT_IX_dis = 0x007e,

	SET_0_INDIRECT_IX_dis = 0x00c6,
	SET_1_INDIRECT_IX_dis = 0x00ce,
	SET_2_INDIRECT_IX_dis = 0x00d6,
	SET_3_INDIRECT_IX_dis = 0x00de,
	SET_4_INDIRECT_IX_dis = 0x00e6,
	SET_5_INDIRECT_IX_dis = 0x00ee,
	SET_6_INDIRECT_IX_dis = 0x00f6,
	SET_7_INDIRECT_IX_dis = 0x00fe,

	RES_0_INDIRECT_IX_dis = 0x0086,
	RES_1_INDIRECT_IX_dis = 0x008e,
	RES_2_INDIRECT_IX_dis = 0x0096,
	RES_3_INDIRECT_IX_dis = 0x009e,
	RES_4_INDIRECT_IX_dis = 0x00a6,
	RES_5_INDIRECT_IX_dis = 0x00ae,
	RES_6_INDIRECT_IX_dis = 0x00b6,
	RES_7_INDIRECT_IX_dis = 0x00be,



	RL_INDIRECT_IX_dis = 0x0016,
	R_INDIRECT_IX_dis = 0x001e,
	RC_INDIRECT_IX_dis = 0x000e,

	

	SLA_INDIRECT_IX_dis = 0x0026,
	SRA_INDIRECT_IX_dis = 0x002e,
	SRL_INDIRECT_IX_dis = 0x003e,
};*/

enum TOpCodesIXBitInstructions : sf::Uint16
{
	/// Rotate and Shift Group
	/// ----------------
	RLC_INDIRECT_IX_dis = 0xDD06,


	/// Bit Set, Reset, and Test Group
	/// ----------------
	BIT_0_INDIRECT_IX_dis = 0xDD46,
	BIT_1_INDIRECT_IX_dis = 0xDD4e,
	BIT_2_INDIRECT_IX_dis = 0xDD56,
	BIT_3_INDIRECT_IX_dis = 0xDD5e,
	BIT_4_INDIRECT_IX_dis = 0xDD66,
	BIT_5_INDIRECT_IX_dis = 0xDD6e,
	BIT_6_INDIRECT_IX_dis = 0xDD76,
	BIT_7_INDIRECT_IX_dis = 0xDD7e,

	SET_0_INDIRECT_IX_dis = 0xDDc6,
	SET_1_INDIRECT_IX_dis = 0xDDce,
	SET_2_INDIRECT_IX_dis = 0xDDd6,
	SET_3_INDIRECT_IX_dis = 0xDDde,
	SET_4_INDIRECT_IX_dis = 0xDDe6,
	SET_5_INDIRECT_IX_dis = 0xDDee,
	SET_6_INDIRECT_IX_dis = 0xDDf6,
	SET_7_INDIRECT_IX_dis = 0xDDfe,

	RES_0_INDIRECT_IX_dis = 0xDD86,
	RES_1_INDIRECT_IX_dis = 0xDD8e,
	RES_2_INDIRECT_IX_dis = 0xDD96,
	RES_3_INDIRECT_IX_dis = 0xDD9e,
	RES_4_INDIRECT_IX_dis = 0xDDa6,
	RES_5_INDIRECT_IX_dis = 0xDDae,
	RES_6_INDIRECT_IX_dis = 0xDDb6,
	RES_7_INDIRECT_IX_dis = 0xDDbe,
	
	RL_INDIRECT_IX_dis = 0xDD16,
	R_INDIRECT_IX_dis =  0xDD1e,
	RC_INDIRECT_IX_dis = 0xDD0e,

	SLA_INDIRECT_IX_dis = 0xDD26,
	SRA_INDIRECT_IX_dis = 0xDD2e,
	SRL_INDIRECT_IX_dis = 0xDD3e,
};


// IY instructions (FD)
enum TOpCodesIYInstructions : sf::Uint16
{
	/// 16-Bit Load Group
	/// -----------------
	PUSH_IY = 0xfde5,
	POP_IY = 0xfde1,


	/// Exchange, Block Transfer, and Search Group
	/// ----------------
	EX_INDIRECT_SP_IY = 0xfde3,


	/// 8-Bit Arithmetic Group
	/// ----------------
	AND_INDIRECT_IY_dis = 0xfda6,
	OR_INDIRECT_IY_dis = 0xfdb6,
	XOR_INDIRECT_IY_dis = 0xfdae,
	CP_INDIRECT_IY_dis = 0xfdbe,

	/// 16-Bit Arithmetic Group
	/// ----------------
	ADD_IY_BC = 0xfd09,
	ADD_IY_DE = 0xfd19,
	ADD_IY_IY = 0xfd29,
	ADD_IY_SP = 0xfd39,
	ADD_A_INDIRECT_IY_dis = 0xfd86,
	ADC_A_INDIRECT_IY_dis = 0xfd8e,
	SBC_A_INDIRECT_IY_dis = 0xfd9e,
	INC_IY = 0xfd23,
	INC_INDIRECT_IY_dis = 0xfd34,
	DEC_IY = 0xfd2b,
	DEC_INDIRECT_IY_dis = 0xfd35,


	/// Bit Set, Reset, and Test Group
	/// ----------------
	IY_BIT_INSTRUCTIONS = 0x00dd, // see TOpCodesIYBitInstructions


	/// Jump Group
	/// ----------------
	JP_INDIRECT_IY = 0xfde9,

	
	LD_IY_n = 0xfd21,
	LD_INDIRECT_ADR_IY = 0xfd22,	
	LD_IY_INDIRECT_ADR = 0xfd2a,	
	LD_INDIRECT_IY_dis_n = 0xfd36,	
	LD_B_INDIRECT_IY_dis = 0xfd46,
	LD_C_INDIRECT_IY_dis = 0xfd4e,
	LD_D_INDIRECT_IY_dis = 0xfd56,
	LD_E_INDIRECT_IY_dis = 0xfd5e,
	LD_H_INDIRECT_IY_dis = 0xfd66,
	LD_L_INDIRECT_IY_dis = 0xfd6e,
	LD_INDIRECT_IY_dis_B = 0xfd70,
	LD_INDIRECT_IY_dis_C = 0xfd71,
	LD_INDIRECT_IY_dis_D = 0xfd72,
	LD_INDIRECT_IY_dis_E = 0xfd73,
	LD_INDIRECT_IY_dis_H = 0xfd74,
	LD_INDIRECT_IY_dis_L = 0xfd75,
	LD_INDIRECT_IY_dis_A = 0xfd77,
	LD_A_INDIRECT_IY_dis = 0xfd7e,
	SUB_INDIRECT_IY_dis = 0xfd96,	
	
	
	
	
	LD_SP_IY = 0xfdf9,
};

// IY bit instructions(FDCB)
/*
enum BackupTOpCodesIYBitInstructions : sf::Uint16
{
	/// Rotate and Shift Group
	/// ----------------
	RLC_INDIRECT_IY_dis = 0x0006,


	/// Bit Set, Reset, and Test Group
	/// ----------------
	BIT_0_INDIRECT_IY_dis = 0x0046,
	BIT_1_INDIRECT_IY_dis = 0x004e,
	BIT_2_INDIRECT_IY_dis = 0x0056,
	BIT_3_INDIRECT_IY_dis = 0x005e,
	BIT_4_INDIRECT_IY_dis = 0x0066,
	BIT_5_INDIRECT_IY_dis = 0x006e,
	BIT_6_INDIRECT_IY_dis = 0x0076,
	BIT_7_INDIRECT_IY_dis = 0x007e,

	SET_0_INDIRECT_IY_dis = 0x00c6,
	SET_1_INDIRECT_IY_dis = 0x00ce,
	SET_2_INDIRECT_IY_dis = 0x00d6,
	SET_3_INDIRECT_IY_dis = 0x00de,
	SET_4_INDIRECT_IY_dis = 0x00e6,
	SET_5_INDIRECT_IY_dis = 0x00ee,
	SET_6_INDIRECT_IY_dis = 0x00f6,
	SET_7_INDIRECT_IY_dis = 0x00fe,

	RES_0_INDIRECT_IY_dis = 0x0086,
	RES_1_INDIRECT_IY_dis = 0x008e,
	RES_2_INDIRECT_IY_dis = 0x0096,
	RES_3_INDIRECT_IY_dis = 0x009e,
	RES_4_INDIRECT_IY_dis = 0x00a6,
	RES_5_INDIRECT_IY_dis = 0x00ae,
	RES_6_INDIRECT_IY_dis = 0x00b6,
	RES_7_INDIRECT_IY_dis = 0x00be,


	RL_INDIRECT_IY_dis = 0x0016,
	R_INDIRECT_IY_dis = 0x001e,
	RC_INDIRECT_IY_dis = 0x000e,	
	SLA_INDIRECT_IY_dis = 0x0026,
	SRA_INDIRECT_IY_dis = 0x002e,
	SRL_INDIRECT_IY_dis = 0x003e,
};
*/

enum TOpCodesIYBitInstructions : sf::Uint16
{
	/// Rotate and Shift Group
	/// ----------------
	RLC_INDIRECT_IY_dis = 0xFD06,


	/// Bit Set, Reset, and Test Group
	/// ----------------
	BIT_0_INDIRECT_IY_dis = 0xFD46,
	BIT_1_INDIRECT_IY_dis = 0xFD4e,
	BIT_2_INDIRECT_IY_dis = 0xFD56,
	BIT_3_INDIRECT_IY_dis = 0xFD5e,
	BIT_4_INDIRECT_IY_dis = 0xFD66,
	BIT_5_INDIRECT_IY_dis = 0xFD6e,
	BIT_6_INDIRECT_IY_dis = 0xFD76,
	BIT_7_INDIRECT_IY_dis = 0xFD7e,

	SET_0_INDIRECT_IY_dis = 0xFDc6,
	SET_1_INDIRECT_IY_dis = 0xFDce,
	SET_2_INDIRECT_IY_dis = 0xFDd6,
	SET_3_INDIRECT_IY_dis = 0xFDde,
	SET_4_INDIRECT_IY_dis = 0xFDe6,
	SET_5_INDIRECT_IY_dis = 0xFDee,
	SET_6_INDIRECT_IY_dis = 0xFDf6,
	SET_7_INDIRECT_IY_dis = 0xFDfe,

	RES_0_INDIRECT_IY_dis = 0xFD86,
	RES_1_INDIRECT_IY_dis = 0xFD8e,
	RES_2_INDIRECT_IY_dis = 0xFD96,
	RES_3_INDIRECT_IY_dis = 0xFD9e,
	RES_4_INDIRECT_IY_dis = 0xFDa6,
	RES_5_INDIRECT_IY_dis = 0xFDae,
	RES_6_INDIRECT_IY_dis = 0xFDb6,
	RES_7_INDIRECT_IY_dis = 0xFDbe,


	RL_INDIRECT_IY_dis = 0xFD16,
	R_INDIRECT_IY_dis =  0xFD1e,
	RC_INDIRECT_IY_dis = 0xFD0e,
	SLA_INDIRECT_IY_dis = 0xFD26,
	SRA_INDIRECT_IY_dis = 0xFD2e,
	SRL_INDIRECT_IY_dis = 0xFD3e,
};

struct TInstruction
{
	TInstruction(const sf::Uint16& Size, const sf::Uint16& Position, const sf::Uint16& Code, const std::string& Name, const sf::Uint32& CodeNumber = 0) :
		InstructionSize(Size),
		InstructionPosition(Position),
		InstructionCode(Code),
		InstructionName(Name),
		InstructionCodeNumber(CodeNumber)
	{
	}

	bool TInstruction::operator ==(const sf::Uint16& Code) const
	{
		return InstructionCode == Code;
	}

	bool TInstruction::operator ==(const TInstruction& Compare) const
	{
		return Compare.InstructionCode == InstructionCode;
	}

	sf::Uint16	InstructionSize;
	sf::Uint16	InstructionPosition;
	sf::Uint16	InstructionCode;
	sf::Uint32	InstructionCodeNumber;
	std::string	InstructionName;
};

using TInstructionSet = std::vector<TInstruction>;

static TInstructionSet InstructionSet({
	{ 1, 0, ADC_A_INDIRECT_HL, "ADC A, (HL)" }, // 8E [0] {142}
	{ 3, 0, ADC_A_INDIRECT_IX_dis, "ADC A, (IX+dis)" }, // DD8E [1] {56718}
	{ 3, 0, ADC_A_INDIRECT_IY_dis, "ADC A, (IY+dis)" }, // FD8E [2] {64910}
	{ 1, 0, ADC_A_A, "ADC A, A" }, // 8F [3] {143}
	{ 1, 0, ADC_A_B, "ADC A, B" }, // 88 [4] {136}
	{ 1, 0, ADC_A_C, "ADC A, C" }, // 89 [5] {137}
	{ 1, 0, ADC_A_D, "ADC A, D" }, // 8A [6] {138}
	{ 1, 0, ADC_A_E, "ADC A, E" }, // 8B [7] {139}
	{ 1, 0, ADC_A_H, "ADC A, H" }, // 8C [8] {140}
	{ 1, 0, ADC_A_L, "ADC A, L" }, // 8D [9] {141}
	{ 2, 0, ADC_A_n, "ADC A, " }, // CE [10] {206}
	{ 2, 0, ADC_HL_BC, "ADC HL, BC" }, // ED4A [11] {60746}
	{ 2, 0, ADC_HL_DE, "ADC HL, DE" }, // ED5A [12] {60762}
	{ 2, 0, ADC_HL_HL, "ADC HL, HL" }, // ED6A [13] {60778}
	{ 2, 0, ADC_HL_SP, "ADC HL, SP" }, // ED7A [14] {60794}
	{ 1, 0, ADD_A_INDIRECT_HL, "ADD A, (HL)" }, // 86 [15] {134}
	{ 3, 0, ADD_A_INDIRECT_IX_dis, "ADD A, (IX+dis)" }, // DD86 [16] {56710}
	{ 3, 0, ADD_A_INDIRECT_IY_dis, "ADD A, (IY+dis)" }, // FD86 [17] {64902}
	{ 1, 0, ADD_A_A, "ADD A, A" }, // 87 [18] {135}
	{ 1, 0, ADD_A_B, "ADD A, B" }, // 80 [19] {128}
	{ 1, 0, ADD_A_C, "ADD A, C" }, // 81 [20] {129}
	{ 1, 0, ADD_A_D, "ADD A, D" }, // 82 [21] {130}
	{ 1, 0, ADD_A_E, "ADD A, E" }, // 83 [22] {131}
	{ 1, 0, ADD_A_H, "ADD A, H" }, // 84 [23] {132}
	{ 1, 0, ADD_A_L, "ADD A, L" }, // 85 [24] {133}
	{ 2, 0, ADD_A_n, "ADD A, " }, // C6 [25] {198}
	{ 1, 0, ADD_HL_BC, "ADD HL, BC" }, // 09 [26] {9}
	{ 1, 0, ADD_HL_DE, "ADD HL, DE" }, // 19 [27] {25}
	{ 1, 0, ADD_HL_HL, "ADD HL, HL" }, // 29 [28] {41}
	{ 1, 0, ADD_HL_SP, "ADD HL, SP" }, // 39 [29] {57}
	{ 2, 0, ADD_IX_BC, "ADD IX, BC" }, // DD09 [30] {56585}
	{ 2, 0, ADD_IX_DE, "ADD IX, DE" }, // DD19 [31] {56601}
	{ 2, 0, ADD_IX_IX, "ADD IX, IX" }, // DD29 [32] {56617}
	{ 2, 0, ADD_IX_SP, "ADD IX, SP" }, // DD39 [33] {56633}
	{ 2, 0, ADD_IY_BC, "ADD IY, BC" }, // FD09 [34] {64777}
	{ 2, 0, ADD_IY_DE, "ADD IY, DE" }, // FD19 [35] {64793}
	{ 2, 0, ADD_IY_IY, "ADD IY, IY" }, // FD29 [36] {64809}
	{ 2, 0, ADD_IY_SP, "ADD IY, SP" }, // FD39 [37] {64825}
	{ 1, 0, AND_INDIRECT_HL, "AND (HL)" }, // A6 [38] {166}
	{ 3, 0, AND_INDIRECT_IX_dis, "AND (IX+dis)" }, // DDA6 [39] {56742}
	{ 3, 0, AND_INDIRECT_IY_dis, "AND (IY+dis)" }, // FDA6 [40] {64934}
	{ 1, 0, AND_A, "AND A" }, // A7 [41] {167}
	{ 1, 0, AND_B, "AND B" }, // A0 [42] {160}
	{ 1, 0, AND_C, "AND C" }, // A1 [43] {161}
	{ 1, 0, AND_D, "AND D" }, // A2 [44] {162}
	{ 1, 0, AND_E, "AND E" }, // A3 [45] {163}
	{ 1, 0, AND_H, "AND H" }, // A4 [46] {164}
	{ 1, 0, AND_L, "AND L" }, // A5 [47] {165}
	{ 2, 0, AND_n, "AND n" }, // E6 [48] {230}
	{ 2, 0, BIT_0_INDIRECT_HL, "BIT 0, (HL)" }, // CB46 [49] {52038}
	{ 4, 0, BIT_0_INDIRECT_IX_dis, "BIT 0, (IX+dis)" }, // DDCB [50] {56779}
	{ 4, 0, BIT_0_INDIRECT_IY_dis, "BIT 0, (IY+dis)" }, // FDCB [51] {64971}
	{ 2, 0, BIT_0_A, "BIT 0, A" }, // CB47 [52] {52039}
	{ 2, 0, BIT_0_B, "BIT 0, B" }, // CB40 [53] {52032}
	{ 2, 0, BIT_0_C, "BIT 0, C" }, // CB41 [54] {52033}
	{ 2, 0, BIT_0_D, "BIT 0, D" }, // CB42 [55] {52034}
	{ 2, 0, BIT_0_E, "BIT 0, E" }, // CB43 [56] {52035}
	{ 2, 0, BIT_0_H, "BIT 0, H" }, // CB44 [57] {52036}
	{ 2, 0, BIT_0_L, "BIT 0, L" }, // CB45 [58] {52037}
	{ 2, 0, BIT_1_INDIRECT_HL, "BIT 1, (HL)" }, // CB4E [59] {52046}
	{ 4, 0, BIT_1_INDIRECT_IX_dis, "BIT 1, (IX+dis)" }, // DDCB [60] {56779}
	{ 4, 0, BIT_1_INDIRECT_IY_dis, "BIT 1, (IY+dis)" }, // FDCB [61] {64971}
	{ 2, 0, BIT_1_A, "BIT 1, A" }, // CB4F [62] {52047}
	{ 2, 0, BIT_1_B, "BIT 1, B" }, // CB48 [63] {52040}
	{ 2, 0, BIT_1_C, "BIT 1, C" }, // CB49 [64] {52041}
	{ 2, 0, BIT_1_D, "BIT 1, D" }, // CB4A [65] {52042}
	{ 2, 0, BIT_1_E, "BIT 1, E" }, // CB4B [66] {52043}
	{ 2, 0, BIT_1_H, "BIT 1, H" }, // CB4C [67] {52044}
	{ 2, 0, BIT_1_L, "BIT 1, L" }, // CB4D [68] {52045}
	{ 2, 0, BIT_2_INDIRECT_HL, "BIT 2, (HL)" }, // CB56 [69] {52054}
	{ 4, 0, BIT_2_INDIRECT_IX_dis, "BIT 2, (IX+dis)" }, // DDCB [70] {56779}
	{ 4, 0, BIT_2_INDIRECT_IY_dis, "BIT 2, (IY+dis)" }, // FDCB [71] {64971}
	{ 2, 0, BIT_2_A, "BIT 2, A" }, // CB57 [72] {52055}
	{ 2, 0, BIT_2_B, "BIT 2, B" }, // CB50 [73] {52048}
	{ 2, 0, BIT_2_C, "BIT 2, C" }, // CB51 [74] {52049}
	{ 2, 0, BIT_2_D, "BIT 2, D" }, // CB52 [75] {52050}
	{ 2, 0, BIT_2_E, "BIT 2, E" }, // CB53 [76] {52051}
	{ 2, 0, BIT_2_H, "BIT 2, H" }, // CB54 [77] {52052}
	{ 2, 0, BIT_2_L, "BIT 2, L" }, // CB55 [78] {52053}
	{ 2, 0, BIT_3_INDIRECT_HL, "BIT 3, (HL)" }, // CB5E [79] {52062}
	{ 4, 0, BIT_3_INDIRECT_IX_dis, "BIT 3, (IX+dis)" }, // DDCB [80] {56779}
	{ 4, 0, BIT_3_INDIRECT_IY_dis, "BIT 3, (IY+dis)" }, // FDCB [81] {64971}
	{ 2, 0, BIT_3_A, "BIT 3, A" }, // CB5F [82] {52063}
	{ 2, 0, BIT_3_B, "BIT 3, B" }, // CB58 [83] {52056}
	{ 2, 0, BIT_3_C, "BIT 3, C" }, // CB59 [84] {52057}
	{ 2, 0, BIT_3_D, "BIT 3, D" }, // CB5A [85] {52058}
	{ 2, 0, BIT_3_E, "BIT 3, E" }, // CB5B [86] {52059}
	{ 2, 0, BIT_3_H, "BIT 3, H" }, // CB5C [87] {52060}
	{ 2, 0, BIT_3_L, "BIT 3, L" }, // CB5D [88] {52061}
	{ 2, 0, BIT_4_INDIRECT_HL, "BIT 4, (HL)" }, // CB66 [89] {52070}
	{ 4, 0, BIT_4_INDIRECT_IX_dis, "BIT 4, (IX+dis)" }, // DDCB [90] {56779}
	{ 4, 0, BIT_4_INDIRECT_IY_dis, "BIT 4, (IY+dis)" }, // FDCB [91] {64971}
	{ 2, 0, BIT_4_A, "BIT 4, A" }, // CB67 [92] {52071}
	{ 2, 0, BIT_4_B, "BIT 4, B" }, // CB60 [93] {52064}
	{ 2, 0, BIT_4_C, "BIT 4, C" }, // CB61 [94] {52065}
	{ 2, 0, BIT_4_D, "BIT 4, D" }, // CB62 [95] {52066}
	{ 2, 0, BIT_4_E, "BIT 4, E" }, // CB63 [96] {52067}
	{ 2, 0, BIT_4_H, "BIT 4, H" }, // CB64 [97] {52068}
	{ 2, 0, BIT_4_L, "BIT 4, L" }, // CB65 [98] {52069}
	{ 2, 0, BIT_5_INDIRECT_HL, "BIT 5, (HL)" }, // CB6E [99] {52078}
	{ 4, 0, BIT_5_INDIRECT_IX_dis, "BIT 5, (IX+dis)" }, // DDCB [100] {56779}
	{ 4, 0, BIT_5_INDIRECT_IY_dis, "BIT 5, (IY+dis)" }, // FDCB [101] {64971}
	{ 2, 0, BIT_5_A, "BIT 5, A" }, // CB6F [102] {52079}
	{ 2, 0, BIT_5_B, "BIT 5, B" }, // CB68 [103] {52072}
	{ 2, 0, BIT_5_C, "BIT 5, C" }, // CB69 [104] {52073}
	{ 2, 0, BIT_5_D, "BIT 5, D" }, // CB6A [105] {52074}
	{ 2, 0, BIT_5_E, "BIT 5, E" }, // CB6B [106] {52075}
	{ 2, 0, BIT_5_H, "BIT 5, H" }, // CB6C [107] {52076}
	{ 2, 0, BIT_5_L, "BIT 5, L" }, // CB6D [108] {52077}
	{ 2, 0, BIT_6_INDIRECT_HL, "BIT 6, (HL)" }, // CB76 [109] {52086}
	{ 4, 0, BIT_6_INDIRECT_IX_dis, "BIT 6, (IX+dis)" }, // DDCB [110] {56779}
	{ 4, 0, BIT_6_INDIRECT_IY_dis, "BIT 6, (IY+dis)" }, // FDCB [111] {64971}
	{ 2, 0, BIT_6_A, "BIT 6, A" }, // CB77 [112] {52087}
	{ 2, 0, BIT_6_B, "BIT 6, B" }, // CB70 [113] {52080}
	{ 2, 0, BIT_6_C, "BIT 6, C" }, // CB71 [114] {52081}
	{ 2, 0, BIT_6_D, "BIT 6, D" }, // CB72 [115] {52082}
	{ 2, 0, BIT_6_E, "BIT 6, E" }, // CB73 [116] {52083}
	{ 2, 0, BIT_6_H, "BIT 6, H" }, // CB74 [117] {52084}
	{ 2, 0, BIT_6_L, "BIT 6, L" }, // CB75 [118] {52085}
	{ 2, 0, BIT_7_INDIRECT_HL, "BIT 7, (HL)" }, // CB7E [119] {52094}
	{ 4, 0, BIT_7_INDIRECT_IX_dis, "BIT 7, (IX+dis)" }, // DDCB [120] {56779}
	{ 4, 0, BIT_7_INDIRECT_IY_dis, "BIT 7, (IY+dis)" }, // FDCB [121] {64971}
	{ 2, 0, BIT_7_A, "BIT 7, A" }, // CB7F [122] {52095}
	{ 2, 0, BIT_7_B, "BIT 7, B" }, // CB78 [123] {52088}
	{ 2, 0, BIT_7_C, "BIT 7, C" }, // CB79 [124] {52089}
	{ 2, 0, BIT_7_D, "BIT 7, D" }, // CB7A [125] {52090}
	{ 2, 0, BIT_7_E, "BIT 7, E" }, // CB7B [126] {52091}
	{ 2, 0, BIT_7_H, "BIT 7, H" }, // CB7C [127] {52092}
	{ 2, 0, BIT_7_L, "BIT 7, L" }, // CB7D [128] {52093}
	{ 3, 0, CALL_C_ADR, "CALL C, " }, // DC [129] {220}
	{ 3, 0, CALL_M_ADR, "CALL M, " }, // FC [130] {252}
	{ 3, 0, CALL_NC_ADR, "CALL NC, " }, // D4 [131] {212}
	{ 3, 0, CALL_NZ_ADR, "CALL NZ, " }, // C4 [132] {196}
	{ 3, 0, CALL_P_ADR, "CALL P, " }, // F4 [133] {244}
	{ 3, 0, CALL_PE_ADR, "CALL PE, " }, // EC [134] {236}
	{ 3, 0, CALL_PO_ADR, "CALL PO, " }, // E4 [135] {228}
	{ 3, 0, CALL_ADR, "CALL " }, // CD [136] {205}
	{ 3, 0, CALL_Z_ADR, "CALL Z, " }, // CC [137] {204}
	{ 1, 0, CCF, "CCF" }, // 3F [138] {63}
	{ 1, 0, CP_INDIRECT_HL, "CP (HL)" }, // BE [139] {190}
	{ 3, 0, CP_INDIRECT_IX_dis, "CP (IX+dis)" }, // DDBE [140] {56766}
	{ 3, 0, CP_INDIRECT_IY_dis, "CP (IY+dis)" }, // FDBE [141] {64958}
	{ 1, 0, CP_A, "CP A" }, // BF [142] {191}
	{ 1, 0, CP_B, "CP B" }, // B8 [143] {184}
	{ 1, 0, CP_C, "CP C" }, // B9 [144] {185}
	{ 1, 0, CP_D, "CP D" }, // BA [145] {186}
	{ 1, 0, CP_E, "CP E" }, // BB [146] {187}
	{ 1, 0, CP_H, "CP H" }, // BC [147] {188}
	{ 1, 0, CP_L, "CP L" }, // BD [148] {189}
	{ 2, 0, CP_n, "CP n" }, // FE [149] {254}
	{ 2, 0, CPD, "CPD" }, // EDA9 [150] {60841}
	{ 2, 0, CPDR, "CPDR" }, // EDB9 [151] {60857}
	{ 2, 0, CPI, "CPI" }, // EDA1 [152] {60833}
	{ 2, 0, CPIR, "CPIR" }, // EDB1 [153] {60849}
	{ 1, 0, CPL, "CPL" }, // 2F [154] {47}
	{ 1, 0, DAA, "DAA" }, // 27 [155] {39}
	{ 1, 0, DEC_INDIRECT_HL, "DEC (HL)" }, // 35 [156] {53}
	{ 3, 0, DEC_INDIRECT_IX_dis, "DEC (IX+dis)" }, // DD35 [157] {56629}
	{ 3, 0, DEC_INDIRECT_IY_dis, "DEC (IY+dis)" }, // FD35 [158] {64821}
	{ 1, 0, DEC_A, "DEC A" }, // 3D [159] {61}
	{ 1, 0, DEC_B, "DEC B" }, // 05 [160] {5}
	{ 1, 0, DEC_BC, "DEC BC" }, // 0B [161] {11}
	{ 1, 0, DEC_C, "DEC C" }, // 0D [162] {13}
	{ 1, 0, DEC_D, "DEC D" }, // 15 [163] {21}
	{ 1, 0, DEC_DE, "DEC DE" }, // 1B [164] {27}
	{ 1, 0, DEC_E, "DEC E" }, // 1D [165] {29}
	{ 1, 0, DEC_H, "DEC H" }, // 25 [166] {37}
	{ 1, 0, DEC_HL, "DEC HL" }, // 2B [167] {43}
	{ 2, 0, DEC_IX, "DEC IX" }, // DD2B [168] {56619}
	{ 2, 0, DEC_IY, "DEC IY" }, // FD2B [169] {64811}
	{ 1, 0, DEC_L, "DEC L" }, // 2D [170] {45}
	{ 1, 0, DEC_SP, "DEC SP" }, // 3B [171] {59}
	{ 1, 0, DI, "DI" }, // F3 [172] {243}
	{ 2, 0, DJNZ_dis, "DJNZ dis" }, // 10 [173] {16}
	{ 1, 0, EI, "EI" }, // FB [174] {251}
	{ 1, 0, EX_INDIRECT_SP_HL, "EX (SP), HL" }, // E3 [175] {227}
	{ 2, 0, EX_INDIRECT_SP_IX, "EX (SP), IX" }, // DDE3 [176] {56803}
	{ 2, 0, EX_INDIRECT_SP_IY, "EX (SP), IY" }, // FDE3 [177] {64995}
	{ 1, 0, EX_AF_AF, "EX AF, AF" }, // 08 [178] {8}
	{ 1, 0, EX_DE_HL, "EX DE, HL" }, // EB [179] {235}
	{ 1, 0, EXX, "EXX" }, // D9 [180] {217}
	{ 1, 0, HALT, "HALT" }, // 76 [181] {118}
	{ 2, 0, IM_0, "IM 0" }, // ED46 [182] {60742}
	{ 2, 0, IM_1, "IM 1" }, // ED56 [183] {60758}
	{ 2, 0, IM_2, "IM 2" }, // ED5E [184] {60766}
	{ 2, 0, IN_A_INDIRECT_C, "IN A, (C)" }, // ED78 [185] {60792}
	{ 2, 0, IN_A_INDIRECT_port, "IN A, (port)" }, // DB [186] {219}
	{ 2, 0, IN_B_INDIRECT_C, "IN B, (C)" }, // ED40 [187] {60736}
	{ 2, 0, IN_C_INDIRECT_C, "IN C, (C)" }, // ED48 [188] {60744}
	{ 2, 0, IN_D_INDIRECT_C, "IN D, (C)" }, // ED50 [189] {60752}
	{ 2, 0, IN_E_INDIRECT_C, "IN E, (C)" }, // ED58 [190] {60760}
	{ 2, 0, IN_H_INDIRECT_C, "IN H, (C)" }, // ED60 [191] {60768}
	{ 2, 0, IN_L_INDIRECT_C, "IN L, (C)" }, // ED68 [192] {60776}
	{ 1, 0, INC_INDIRECT_HL, "INC (HL)" }, // 34 [193] {52}
	{ 3, 0, INC_INDIRECT_IX_dis, "INC (IX+dis)" }, // DD34 [194] {56628}
	{ 3, 0, INC_INDIRECT_IY_dis, "INC (IY+dis)" }, // FD34 [195] {64820}
	{ 1, 0, INC_A, "INC A" }, // 3C [196] {60}
	{ 1, 0, INC_B, "INC B" }, // 04 [197] {4}
	{ 1, 0, INC_BC, "INC BC" }, // 03 [198] {3}
	{ 1, 0, INC_C, "INC C" }, // 0C [199] {12}
	{ 1, 0, INC_D, "INC D" }, // 14 [200] {20}
	{ 1, 0, INC_DE, "INC DE" }, // 13 [201] {19}
	{ 1, 0, INC_E, "INC E" }, // 1C [202] {28}
	{ 1, 0, INC_H, "INC H" }, // 24 [203] {36}
	{ 1, 0, INC_HL, "INC HL" }, // 23 [204] {35}
	{ 2, 0, INC_IX, "INC IX" }, // DD23 [205] {56611}
	{ 2, 0, INC_IY, "INC IY" }, // FD23 [206] {64803}
	{ 1, 0, INC_L, "INC L" }, // 2C [207] {44}
	{ 1, 0, INC_SP, "INC SP" }, // 33 [208] {51}
	{ 2, 0, IND, "IND" }, // EDAA [209] {60842}
	{ 2, 0, INDR, "INDR" }, // EDBA [210] {60858}
	{ 2, 0, INI, "INI" }, // EDA2 [211] {60834}
	{ 2, 0, INIR, "INIR" }, // EDB2 [212] {60850}
	{ 1, 0, JP_INDIRECT_HL, "JP (HL)" }, // E9 [213] {233}
	{ 2, 0, JP_INDIRECT_IX, "JP (IX)" }, // DDE9 [214] {56809}
	{ 2, 0, JP_INDIRECT_IY, "JP (IY)" }, // FDE9 [215] {65001}
	{ 3, 0, JP_C_ADR, "JP C, " }, // DA [216] {218}
	{ 3, 0, JP_M_ADR, "JP M, " }, // FA [217] {250}
	{ 3, 0, JP_NC_ADR, "JP NC, " }, // D2 [218] {210}
	{ 3, 0, JP_NZ_ADR, "JP NZ, " }, // C2 [219] {194}
	{ 3, 0, JP_P_ADR, "JP P, " }, // F2 [220] {242}
	{ 3, 0, JP_PE_ADR, "JP PE, " }, // EA [221] {234}
	{ 3, 0, JP_PO_ADR, "JP PO, " }, // E2 [222] {226}
	{ 3, 0, JP_ADR, "JP " }, // C3 [223] {195}
	{ 3, 0, JP_Z_ADR, "JP Z, " }, // CA [224] {202}
	{ 2, 0, JR_C_dis, "JR C, dis" }, // 38 [225] {56}
	{ 2, 0, JR_NC_dis, "JR NC, dis" }, // 30 [226] {48}
	{ 2, 0, JR_NZ_dis, "JR NZ, dis" }, // 20 [227] {32}
	{ 2, 0, JR_dis, "JR dis" }, // 18 [228] {24}
	{ 2, 0, JR_Z_dis, "JR Z, dis" }, // 28 [229] {40}
	{ 1, 0, LD_INDIRECT_BC_A, "LD (BC), A" }, // 02 [230] {2}
	{ 1, 0, LD_INDIRECT_DE_A, "LD (DE), A" }, // 12 [231] {18}
	{ 1, 0, LD_INDIRECT_HL_A, "LD (HL), A" }, // 77 [232] {119}
	{ 1, 0, LD_INDIRECT_HL_B, "LD (HL), B" }, // 70 [233] {112}
	{ 1, 0, LD_INDIRECT_HL_C, "LD (HL), C" }, // 71 [234] {113}
	{ 1, 0, LD_INDIRECT_HL_D, "LD (HL), D" }, // 72 [235] {114}
	{ 1, 0, LD_INDIRECT_HL_E, "LD (HL), E" }, // 73 [236] {115}
	{ 1, 0, LD_INDIRECT_HL_H, "LD (HL), H" }, // 74 [237] {116}
	{ 1, 0, LD_INDIRECT_HL_L, "LD (HL), L" }, // 75 [238] {117}
	{ 2, 0, LD_INDIRECT_HL_n, "LD (HL), " }, // 36 [239] {54}
	{ 3, 0, LD_INDIRECT_IX_dis_A, "LD (IX+dis), A" }, // DD77 [240] {56695}
	{ 3, 0, LD_INDIRECT_IX_dis_B, "LD (IX+dis), B" }, // DD70 [241] {56688}
	{ 3, 0, LD_INDIRECT_IX_dis_C, "LD (IX+dis), C" }, // DD71 [242] {56689}
	{ 3, 0, LD_INDIRECT_IX_dis_D, "LD (IX+dis), D" }, // DD72 [243] {56690}
	{ 3, 0, LD_INDIRECT_IX_dis_E, "LD (IX+dis), E" }, // DD73 [244] {56691}
	{ 3, 0, LD_INDIRECT_IX_dis_H, "LD (IX+dis), H" }, // DD74 [245] {56692}
	{ 3, 0, LD_INDIRECT_IX_dis_L, "LD (IX+dis), L" }, // DD75 [246] {56693}
	{ 4, 0, LD_INDIRECT_IX_dis_n, "LD (IX+dis), " }, // DD36 [247] {56630}
	{ 3, 0, LD_INDIRECT_IY_dis_A, "LD (IY+dis), A" }, // FD77 [248] {64887}
	{ 3, 0, LD_INDIRECT_IY_dis_B, "LD (IY+dis), B" }, // FD70 [249] {64880}
	{ 3, 0, LD_INDIRECT_IY_dis_C, "LD (IY+dis), C" }, // FD71 [250] {64881}
	{ 3, 0, LD_INDIRECT_IY_dis_D, "LD (IY+dis), D" }, // FD72 [251] {64882}
	{ 3, 0, LD_INDIRECT_IY_dis_E, "LD (IY+dis), E" }, // FD73 [252] {64883}
	{ 3, 0, LD_INDIRECT_IY_dis_H, "LD (IY+dis), H" }, // FD74 [253] {64884}
	{ 3, 0, LD_INDIRECT_IY_dis_L, "LD (IY+dis), L" }, // FD75 [254] {64885}
	{ 4, 0, LD_INDIRECT_IY_dis_n, "LD (IY+dis), " }, // FD36 [255] {64822}
	{ 3, 0, LD_INDIRECT_ADR_A, "LD (), A" }, // 32 [256] {50}
	{ 4, 0, LD_INDIRECT_ADR_BC, "LD (), BC" }, // ED43 [257] {60739}
	{ 4, 0, LD_INDIRECT_ADR_DE, "LD (), DE" }, // ED53 [258] {60755}
	{ 3, 0, LD_INDIRECT_ADR_HL, "LD (), HL" }, // 22 [259] {34}
	{ 4, 0, LD_INDIRECT_ADR_IX, "LD (), IX" }, // DD22 [260] {56610}
	{ 4, 0, LD_INDIRECT_ADR_IY, "LD (), IY" }, // FD22 [261] {64802}
	{ 4, 0, LD_INDIRECT_ADR_SP, "LD (), SP" }, // ED73 [262] {60787}
	{ 1, 0, LD_A_INDIRECT_BC, "LD A, (BC)" }, // 0A [263] {10}
	{ 1, 0, LD_A_INDIRECT_DE, "LD A, (DE)" }, // 1A [264] {26}
	{ 1, 0, LD_A_INDIRECT_HL, "LD A, (HL)" }, // 7E [265] {126}
	{ 3, 0, LD_A_INDIRECT_IX_dis, "LD A, (IX+dis)" }, // DD7E [266] {56702}
	{ 3, 0, LD_A_INDIRECT_IY_dis, "LD A, (IY+dis)" }, // FD7E [267] {64894}
	{ 3, 0, LD_A_INDIRECT_ADR, "LD A, ()" }, // 3A [268] {58}
	{ 1, 0, LD_A_A, "LD A, A" }, // 7F [269] {127}
	{ 1, 0, LD_A_B, "LD A, B" }, // 78 [270] {120}
	{ 1, 0, LD_A_C, "LD A, C" }, // 79 [271] {121}
	{ 1, 0, LD_A_D, "LD A, D" }, // 7A [272] {122}
	{ 1, 0, LD_A_E, "LD A, E" }, // 7B [273] {123}
	{ 1, 0, LD_A_H, "LD A, H" }, // 7C [274] {124}
	{ 2, 0, LD_A_I, "LD A, I" }, // ED57 [275] {60759}
	{ 1, 0, LD_A_L, "LD A, L" }, // 7D [276] {125}
	{ 2, 0, LD_A_R, "LD A, R" }, // ED5F [277] {60767}
	{ 2, 0, LD_A_n, "LD A, " }, // 3E [278] {62}
	{ 1, 0, LD_B_INDIRECT_HL, "LD B, (HL)" }, // 46 [279] {70}
	{ 3, 0, LD_B_INDIRECT_IX_dis, "LD B, (IX+dis)" }, // DD46 [280] {56646}
	{ 3, 0, LD_B_INDIRECT_IY_dis, "LD B, (IY+dis)" }, // FD46 [281] {64838}
	{ 1, 0, LD_B_A, "LD B, A" }, // 47 [282] {71}
	{ 1, 0, LD_B_B, "LD B, B" }, // 40 [283] {64}
	{ 1, 0, LD_B_C, "LD B, C" }, // 41 [284] {65}
	{ 1, 0, LD_B_D, "LD B, D" }, // 42 [285] {66}
	{ 1, 0, LD_B_E, "LD B, E" }, // 43 [286] {67}
	{ 1, 0, LD_B_H, "LD B, H" }, // 44 [287] {68}
	{ 1, 0, LD_B_L, "LD B, L" }, // 45 [288] {69}
	{ 2, 0, LD_B_n, "LD B, " }, // 06 [289] {6}
	{ 4, 0, LD_BC_INDIRECT_ADR, "LD BC, ()" }, // ED4B [290] {60747}
	{ 3, 0, LD_BC_n, "LD BC, " }, // 01 [291] {1}
	{ 1, 0, LD_C_INDIRECT_HL, "LD C, (HL)" }, // 4E [292] {78}
	{ 3, 0, LD_C_INDIRECT_IX_dis, "LD C, (IX+dis)" }, // DD4E [293] {56654}
	{ 3, 0, LD_C_INDIRECT_IY_dis, "LD C, (IY+dis)" }, // FD4E [294] {64846}
	{ 1, 0, LD_C_A, "LD C, A" }, // 4F [295] {79}
	{ 1, 0, LD_C_B, "LD C, B" }, // 48 [296] {72}
	{ 1, 0, LD_C_C, "LD C, C" }, // 49 [297] {73}
	{ 1, 0, LD_C_D, "LD C, D" }, // 4A [298] {74}
	{ 1, 0, LD_C_E, "LD C, E" }, // 4B [299] {75}
	{ 1, 0, LD_C_H, "LD C, H" }, // 4C [300] {76}
	{ 1, 0, LD_C_L, "LD C, L" }, // 4D [301] {77}
	{ 2, 0, LD_C_n, "LD C, " }, // 0E [302] {14}
	{ 1, 0, LD_D_INDIRECT_HL, "LD D, (HL)" }, // 56 [303] {86}
	{ 3, 0, LD_D_INDIRECT_IX_dis, "LD D, (IX+dis)" }, // DD56 [304] {56662}
	{ 3, 0, LD_D_INDIRECT_IY_dis, "LD D, (IY+dis)" }, // FD56 [305] {64854}
	{ 1, 0, LD_D_A, "LD D, A" }, // 57 [306] {87}
	{ 1, 0, LD_D_B, "LD D, B" }, // 50 [307] {80}
	{ 1, 0, LD_D_C, "LD D, C" }, // 51 [308] {81}
	{ 1, 0, LD_D_D, "LD D, D" }, // 52 [309] {82}
	{ 1, 0, LD_D_E, "LD D, E" }, // 53 [310] {83}
	{ 1, 0, LD_D_H, "LD D, H" }, // 54 [311] {84}
	{ 1, 0, LD_D_L, "LD D, L" }, // 55 [312] {85}
	{ 2, 0, LD_D_n, "LD D, " }, // 16 [313] {22}
	{ 4, 0, LD_DE_INDIRECT_ADR, "LD DE, ()" }, // ED5B [314] {60763}
	{ 3, 0, LD_DE_n, "LD DE, " }, // 11 [315] {17}
	{ 1, 0, LD_E_INDIRECT_HL, "LD E, (HL)" }, // 5E [316] {94}
	{ 3, 0, LD_E_INDIRECT_IX_dis, "LD E, (IX+dis)" }, // DD5E [317] {56670}
	{ 3, 0, LD_E_INDIRECT_IY_dis, "LD E, (IY+dis)" }, // FD5E [318] {64862}
	{ 1, 0, LD_E_A, "LD E, A" }, // 5F [319] {95}
	{ 1, 0, LD_E_B, "LD E, B" }, // 58 [320] {88}
	{ 1, 0, LD_E_C, "LD E, C" }, // 59 [321] {89}
	{ 1, 0, LD_E_D, "LD E, D" }, // 5A [322] {90}
	{ 1, 0, LD_E_E, "LD E, E" }, // 5B [323] {91}
	{ 1, 0, LD_E_H, "LD E, H" }, // 5C [324] {92}
	{ 1, 0, LD_E_L, "LD E, L" }, // 5D [325] {93}
	{ 2, 0, LD_E_n, "LD E, " }, // 1E [326] {30}
	{ 1, 0, LD_H_INDIRECT_HL, "LD H, (HL)" }, // 66 [327] {102}
	{ 3, 0, LD_H_INDIRECT_IX_dis, "LD H, (IX+dis)" }, // DD66 [328] {56678}
	{ 3, 0, LD_H_INDIRECT_IY_dis, "LD H, (IY+dis)" }, // FD66 [329] {64870}
	{ 1, 0, LD_H_A, "LD H, A" }, // 67 [330] {103}
	{ 1, 0, LD_H_B, "LD H, B" }, // 60 [331] {96}
	{ 1, 0, LD_H_C, "LD H, C" }, // 61 [332] {97}
	{ 1, 0, LD_H_D, "LD H, D" }, // 62 [333] {98}
	{ 1, 0, LD_H_E, "LD H, E" }, // 63 [334] {99}
	{ 1, 0, LD_H_H, "LD H, H" }, // 64 [335] {100}
	{ 1, 0, LD_H_L, "LD H, L" }, // 65 [336] {101}
	{ 2, 0, LD_H_n, "LD H, " }, // 26 [337] {38}
	{ 3, 0, LD_HL_INDIRECT_ADR, "LD HL, ()" }, // 2A [338] {42}
	{ 3, 0, LD_HL_n, "LD HL, " }, // 21 [339] {33}
	{ 2, 0, LD_I_A, "LD I, A" }, // ED47 [340] {60743}
	{ 4, 0, LD_IX_INDIRECT_ADR, "LD IX, ()" }, // DD2A [341] {56618}
	{ 4, 0, LD_IX_n, "LD IX, " }, // DD21 [342] {56609}
	{ 4, 0, LD_IY_INDIRECT_ADR, "LD IY, ()" }, // FD2A [343] {64810}
	{ 4, 0, LD_IY_n, "LD IY, " }, // FD21 [344] {64801}
	{ 1, 0, LD_L_INDIRECT_HL, "LD L, (HL)" }, // 6E [345] {110}
	{ 3, 0, LD_L_INDIRECT_IX_dis, "LD L, (IX+dis)" }, // DD6E [346] {56686}
	{ 3, 0, LD_L_INDIRECT_IY_dis, "LD L, (IY+dis)" }, // FD6E [347] {64878}
	{ 1, 0, LD_L_A, "LD L, A" }, // 6F [348] {111}
	{ 1, 0, LD_L_B, "LD L, B" }, // 68 [349] {104}
	{ 1, 0, LD_L_C, "LD L, C" }, // 69 [350] {105}
	{ 1, 0, LD_L_D, "LD L, D" }, // 6A [351] {106}
	{ 1, 0, LD_L_E, "LD L, E" }, // 6B [352] {107}
	{ 1, 0, LD_L_H, "LD L, H" }, // 6C [353] {108}
	{ 1, 0, LD_L_L, "LD L, L" }, // 6D [354] {109}
	{ 2, 0, LD_L_n, "LD L, " }, // 2E [355] {46}
	{ 2, 0, LD_R_A, "LD R, A" }, // ED4F [356] {60751}
	{ 4, 0, LD_SP_INDIRECT_ADR, "LD SP, ()" }, // ED7B [357] {60795}
	{ 1, 0, LD_SP_HL, "LD SP, HL" }, // F9 [358] {249}
	{ 2, 0, LD_SP_IX, "LD SP, IX" }, // DDF9 [359] {56825}
	{ 2, 0, LD_SP_IY, "LD SP, IY" }, // FDF9 [360] {65017}
	{ 3, 0, LD_SP_n, "LD SP, " }, // 31 [361] {49}
	{ 2, 0, LDD, "LDD" }, // EDA8 [362] {60840}
	{ 2, 0, LDDR, "LDDR" }, // EDB8 [363] {60856}
	{ 2, 0, LDI, "LDI" }, // EDA0 [364] {60832}
	{ 2, 0, LDIR, "LDIR" }, // EDB0 [365] {60848}
	{ 2, 0, NEG, "NEG" }, // ED44 [366] {60740}
	{ 1, 0, NOP, "NOP" }, // 00 [367] {0}
	{ 1, 0, OR_INDIRECT_HL, "OR (HL)" }, // B6 [368] {182}
	{ 3, 0, OR_INDIRECT_IX_dis, "OR (IX+dis)" }, // DDB6 [369] {56758}
	{ 3, 0, OR_INDIRECT_IY_dis, "OR (IY+dis)" }, // FDB6 [370] {64950}
	{ 1, 0, OR_A, "OR A" }, // B7 [371] {183}
	{ 1, 0, OR_B, "OR B" }, // B0 [372] {176}
	{ 1, 0, OR_C, "OR C" }, // B1 [373] {177}
	{ 1, 0, OR_D, "OR D" }, // B2 [374] {178}
	{ 1, 0, OR_E, "OR E" }, // B3 [375] {179}
	{ 1, 0, OR_H, "OR H" }, // B4 [376] {180}
	{ 1, 0, OR_L, "OR L" }, // B5 [377] {181}
	{ 2, 0, OR_n, "OR n" }, // F6 [378] {246}
	{ 2, 0, OTDR, "OTDR" }, // EDBB [379] {60859}
	{ 2, 0, OTIR, "OTIR" }, // EDB3 [380] {60851}
	{ 2, 0, OUT_INDIRECT_C_A, "OUT (C), A" }, // ED79 [381] {60793}
	{ 2, 0, OUT_INDIRECT_C_B, "OUT (C), B" }, // ED41 [382] {60737}
	{ 2, 0, OUT_INDIRECT_C_C, "OUT (C), C" }, // ED49 [383] {60745}
	{ 2, 0, OUT_INDIRECT_C_D, "OUT (C), D" }, // ED51 [384] {60753}
	{ 2, 0, OUT_INDIRECT_C_E, "OUT (C), E" }, // ED59 [385] {60761}
	{ 2, 0, OUT_INDIRECT_C_H, "OUT (C), H" }, // ED61 [386] {60769}
	{ 2, 0, OUT_INDIRECT_C_L, "OUT (C), L" }, // ED69 [387] {60777}
	{ 2, 0, OUT_INDIRECT_port_A, "OUT (port), A" }, // D3 [388] {211}
	{ 2, 0, OUTD, "OUTD" }, // EDAB [389] {60843}
	{ 2, 0, OUTI, "OUTI" }, // EDA3 [390] {60835}
	{ 1, 0, POP_AF, "POP AF" }, // F1 [391] {241}
	{ 1, 0, POP_BC, "POP BC" }, // C1 [392] {193}
	{ 1, 0, POP_DE, "POP DE" }, // D1 [393] {209}
	{ 1, 0, POP_HL, "POP HL" }, // E1 [394] {225}
	{ 2, 0, POP_IX, "POP IX" }, // DDE1 [395] {56801}
	{ 2, 0, POP_IY, "POP IY" }, // FDE1 [396] {64993}
	{ 1, 0, PUSH_AF, "PUSH AF" }, // F5 [397] {245}
	{ 1, 0, PUSH_BC, "PUSH BC" }, // C5 [398] {197}
	{ 1, 0, PUSH_DE, "PUSH DE" }, // D5 [399] {213}
	{ 1, 0, PUSH_HL, "PUSH HL" }, // E5 [400] {229}
	{ 2, 0, PUSH_IX, "PUSH IX" }, // DDE5 [401] {56805}
	{ 2, 0, PUSH_IY, "PUSH IY" }, // FDE5 [402] {64997}
	{ 2, 0, RES_0_INDIRECT_HL, "RES 0, (HL)" }, // CB86 [403] {52102}
	{ 4, 0, RES_0_INDIRECT_IX_dis, "RES 0, (IX+dis)" }, // DDCB [404] {56779}
	{ 4, 0, RES_0_INDIRECT_IY_dis, "RES 0, (IY+dis)" }, // FDCB [405] {64971}
	{ 2, 0, RES_0_A, "RES 0, A" }, // CB87 [406] {52103}
	{ 2, 0, RES_0_B, "RES 0, B" }, // CB80 [407] {52096}
	{ 2, 0, RES_0_C, "RES 0, C" }, // CB81 [408] {52097}
	{ 2, 0, RES_0_D, "RES 0, D" }, // CB82 [409] {52098}
	{ 2, 0, RES_0_E, "RES 0, E" }, // CB83 [410] {52099}
	{ 2, 0, RES_0_H, "RES 0, H" }, // CB84 [411] {52100}
	{ 2, 0, RES_0_L, "RES 0, L" }, // CB85 [412] {52101}
	{ 2, 0, RES_1_INDIRECT_HL, "RES 1, (HL)" }, // CB8E [413] {52110}
	{ 4, 0, RES_1_INDIRECT_IX_dis, "RES 1, (IX+dis)" }, // DDCB [414] {56779}
	{ 4, 0, RES_1_INDIRECT_IY_dis, "RES 1, (IY+dis)" }, // FDCB [415] {64971}
	{ 2, 0, RES_1_A, "RES 1, A" }, // CB8F [416] {52111}
	{ 2, 0, RES_1_B, "RES 1, B" }, // CB88 [417] {52104}
	{ 2, 0, RES_1_C, "RES 1, C" }, // CB89 [418] {52105}
	{ 2, 0, RES_1_D, "RES 1, D" }, // CB8A [419] {52106}
	{ 2, 0, RES_1_E, "RES 1, E" }, // CB8B [420] {52107}
	{ 2, 0, RES_1_H, "RES 1, H" }, // CB8C [421] {52108}
	{ 2, 0, RES_1_L, "RES 1, L" }, // CB8D [422] {52109}
	{ 2, 0, RES_2_INDIRECT_HL, "RES 2, (HL)" }, // CB96 [423] {52118}
	{ 4, 0, RES_2_INDIRECT_IX_dis, "RES 2, (IX+dis)" }, // DDCB [424] {56779}
	{ 4, 0, RES_2_INDIRECT_IY_dis, "RES 2, (IY+dis)" }, // FDCB [425] {64971}
	{ 2, 0, RES_2_A, "RES 2, A" }, // CB97 [426] {52119}
	{ 2, 0, RES_2_B, "RES 2, B" }, // CB90 [427] {52112}
	{ 2, 0, RES_2_C, "RES 2, C" }, // CB91 [428] {52113}
	{ 2, 0, RES_2_D, "RES 2, D" }, // CB92 [429] {52114}
	{ 2, 0, RES_2_E, "RES 2, E" }, // CB93 [430] {52115}
	{ 2, 0, RES_2_H, "RES 2, H" }, // CB94 [431] {52116}
	{ 2, 0, RES_2_L, "RES 2, L" }, // CB95 [432] {52117}
	{ 2, 0, RES_3_INDIRECT_HL, "RES 3, (HL)" }, // CB9E [433] {52126}
	{ 4, 0, RES_3_INDIRECT_IX_dis, "RES 3, (IX+dis)" }, // DDCB [434] {56779}
	{ 4, 0, RES_3_INDIRECT_IY_dis, "RES 3, (IY+dis)" }, // FDCB [435] {64971}
	{ 2, 0, RES_3_A, "RES 3, A" }, // CB9F [436] {52127}
	{ 2, 0, RES_3_B, "RES 3, B" }, // CB98 [437] {52120}
	{ 2, 0, RES_3_C, "RES 3, C" }, // CB99 [438] {52121}
	{ 2, 0, RES_3_D, "RES 3, D" }, // CB9A [439] {52122}
	{ 2, 0, RES_3_E, "RES 3, E" }, // CB9B [440] {52123}
	{ 2, 0, RES_3_H, "RES 3, H" }, // CB9C [441] {52124}
	{ 2, 0, RES_3_L, "RES 3, L" }, // CB9D [442] {52125}
	{ 2, 0, RES_4_INDIRECT_HL, "RES 4, (HL)" }, // CBA6 [443] {52134}
	{ 4, 0, RES_4_INDIRECT_IX_dis, "RES 4, (IX+dis)" }, // DDCB [444] {56779}
	{ 4, 0, RES_4_INDIRECT_IY_dis, "RES 4, (IY+dis)" }, // FDCB [445] {64971}
	{ 2, 0, RES_4_A, "RES 4, A" }, // CBA7 [446] {52135}
	{ 2, 0, RES_4_B, "RES 4, B" }, // CBA0 [447] {52128}
	{ 2, 0, RES_4_C, "RES 4, C" }, // CBA1 [448] {52129}
	{ 2, 0, RES_4_D, "RES 4, D" }, // CBA2 [449] {52130}
	{ 2, 0, RES_4_E, "RES 4, E" }, // CBA3 [450] {52131}
	{ 2, 0, RES_4_H, "RES 4, H" }, // CBA4 [451] {52132}
	{ 2, 0, RES_4_L, "RES 4, L" }, // CBA5 [452] {52133}
	{ 2, 0, RES_5_INDIRECT_HL, "RES 5, (HL)" }, // CBAE [453] {52142}
	{ 4, 0, RES_5_INDIRECT_IX_dis, "RES 5, (IX+dis)" }, // DDCB [454] {56779}
	{ 4, 0, RES_5_INDIRECT_IY_dis, "RES 5, (IY+dis)" }, // FDCB [455] {64971}
	{ 2, 0, RES_5_A, "RES 5, A" }, // CBAF [456] {52143}
	{ 2, 0, RES_5_B, "RES 5, B" }, // CBA8 [457] {52136}
	{ 2, 0, RES_5_C, "RES 5, C" }, // CBA9 [458] {52137}
	{ 2, 0, RES_5_D, "RES 5, D" }, // CBAA [459] {52138}
	{ 2, 0, RES_5_E, "RES 5, E" }, // CBAB [460] {52139}
	{ 2, 0, RES_5_H, "RES 5, H" }, // CBAC [461] {52140}
	{ 2, 0, RES_5_L, "RES 5, L" }, // CBAD [462] {52141}
	{ 2, 0, RES_6_INDIRECT_HL, "RES 6, (HL)" }, // CBB6 [463] {52150}
	{ 4, 0, RES_6_INDIRECT_IX_dis, "RES 6, (IX+dis)" }, // DDCB [464] {56779}
	{ 4, 0, RES_6_INDIRECT_IY_dis, "RES 6, (IY+dis)" }, // FDCB [465] {64971}
	{ 2, 0, RES_6_A, "RES 6, A" }, // CBB7 [466] {52151}
	{ 2, 0, RES_6_B, "RES 6, B" }, // CBB0 [467] {52144}
	{ 2, 0, RES_6_C, "RES 6, C" }, // CBB1 [468] {52145}
	{ 2, 0, RES_6_D, "RES 6, D" }, // CBB2 [469] {52146}
	{ 2, 0, RES_6_E, "RES 6, E" }, // CBB3 [470] {52147}
	{ 2, 0, RES_6_H, "RES 6, H" }, // CBB4 [471] {52148}
	{ 2, 0, RES_6_L, "RES 6, L" }, // CBB5 [472] {52149}
	{ 2, 0, RES_7_INDIRECT_HL, "RES 7, (HL)" }, // CBBE [473] {52158}
	{ 4, 0, RES_7_INDIRECT_IX_dis, "RES 7, (IX+dis)" }, // DDCB [474] {56779}
	{ 4, 0, RES_7_INDIRECT_IY_dis, "RES 7, (IY+dis)" }, // FDCB [475] {64971}
	{ 2, 0, RES_7_A, "RES 7, A" }, // CBBF [476] {52159}
	{ 2, 0, RES_7_B, "RES 7, B" }, // CBB8 [477] {52152}
	{ 2, 0, RES_7_C, "RES 7, C" }, // CBB9 [478] {52153}
	{ 2, 0, RES_7_D, "RES 7, D" }, // CBBA [479] {52154}
	{ 2, 0, RES_7_E, "RES 7, E" }, // CBBB [480] {52155}
	{ 2, 0, RES_7_H, "RES 7, H" }, // CBBC [481] {52156}
	{ 2, 0, RES_7_L, "RES 7, L" }, // CBBD [482] {52157}
	{ 1, 0, RET, "RET" }, // C9 [483] {201}
	{ 1, 0, RET_C, "RET C" }, // D8 [484] {216}
	{ 1, 0, RET_M, "RET M" }, // F8 [485] {248}
	{ 1, 0, RET_NC, "RET NC" }, // D0 [486] {208}
	{ 1, 0, RET_NZ, "RET NZ" }, // C0 [487] {192}
	{ 1, 0, RET_P, "RET P" }, // F0 [488] {240}
	{ 1, 0, RET_PE, "RET PE" }, // E8 [489] {232}
	{ 1, 0, RET_PO, "RET PO" }, // E0 [490] {224}
	{ 1, 0, RET_Z, "RET Z" }, // C8 [491] {200}
	{ 2, 0, RETI, "RETI" }, // ED4D [492] {60749}
	{ 2, 0, RETN, "RETN" }, // ED45 [493] {60741}
	{ 2, 0, RL_INDIRECT_HL, "RL (HL)" }, // CB16 [494] {51990}
	{ 4, 0, RL_INDIRECT_IX_dis, "RL (IX+dis)" }, // DDCB [495] {56779}
	{ 4, 0, RL_INDIRECT_IY_dis, "RL (IY+dis)" }, // FDCB [496] {64971}
	{ 2, 0, RL_A, "RL A" }, // CB17 [497] {51991}
	{ 2, 0, RL_B, "RL B" }, // CB10 [498] {51984}
	{ 2, 0, RL_C, "RL C" }, // CB11 [499] {51985}
	{ 2, 0, RL_D, "RL D" }, // CB12 [500] {51986}
	{ 2, 0, RL_E, "RL E" }, // CB13 [501] {51987}
	{ 2, 0, RL_H, "RL H" }, // CB14 [502] {51988}
	{ 2, 0, RL_L, "RL L" }, // CB15 [503] {51989}
	{ 1, 0, RLA, "RLA" }, // 17 [504] {23}
	{ 2, 0, RLC_INDIRECT_HL, "RLC (HL)" }, // CB06 [505] {51974}
	{ 4, 0, RLC_INDIRECT_IX_dis, "RLC (IX+dis)" }, // DDCB [506] {56779}
	{ 4, 0, RLC_INDIRECT_IY_dis, "RLC (IY+dis)" }, // FDCB [507] {64971}
	{ 2, 0, RLC_A, "RLC A" }, // CB07 [508] {51975}
	{ 2, 0, RLC_B, "RLC B" }, // CB00 [509] {51968}
	{ 2, 0, RLC_C, "RLC C" }, // CB01 [510] {51969}
	{ 2, 0, RLC_D, "RLC D" }, // CB02 [511] {51970}
	{ 2, 0, RLC_E, "RLC E" }, // CB03 [512] {51971}
	{ 2, 0, RLC_H, "RLC H" }, // CB04 [513] {51972}
	{ 2, 0, RLC_L, "RLC L" }, // CB05 [514] {51973}
	{ 1, 0, RLCA, "RLCA" }, // 07 [515] {7}
	{ 2, 0, RLD, "RLD" }, // ED6F [516] {60783}
	{ 2, 0, R_INDIRECT_HL, "RR (HL)" }, // CB1E [517] {51998}
	{ 4, 0, R_INDIRECT_IX_dis, "RR (IX+dis)" }, // DDCB [518] {56779}
	{ 4, 0, R_INDIRECT_IY_dis, "RR (IY+dis)" }, // FDCB [519] {64971}
	{ 2, 0, R_A, "RR A" }, // CB1F [520] {51999}
	{ 2, 0, R_B, "RR B" }, // CB18 [521] {51992}
	{ 2, 0, R_C, "RR C" }, // CB19 [522] {51993}
	{ 2, 0, R_D, "RR D" }, // CB1A [523] {51994}
	{ 2, 0, R_E, "RR E" }, // CB1B [524] {51995}
	{ 2, 0, R_H, "RR H" }, // CB1C [525] {51996}
	{ 2, 0, R_L, "RR L" }, // CB1D [526] {51997}
	{ 1, 0, RRA, "RRA" }, // 1F [527] {31}
	{ 2, 0, RC_INDIRECT_HL, "RRC (HL)" }, // CB0E [528] {51982}
	{ 4, 0, RC_INDIRECT_IX_dis, "RRC (IX+dis)" }, // DDCB [529] {56779}
	{ 4, 0, RC_INDIRECT_IY_dis, "RRC (IY+dis)" }, // FDCB [530] {64971}
	{ 2, 0, RC_A, "RRC A" }, // CB0F [531] {51983}
	{ 2, 0, RC_B, "RRC B" }, // CB08 [532] {51976}
	{ 2, 0, RC_C, "RRC C" }, // CB09 [533] {51977}
	{ 2, 0, RC_D, "RRC D" }, // CB0A [534] {51978}
	{ 2, 0, RC_E, "RRC E" }, // CB0B [535] {51979}
	{ 2, 0, RC_H, "RRC H" }, // CB0C [536] {51980}
	{ 2, 0, RC_L, "RRC L" }, // CB0D [537] {51981}
	{ 1, 0, RRCA, "RRCA" }, // 0F [538] {15}
	{ 2, 0, RRD, "RRD" }, // ED67 [539] {60775}
	{ 1, 0, RST_0H, "RST 00H" }, // C7 [540] {199}
	{ 1, 0, RST_08H, "RST 08H" }, // CF [541] {207}
	{ 1, 0, RST_10H, "RST 10H" }, // D7 [542] {215}
	{ 1, 0, RST_18H, "RST 18H" }, // DF [543] {223}
	{ 1, 0, RST_20H, "RST 20H" }, // E7 [544] {231}
	{ 1, 0, RST_28H, "RST 28H" }, // EF [545] {239}
	{ 1, 0, RST_30H, "RST 30H" }, // F7 [546] {247}
	{ 1, 0, RST_38H, "RST 38H" }, // FF [547] {255}
	{ 1, 0, SBC_A_INDIRECT_HL, "SBC A, (HL)" }, // 9E [548] {158}
	{ 3, 0, SBC_A_INDIRECT_IX_dis, "SBC A, (IX+dis)" }, // DD9E [549] {56734}
	{ 3, 0, SBC_A_INDIRECT_IY_dis, "SBC A, (IY+dis)" }, // FD9E [550] {64926}
	{ 1, 0, SBC_A_A, "SBC A, A" }, // 9F [551] {159}
	{ 1, 0, SBC_A_B, "SBC A, B" }, // 98 [552] {152}
	{ 1, 0, SBC_A_C, "SBC A, C" }, // 99 [553] {153}
	{ 1, 0, SBC_A_D, "SBC A, D" }, // 9A [554] {154}
	{ 1, 0, SBC_A_E, "SBC A, E" }, // 9B [555] {155}
	{ 1, 0, SBC_A_H, "SBC A, H" }, // 9C [556] {156}
	{ 1, 0, SBC_A_L, "SBC A, L" }, // 9D [557] {157}
	{ 2, 0, SBC_A_n, "SBC A, " }, // DE [558] {222}
	{ 2, 0, SBC_HL_BC, "SBC HL, BC" }, // ED42 [559] {60738}
	{ 2, 0, SBC_HL_DE, "SBC HL, DE" }, // ED52 [560] {60754}
	{ 2, 0, SBC_HL_HL, "SBC HL, HL" }, // ED62 [561] {60770}
	{ 2, 0, SBC_HL_SP, "SBC HL, SP" }, // ED72 [562] {60786}
	{ 1, 0, SCF, "SCF" }, // 37 [563] {55}
	{ 2, 0, SET_0_INDIRECT_HL, "SET 0, (HL)" }, // CBC6 [564] {52166}
	{ 4, 0, SET_0_INDIRECT_IX_dis, "SET 0, (IX+dis)" }, // DDCB [565] {56779}
	{ 4, 0, SET_0_INDIRECT_IY_dis, "SET 0, (IY+dis)" }, // FDCB [566] {64971}
	{ 2, 0, SET_0_A, "SET 0, A" }, // CBC7 [567] {52167}
	{ 2, 0, SET_0_B, "SET 0, B" }, // CBC0 [568] {52160}
	{ 2, 0, SET_0_C, "SET 0, C" }, // CBC1 [569] {52161}
	{ 2, 0, SET_0_D, "SET 0, D" }, // CBC2 [570] {52162}
	{ 2, 0, SET_0_E, "SET 0, E" }, // CBC3 [571] {52163}
	{ 2, 0, SET_0_H, "SET 0, H" }, // CBC4 [572] {52164}
	{ 2, 0, SET_0_L, "SET 0, L" }, // CBC5 [573] {52165}
	{ 2, 0, SET_1_INDIRECT_HL, "SET 1, (HL)" }, // CBCE [574] {52174}
	{ 4, 0, SET_1_INDIRECT_IX_dis, "SET 1, (IX+dis)" }, // DDCB [575] {56779}
	{ 4, 0, SET_1_INDIRECT_IY_dis, "SET 1, (IY+dis)" }, // FDCB [576] {64971}
	{ 2, 0, SET_1_A, "SET 1, A" }, // CBCF [577] {52175}
	{ 2, 0, SET_1_B, "SET 1, B" }, // CBC8 [578] {52168}
	{ 2, 0, SET_1_C, "SET 1, C" }, // CBC9 [579] {52169}
	{ 2, 0, SET_1_D, "SET 1, D" }, // CBCA [580] {52170}
	{ 2, 0, SET_1_E, "SET 1, E" }, // CBCB [581] {52171}
	{ 2, 0, SET_1_H, "SET 1, H" }, // CBCC [582] {52172}
	{ 2, 0, SET_1_L, "SET 1, L" }, // CBCD [583] {52173}
	{ 2, 0, SET_2_INDIRECT_HL, "SET 2, (HL)" }, // CBD6 [584] {52182}
	{ 4, 0, SET_2_INDIRECT_IX_dis, "SET 2, (IX+dis)" }, // DDCB [585] {56779}
	{ 4, 0, SET_2_INDIRECT_IY_dis, "SET 2, (IY+dis)" }, // FDCB [586] {64971}
	{ 2, 0, SET_2_A, "SET 2, A" }, // CBD7 [587] {52183}
	{ 2, 0, SET_2_B, "SET 2, B" }, // CBD0 [588] {52176}
	{ 2, 0, SET_2_C, "SET 2, C" }, // CBD1 [589] {52177}
	{ 2, 0, SET_2_D, "SET 2, D" }, // CBD2 [590] {52178}
	{ 2, 0, SET_2_E, "SET 2, E" }, // CBD3 [591] {52179}
	{ 2, 0, SET_2_H, "SET 2, H" }, // CBD4 [592] {52180}
	{ 2, 0, SET_2_L, "SET 2, L" }, // CBD5 [593] {52181}
	{ 2, 0, SET_3_INDIRECT_HL, "SET 3, (HL)" }, // CBDE [594] {52190}
	{ 4, 0, SET_3_INDIRECT_IX_dis, "SET 3, (IX+dis)" }, // DDCB [595] {56779}
	{ 4, 0, SET_3_INDIRECT_IY_dis, "SET 3, (IY+dis)" }, // FDCB [596] {64971}
	{ 2, 0, SET_3_A, "SET 3, A" }, // CBDF [597] {52191}
	{ 2, 0, SET_3_B, "SET 3, B" }, // CBD8 [598] {52184}
	{ 2, 0, SET_3_C, "SET 3, C" }, // CBD9 [599] {52185}
	{ 2, 0, SET_3_D, "SET 3, D" }, // CBDA [600] {52186}
	{ 2, 0, SET_3_E, "SET 3, E" }, // CBDB [601] {52187}
	{ 2, 0, SET_3_H, "SET 3, H" }, // CBDC [602] {52188}
	{ 2, 0, SET_3_L, "SET 3, L" }, // CBDD [603] {52189}
	{ 2, 0, SET_4_INDIRECT_HL, "SET 4, (HL)" }, // CBE6 [604] {52198}
	{ 4, 0, SET_4_INDIRECT_IX_dis, "SET 4, (IX+dis)" }, // DDCB [605] {56779}
	{ 4, 0, SET_4_INDIRECT_IY_dis, "SET 4, (IY+dis)" }, // FDCB [606] {64971}
	{ 2, 0, SET_4_A, "SET 4, A" }, // CBE7 [607] {52199}
	{ 2, 0, SET_4_B, "SET 4, B" }, // CBE0 [608] {52192}
	{ 2, 0, SET_4_C, "SET 4, C" }, // CBE1 [609] {52193}
	{ 2, 0, SET_4_D, "SET 4, D" }, // CBE2 [610] {52194}
	{ 2, 0, SET_4_E, "SET 4, E" }, // CBE3 [611] {52195}
	{ 2, 0, SET_4_H, "SET 4, H" }, // CBE4 [612] {52196}
	{ 2, 0, SET_4_L, "SET 4, L" }, // CBE5 [613] {52197}
	{ 2, 0, SET_5_INDIRECT_HL, "SET 5, (HL)" }, // CBEE [614] {52206}
	{ 4, 0, SET_5_INDIRECT_IX_dis, "SET 5, (IX+dis)" }, // DDCB [615] {56779}
	{ 4, 0, SET_5_INDIRECT_IY_dis, "SET 5, (IY+dis)" }, // FDCB [616] {64971}
	{ 2, 0, SET_5_A, "SET 5, A" }, // CBEF [617] {52207}
	{ 2, 0, SET_5_B, "SET 5, B" }, // CBE8 [618] {52200}
	{ 2, 0, SET_5_C, "SET 5, C" }, // CBE9 [619] {52201}
	{ 2, 0, SET_5_D, "SET 5, D" }, // CBEA [620] {52202}
	{ 2, 0, SET_5_E, "SET 5, E" }, // CBEB [621] {52203}
	{ 2, 0, SET_5_H, "SET 5, H" }, // CBEC [622] {52204}
	{ 2, 0, SET_5_L, "SET 5, L" }, // CBED [623] {52205}
	{ 2, 0, SET_6_INDIRECT_HL, "SET 6, (HL)" }, // CBF6 [624] {52214}
	{ 4, 0, SET_6_INDIRECT_IX_dis, "SET 6, (IX+dis)" }, // DDCB [625] {56779}
	{ 4, 0, SET_6_INDIRECT_IY_dis, "SET 6, (IY+dis)" }, // FDCB [626] {64971}
	{ 2, 0, SET_6_A, "SET 6, A" }, // CBF7 [627] {52215}
	{ 2, 0, SET_6_B, "SET 6, B" }, // CBF0 [628] {52208}
	{ 2, 0, SET_6_C, "SET 6, C" }, // CBF1 [629] {52209}
	{ 2, 0, SET_6_D, "SET 6, D" }, // CBF2 [630] {52210}
	{ 2, 0, SET_6_E, "SET 6, E" }, // CBF3 [631] {52211}
	{ 2, 0, SET_6_H, "SET 6, H" }, // CBF4 [632] {52212}
	{ 2, 0, SET_6_L, "SET 6, L" }, // CBF5 [633] {52213}
	{ 2, 0, SET_7_INDIRECT_HL, "SET 7, (HL)" }, // CBFE [634] {52222}
	{ 4, 0, SET_7_INDIRECT_IX_dis, "SET 7, (IX+dis)" }, // DDCB [635] {56779}
	{ 4, 0, SET_7_INDIRECT_IY_dis, "SET 7, (IY+dis)" }, // FDCB [636] {64971}
	{ 2, 0, SET_7_A, "SET 7, A" }, // CBFF [637] {52223}
	{ 2, 0, SET_7_B, "SET 7, B" }, // CBF8 [638] {52216}
	{ 2, 0, SET_7_C, "SET 7, C" }, // CBF9 [639] {52217}
	{ 2, 0, SET_7_D, "SET 7, D" }, // CBFA [640] {52218}
	{ 2, 0, SET_7_E, "SET 7, E" }, // CBFB [641] {52219}
	{ 2, 0, SET_7_H, "SET 7, H" }, // CBFC [642] {52220}
	{ 2, 0, SET_7_L, "SET 7, L" }, // CBFD [643] {52221}
	{ 2, 0, SLA_INDIRECT_HL, "SLA (HL)" }, // CB26 [644] {52006}
	{ 4, 0, SLA_INDIRECT_IX_dis, "SLA (IX+dis)" }, // DDCB [645] {56779}
	{ 4, 0, SLA_INDIRECT_IY_dis, "SLA (IY+dis)" }, // FDCB [646] {64971}
	{ 2, 0, SLA_A, "SLA A" }, // CB27 [647] {52007}
	{ 2, 0, SLA_B, "SLA B" }, // CB20 [648] {52000}
	{ 2, 0, SLA_C, "SLA C" }, // CB21 [649] {52001}
	{ 2, 0, SLA_D, "SLA D" }, // CB22 [650] {52002}
	{ 2, 0, SLA_E, "SLA E" }, // CB23 [651] {52003}
	{ 2, 0, SLA_H, "SLA H" }, // CB24 [652] {52004}
	{ 2, 0, SLA_L, "SLA L" }, // CB25 [653] {52005}
	{ 2, 0, SRA_INDIRECT_HL, "SRA (HL)" }, // CB2E [654] {52014}
	{ 4, 0, SRA_INDIRECT_IX_dis, "SRA (IX+dis)" }, // DDCB [655] {56779}
	{ 4, 0, SRA_INDIRECT_IY_dis, "SRA (IY+dis)" }, // FDCB [656] {64971}
	{ 2, 0, SRA_A, "SRA A" }, // CB2F [657] {52015}
	{ 2, 0, SRA_B, "SRA B" }, // CB28 [658] {52008}
	{ 2, 0, SRA_C, "SRA C" }, // CB29 [659] {52009}
	{ 2, 0, SRA_D, "SRA D" }, // CB2A [660] {52010}
	{ 2, 0, SRA_E, "SRA E" }, // CB2B [661] {52011}
	{ 2, 0, SRA_H, "SRA H" }, // CB2C [662] {52012}
	{ 2, 0, SRA_L, "SRA L" }, // CB2D [663] {52013}
	{ 2, 0, SRL_INDIRECT_HL, "SRL (HL)" }, // CB3E [664] {52030}
	{ 4, 0, SRL_INDIRECT_IX_dis, "SRL (IX+dis)" }, // DDCB [665] {56779}
	{ 4, 0, SRL_INDIRECT_IY_dis, "SRL (IY+dis)" }, // FDCB [666] {64971}
	{ 2, 0, SRL_A, "SRL A" }, // CB3F [667] {52031}
	{ 2, 0, SRL_B, "SRL B" }, // CB38 [668] {52024}
	{ 2, 0, SRL_C, "SRL C" }, // CB39 [669] {52025}
	{ 2, 0, SRL_D, "SRL D" }, // CB3A [670] {52026}
	{ 2, 0, SRL_E, "SRL E" }, // CB3B [671] {52027}
	{ 2, 0, SRL_H, "SRL H" }, // CB3C [672] {52028}
	{ 2, 0, SRL_L, "SRL L" }, // CB3D [673] {52029}
	{ 1, 0, SUB_INDIRECT_HL, "SUB (HL)" }, // 96 [674] {150}
	{ 3, 0, SUB_INDIRECT_IX_dis, "SUB (IX+dis)" }, // DD96 [675] {56726}
	{ 3, 0, SUB_INDIRECT_IY_dis, "SUB (IY+dis)" }, // FD96 [676] {64918}
	{ 1, 0, SUB_A, "SUB A" }, // 97 [677] {151}
	{ 1, 0, SUB_B, "SUB B" }, // 90 [678] {144}
	{ 1, 0, SUB_C, "SUB C" }, // 91 [679] {145}
	{ 1, 0, SUB_D, "SUB D" }, // 92 [680] {146}
	{ 1, 0, SUB_E, "SUB E" }, // 93 [681] {147}
	{ 1, 0, SUB_H, "SUB H" }, // 94 [682] {148}
	{ 1, 0, SUB_L, "SUB L" }, // 95 [683] {149}
	{ 2, 0, SUB_n, "SUB n" }, // D6 [684] {214}
	{ 1, 0, XOR_INDIRECT_HL, "XOR (HL)" }, // AE [685] {174}
	{ 3, 0, XOR_INDIRECT_IX_dis, "XOR (IX+dis)" }, // DDAE [686] {56750}
	{ 3, 0, XOR_INDIRECT_IY_dis, "XOR (IY+dis)" }, // FDAE [687] {64942}
	{ 1, 0, XOR_A, "XOR A" }, // AF [688] {175}
	{ 1, 0, XOR_B, "XOR B" }, // A8 [689] {168}
	{ 1, 0, XOR_C, "XOR C" }, // A9 [690] {169}
	{ 1, 0, XOR_D, "XOR D" }, // AA [691] {170}
	{ 1, 0, XOR_E, "XOR E" }, // AB [692] {171}
	{ 1, 0, XOR_H, "XOR H" }, // AC [693] {172}
	{ 1, 0, XOR_L, "XOR L" }, // AD [694] {173}
	{ 2, 0, XOR_n, "XOR n" }, // EE [695] {238}
});
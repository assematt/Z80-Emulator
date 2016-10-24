#pragma once

// Normal instruction
enum TOpCodesMainInstruction
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
enum TOpCodesExtendedInstruction
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
enum TOpCodesBitInstructions
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
enum TOpCodesIXInstructions
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
enum TOpCodesIXBitInstructions
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
};

// IY instructions (FD)
enum TOpCodesIYInstructions
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
enum TOpCodesIYBitInstructions
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
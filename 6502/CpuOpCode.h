#pragma once

#include "Base.h"

struct CpuOpCode
{
	static constexpr Byte
		LDA_IM = 0xa9,
		LDA_ZP = 0xa5,
		LDA_ZX = 0xb5,
		LDA_AB = 0xad,
		LDA_AX = 0xbd,
		LDA_AY = 0xb9;

	static constexpr Byte
		LDX_IM = 0xa2,
		LDX_ZP = 0xa6,
		LDX_ZY = 0xb6,
		LDX_AB = 0xae,
		LDX_AY = 0xbe;

	static constexpr Byte
		LDY_IM = 0xa0,
		LDY_ZP = 0xa4,
		LDY_ZX = 0xb4,
		LDY_AB = 0xac,
		LDY_AX = 0xbc;

	static constexpr Byte
		STA_ZP = 0x85,
		STA_ZX = 0x95,
		STA_AB = 0x8d,
		STA_AX = 0x9d,
		STA_AY = 0x99;

	static constexpr Byte
		STX_ZP = 0x86,
		STX_ZY = 0x96,
		STX_AB = 0x8e;

	static constexpr Byte
		STY_ZP = 0x84,
		STY_ZA = 0x94,
		STY_AB = 0x8c;

	static constexpr Byte
		TAX_IP = 0xb9,
		TAY_IP = 0x00,
		TXA_IP = 0x00,
		TYA_IP = 0x00;

	static constexpr Byte
		TSX_IP = 0xba,
		PXS_IP = 0x9a,
		PHA_IP = 0x48,
		PHP_IP = 0x08,
		PLA_IP = 0x68,
		PLP_IP = 0x28;

	static constexpr Byte
		AND_IM = 0x29,
		AND_ZP = 0x25,
		AND_ZX = 0x35,
		AND_AB = 0x2d,
		AND_AX = 0x3d,
		AND_AY = 0x39;

	static constexpr Byte
		ERO_IM = 0x09,
		ERO_ZP = 0x05,
		ERO_ZX = 0x15,
		ERO_AB = 0x0d,
		ERO_AX = 0x1d,
		ERO_AY = 0x19;

	static constexpr Byte
		ORA_IM = 0x49,
		ORA_ZP = 0x45,
		ORA_ZX = 0x55,
		ORA_AB = 0x4d,
		ORA_AX = 0x5d,
		ORA_AY = 0x59;

	static constexpr Byte
		BIT_ZP = 0x24,
		BIT_AB = 0x2c;

	static constexpr Byte
		ADC_IM = 0x69,
		ADC_ZP = 0x65,
		ADC_ZX = 0x75,
		ADC_AB = 0x6d,
		ADC_AX = 0x7d,
		ADC_AY = 0x79;

	static constexpr Byte
		SBC_IM = 0xe9,
		SBC_ZP = 0xe5,
		SBC_ZX = 0xf5,
		SBC_AB = 0xed,
		SBC_AX = 0xfd,
		SBC_AY = 0xf9;

	static constexpr Byte
		CMP_IM = 0xc9,
		CMP_ZP = 0xc5,
		CMP_ZX = 0xd5,
		CMP_AB = 0xcd,
		CMP_AX = 0xdd,
		CMP_AY = 0xd9;

	static constexpr Byte
		CPX_IM = 0xe0,
		CPX_ZP = 0xe4,
		CPX_AB = 0xec;

	static constexpr Byte
		CPY_IM = 0xc0,
		CPY_ZP = 0xc4,
		CPY_AB = 0xcc;

	static constexpr Byte
		INC_ZP = 0xe6,
		INC_ZX = 0xf6,
		INC_AB = 0xee,
		INC_AX = 0xfe;

	static constexpr Byte
		INX_IP = 0xe8,
		INY_IP = 0xc8;

	static constexpr Byte
		DEC_ZP = 0xc6,
		DEC_ZX = 0xd6,
		DEC_AB = 0xce,
		DEC_AX = 0xde;

	static constexpr Byte
		DEX_IP = 0xca,
		DEY_IP = 0x88;

	static constexpr Byte
		ASL_AC = 0x0a,
		ASL_ZP = 0x06,
		ASL_ZX = 0x16,
		ASL_AB = 0x0e,
		ASL_AX = 0x1e;

	static constexpr Byte
		LSR_AC = 0x4a,
		LSR_ZP = 0x46,
		LSR_ZX = 0x56,
		LSR_AB = 0x4e,
		LSR_AX = 0x5e;

	static constexpr Byte
		ROL_AC = 0x2a,
		ROL_ZP = 0x26,
		ROL_ZX = 0x36,
		ROL_AB = 0x2e,
		ROL_AX = 0x3e;

	static constexpr Byte
		ROR_AC = 0x6a,
		ROR_ZP = 0x66,
		ROR_ZX = 0x76,
		ROR_AB = 0x6e,
		ROR_AX = 0x7e;

	static constexpr Byte
		JMP_AB = 0x4c,
		JMP_IN = 0x6c;

	static constexpr Byte
		BCC_RL = 0x90,
		BCS_RL = 0xb0,
		BEQ_RL = 0xf0,
		BMI_RL = 0x30,
		BNE_RL = 0xd0,
		BPL_RL = 0x10,
		BVC_RL = 0x50,
		BVS_RL = 0x70;

	static constexpr Byte
		CLC_IP = 0x18,
		CLI_IP = 0x58,
		CLV_IP = 0xb8,
		SEC_IP = 0x38,
		SED_IP = 0xf8,
		SEI_IP = 0x78;

	static constexpr Byte
		NOP_IP = 0xea;

	static constexpr Byte
		None = 0x00,
		Reset = 0xff;
};
#include "Io.h"
#include "Cpu.h"
#include "CpuOpCode.h"
#include "Memory.h"
#include "Oscillator.h"

#include <cstdio>

int main()
{
	IoBoard board;

	Cpu cpu;
	Memory ram{ 16 * 1024, true };
	Memory rom{ 32 * 1024, false };
	Oscillator oscillator;

	constexpr Byte
		PIN_BOOL_CLOCK = 0,
		PIN_BOOL_READ_WRITE = 4,
		PIN_BYTE_DATA = 5,
		PIN_BYTE_ADDR_LOW = 6,
		PIN_BYTE_ADDR_HIGH	= 7;

	{ // setup Cpu
		CpuConnection conn;

		conn.Clock = { PIN_BOOL_CLOCK };
		conn.ReadWrite = { PIN_BOOL_READ_WRITE  };

		conn.Data = { PIN_BYTE_DATA };
		conn.AddressLow = { PIN_BYTE_ADDR_LOW };
		conn.AddressHigh = { PIN_BYTE_ADDR_HIGH };

		cpu.Connect(&board, conn);
		cpu.Reset();
	}

	{ // setup ram
		// active address 0x0000 - 0x3fff # 16kb
		MemoryConnection conn;

		conn.Data = { PIN_BYTE_DATA };
		conn.AddressLow = { PIN_BYTE_ADDR_LOW };
		conn.AddressHigh = { PIN_BYTE_ADDR_HIGH, 0b01111111 };

		conn.DataDirection = { PIN_BOOL_READ_WRITE };
		conn.ChipSelect = { PIN_BYTE_ADDR_HIGH, 0b11000000 };
		conn.ActiveValue = 0b00000000;

		ram.Connect(&board, conn);
		ram.Reset();
	}

	{ // setup rom
		// active address 0x8000 - 0xffff # 32kb
		MemoryConnection conn;

		conn.Data = { PIN_BYTE_DATA };
		conn.AddressLow = { PIN_BYTE_ADDR_LOW };
		conn.AddressHigh = { PIN_BYTE_ADDR_HIGH, 0b01111111 };

		conn.DataDirection = { PIN_BOOL_READ_WRITE };
		conn.ChipSelect = { PIN_BYTE_ADDR_HIGH, 0b10000000 };
		conn.ActiveValue = 0b10000000;

		rom.Connect(&board, conn);
		rom.Reset();

		// put some insturctions
		// reset vector

		rom[0x7ffc] = 0x00;
		rom[0x7ffd] = 0x80;

		/*
			str_buff = $0200

			.org $8000
			  lda #$7a
			  ldx #$7a-$62
			loop:
			  sta str_buff,x
			  beq exit
			  sbc #1
			  dex
			  jmp loop
			exit:
			  jmp exit


			LOC   CODE         LABEL     INSTRUCTION

										 STR_BUFF = $0200
			8000                         * = $8000
			8000  A9 7A                  LDA #$7A
			8002  A2 18                  LDX #$18
			8004               LOOP
			8004  9D 00 02               STA $0200,X
			8007  F0 06                  BEQ $800F
			8009  E9 01                  SBC #$01
			800B  CA                     DEX
			800C  4C 04 80               JMP $8004
			800F               EXIT
			800F  4C 0F 80               JMP $800F
		*/

		rom[0x0000] = CpuOpCode::LDA_IM;
		rom[0x0001] = 'z';

		rom[0x0002] = CpuOpCode::LDX_IM;
		rom[0x0003] = 'z' - 'a';

		rom[0x0004] = CpuOpCode::STA_AX;
		rom[0x0005] = 0x00;
		rom[0x0006] = 0x02;

		rom[0x0007] = CpuOpCode::BEQ_RL;
		rom[0x0008] = 6;

		rom[0x0009] = CpuOpCode::SBC_IM;
		rom[0x000a] = 1;

		rom[0x000b] = CpuOpCode::DEX_IP;

		rom[0x000c] = CpuOpCode::JMP_AB;
		rom[0x000d] = 0x04;
		rom[0x000e] = 0x80;

		rom[0x000f] = CpuOpCode::JMP_AB;
		rom[0x0010] = 0x0f;
		rom[0x0011] = 0x80;
	}

	{ // setup Oscillator
		OscillatorConnection conn;

		conn.Clock = { PIN_BOOL_CLOCK };

		oscillator.Connect(&board, conn);
	}

	Word cycles = 444;


	while (cycles--)
	{
		Byte pulse = 2;

		while (pulse--)
		{
			oscillator.Oscillate();

			cpu.Update();
			rom.Update();
			ram.Update();
		}

#if true
		// logging what is in board's busses.
		Word addr = board[PIN_BYTE_ADDR_LOW] | (board[PIN_BYTE_ADDR_HIGH] << 8);
		Byte data = board[PIN_BYTE_DATA];
		Byte rw = board[PIN_BOOL_READ_WRITE] ? 'r' : 'W';

		printf("\n0x%04x %c 0x%02x", addr, rw, data);
#endif
	}

	return 0;
}
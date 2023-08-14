#include "Cpu.h"
#include "CpuInstruction.h"

#include <cstdio>

void Cpu::Connect(IoBoard* board, const CpuConnection& connection)
{
	m_IoHandler.SetConnection(connection);
	m_IoHandler.SetBoard(board);
}

void Cpu::Reset()
{
	m_Flag.ClearAll();
	m_Register.ClearAll();
	m_Cycles = 1;
	m_Register.OpCode = CpuOpCode::Reset;
}

void Cpu::Update()
{
	m_Clock = m_IoHandler.ReadClock();

	if (m_Cycles == 0)
	{
		Fetch();
	}
	else
	{
		Exacute();
	}

	if (m_Clock.IsFalling())
	{
		m_Cycles++;
	}
}

void Cpu::Fetch()
{
	if (m_Clock.IsRising())
	{
		m_IoHandler.SetReading();
		m_IoHandler.SetAddress(m_Register.ProgramCounter++);
	}
	else
	{
		m_Register.OpCode = m_IoHandler.ReadData();
		m_Cycles = 0;
	}
}

void Cpu::Exacute()
{
	if (m_Clock.IsRising())
	{
		switch (m_Register.OpCode)
		{
		case CpuOpCode::Reset:
		{
			switch (m_Cycles)
			{
			case 1:
				m_IoHandler.SetReading();
				m_IoHandler.SetAddress(0xfffc);
				break;
			case 2:
				m_IoHandler.SetReading();
				m_IoHandler.SetAddress(0xfffd);
				break;
			}
		} break;
			
		case CpuOpCode::LDA_IM:
		case CpuOpCode::LDX_IM:
		case CpuOpCode::LDY_IM:
			m_IoHandler.SetReading();
			m_IoHandler.SetAddress(m_Register.ProgramCounter++);
			break;

		case CpuOpCode::SBC_IM:
			switch (m_Cycles)
			{
			case 1:
				m_IoHandler.SetReading();
				m_IoHandler.SetAddress(m_Register.ProgramCounter++);
				break;
			case 2:
				break;
			}
			break;

		case CpuOpCode::STA_AX:
			switch (m_Cycles)
			{
			case 1:
			case 2:
				m_IoHandler.SetReading();
				m_IoHandler.SetAddress(m_Register.ProgramCounter++);
				break;
			case 3:
				m_IoHandler.SetWriting();
				m_IoHandler.SetAddress(m_Byte0 | (m_Byte1 << 8) + m_Register.IndexX);
				m_IoHandler.WriteData(m_Register.Accumulator);
				break;
			}
			break;

		case CpuOpCode::BEQ_RL:
			switch (m_Cycles)
			{
			case 1:
				m_IoHandler.SetReading();
				m_IoHandler.SetAddress(m_Register.ProgramCounter++);
				break;
			case 2:
				if (m_Flag.Zero)
				{
					if (m_Byte0 & 0b10000000)
					{
						m_Register.ProgramCounter -= m_Byte0 & 0b10000000;
					}
					else
					{
						m_Register.ProgramCounter += m_Byte0;
					}
				}
				break;
			}
			break;

		case CpuOpCode::DEX_IP:
			break;

		case CpuOpCode::JMP_AB:
			switch (m_Cycles)
			{
			case 1:
			case 2:
				m_IoHandler.SetReading();
				m_IoHandler.SetAddress(m_Register.ProgramCounter++);
				break;
			case 3:
				break;
			}
			break;
		}

		return;
	}

	if (m_Clock.IsFalling())
	{
		switch (m_Register.OpCode)
		{
		case CpuOpCode::Reset:
		{
			switch (m_Cycles)
			{
			case 1:
				m_Register.ProgramCounter |= m_IoHandler.ReadData() << 0;
				break;
			case 2:
				m_Register.ProgramCounter |= m_IoHandler.ReadData() << 8;
			default:
				ClearInsturction();
			}
		} break;

		case CpuOpCode::LDA_IM:
		{
			m_Register.Accumulator = m_IoHandler.ReadData();
			m_Flag.Zero = m_Register.Accumulator == 0;
			m_Flag.Negative = m_Register.Accumulator & 0b10000000;
			ClearInsturction();
		} break;

		case CpuOpCode::LDX_IM:
		{
			m_Register.IndexX = m_IoHandler.ReadData();
			m_Flag.Zero = m_Register.IndexX == 0;
			m_Flag.Negative = m_Register.IndexX & 0b10000000;
			ClearInsturction();
		} break;

		case CpuOpCode::LDY_IM:
		{
			m_Register.IndexY = m_IoHandler.ReadData();
			m_Flag.Zero = m_Register.IndexY == 0;
			m_Flag.Negative = m_Register.IndexY & 0b10000000;
			ClearInsturction();
		} break;

		case CpuOpCode::SBC_IM:
			switch (m_Cycles)
			{
			case 1:
				m_Byte0 = m_IoHandler.ReadData();
				break;
			case 2:
				m_Register.Accumulator -= m_Byte0 - m_Flag.Carry;
				m_Flag.Zero = m_Register.Accumulator == 0;
				m_Flag.Negative = m_Register.Accumulator & 0b10000000;
				// http://www.righto.com/2012/12/the-6502-overflow-flag-explained.html
			default:
				ClearInsturction();
			}
			break;

		case CpuOpCode::STA_AX:
			switch (m_Cycles)
			{
			case 1:
				m_Byte0 = m_IoHandler.ReadData();
				break;
			case 2:
				m_Byte1 = m_IoHandler.ReadData();
				break;
			case 3:
			default:
				ClearInsturction();
			}
			break;

		case CpuOpCode::BEQ_RL:
			switch (m_Cycles)
			{
			case 1:
				m_Byte0 = m_IoHandler.ReadData();
				break;
			case 2:
			default: ClearInsturction();
			}
			break;

		case CpuOpCode::DEX_IP:
			m_Register.IndexX--;
			m_Flag.Zero = m_Register.IndexX == 0;
			m_Flag.Negative = m_Register.IndexX & 0b10000000;
			ClearInsturction();
			break;

		case CpuOpCode::JMP_AB:
			switch (m_Cycles)
			{
			case 1:
				m_Byte0 = m_IoHandler.ReadData();
				break;
			case 2:
				m_Byte1 = m_IoHandler.ReadData();
				break;
			case 3:
				m_Register.ProgramCounter = m_Byte0 | (m_Byte1 << 8);
			default:
				ClearInsturction();
			}
			break;

		default:
			printf(" # unkown opcode %02x at %04x", m_Register.OpCode, m_Register.ProgramCounter - 1);
			ClearInsturction();
		}

		return;
	}
}
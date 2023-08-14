#pragma once

#include "CpuIo.h"

struct CpuRegister
{
	Word ProgramCounter, StackPointer;
	Byte OpCode, Accumulator, IndexX, IndexY;

	void ClearAll()
	{
		OpCode = ProgramCounter = StackPointer = Accumulator = IndexX = IndexY = 0;
	}
};

struct CpuFlag
{
	Byte Carry : 1;
	Byte Zero : 1;
	Byte Interrupt : 1;
	Byte Decimal : 1;
	Byte Break : 1;
	Byte Unused : 1;
	Byte Overflow : 1;
	Byte Negative : 1;

	void ClearAll()
	{
		Carry = Zero = Interrupt = Decimal = Break = Unused = Overflow = Negative = 0;
	}
};

class Cpu
{
public:
	void Connect(IoBoard* board, const CpuConnection& connection);
	void Reset();
	void Update();

	Byte GetCycles() const { return m_Cycles; }
private:
	void Fetch();
	void Exacute();
	/*
	* # must be call only when the clock is falling.
	*/
	void ClearInsturction() { m_Cycles = 0xff; };
private:
	SignalEdage m_Clock;
	CpuFlag m_Flag;
	Byte m_Cycles;
	Byte m_Byte0, m_Byte1;
	CpuRegister m_Register;
	CpuIoHandler m_IoHandler;
};
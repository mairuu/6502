#pragma once

#include "Base.h"

class IoBoard
{
public:
	Byte& operator[](Byte i) { return m_Buffer[i]; }
private:
	Byte m_Buffer[8]{ 0 };
};

struct IoSlot
{
	Byte Pin, Mask = 0xff;
};

class IoHandler
{
public:
	void SetBoard(IoBoard* board) { m_Board = board; }
protected:
	Byte Read(const IoSlot& slot) { return (*m_Board)[slot.Pin] & slot.Mask; }
	void Write(const IoSlot& slot, Byte value) { (*m_Board)[slot.Pin] = value & slot.Mask; }
private:
	IoBoard* m_Board = nullptr;
};
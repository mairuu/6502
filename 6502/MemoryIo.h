#pragma once

#include "Io.h"

struct MemoryConnection
{
	IoSlot Data, AddressLow, AddressHigh;
	IoSlot ChipSelect;
	/*
	* Data Direction
	* 
	* when in high state the memory will be writing from it's buffer to data slot.
	* when in low  state the memory will be writing from data slot to it's buffer.
	*/
	IoSlot DataDirection;
	/*
	* This value will be use to determined whether if memory use be active along with ChipSelect io slot
	*/
	Byte ActiveValue = High;
};

class MemoryIoHandler : public IoHandler
{
public:
	void SetConnection(const MemoryConnection& connection) { m_Connection = connection; }
	bool IsChipSelect();
	Word ReadAddress();
	Byte ReadData();
	Byte ReadDataDirection();
	void WriteData(Byte value);
private:
	MemoryConnection m_Connection;
};
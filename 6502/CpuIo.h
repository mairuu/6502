#pragma once

#include "Io.h"
#include "SignalEdage.h"

struct CpuConnection
{
	IoSlot Clock, Data, AddressLow, AddressHigh;
	/*
	* when high state cpu is reading from data slot.
	* when low state cpu is writing to data slot.
	*/
	IoSlot ReadWrite;
};

class CpuIoHandler : public IoHandler
{
public:
	void SetConnection(const CpuConnection& connection) { m_Connection = connection; }
	void SetAddress(Word address);
	void SetReading();
	void SetWriting();
	Byte ReadData();
	SignalEdage ReadClock();
	void WriteData(Byte value);
private:
	CpuConnection m_Connection;
};

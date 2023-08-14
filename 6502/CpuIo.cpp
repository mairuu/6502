#include "CpuIo.h"

void CpuIoHandler::SetAddress(Word address)
{
	Write(m_Connection.AddressLow,  (address & 0x00ff) >> 0);
	Write(m_Connection.AddressHigh, (address & 0xff00) >> 8);
}

void CpuIoHandler::SetReading()
{
	Write(m_Connection.ReadWrite, High);
}

void CpuIoHandler::SetWriting()
{
	Write(m_Connection.ReadWrite, Low);
}

Byte CpuIoHandler::ReadData()
{
	return Read(m_Connection.Data);
}

SignalEdage CpuIoHandler::ReadClock()
{
	return SignalEdage::From(Read(m_Connection.Clock));
}

void CpuIoHandler::WriteData(Byte byte)
{
	Write(m_Connection.Data, byte);
}
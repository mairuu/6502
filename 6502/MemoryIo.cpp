#include "MemoryIo.h"

Word MemoryIoHandler::ReadAddress()
{
	return Read(m_Connection.AddressLow) | (Read(m_Connection.AddressHigh) << 8);
}

Byte MemoryIoHandler::ReadData()
{
	return Read(m_Connection.Data);
}

Byte MemoryIoHandler::ReadDataDirection()
{
	return Read(m_Connection.DataDirection);
}

bool MemoryIoHandler::IsChipSelect()
{
	return Read(m_Connection.ChipSelect) == m_Connection.ActiveValue;
}

void MemoryIoHandler::WriteData(Byte value)
{
	Write(m_Connection.Data, value);
}

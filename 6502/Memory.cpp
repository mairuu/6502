#include "Memory.h"

Memory::Memory(Word size, bool enableWriting)
	: m_Size(size), m_EnableWriting(enableWriting)
{
	m_Buffer = new Byte[size];
}

Memory::~Memory()
{
	delete[] m_Buffer;
}

void Memory::Connect(IoBoard* board, const MemoryConnection& connection)
{
	m_IoHandler.SetBoard(board);
	m_IoHandler.SetConnection(connection);
}

void Memory::Reset()
{
	for (Word i = 0; i < m_Size; i++)
	{
		m_Buffer[i] = 0;
	}
}

void Memory::Update()
{
	if (!m_IoHandler.IsChipSelect())
	{
		return;
	}

	bool isWriting = m_IoHandler.ReadDataDirection() == Low;
	// bool isReading = m_IoHandler.ReadDataDirection() == High;
	bool isReading = !isWriting;

	if (isReading)
	{
		Word address = m_IoHandler.ReadAddress();
		m_IoHandler.WriteData(m_Buffer[address]);
		return;
	}

	if (isWriting && m_EnableWriting)
	{
		Word address = m_IoHandler.ReadAddress();
		m_Buffer[address] = m_IoHandler.ReadData();
	}
}
 
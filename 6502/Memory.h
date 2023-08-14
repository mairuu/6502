#pragma once

#include "MemoryIo.h"

class Memory
{
public:
	Memory(Word size, bool enableWriting = true);
	~Memory();
	Byte& operator[](Word i) { return m_Buffer[i]; }
	void Connect(IoBoard* board, const MemoryConnection& connection);
	void Reset();
	void Update();
private:
	Word m_Size = 0;
	bool m_EnableWriting = false;
	Byte* m_Buffer = nullptr;
	MemoryIoHandler m_IoHandler;
};
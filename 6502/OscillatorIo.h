#pragma once

#include "Io.h"
#include "SignalEdage.h"

struct OscillatorConnection
{
	IoSlot Clock;
};

class OscillatorIoHander : public IoHandler
{
public:
	void WriteClock(SignalEdage clockEdage);
	void SetConnection(const OscillatorConnection& connection) { m_Connection = connection; }
private:
	OscillatorConnection m_Connection;
};
#pragma once

#include "OscillatorIo.h"

class Oscillator
{
public:
	void Connect(IoBoard* board, const OscillatorConnection& connection);
	void Oscillate();
private:
	SignalEdage m_ClockEdage;
	OscillatorIoHander m_IoHandler;
};

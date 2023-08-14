#include "OscillatorIo.h"

void OscillatorIoHander::WriteClock(SignalEdage clockEdage)
{
	Write(m_Connection.Clock, (Byte)(clockEdage));
}

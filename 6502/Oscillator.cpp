#include "Oscillator.h"


void Oscillator::Connect(IoBoard* board, const OscillatorConnection& connection)
{
	m_IoHandler.SetBoard(board);
	m_IoHandler.SetConnection(connection);
}

void Oscillator::Oscillate()
{
	m_ClockEdage.NextEdage();
	m_IoHandler.WriteClock(m_ClockEdage);
}

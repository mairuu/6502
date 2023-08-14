#include "SignalEdage.h"

void SignalEdage::NextEdage()
{
	m_Edage = (m_Edage == Edage::Falling)
		? Edage::Rising
		: Edage::Falling;
}

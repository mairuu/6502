#pragma once

#include "Base.h"

class SignalEdage
{
public:
	enum Edage : Byte
	{
		Falling = 0, Rising = 1,
	};

	SignalEdage(Edage edage = Edage::Falling)
		: m_Edage(edage) {}

	static SignalEdage From(Byte byte) { return SignalEdage(byte ? Rising : Falling); }
	operator Byte() { return (Byte)m_Edage; }

	bool IsRising() { return m_Edage == Rising; }
	bool IsFalling() { return m_Edage == Falling; }

	void NextEdage();
private:
	Edage m_Edage;
};
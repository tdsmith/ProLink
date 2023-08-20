#include "StdAfx.h"
#include "rlfrequency.h"

rlFrequency::rlFrequency (const double dfFrequency, const rlFrequency::FrequencyUnits DefaultUnits)
{
	m_DefaultUnits = DefaultUnits;
	SetFrequency (dfFrequency);
}

rlFrequency::~rlFrequency (void)
{
}

rlFrequency::FrequencyUnits rlFrequency::GetDefaultUnits (void)
{
	return m_DefaultUnits;
}

void rlFrequency::SetDefaultUnits (const rlFrequency::FrequencyUnits DefaultUnits)
{
	m_DefaultUnits = DefaultUnits;
}

double rlFrequency::GetFrequency (void) const
{
	switch (m_DefaultUnits)
	{
		case KHz:
			return GetFrequencyKHz ();
		case MHz:
			return GetFrequencyMHz ();
		case GHz:
			return GetFrequencyGHz ();
		case unknown:
		case Hz:
		default:
			return GetFrequencyHz ();
	}
}

double rlFrequency::GetFrequencyHz (void) const
{
	return m_dfFrequencyHz;
}

double rlFrequency::GetFrequencyKHz (void) const
{
	return m_dfFrequencyHz / 1000;
}

double rlFrequency::GetFrequencyMHz (void) const
{
	return m_dfFrequencyHz / 1000000;
}

double rlFrequency::GetFrequencyGHz (void) const
{
	return m_dfFrequencyHz / 1000000000;
}

void rlFrequency::SetFrequency (const double dfFrequency)
{
	switch (m_DefaultUnits)
	{
		case unknown:
		case Hz:
			SetFrequencyHz (dfFrequency);
		case KHz:
			SetFrequencyKHz (dfFrequency);
		case MHz:
			SetFrequencyMHz (dfFrequency);
		case GHz:
			SetFrequencyGHz (dfFrequency);
	}
}

void rlFrequency::SetFrequencyHz (const double dfFrequencyHz)
{
	m_dfFrequencyHz = dfFrequencyHz;
}

void rlFrequency::SetFrequencyKHz (const double dfFrequencyKHz)
{
	m_dfFrequencyHz = dfFrequencyKHz * 1000;
}

void rlFrequency::SetFrequencyMHz (const double dfFrequencyMHz)
{
	m_dfFrequencyHz = dfFrequencyMHz * 1000000;
}

void rlFrequency::SetFrequencyGHz (const double dfFrequencyGHz)
{
	m_dfFrequencyHz = dfFrequencyGHz * 1000000000;
}


rlFrequency &rlFrequency::operator= (double dfFrequency)
{
	SetFrequency (dfFrequency);

	return *this;
}

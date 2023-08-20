#include "StdAfx.h"
#include "rlmemorychannel.h"

rlMemoryChannel::rlMemoryChannel(void)
{
	Empty ();
}

rlMemoryChannel::~rlMemoryChannel(void)
{
}

void rlMemoryChannel::Empty (void)
{
	m_nChannelNumber = 0;
	m_Frequency = 0;
	m_strDescription.Empty ();
	m_strCarNumber.Empty ();
	m_bDelay = false;
	m_bLockout = false;
	m_bPriority = false;
}

const int rlMemoryChannel::GetChannelNumber (void) const
{
	return m_nChannelNumber;
}

void rlMemoryChannel::SetChannelNumber (const int nChannelNumber)
{
	m_nChannelNumber = nChannelNumber;
}

const rlFrequency rlMemoryChannel::GetFrequency (void) const
{
	return m_Frequency;
}

void rlMemoryChannel::SetFrequency (const rlFrequency *pFrequency)
{
	m_Frequency = *pFrequency;
}

const CString rlMemoryChannel::GetDescription (void) const
{
	return m_strDescription;
}

void rlMemoryChannel::SetDescription (const CString strDescription)
{
	m_strDescription = strDescription;
}

const CString rlMemoryChannel::GetCarNumber (void) const
{
	return m_strCarNumber;
}

void rlMemoryChannel::SetCarNumber (const CString strCarNumber)
{
	// TODO: add verification here
	m_strCarNumber = strCarNumber;
}

const bool rlMemoryChannel::GetDelay (void) const
{
	return m_bDelay;
}

void rlMemoryChannel::SetDelay (const bool bDelay)
{
	m_bDelay = bDelay;
}

const bool rlMemoryChannel::GetLockout (void) const
{
	return m_bLockout;
}

void rlMemoryChannel::SetLockout (const bool bLockout)
{
	m_bLockout = bLockout;
}

const bool rlMemoryChannel::GetPriority (void) const
{
	return m_bPriority;
}

void rlMemoryChannel::SetPriority (const bool bPriority)
{
	m_bPriority = bPriority;
}

// this should make copying freqs a ton easier eh?
// rlMemoryChannel rlMemoryChannel::operator=
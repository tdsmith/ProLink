#include "StdAfx.h"
#include "rlmemorylayout.h"

rlMemoryLayout::rlMemoryLayout(void)
{
	m_nFirstChannel = 0;
	m_nFirstBank = 0;
	m_nBankCount = 0;
	m_nBankSize = 0;
}

rlMemoryLayout::~rlMemoryLayout(void)
{
}

const int rlMemoryLayout::GetFirstChannel (void)
{
	return m_nFirstChannel;
}

void rlMemoryLayout::SetFirstChannel (const int nFirstChannel)
{
	m_nFirstChannel = nFirstChannel;
}

const int rlMemoryLayout::GetChannelCount (void)
{
	return m_nBankCount * m_nBankSize;
}

const int rlMemoryLayout::GetLastChannel (void)
{
	return m_nFirstChannel + GetChannelCount () - 1;
}

const int rlMemoryLayout::GetFirstBank (void)
{
	return m_nFirstBank;
}

void rlMemoryLayout::SetFirstBank (const int nFirstBank)
{
	m_nFirstBank = nFirstBank;
}

const int rlMemoryLayout::GetBankCount (void)
{
	return m_nBankCount;
}

void rlMemoryLayout::SetBankCount (const int nBankCount)
{
	m_nBankCount = nBankCount;
}

const int rlMemoryLayout::GetBankSize (void)
{
	return m_nBankSize;
}

void rlMemoryLayout::SetBankSize (const int nBankSize)
{
	m_nBankSize = nBankSize;
}

const int rlMemoryLayout::GetChannelFromBankIndex (const int nBank, const int nBankIndex)
{
	return (m_nFirstChannel + ((nBank - m_nFirstBank) * m_nBankSize)) + nBankIndex;
}

const int rlMemoryLayout::GetBankFromChannel (const int nChannel)
{
	return (nChannel / m_nBankSize) + m_nFirstBank;
}

const int rlMemoryLayout::GetBankIndexFromChannel (const int nChannel)
{
	int nBank = GetBankFromChannel (nChannel);

	return m_nFirstChannel + (nChannel - ((nBank - m_nFirstBank) * m_nBankSize));
}


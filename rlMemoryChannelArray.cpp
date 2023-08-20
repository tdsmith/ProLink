#include "StdAfx.h"
#include "rlmemorychannelarray.h"

rlMemoryChannelArray::rlMemoryChannelArray (void)
{

}

rlMemoryChannelArray::~rlMemoryChannelArray (void)
{
	Empty ();
}

const INT_PTR rlMemoryChannelArray::Add (rlMemoryChannel **ppMemoryChannel)
{
	*ppMemoryChannel = new rlMemoryChannel;
	return m_MemoryChannelArray.Add (*ppMemoryChannel);
}

const INT_PTR rlMemoryChannelArray::GetCount (void) const
{
	return m_MemoryChannelArray.GetCount ();
}

rlMemoryChannel *rlMemoryChannelArray::GetAt (const INT_PTR nIndex) const
{
	return m_MemoryChannelArray.GetAt (nIndex);
}

void rlMemoryChannelArray::Empty (void)
{
	rlMemoryChannel *pMemoryChannel;

	for (int x = 0; x < m_MemoryChannelArray.GetCount (); x++)
	{
		pMemoryChannel = m_MemoryChannelArray.GetAt (x);
		delete pMemoryChannel;
	}

	m_MemoryChannelArray.RemoveAll ();
}

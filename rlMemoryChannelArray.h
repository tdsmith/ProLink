#pragma once

#include <afxtempl.h>
#include "rlMemoryChannel.h"

class rlMemoryChannelArray
{
	public:
		rlMemoryChannelArray(void);
		~rlMemoryChannelArray(void);

		const INT_PTR Add (rlMemoryChannel **);

		const INT_PTR GetCount (void) const;
		rlMemoryChannel *GetAt (const INT_PTR) const;

		void Empty (void);

	protected:
		CTypedPtrArray <CPtrArray, rlMemoryChannel *> m_MemoryChannelArray;

};

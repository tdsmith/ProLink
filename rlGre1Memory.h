#pragma once

#include "rlMemory.h"

class rlGre1Memory : public rlMemory
{
	public:
		rlGre1Memory (rlModule *);
		virtual ~rlGre1Memory (void);

		virtual HRESULT GetChannel (const int, rlMemoryChannel *);
		virtual HRESULT GetChannelRange (const int, const int, rlMemoryChannelArray *);
		virtual HRESULT GetAllChannels (rlMemoryChannelArray *);

		virtual HRESULT SetChannelSingle (const rlMemoryChannel *);

		virtual HRESULT SetChannelMultiStart (const int);
		virtual HRESULT SetChannelMultiEnd (void);
		virtual HRESULT SetChannelMulti (const rlMemoryChannel *);

		virtual HRESULT SetChannelRange (const int, const int, const rlMemoryChannelArray *);
		virtual HRESULT SetAllChannels (const rlMemoryChannelArray *);

};

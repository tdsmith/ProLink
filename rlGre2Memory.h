#pragma once
#include "rlmemory.h"

class rlGre2Memory : public rlMemory
{
	public:
		rlGre2Memory (rlModule *);
		virtual ~rlGre2Memory (void);

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

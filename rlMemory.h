#pragma once

#include "rlModule.h"
#include "rlMemoryChannel.h"
#include "rlMemoryChannelArray.h"
#include "rlProgressTarget.h"

class rlModule;

class rlMemory
{
	public:
		rlMemory (rlModule *);
		virtual ~rlMemory (void);

		virtual HRESULT SetProgressTarget (rlProgressTarget *);

		virtual HRESULT GetChannel (const int, rlMemoryChannel *);
		virtual HRESULT GetChannelRange (const int, const int, rlMemoryChannelArray *);
		virtual HRESULT GetAllChannels (rlMemoryChannelArray *);

		virtual HRESULT SetChannelSingle (const rlMemoryChannel *);

		virtual HRESULT SetChannelMultiStart (const int);
		virtual HRESULT SetChannelMultiEnd (void);
		virtual HRESULT SetChannelMulti (const rlMemoryChannel *);

		virtual HRESULT SetChannelRange (const int, const int, const rlMemoryChannelArray *);
		virtual HRESULT SetAllChannels (const rlMemoryChannelArray *);

	protected:
		rlModule *m_pModule;
		rlProgressTarget *m_pProgressTarget;

};

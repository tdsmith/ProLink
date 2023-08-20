#pragma once

#include "rlMemoryChannel.h"
#include "rlSerialLink.h"

class rlGre2Link
{
	public:
		rlGre2Link (void);
		~rlGre2Link (void);

		HRESULT SetComDevice (const CString);
		const CString GetComDevice (void);

		HRESULT SendChannelData (const rlMemoryChannel *);

		HRESULT StartMultiChannelData (void);
		HRESULT EndMultiChannelData (void);
		HRESULT SendMultiChannelData (const rlMemoryChannel *);

	protected:
		HRESULT SendStartData (void);
		HRESULT SendEndData (void);

		HRESULT SendData (const CString);

		const int CalculateChecksum (const CString);

		rlSerialLink m_SerialLink;

};

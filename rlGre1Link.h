#pragma once

#include "rlSerialLink.h"
#include "rlMemoryChannel.h"
#include "rlGre1DataFrame.h"

class rlGre1Link
{
	public:
		rlGre1Link (void);
		~rlGre1Link (void);

		HRESULT SetComParameters (const CString, const DWORD, const BYTE);

		const CString GetComDevice (void);
		const DWORD GetComBaud (void);
		const BYTE GetComStopBits (void);

		HRESULT SendChannelData (const rlMemoryChannel *);

		HRESULT StartMultiChannelData (const BYTE = 0);
		HRESULT EndMultiChannelData (void);
		HRESULT SendMultiChannelData (const rlMemoryChannel *);

	protected:
		HRESULT SendStartFrame (const BYTE = 0);
		HRESULT SendEndFrame (void);

		HRESULT SendDataFrame (const rlGre1DataFrame *);

		void AddDataParameter (CString *, const char, const CString *) const;
		void AddDataParameter (CString *, const char, const int) const;

		rlSerialLink m_SerialLink;

};

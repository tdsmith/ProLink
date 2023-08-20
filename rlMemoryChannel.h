#pragma once

#include "rlFrequency.h"

class rlMemoryChannel
{
	public:
		rlMemoryChannel(void);
		~rlMemoryChannel(void);

		void Empty (void);

		const int GetChannelNumber (void) const;
		void SetChannelNumber (const int);

		const rlFrequency GetFrequency (void) const;
		void SetFrequency (const rlFrequency *);

		const CString GetDescription (void) const;
		void SetDescription (const CString);

		const CString GetCarNumber (void) const;
		void SetCarNumber (const CString);

		const bool GetDelay (void) const;
		void SetDelay (const bool);

		const bool GetLockout (void) const;
		void SetLockout (const bool);

		const bool GetPriority (void) const;
		void SetPriority (const bool);

	protected:
		int m_nChannelNumber;
		rlFrequency m_Frequency;
		CString m_strDescription;
		CString m_strCarNumber;
		bool m_bDelay;
		bool m_bLockout;
		bool m_bPriority;

};

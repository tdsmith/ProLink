#pragma once

class rlMemoryLayout
{
	public:
		rlMemoryLayout(void);
		~rlMemoryLayout(void);

		const int GetFirstChannel (void);
		void SetFirstChannel (const int);

		const int GetChannelCount (void);
		const int GetLastChannel (void);

		const int GetFirstBank (void);
		void SetFirstBank (const int);

		const int GetBankCount (void);
		void SetBankCount (const int);

		const int GetBankSize (void);
		void SetBankSize (const int);

		const int GetChannelFromBankIndex (const int, const int);
		const int GetBankFromChannel (const int);
		const int GetBankIndexFromChannel (const int);

	protected:
		int m_nFirstChannel;
		int m_nFirstBank;

		int m_nBankCount;
		int m_nBankSize;
		
};

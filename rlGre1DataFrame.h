#pragma once

class rlGre1DataFrame
{
	public:
		rlGre1DataFrame (const BYTE = 0, const BYTE = 0, const BYTE * = NULL);
		~rlGre1DataFrame (void);

		const BYTE GetCommand (void) const;
		const BYTE GetCommandParameter (void) const;
		void SetCommand (const BYTE, const BYTE);
		void SetCommand (const BYTE);
		void SetCommandParameter (const BYTE);

		const BYTE *GetData (void) const;
		void SetData (const BYTE *);

		const BYTE GetRawDataFrame (BYTE *) const;

	protected:
		void CalculateChecksum (void);
		void CalculateMessageLength (void);
		
		BYTE m_cHeaderMarker;			// Header marker, always SCANNER_FRAME_HEADERMARKER (0x81)

		BYTE m_cMessageLength;			// Message length, not including cHeaderMarker or cChecksum

		BYTE m_cCommand;				// Command
		BYTE m_cCommandParameter;		// Parameter for command

		BYTE *m_pcData;					// Pointer to the data

		BYTE m_cChecksum;				// Checksum
};

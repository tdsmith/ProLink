#pragma once

class rlSerialLink
{
	public:
		rlSerialLink (void);
		~rlSerialLink (void);

		HRESULT SetComParameters (const CString, const DWORD, const BYTE);

		HRESULT GetComDevice (CString *);
		HRESULT SetComDevice (const CString);
		HRESULT GetComBaud (DWORD *);
		HRESULT SetComBaud (const DWORD);
		HRESULT GetComStopBits (BYTE *);
		HRESULT SetComStopBits (const BYTE);

		HRESULT ComOpen (void);
		HRESULT ComClose (void);

		HRESULT ComSend (const DWORD, const BYTE *);

	private:
		CString m_strComDevice;
		DWORD m_dwComBaud;
		BYTE m_cComStopBits;

		HANDLE m_hComDevice;
		BOOL m_bComDeviceOpen;

};

#include "StdAfx.h"
#include "rlSerialLink.h"

// wReserved is defined in richedit.h but is needed for DCB struct
#undef wReserved

rlSerialLink::rlSerialLink(void)
{
	m_bComDeviceOpen = false;
}

rlSerialLink::~rlSerialLink(void)
{
	if (m_bComDeviceOpen) ComClose ();
}

HRESULT rlSerialLink::SetComParameters (const CString strComDevice, const DWORD dwComBaud, const BYTE cComStopBits)
{
	HRESULT hResult;

	hResult = SetComDevice (strComDevice);
	if (!SUCCEEDED (hResult)) return hResult;

	hResult = SetComBaud (dwComBaud);
	if (!SUCCEEDED (hResult)) return hResult;

	hResult = SetComStopBits (cComStopBits);
	if (!SUCCEEDED (hResult)) return hResult;

	return S_OK;
}

HRESULT rlSerialLink::GetComDevice (CString *pstrComDevice)
{
	*pstrComDevice = m_strComDevice;

	return S_OK;
}

HRESULT rlSerialLink::SetComDevice (const CString strComDevice)
{
	// TODO: validate parameter data

	m_strComDevice = strComDevice;

	return S_OK;
}

HRESULT rlSerialLink::GetComBaud (DWORD *pdwComBaud)
{
	*pdwComBaud = m_dwComBaud;

	return S_OK;
}

HRESULT rlSerialLink::SetComBaud (const DWORD dwComBaud)
{
	if ((dwComBaud < 110) || (dwComBaud > 256000)) return E_INVALIDARG;

	m_dwComBaud = dwComBaud;

	return S_OK;
}

HRESULT rlSerialLink::GetComStopBits (BYTE *pcComStopBits)
{
	*pcComStopBits = m_cComStopBits;

	return S_OK;
}

HRESULT rlSerialLink::SetComStopBits (const BYTE cComStopBits)
{
	if ((cComStopBits != ONESTOPBIT) && (cComStopBits != ONE5STOPBITS) && (cComStopBits != TWOSTOPBITS)) return E_INVALIDARG;

	m_cComStopBits = cComStopBits;

	return S_OK;
}

HRESULT rlSerialLink::ComOpen (void)
{
//	GDDEBUG (0, "Attempting to open COM device %s.", m_strComDevice);

	if (m_bComDeviceOpen)
	{
//		GDDEBUG (1, "COM device %s is already open.", m_strComDevice);
		return S_OK;
	}

	DCB dcb;

	m_hComDevice = CreateFile (m_strComDevice, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
	if (m_hComDevice == INVALID_HANDLE_VALUE)
	{
		DWORD dwLastError = ::GetLastError ();
//		GDDEBUG (3, "Couldn't open COM device %s because CreateFile returned INVALID_HANDLE_VALUE.  GetLastError returned 0x%08X.", m_strComDevice, dwLastError);
		return E_FAIL;
	}

	if (!GetCommState (m_hComDevice, &dcb))
	{
//		GDDEBUG (3, "Couldn't open COM device %s because GetCommState returned FALSE.", m_strComDevice);
		return E_FAIL;
	}

	dcb.BaudRate = m_dwComBaud;
	dcb.fBinary = TRUE;
	dcb.fParity = FALSE;
	dcb.fOutxCtsFlow = FALSE;
	dcb.fOutxDsrFlow = FALSE;
	dcb.fDtrControl = DTR_CONTROL_DISABLE;
	dcb.fDsrSensitivity = FALSE;
	dcb.fOutX = FALSE;
	dcb.fInX = FALSE;
	dcb.fErrorChar = FALSE;
	dcb.fNull = FALSE;
	dcb.fRtsControl = RTS_CONTROL_DISABLE;
	dcb.fAbortOnError = FALSE;
	dcb.wReserved = 0;
	dcb.ByteSize = 8;
	dcb.Parity = NOPARITY;
	dcb.StopBits = m_cComStopBits;

	if (!SetCommState (m_hComDevice, &dcb))
	{
//		GDDEBUG (3, "Couldn't open COM device %s because SetCommState returned FALSE.", m_strComDevice);
		return E_FAIL;
	}

	m_bComDeviceOpen = true;

//	GDDEBUG (0, "COM device %s was opened successfully.", m_strComDevice);

	return S_OK;
}

HRESULT rlSerialLink::ComClose (void)
{
//	GDDEBUG (0, "Attempting to close COM device %s.", m_strComDevice);

	if (!m_bComDeviceOpen)
	{
//		GDDEBUG (1, "Couldn't close COM device %s because it is not open.", m_strComDevice);
		return S_OK;
	}

	if (!CloseHandle (m_hComDevice))
	{
//		GDDEBUG (2, "Couldn't close COM device %s because CloseHandle returned FALSE.", m_strComDevice);
		return E_FAIL;
	}

	m_bComDeviceOpen = false;

//	GDDEBUG (0, "COM device %s was closed successfully.", m_strComDevice);

	return S_OK;
}

HRESULT rlSerialLink::ComSend (const DWORD dwBufferLength, const BYTE *pSendBuffer)
{
//	GDDEBUG (0, "ComSend is attempting to send the following data:");
//	gdGetDebug ()->MessageBinary (0, dwBufferLength, pSendBuffer);

	if (!m_bComDeviceOpen)
	{
//		GDDEBUG (3, "ComSend could not send data because the COM device is not open.");
		return E_FAIL;
	}

	DWORD dwBytesWritten;

	if (!::WriteFile (m_hComDevice, pSendBuffer, dwBufferLength, &dwBytesWritten, NULL))
	{
//		GDDEBUG (3, "::WriteFile () failed.");
		return E_FAIL;
	}

	if (dwBytesWritten != dwBufferLength)
	{
//		GDDEBUG (2, "ComSend failed because WriteFile said it wrote %d bytes when it was supposed to write %d bytes.", dwBytesWritten, dwBufferLength);
		return E_FAIL;
	}

	return S_OK;
}

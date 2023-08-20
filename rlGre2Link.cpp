#include "StdAfx.h"
#include "rlgre2link.h"

rlGre2Link::rlGre2Link(void)
{
}

rlGre2Link::~rlGre2Link(void)
{
}

HRESULT rlGre2Link::SetComDevice (const CString strComDevice)
{
	return m_SerialLink.SetComParameters (strComDevice, 2400, 2);
}

const CString rlGre2Link::GetComDevice (void)
{
	CString strComDevice;
	m_SerialLink.GetComDevice (&strComDevice);

	return strComDevice;
}

HRESULT rlGre2Link::SendChannelData (const rlMemoryChannel *pChannelData)
{
	HRESULT hResult;

	hResult = StartMultiChannelData ();
	if (!SUCCEEDED (hResult)) return hResult;

	hResult = SendMultiChannelData (pChannelData);
	if (!SUCCEEDED (hResult)) return hResult;

	hResult = EndMultiChannelData ();
	if (!SUCCEEDED (hResult)) return hResult;

	return S_OK;
}

HRESULT rlGre2Link::StartMultiChannelData (void)
{
	HRESULT hResult;

	hResult = m_SerialLink.ComOpen ();
	if (!SUCCEEDED (hResult)) return hResult;

	hResult = SendStartData ();
	if (!SUCCEEDED (hResult)) return hResult;

	return S_OK;
}

HRESULT rlGre2Link::EndMultiChannelData (void)
{
	HRESULT hResult;

	hResult = SendEndData ();
	if (!SUCCEEDED (hResult)) return hResult;

	hResult = m_SerialLink.ComClose ();
	if (!SUCCEEDED (hResult)) return hResult;

	return S_OK;
}

HRESULT rlGre2Link::SendMultiChannelData (const rlMemoryChannel *pChannelData)
{
	CString strData;
	CString strTemp;

	strData = "$902,";

	if (pChannelData->GetChannelNumber () == 0) return S_OK;

	strTemp.Format ("%04u", pChannelData->GetChannelNumber ());
	strData += strTemp;

	strData += ',';

	double dfFrequency = pChannelData->GetFrequency ().GetFrequencyMHz ();

	strTemp.Format ("%09.4f", dfFrequency);
	strData += strTemp;

	strData += ",1*";

	strTemp.Format ("%02X", CalculateChecksum (strData));

	strData += strTemp;

	HRESULT hResult = SendData (strData);
	if (!SUCCEEDED (hResult)) return hResult;

	return S_OK;
}

HRESULT rlGre2Link::SendStartData (void)
{
	return SendData ("$999*F9");
}

HRESULT rlGre2Link::SendEndData (void)
{
	return SendData ("$904*EB");
}

HRESULT rlGre2Link::SendData (const CString strData)
{
	int nLength = strData.GetLength () + 3;
	BYTE *pcDataFrame = DEBUG_NEW BYTE [nLength];
	strncpy ((char *) pcDataFrame, strData, nLength);
	pcDataFrame [nLength - 3] = '\x0D';
	pcDataFrame [nLength - 2] = '\x0A';
	pcDataFrame [nLength - 1] = '\0';

	HRESULT hResult = m_SerialLink.ComSend (nLength, (BYTE *) pcDataFrame);

	delete pcDataFrame;

	if (FAILED (hResult)) return hResult;

	return S_OK;
}

const int rlGre2Link::CalculateChecksum (const CString strData)
{
	CString strTemp = strData;
	char cTemp;
	int nChecksum = 0;

	for (int x = 0; x < strTemp.GetLength (); x++)
	{
		cTemp = cTemp = strTemp.GetAt (x);

		if ((cTemp >= 0x30) && (cTemp <= 0x39)) // numbers 0-9
		{
			nChecksum += (cTemp - 0x30);
		}
	}
	
	return nChecksum;
}


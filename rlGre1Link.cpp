#include "StdAfx.h"
#include "rlGre1Link.h"

#include "rlGre1Module.h"
#include "rlGre1DataFrame.h"

rlGre1Link::rlGre1Link (void)
{

}

rlGre1Link::~rlGre1Link (void)
{

}

HRESULT rlGre1Link::SetComParameters (const CString strComDevice, const DWORD dwBaud, const BYTE cStopBits)
{
	return m_SerialLink.SetComParameters (strComDevice, dwBaud, cStopBits);
}

const CString rlGre1Link::GetComDevice (void)
{
	CString strComDevice;
	m_SerialLink.GetComDevice (&strComDevice);

	return strComDevice;
}

const DWORD rlGre1Link::GetComBaud (void)
{
	DWORD dwComBaud;
	m_SerialLink.GetComBaud (&dwComBaud);

	return dwComBaud;
}

const BYTE rlGre1Link::GetComStopBits (void)
{
	BYTE cComStopBits;
	m_SerialLink.GetComStopBits (&cComStopBits);

	return cComStopBits;
}

HRESULT rlGre1Link::SendChannelData (const rlMemoryChannel *pChannelData)
{
	HRESULT hResult;

	hResult = StartMultiChannelData (1);
	if (!SUCCEEDED (hResult)) return hResult;

	hResult = SendMultiChannelData (pChannelData);
	if (!SUCCEEDED (hResult)) return hResult;

	hResult = EndMultiChannelData ();
	if (!SUCCEEDED (hResult)) return hResult;

	return S_OK;
}

HRESULT rlGre1Link::StartMultiChannelData (const BYTE cFrames)
{
	HRESULT hResult;

	hResult = m_SerialLink.ComOpen ();
	if (!SUCCEEDED (hResult)) return hResult;

	hResult = SendStartFrame (cFrames);
	if (!SUCCEEDED (hResult)) return hResult;

	return S_OK;
}

HRESULT rlGre1Link::EndMultiChannelData (void)
{
	HRESULT hResult;

	hResult = SendEndFrame ();
	if (!SUCCEEDED (hResult)) return hResult;

	hResult = m_SerialLink.ComClose ();
	if (!SUCCEEDED (hResult)) return hResult;

	return S_OK;
}

HRESULT rlGre1Link::SendMultiChannelData (const rlMemoryChannel *pChannelData)
{
	CString strData;

	if (pChannelData->GetChannelNumber () != 0) AddDataParameter (&strData, 'C', pChannelData->GetChannelNumber ());

	CString strCarNumber = pChannelData->GetCarNumber ();
	if (!strCarNumber.IsEmpty ()) AddDataParameter (&strData, 'V', &strCarNumber);

	double dfFrequency = pChannelData->GetFrequency ().GetFrequencyMHz ();

	CString strFrequency;
	strFrequency.Format ("%08.4f", dfFrequency);

	CString strDelay (pChannelData->GetDelay ()?'S':'R');
	CString strLockout (pChannelData->GetLockout ()?'S':'R');
	CString strPriority (pChannelData->GetPriority ()?'S':'R');

	AddDataParameter (&strData, 'F', &strFrequency);
	AddDataParameter (&strData, 'D', &strDelay);
	AddDataParameter (&strData, 'L', &strLockout);
	AddDataParameter (&strData, 'P', &strPriority);

	BYTE *pcBuffer = (BYTE *) strData.GetBuffer (255);

	rlGre1DataFrame DataFrame (GRE1_COMMAND_CHANNELDATA, 0x00, pcBuffer);

	strData.ReleaseBuffer (-1);

	HRESULT hResult = SendDataFrame (&DataFrame);
	if (!SUCCEEDED (hResult)) return hResult;

	return S_OK;
}

HRESULT rlGre1Link::SendStartFrame (const BYTE cFrames)
{
	rlGre1DataFrame DataFrame (GRE1_COMMAND_STARTCOMMUNICATIONS, 0x01, &cFrames);
	return SendDataFrame (&DataFrame);
}

HRESULT rlGre1Link::SendEndFrame (void)
{
	rlGre1DataFrame DataFrame (GRE1_COMMAND_ENDCOMMUNICATIONS, 0x01, 0x00);
	return SendDataFrame (&DataFrame);
}

HRESULT rlGre1Link::SendDataFrame (const rlGre1DataFrame *pDataFrame)
{
	BYTE pcDataFrame [255];
	BYTE cDataFrameLength = pDataFrame->GetRawDataFrame (pcDataFrame);

	HRESULT hResult = m_SerialLink.ComSend (cDataFrameLength, (BYTE *) pcDataFrame);
	if (!SUCCEEDED (hResult)) return hResult;

	return S_OK;
}

void rlGre1Link::AddDataParameter (CString *pstrData, const char cKey, const CString *pstrValue) const
{
	CString strParameter;
	CString strKey;
	strKey = cKey;

	strParameter.Format ("%s%s^", strKey, *pstrValue);
	(*pstrData) += strParameter;
}

void rlGre1Link::AddDataParameter (CString *pstrData, const char cKey, const int nValue) const
{
	CString strValue;
	strValue.Format ("%d", nValue);

	AddDataParameter (pstrData, cKey, &strValue);
}

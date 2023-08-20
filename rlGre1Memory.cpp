#include "StdAfx.h"
#include "rlGre1Memory.h"

#include "rlGre1Module.h"
#include "rlGre1Link.h"


rlGre1Memory::rlGre1Memory (rlModule *pModule) : rlMemory (pModule)
{
}

rlGre1Memory::~rlGre1Memory (void)
{
}

HRESULT rlGre1Memory::GetChannel (const int, rlMemoryChannel *)
{
	return E_NOTIMPL;
}

HRESULT rlGre1Memory::GetChannelRange (const int, const int, rlMemoryChannelArray *)
{
	return E_NOTIMPL;
}

HRESULT rlGre1Memory::GetAllChannels (rlMemoryChannelArray *)
{
	return E_NOTIMPL;
}

HRESULT rlGre1Memory::SetChannelSingle (const rlMemoryChannel *pMemoryChannel)
{
	HRESULT hResult;

	hResult = SetChannelMultiStart (1);
	if (!SUCCEEDED (hResult)) return hResult;

	hResult = SetChannelMulti (pMemoryChannel);
	if (!SUCCEEDED (hResult)) return hResult;

	hResult = SetChannelMultiEnd ();
	if (!SUCCEEDED (hResult)) return hResult;

	return S_OK;
}

HRESULT rlGre1Memory::SetChannelMultiStart (const int nCount)
{
	HRESULT hResult;

	if (!((rlGre1Module *)(m_pModule))->ShowTransferInstructionsDlg ()) return S_FALSE;

	rlGre1Link *pGre1Link;
	hResult = ((rlGre1Module *) m_pModule)->GetLink (&pGre1Link);
	if (FAILED (hResult)) return hResult;

	hResult = pGre1Link->StartMultiChannelData ((BYTE) nCount);
	if (FAILED (hResult)) return hResult;

	return S_OK;
}

HRESULT rlGre1Memory::SetChannelMultiEnd (void)
{
	HRESULT hResult;

	rlGre1Link *pGre1Link;
	hResult = ((rlGre1Module *) m_pModule)->GetLink (&pGre1Link);
	if (FAILED (hResult)) return hResult;

	hResult = pGre1Link->EndMultiChannelData ();
	if (FAILED (hResult)) return hResult;

	return S_OK;
}

HRESULT rlGre1Memory::SetChannelMulti (const rlMemoryChannel *pMemoryChannel)
{
	HRESULT hResult;

	rlGre1Link *pGre1Link;
	hResult = ((rlGre1Module *) m_pModule)->GetLink (&pGre1Link);
	if (FAILED (hResult)) return hResult;

	hResult = pGre1Link->SendMultiChannelData (pMemoryChannel);
	if (FAILED (hResult)) return hResult;

	return S_OK;
}

HRESULT rlGre1Memory::SetChannelRange (const int nFirst, const int nLast, const rlMemoryChannelArray *pMemoryChannelArray)
{
	if (!((rlGre1Module *)(m_pModule))->ShowTransferInstructionsDlg ()) return S_FALSE;

	HRESULT hResult;

	int nCount = nLast - nFirst;

	hResult = SetChannelMultiStart (nCount);
	if (FAILED (hResult)) return hResult;

	if (m_pProgressTarget != NULL) m_pProgressTarget->OnSetRange (nFirst, nLast);

	rlMemoryChannel *pMemoryChannel;

	if (nFirst > 200)
	{
		AfxMessageBox("You cannot upload the dummy bank.", MB_OK);
	}
	else
	{

		for (int x = nFirst; x < nLast; x++)
		{
			if (m_pProgressTarget != NULL) m_pProgressTarget->OnSetPosition (x);

			pMemoryChannel = pMemoryChannelArray->GetAt (x);

			hResult = SetChannelMulti (pMemoryChannel);
			if (FAILED (hResult)) return hResult;
		}

		hResult = SetChannelMultiEnd ();
	}
/*
	if (FAILED (hResult))
	{
		GDDEBUGHRESULT (3, _T("rlGre1Memory::SetChannelMultiEnd ()"), hResult);
		return hResult;
	}
*/
	return S_OK;
}

HRESULT rlGre1Memory::SetAllChannels (const rlMemoryChannelArray *pMemoryChannelArray)
{
	int nCount = (int) pMemoryChannelArray->GetCount ();
	if (nCount > 200) nCount = 200;

	return SetChannelRange (0, nCount, pMemoryChannelArray);
}

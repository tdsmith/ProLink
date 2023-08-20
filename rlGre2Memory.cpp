#include "StdAfx.h"
#include "rlGre2Memory.h"

#include "rlGre2Module.h"
#include "rlGre2Link.h"

rlGre2Memory::rlGre2Memory (rlModule *pModule) : rlMemory (pModule)
{
}

rlGre2Memory::~rlGre2Memory (void)
{
}

HRESULT rlGre2Memory::GetChannel (const int, rlMemoryChannel *)
{
	return E_NOTIMPL;
}

HRESULT rlGre2Memory::GetChannelRange (const int, const int, rlMemoryChannelArray *)
{
	return E_NOTIMPL;
}

HRESULT rlGre2Memory::GetAllChannels (rlMemoryChannelArray *)
{
	return E_NOTIMPL;
}

HRESULT rlGre2Memory::SetChannelSingle (const rlMemoryChannel *pMemoryChannel)
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

HRESULT rlGre2Memory::SetChannelMultiStart (const int)
{
	HRESULT hResult;

	rlGre2Link *pGre2Link;
	hResult = ((rlGre2Module *) m_pModule)->GetLink (&pGre2Link);
	if (!SUCCEEDED (hResult)) return hResult;

	hResult = pGre2Link->StartMultiChannelData ();
	if (!SUCCEEDED (hResult)) return hResult;

	return S_OK;
}

HRESULT rlGre2Memory::SetChannelMultiEnd (void)
{
	HRESULT hResult;

	rlGre2Link *pGre2Link;
	hResult = ((rlGre2Module *) m_pModule)->GetLink (&pGre2Link);
	if (!SUCCEEDED (hResult)) return hResult;

	hResult = pGre2Link->EndMultiChannelData ();
	if (FAILED (hResult)) return hResult;

	return S_OK;
}

HRESULT rlGre2Memory::SetChannelMulti (const rlMemoryChannel *pMemoryChannel)
{
	HRESULT hResult;

	rlGre2Link *pGre2Link;
	hResult = ((rlGre2Module *) m_pModule)->GetLink (&pGre2Link);
	if (!SUCCEEDED (hResult)) return hResult;

	hResult = pGre2Link->SendMultiChannelData (pMemoryChannel);
	if (FAILED (hResult)) return hResult;

	return S_OK;
}

HRESULT rlGre2Memory::SetChannelRange (const int nFirst, const int nLast, const rlMemoryChannelArray *pMemoryChannelArray)
{
	HRESULT hResult;

	int nCount = nLast - nFirst;

	hResult = SetChannelMultiStart (nCount);
	if (FAILED (hResult)) return hResult;

	if (m_pProgressTarget != NULL) m_pProgressTarget->OnSetRange (nFirst, nLast);

	rlMemoryChannel *pMemoryChannel;

	for (int x = nFirst; x < nLast; x++)
	{
		if (m_pProgressTarget != NULL) m_pProgressTarget->OnSetPosition (x);

		pMemoryChannel = pMemoryChannelArray->GetAt (x);

		hResult = SetChannelMulti (pMemoryChannel);
		if (FAILED (hResult)) return hResult;
	}
 
	hResult = SetChannelMultiEnd ();
	if (FAILED (hResult)) return hResult;

	return S_OK;
}

HRESULT rlGre2Memory::SetAllChannels (const rlMemoryChannelArray *pMemoryChannelArray)
{
	int nCount = (int) pMemoryChannelArray->GetCount ();
	if (nCount > 400) nCount = 400;

	return SetChannelRange (0, nCount, pMemoryChannelArray);
}

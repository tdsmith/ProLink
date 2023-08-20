#include "StdAfx.h"
#include "rlmemory.h"

#include "rlModule.h"

#include "ProLinkView.h"

rlMemory::rlMemory (rlModule *pModule)
{
	m_pModule = pModule;
	m_pProgressTarget = NULL;
}

rlMemory::~rlMemory (void)
{
}

HRESULT rlMemory::SetProgressTarget (rlProgressTarget *pProgressTarget)
{
	m_pProgressTarget = pProgressTarget;

	return S_OK;
}

HRESULT rlMemory::GetChannel (const int, rlMemoryChannel *)
{
	return E_NOTIMPL;
}

HRESULT rlMemory::GetChannelRange (const int, const int, rlMemoryChannelArray *)
{
	return E_NOTIMPL;
}

HRESULT rlMemory::GetAllChannels (rlMemoryChannelArray *)
{
	return E_NOTIMPL;
}

HRESULT rlMemory::SetChannelSingle (const rlMemoryChannel *)
{
	return E_NOTIMPL;
}

HRESULT rlMemory::SetChannelMultiStart (const int)
{
	return E_NOTIMPL;
}

HRESULT rlMemory::SetChannelMultiEnd (void)
{
	return E_NOTIMPL;
}

HRESULT rlMemory::SetChannelMulti (const rlMemoryChannel *)
{
	return E_NOTIMPL;
}

HRESULT rlMemory::SetChannelRange (const int, const int, const rlMemoryChannelArray *)
{
	return E_NOTIMPL;
}

HRESULT rlMemory::SetAllChannels (const rlMemoryChannelArray *)
{
	return E_NOTIMPL;
}

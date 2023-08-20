#include "StdAfx.h"
#include "rlgre3module.h"

rlGre3Module::rlGre3Module (void)
{
	m_MemoryLayout.SetFirstChannel (1);
	m_MemoryLayout.SetFirstBank (1);
	m_MemoryLayout.SetBankCount (10);
	m_MemoryLayout.SetBankSize (20);
}

rlGre3Module::~rlGre3Module (void)
{
}

HRESULT rlGre3Module::GetModuleIdentifier (LPTSTR *plpIndentifier)
{
	*plpIndentifier = _T("GCS-GRE3");
	return S_OK;
}

HRESULT rlGre3Module::GetName(LPTSTR *plpName)
{
	*plpName = _T("RadioShack Clone Protocol Scanners by GRE");
	return S_OK;
}

HRESULT rlGre3Module::GetDescription(LPTSTR *plpDescription)
{
	*plpDescription = _T("This module implements a serial interface to Radio Shack scanners made by GRE that use the RadioShack Clone Protocol including the Pro-92 and Pro-2067.");

	return S_OK;
}


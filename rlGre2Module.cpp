#include "StdAfx.h"
#include "rlGre2Module.h"

#include "rlGre2PropertiesDlg.h"

rlGre2Module::rlGre2Module (void)
{
	m_pGre2Link = DEBUG_NEW rlGre2Link ();
	m_pMemory = DEBUG_NEW rlGre2Memory (this);

	m_MemoryLayout.SetFirstChannel (1);
	m_MemoryLayout.SetFirstBank (1);
	m_MemoryLayout.SetBankCount (10);
	m_MemoryLayout.SetBankSize (40);

	CString strComPort = AfxGetApp ()->GetProfileString (_T("RadioLink\\Gre2"), _T("Communications Port"), _T("COM1"));

	m_pGre2Link->SetComDevice (strComPort);
}

rlGre2Module::~rlGre2Module (void)
{
	delete m_pGre2Link;
	delete m_pMemory;
}

HRESULT rlGre2Module::GetModuleIdentifier (LPTSTR *plpIndentifier)
{
	*plpIndentifier = _T("GCS-GRE2");
	return S_OK;
}

HRESULT rlGre2Module::GetName(LPTSTR *plpName)
{
	*plpName = _T("RadioShack GRE Radio Interface Protocol Scanners by GRE");
	return S_OK;
}

HRESULT rlGre2Module::GetDescription(LPTSTR *plpDescription)
{
	*plpDescription = _T("This module implements a one-way serial interface to Radio Shack scanners made by GRE that use the GRE Radio Interface Protocol (GRIP) including the Pro-64 and Pro-2041.");

	return S_OK;
}

HRESULT rlGre2Module::ShowPropertiesDlg (void)
{
	rlGre2PropertiesDlg dlgProperties;

	dlgProperties.m_strPort = m_pGre2Link->GetComDevice ();

	if (dlgProperties.DoModal () == IDCANCEL) return S_OK;

	AfxGetApp ()->WriteProfileString (_T("RadioLink\\Gre2"), _T("Communications Port"), dlgProperties.m_strPort);

	m_pGre2Link->SetComDevice (dlgProperties.m_strPort);

	return S_OK;
}

HRESULT rlGre2Module::GetLink (rlGre2Link **ppGre2Link)
{
	*ppGre2Link = m_pGre2Link;

	return S_OK;
}

HRESULT rlGre2Module::GetMemory (rlMemory **ppMemory)
{
	*ppMemory = m_pMemory;

	return S_OK;
}

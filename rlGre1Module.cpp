#include "StdAfx.h"
#include "rlgre1module.h"

#include "rlGre1PropertiesDlg.h"
#include "rlGre1TransferInstructionsDlg.h"

rlGre1Module::rlGre1Module (void)
{
	m_pGre1Link = DEBUG_NEW rlGre1Link ();
	m_pMemory = DEBUG_NEW rlGre1Memory (this);

	m_MemoryLayout.SetFirstChannel (1);
	m_MemoryLayout.SetFirstBank (1);
	m_MemoryLayout.SetBankCount (10);
	m_MemoryLayout.SetBankSize (20);

	CString strComPort = AfxGetApp ()->GetProfileString (_T("RadioLink\\Gre1"), _T("Communications Port"), _T("COM1"));
	DWORD dwBaud = AfxGetApp ()->GetProfileInt (_T("RadioLink\\Gre1"), _T("Baud"), 4800);
	BYTE cStopBits = (unsigned char) AfxGetApp ()->GetProfileInt (_T("RadioLink\\Gre1"), _T("Stop Bits"), 2);
	CString nPriorityChannels = AfxGetApp ()->GetProfileString (_T("RadioLink\\Gre1"), _T("Priority Channels"), "(Custom)");

	m_pGre1Link->SetComParameters (strComPort, dwBaud, cStopBits);

	m_bShowTransferInstructions = (AfxGetApp ()->GetProfileInt (_T("RadioLink\\Gre1"), _T("Show Transfer Instructions"), TRUE))?true:false;
}

rlGre1Module::~rlGre1Module (void)
{
	delete m_pGre1Link;
	delete m_pMemory;
}

HRESULT rlGre1Module::GetModuleIdentifier (LPTSTR *plpIndentifier)
{
	*plpIndentifier = _T("GCS-GRE1");
	return S_OK;
}

HRESULT rlGre1Module::GetName(LPTSTR *plpName)
{
	*plpName = _T("RadioShack Scanner Control Protocol Scanners by GRE");
	return S_OK;
}

HRESULT rlGre1Module::GetDescription(LPTSTR *plpDescription)
{
	*plpDescription = _T("This module implements a one-way serial interface to Radio Shack scanners made by GRE that use the RadioShack Scanner Control Protocol including the Pro-76, Pro-79, Pro-82, Pro-89, Pro-2016 and Pro-2017.");

	return S_OK;
}

HRESULT rlGre1Module::ShowPropertiesDlg (void)
{
	CString strTemp;
	rlGre1PropertiesDlg dlg;

	dlg.m_strModel = AfxGetApp ()->GetProfileString (_T("RadioLink\\Gre1"), _T("Scanner Model"), _T("RadioShack Pro-89"));
	dlg.m_bCarNumbers = AfxGetApp ()->GetProfileInt (_T("RadioLink\\Gre1"), _T("Car Numbers"), TRUE);

	dlg.m_strPort = m_pGre1Link->GetComDevice ();

	strTemp.Format ("%d", m_pGre1Link->GetComBaud ());
	dlg.m_strSpeed = strTemp;

	strTemp.Format ("%u", m_pGre1Link->GetComStopBits ());
	dlg.m_strStopBits = strTemp;

	dlg.m_nPriorityChannels = AfxGetApp ()->GetProfileString (_T("RadioLink\\Gre1"), _T("Priority Channels"), "(Custom)");

	dlg.m_bShowTransferInstructions = m_bShowTransferInstructions;

	if (dlg.DoModal () == IDCANCEL) return S_OK;

	CString strModel = dlg.m_strModel;
	m_bShowTransferInstructions = dlg.m_bShowTransferInstructions?true:false;
	BOOL bCarNumbers = dlg.m_bCarNumbers;
	CString strPort = dlg.m_strPort;
	DWORD dwSpeed = strtoul (dlg.m_strSpeed, NULL, 10);
	BYTE cStopBits = (unsigned char) atoi (dlg.m_strStopBits);
	CString nPriorityChannels = dlg.m_nPriorityChannels;

	AfxGetApp ()->WriteProfileString (_T("RadioLink\\Gre1"), _T("Scanner Model"), strModel);
	AfxGetApp ()->WriteProfileInt (_T("RadioLink\\Gre1"), _T("Show Transfer Instructions"), dlg.m_bShowTransferInstructions);
	AfxGetApp ()->WriteProfileInt (_T("RadioLink\\Gre1"), _T("Car Numbers"), bCarNumbers);
	AfxGetApp ()->WriteProfileString (_T("RadioLink\\Gre1"), _T("Communications Port"), strPort);
	AfxGetApp ()->WriteProfileInt (_T("RadioLink\\Gre1"), _T("Baud"), dwSpeed);
	AfxGetApp ()->WriteProfileInt (_T("RadioLink\\Gre1"), _T("Stop Bits"), cStopBits);
	AfxGetApp ()->WriteProfileString (_T("RadioLink\\Gre1"), _T("Priority Channels"), nPriorityChannels);

	m_pGre1Link->SetComParameters (strPort, dwSpeed, cStopBits);

	return S_OK;
}

HRESULT rlGre1Module::GetLink (rlGre1Link **ppGre1Link)
{
	*ppGre1Link = m_pGre1Link;

	return S_OK;
}

HRESULT rlGre1Module::GetMemory (rlMemory **ppMemory)
{
	*ppMemory = m_pMemory;

	return S_OK;
}

bool rlGre1Module::ShowTransferInstructionsDlg (void)
{
	if (m_bShowTransferInstructions)
	{
		rlGre1TransferInstructionsDlg dlgTransferInstructions;
		if (dlgTransferInstructions.DoModal () == IDCANCEL)
		{
			return false; // transfer was cancelled
		}

		BOOL bShowTransferInstructions = dlgTransferInstructions.m_bDontShowAgain?FALSE:TRUE;
		m_bShowTransferInstructions = bShowTransferInstructions?true:false;

		AfxGetApp ()->WriteProfileInt (_T("RadioLink\\Gre1"), _T("Show Transfer Instructions"), bShowTransferInstructions);
	}

	return true;
}

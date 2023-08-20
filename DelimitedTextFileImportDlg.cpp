// DelimitedTextFileImportDlg.cpp : implementation file
//

#include "stdafx.h"
#include "DelimitedTextFileImportDlg.h"


// CDelimitedTextFileImportDlg dialog

IMPLEMENT_DYNAMIC(CDelimitedTextFileImportDlg, CDialog)
CDelimitedTextFileImportDlg::CDelimitedTextFileImportDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CDelimitedTextFileImportDlg::IDD, pParent)
{
	m_pDataTable = NULL;
}

CDelimitedTextFileImportDlg::~CDelimitedTextFileImportDlg()
{
}

void CDelimitedTextFileImportDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COLUMNHEADERS, m_chkColumnHeaders);
}


void CDelimitedTextFileImportDlg::SetDataTable (CTable *pDataTable)
{
	m_pDataTable = pDataTable;
}

BEGIN_MESSAGE_MAP(CDelimitedTextFileImportDlg, CDialog)
END_MESSAGE_MAP()


// CDelimitedTextFileImportDlg message handlers

BOOL CDelimitedTextFileImportDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_chkColumnHeaders.SetCheck (1);

	/*
	m_cmbColumnChannel.AddString (_T("(None)"));
	m_cmbColumnFrequency.AddString (_T("(None)"));
	m_cmbColumnDescription.AddString (_T("(None)"));
	m_cmbColumnCarNumber.AddString (_T("(None)"));
	m_cmbColumnDelay.AddString (_T("(None)"));
	m_cmbColumnLockout.AddString (_T("(None)"));
	m_cmbColumnPriority.AddString (_T("(None)"));

	m_cmbColumnChannel.AddString (_T("(Auto Number)"));

	if (m_pDataTable != NULL)
	{
		int nColumnCount = m_pDataTable->GetColumnCount ();

		for (int nColumn = 0; nColumn < nColumnCount; nColumn++)
		{
			m_cmbColumnChannel.AddString (m_pDataTable->GetCell (0, nColumn)->GetDataString ());
			m_cmbColumnFrequency.AddString (m_pDataTable->GetCell (0, nColumn)->GetDataString ());
			m_cmbColumnDescription.AddString (m_pDataTable->GetCell (0, nColumn)->GetDataString ());
			m_cmbColumnCarNumber.AddString (m_pDataTable->GetCell (0, nColumn)->GetDataString ());
			m_cmbColumnDelay.AddString (m_pDataTable->GetCell (0, nColumn)->GetDataString ());
			m_cmbColumnLockout.AddString (m_pDataTable->GetCell (0, nColumn)->GetDataString ());
			m_cmbColumnPriority.AddString (m_pDataTable->GetCell (0, nColumn)->GetDataString ());
		}
	}

	int nFoundChannelIndex = m_cmbColumnChannel.FindString (0, _T("ID"));
	int nFoundFrequencyIndex = m_cmbColumnFrequency.FindString (0, _T("Frequency"));
	int nFoundDescriptionIndex = m_cmbColumnDescription.FindString (0, _T("Description"));
	int nFoundCarNumberIndex = m_cmbColumnCarNumber.FindString (0, _T("Car Number"));
	int nFoundDelayIndex = m_cmbColumnDelay.FindString (0, _T("Delay"));
	int nFoundLockoutIndex = m_cmbColumnLockout.FindString (0, _T("Lockout"));
	int nFoundPriorityIndex = m_cmbColumnPriority.FindString (0, _T("Priority"));
	
	if (nFoundChannelIndex == -1) nFoundChannelIndex = 1;
	if (nFoundFrequencyIndex == -1) nFoundFrequencyIndex = 0;
	if (nFoundDescriptionIndex == -1) nFoundDescriptionIndex = 0;
	if (nFoundCarNumberIndex == -1) nFoundCarNumberIndex = 0;
	if (nFoundDelayIndex == -1) nFoundDelayIndex = 0;
	if (nFoundLockoutIndex == -1) nFoundLockoutIndex = 0;
	if (nFoundPriorityIndex == -1) nFoundPriorityIndex = 0;

	m_cmbColumnChannel.SetCurSel (nFoundChannelIndex);
	m_cmbColumnFrequency.SetCurSel (nFoundFrequencyIndex);
	m_cmbColumnDescription.SetCurSel (nFoundDescriptionIndex);
	m_cmbColumnCarNumber.SetCurSel (nFoundCarNumberIndex);
	m_cmbColumnDelay.SetCurSel (nFoundDelayIndex);
	m_cmbColumnLockout.SetCurSel (nFoundLockoutIndex);
	m_cmbColumnPriority.SetCurSel (nFoundPriorityIndex);
	*/

	return TRUE;
}

// rlGre2PropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProLink.h"
#include "rlGre2PropertiesDlg.h"


// rlGre2PropertiesDlg dialog

IMPLEMENT_DYNAMIC(rlGre2PropertiesDlg, CDialog)
rlGre2PropertiesDlg::rlGre2PropertiesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(rlGre2PropertiesDlg::IDD, pParent)
	, m_strPort(_T(""))
{
}

rlGre2PropertiesDlg::~rlGre2PropertiesDlg()
{
}

void rlGre2PropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PORT, m_cmbPort);
	DDX_CBString(pDX, IDC_PORT, m_strPort);
}


BEGIN_MESSAGE_MAP(rlGre2PropertiesDlg, CDialog)
END_MESSAGE_MAP()


// rlGre2PropertiesDlg message handlers

BOOL rlGre2PropertiesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cmbPort.AddString ("COM1");
	m_cmbPort.AddString ("COM2");
	m_cmbPort.AddString ("COM3");
	m_cmbPort.AddString ("COM4");
	m_cmbPort.AddString ("COM5");
	m_cmbPort.AddString ("COM6");
	m_cmbPort.AddString ("COM7");
	m_cmbPort.AddString ("COM8");
	m_cmbPort.AddString ("COM9");

	m_cmbPort.SetCurSel (m_cmbPort.FindString (-1, m_strPort));

	return TRUE;
}


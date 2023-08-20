// ModulesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProLink.h"
#include "rlManagerModulesDlg.h"


// CModulesDlg dialog

IMPLEMENT_DYNAMIC(rlManagerModulesDlg, CDialog)
rlManagerModulesDlg::rlManagerModulesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(rlManagerModulesDlg::IDD, pParent)
{
	m_pManager = DEBUG_NEW rlManager;
}

rlManagerModulesDlg::~rlManagerModulesDlg()
{
	delete m_pManager;
}

void rlManagerModulesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MODULESLIST, m_lstModules);
	DDX_Control(pDX, IDC_DESCRIPTION, m_txtDescription);
}


BEGIN_MESSAGE_MAP(rlManagerModulesDlg, CDialog)
//	ON_WM_CREATE()
ON_BN_CLICKED(IDC_PROPERTIES, OnBnClickedProperties)
ON_LBN_SELCHANGE(IDC_MODULESLIST, OnSelChangeModulesList)
ON_BN_CLICKED(IDC_SETASDEFAULT, OnBnClickedSetAsDefault)
ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CModulesDlg message handlers

BOOL rlManagerModulesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	int nModuleCount;
	m_pManager->GetModuleCount (&nModuleCount);

	m_pManager->GetDefaultModuleIndex (&m_nDefaultModuleIndex);

	rlModule *pModule;

	for (int x = 0; x < nModuleCount; x++)
	{
		m_pManager->GetModule (x, &pModule);

		LPTSTR lpName;
		pModule->GetName (&lpName);
		m_lstModules.AddString (lpName);

		if (m_nDefaultModuleIndex == x) m_lstModules.SetItemStyle (x, GD_LISTBOXEX_ITEMSTYLE_BOLD);

		m_pManager->ReleaseModule (pModule);
	}

	m_lstModules.SetCurSel (m_nDefaultModuleIndex);
	OnSelChangeModulesList ();

	return TRUE;
}

void rlManagerModulesDlg::OnBnClickedProperties ()
{
	int nSel = m_lstModules.GetCurSel ();

	rlModule *pModule;
	m_pManager->GetModule (nSel, &pModule);

	if (FAILED (pModule->ShowPropertiesDlg ()))
	{
		AfxMessageBox (_T("This module has no options that you can set."));
	}

	m_pManager->ReleaseModule (pModule);
}

void rlManagerModulesDlg::OnSelChangeModulesList ()
{
	int nSel = m_lstModules.GetCurSel ();

	rlModule *pModule;
	m_pManager->GetModule (nSel, &pModule);

	LPTSTR lpDescription;
	pModule->GetDescription (&lpDescription);
	m_txtDescription.SetWindowText (lpDescription);

	m_pManager->ReleaseModule (pModule);
}

void rlManagerModulesDlg::OnBnClickedSetAsDefault()
{
	int nSel = m_lstModules.GetCurSel ();

	m_nDefaultModuleIndex = nSel;

	m_lstModules.SetRedraw (FALSE);

	for (int x = 0; x < m_lstModules.GetCount (); x++)
	{
		if (x == nSel)
		{
			m_lstModules.SetItemStyle (x, GD_LISTBOXEX_ITEMSTYLE_BOLD);
		}
		else
		{
			m_lstModules.SetItemStyle (x, GD_LISTBOXEX_ITEMSTYLE_NORMAL);
		}
	}

	m_lstModules.SetRedraw (TRUE);
	m_lstModules.Invalidate ();
}

void rlManagerModulesDlg::OnBnClickedOk()
{
	m_pManager->SetDefaultModule (m_nDefaultModuleIndex);

	OnOK();
}

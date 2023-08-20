// SettingsDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ProLink.h"
#include "SettingsDialog.h"
#include "ColorButton.h"
#include ".\settingsdialog.h"

// CSettingsDialog dialog

IMPLEMENT_DYNAMIC(CSettingsDialog, CPropertyPage)
CSettingsDialog::CSettingsDialog(CWnd* pParent /*=NULL*/)
	: CPropertyPage(CSettingsDialog::IDD)
{	
}

CSettingsDialog::~CSettingsDialog()
{
}

void CSettingsDialog::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CSettingsDialog)
	DDX_Control(pDX, IDC_BANK_COLOR_1, m_btColor1);
	DDX_Control(pDX, IDC_BANK_COLOR_2, m_btColor2);
	DDX_Control(pDX, IDC_BANK_COLOR_3, m_btColor3);
	DDX_Control(pDX, IDC_TEXT_COLOR, m_btTxtColor);
	//}}AFX_DATA_MAP
	COLORREF ThrowAwayColor;	
	DDX_ColorButtonX(pDX, IDC_BANK_COLOR_1, ThrowAwayColor);
	DDX_ColorButtonX(pDX, IDC_BANK_COLOR_2, ThrowAwayColor);
	DDX_ColorButtonX(pDX, IDC_BANK_COLOR_3, ThrowAwayColor);
	DDX_ColorButtonX(pDX, IDC_TEXT_COLOR, ThrowAwayColor);
}


BEGIN_MESSAGE_MAP(CSettingsDialog, CPropertyPage)
	ON_MESSAGE(CPN_SELENDOK,     OnSelEndOK)
	ON_MESSAGE(CPN_SELENDCANCEL, OnSelEndCancel)
	ON_MESSAGE(CPN_SELCHANGE,    OnSelChange)
	ON_MESSAGE(CPN_CLOSEUP,      OnCloseUp)
	ON_MESSAGE(CPN_DROPDOWN,     OnDropDown)
	ON_BN_CLICKED(IDC_COLOR_RESET, OnBnClickedColorReset)
END_MESSAGE_MAP()


// CSettingsDialog message handlers

BOOL CSettingsDialog::OnInitDialog()
{	
	CPropertyPage::OnInitDialog();

	COLORREF *clr;
	unsigned int sz = sizeof(COLORREF);
	
	AfxGetApp()->GetProfileBinary(_T(""), _T("TextColor"), (LPBYTE*)&clr,&sz);
	m_btTxtColor.Color = *clr;
	delete clr;

	AfxGetApp()->GetProfileBinary(_T(""), _T("BankColor1"), (LPBYTE*)&clr,&sz);
	m_btColor1.Color = *clr;
	delete clr;

	AfxGetApp()->GetProfileBinary(_T(""), _T("BankColor2"), (LPBYTE*)&clr,&sz);
	m_btColor2.Color = *clr;
	delete clr;

	AfxGetApp()->GetProfileBinary(_T(""), _T("BankColor3"), (LPBYTE*)&clr,&sz);
	m_btColor3.Color = *clr;
	delete clr;

	return TRUE;
}

LONG CSettingsDialog::OnSelEndOK(UINT /*lParam*/, LONG /*wParam*/)
{	
	COLORREF clr;
	clr = m_btTxtColor.Color;
	AfxGetApp()->WriteProfileBinary(_T(""), _T("TextColor"), (LPBYTE)&clr, sizeof(COLORREF));

	clr = m_btColor1.Color;
	AfxGetApp()->WriteProfileBinary(_T(""), _T("BankColor1"), (LPBYTE)&clr, sizeof(COLORREF));	

	clr = m_btColor2.Color;
	AfxGetApp()->WriteProfileBinary(_T(""), _T("BankColor2"), (LPBYTE)&clr, sizeof(COLORREF));

	clr = m_btColor3.Color;
	AfxGetApp()->WriteProfileBinary(_T(""), _T("BankColor3"), (LPBYTE)&clr, sizeof(COLORREF));

	TRACE0("Selection ended OK\n");
	
    return TRUE;
}

LONG CSettingsDialog::OnSelEndCancel(UINT /*lParam*/, LONG /*wParam*/)
{
    TRACE0("Selection cancelled\n");
    return TRUE;
}

LONG CSettingsDialog::OnSelChange(UINT /*lParam*/, LONG /*wParam*/)
{
    TRACE0("Selection changed\n");
    return TRUE;
}

LONG CSettingsDialog::OnCloseUp(UINT /*lParam*/, LONG /*wParam*/)
{
    TRACE0("Colour picker close up\n");
    return TRUE;
}

LONG CSettingsDialog::OnDropDown(UINT /*lParam*/, LONG /*wParam*/)
{
    TRACE0("Colour picker drop down\n");
    return TRUE;
}

void CSettingsDialog::OnBnClickedColorReset()
{
	m_btColor1.Color = RGB(236,249,253);
	m_btColor2.Color = RGB(253,253,240);
	m_btColor3.Color = RGB(254,248,254);
	m_btTxtColor.Color = RGB(0,0,0);
	OnSelEndOK(0,0); // TODO: fix this. is there a better way?
}

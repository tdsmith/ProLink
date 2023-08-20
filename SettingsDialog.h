#pragma once

#include "ColorButton.h"
#include "ProLinkView.h"

// CSettingsDialog dialog

class CSettingsDialog : public CPropertyPage
{
	DECLARE_DYNAMIC(CSettingsDialog)

public:
	CSettingsDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CSettingsDialog();

// Dialog Data
	enum { IDD = IDD_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	CColorButtonX m_btColor1, m_btColor2, m_btColor3, m_btTxtColor;
	virtual BOOL OnInitDialog();
	afx_msg LONG OnSelEndOK(UINT /*lParam*/, LONG /*wParam*/);
	afx_msg LONG OnSelEndCancel(UINT /*lParam*/, LONG /*wParam*/);
	afx_msg LONG OnSelChange(UINT /*lParam*/, LONG /*wParam*/);
	afx_msg LONG OnCloseUp(UINT /*lParam*/, LONG /*wParam*/);
	afx_msg LONG OnDropDown(UINT /*lParam*/, LONG /*wParam*/);
    	DECLARE_MESSAGE_MAP()
public:


	afx_msg void OnBnClickedColorReset();
};

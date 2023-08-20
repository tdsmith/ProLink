#pragma once

#include "resource.h"
#include "afxwin.h"

// rlGre2PropertiesDlg dialog

class rlGre2PropertiesDlg : public CDialog
{
	DECLARE_DYNAMIC(rlGre2PropertiesDlg)

public:
	rlGre2PropertiesDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~rlGre2PropertiesDlg();

// Dialog Data
	enum { IDD = IDD_GRE2_PROPERTIES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CComboBox m_cmbPort;
	virtual BOOL OnInitDialog();
	CString m_strPort;
};

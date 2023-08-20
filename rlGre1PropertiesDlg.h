#pragma once

#include "resource.h"
#include "afxwin.h"

// rlGre1PropertiesDlg dialog

class rlGre1PropertiesDlg : public CDialog
{
	DECLARE_DYNAMIC(rlGre1PropertiesDlg)

public:
	rlGre1PropertiesDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~rlGre1PropertiesDlg();

// Dialog Data
	enum { IDD = IDD_GRE1_PROPERTIES };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CComboBox m_cmbModel;
	afx_msg void OnCbnSelChangeModel ();
	CComboBox m_cmbPort;
	CComboBox m_cmbSpeed;
	CComboBox m_cmbStopBits;
	CComboBox m_cmbPriChans;
	CButton m_chkCarNumbers;
	CString m_strModel;
	CString m_strPort;
	CString m_strSpeed;
	CString m_strStopBits;
	BOOL m_bCarNumbers;
	BOOL m_bShowTransferInstructions;
	CString m_nPriorityChannels;
};

#pragma once
#include "afxwin.h"

#include "gdListBoxEx.h"
#include "rlManager.h"

// CModulesDlg dialog

class rlManagerModulesDlg : public CDialog
{
	DECLARE_DYNAMIC(rlManagerModulesDlg)

	public:
		rlManagerModulesDlg(CWnd* pParent = NULL);   // standard constructor
		virtual ~rlManagerModulesDlg();

		// Dialog Data
		enum { IDD = IDD_MODULES };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		gdListBoxEx m_lstModules;
		rlManager *m_pManager;

		int m_nDefaultModuleIndex;

	public:
		virtual BOOL OnInitDialog();
		CStatic m_txtDescription;
		afx_msg void OnBnClickedProperties();
		afx_msg void OnSelChangeModulesList();

	DECLARE_MESSAGE_MAP()
	afx_msg void OnBnClickedSetAsDefault();
	afx_msg void OnBnClickedOk();
};

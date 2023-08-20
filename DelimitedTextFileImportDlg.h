#pragma once

#include "Table.h"
#include "afxwin.h"
#include "Resource.h"

// CDelimitedTextFileImportDlg dialog

class CDelimitedTextFileImportDlg : public CDialog
{
	DECLARE_DYNAMIC(CDelimitedTextFileImportDlg)

	public:
		CDelimitedTextFileImportDlg(CWnd* pParent = NULL);   // standard constructor
		virtual ~CDelimitedTextFileImportDlg();

		// Dialog Data
		enum { IDD = IDD_IMPORT_DELIMITED };

		void SetDataTable (CTable *);

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

		CTable *m_pDataTable;

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CButton m_chkColumnHeaders;
};

#pragma once
#include "afxwin.h"

#include "Resource.h"

class gdDupeMessagesDialog : public CDialog
{
	DECLARE_DYNAMIC(gdDupeMessagesDialog)

	public:
		gdDupeMessagesDialog(CWnd* pParent = NULL);   // standard constructor
		virtual ~gdDupeMessagesDialog();

	// Dialog Data
		enum { IDD = IDD_DUPE_MESSAGES };

	protected:
		virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

	public:
		afx_msg void OnSize(UINT nType, int cx, int cy);
		CEdit m_lstDupeMessages;
		virtual BOOL OnInitDialog();

		void AddMessage (const CString);
		void Clear ();

protected:
		virtual void OnCancel();
};

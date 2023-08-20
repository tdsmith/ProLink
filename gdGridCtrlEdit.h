#include "ProLinkView.h"

#pragma once


class gdGridCtrl;

// gdGridCtrlEdit

class gdGridCtrlEdit : public CEdit
{
	DECLARE_DYNAMIC (gdGridCtrlEdit)

	public:
		gdGridCtrlEdit (CProLinkView *, const int, const int, const CString);
		virtual ~gdGridCtrlEdit ();

	protected:
		CProLinkView *m_pGridCtrl;
		int m_nItem;
		int m_nSubItem;
		CString m_strInitialText;
		bool m_bChanged;

	public:
		virtual BOOL Create(DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID);
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		afx_msg void OnKillFocus(CWnd* pNewWnd);
		HRESULT SetGridCtrlText(void);
		afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
		afx_msg void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

	protected:
		virtual void PostNcDestroy();

	DECLARE_MESSAGE_MAP ()
};



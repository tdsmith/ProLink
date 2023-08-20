// gdGridCtrlEdit.cpp : implementation file
//

#include "stdafx.h"
#include "gdGridCtrlEdit.h"


// gdGridCtrlEdit

IMPLEMENT_DYNAMIC (gdGridCtrlEdit, CEdit)

gdGridCtrlEdit::gdGridCtrlEdit (CProLinkView *pGridCtrl, const int nItem, const int nSubItem, const CString strInitialText)
	: m_strInitialText (strInitialText)
{
	m_pGridCtrl = pGridCtrl;
	m_nItem = nItem;
	m_nSubItem = nSubItem;
	m_bChanged = false;
}

gdGridCtrlEdit::~gdGridCtrlEdit ()
{
}


BEGIN_MESSAGE_MAP (gdGridCtrlEdit, CEdit)
	ON_WM_KILLFOCUS()
	ON_WM_CHAR()
	ON_WM_KEYDOWN()
END_MESSAGE_MAP ()



// gdGridCtrlEdit message handlers


BOOL gdGridCtrlEdit::Create (DWORD dwStyle, const RECT& rect, CWnd* pParentWnd, UINT nID)
{
	if (!CEdit::Create(dwStyle, rect, pParentWnd, nID)) return FALSE;

	CFont *pFont = GetParent ()->GetFont ();
	SetFont (pFont);

	SetWindowText (m_strInitialText);
	SetFocus ();
	SetSel (0, -1);

	return TRUE;
}

BOOL gdGridCtrlEdit::PreTranslateMessage (MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN)
	{
		if (pMsg->wParam == VK_RETURN
				|| pMsg->wParam == VK_DELETE
				|| pMsg->wParam == VK_ESCAPE
				|| GetKeyState (VK_CONTROL)
			)
		{
			::TranslateMessage (pMsg);
			::DispatchMessage (pMsg);
			return TRUE;	// stop further processing
		}
	}

	return CEdit::PreTranslateMessage (pMsg);
}

void gdGridCtrlEdit::PostNcDestroy()
{
	CEdit::PostNcDestroy();

	delete this;
}

void gdGridCtrlEdit::OnKillFocus (CWnd* pNewWnd)
{
	CEdit::OnKillFocus(pNewWnd);

	SetGridCtrlText ();
	DestroyWindow ();
}

HRESULT gdGridCtrlEdit::SetGridCtrlText(void)
{
	if (m_bChanged)
	{
		CString strText;
		GetWindowText (strText);

		LV_DISPINFO DisplayInfo;
		DisplayInfo.hdr.hwndFrom = GetParent ()->m_hWnd;
		DisplayInfo.hdr.idFrom = GetDlgCtrlID ();
		DisplayInfo.hdr.code = LVN_ENDLABELEDIT;

		DisplayInfo.item.mask = LVIF_TEXT;
		DisplayInfo.item.iItem = m_nItem;
		DisplayInfo.item.iSubItem = m_nSubItem;
		DisplayInfo.item.pszText = LPTSTR ((LPCTSTR) strText);
		DisplayInfo.item.cchTextMax = strText.GetLength ();

		GetParent ()->SendMessage (WM_NOTIFY, GetParent ()->GetDlgCtrlID (), (LPARAM) &DisplayInfo);
	}

	return S_OK;
}

void gdGridCtrlEdit::OnChar(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	CListCtrl& listCtrl = m_pGridCtrl->GetListCtrl();

	bool bShift = ::GetKeyState (VK_SHIFT) < 0;

	switch (nChar)
	{
		case VK_ESCAPE:
			m_bChanged = false;
			m_pGridCtrl->SetFocus ();
			return;

		case VK_RETURN:
			SetGridCtrlText ();
			if (bShift)
			{
				if (m_nSubItem > 0) m_pGridCtrl->EditItem (m_nItem, m_pGridCtrl->GetNextSubItemLeft (m_nSubItem), NULL);
			}
			else
			{
				if (m_nSubItem < 3)
					m_pGridCtrl->EditItem (m_nItem, m_pGridCtrl->GetNextSubItemRight (m_nSubItem), NULL);
				else
					m_pGridCtrl->SetFocus ();
			}
			return;
		case VK_TAB:
			if (bShift)
			{
				if (m_nSubItem > 0) m_pGridCtrl->EditItem (m_nItem, m_pGridCtrl->GetNextSubItemLeft (m_nSubItem), NULL);
			}
			else
			{
				if (m_nSubItem < 3)
					m_pGridCtrl->EditItem (m_nItem, m_pGridCtrl->GetNextSubItemRight (m_nSubItem), NULL);
				else
					m_pGridCtrl->SetFocus ();
			}
			return;

		default:
			m_bChanged = true;

	}
	
	CEdit::OnChar (nChar, nRepCnt, nFlags);

	CString strText;
	GetWindowText (strText);

	CWindowDC dc (this);

	CFont *pFont = GetParent ()->GetFont ();
	CFont *pFontDC = dc.SelectObject (pFont);
	CSize TextSize = dc.GetTextExtent (strText);
	dc.SelectObject (pFontDC);
	TextSize.cx += 5;

	CRect Rectangle, ParentRectangle;

	GetClientRect (&Rectangle);
	GetParent()->GetClientRect (&ParentRectangle);

	ClientToScreen (&Rectangle);
	GetParent ()->ScreenToClient (&Rectangle);

	if (TextSize.cx > Rectangle.Width())
	{
		if (TextSize.cx + Rectangle.left < ParentRectangle.right)
		{
			Rectangle.right = Rectangle.left + TextSize.cx;
		}
		else
		{
			Rectangle.right = ParentRectangle.right;
		}

		MoveWindow (&Rectangle);
	}
}

void gdGridCtrlEdit::OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags)
{
	//bool bControl = ::GetKeyState (VK_CONTROL) < 0;
	int nSelStart, nSelEnd;
	GetSel (nSelStart, nSelEnd);

	switch (nChar)
	{
		case VK_UP:
			if (m_nItem > 0)
			{
				SetGridCtrlText ();
				m_pGridCtrl->EditItem (m_pGridCtrl->GetNextItemUp (m_nItem), m_nSubItem, NULL);
				return;
			}
			break;

		case VK_DOWN:
			SetGridCtrlText ();
			m_pGridCtrl->EditItem (m_pGridCtrl->GetNextItemDown (m_nItem), m_nSubItem, NULL);
			return;

		case VK_LEFT:
			if (nSelStart == 0 && (nSelStart == nSelEnd || nSelEnd != LineLength ()))
			{
				SetGridCtrlText ();
				m_pGridCtrl->EditItem (m_nItem, m_pGridCtrl->GetNextSubItemLeft (m_nSubItem), NULL);
				return;
			}
			break;

		case VK_RIGHT:
			if (nSelEnd == LineLength () && (nSelStart == nSelEnd || nSelStart != 0))
			{
				SetGridCtrlText ();
				m_pGridCtrl->EditItem (m_nItem, m_pGridCtrl->GetNextSubItemRight (m_nSubItem), NULL);
				return;
			}
			break;

		case VK_DELETE:
			m_bChanged = true;
			break;
	}

	CEdit::OnKeyDown(nChar, nRepCnt, nFlags);
}

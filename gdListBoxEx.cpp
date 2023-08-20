// gdListBoxEx.cpp : implementation file
//

#include "stdafx.h"
#include "ProLink.h"
#include "gdListBoxEx.h"


// gdListBoxEx

IMPLEMENT_DYNAMIC(gdListBoxEx, CListBox)
gdListBoxEx::gdListBoxEx()
{
}

gdListBoxEx::~gdListBoxEx()
{
}

const GD_LISTBOXEX_ITEMSTYLE gdListBoxEx::GetItemStyle (const int nItem)
{
	return (GD_LISTBOXEX_ITEMSTYLE) GetItemData (nItem);
}

void gdListBoxEx::SetItemStyle (const int nItem, const GD_LISTBOXEX_ITEMSTYLE ItemStyle)
{
	SetItemData (nItem, (GD_LISTBOXEX_ITEMSTYLE) ItemStyle);
}

BEGIN_MESSAGE_MAP(gdListBoxEx, CListBox)
END_MESSAGE_MAP()

// gdListBoxEx message handlers

void gdListBoxEx::DrawItem (LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	CDC* pDC = CDC::FromHandle (lpDrawItemStruct->hDC);
	CRect rect;

	// Draw the colored rectangle portion
	rect.CopyRect (&lpDrawItemStruct->rcItem);

	pDC->SetBkMode (TRANSPARENT);


	if (lpDrawItemStruct->itemState & ODS_SELECTED)
	{
		pDC->FillSolidRect (rect, GetSysColor (COLOR_HIGHLIGHT));
		pDC->SetTextColor (GetSysColor (COLOR_HIGHLIGHTTEXT));
	}
	else
	{
		pDC->FillSolidRect (rect, GetSysColor (COLOR_WINDOW));
		pDC->SetTextColor (GetSysColor (COLOR_WINDOWTEXT));
	}

	rect.left += 2;

	if ((int) (lpDrawItemStruct->itemID) >= 0) // Valid ID
	{
		CString sText;
		int nIndex;

		CFont newFont;
		CFont *pOldFont;

		nIndex = lpDrawItemStruct->itemID;
		GetText (nIndex, sText);

		GD_LISTBOXEX_ITEMSTYLE fontStyle = (GD_LISTBOXEX_ITEMSTYLE) GetItemData (nIndex);

		// To avoid unnecessary processing
		if (fontStyle == GD_LISTBOXEX_ITEMSTYLE_NORMAL)
		{
			pDC->DrawText (sText, rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
			return;
		}
		
		LOGFONT logFont;
		CFont *pFont = GetFont ();
		pFont->GetLogFont (&logFont);

		if (fontStyle & GD_LISTBOXEX_ITEMSTYLE_BOLD) logFont.lfWeight = FW_BOLD;
		if (fontStyle & GD_LISTBOXEX_ITEMSTYLE_ITALIC) logFont.lfItalic = TRUE;
		if (fontStyle & GD_LISTBOXEX_ITEMSTYLE_UNDERLINE) logFont.lfUnderline = TRUE;
		if (fontStyle & GD_LISTBOXEX_ITEMSTYLE_STRIKEOUT) logFont.lfStrikeOut = TRUE;

		newFont.CreateFontIndirect (&logFont);
		pOldFont = pDC->SelectObject (&newFont);
		pDC->DrawText (sText, rect, DT_LEFT | DT_VCENTER | DT_SINGLELINE);
		pDC->SelectObject (pOldFont);
		newFont.DeleteObject ();
	}	
}

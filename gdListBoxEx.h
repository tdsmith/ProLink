#pragma once

typedef DWORD GD_LISTBOXEX_ITEMSTYLE;

#define GD_LISTBOXEX_ITEMSTYLE_NORMAL		0x00000000
#define GD_LISTBOXEX_ITEMSTYLE_BOLD			0x00000001
#define GD_LISTBOXEX_ITEMSTYLE_ITALIC		0x00000010
#define GD_LISTBOXEX_ITEMSTYLE_UNDERLINE	0x00000100
#define GD_LISTBOXEX_ITEMSTYLE_STRIKEOUT	0x00001000

// gdListBoxEx

class gdListBoxEx : public CListBox
{
	DECLARE_DYNAMIC(gdListBoxEx)

	public:
		gdListBoxEx ();
		virtual ~gdListBoxEx ();

		const GD_LISTBOXEX_ITEMSTYLE GetItemStyle (const int);
		void SetItemStyle (const int, const GD_LISTBOXEX_ITEMSTYLE);

	protected:

	DECLARE_MESSAGE_MAP()

public:
	virtual void DrawItem (LPDRAWITEMSTRUCT /*lpDrawItemStruct*/);
};



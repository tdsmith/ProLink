// ProLinkView.cpp : implementation of the CProLinkView class
//

#include "stdafx.h"
#include "ProLink.h"
#include "rlModule.h"
#include "ProLinkDoc.h"
#include "ProLinkView.h"
#include "rlMemoryLayout.h"
#include "gdGridCtrlEdit.h"
#include "rlManagerModulesDlg.h"
#include "SettingsDialog.h"
#include "MainFrm.h"
#include "gdDupe.h"
#include "RadioShackDBF.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CProLinkView

const UINT m_FindDialogMessage = RegisterWindowMessage(FINDMSGSTRING);

IMPLEMENT_DYNCREATE(CProLinkView, CListView)

BEGIN_MESSAGE_MAP(CProLinkView, CListView)
	//{{AFX_MSG_MAP(CProLinkView)
	
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	ON_WM_LBUTTONDBLCLK ()
	ON_WM_CHAR ()
	ON_WM_CREATE ()
	ON_WM_SETFOCUS ()
	ON_WM_CONTEXTMENU()
	// Standard printing commands
	ON_NOTIFY (NM_CUSTOMDRAW, AFX_IDW_PANE_FIRST, OnCustomdrawMyList)
	ON_NOTIFY (LVN_ENDLABELEDIT, AFX_IDW_PANE_FIRST, OnEndLabelEdit)
	ON_COMMAND(ID_FILE_PRINT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CListView::OnFilePrintPreview)
	ON_COMMAND(ID_TRANSFER_UPLOADALL, OnTransferUploadAll)
	ON_COMMAND(ID_TRANSFER_UPLOADSELECTED, OnTransferUploadSelected)
	ON_COMMAND(ID_TRANSFER_MODULES, OnTransferModules)
	ON_COMMAND(ID_OPTIONS_SETTINGS, OnOptionsSettings)
	ON_COMMAND(ID_IMPORT_RADIOSHACK, OnImportRadioShack)
	ON_COMMAND(ID_EDIT_CUT, OnEditCut)
	ON_COMMAND(ID_EDIT_COPY, OnEditCopy)
	ON_COMMAND(ID_EDIT_PASTE, OnEditPaste)
	ON_COMMAND(ID_EDIT_SELECTALL, OnEditSelectAll)
	ON_COMMAND(ID_EDIT_DELETE, OnEditDelete)
	ON_COMMAND(ID_EDIT_FIND, OnEditFind)
	ON_COMMAND(ID_EDIT_FINDDUPLICATES, OnEditFindDuplicates)
	ON_COMMAND(ID_SETALL_DELAY, OnSetAllDelay)
	ON_COMMAND(ID_SETALL_LOCKOUT, OnSetAllLockout)
	ON_COMMAND(ID_CLEARALL_CARNO, OnClearAllCarNo)
	ON_COMMAND(ID_CLEARALL_DELAY, OnClearAllDelay)
	ON_COMMAND(ID_CLEARALL_LOCKOUT, OnClearAllLockout)
	ON_COMMAND(ID_CLEARALL_DESCRIPTION, OnClearAllDescription)
	ON_COMMAND(ID_BUTTON_ALL, OnButtonAll)
	ON_COMMAND(ID_BUTTON_1, OnButton1)
	ON_COMMAND(ID_BUTTON_2, OnButton2)
	ON_COMMAND(ID_BUTTON_3, OnButton3)
	ON_COMMAND(ID_BUTTON_4, OnButton4)
	ON_COMMAND(ID_BUTTON_5, OnButton5)
	ON_COMMAND(ID_BUTTON_6, OnButton6)
	ON_COMMAND(ID_BUTTON_7, OnButton7)
	ON_COMMAND(ID_BUTTON_8, OnButton8)
	ON_COMMAND(ID_BUTTON_9, OnButton9)
	ON_COMMAND(ID_BUTTON_0, OnButton0)
	ON_COMMAND(ID_BUTTON_D, OnButtonD)

	ON_REGISTERED_MESSAGE(m_FindDialogMessage, DoFind)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProLinkView construction/destruction

CProLinkView::CProLinkView() : m_cListCtrl( GetListCtrl() )
{		
	BOOL bFirstRun = AfxGetApp ()->GetProfileInt (_T(""), _T("First Run"), TRUE);

	if (bFirstRun)
	{
		// Set the transfer module
		OnTransferModules ();
		AfxGetApp ()->WriteProfileInt (_T(""), _T("First Run"), FALSE);
		// Set the background colors
		COLORREF clr;
		clr = RGB(236, 249, 253);
		AfxGetApp()->WriteProfileBinary(_T(""), _T("BankColor1"), (LPBYTE)&clr, sizeof(COLORREF));

		clr = RGB(253, 253, 240);
		AfxGetApp()->WriteProfileBinary(_T(""), _T("BankColor2"), (LPBYTE)&clr, sizeof(COLORREF));

		clr = RGB(254, 248, 254);
		AfxGetApp()->WriteProfileBinary(_T(""), _T("BankColor3"), (LPBYTE)&clr, sizeof(COLORREF));

		clr = RGB(0, 0, 0);
		AfxGetApp()->WriteProfileBinary(_T(""), _T("TextColor"), (LPBYTE)&clr, sizeof(COLORREF));
	}	
	unsigned int sz;
	sz = sizeof(COLORREF);

	AfxGetApp()->GetProfileBinary(_T(""), _T("BankColor1"), (LPBYTE*)&clr1,&sz);
	AfxGetApp()->GetProfileBinary(_T(""), _T("BankColor2"), (LPBYTE*)&clr2,&sz);
	AfxGetApp()->GetProfileBinary(_T(""), _T("BankColor3"), (LPBYTE*)&clr3,&sz);
	AfxGetApp()->GetProfileBinary(_T(""), _T("TextColor"), (LPBYTE*)&txtClr,&sz);
//		dlg.m_strModel = AfxGetApp ()->GetProfileString (_T("RadioLink\\Gre1"), _T("Scanner Model"), _T("(Custom)"));

}

CProLinkView::~CProLinkView()
{
	delete clr1;
	delete clr2;
	delete clr3;
	delete txtClr;
	//delete pMemoryLayout;
	//delete pModule;
}


void CProLinkView::OnCustomdrawMyList ( NMHDR* pNMHDR, LRESULT* pResult )
{ 
	
	COLORREF crText;	

	//AfxMessageBox("this is called a LOT");
	NMLVCUSTOMDRAW* pLVCD = reinterpret_cast<NMLVCUSTOMDRAW*>( pNMHDR );

    // Take the default processing unless we set this to something else below.
    *pResult = CDRF_DODEFAULT;

    // First thing - check the draw stage. If it's the control's prepaint
    // stage, then tell Windows we want messages for every item.

    if ( CDDS_PREPAINT == pLVCD->nmcd.dwDrawStage )
        {
        *pResult = CDRF_NOTIFYITEMDRAW;
        }
    else if ( CDDS_ITEMPREPAINT == pLVCD->nmcd.dwDrawStage )
        { 
        // This is the prepaint stage for an item. Here's where we set the
        // item's text color. Our return value will tell Windows to draw the
        // item itself, but it will use the new color we set here.
        // We'll cycle the colors through red, green, and light blue.			


		int bank = GetDocument()->pMemoryLayout->GetBankFromChannel(pLVCD->nmcd.dwItemSpec);
		if ((bank % 3) == 0)
            crText = *clr1;
		else if ((bank % 3) == 1)
			crText = *clr2;
		else if ((bank % 3) == 2)
			crText = *clr3;
		else
			crText = RGB(254,254,254); // WHITE for extra columns/etc

		// Store the color back in the NMLVCUSTOMDRAW struct.
        pLVCD->clrTextBk = crText;
		pLVCD->clrText = *txtClr;

		// Tell Windows to paint the control itself.       
		*pResult = CDRF_DODEFAULT;
		
        }
		
}

void CProLinkView::OnContextMenu(CWnd *pWnd, CPoint point)
{	
	// Load the desired menu
	CMenu mnuPopupSubmit;
	mnuPopupSubmit.LoadMenu(IDR_CONTEXT);

	// Get a pointer to the first item of the menu
	CMenu *mnuPopupMenu = mnuPopupSubmit.GetSubMenu(0);
	ASSERT(mnuPopupMenu);
	
	mnuPopupMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_RIGHTBUTTON, point.x, point.y, this);
}

CProLinkView * CProLinkView::GetView()
{
    CFrameWnd * pFrame = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);

    CView * pView = pFrame->GetActiveView();
    if ( !pView )
       return NULL;

    // Fail if view is of wrong kind
    // (this could occur with splitter windows, or additional
    // views on a single document
    if ( ! pView->IsKindOf( RUNTIME_CLASS(CProLinkView) ) )
       return NULL;

    return (CProLinkView *) pView;
}

BOOL CProLinkView::PreCreateWindow(CREATESTRUCT& cs)
{
   cs.style &= ~LVS_TYPEMASK;
   cs.style |= LVS_REPORT | LVS_SHOWSELALWAYS | LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT;

	return CListView::PreCreateWindow(cs);
	
}

void CProLinkView::OnImportRadioShack()
{
	CString importFile;
	string strDate;
	string loadFile;
	RadioShackDBF rsdbf;
	CString strTemp;;
	static char BASED_CODE szFilter[] = "RadioShack Scanner Loader Files (*.dbf)|*.dbf|";
	// set first param to TRUE to get "open read only"
	CFileDialog dlg(FALSE,NULL,NULL,NULL,szFilter);
	if (dlg.DoModal() == IDOK){	
		importFile = dlg.GetPathName();  
	}
	else return;

	loadFile = importFile;
	rsdbf.Load(loadFile);
	if (rsdbf.NumRecords() == 0)
	{
		AfxMessageBox("The database is empty.", MB_OK, MB_ICONEXCLAMATION);
		return;
	}
	for (int i = 0; i < rsdbf.NumRecords(); i++)
	{
		GetDocument()->SetItemString(rsdbf.GetRecord(i)._channel-1, 1, rsdbf.GetRecord(i)._frequency.data());
		GetDocument()->SetItemString(rsdbf.GetRecord(i)._channel-1, 2, rsdbf.GetRecord(i)._service.data());
		GetDocument()->SetItemString(rsdbf.GetRecord(i)._channel-1, 4, (rsdbf.GetRecord(i)._delay) ? "X" : " ");
		GetDocument()->SetItemString(rsdbf.GetRecord(i)._channel-1, 5, (rsdbf.GetRecord(i)._channelloc) ? "X" : " ");
		GetDocument()->SetItemString(rsdbf.GetRecord(i)._channel-1, 6, (rsdbf.GetRecord(i)._selectenab) ? "X" : " ");
	}
	GetDocument()->SetModifiedFlag(TRUE);
	GetListCtrl().SetRedraw(TRUE);
	GetListCtrl().Invalidate(FALSE);
	GetDocument()->UpdateAllViews(NULL);
}

/////////////////////////////////////////////////////////////////////////////
// CProLinkView drawing


void CProLinkView::OnInitialUpdate() {
	
	CListCtrl & clc = GetListCtrl();
	static BOOL bInitialized = FALSE;
	CListView::OnInitialUpdate();
	clc.SetView(AFX_WS_DEFAULT_VIEW | LVS_OWNERDATA);
	clc.SetExtendedStyle( GetListCtrl().GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_HEADERDRAGDROP);

	// TODO2006: there has to be a better way to "press" the all button
	// on a new or opened document
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	pMainFrm->ResetToolbar(ID_BUTTON_ALL);

	if (!bInitialized)
	{
		while (GetListCtrl().DeleteColumn(0));
		GetListCtrl().InsertColumn (CHANNEL_LIST_COLUMN_NUMBER, _T("#"), LVCFMT_CENTER, 30, CHANNEL_LIST_COLUMN_NUMBER);

		// for some reason, InsertColumn doesn't set the format on the first column, so we have to set it again ourselves
		LVCOLUMN ColumnInfo;
		ColumnInfo.mask = LVCF_FMT;
		ColumnInfo.fmt = LVCFMT_CENTER;
		GetListCtrl().SetColumn (CHANNEL_LIST_COLUMN_NUMBER, &ColumnInfo);
	
		GetListCtrl().InsertColumn (CHANNEL_LIST_COLUMN_FREQUENCY, _T("Frequency"), LVCFMT_CENTER, 100, CHANNEL_LIST_COLUMN_FREQUENCY);
		GetListCtrl().InsertColumn (CHANNEL_LIST_COLUMN_DESCRIPTION, _T("Description"), LVCFMT_LEFT, 350, CHANNEL_LIST_COLUMN_DESCRIPTION);
		GetListCtrl().InsertColumn (CHANNEL_LIST_COLUMN_CARNUMBER, _T("Car Number"), LVCFMT_CENTER, 75, CHANNEL_LIST_COLUMN_CARNUMBER);
		GetListCtrl().InsertColumn (CHANNEL_LIST_COLUMN_DELAY, _T("Delay"), LVCFMT_CENTER, 50, CHANNEL_LIST_COLUMN_DELAY);
		GetListCtrl().InsertColumn (CHANNEL_LIST_COLUMN_LOCKOUT, _T("Lockout"), LVCFMT_CENTER, 50, CHANNEL_LIST_COLUMN_LOCKOUT);
		GetListCtrl().InsertColumn (CHANNEL_LIST_COLUMN_PRIORITY, _T("Priority"), LVCFMT_CENTER, 50, CHANNEL_LIST_COLUMN_PRIORITY);
	}
	

	GetListCtrl().DeleteAllItems();

	// frequencies
	for (int i = GetDocument()->nFirstChannel-1; i < GetDocument()->nLastChannel; i++)
	{
		GetListCtrl().InsertItem(i, NULL);
	}

	BOOL buttonAll = FALSE;
	CProLinkDoc* pDoc = GetDocument();

	ShowAllData();

	m_Print.SetListCtrl(&m_cListCtrl);
	m_Print.SetListView(this);
	m_Print.SetAppName(AfxGetAppName());
	m_Print.SetDocTitle(GetDocument()->GetTitle());

}

void CProLinkView::ShowAllData()
{
	GetListCtrl().SetRedraw(FALSE);
	 //OnDraw(NULL);
	int x = 0;
	CProLinkDoc* pDoc = GetDocument();
	rlMemoryChannel* pChannel;
	CString tempStr;
		
//		tempStr.Format("%d", pDoc->m_MemoryChannelArray.GetCount());		
		for (int nRow = 0; nRow < pDoc->m_MemoryChannelArray.GetCount(); nRow++)		
		{
			
			pChannel = pDoc->m_MemoryChannelArray.GetAt(nRow);

				tempStr.Format("%d", pChannel->GetChannelNumber());				
				GetListCtrl().SetItemText(nRow, CHANNEL_LIST_COLUMN_NUMBER, tempStr);
				if (pChannel->GetFrequency().GetFrequencyMHz() != 0)
					tempStr.Format("%.4f", pChannel->GetFrequency().GetFrequencyMHz());
				else
					tempStr.Format("");
				GetListCtrl().SetItemText(nRow, CHANNEL_LIST_COLUMN_FREQUENCY, tempStr);
				tempStr.Format("%s", pChannel->GetDescription());
				GetListCtrl().SetItemText(nRow, CHANNEL_LIST_COLUMN_DESCRIPTION, tempStr);
				tempStr.Format("%s", pChannel->GetCarNumber());
				GetListCtrl().SetItemText(nRow, CHANNEL_LIST_COLUMN_CARNUMBER, tempStr);

				if (pChannel->GetDelay())
					tempStr.Format("X");
				else
					tempStr.Format(" ");
				GetListCtrl().SetItemText(nRow, CHANNEL_LIST_COLUMN_DELAY, tempStr);

				if (pChannel->GetLockout())
					tempStr.Format("X");
				else
					tempStr.Format(" ");
				GetListCtrl().SetItemText(nRow, CHANNEL_LIST_COLUMN_LOCKOUT, tempStr);

				if (pChannel->GetPriority())
					tempStr.Format("X");
				else
					tempStr.Format(" ");
				GetListCtrl().SetItemText(nRow, CHANNEL_LIST_COLUMN_PRIORITY, tempStr);


		}
	GetListCtrl().SetRedraw(TRUE);
	GetListCtrl().Invalidate(FALSE);

}

void CProLinkView::OnUpdate(CView* pSender, LPARAM lHint, CObject* pHint)
{
	int i = 0;
	rlMemoryChannel* pChannel;
	CString tempStr;

	tempStr.Format("%d", atoi(GetListCtrl().GetItemText(0, 0)));
	
		i = atoi(tempStr);
		if (i != 0) // TODO: someone explain why this is 0 on initialization?
			i--;
		for (int nRow = 0; nRow < GetListCtrl().GetItemCount(); nRow++)		
		{
				
				pChannel = GetDocument()->m_MemoryChannelArray.GetAt(i);

				tempStr.Format("%d", pChannel->GetChannelNumber());		
				GetListCtrl().SetItemText(nRow, CHANNEL_LIST_COLUMN_NUMBER, tempStr);
				if (pChannel->GetFrequency().GetFrequencyMHz() != 0)
					tempStr.Format("%.4f", pChannel->GetFrequency().GetFrequencyMHz());
				else
					tempStr.Format("");
				GetListCtrl().SetItemText(nRow, CHANNEL_LIST_COLUMN_FREQUENCY, tempStr);
				tempStr.Format("%s", pChannel->GetDescription());
				GetListCtrl().SetItemText(nRow, CHANNEL_LIST_COLUMN_DESCRIPTION, tempStr);
				tempStr.Format("%s", pChannel->GetCarNumber());
				GetListCtrl().SetItemText(nRow, CHANNEL_LIST_COLUMN_CARNUMBER, tempStr);

				if (pChannel->GetDelay())
					tempStr.Format("X");
				else
					tempStr.Format(" ");
				GetListCtrl().SetItemText(nRow, CHANNEL_LIST_COLUMN_DELAY, tempStr);

				if (pChannel->GetLockout())
					tempStr.Format("X");
				else
					tempStr.Format(" ");
				GetListCtrl().SetItemText(nRow, CHANNEL_LIST_COLUMN_LOCKOUT, tempStr);

				if (pChannel->GetPriority())
					tempStr.Format("X");
				else
					tempStr.Format(" ");
				GetListCtrl().SetItemText(nRow, CHANNEL_LIST_COLUMN_PRIORITY, tempStr);


			i++;				
		}
}

/////////////////////////////////////////////////////////////////////////////
// CProLinkView printing

BOOL CProLinkView::OnPreparePrinting(CPrintInfo* pInfo)
{
   m_Print.OnPreparePrinting(pInfo);
   return DoPreparePrinting(pInfo);
}

void CProLinkView::OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo)
{   
   m_Print.OnBeginPrinting(pDC, pInfo);
}

void CProLinkView::OnPrint(CDC* pDC, CPrintInfo* pInfo) 
{
   m_Print.OnPrint(pDC, pInfo);
}

void CProLinkView::OnEndPrinting(CDC* pDC, CPrintInfo* pInfo)
{
   m_Print.OnEndPrinting(pDC, pInfo);
}

/////////////////////////////////////////////////////////////////////////////
// CProLinkView diagnostics

#ifdef _DEBUG
void CProLinkView::AssertValid() const
{
	CListView::AssertValid();
}

void CProLinkView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CProLinkDoc* CProLinkView::GetDocument() // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CProLinkDoc)));
	return (CProLinkDoc*)m_pDocument;
}
#endif //_DEBUG

////////////////////////////////////////////////////////////////////////////
// CProLinkView message handlers

void CProLinkView::AutoSizeColumns()
{      
   CListCtrl& listCtrl = GetListCtrl();
   listCtrl.SetRedraw(false);

   CHeaderCtrl* pHeaderCtrl = listCtrl.GetHeaderCtrl();
   ASSERT(pHeaderCtrl != NULL);
   for (int i=0; i < pHeaderCtrl->GetItemCount(); i++)
      listCtrl.SetColumnWidth(i, LVSCW_AUTOSIZE_USEHEADER);

   listCtrl.SetRedraw(true);
}

void CProLinkView::AutoSizeColumn(int nCol)
{
   CListCtrl& listCtrl = GetListCtrl();
   listCtrl.SetRedraw(false);

   CHeaderCtrl* pHeaderCtrl = listCtrl.GetHeaderCtrl();
   ASSERT(pHeaderCtrl != NULL);
   ASSERT(nCol >= 0 && nCol < pHeaderCtrl->GetItemCount());
   if (nCol < 0 || nCol >= pHeaderCtrl->GetItemCount()) return;

   listCtrl.SetColumnWidth(nCol, LVSCW_AUTOSIZE_USEHEADER);
   listCtrl.SetRedraw(true);
}

void CProLinkView::OnLButtonDblClk(UINT nFlags, CPoint point)
{
	CListView::OnLButtonDblClk (nFlags, point);

	CListCtrl& listCtrl = GetListCtrl();

	LVHITTESTINFO HitTestInfo;
	HitTestInfo.pt = point;
	listCtrl.SubItemHitTest (&HitTestInfo);

	if ((HitTestInfo.flags && LVHT_ONITEM) != 0)
	{
		if ((listCtrl.GetItemState (HitTestInfo.iItem, LVIS_FOCUSED) & LVIS_FOCUSED) == LVIS_FOCUSED)
		{
			EditItem (HitTestInfo.iItem, HitTestInfo.iSubItem, NULL);
			GetDocument()->UpdateAllViews( NULL );
		}
	}
}

HRESULT CProLinkView::EditItem (const int nItem, const int nSubItem, CEdit **ppEditCtrl)
{	
	CListCtrl& listCtrl = GetListCtrl();
	SetFocus ();
	SelectItem (nItem, true);
	CString strTemp;
	int nPriorityChannels;

	// do not allow editing of channel number
	switch (nSubItem)
	{
		case 0: return NULL;	
		case 4:
		case 5:
			if (GetDocument()->GetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, nSubItem) == _T(" "))
			{
				GetDocument()->SetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, nSubItem, _T("X"));
			}
			else if (GetDocument()->GetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, nSubItem) == _T("X"))
			{
				GetDocument()->SetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, nSubItem, _T(" "));
			}
			// channels in the dummy bank do not affect the dirty bit
			if (atoi(GetListCtrl().GetItemText(nItem, 0)) <= GetDocument()->nLastChannel)
				GetDocument()->SetModifiedFlag(TRUE);
			return S_OK;
		case 6:
			strTemp = AfxGetApp ()->GetProfileString (_T("RadioLink\\Gre1"), _T("Priority Channels"), "(Custom)");
			if (strTemp == "(Custom)")
			{
				// if we have custom priority setting, let whatever happen happen
				if (GetDocument()->GetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, nSubItem) == _T(" "))
				{
					GetDocument()->SetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, nSubItem, _T("X"));
				}
				else if (GetDocument()->GetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, nSubItem) == _T("X"))
				{
					GetDocument()->SetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, nSubItem, _T(" "));
				}
			}
			else
			{
				// it has to be 1 or 10
				nPriorityChannels = atoi(strTemp);
				// if there is only 1 priority channel...
				if (nPriorityChannels == 1)
				{
					// and this one isnt it (its not set)
					if (GetDocument()->GetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, nSubItem) == _T(" "))
					{
						// clear all priorities
						OnClearAllPriority();
						// set this one
						GetDocument()->SetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, nSubItem, _T("X"));
					}
				}
				else if (nPriorityChannels == 10)
				{
					if (FindNumPriChans() < 10)
					{
						if (GetDocument()->GetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, nSubItem) == _T(" "))
						{
							GetDocument()->SetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, nSubItem, _T("X"));
						}
						else if (GetDocument()->GetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, nSubItem) == _T("X"))
						{
							GetDocument()->SetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, nSubItem, _T(" "));
						}
					}
					else
					{
						AfxMessageBox("You are already at the maximum number of priority channels.", MB_OK, MB_ICONEXCLAMATION);
					}
				}
				else 
				{
					// something weird is going on...
					AfxMessageBox("Error determining number of priority channels. Please check your settings.", MB_OK, MB_ICONERROR);
				}
			}
			if (atoi(GetListCtrl().GetItemText(nItem, 0)) <= GetDocument()->nLastChannel)
				GetDocument()->SetModifiedFlag(TRUE);
			return S_OK;
 	}


	if (!listCtrl.EnsureVisible (nItem, FALSE)) return NULL;

	CHeaderCtrl *pHeaderCtrl = (CHeaderCtrl *) GetDlgItem (0);
	int nColumnCount = pHeaderCtrl->GetItemCount ();

	if (nSubItem >= nColumnCount || listCtrl.GetColumnWidth (nSubItem) < 5) return NULL;

	CRect rcSubItem;
	listCtrl.GetSubItemRect (nItem, nSubItem, LVIR_BOUNDS, rcSubItem);

	CRect rcClient;
	GetClientRect (&rcClient);

	if (rcSubItem.left < rcClient.left || rcSubItem.right > rcClient.right)
	{
		CSize Size;
		if (rcSubItem.left < rcClient.left)
			Size.cx = rcSubItem.left - rcClient.left;
		else if (rcSubItem.right > rcClient.right)
			Size.cx = rcSubItem.right - rcClient.right;

		Size.cy = 0;

		listCtrl.Scroll (Size);

		listCtrl.GetSubItemRect (nItem, nSubItem, LVIR_BOUNDS, rcSubItem);
	}

	LV_COLUMN ColumnInfo;
	ColumnInfo.mask = LVCF_FMT;
	listCtrl.GetColumn (nSubItem, &ColumnInfo);

	int nColumnJustification = ColumnInfo.fmt & LVCFMT_JUSTIFYMASK;

	DWORD dwStyle;
	if (nColumnJustification == LVCFMT_LEFT)
	{
		dwStyle = ES_LEFT;
	}
	else if (nColumnJustification == LVCFMT_RIGHT)
	{
		dwStyle = ES_RIGHT;
	}
	else
	{
		dwStyle = ES_CENTER;
	}

	rcSubItem.top -= 3;
	if (rcSubItem.right > rcClient.right) rcSubItem.right = rcClient.right;

	dwStyle |= WS_BORDER | WS_CHILD | WS_VISIBLE | ES_AUTOHSCROLL;

	CEdit *pEditCtrl = new gdGridCtrlEdit (this, nItem, nSubItem, listCtrl.GetItemText (nItem, nSubItem));
	pEditCtrl->Create (dwStyle, rcSubItem, this, 0);

	if (ppEditCtrl != NULL) *ppEditCtrl = pEditCtrl;

	// delete gridctrledit??? maybe later?
	return S_OK;
}

void CProLinkView::SelectItem(int nItem, bool bDeselectOthers)
{
	CListCtrl& listCtrl = GetListCtrl();
	if (bDeselectOthers)
	{
		int nSelectedItem;
		POSITION pos = listCtrl.GetFirstSelectedItemPosition ();

		while (pos != NULL)
		{
			nSelectedItem = listCtrl.GetNextSelectedItem (pos);
			listCtrl.SetItemState (nSelectedItem, 0, LVIS_SELECTED);			
		}
	}

	listCtrl.SetItemState (nItem, LVIS_SELECTED | LVIS_FOCUSED, LVIS_SELECTED | LVIS_FOCUSED);
}

const int CProLinkView::GetNextItemUp (const int nItem)
{
	int nNextItem = nItem - 1;

	if (nNextItem < 0) nNextItem = 0;

	return nNextItem;
}

const int CProLinkView::GetNextItemDown (const int nItem, const bool /*bCreate*/)
{
	CListCtrl& listCtrl = GetListCtrl();
	int nNextItem = nItem + 1;

	if (nNextItem > listCtrl.GetItemCount ()) nNextItem = listCtrl.GetItemCount ();

	return nNextItem;
}

const int CProLinkView::GetNextSubItemLeft (const int nSubItem)
{
	CListCtrl& listCtrl = GetListCtrl();
	int nCount = listCtrl.GetHeaderCtrl ()->GetItemCount ();
	LPINT pnOrder = new int[nCount];
	listCtrl.GetColumnOrderArray (pnOrder, nCount);

	int nNextItem = 0;

	for (int x = 0; x < nCount; x++)
	{
		if (pnOrder [x] == nSubItem)
		{
			nNextItem = x - 1;
			if (nNextItem < 0) nNextItem = 0;
			nNextItem = pnOrder [nNextItem];
			break;
		}
	}

	delete pnOrder;

	return nNextItem;
}

const int CProLinkView::GetNextSubItemRight (const int nSubItem)
{
	CListCtrl& listCtrl = GetListCtrl();
	int nCount = listCtrl.GetHeaderCtrl ()->GetItemCount ();
	LPINT pnOrder = new int[nCount];
	listCtrl.GetColumnOrderArray (pnOrder, nCount);

	int nNextItem = 0;

	for (int x = 0; x < nCount; x++)
	{
		if (pnOrder [x] == nSubItem)
		{
			nNextItem = x + 1;
			if (nNextItem > nCount) nNextItem = nCount;
			nNextItem = pnOrder [nNextItem];
			break;
		}
	}

	delete pnOrder;

	return nNextItem;
}


void CProLinkView::OnChar (UINT nChar, UINT /*nRepCnt*/, UINT nFlags)
{
	CListCtrl& listCtrl = GetListCtrl();
	if (listCtrl.GetSelectedCount () == 1)
	{
		int nItem = listCtrl.GetNextItem (-1, LVNI_SELECTED);

		CEdit *pEdit = NULL;
		if (FAILED (EditItem (nItem, 1, &pEdit))) return;

		// TODO:
		// with this uncommented, tab on row selection goes to 
		// description first... whats the point of this again?
		//pEdit->SendMessage (WM_CHAR, nChar, nFlags);
	}
}

void CProLinkView::OnEditFind()
{
	//if (m_pFindDialog != NULL)
	//{
	m_pFindDialog = new CFindReplaceDialog();
	m_pFindDialog->Create(TRUE, "", NULL, FR_DOWN | FR_NOWHOLEWORD | FR_HIDEWHOLEWORD, this);
	//}
	
	//delete m_pFindDialog;
}

void CProLinkView::OnEditFindDuplicates()
{
	// using the same idea as the find feature, this only searches
	// the current screen. ie, all, bank 1, bank 2, etc

	// we are going to use a simple recursive search alogorithm
	// shouldnt be too bad because we are using very few freqs
	gdGetDupe ()->ShowDupeMessagesDialog (this);

	int channels = GetListCtrl().GetItemCount();
	int dupecount = 0, zerocount = 0, duplicated = 0;
	double *found = new double[channels];

	int pos = 0; // position we are up to in found array
	double freq; // temporary frequency holder
	char *end;	 
	CString temp, temp2; // temporary strings for writing the message
	CStringArray dupes; // array of duplicates
	bool isDupe = false;

	
	for (int nRow = 0; nRow < GetListCtrl().GetItemCount(); nRow++)		
	{
		freq = strtod(GetListCtrl().GetItemText(nRow, 1), &end); // frequency
		if (freq == 0)
		{
			zerocount++;
		}
		else
		{
		// search through the array for the current freq
		for (int i = 0; i < pos; i++)
		{
			if (found[i] == freq) // found it
			{	
				dupecount++;
				temp = dupes.GetAt(i);
				temp.Format("%s %d", temp, nRow+1);
				dupes.SetAt(i, temp);				
				isDupe = true;
			}			
		}

		if (!isDupe) // not a duplicate, add it to the array
		{			
			found[pos] = freq;
			dupes.Add("");
			temp = dupes.GetAt(i);
			temp.Format("%d", nRow+1);
			dupes.SetAt(i, temp);
			pos++;			
		}
		isDupe = false;
	}
	}


	if (pos != 0)
	{	
		gdGetDupe ()->Message("FREQUENCY\tCHANNELS");
		for (int j = 0; j < pos; j++)
		{
			// TODO:
			// every non-zero freq has at least 1 number in it, so if we
			// test for the space between numbers, we can find ones that
			// have duplicates. yeah, im sure theres a better way...
			if ((dupes.GetAt(j)).Find(" ") != -1)
			{								
				// TODO: i wish this would prepend zeros correctly!
				// %03.4f on 42.4 should give us 042.4000 but it doesnt :(
				temp2.Format("%03.4f\t\t%s", found[j], dupes.GetAt(j));				
				gdGetDupe ()->Message(temp2);
				temp = temp + temp2;
				duplicated++;
			}	
		}	
		if (duplicated == 0)
		{
			gdGetDupe ()->Clear();
			gdGetDupe ()->Message("No duplicate frequencies were found.");
		}
		gdGetDupe ()->Message(" ");
		temp2.Format("duplicated: %d", duplicated);
		gdGetDupe ()->Message(temp2);
		temp2.Format("duplicates: %d", dupecount);
		gdGetDupe ()->Message(temp2);
		temp2.Format("valid: %d", nRow-dupecount);
		gdGetDupe ()->Message(temp2);
		temp2.Format("free: %d", zerocount);
		gdGetDupe ()->Message(temp2);

	}
	else 
	{
		gdGetDupe ()->Message("The frequency list is empty.");
	}

	delete found;
}

LRESULT CProLinkView::DoFind(WPARAM wParam, LPARAM lParam)
{
	ASSERT(m_pFindDialog != NULL);
    if (m_pFindDialog->IsTerminating())
    {
        m_pFindDialog = NULL;
        return 0;
    }
    if(m_pFindDialog->FindNext())
    {
        //read data from dialog
        CString FindName = m_pFindDialog->GetFindString();
        bool bMatchCase = m_pFindDialog->MatchCase() == TRUE;
        //bool bMatchWholeWord = m_pFindDialog->MatchWholeWord() == TRUE;
        bool bSearchDown = m_pFindDialog->SearchDown() == TRUE;

		POSITION pos = GetListCtrl().GetFirstSelectedItemPosition();
		int nSelectedItem = GetListCtrl().GetNextSelectedItem(pos);

		/* TODO: there's GOTTA be a more efficient way to do this... */

		if (bSearchDown)
		{

		for (int nRow = nSelectedItem+1; nRow < GetListCtrl().GetItemCount(); nRow++)		
		{
			// Check freq(1), desc(2) and car#(3)
			if (bMatchCase)
			{
				if  ((GetListCtrl().GetItemText(nRow, 1).Find(FindName) != -1) ||  
					(GetListCtrl().GetItemText(nRow, 2).Find(FindName) != -1) ||
					(GetListCtrl().GetItemText(nRow, 3).Find(FindName) != -1))
				{				
					SetFocus ();
					SelectItem (nRow, true);
					if (!GetListCtrl().EnsureVisible (nRow+1, FALSE)) return 1;
					return 0;
				}
			}
			else
			{
				CString cFreq = GetListCtrl().GetItemText(nRow, 1).MakeLower();
				CString cDesc = GetListCtrl().GetItemText(nRow, 2).MakeLower();
				CString cCar = GetListCtrl().GetItemText(nRow, 3).MakeLower();
				FindName.MakeLower();

				if  ((cFreq.Find(FindName) != -1) || (cDesc.Find(FindName) != -1) || (cCar.Find(FindName) != -1))
				{
					SetFocus ();
					SelectItem (nRow, true);				
					if (!GetListCtrl().EnsureVisible (nRow+1, FALSE)) return 1;
					m_pFindDialog->SetFocus();
					return 0;
				}
			}			
		}
		AfxMessageBox("Cannot find " + FindName, MB_OK | MB_ICONINFORMATION);
		} // end down
		else // find up
		{			
		for (int nRow = nSelectedItem-1; nRow >= 0; nRow--)		
		{
			// Check freq(1), desc(2) and car#(3)
			if (bMatchCase)
			{
				if  ((GetListCtrl().GetItemText(nRow, 1).Find(FindName) != -1) ||  
					(GetListCtrl().GetItemText(nRow, 2).Find(FindName) != -1) ||
					(GetListCtrl().GetItemText(nRow, 3).Find(FindName) != -1))
				{				
					SetFocus ();
					SelectItem (nRow, true);
					if (!GetListCtrl().EnsureVisible (nRow-1, FALSE)) return 1;
					return 0;
				}
			}
			else
			{
				CString cFreq = GetListCtrl().GetItemText(nRow, 1).MakeLower();
				CString cDesc = GetListCtrl().GetItemText(nRow, 2).MakeLower();
				CString cCar = GetListCtrl().GetItemText(nRow, 3).MakeLower();
				FindName.MakeLower();

				if  ((cFreq.Find(FindName) != -1) || (cDesc.Find(FindName) != -1) || (cCar.Find(FindName) != -1))
				{
					SetFocus ();
					SelectItem (nRow, true);				
					if (!GetListCtrl().EnsureVisible (nRow-1, FALSE))
					{
						m_pFindDialog->SetFocus();
						return 1;
					}
					m_pFindDialog->SetFocus();
					return 0;
				}
			}			
		}
		AfxMessageBox("Cannot find " + FindName, MB_OK | MB_ICONINFORMATION);
		}
	}

    return 0;
}


void CProLinkView::OnEditCopy()
{
	DoCopy(FALSE);
}

void CProLinkView::OnEditCut()
{
	DoCopy(TRUE);
}

void CProLinkView::OnEditPaste()
{
	
	if ( !IsClipboardFormatAvailable( CF_TEXT ) )
		return;
     if ( !OpenClipboard() )
     {
          ASSERT( 0 );
          return;
     }

     HANDLE handle = GetClipboardData( CF_TEXT );
     LPTSTR ptr = (LPTSTR)GlobalLock( handle );

     CString t = ptr;     
     
     GlobalUnlock( handle );

     CloseClipboard();

    CStringArray lines;	
    int numLines = GetStringParts( t, lines, "\r\n" ) - 1; // -1 for terminating \r\n
	int index = 0;

	for (int nItem = 0; nItem < GetListCtrl().GetItemCount (); nItem++)
	{
		if (GetListCtrl().GetItemState (nItem, LVIS_SELECTED))
		{
			if (index < numLines) // there is something to paste...
			{
				CStringArray items;
				// if pasting from somewhere else, make sure these work!
				// may want to remove whitespace too?
				int numItems = GetStringParts(lines.GetAt(index), items, "\t" );								
				if (numItems > 0)
				{					
					GetDocument()->SetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, 1, items.GetAt(0));
				}
				if (numItems > 1)
				{
				
					GetDocument()->SetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, 2, items[1]);
				}
				if (numItems > 2)
				{
				
					GetDocument()->SetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, 3, items[2]);
				}
				if (numItems > 3)
				{
				
					GetDocument()->SetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, 4, items[3]);
				}
				if (numItems > 4)
				{
				
					GetDocument()->SetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, 5, items[4]);
				}
				if (numItems > 5)
				{
				
					GetDocument()->SetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, 6, items[5]);
				}
				index++;
				// pasting to the dummy bank does not affect dirty bit
				if (atoi(GetListCtrl().GetItemText(nItem, 0)) <= GetDocument()->nLastChannel)
					GetDocument()->SetModifiedFlag(TRUE);
			}			
		}
	}
	GetDocument()->UpdateAllViews(NULL);
}

void CProLinkView::DoCopy(BOOL bCut)
{
	CString data;
	GetListCtrl().SetRedraw (FALSE);

	data.Empty();

	for (int nItem = 0; nItem < GetListCtrl().GetItemCount (); nItem++)
	{
		if (GetListCtrl().GetItemState (nItem, LVIS_SELECTED))
		{			
			for (int i = 1; i <= 6; i++)
			{
				data += GetDocument()->GetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, i); //
				data += "\t";
			}
			data += "\r\n";
		}
	}
     if ( !OpenClipboard() )
     {
          ASSERT( 0 );
          return;
    }
    HANDLE handle = GlobalAlloc( GMEM_MOVEABLE, ( data.GetLength() + 1 ) * sizeof( char ) );
    LPTSTR ptr = (LPTSTR)GlobalLock( handle );
    strcpy( ptr, (LPCTSTR)data );
    GlobalUnlock( handle );

	EmptyClipboard();
	SetClipboardData(CF_TEXT, handle);
	CloseClipboard();
	if (bCut) // if we are doing a cut.. delete the data
		OnEditDelete();
	 GetListCtrl().SetRedraw (TRUE);
}


void CProLinkView::OnEditDelete()
{
	
	if ((GetStyle() & LVS_OWNERDATA) != 0) return; // let the parent handle this message

	SetRedraw (FALSE);

	int nSubItem;
	LVCOLUMN Column;
	Column.mask = 0;
	for (int nItem = 0; nItem < GetListCtrl().GetItemCount (); nItem++)
	{
		if (GetListCtrl().GetItemState (nItem, LVIS_SELECTED))
		{

			for (nSubItem = 1; nSubItem <= 6; nSubItem++)
			{
				GetDocument()->SetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, nSubItem, "");
			}
			// cutting from the dummy bank does not affect dirty bit
			if (atoi(GetListCtrl().GetItemText(nItem, 0)) <= GetDocument()->nLastChannel)
				GetDocument()->SetModifiedFlag(TRUE);
		}
	}
	GetDocument()->UpdateAllViews(NULL);
	SetRedraw (TRUE);

}

void CProLinkView::OnEditSelectAll()
{
	SetRedraw (FALSE);

	for (int nItem = 0; nItem < GetListCtrl().GetItemCount (); nItem++)
	{
		GetListCtrl().SetItemState (nItem, LVIS_SELECTED, LVIS_SELECTED);
	}

	SetRedraw (TRUE);
}

void CProLinkView::OnSetAllLockout()
{
	SetRedraw (FALSE);

	for (int nItem = 0; nItem < GetListCtrl().GetItemCount (); nItem++)
	{
		GetDocument()->SetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, CHANNEL_LIST_COLUMN_LOCKOUT, _T("X"));
	}
	if (atoi(GetListCtrl().GetItemText(nItem, 0)) <= GetDocument()->nLastChannel)
		GetDocument()->SetModifiedFlag(TRUE);
	SetRedraw (TRUE);
	GetDocument()->UpdateAllViews(NULL);
}

void CProLinkView::OnSetAllDelay()
{
	SetRedraw (FALSE);

	for (int nItem = 0; nItem < GetListCtrl().GetItemCount (); nItem++)
	{
		GetDocument()->SetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, CHANNEL_LIST_COLUMN_DELAY, _T("X"));
	}
	if (atoi(GetListCtrl().GetItemText(nItem, 0)) <= GetDocument()->nLastChannel)
		GetDocument()->SetModifiedFlag(TRUE);
	SetRedraw (TRUE);
	GetDocument()->UpdateAllViews(NULL);
}

void CProLinkView::OnClearAllDelay()
{
	SetRedraw (FALSE);

	for (int nItem = 0; nItem < GetListCtrl().GetItemCount (); nItem++)
	{
		GetDocument()->SetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, CHANNEL_LIST_COLUMN_DELAY, _T(" "));
	}
	if (atoi(GetListCtrl().GetItemText(nItem, 0)) <= GetDocument()->nLastChannel)
		GetDocument()->SetModifiedFlag(TRUE);
	SetRedraw (TRUE);
	GetDocument()->UpdateAllViews(NULL);
}

void CProLinkView::OnClearAllLockout()
{
	SetRedraw (FALSE);

	for (int nItem = 0; nItem < GetListCtrl().GetItemCount (); nItem++)
	{
		GetDocument()->SetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, CHANNEL_LIST_COLUMN_LOCKOUT, _T(" "));
	}
	if (atoi(GetListCtrl().GetItemText(nItem, 0)) <= GetDocument()->nLastChannel)
		GetDocument()->SetModifiedFlag(TRUE);
	SetRedraw (TRUE);
	GetDocument()->UpdateAllViews(NULL);
}

void CProLinkView::OnClearAllCarNo()
{
	SetRedraw (FALSE);

	for (int nItem = 0; nItem < GetListCtrl().GetItemCount (); nItem++)
	{
		GetDocument()->SetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, CHANNEL_LIST_COLUMN_CARNUMBER, _T(""));
	}
	if (atoi(GetListCtrl().GetItemText(nItem, 0)) <= GetDocument()->nLastChannel)
		GetDocument()->SetModifiedFlag(TRUE);
	SetRedraw (TRUE);
	GetDocument()->UpdateAllViews(NULL);
}

void CProLinkView::OnClearAllDescription()
{
	SetRedraw (FALSE);

	for (int nItem = 0; nItem < GetListCtrl().GetItemCount (); nItem++)
	{
		GetDocument()->SetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, CHANNEL_LIST_COLUMN_DESCRIPTION, _T(""));
	}
	if (atoi(GetListCtrl().GetItemText(nItem, 0)) <= GetDocument()->nLastChannel)
		GetDocument()->SetModifiedFlag(TRUE);
	SetRedraw (TRUE);
	GetDocument()->UpdateAllViews(NULL);
}

void CProLinkView::OnClearAllPriority()
{
	SetRedraw (FALSE);

	for (int nItem = 0; nItem < GetListCtrl().GetItemCount (); nItem++)
	{
		GetDocument()->SetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, CHANNEL_LIST_COLUMN_PRIORITY, _T(" "));
	}
	if (atoi(GetListCtrl().GetItemText(nItem, 0)) <= GetDocument()->nLastChannel)
		GetDocument()->SetModifiedFlag(TRUE);
	SetRedraw (TRUE);
	GetDocument()->UpdateAllViews(NULL);
}

int CProLinkView::FindNumPriChans()
{
	int count = 0;
	for (int nItem = 0; nItem < GetListCtrl().GetItemCount (); nItem++)
	{
		if (GetDocument()->GetItemString(atoi(GetListCtrl().GetItemText(nItem, 0))-1, CHANNEL_LIST_COLUMN_PRIORITY) == "X")
			count++;
	}
	return count;
}

void CProLinkView::OnEndLabelEdit (NMHDR *pNMHDR, LRESULT *lRESULT)
{
	CString strShortName;
	//AfxMessageBox("CALLED ONENDLABELEDIT");
	CListCtrl& listCtrl = GetListCtrl();
//	if ((GetStyle() & LVS_OWNERDATA) != 0) return FALSE; // let the parent handle this message

	NMLVDISPINFO *pDispInfo = reinterpret_cast <NMLVDISPINFO *> (pNMHDR);
	LVITEM *pItem = &pDispInfo->item;

	if (pItem->pszText != NULL)
	{
		GetDocument()->SetItemString (atoi(GetListCtrl().GetItemText(pItem->iItem, 0))-1, pItem->iSubItem, pItem->pszText);					
		if (atoi(GetListCtrl().GetItemText(pItem->iItem, 0)) <= GetDocument()->nLastChannel)
			GetDocument()->SetModifiedFlag(TRUE);
		GetDocument()->UpdateAllViews(NULL);
	}
	
}


void CProLinkView::OnTransferUploadAll ()
{
		
	rlMemory *pMemory;
	HRESULT hResult = GetDocument()->pModule->GetMemory (&pMemory);
	if (FAILED (hResult))
	{
		CString strErrorMessage;
		strErrorMessage.Format (_T("An error occured while attempting to retrieve the rlMemory interface from the selected RadioLink Module.\n\nrlModule::GetMemory () returned error code 0x%X.\n\nPlease contact the maker of this RadioLink Module for further assistance."), hResult);
		::AfxMessageBox (strErrorMessage);
//		GetDocument()->m_RadioLinkManager.ReleaseModule (pModule);
		return;
	}

	if (m_pTransferProgressDialog == NULL) delete m_pTransferProgressDialog;
	m_pTransferProgressDialog = new CTransferProgressDialog (this);
	m_pTransferProgressDialog->Create (IDD_TRANSFER_PROGRESS, this);

	pMemory->SetProgressTarget (this);

	hResult = pMemory->SetAllChannels (&GetDocument()->m_MemoryChannelArray);
	if (FAILED (hResult))
	{
		::AfxMessageBox (_T("A transfer error has occurred."), MB_ICONEXCLAMATION | MB_OK);
	}

	m_pTransferProgressDialog->DestroyWindow ();
	delete m_pTransferProgressDialog;
	m_pTransferProgressDialog = NULL;

//	GetDocument()->m_RadioLinkManager.ReleaseModule (pModule);
}

void CProLinkView::OnTransferUploadSelected()
{
	CListCtrl& listCtrl = GetListCtrl();
	int nSelectedCount = listCtrl.GetSelectedCount ();
	if (nSelectedCount == 0)
	{
		return;
	}


	rlMemory *pMemory;
	HRESULT hResult = GetDocument()->pModule->GetMemory (&pMemory);
	if (FAILED (hResult))
	{

		CString strErrorMessage;
		strErrorMessage.Format (_T("An error occured while attempting to retrieve the rlMemory interface from the selected RadioLink Module.\n\nrlModule::GetMemory () returned error code 0x%X.\n\nPlease contact the maker of this RadioLink Module for further assistance."), hResult);
		::AfxMessageBox (strErrorMessage);
		//GetDocument()->m_RadioLinkManager.ReleaseModule (pModule);
		return;
	}
	int nRow = GetListCtrl().GetNextItem (-1, LVNI_SELECTED);
	int nProgress = 0, nItemSelected = 0;
	CString tempStr;
	if (atoi(GetListCtrl().GetItemText(nRow,0)) > GetDocument()->nLastChannel)
	{
		AfxMessageBox("Error: You can not upload frequencies from the dummy bank, you dummy!", MB_ICONERROR);
		return;
	}

	if (m_pTransferProgressDialog == NULL) delete m_pTransferProgressDialog;
	m_pTransferProgressDialog = new CTransferProgressDialog (this);
	m_pTransferProgressDialog->Create (IDD_TRANSFER_PROGRESS, this);

	m_pTransferProgressDialog->m_ctrlProgress.SetRange (0, (short) nSelectedCount);

	pMemory->SetChannelMultiStart (nSelectedCount);



	while (nRow != -1)
	{
		m_pTransferProgressDialog->m_ctrlProgress.SetPos (nProgress);

		nItemSelected = atoi(GetListCtrl().GetItemText(nRow,0))-1; // damn that -1		

		tempStr.Format("%d", nItemSelected);
		if (!SUCCEEDED (pMemory->SetChannelMulti (GetDocument()->m_MemoryChannelArray.GetAt (nItemSelected))))
		{
			::AfxMessageBox (_T("A transfer error has occurred."), MB_ICONEXCLAMATION | MB_OK);
		}

		nRow = GetListCtrl().GetNextItem (nRow, LVNI_SELECTED);
		nProgress++;
	}

	pMemory->SetChannelMultiEnd ();

	m_pTransferProgressDialog->DestroyWindow ();
	delete m_pTransferProgressDialog;
	m_pTransferProgressDialog = NULL;

//	GetDocument()->m_RadioLinkManager.ReleaseModule (pModule);
}




afx_msg void CProLinkView::OnGetDispInfo (NMHDR *pNotifyStruct, LRESULT * /*lResult*/)
{

	NMLVDISPINFO *pDispInfo = (NMLVDISPINFO *) pNotifyStruct;
	LVITEM *pItem = &(pDispInfo)->item;

	if (pItem->mask & LVIF_TEXT) // need to fill in text
	{
		int nItem = pItem->iItem;
		int nSubItem = pItem->iSubItem;

		CString strTemp = GetDocument()->GetItemString (nItem, nSubItem);
		_tcscpy (pItem->pszText, strTemp);
	}
}

void CProLinkView::OnSetRange (const int nLower, const int nUpper)
{
	if (m_pTransferProgressDialog != NULL)
	{
		m_pTransferProgressDialog->m_ctrlProgress.SetRange32 (nLower, nUpper);
	}
}

void CProLinkView::OnSetPosition (const int nPosition)
{
	if (m_pTransferProgressDialog != NULL)
	{
		m_pTransferProgressDialog->m_ctrlProgress.SetPos (nPosition);
	}
}

void CProLinkView::OnTransferModules ()
{
	rlManagerModulesDlg dlg;
	dlg.DoModal ();
}

void CProLinkView::OnOptionsSettings()
{
		CPropertySheet PropertySheet;
		CSettingsDialog	   PropertyPage;

		PropertySheet.AddPage(&PropertyPage);
		PropertySheet.SetTitle("Settings");
		PropertySheet.DoModal();
		GetDocument()->UpdateAllViews(NULL);
}

void CProLinkView::OnButtonAll()
{
	CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd();
	pMainFrm->ResetToolbar(ID_BUTTON_ALL);
	GetListCtrl().DeleteAllItems();
	for (int i = 0; i < GetDocument()->pMemoryLayout->GetChannelCount(); i++)
		GetListCtrl().InsertItem(i, NULL);
	GetListCtrl().SetItemText(0, 0, "1");
	GetDocument()->UpdateAllViews(NULL);
}

void CProLinkView::OnButton1() { CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd(); pMainFrm->ResetToolbar(ID_BUTTON_1); ShowBank(1); }
void CProLinkView::OnButton2() { CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd(); pMainFrm->ResetToolbar(ID_BUTTON_2); ShowBank(2); }
void CProLinkView::OnButton3() { CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd(); pMainFrm->ResetToolbar(ID_BUTTON_3); ShowBank(3); }
void CProLinkView::OnButton4() { CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd(); pMainFrm->ResetToolbar(ID_BUTTON_4); ShowBank(4); }
void CProLinkView::OnButton5() { CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd(); pMainFrm->ResetToolbar(ID_BUTTON_5); ShowBank(5); }
void CProLinkView::OnButton6() { CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd(); pMainFrm->ResetToolbar(ID_BUTTON_6); ShowBank(6); }
void CProLinkView::OnButton7() { CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd(); pMainFrm->ResetToolbar(ID_BUTTON_7); ShowBank(7); }
void CProLinkView::OnButton8() { CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd(); pMainFrm->ResetToolbar(ID_BUTTON_8); ShowBank(8); }
void CProLinkView::OnButton9() { CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd(); pMainFrm->ResetToolbar(ID_BUTTON_9); ShowBank(9); }
void CProLinkView::OnButton0() { CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd(); pMainFrm->ResetToolbar(ID_BUTTON_0); ShowBank(0); }
void CProLinkView::OnButtonD() { CMainFrame* pMainFrm = (CMainFrame*)AfxGetMainWnd(); pMainFrm->ResetToolbar(ID_BUTTON_D); ShowBank(10); }

void CProLinkView::ShowBank(int bank)
{
	CString tempStr;
	int x = 0;

	GetListCtrl().DeleteAllItems();
	for (int i = 0; i < GetDocument()->pMemoryLayout->GetBankSize(); i++)
		GetListCtrl().InsertItem(i, NULL);
	if (bank == 10)
	{
		x = GetDocument()->pMemoryLayout->GetLastChannel() + 1;
		tempStr.Format("%d", x);		
	}
	else if (bank == 0) // SPECIAL BANK, LAST BANK, STARTS AT LAST FREQ - BANKSIZE
	{
		x = GetDocument()->pMemoryLayout->GetLastChannel() - GetDocument()->pMemoryLayout->GetBankSize() + 1;
		tempStr.Format("%d", x);
	}
	else if (bank == 1) // SPECIAL BANK, ALWAYS STARTS AT 1
	{
		tempStr.Format("1");
	}
	else
	{
		x = ((bank-1) * (GetDocument()->pMemoryLayout->GetBankSize())) + 1;
		tempStr.Format("%d", x);
	}
	GetListCtrl().SetItemText(0, 0, tempStr);
	GetDocument()->UpdateAllViews(NULL);
}


int CProLinkView::GetStringParts(CString src, CStringArray& lines, LPCTSTR pszToken )
{
     CString t;
     int num = 0;
     int id = 0;

     int len = strlen( pszToken );

     do
     {
          id = src.Find( pszToken );

          if ( id > -1 )
          {
               t = src.Left( id );
               src = src.Right( src.GetLength() - id - len );
               lines.Add( t );
          }
          else
               lines.Add( src );

          num++;
     }
     while ( id > -1 );

     return num;
}

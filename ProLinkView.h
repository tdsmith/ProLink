// ProLinkView.h : interface of the CProLinkView class
//
/////////////////////////////////////////////////////////////////////////////

#include "ProLinkDoc.h"
#include "TransferProgressDialog.h"

#define CHANNEL_LIST_COLUMN_NUMBER			0
#define CHANNEL_LIST_COLUMN_FREQUENCY		1
#define CHANNEL_LIST_COLUMN_DESCRIPTION		2
#define CHANNEL_LIST_COLUMN_CARNUMBER		3
#define CHANNEL_LIST_COLUMN_DELAY			4
#define CHANNEL_LIST_COLUMN_LOCKOUT			5
#define CHANNEL_LIST_COLUMN_PRIORITY		6


#if !defined(AFX_ProLinkVIEW_H__F49C0FCC_CBEC_4F32_A5DD_FD64082F448A__INCLUDED_)
#define AFX_ProLinkVIEW_H__F49C0FCC_CBEC_4F32_A5DD_FD64082F448A__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "ProLinkViewPrint.h"

class CProLinkView : public CListView, rlProgressTarget
{
protected: // create from serialization only
	CProLinkView();
	DECLARE_DYNCREATE(CProLinkView)

// Attributes
public:
	CProLinkDoc* GetDocument();

// Operations
public:
	HRESULT EditItem(const int, const int, CEdit **ppEditCtrl = NULL);
// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProLinkView)
	public:
	//virtual void OnDraw(CDC* pDC);  // overridden to draw this view
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	protected:
	virtual void OnUpdate(CView *pSender, LPARAM lHint, CObject *pHint);
	virtual void OnInitialUpdate(); // called first time after construct
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnPrint(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndLabelEdit(NMHDR *pNMHDR, LRESULT *pResult);
	virtual void OnContextMenu(CWnd*, CPoint);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CProLinkView();
	static CProLinkView * GetView();
	afx_msg void OnLButtonDblClk(UINT nFlags, CPoint point);
	void SelectItem(int nItem, bool bDeselectOthers);
	//afx_msg int OnCreate(LPCREATESTRUCT lpcs);
	afx_msg void OnChar(UINT nChar, UINT nRepCnt, UINT nFlags);
	afx_msg void OnTransferModules();
	afx_msg void OnOptionsSettings();
	int GetStringParts(CString src, CStringArray& lines, LPCTSTR pszToken);
	afx_msg void OnTransferUploadAll();
	afx_msg void OnEditSelectAll();
	afx_msg void OnEditDelete();
	afx_msg void OnTransferUploadSelected();
	afx_msg void OnEditCut();
	afx_msg void OnEditCopy();
	afx_msg void OnEditPaste();
	afx_msg void OnEditFind();
	afx_msg void OnEditFindDuplicates();
	afx_msg void OnFileNew();
	afx_msg void OnFileSave();
	afx_msg void OnFileSaveAs();
		
	void DoCopy(BOOL);
	afx_msg LRESULT DoFind(WPARAM, LPARAM);
	afx_msg void OnImportRadioShack();
	afx_msg void OnSetAllLockout();
	afx_msg void OnSetAllDelay();
	afx_msg void OnClearAllCarNo();
	afx_msg void OnClearAllDelay();
	afx_msg void OnClearAllLockout();
	afx_msg void OnClearAllDescription();
	afx_msg void OnClearAllPriority();
	afx_msg void OnButtonAll();
	afx_msg void OnButton1();
	afx_msg void OnButton2();
	afx_msg void OnButton3();
	afx_msg void OnButton4();
	afx_msg void OnButton5();
	afx_msg void OnButton6();
	afx_msg void OnButton7();
	afx_msg void OnButton8();
	afx_msg void OnButton9();
	afx_msg void OnButton0();
	afx_msg void OnButtonD();
	void ShowBank(int);

	virtual void OnSetRange (const int, const int);
	virtual void OnSetPosition (const int);

	const int GetNextItemUp (const int);
	const int GetNextItemDown (const int, const bool = false);
	const int GetNextSubItemLeft (const int);
	const int GetNextSubItemRight (const int);

	afx_msg void OnGetDispInfo (NMHDR *pNotifyStruct, LRESULT *lResult);
	afx_msg void OnCustomdrawMyList ( NMHDR* pNMHDR, LRESULT* pResult );
	
   CProLinkViewPrint m_Print;
	


#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	void ShowAllData();
	int FindNumPriChans();
	void AutoSizeColumns();
	void AutoSizeColumn(int nCol);
   
	CTransferProgressDialog *m_pTransferProgressDialog;

	COLORREF *clr1, *clr2, *clr3, *txtClr;

	CFindReplaceDialog *m_pFindDialog;
	static const UINT m_pFindDialogMessage;



// stuff here
	




	// Generated message map functions
protected:  
	//{{AFX_MSG(CProLinkView)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()

private:
   CListCtrl& m_cListCtrl;

};

#ifndef _DEBUG  // debug version in ProLinkView.cpp
inline CProLinkDoc* CProLinkView::GetDocument()
   { return (CProLinkDoc*)m_pDocument; }
#endif

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ProLinkVIEW_H__F49C0FCC_CBEC_4F32_A5DD_FD64082F448A__INCLUDED_)

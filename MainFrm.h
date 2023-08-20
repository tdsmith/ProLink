// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////



#define CHANNEL_LIST_COLUMN_NUMBER			0
#define CHANNEL_LIST_COLUMN_FREQUENCY		1
#define CHANNEL_LIST_COLUMN_DESCRIPTION		2
#define CHANNEL_LIST_COLUMN_CARNUMBER		3
#define CHANNEL_LIST_COLUMN_DELAY			4
#define CHANNEL_LIST_COLUMN_LOCKOUT			5
#define CHANNEL_LIST_COLUMN_PRIORITY		6

#if !defined(AFX_MAINFRM_H__10707995_F9F7_4024_ACBD_316FDAB9B4E7__INCLUDED_)
#define AFX_MAINFRM_H__10707995_F9F7_4024_ACBD_316FDAB9B4E7__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:

// Operations
public:

	//afx_msg void OnFileNew();

	//LRESULT WMFileOpen(WPARAM,LPARAM);
	// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMainFrame)
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	//}}AFX_VIRTUAL

// Implementation
public:
	virtual ~CMainFrame();
	void ResetToolbar(int);
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CStatusBar  m_wndStatusBar;
	CToolBar    m_wndToolBar;


// Generated message map functions
protected:
	
	//{{AFX_MSG(CMainFrame)
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG


	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MAINFRM_H__10707995_F9F7_4024_ACBD_316FDAB9B4E7__INCLUDED_)

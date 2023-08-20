// MainFrm.cpp : implementation of the CMainFrame class
//

#include "stdafx.h"
#include "ProLink.h"
#include "ProLinkView.h"
#include "rlManagerModulesDlg.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	//{{AFX_MSG_MAP(CMainFrame)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	ON_WM_CREATE()
	//}}AFX_MSG_MAP
	//ON_WM_CREATE ()
	ON_WM_SETFOCUS ()
//	ON_MESSAGE(WM_FILE_OPEN, WMFileOpen)
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

/////////////////////////////////////////////////////////////////////////////
// CMainFrame construction/destruction

CMainFrame::CMainFrame()
{
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
//	AfxMessageBox("MainFrame CREATE");
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;
	
	
	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP
		| CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	// Change properties for the bank buttons..
	ResetToolbar(ID_BUTTON_ALL);

	if (!m_wndStatusBar.Create(this) ||
		!m_wndStatusBar.SetIndicators(indicators,
		  sizeof(indicators)/sizeof(UINT)))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}


	// TODO: Delete these three lines if you don't want the toolbar to
	//  be dockable
	//m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	//EnableDocking(CBRS_ALIGN_ANY);
	//DockControlBar(&m_wndToolBar);
	
	
//	OnFileNew();

	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

void CMainFrame::ResetToolbar(int pressed)
{
	m_wndToolBar.SetButtonStyle( m_wndToolBar.CommandToIndex(ID_BUTTON_ALL), TBBS_CHECKBOX | TBBS_GROUP );
	m_wndToolBar.SetButtonStyle( m_wndToolBar.CommandToIndex(ID_BUTTON_D), TBBS_CHECKBOX | TBBS_GROUP );
	m_wndToolBar.SetButtonStyle( m_wndToolBar.CommandToIndex(ID_BUTTON_0), TBBS_CHECKBOX | TBBS_GROUP );
	m_wndToolBar.SetButtonStyle( m_wndToolBar.CommandToIndex(ID_BUTTON_1), TBBS_CHECKBOX | TBBS_GROUP );
	m_wndToolBar.SetButtonStyle( m_wndToolBar.CommandToIndex(ID_BUTTON_2), TBBS_CHECKBOX | TBBS_GROUP );
	m_wndToolBar.SetButtonStyle( m_wndToolBar.CommandToIndex(ID_BUTTON_3), TBBS_CHECKBOX | TBBS_GROUP );
	m_wndToolBar.SetButtonStyle( m_wndToolBar.CommandToIndex(ID_BUTTON_4), TBBS_CHECKBOX | TBBS_GROUP );
	m_wndToolBar.SetButtonStyle( m_wndToolBar.CommandToIndex(ID_BUTTON_5), TBBS_CHECKBOX | TBBS_GROUP );
	m_wndToolBar.SetButtonStyle( m_wndToolBar.CommandToIndex(ID_BUTTON_6), TBBS_CHECKBOX | TBBS_GROUP );
	m_wndToolBar.SetButtonStyle( m_wndToolBar.CommandToIndex(ID_BUTTON_7), TBBS_CHECKBOX | TBBS_GROUP );
	m_wndToolBar.SetButtonStyle( m_wndToolBar.CommandToIndex(ID_BUTTON_8), TBBS_CHECKBOX | TBBS_GROUP );
	m_wndToolBar.SetButtonStyle( m_wndToolBar.CommandToIndex(ID_BUTTON_9), TBBS_CHECKBOX | TBBS_GROUP );

	m_wndToolBar.SetButtonStyle( m_wndToolBar.CommandToIndex(pressed), TBBS_CHECKED | TBBS_CHECKBOX | TBBS_GROUP );
}

/////////////////////////////////////////////////////////////////////////////
// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}

#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CMainFrame message handlers


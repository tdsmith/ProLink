// ProLink.h : main header file for the ProLink application
//

#if !defined(AFX_ProLink_H__5452551E_B2A5_4719_A826_F1D6181EB5FC__INCLUDED_)
#define AFX_ProLink_H__5452551E_B2A5_4719_A826_F1D6181EB5FC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"       // main symbols

/////////////////////////////////////////////////////////////////////////////
// CProLinkApp:
// See ProLink.cpp for the implementation of this class
//

class CProLinkApp : public CWinApp
{
public:
	CProLinkApp();

// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProLinkApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// Implementation
	//{{AFX_MSG(CProLinkApp)
	afx_msg void OnAppAbout();
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ProLink_H__5452551E_B2A5_4719_A826_F1D6181EB5FC__INCLUDED_)

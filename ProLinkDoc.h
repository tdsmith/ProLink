// ProLinkDoc.h : interface of the CProLinkDoc class
//
/////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"

#if !defined(AFX_ProLinkDOC_H__FFC29200_B748_4B3E_B9EF_637FAF711AFD__INCLUDED_)
#define AFX_ProLinkDOC_H__FFC29200_B748_4B3E_B9EF_637FAF711AFD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


#include "rlManager.h"

#include "rlMemoryChannelArray.h"
#include "rlProgressTarget.h"
#include "Table.h"
#include "DelimitedTextFile.h"
#include "ProLink.h"


#define CHANNEL_LIST_COLUMN_NUMBER			0
#define CHANNEL_LIST_COLUMN_FREQUENCY		1
#define CHANNEL_LIST_COLUMN_DESCRIPTION		2
#define CHANNEL_LIST_COLUMN_CARNUMBER		3
#define CHANNEL_LIST_COLUMN_DELAY			4
#define CHANNEL_LIST_COLUMN_LOCKOUT			5
#define CHANNEL_LIST_COLUMN_PRIORITY		6

class CProLinkDoc : public CDocument
{
protected: // create from serialization only
	CProLinkDoc();
	DECLARE_DYNCREATE(CProLinkDoc)

// Attributes
public:


// Operations
public:


// Overrides
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CProLinkDoc)
	public:
	virtual BOOL OnNewDocument();
	//virtual BOOL SaveModified();
	//virtual BOOL DoFileSave();
	virtual void OnCloseDocument();
	virtual void SetModifiedFlag(BOOL bModified);
	virtual BOOL OnSaveDocument(LPCTSTR);
	virtual BOOL OnOpenDocument(LPCTSTR);
	virtual void Serialize(CArchive& ar);
	//}}AFX_VIRTUAL

// Implementation
public:
	//virtual CProLinkDoc();
	virtual ~CProLinkDoc();
	rlMemoryChannelArray m_MemoryChannelArray;
	rlManager m_RadioLinkManager;
	//rlMemoryLayout pMemoryLayout;

	rlModule *pModule; // make this static?
	rlMemoryLayout *pMemoryLayout;
	int nFirstChannel, nLastChannel, nBankSize;	
	//CString		m_strFileName;
	void SetItemString (const int, const int, const CString);
	const CString GetItemString (const int, const int);

#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:
	
	

	
// Generated message map functions
protected:
	//{{AFX_MSG(CProLinkDoc)
		// NOTE - the ClassWizard will add and remove member functions here.
		//    DO NOT EDIT what you see in these blocks of generated code !
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_ProLinkDOC_H__FFC29200_B748_4B3E_B9EF_637FAF711AFD__INCLUDED_)

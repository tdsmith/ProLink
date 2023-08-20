// gdDupeMessagesDialog.cpp : implementation file
//

#include "stdafx.h"
#include "ProLink.h"
#include "gdDupeMessagesDialog.h"


// gdDupeMessagesDialog dialog

IMPLEMENT_DYNAMIC(gdDupeMessagesDialog, CDialog)
gdDupeMessagesDialog::gdDupeMessagesDialog(CWnd* pParent /*=NULL*/)
	: CDialog(gdDupeMessagesDialog::IDD, pParent)
{
}

gdDupeMessagesDialog::~gdDupeMessagesDialog()
{
}

void gdDupeMessagesDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_DUPE_MESSAGES, m_lstDupeMessages);	
}


BEGIN_MESSAGE_MAP(gdDupeMessagesDialog, CDialog)
	ON_WM_SIZE()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()


// gdDupeMessagesDialog message handlers

BOOL gdDupeMessagesDialog::OnInitDialog ()
{
	CDialog::OnInitDialog ();

	CRect rect;
	GetClientRect (&rect);
	m_lstDupeMessages.MoveWindow (&rect);

	return TRUE;
}

void gdDupeMessagesDialog::OnSize (UINT nType, int cx, int cy)
{
	CDialog::OnSize (nType, cx, cy);

	if (m_lstDupeMessages.m_hWnd != NULL)
	{
		m_lstDupeMessages.MoveWindow (0, 0, cx, cy);
	}
}

void gdDupeMessagesDialog::Clear()
{
	m_lstDupeMessages.SetWindowText ("");
}

void gdDupeMessagesDialog::AddMessage (const CString strMessage)
{	
	CString windowText;		
	m_lstDupeMessages.GetWindowText(windowText);	
	windowText.Append("\r\n");
	windowText.Append(strMessage);
	m_lstDupeMessages.SetWindowText (windowText);
}

void gdDupeMessagesDialog::OnCancel()
{
	CDialog::OnCancel();

	DestroyWindow ();
}

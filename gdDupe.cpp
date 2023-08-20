// Note: this code was shamelessly taken from the ProLink 0.30 alpha
// source code and modified as needed.

#include "StdAfx.h"
#include "gdDupe.h"

#include "gdDupeMessagesDialog.h"

gdDupe G_GD_DUPE_OBJECT;

gdDupe *gdGetDupe (void)
{
	return &G_GD_DUPE_OBJECT;
}

gdDupe::gdDupe(void)
{
	m_pMessagesDialog = new gdDupeMessagesDialog;
}

gdDupe::~gdDupe(void)
{
	delete m_pMessagesDialog;
}

void gdDupe::Clear ()
{
	m_pMessagesDialog->Clear();
}

void gdDupe::Message (LPCTSTR lpMessage, ...)
{
	va_list args;
	va_start (args, lpMessage); 

	void *pArgs = *(void **)args;

	CString strTemp;
	strTemp.Format (lpMessage, pArgs);

	if (IsWindow (*m_pMessagesDialog)) m_pMessagesDialog->AddMessage (strTemp);

	va_end (args);
}


void gdDupe::ShowDupeMessagesDialog (CWnd *pParent)
{	
	if (IsWindow (*m_pMessagesDialog))
	{
		m_pMessagesDialog->DestroyWindow();
	}
	m_pMessagesDialog->Create (IDD_DUPE_MESSAGES, pParent);
	m_pMessagesDialog->ShowWindow (SW_SHOWDEFAULT);
}


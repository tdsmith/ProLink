#pragma once
#include "afxcmn.h"
#include "Resource.h"

// CTransferProgressDialog dialog

class CTransferProgressDialog : public CDialog
{
	DECLARE_DYNAMIC(CTransferProgressDialog)

public:
	CTransferProgressDialog(CWnd* pParent = NULL);   // standard constructor
	virtual ~CTransferProgressDialog();

// Dialog Data
	enum { IDD = IDD_TRANSFER_PROGRESS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	CProgressCtrl m_ctrlProgress;
};

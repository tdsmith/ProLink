// TransferProgressDialog.cpp : implementation file
//

#include "stdafx.h"
#include "TransferProgressDialog.h"
#include "Resource.h"

// CTransferProgressDialog dialog

IMPLEMENT_DYNAMIC(CTransferProgressDialog, CDialog)
CTransferProgressDialog::CTransferProgressDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CTransferProgressDialog::IDD, pParent)
{
}

CTransferProgressDialog::~CTransferProgressDialog()
{
}

void CTransferProgressDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PROGRESS, m_ctrlProgress);
}


BEGIN_MESSAGE_MAP(CTransferProgressDialog, CDialog)
END_MESSAGE_MAP()


// CTransferProgressDialog message handlers


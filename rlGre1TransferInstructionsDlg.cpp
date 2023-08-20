// rlGre1TransferInstructionsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProLink.h"
#include "rlGre1TransferInstructionsDlg.h"


// rlGre1TransferInstructionsDlg dialog

IMPLEMENT_DYNAMIC(rlGre1TransferInstructionsDlg, CDialog)
rlGre1TransferInstructionsDlg::rlGre1TransferInstructionsDlg(CWnd* pParent /*=NULL*/)
	: CDialog(rlGre1TransferInstructionsDlg::IDD, pParent)
	, m_bDontShowAgain(FALSE)
{
}

rlGre1TransferInstructionsDlg::~rlGre1TransferInstructionsDlg()
{
}

void rlGre1TransferInstructionsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_DONTSHOWAGAIN, m_bDontShowAgain);
}


BEGIN_MESSAGE_MAP(rlGre1TransferInstructionsDlg, CDialog)
END_MESSAGE_MAP()


// rlGre1TransferInstructionsDlg message handlers

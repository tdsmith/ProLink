#pragma once

#include "resource.h"
// rlGre1TransferInstructionsDlg dialog

class rlGre1TransferInstructionsDlg : public CDialog
{
	DECLARE_DYNAMIC(rlGre1TransferInstructionsDlg)

public:
	rlGre1TransferInstructionsDlg(CWnd* pParent = NULL);   // standard constructor
	virtual ~rlGre1TransferInstructionsDlg();

// Dialog Data
	enum { IDD = IDD_GRE1_TRANSFERINSTRUCTIONS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	BOOL m_bDontShowAgain;
};

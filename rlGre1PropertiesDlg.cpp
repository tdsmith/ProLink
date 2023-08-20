// rlGre1PropertiesDlg.cpp : implementation file
//

#include "stdafx.h"
#include "ProLink.h"
#include "rlGre1PropertiesDlg.h"


struct GRE1_RADIO_MODEL
{
	LPCTSTR	lpszModelName;
	DWORD	dwBaudRate;
	BYTE	cStopBits;
	bool	bSupportsCarNumbers;
	DWORD	nPriorityChannels;
};

GRE1_RADIO_MODEL g_RadioModels [] =
{
	{	_T("RadioShack Pro-64"),		0,		0,	false,	0},		// communication settings unknown
	{	_T("RadioShack Pro-76"),		2400,	2,	false,	10},	// setting from Riley McArdle
	{	_T("RadioShack Pro-79"),		4800,	2,	false,	1},		// setting from Mark Horka
	{	_T("RadioShack Pro-82"),		0,		0,	false,	0},		// communication settings unknown
	{	_T("RadioShack Pro-89"),		4800,	2,	true,	1},		// setting from Riley McArdle
	{	_T("RadioShack Pro-2016"),		0,		0,	false,	0},		// communication settings unknown
	{	_T("RadioShack Pro-2017"),		0,		0,	false,	0},		// communication settings unknown
	{	_T("RadioShack Pro-2041"),		0,		0,	false,	0},		// communication settings unknown
};


// rlGre1PropertiesDlg dialog

IMPLEMENT_DYNAMIC(rlGre1PropertiesDlg, CDialog)
rlGre1PropertiesDlg::rlGre1PropertiesDlg(CWnd* pParent /*=NULL*/)
	: CDialog(rlGre1PropertiesDlg::IDD, pParent)
	, m_strModel(_T(""))
	, m_strPort(_T(""))
	, m_strSpeed(_T(""))
	, m_strStopBits(_T(""))
	, m_bCarNumbers(FALSE)
	, m_bShowTransferInstructions(FALSE)
	, m_nPriorityChannels(_T(""))
{
}

rlGre1PropertiesDlg::~rlGre1PropertiesDlg()
{
}

void rlGre1PropertiesDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MODEL, m_cmbModel);
	DDX_Control(pDX, IDC_PORT, m_cmbPort);
	DDX_Control(pDX, IDC_SPEED, m_cmbSpeed);
	DDX_Control(pDX, IDC_STOPBITS, m_cmbStopBits);
	DDX_Control(pDX, IDC_CARNUMBERS, m_chkCarNumbers);
	DDX_Control(pDX, IDC_PRICHANS, m_cmbPriChans);
	DDX_CBString(pDX, IDC_MODEL, m_strModel);
	DDX_CBString(pDX, IDC_PORT, m_strPort);
	DDX_CBString(pDX, IDC_SPEED, m_strSpeed);
	DDX_CBString(pDX, IDC_STOPBITS, m_strStopBits);
	DDX_CBString(pDX, IDC_PRICHANS, m_nPriorityChannels);
	DDX_Check(pDX, IDC_CARNUMBERS, m_bCarNumbers);
	DDX_Check(pDX, IDC_TRANSFERINSTRUCTIONS, m_bShowTransferInstructions);
}


BEGIN_MESSAGE_MAP(rlGre1PropertiesDlg, CDialog)
	ON_CBN_SELCHANGE(IDC_MODEL, OnCbnSelChangeModel)
END_MESSAGE_MAP()


// rlGre1PropertiesDlg message handlers

BOOL rlGre1PropertiesDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	m_cmbModel.AddString ("(Custom)");

	for (int x = 0; x < sizeof (g_RadioModels) / sizeof (GRE1_RADIO_MODEL); x++)
	{
		m_cmbModel.AddString (g_RadioModels [x].lpszModelName);
	}

	m_cmbPort.AddString ("COM1");
	m_cmbPort.AddString ("COM2");
	m_cmbPort.AddString ("COM3");
	m_cmbPort.AddString ("COM4");
	m_cmbPort.AddString ("COM5");
	m_cmbPort.AddString ("COM6");
	m_cmbPort.AddString ("COM7");
	m_cmbPort.AddString ("COM8");
	m_cmbPort.AddString ("COM9");

	m_cmbSpeed.AddString ("1200");
	m_cmbSpeed.AddString ("2400");
	m_cmbSpeed.AddString ("4800");
	m_cmbSpeed.AddString ("9600");

	m_cmbStopBits.AddString ("1");
	m_cmbStopBits.AddString ("2");

	m_cmbPriChans.AddString ("1");
	m_cmbPriChans.AddString ("10");
	m_cmbPriChans.AddString ("(Custom)");

	m_cmbModel.SetCurSel (m_cmbModel.FindString (-1, m_strModel));
	m_cmbPort.SetCurSel (m_cmbPort.FindString (-1, m_strPort));
	m_cmbSpeed.SetCurSel (m_cmbSpeed.FindString (-1, m_strSpeed));
	m_cmbStopBits.SetCurSel (m_cmbStopBits.FindString (-1, m_strStopBits));
	m_cmbPriChans.SetCurSel (m_cmbPriChans.FindString (-1, m_nPriorityChannels));

	OnCbnSelChangeModel ();

	return TRUE;
}

void rlGre1PropertiesDlg::OnCbnSelChangeModel ()
{
	int nIndex = m_cmbModel.GetCurSel ();

	if (nIndex == 0) // "(Custom)"
	{
		m_cmbSpeed.EnableWindow (true);
		m_cmbStopBits.EnableWindow (true);
		m_chkCarNumbers.EnableWindow (true);
		m_cmbPriChans.EnableWindow (true);
	}
	else
	{
		GRE1_RADIO_MODEL RadioModel = g_RadioModels [nIndex - 1];
		CString strTemp;

		if (RadioModel.dwBaudRate != 0)
		{
			strTemp.Format ("%d", RadioModel.dwBaudRate);
			m_cmbSpeed.SetCurSel (m_cmbSpeed.FindString (-1, strTemp));
			m_cmbSpeed.EnableWindow (false);
		}
		else
		{
			m_cmbSpeed.SetCurSel (2);
			m_cmbSpeed.EnableWindow (true);
		}

		if (RadioModel.cStopBits != 0)
		{
			strTemp.Format ("%d", RadioModel.cStopBits);
			m_cmbStopBits.SetCurSel (m_cmbStopBits.FindString (-1, strTemp));
			m_cmbStopBits.EnableWindow (false);
		}
		else
		{
			m_cmbStopBits.SetCurSel (1);
			m_cmbStopBits.EnableWindow (true);
		}

		if (RadioModel.nPriorityChannels != 0)
		{
			strTemp.Format ("%d", RadioModel.nPriorityChannels);
			m_cmbPriChans.SetCurSel (m_cmbPriChans.FindString (-1, strTemp));
			m_cmbPriChans.EnableWindow (false);
		}
		else
		{
			m_cmbPriChans.SetCurSel (0);
			m_cmbPriChans.EnableWindow (true);
		}


		m_chkCarNumbers.SetCheck (RadioModel.bSupportsCarNumbers);
		m_chkCarNumbers.EnableWindow (false);

	}
}

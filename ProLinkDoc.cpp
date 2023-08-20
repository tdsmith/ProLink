// ProLinkDoc.cpp : implementation of the CProLinkDoc class
//
#include "stdafx.h"

#include "ProLinkDoc.h"
#include "ProLinkView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CProLinkDoc

IMPLEMENT_DYNCREATE(CProLinkDoc, CDocument)

BEGIN_MESSAGE_MAP(CProLinkDoc, CDocument)
	//{{AFX_MSG_MAP(CProLinkDoc)
		// NOTE - the ClassWizard will add and remove mapping macros here.
		//    DO NOT EDIT what you see in these blocks of generated code!
	//}}AFX_MSG_MAP
	ON_COMMAND(ID_FILE_SAVE, CDocument::OnFileSave)
	ON_COMMAND(ID_FILE_SAVE_AS, CDocument::OnFileSaveAs)
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CProLinkDoc construction/destruction

CProLinkDoc::CProLinkDoc()
{
	m_RadioLinkManager.GetDefaultModule (&pModule);
	pModule->GetMemoryLayout (&pMemoryLayout);

	nFirstChannel = pMemoryLayout->GetFirstChannel();
	nLastChannel = pMemoryLayout->GetLastChannel();
	nBankSize = pMemoryLayout->GetBankSize();	
}

CProLinkDoc::~CProLinkDoc()
{
	delete pModule;	
}


void CProLinkDoc::SetModifiedFlag(BOOL bModified)
{
   if (IsModified() != bModified) {
      CDocument::SetModifiedFlag(bModified);
      CString title = GetTitle();
      int asterisk = title.GetLength()-1;
      if (asterisk >=0 && title.GetAt(asterisk)=='*') {
         if (!bModified)
            title.SetAt(asterisk,0);
      } else if (bModified)
         title += '*';
      SetTitle(title);
   }
}

BOOL CProLinkDoc::OnNewDocument()
{

//	ASSERT(&pModule == NULL);


//	m_RadioLinkManager.ReleaseModule (pModule);
	CString strTemp;
	rlMemoryChannel *pChannelTemp;

 
	
	// check to see if the dummy bank is empty
	// TODO2006: make this its own boolean function
	if (m_MemoryChannelArray.GetCount() != 0)
	{
		for (int x = nLastChannel; x < nLastChannel+nBankSize; x++)
		{
			pChannelTemp = m_MemoryChannelArray.GetAt(x);
			if (pChannelTemp->GetFrequency().GetFrequency() != 0)
				if(AfxMessageBox("The dummy bank is not empty and all data in it will be lost. Do you want to continue?", MB_YESNO | MB_ICONQUESTION) == IDNO)
					return FALSE;
				else
					break;
		}
	}

	m_MemoryChannelArray.Empty ();



	for (int x = nFirstChannel; x <= nLastChannel + nBankSize; x++)
	{
		strTemp.Format ("%d", x);
		m_MemoryChannelArray.Add (&pChannelTemp);
		pChannelTemp->SetChannelNumber (x);
	}
	UpdateAllViews( NULL );

	
	//SendMessage(ID_BUTTON_ALL, 0, 0);

	return CDocument::OnNewDocument();
}

void CProLinkDoc::OnCloseDocument()
{
	//delete pModule;
	//delete pMemoryLayout;

	CDocument::OnCloseDocument();
}

BOOL CProLinkDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	SetPathName(lpszPathName);
	CString strFileName;
	strFileName.Format("%s", lpszPathName);
	CTable ChannelDataTable;

	ChannelDataTable.AddColumn (7);
	ChannelDataTable.AddRow (m_MemoryChannelArray.GetCount()+1-nBankSize);

	CTableCell cellID (_T("ID"));
	CTableCell cellFrequency (_T("Frequency"));
	CTableCell cellDescription (_T("Description"));
	CTableCell cellNumber (_T("Car Number"));
	CTableCell cellDelay (_T("Delay"));
	CTableCell cellLockout (_T("Lockout"));
	CTableCell cellPriority (_T("Priority"));

	ChannelDataTable.SetCell (0, CHANNEL_LIST_COLUMN_NUMBER, &cellID);
	ChannelDataTable.SetCell (0, CHANNEL_LIST_COLUMN_FREQUENCY, &cellFrequency);
	ChannelDataTable.SetCell (0, CHANNEL_LIST_COLUMN_DESCRIPTION, &cellDescription);
	ChannelDataTable.SetCell (0, CHANNEL_LIST_COLUMN_CARNUMBER, &cellNumber);
	ChannelDataTable.SetCell (0, CHANNEL_LIST_COLUMN_DELAY, &cellDelay);
	ChannelDataTable.SetCell (0, CHANNEL_LIST_COLUMN_LOCKOUT, &cellLockout);
	ChannelDataTable.SetCell (0, CHANNEL_LIST_COLUMN_PRIORITY, &cellPriority);

	CString strItemString;
	CTableCell CellData;

	for (int nRow = 0; nRow < m_MemoryChannelArray.GetCount()-nBankSize; nRow++)
	{
		for (int nColumn = 0; nColumn < ChannelDataTable.GetColumnCount(); nColumn++)
		{
			strItemString = GetItemString (nRow, nColumn);

			if (nColumn == CHANNEL_LIST_COLUMN_CARNUMBER)
			{
				CellData.SetData (&strItemString);
			}
			else
			{
				CellData.SetDataAutoType (&strItemString);
			}
			
			ChannelDataTable.SetCell (nRow + 1, nColumn, &CellData);
		}
	}

	CDelimitedTextFile dtfTextFile (&ChannelDataTable);
	if (!dtfTextFile.SaveFile (&strFileName))
	{
		::AfxMessageBox (_T("The file could not be saved.\n"), MB_ICONEXCLAMATION | MB_OK);
	}

	SetModifiedFlag(FALSE);	

	POSITION pos = GetFirstViewPosition();
	CProLinkView* pFirstView = (CProLinkView*) GetNextView( pos );
	pFirstView->m_Print.SetDocTitle(GetTitle());

	// TODO 2006: why does CDocument::OnSaveDocument(lpszPathName)
	// clobber my file?!?!
	return TRUE;
}

BOOL CProLinkDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	SetPathName(lpszPathName);	
	CString strFileName;
	strFileName.Format("%s", lpszPathName);

	CTable ChannelDataTable;
	CDelimitedTextFile dtfTextFile (&ChannelDataTable);
	
	if (!dtfTextFile.LoadFile (&GetPathName()))
	{
		::AfxMessageBox (_T("The file could not be opened.\n"), MB_ICONEXCLAMATION | MB_OK);
		return FALSE;
	}

	m_MemoryChannelArray.Empty ();
	
	rlMemoryChannel *pChannelTemp;
	CString strTemp;

	// import frequencies from data table
	for (int nRow = 0; nRow < ChannelDataTable.GetRowCount()-1+nBankSize; nRow++)
	{
		
		m_MemoryChannelArray.Add (&pChannelTemp);
		strTemp.Format("%d", nRow+1);
		SetItemString (nRow, 0, strTemp);
		for (int nColumn = 1; nColumn < ChannelDataTable.GetColumnCount(); nColumn++)
		{
			if (nRow < ChannelDataTable.GetRowCount()-1)
				strTemp = ChannelDataTable.GetCell (nRow + 1, nColumn)->GetDataString ();
			else
				strTemp.Format("");
			SetItemString (nRow, nColumn, strTemp);			
		}
	}
	
	SetModifiedFlag(FALSE);
	SetTitle(strFileName);
	return TRUE;//	CDocument::OnOpenDocument(lpszPathName);
}

/////////////////////////////////////////////////////////////////////////////
// CProLinkDoc serialization

void CProLinkDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: add storing code here
	}
	else
	{
		// TODO: add loading code here
	}
}

/////////////////////////////////////////////////////////////////////////////
// CProLinkDoc diagnostics

#ifdef _DEBUG
void CProLinkDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CProLinkDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG

/////////////////////////////////////////////////////////////////////////////
// CProLinkDoc commands

void CProLinkDoc::SetItemString (const int nItem, const int nSubItem, const CString strText)
{
	rlMemoryChannel *pMemoryChannel = m_MemoryChannelArray.GetAt (nItem);
	int nChannelNumber;
	rlFrequency Frequency;
	CString strTemp = strText;	
	
	switch (nSubItem)
	{
		case CHANNEL_LIST_COLUMN_NUMBER:
			nChannelNumber = _tstoi (strText);
			pMemoryChannel->SetChannelNumber (nChannelNumber);
			break;
		case CHANNEL_LIST_COLUMN_FREQUENCY:
			Frequency.SetFrequencyMHz (strtod (strText, NULL));
			if (Frequency.GetFrequencyMHz() != 0)
				strTemp.Format("%.4f", Frequency.GetFrequencyMHz());
			else
				strTemp.Format("");
			pMemoryChannel->SetFrequency (&Frequency);
			break;
		case CHANNEL_LIST_COLUMN_DESCRIPTION:
			pMemoryChannel->SetDescription (strText);
			break;
		case CHANNEL_LIST_COLUMN_CARNUMBER:
			pMemoryChannel->SetCarNumber (strText);
			break;
		case CHANNEL_LIST_COLUMN_DELAY:
			if (!strText.CompareNoCase (_T("X")) || !strText.CompareNoCase (_T("yes")) || !strText.CompareNoCase (_T("On")))
			{
				pMemoryChannel->SetDelay (true);
			}
			else
			{
				pMemoryChannel->SetDelay (false);
			}
			break;
		case CHANNEL_LIST_COLUMN_LOCKOUT:
			if (!strText.CompareNoCase (_T("X")) || !strText.CompareNoCase (_T("yes")) || !strText.CompareNoCase (_T("On")))
			{
				pMemoryChannel->SetLockout (true);
			}
			else
			{
				pMemoryChannel->SetLockout (false);
			}
			break;
		case CHANNEL_LIST_COLUMN_PRIORITY:			
			if (!strText.CompareNoCase (_T("X")) || !strText.CompareNoCase (_T("yes")) || !strText.CompareNoCase (_T("On")))
			{
				pMemoryChannel->SetPriority (true);
			}
			else
			{
				pMemoryChannel->SetPriority (false);
			}
			break;
		default:
			break;
	};
}


const CString CProLinkDoc::GetItemString (const int nItem, const int nSubItem)
{
	ASSERT(&m_MemoryChannelArray != NULL);
	rlMemoryChannel *pMemoryChannel = m_MemoryChannelArray.GetAt (nItem);
	CString strTemp;

	switch (nSubItem)
	{
		case CHANNEL_LIST_COLUMN_NUMBER:
			strTemp.Format ("%d", pMemoryChannel->GetChannelNumber ());
			break;
		case CHANNEL_LIST_COLUMN_FREQUENCY:
			if (pMemoryChannel->GetFrequency ().GetFrequencyMHz () != 0)
			{
				strTemp.Format ("%.4f", pMemoryChannel->GetFrequency ().GetFrequencyMHz ());
			}
			break;
		case CHANNEL_LIST_COLUMN_DESCRIPTION:
			strTemp = pMemoryChannel->GetDescription ();
			break;
		case CHANNEL_LIST_COLUMN_CARNUMBER:
			strTemp = pMemoryChannel->GetCarNumber ();
			break;
		case CHANNEL_LIST_COLUMN_DELAY:
			strTemp = pMemoryChannel->GetDelay ()?_T("X"):_T(" ");
			break;
		case CHANNEL_LIST_COLUMN_LOCKOUT:
			strTemp = pMemoryChannel->GetLockout ()?_T("X"):_T(" ");
			break;
		case CHANNEL_LIST_COLUMN_PRIORITY:
			strTemp = pMemoryChannel->GetPriority ()?_T("X"):_T(" ");
			break;
		default:
			break;
	};

	return strTemp;
}


// DelimitedTextFile.cpp: implementation of the CDelimitedTextFile class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DelimitedTextFile.h"

#include "DelimitedTextParser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDelimitedTextFile::CDelimitedTextFile (CTable *pTable)
{
	m_pTable = pTable;
}

CDelimitedTextFile::~CDelimitedTextFile ()
{

}

void CDelimitedTextFile::SetTable (CTable *pTable)
{
	m_pTable = pTable;
}

const int CDelimitedTextFile::LoadFile (const CString *strFileName)
{
	HANDLE hFile = ::CreateFile (*strFileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return 0;

	m_pTable->DeleteAll ();

	CString strBuffer;		// holds the running buffer
	CString strTemp;		// temporarily holds the information recieved from ::ReadFile
	LPSTR lpTemp;			// a pointer to the information in strTemp
	CString strLine;		// holds the current line
	DWORD dwBytesRead = 0;	// recieves the number of bytes that ::ReadFile actually read
	BOOL bReadStatus;		// return value from ::ReadFile
	bool bEndOfFile = false;// flag that is set when we have reached the end of the file
	int nLineEnd = 0;		// holds the location of the end of the line

	CDelimitedTextParser TextParser;
	CTable TableLine;

	int nRow;

	TextParser.SetColumnDelimiter (',');
	TextParser.SetTextDelimiter ('\"');
	TextParser.StripTextDelimiters (true);

	int iterator; // iterator

	while (!bEndOfFile)
	{
		lpTemp = strTemp.GetBuffer (256);
		bReadStatus = ::ReadFile (hFile, lpTemp, 256, &dwBytesRead, NULL);
		strTemp.ReleaseBuffer (dwBytesRead);
		if (!bReadStatus)
		{
			// TODO: error checking and reporting
			::CloseHandle (hFile);
			return 0;
		}
		if (!dwBytesRead) bEndOfFile = true;	// ReadFile returns TRUE and sets dwBytesRead to 0 at the EOF

		strBuffer += strTemp;
		strTemp.Empty ();

		nLineEnd = strBuffer.Find ('\n', 0);	// find the newline marker

		// Check if we are at the end of the file, can't find a newline marker and there is still
		// text in the buffer.  If so, set the end of the line to the end of the buffer.
		if (bEndOfFile && nLineEnd == -1 && !strBuffer.IsEmpty ())
			nLineEnd = strBuffer.GetLength () + 1;

		while (nLineEnd != -1)
		{
			strLine = strBuffer.Left (nLineEnd - 1);
			strBuffer = strBuffer.Right (strBuffer.GetLength () - (nLineEnd + 1));

			if (!strLine.IsEmpty ()) // ignore empty lines
			{
				TextParser.ParseLine (strLine, &TableLine);

				nRow = m_pTable->AddRow ();

				if (m_pTable->GetColumnCount () < TableLine.GetRowCount ())
				{
					m_pTable->AddColumn (TableLine.GetRowCount () - m_pTable->GetColumnCount ());
				}

				for (iterator = 0; iterator < TableLine.GetRowCount (); iterator++)
				{
					m_pTable->SetCell (nRow, iterator, TableLine.GetCell (iterator, 0));
				}
			}

			nLineEnd = strBuffer.Find ('\n', 0);	// find the newline marker

			// Check if we are at the end of the file, can't find a newline marker and there is still
			// text in the buffer.  If so, set the end of the line to the end of the buffer.
			if (bEndOfFile && nLineEnd == -1 && !strBuffer.IsEmpty ())
				nLineEnd = strBuffer.GetLength () + 1;
		}
	}

	if (!::CloseHandle (hFile)) return 0;

	return 1;
}

const int CDelimitedTextFile::SaveFile (const CString *strFileName)
{
	// TODO: Fix this! CREATE_ALWAYS and OPEN_ALWAYS do not work with existing files for some reason
	HANDLE hFile = ::CreateFile (*strFileName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE) return 0;

	CString strLine;
	int nLineLength;
	DWORD dwBytesWritten;

	for (int nRow = 0; nRow < m_pTable->GetRowCount (); nRow++)
	{
		for (int nColumn = 0; nColumn < m_pTable->GetColumnCount (); nColumn++)
		{
			if (nColumn != 0) strLine += ',';
			if (m_pTable->GetCell (nRow, nColumn)->GetDataType () == CTableCell::String)
			{
				if (!m_pTable->GetCell (nRow, nColumn)->GetDataString ().IsEmpty ())
				{
					strLine += '\"';
					strLine += m_pTable->GetCell (nRow, nColumn)->GetDataString ();
					strLine += '\"';
				}
			}
			else
			{
				strLine += m_pTable->GetCell (nRow, nColumn)->GetDataString ();
			}
		}

		strLine += "\x0D\x0A";

		nLineLength = strLine.GetLength ();
		if (!WriteFile (hFile, strLine, nLineLength, &dwBytesWritten, NULL)) return 0;

		if (dwBytesWritten != (unsigned int) nLineLength) return 0;

		strLine.Empty ();
	}

	if (!::CloseHandle (hFile)) return 0;

	return 1;
}

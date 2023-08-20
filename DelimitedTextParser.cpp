// DelimitedTextParser.cpp: implementation of the CDelimitedTextParser class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "DelimitedTextParser.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CDelimitedTextParser::CDelimitedTextParser()
{
	SetColumnDelimiter (',');
	SetTextDelimiter ('\"');
	StripTextDelimiters (true);
}

CDelimitedTextParser::~CDelimitedTextParser()
{

}

void CDelimitedTextParser::SetColumnDelimiter (const char cColumnDelimiter)
{
	m_cColumnDelimiter = cColumnDelimiter;
}

void CDelimitedTextParser::SetTextDelimiter (const char cTextDelimiter)
{
	SetTextStartDelimiter (cTextDelimiter);
	SetTextEndDelimiter (cTextDelimiter);
}

void CDelimitedTextParser::SetTextStartDelimiter (const char cTextStartDelimiter)
{
	m_cTextStartDelimiter = cTextStartDelimiter;
}

void CDelimitedTextParser::SetTextEndDelimiter (const char cTextEndDelimiter)
{
	m_cTextEndDelimiter = cTextEndDelimiter;
}

void CDelimitedTextParser::StripTextDelimiters (const bool bStripTextDelimiters)
{
	m_bStripTextDelimiters = bStripTextDelimiters;
}

void CDelimitedTextParser::ParseLine (const CString strText, CTable *pTable)
{
	if (strText.IsEmpty ())
	{
		pTable->DeleteAll ();
		return;
	}

	pTable->DeleteAll ();
	pTable->AddColumn ();

	CString strTemp;
	CTableCell TableCell;

	bool bIsText = false;
	int nTextStart = 0;
	int nTextEnd = 0;

	int nColumnStart = 0;
	int nColumnEnd = strText.Find (m_cColumnDelimiter, nColumnStart + 1);

	while (nColumnEnd != -1)
	{
		// find the start and end of any upcoming text
		nTextStart = strText.Find (m_cTextStartDelimiter, nColumnStart);
		nTextEnd = strText.Find (m_cTextEndDelimiter, nTextStart + 1);

		// if the text is valid
		if (nTextStart != -1 && nTextEnd != -1 && nTextStart < nTextEnd)
		{
			// if the text is part of the current column
			if (nTextStart < nColumnEnd)
			{
				// then the column ends at the first column delimiter past the text end delimiter
				nColumnEnd = strText.Find (m_cColumnDelimiter, nTextEnd);

				bIsText = true;
			}
		}

		if (bIsText)
		{
			strTemp = strText.Mid (nTextStart, nTextEnd - nTextStart);
		}
		else
		{
			strTemp = strText.Mid (nColumnStart, nColumnEnd - nColumnStart);
		}

		if (m_bStripTextDelimiters)
		{
			strTemp.TrimLeft (m_cTextStartDelimiter);
			strTemp.TrimRight (m_cTextEndDelimiter);
		}

		if (bIsText)
		{
			TableCell.SetData (&strTemp);
		}
		else
		{
			TableCell.SetDataAutoType (&strTemp);
		}

		pTable->SetCell (pTable->AddRow (), 0, &TableCell);

		bIsText = false;
		nColumnStart = nColumnEnd + 1; // get rid of the column delimiter
		nColumnEnd = strText.Find (m_cColumnDelimiter, nColumnStart);
	}

	nColumnEnd = strText.GetLength ();

	strTemp = strText.Mid (nColumnStart, nColumnEnd - nColumnStart);

	if (m_bStripTextDelimiters)
	{
		strTemp.TrimLeft (m_cTextStartDelimiter);
		strTemp.TrimRight (m_cTextEndDelimiter);
	}

	TableCell.SetDataAutoType (&strTemp);
	pTable->SetCell (pTable->AddRow (), 0, &TableCell);
}


// DelimitedTextParser.h: interface for the CDelimitedTextParser class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DELIMITEDTEXTPARSER_H__55758F4A_966B_4436_83A9_2B11308909A6__INCLUDED_)
#define AFX_DELIMITEDTEXTPARSER_H__55758F4A_966B_4436_83A9_2B11308909A6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Table.h"

class CDelimitedTextParser  
{
	public:
		CDelimitedTextParser ();
		virtual ~CDelimitedTextParser ();

		void SetColumnDelimiter (const char);
		void SetTextDelimiter (const char);
		void SetTextStartDelimiter (const char);
		void SetTextEndDelimiter (const char);
		void StripTextDelimiters (const bool);

		void ParseLine (const CString, CTable *);

	protected:
		const CTableCell::E_CELL_DATA_TYPE DetermineDataType (const CString *) const;

		char m_cColumnDelimiter;
		char m_cTextStartDelimiter;
		char m_cTextEndDelimiter;
		bool m_bStripTextDelimiters;

};

#endif // !defined(AFX_DELIMITEDTEXTPARSER_H__55758F4A_966B_4436_83A9_2B11308909A6__INCLUDED_)

// DelimitedTextFile.h: interface for the CDelimitedTextFile class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_DELIMITEDTEXTFILE_H__6F1BE960_E7E3_47E6_8D35_B64BF55CED57__INCLUDED_)
#define AFX_DELIMITEDTEXTFILE_H__6F1BE960_E7E3_47E6_8D35_B64BF55CED57__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Table.h"

class CDelimitedTextFile  
{
	public:
		CDelimitedTextFile (CTable * = NULL);
		virtual ~CDelimitedTextFile ();

		void SetTable (CTable *);

		const int LoadFile (const CString *);
		const int SaveFile (const CString *);

	protected:
		CTable *m_pTable;

};

#endif // !defined(AFX_DELIMITEDTEXTFILE_H__6F1BE960_E7E3_47E6_8D35_B64BF55CED57__INCLUDED_)

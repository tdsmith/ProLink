// Table.h: interface for the CTable class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLE_H__E4D617E0_12F8_4302_8DE8_4538F4127F72__INCLUDED_)
#define AFX_TABLE_H__E4D617E0_12F8_4302_8DE8_4538F4127F72__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "TableCell.h"

class CTable  
{
	public:
		CTable ();
		virtual ~CTable ();

		const int GetRowCount (void);
		const int GetColumnCount (void);

		const int AddRow (const int = 1);
		const int AddColumn (const int = 1);

		const CTableCell *GetCell (const int, const int);
		void SetCell (const int, const int, const CTableCell *);

		void DeleteAll (void);

	protected:
		const int GetCellIndex (const int, const int);
		const int GetCellIndex (const int, const int, const int, const int);
		const int GetSpaceRequired (const int, const int);

		void FreeMemory (void);

		CTableCell **m_ppCells;

		int m_nRowCount;
		int m_nColumnCount;

};

#endif // !defined(AFX_TABLE_H__E4D617E0_12F8_4302_8DE8_4538F4127F72__INCLUDED_)

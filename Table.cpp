// Table.cpp: implementation of the CTable class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Table.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTable::CTable ()
{
	m_ppCells = NULL;
	m_nRowCount = 0;
	m_nColumnCount = 0;
}

CTable::~CTable ()
{
	FreeMemory ();
}

const int CTable::GetRowCount (void)
{
	return m_nRowCount;
}

const int CTable::GetColumnCount (void)
{
	return m_nColumnCount;
}

const int CTable::AddRow (const int nAddRowCount)
{
	int nNewRowCount = m_nRowCount + nAddRowCount;
	int nNewColumnCount = m_nColumnCount;

	// get the amount of memory required by the table
	int nSpaceRequired = GetSpaceRequired (nNewRowCount, nNewColumnCount);

	// reallocate memory for the table
	CTableCell **ppNewData = (CTableCell **) realloc (m_ppCells, nSpaceRequired);

	if (ppNewData == NULL) // the memory allocation failed
	{
		return -1;
	}

	// create the CTableCell objects for all the new cells
	int nIndex;

	for (int nRow = m_nRowCount; nRow < nNewRowCount; nRow++)
	{
		for (int nColumn = 0; nColumn < nNewColumnCount; nColumn++)
		{
			nIndex = GetCellIndex (nRow, nColumn, nNewRowCount, nNewColumnCount);

			ppNewData [nIndex] = new CTableCell;
		}
	}

	m_nRowCount = nNewRowCount;
	m_nColumnCount = nNewColumnCount;
	m_ppCells = ppNewData;

	return m_nRowCount - 1; // return the index to the last row, subtract one because it is zero based
}

const int CTable::AddColumn (const int nAddColumnCount)
{
	int nNewRowCount = m_nRowCount;
	int nNewColumnCount = m_nColumnCount + nAddColumnCount;

	// get the amount of memory required by the new table
	int nSpaceRequired = GetSpaceRequired (nNewRowCount, nNewColumnCount);

	// allocate memory for the new table
	CTableCell **ppNewData = (CTableCell **) malloc (nSpaceRequired);

	if (ppNewData == NULL) // the memory allocation failed
	{
		return -1;
	}

	if (m_ppCells != NULL) // if the table is empty, we don't need to copy anything over
	{
		// copy the old cells to the new table
		int nOldIndex;
		int nNewIndex;

		for (int nRow = 0; nRow < m_nRowCount; nRow++)
		{
			for (int nColumn = 0; nColumn < m_nColumnCount; nColumn++)
			{
				nOldIndex = GetCellIndex (nRow, nColumn);
				nNewIndex = GetCellIndex (nRow, nColumn, nNewRowCount, nNewColumnCount);

				ppNewData [nNewIndex] = m_ppCells [nOldIndex];
			}
		}
	}

	// create the CTableCell objects for all the new cells
	int nIndex;

	for (int nRow = 0; nRow < nNewRowCount; nRow++)
	{
		for (int nColumn = m_nColumnCount; nColumn < nNewColumnCount; nColumn++)
		{
			nIndex = GetCellIndex (nRow, nColumn, nNewRowCount, nNewColumnCount);

			ppNewData [nIndex] = new CTableCell;
		}
	}

	// free the memory for the old table
	FreeMemory ();

	m_nRowCount = nNewRowCount;
	m_nColumnCount = nNewColumnCount;
	m_ppCells = ppNewData;

	return m_nRowCount - 1; // return the index to the last column, subtract one because it is zero based
}

const CTableCell *CTable::GetCell (const int nRow, const int nColumn)
{
	if (m_ppCells == NULL) return NULL;

	int nIndex = GetCellIndex (nRow, nColumn);

	return m_ppCells [nIndex];
}

void CTable::SetCell (const int nRow, const int nColumn, const CTableCell *pCell)
{
	if (m_ppCells == NULL) return;

	int nIndex = GetCellIndex (nRow, nColumn);

	if (nIndex == -1) return; // cell location is out of range

	m_ppCells [nIndex]->Copy (pCell);
}

void CTable::DeleteAll (void)
{
	FreeMemory ();

	m_ppCells = NULL;
	m_nRowCount = 0;
	m_nColumnCount = 0;
}

const int CTable::GetCellIndex (const int nRow, const int nColumn)
{
	return GetCellIndex (nRow, nColumn, m_nRowCount, m_nColumnCount);
}

const int CTable::GetCellIndex (const int nRow, const int nColumn, const int nRowCount, const int nColumnCount)
{
	if ((nRow > nRowCount - 1) || (nColumn > nColumnCount - 1) || (nRow < 0) || (nColumn < 0)) return -1;

	return (nRow * nColumnCount) + nColumn;
}

const int CTable::GetSpaceRequired (const int nRows, const int nColumns)
{
	return nRows * nColumns * sizeof (CTableCell *);
}

void CTable::FreeMemory (void)
{
	int nIndex;

	for (int nRow = 0; nRow < m_nRowCount; nRow++)
	{
		for (int nColumn = 0; nColumn < m_nColumnCount; nColumn++)
		{
			nIndex = GetCellIndex (nRow, nColumn);

			delete m_ppCells [nIndex];
		}
	}

	free (m_ppCells);
}

// TableCell.h: interface for the CTableCell class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TABLECELL_H__89C28485_4A80_4CCF_A69A_61676200E7CD__INCLUDED_)
#define AFX_TABLECELL_H__89C28485_4A80_4CCF_A69A_61676200E7CD__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class CTableCell  
{
	public:
		enum E_CELL_DATA_TYPE
		{
			Void,
			Boolean,
			Integer,
			Double,
			String,
		};

	public:
		CTableCell ();
		CTableCell (const bool);
		CTableCell (const int);
		CTableCell (const double);
		CTableCell (const CString, bool = false);
		CTableCell (const char *, bool = false);

		virtual ~CTableCell ();

		const E_CELL_DATA_TYPE GetDataType (void) const;

		const void *GetData (void) const;
		void GetData (const void *) const;
		void GetData (const bool *) const;
		void GetData (const int *) const;
		void GetData (const double *) const;
		void GetData (const CString *) const;

		const bool GetDataBoolean (void) const;
		const int GetDataInteger (void) const;
		const double GetDataDouble (void) const;
		const CString GetDataString (void) const;

		const E_CELL_DATA_TYPE SetDataAutoType (const CString *);

		void SetData (const bool);
		void SetData (const int);
		void SetData (const double);
		void SetData (const CString *);

		void Copy (const CTableCell *);

	protected:
		void FreeMemory (void);

		E_CELL_DATA_TYPE m_DataType;
		void *m_pData;

};

#endif // !defined(AFX_TABLECELL_H__89C28485_4A80_4CCF_A69A_61676200E7CD__INCLUDED_)

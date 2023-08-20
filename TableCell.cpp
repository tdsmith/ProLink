// TableCell.cpp: implementation of the CTableCell class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "TableCell.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CTableCell::CTableCell ()
{
	m_pData = NULL;
	m_DataType = Void;
}

CTableCell::CTableCell (const bool bData)
{
	m_pData = NULL;
	m_DataType = Void;

	SetData (bData);
}

CTableCell::CTableCell (const int nData)
{
	m_pData = NULL;
	m_DataType = Void;

	SetData (nData);
}

CTableCell::CTableCell (const double dfData)
{
	m_pData = NULL;
	m_DataType = Void;

	SetData (dfData);
}

CTableCell::CTableCell (const CString strData, bool bAutoType)
{
	m_pData = NULL;
	m_DataType = Void;

	if (bAutoType)
	{
		SetDataAutoType (&strData);
	}
	else
	{
		SetData (&strData);
	}
}

CTableCell::CTableCell (const char *pcData, bool bAutoType)
{
	m_pData = NULL;
	m_DataType = Void;

	CString strData (pcData);

	if (bAutoType)
	{
		SetDataAutoType (&strData);
	}
	else
	{
		SetData (&strData);
	}
}

CTableCell::~CTableCell ()
{
	FreeMemory ();
}

const CTableCell::E_CELL_DATA_TYPE CTableCell::GetDataType (void) const
{
	return m_DataType;
}

const void *CTableCell::GetData (void) const
{
	return m_pData;
}

void CTableCell::GetData (const void *pData) const
{
	pData = m_pData;
}

void CTableCell::GetData (const bool *pData) const
{
	pData = (bool *) m_pData;
}

void CTableCell::GetData (const int *pData) const
{
	pData = (int *) m_pData;
}

void CTableCell::GetData (const double *pData) const
{
	pData = (double *) m_pData;
}

void CTableCell::GetData (const CString *pData) const
{
	pData = (CString *) m_pData;
}

const bool CTableCell::GetDataBoolean (void) const
{
	if (m_DataType != Boolean) return false;

	return *(bool *) m_pData;
}

const int CTableCell::GetDataInteger (void) const
{
	if (m_DataType != Integer) return -1;

	return *(int *) m_pData;
}

const double CTableCell::GetDataDouble (void) const
{
	if (m_DataType != Double) return -1;

	return *(double *) m_pData;
}

const CString CTableCell::GetDataString (void) const
{
	CString strTemp;

	switch (m_DataType)
	{
		case Boolean:
			if (GetDataBoolean ())
			{
				strTemp = _T("X");
			}
			else
			{
				strTemp = _T(" ");
			}
			break;

		case Integer:
			strTemp.Format ("%d", GetDataInteger ());
			break;

		case Double:
			strTemp.Format ("%f", GetDataDouble ());
			break;

		case String:
			strTemp = * (CString *) m_pData;
			break;
	}

	return strTemp;
}

const CTableCell::E_CELL_DATA_TYPE CTableCell::SetDataAutoType (const CString *pstrData)
{
	CString strTemp;
	strTemp = *pstrData;
	strTemp.TrimLeft ();
	strTemp.TrimRight ();

	if (strTemp.IsEmpty ())
	{
		FreeMemory ();
		return Void;
	}

	if (!strTemp.CompareNoCase (_T("X")) || !strTemp.CompareNoCase (_T("True")))
	{
		SetData (true);
		return Boolean;
	}
	else if (!strTemp.CompareNoCase (_T(" ")) || !strTemp.CompareNoCase (_T("False")))
	{
		SetData (false);
		return Boolean;
	}

	char cTemp;
	int bNonNumeric = false;
	int bDecimal = false;

	for (int x = 0; x < strTemp.GetLength (); x++)
	{
		cTemp = strTemp.GetAt (x);

		if ((cTemp >= 0x30) && (cTemp <= 0x39)) // numbers 0-9
		{
			// numeric
		}
		else if ((cTemp == 0x2b) || (cTemp == 0x2d))	// plus or minus sign
		{
			// plus or minus sign only valid at the beginning of a number
			if (x != 0)
			{
				bNonNumeric = true;
			}
		}
		else if (cTemp == 0x2e) // decimal point
		{
			// check if the decimal flag is already set
			if (bDecimal)
			{
				bNonNumeric = true;	// it's not a number if there are two decimals
			}
			else
			{
				bDecimal = true;
			}
		}
		else
		{
			bNonNumeric = true;
			break;
		}
	}

	if (bNonNumeric)
	{
		SetData (&strTemp);
		return String;
	}
	
	if (bDecimal)
	{
		double dfData = atof (strTemp);
		SetData (dfData);
		return Double;
	}

	int nData = atoi (strTemp);
	SetData (nData);
	return Integer;
}

void CTableCell::SetData (const bool bData)
{
	FreeMemory ();

	m_DataType = Boolean;
	m_pData = new bool;
	*(bool *) m_pData = bData;
}

void CTableCell::SetData (const int nData)
{
	FreeMemory ();

	m_DataType = Integer;
	m_pData = new int;
	*(int *) m_pData = nData;
}

void CTableCell::SetData (const double dfData)
{
	FreeMemory ();

	m_DataType = Double;
	m_pData = new double;
	*(double *) m_pData = dfData;
}

void CTableCell::SetData (const CString *pstrData)
{
	FreeMemory ();

	m_DataType = String;
	m_pData = new CString;

	*(CString *) m_pData = *pstrData;
}

void CTableCell::Copy (const CTableCell *pCell)
{
	if (pCell == NULL)
	{
		FreeMemory ();
		return;
	}

	E_CELL_DATA_TYPE DataType = pCell->GetDataType ();

	switch (DataType)
	{
		case Boolean:
			SetData (pCell->GetDataBoolean ());
			break;

		case Integer:
			SetData (pCell->GetDataInteger ());
			break;

		case Double:
			SetData (pCell->GetDataDouble ());
			break;

		case String:
			CString strDataString = pCell->GetDataString ();
			SetData (&strDataString);
			break;

	}
}

void CTableCell::FreeMemory (void)
{
	switch (m_DataType)
	{
		case (Boolean):
			delete (bool *) m_pData;
			break;

		case (Integer):
			delete (int *) m_pData;
			break;

		case (Double):
			delete (double *) m_pData;
			break;

		case (String):
			delete (CString *) m_pData;
			break;

	}

	m_pData = NULL;
	m_DataType = Void;
}


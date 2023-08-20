#include "StdAfx.h"
#include "rlGre1DataFrame.h"

#include "rlGre1Module.h"

rlGre1DataFrame::rlGre1DataFrame (const BYTE cCommand, const BYTE cCommandParameter, const BYTE *pcData)
{
	m_pcData = new BYTE [250];	// this must be initialized before CalculateMessageLength and CalculateChecksum are run
	m_pcData [0] = '\0';		// null terminate the beginning

	m_cHeaderMarker = GRE1_FRAME_HEADERMARKER;

	m_cMessageLength = 0;
	m_cChecksum = 0;

	SetCommand (cCommand, cCommandParameter);

	if (pcData != NULL)
	{
		SetData (pcData);
	}
}

rlGre1DataFrame::~rlGre1DataFrame (void)
{
	delete m_pcData;
}

const BYTE rlGre1DataFrame::GetCommand (void) const
{
	return m_cCommand;
}

const BYTE rlGre1DataFrame::GetCommandParameter (void) const
{
	return m_cCommandParameter;
}

void rlGre1DataFrame::SetCommand (const BYTE cCommand, const BYTE cCommandParameter)
{
	m_cCommand = cCommand;
	m_cCommandParameter = cCommandParameter;

	CalculateMessageLength ();
	CalculateChecksum ();
}

void rlGre1DataFrame::SetCommand (const BYTE cCommand)
{
	m_cCommand = cCommand;

	CalculateMessageLength ();
	CalculateChecksum ();
}

void rlGre1DataFrame::SetCommandParameter (const BYTE cCommandParameter)
{
	m_cCommandParameter = cCommandParameter;

	CalculateMessageLength ();
	CalculateChecksum ();
}

const BYTE *rlGre1DataFrame::GetData (void) const
{
	return m_pcData;
}

void rlGre1DataFrame::SetData (const BYTE *pcData)
{
	int i;

	for (i = 0; (i < 250) && (pcData [i] != 0); i++)
	{
		m_pcData [i] = pcData [i];
	}

	if (i > 249)	// make sure we don't put the null in no mans land
	{
		ASSERT (FALSE);
		i = 249;
	}

	m_pcData [i] = 0;	// null terminated

	CalculateMessageLength ();
	CalculateChecksum ();
}

const BYTE rlGre1DataFrame::GetRawDataFrame (BYTE *pcRawFrame) const
{
	ASSERT (pcRawFrame != NULL);

	BYTE x = 0;

	pcRawFrame [x] = m_cHeaderMarker;		x++;
	pcRawFrame [x] = m_cMessageLength;		x++;
	pcRawFrame [x] = m_cCommand;			x++;
	pcRawFrame [x] = m_cCommandParameter;	x++;

	for (int i = 0; (i < 250) && (m_pcData [i] != 0); i++)
	{
		pcRawFrame [x] = m_pcData [i];		x++;
	}

	// there must be something here, so put null
	if (i == 0) { pcRawFrame [x] = '\0'; x++; };

	pcRawFrame [x] = m_cChecksum;			x++;

	return x;
}

void rlGre1DataFrame::CalculateChecksum (void)
{
	BYTE cChecksum = 0;

	cChecksum = static_cast <BYTE> (cChecksum + m_cMessageLength);
	cChecksum = static_cast <BYTE> (cChecksum + m_cCommand);
	cChecksum = static_cast <BYTE> (cChecksum + m_cCommandParameter);

	for (int i = 0; (i < 250) && (m_pcData [i] != 0); i++)
	{
		cChecksum = static_cast <BYTE> (cChecksum + m_pcData [i]);
	}

	cChecksum = -cChecksum;	// two's complement

	m_cChecksum = cChecksum;
}

void rlGre1DataFrame::CalculateMessageLength (void)
{
	// Count m_cMessageLength, m_cCommand, m_cCommandParameter and m_pcData.
	// Do not count m_cHeaderMarker and m_cChecksum.

	BYTE i;

	for (i = 0; (i < 250) && (m_pcData [i] != 0); i++)
	{
		// just count
	}

	// data portion can't be empty
	if (i == 0) i++;

	m_cMessageLength = 3 + i;
}

#pragma once

#include "rlModule.h"
#include "rlGre1Link.h"
#include "rlGre1Memory.h"

class rlGre1Module : public rlModule
{
	public:
		rlGre1Module (void);
		virtual ~rlGre1Module (void);

		virtual HRESULT GetModuleIdentifier (LPTSTR *);

		virtual HRESULT GetName(LPTSTR *plpName);
		virtual HRESULT GetDescription(LPTSTR *plpDescription);

		virtual HRESULT ShowPropertiesDlg (void);

		virtual HRESULT GetLink (rlGre1Link **);
		virtual HRESULT GetMemory (rlMemory **);

		bool ShowTransferInstructionsDlg (void);

	protected:
		rlGre1Link *m_pGre1Link;
		rlGre1Memory *m_pMemory;

		bool m_bShowTransferInstructions;

};

#define GRE1_FRAME_HEADERMARKER					0x81

#define GRE1_COMMAND_STARTCOMMUNICATIONS		0x01
#define GRE1_COMMAND_ENDCOMMUNICATIONS			0x02

#define GRE1_COMMAND_CHANNELDATA				0x10
#define GRE1_COMMAND_CHANNELDATA_MULTI			0x11
#define GRE1_COMMAND_CHANNELDATA_LOWEST			0x12

#define GRE1_COMMAND_SCANBANK					0x20
#define GRE1_COMMAND_SCANBANK_MULTI				0x21
//#define GRE1_COMMAND_IDBANK					0x22
//#define GRE1_COMMAND_IDBANK_MULTI				0x23
//#define GRE1_COMMAND_IDBANK					0x24
//#define GRE1_COMMAND_IDBANK_MULTI				0x25

#define GRE1_COMMAND_DIRECTSEARCHDATA			0x30

#define GRE1_COMMAND_LIMITSEARCHDATA			0x32
#define GRE1_COMMAND_LIMITSEARCHDATA_MULTI		0x33

#define GRE1_COMMAND_PRIORITYDATA1				0x41
#define GRE1_COMMAND_PRIORITYDATA2				0x42
#define GRE1_COMMAND_PRIORITYDATA3				0x43
//#define GRE1_COMMAND_PRIORITYDATA3			0x44
//#define GRE1_COMMAND_PRIORITYDATA3_MULTI		0x45

#define GRE1_COMMAND_SCANNERMODEDATA			0x50

#define GRE1_COMMAND_FREQUENCYSKIPDATA			0x60
#define GRE1_COMMAND_FREQUENCYSKIPDATA_MULTI	0x61

#define GRE1_COMMAND_CLEARMEMORY				0x70

#pragma once

#include "rlMemory.h"
#include "rlMemoryLayout.h"

class rlMemory;

class rlModule
{
	public:
		rlModule (void);
		virtual ~rlModule (void);

		virtual HRESULT GetModuleIdentifier (LPTSTR *);

		virtual HRESULT GetName (LPTSTR *);
		virtual HRESULT GetDescription (LPTSTR *);

		virtual HRESULT GetMemoryLayout (rlMemoryLayout **);

		virtual HRESULT ShowPropertiesDlg (void);

		virtual HRESULT GetMemory (rlMemory **);

	protected:
		rlMemoryLayout m_MemoryLayout;

};

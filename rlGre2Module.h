#pragma once

#include "rlModule.h"
#include "rlGre2Memory.h"
#include "rlGre2Link.h"

class rlGre2Module : public rlModule
{
	public:
		rlGre2Module (void);
		virtual ~rlGre2Module (void);

		virtual HRESULT GetModuleIdentifier (LPTSTR *);

		HRESULT GetName (LPTSTR *);
		HRESULT GetDescription (LPTSTR *);

		virtual HRESULT ShowPropertiesDlg (void);

		virtual HRESULT GetLink (rlGre2Link **);
		virtual HRESULT GetMemory (rlMemory **);

	protected:
		rlGre2Link *m_pGre2Link;
		rlGre2Memory *m_pMemory;

};

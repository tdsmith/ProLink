#pragma once
#include "rlmodule.h"

class rlGre3Module : public rlModule
{
	public:
		rlGre3Module (void);
		virtual ~rlGre3Module (void);

		virtual HRESULT GetModuleIdentifier (LPTSTR *);

		HRESULT GetName (LPTSTR *);
		HRESULT GetDescription (LPTSTR *);

};

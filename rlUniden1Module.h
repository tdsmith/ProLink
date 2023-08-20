#pragma once
#include "rlmodule.h"

class rlUniden1Module : public rlModule
{
	public:
		rlUniden1Module (void);
		virtual ~rlUniden1Module (void);

		virtual HRESULT GetModuleIdentifier (LPTSTR *);

		virtual HRESULT GetName (LPTSTR *);
		virtual HRESULT GetDescription (LPTSTR *);

};

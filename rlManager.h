#pragma once

#include "rlModule.h"

class rlManager
{
	public:
		rlManager(void);
		~rlManager(void);

		HRESULT GetModuleCount (int *);
		HRESULT GetModule (const int nModuleIndex, rlModule **);
		HRESULT GetDefaultModuleIndex (int *);
		HRESULT GetDefaultModule (rlModule **);
		HRESULT SetDefaultModule (const int);

		HRESULT ReleaseModule (rlModule *);

	private:

};

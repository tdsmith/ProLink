#include "StdAfx.h"
#include "rlManager.h"

#include "rlGre1Module.h"
#include "rlGre2Module.h"
#include "rlGre3Module.h"
#include "rlUniden1Module.h"

rlManager::rlManager(void)
{
}

rlManager::~rlManager(void)
{
}

HRESULT rlManager::GetModuleCount (int *pnModuleCount)
{
	*pnModuleCount = 2;

	return S_OK;
}

HRESULT rlManager::GetModule (const int nModuleIndex, rlModule **ppModule)
{
	switch (nModuleIndex)
	{
		case (0):
			*ppModule = DEBUG_NEW rlGre1Module;
			break;
		case (1):
			*ppModule = DEBUG_NEW rlGre2Module;
			break;
		/*
		case (2):
			*ppModule = DEBUG_NEW rlGre3Module;
			break;
		case (3):
			*ppModule = DEBUG_NEW rlUniden1Module;
			break;
		*/
		default:
			return E_INVALIDARG;
	}
	return S_OK;
}

HRESULT rlManager::GetDefaultModuleIndex (int *pnModuleIndex)
{
	CString strDefaultModule = AfxGetApp ()->GetProfileString (_T("RadioLink"), _T("Default Module"));

	int nDefaultModuleIndex = 0;

	if (!strDefaultModule.IsEmpty ())
	{
		int nModuleCount;
		GetModuleCount (&nModuleCount);

		rlModule *pModule;

		LPTSTR lpModuleIdentifier;

		for (int x = 0; x <  nModuleCount; x++)
		{
			GetModule (x, &pModule);
			pModule->GetModuleIdentifier (&lpModuleIdentifier);
			ReleaseModule (pModule);

			if (strcmp (strDefaultModule, lpModuleIdentifier) == 0)
			{
				nDefaultModuleIndex = x;
				break;
			}
		}
	}

	*pnModuleIndex = nDefaultModuleIndex;

	return S_OK;
}

HRESULT rlManager::GetDefaultModule (rlModule **ppModule)
{
	int nIndex;
	GetDefaultModuleIndex (&nIndex);

	return GetModule (nIndex, ppModule);
}

HRESULT rlManager::SetDefaultModule (const int nModuleIndex)
{
	rlModule *pModule;
	GetModule (nModuleIndex, &pModule);

	LPTSTR lpIdentifier;
	pModule->GetModuleIdentifier (&lpIdentifier);

	ReleaseModule (pModule);

	AfxGetApp ()->WriteProfileString (_T("RadioLink"), _T("Default Module"), lpIdentifier);

	return S_OK;
}

HRESULT rlManager::ReleaseModule (rlModule *pModule)
{
	delete pModule;

	return S_OK;
}

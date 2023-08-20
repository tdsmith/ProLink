#include "StdAfx.h"
#include "rluniden1module.h"

rlUniden1Module::rlUniden1Module (void)
{
}

rlUniden1Module::~rlUniden1Module (void)
{
}

HRESULT rlUniden1Module::GetModuleIdentifier (LPTSTR *plpIndentifier)
{
	*plpIndentifier = _T("GCS-Uniden1");
	return S_OK;
}

HRESULT rlUniden1Module::GetName(LPTSTR *plpName)
{
	*plpName = _T("Uniden Remote Scanner Protocol Scanners");

	return S_OK;
}

HRESULT rlUniden1Module::GetDescription(LPTSTR *plpDescription)
{
	*plpDescription = _T("This module implements a serial interface to Uniden scanners and RadioShack scanners made by Uniden that use the Uniden Remote Scanner Protocol including the Uniden BC245XLT, BC780XLT, BC895XLT and the Radio Shack Pro-2052.");

	return S_OK;
}


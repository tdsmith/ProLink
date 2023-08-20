#include "StdAfx.h"
#include "rlmodule.h"

rlModule::rlModule(void)
{
}

rlModule::~rlModule(void)
{

}

HRESULT rlModule::GetModuleIdentifier (LPTSTR * /*plpIndentifier*/)
{
	return E_NOTIMPL;
}

HRESULT rlModule::GetName(LPTSTR * /*plpName*/)
{
	return E_NOTIMPL;
}

HRESULT rlModule::GetDescription(LPTSTR * /*plpDescription*/)
{
	return E_NOTIMPL;
}

HRESULT rlModule::GetMemoryLayout (rlMemoryLayout **ppMemoryLayout)
{
	*ppMemoryLayout = &m_MemoryLayout;

	return S_OK;
}

HRESULT rlModule::ShowPropertiesDlg (void)
{
	return E_NOTIMPL;
}

HRESULT rlModule::GetMemory (rlMemory ** /*ppMemory*/)
{
	return E_NOTIMPL;
}

#include "globalvars.h"

bool globalvars::UpdateGlobalvars()
{
	DWORD64 m_DglobalVars = 0;
	if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetGlobalVarsAddress(), m_DglobalVars))
		return false;

	this->address = m_DglobalVars;

	if (!this->GetRealTime())
		return false;
	if (!this->GetFrameCount())
		return false;
	if (!this->GetMaxClients())
		return false;
	if (!this->GetTickCount())
		return false;
	if (!this->GetIntervalPerTick())
		return false;
	if (!this->GetIntervalPerTick2())
		return false;
	if (!this->GetcurrentTime())
		return false;
	if (!this->GetcurrentTime2())
		return false;
	if (!this->GetCurrentNetchan())
		return false;
	if (!this->GetCurrentMap())
		return false;
	if (!this->GetCurrentMapName())
		return false;

	return true;
}

bool globalvars::GetRealTime()
{
	return GetDataAddressWithOffset<float>(this->address, Offset::GlobalVar.RealTime, this->g_fRealTime);
}

bool globalvars::GetFrameCount()
{
	return GetDataAddressWithOffset<int>(this->address, Offset::GlobalVar.FrameCount, this->g_iFrameCount);
}

bool globalvars::GetMaxClients()
{
	return GetDataAddressWithOffset<int>(this->address, Offset::GlobalVar.MaxClients, this->g_iMaxClients);
}

bool globalvars::GetTickCount()
{
	return GetDataAddressWithOffset<int>(this->address, Offset::GlobalVar.TickCount, this->g_iTickCount);
}

bool globalvars::GetIntervalPerTick()
{
	return GetDataAddressWithOffset<float>(this->address, Offset::GlobalVar.IntervalPerTick, this->g_fIntervalPerTick);
}

bool globalvars::GetIntervalPerTick2()
{
	return GetDataAddressWithOffset<float>(this->address, Offset::GlobalVar.IntervalPerTick2, this->g_fIntervalPerTick2);
}

bool globalvars::GetcurrentTime()
{
	return GetDataAddressWithOffset<float>(this->address, Offset::GlobalVar.CurrentTime, this->g_fCurrentTime);
}

bool globalvars::GetcurrentTime2()
{
	return GetDataAddressWithOffset<float>(this->address, Offset::GlobalVar.CurrentTime2, this->g_fCurrentTime2);
}

bool globalvars::GetCurrentNetchan()
{
	return GetDataAddressWithOffset<void*>(this->address, Offset::GlobalVar.CurrentNetchan, this->g_vCurrentNetchan);
}

bool globalvars::GetCurrentMap()
{
	return GetDataAddressWithOffset<char*>(this->address, Offset::GlobalVar.CurrentMap, this->g_cCurrentMap);
}

bool globalvars::GetCurrentMapName()
{
	return GetDataAddressWithOffset<char*>(this->address, Offset::GlobalVar.CurrentMapName, this->g_cCurrentMapName);
}
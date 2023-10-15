#pragma once
#include <Windows.h>
#include "Utils/ProcessManager.hpp"

template <typename T>
inline bool GetDataAddressWithOffset(const DWORD64& Address, DWORD Offset, T& Data)
{
	if (Address == 0)
		return false;

	if (!ProcessMgr.ReadMemory<T>(Address + Offset, Data))
		return false;

	return true;
}
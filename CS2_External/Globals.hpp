#pragma once
#include <Windows.h>
#include "Utils/ProcessManager.hpp"

template <typename T>
inline bool GetDataAddressWithOffset(const uintptr_t& Address, DWORD Offset, T& Data)
{
	if (Address == 0)
		return false;
	return ProcessMgr.ReadMemory<T>(Address + Offset, Data, sizeof(T));

}

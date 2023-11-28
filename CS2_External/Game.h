#pragma once
#include <optional>
#include "Utils/ProcessManager.hpp"
#include "Offsets.h"
#include "View.hpp"

class CGame
{
private:
	struct
	{
		uintptr_t ClientDLL;
		uintptr_t EntityList;
		uintptr_t Matrix;
		uintptr_t ViewAngle;
		uintptr_t EntityListEntry;
		uintptr_t LocalController;
		uintptr_t LocalPawn;
		uintptr_t ForceJump;
		uintptr_t GlobalVars;
	}Address;

public:
	CView View;

public:	

	bool InitAddress();

	uintptr_t GetClientDLLAddress();

	uintptr_t GetEntityListAddress();

	uintptr_t GetMatrixAddress();

	uintptr_t GetViewAngleAddress();

	uintptr_t GetEntityListEntry();

	uintptr_t GetLocalControllerAddress();

	uintptr_t GetLocalPawnAddress();

	uintptr_t GetGlobalVarsAddress();

	bool UpdateEntityListEntry();

	bool SetViewAngle(float Yaw, float Pitch);

	bool SetForceJump(int Value);
};

inline CGame gGame;

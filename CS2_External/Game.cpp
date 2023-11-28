#include "Game.h"

bool CGame::InitAddress()
{
	this->Address.ClientDLL = reinterpret_cast<uintptr_t>(ProcessMgr.GetProcessModuleHandle("client.dll"));
	
	this->Address.EntityList = GetClientDLLAddress() + Offset::EntityList;
	this->Address.Matrix = GetClientDLLAddress() + Offset::Matrix;
	this->Address.ViewAngle = GetClientDLLAddress() + Offset::ViewAngle;
	this->Address.LocalController = GetClientDLLAddress() + Offset::LocalPlayerController;
	this->Address.LocalPawn = GetClientDLLAddress() + Offset::LocalPlayerPawn;
	this->Address.ForceJump = GetClientDLLAddress() + Offset::ForceJump;
	this->Address.GlobalVars = GetClientDLLAddress() + Offset::GlobalVars;

	return this->Address.ClientDLL != 0;
}

uintptr_t CGame::GetClientDLLAddress()
{
	return this->Address.ClientDLL;
}

uintptr_t CGame::GetEntityListAddress()
{
	return this->Address.EntityList;
}

uintptr_t CGame::GetMatrixAddress()
{
	return this->Address.Matrix;
}

uintptr_t CGame::GetViewAngleAddress() 
{
	return this->Address.ViewAngle;
}

uintptr_t CGame::GetEntityListEntry()
{
	return this->Address.EntityListEntry;
}

uintptr_t CGame::GetLocalControllerAddress()
{
	return this->Address.LocalController;
}

uintptr_t CGame::GetLocalPawnAddress()
{
	return this->Address.LocalPawn;
}

uintptr_t CGame::GetGlobalVarsAddress()
{
	return this->Address.GlobalVars;
}

bool CGame::UpdateEntityListEntry()
{
    auto EntityListEntry = ProcessMgr.RAM<uintptr_t>(gGame.GetEntityListAddress());
    if (!EntityListEntry)
		return false;
    auto World = ProcessMgr.RAM<uintptr_t>(EntityListEntry + 0x10);
	if (!World)
		return false;

	this->Address.EntityListEntry = World;

	return this->Address.EntityListEntry != 0;
}

bool CGame::SetViewAngle(float Yaw, float Pitch)
{
	Vec2 Angle{ Pitch,Yaw };
	return ProcessMgr.WPM<Vec2>(this->Address.ViewAngle, Angle);
}

bool CGame::SetForceJump(int value)
{
	return ProcessMgr.WPM<int>(this->Address.ForceJump, value);
}

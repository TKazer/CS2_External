#include "Game.h"

bool CGame::InitAddress()
{
    Address.ClientDLL = reinterpret_cast<DWORD64>(ProcessMgr.GetProcessModuleHandle("client.dll"));
    if (Address.ClientDLL == 0)
        return false;

    DWORD64 clientDLLAddress = GetClientDLLAddress();
    Address.EntityList = clientDLLAddress + Offset::EntityList;
    Address.Matrix = clientDLLAddress + Offset::Matrix;
    Address.ViewAngle = clientDLLAddress + Offset::ViewAngle;
    Address.LocalController = clientDLLAddress + Offset::LocalPlayerController;
    Address.LocalPawn = clientDLLAddress + Offset::LocalPlayerPawn;
    Address.ForceJump = clientDLLAddress + Offset::ForceJump;
    Address.GlobalVars = clientDLLAddress + Offset::GlobalVars;

    return true;
}

DWORD64 CGame::GetClientDLLAddress()
{
    return Address.ClientDLL;
}

DWORD64 CGame::GetEntityListAddress()
{
    return Address.EntityList;
}

DWORD64 CGame::GetMatrixAddress()
{
    return Address.Matrix;
}

DWORD64 CGame::GetViewAngleAddress() 
{
    return Address.ViewAngle;
}

DWORD64 CGame::GetEntityListEntry()
{
    return Address.EntityListEntry;
}

DWORD64 CGame::GetLocalControllerAddress()
{
    return Address.LocalController;
}

DWORD64 CGame::GetLocalPawnAddress()
{
    return Address.LocalPawn;
}

DWORD64 CGame::GetGlobalVarsAddress()
{
    return Address.GlobalVars;
}

bool CGame::UpdateEntityListEntry()
{
    DWORD64 entityListEntry = 0;
    if (!ProcessMgr.ReadMemory<DWORD64>(GetEntityListAddress(), entityListEntry))
        return false;
    if (!ProcessMgr.ReadMemory<DWORD64>(entityListEntry + 0x10, entityListEntry))
        return false;

    Address.EntityListEntry = entityListEntry;

    return true;
}

bool CGame::SetViewAngle(float Yaw, float Pitch)
{
    Vec2 Angle{ Pitch, Yaw };

    return ProcessMgr.WriteMemory<Vec2>(Address.ViewAngle, Angle);
}

bool CGame::SetForceJump(int value)
{
    return ProcessMgr.WriteMemory<int>(Address.ForceJump, value);
}

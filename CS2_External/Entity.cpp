#include "Entity.h"

template <typename T>
bool GetDataAddressWithOffset(const DWORD64& Address, DWORD Offset, T& Data)
{
	if (Address == 0)
		return false;

	if (!ProcessMgr.ReadMemory<T>(Address + Offset, Data))
		return false;

	return true;
}

bool CEntity::Update(const DWORD64& EntityAddress)
{
	if (EntityAddress == 0)
		return false;
	this->EntityAddress = EntityAddress;

	if (!GetPawn())
		return false;
	if (!GetTeamID())
		return false;
	if (!GetIsAlive())
		return false;
	if (!GetHealth())
		return false;
	if (!GetPos())
		return false;
	if (!GetViewAngle())
		return false;
	if (!GetCameraPos())
		return false;
	if (!BoneData.UpdateAllBoneData(EntityPawnAddress))
		return false;

	return true;
}

bool CEntity::GetTeamID()
{
	return GetDataAddressWithOffset<int>(EntityAddress, Offset::Entity.TeamID, this->TeamID);
}

bool CEntity::GetHealth()
{
	return GetDataAddressWithOffset<int>(EntityAddress, Offset::Entity.Health, this->Health);
}

bool CEntity::GetIsAlive()
{
	return GetDataAddressWithOffset<int>(EntityAddress, Offset::Entity.IsAlive, this->AliveStatus);
}

bool CEntity::GetViewAngle()
{
	return GetDataAddressWithOffset<Vec2>(EntityPawnAddress, Offset::Pawn.angEyeAngles, this->ViewAngle);
}

bool CEntity::GetCameraPos()
{
	return GetDataAddressWithOffset<Vec3>(EntityPawnAddress, Offset::Pawn.vecLastClipCameraPos, this->CameraPos);
}

bool CEntity::GetPawn()
{
	if (!GetDataAddressWithOffset<DWORD>(EntityAddress, Offset::Entity.PlayerPawn, this->Pawn))
		return false;

	if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListEntry() + 0x78 * (Pawn & 0x1FF), this->EntityPawnAddress))
		return false;

	return this->EntityPawnAddress != 0;
}

bool CEntity::GetPos()
{
	return GetDataAddressWithOffset<Vec3>(EntityPawnAddress, Offset::Pawn.Pos, this->Pos);
}

bool CEntity::IsAlive()
{
	return this->AliveStatus == 1 && this->Health > 0;
}

bool CEntity::IsInScreen()
{
	return gGame.View.WorldToScreen(this->Pos, this->ScreenPos);
}
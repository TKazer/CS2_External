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

bool CEntity::UpdateController(const DWORD64& PlayerControllerAddress)
{
	if (PlayerControllerAddress == 0)
		return false;
	this->Controller.Address = PlayerControllerAddress;

	if (!this->Controller.GetHealth())
		return false;
	if (!this->Controller.GetIsAlive())
		return false;
	if (!this->Controller.GetTeamID())
		return false;

	this->Pawn.Address = this->Controller.GetPlayerPawnAddress();

	return true;
}

bool CEntity::UpdatePawn(const DWORD64& PlayerPawnAddress)
{
	if (PlayerPawnAddress == 0)
		return false;
	this->Pawn.Address = PlayerPawnAddress;

	if (!this->Pawn.GetCameraPos())
		return false;
	if (!this->Pawn.GetPos())
		return false;
	if (!this->Pawn.GetViewAngle())
		return false;
	if (!this->Pawn.BoneData.UpdateAllBoneData(PlayerPawnAddress))
		return false;

	return true;
}

bool PlayerController::GetTeamID()
{
	return GetDataAddressWithOffset<int>(Address, Offset::Entity.TeamID, this->TeamID);
}

bool PlayerController::GetHealth()
{
	return GetDataAddressWithOffset<int>(Address, Offset::Entity.Health, this->Health);
}

bool PlayerController::GetIsAlive()
{
	return GetDataAddressWithOffset<int>(Address, Offset::Entity.IsAlive, this->AliveStatus);
}

bool PlayerPawn::GetViewAngle()
{
	return GetDataAddressWithOffset<Vec2>(Address, Offset::Pawn.angEyeAngles, this->ViewAngle);
}

bool PlayerPawn::GetCameraPos()
{
	return GetDataAddressWithOffset<Vec3>(Address, Offset::Pawn.vecLastClipCameraPos, this->CameraPos);
}

DWORD64 PlayerController::GetPlayerPawnAddress()
{
	DWORD64 EntityPawnListEntry = 0;
	DWORD64 EntityPawnAddress = 0;

	if (!GetDataAddressWithOffset<DWORD>(Address, Offset::Entity.PlayerPawn, this->Pawn))
		return 0;

	if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListAddress(), EntityPawnListEntry))
		return 0;

	if (!ProcessMgr.ReadMemory<DWORD64>(EntityPawnListEntry + 0x10 + 8 * ((Pawn & 0x7FFF) >> 9), EntityPawnListEntry))
		return 0;

	if (!ProcessMgr.ReadMemory<DWORD64>(EntityPawnListEntry + 0x78 * (Pawn & 0x1FF), EntityPawnAddress))
		return 0;

	return EntityPawnAddress;
}

bool PlayerPawn::GetPos()
{
	return GetDataAddressWithOffset<Vec3>(Address, Offset::Pawn.Pos, this->Pos);
}

bool CEntity::IsAlive()
{
	return this->Controller.AliveStatus == 1 && this->Controller.Health > 0;
}

bool CEntity::IsInScreen()
{
	return gGame.View.WorldToScreen(this->Pawn.Pos, this->Pawn.ScreenPos);
}

CBone CEntity::GetBone() const
{
	if (this->Pawn.Address == 0)
		return CBone{};
	return this->Pawn.BoneData;
}
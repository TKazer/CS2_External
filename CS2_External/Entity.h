#pragma once
#include "Game.h"
#include "View.hpp"
#include "Bone.h"
#include "Globals.hpp"

struct C_UTL_VECTOR
{
	uintptr_t Count = 0;
	uintptr_t Data = 0;
};

class PlayerController
{
public:
	uintptr_t Address = 0;
	int TeamID = 0;
	int Health = 0;
	int AliveStatus = 0;
	DWORD Pawn = 0;
	std::string PlayerName;
public:
	bool GetTeamID();
	bool GetHealth();
	bool GetIsAlive();
	bool GetPlayerName();
	uintptr_t GetPlayerPawnAddress();
};

class PlayerPawn
{
public:
	enum class Flags
	{
		NONE,
		IN_AIR = 1 << 0
	};

	uintptr_t Address = 0;
	CBone BoneData;
	Vec2 ViewAngle;
	Vec3 Pos;
	Vec2 ScreenPos;
	Vec3 CameraPos;
	std::string WeaponName;
	DWORD ShotsFired;
	Vec2 AimPunchAngle;
	C_UTL_VECTOR AimPunchCache;
	int Health;
    int Armor;
	int TeamID;
	int Fov;
	uint32_t bSpottedByMask;
	bool Spotted;
	int fFlags;
public:
	bool GetPos();

	bool GetViewAngle();
	bool GetCameraPos();
	bool GetWeaponName();
	bool GetShotsFired();
	bool GetAimPunchAngle();
    bool GetArmor();
	bool GetHealth();
	bool GetTeamID();
	bool GetFov();
	bool GetSpotted();
    bool GetSpottedByMask();
	bool GetFFlags();
	bool GetAimPunchCache();

	constexpr bool HasFlag(const Flags Flag) const noexcept {
		return fFlags & (int)Flag;
	}
};

class CEntity
{
public:
	PlayerController Controller;
	PlayerPawn Pawn;
public:
	// 更新数据
	bool UpdateController(const uintptr_t& PlayerControllerAddress);
	bool UpdatePawn(const uintptr_t& PlayerPawnAddress);
	// 是否存活
	bool IsAlive();
	// 是否在屏幕内
	bool IsInScreen();
	// 获取骨骼数据
	CBone GetBone() const;
};

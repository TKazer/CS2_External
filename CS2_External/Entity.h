#pragma once
#include "Game.h"
#include "View.hpp"
#include "Bone.h"

class PlayerController
{
public:
	DWORD64 Address = 0;
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
	DWORD64 GetPlayerPawnAddress();
};

class PlayerPawn
{
public:
	DWORD64 Address = 0;
	CBone BoneData;
	Vec2 ViewAngle;
	Vec3 Pos;
	Vec2 ScreenPos;
	Vec3 CameraPos;
	std::string WeaponName;
	DWORD ShotsFired;
	Vec2 AimPunchAngle;
	int Health;
	int TeamID;
	int Fov;
	int bSpottedByMask;
public:
	bool GetPos();
	bool GetViewAngle();
	bool GetCameraPos();
	bool GetWeaponName();
	bool GetShotsFired();
	bool GetAimPunchAngle();
	bool GetHealth();
	bool GetTeamID();
	bool GetFov();
	bool GetSpotted();
};

class CEntity
{
public:
	PlayerController Controller;
	PlayerPawn Pawn;
public:
	// 更新数据
	bool UpdateController(const DWORD64& PlayerControllerAddress);
	bool UpdatePawn(const DWORD64& PlayerPawnAddress);
	// 是否存活
	bool IsAlive();
	// 是否在屏幕内
	bool IsInScreen();
	// 获取骨骼数据
	CBone GetBone() const;
};
#pragma once
#include "Game.h"
#include "View.hpp"
#include "Bone.h"

class CEntity
{
public:
	DWORD64 EntityAddress = 0;
	DWORD64 EntityPawnAddress = 0;
	CBone BoneData;
	int TeamID = 0;
	int Health = 0;
	int AliveStatus = 0;
	DWORD Pawn = 0;
	Vec2 ViewAngle;
	Vec3 Pos;
	Vec2 ScreenPos;
	Vec3 CameraPos;
public:
	// 更新数据
	bool Update(const DWORD64& EntityAddress);
	// 是否存活
	bool IsAlive();
	// 是否在屏幕内
	bool IsInScreen();
private:
	bool GetTeamID();
	bool GetHealth();
	bool GetIsAlive();
	bool GetPawn();
	bool GetPos();
	bool GetViewAngle();
	bool GetCameraPos();
};
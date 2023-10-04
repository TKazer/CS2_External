#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Game.h"
#include "Entity.h"
#include <iostream>


namespace AimControl
{
	inline int HotKey = VK_LMENU;
	inline float AimFov = 5;
	inline float Smooth = 0.7;
	inline Vec2 RCSScale = { 1.2f,1.4f };
	inline int RCSBullet = 1;
	inline std::vector<int> HotKeyList{VK_LMENU, VK_RBUTTON, VK_XBUTTON1, VK_XBUTTON2, VK_CAPITAL, VK_LSHIFT, VK_LCONTROL};

	inline void SetHotKey(int Index)
	{
		HotKey = HotKeyList.at(Index);
	}

	inline void AimBot(const CEntity& Local, Vec3 LocalPos,  Vec3 AimPos)
	{
		float Yaw, Pitch;
		float Distance, Norm;
		Vec3 OppPos;
		
		OppPos = AimPos - LocalPos;

		Distance = sqrt(pow(OppPos.x, 2) + pow(OppPos.y, 2));
		
		Yaw = atan2f(OppPos.y, OppPos.x) * 57.295779513 - Local.Pawn.ViewAngle.y;
		Pitch = -atan(OppPos.z / Distance) * 57.295779513 - Local.Pawn.ViewAngle.x;
		Norm = sqrt(pow(Yaw, 2) + pow(Pitch, 2));
		if (Norm > AimFov)
			return;

		Yaw = Yaw * Smooth + Local.Pawn.ViewAngle.y;
		Pitch = Pitch * Smooth + Local.Pawn.ViewAngle.x;

		// Recoil control
		if (Local.Pawn.ShotsFired > RCSBullet)
		{
			Yaw = Yaw - Local.Pawn.AimPunchAngle.y * RCSScale.x;
			Pitch = Pitch - Local.Pawn.AimPunchAngle.x * RCSScale.y;
		}

		gGame.SetViewAngle(Yaw, Pitch);
	}
}
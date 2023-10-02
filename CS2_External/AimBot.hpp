#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Game.h"
#include "Entity.h"
#include <iostream>


namespace AimControl
{
	static int HotKey = VK_LMENU;	// 瞄准热键
	static float AimRange = 1920;	// 瞄准范围(px)
	static float AimFov = 5;		// 瞄准范围(fov)
	//if need 89fov or higher,del AimRange check,only use fov check.
	static float Smooth = 0.7;		// 平滑系数
	static Vec2 RCSScale = { 1.2f,1.4f };		// 后坐力系数
	static int RCSBullet = 1;		// 后坐力控制开始


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
#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Game.h"
#include "Entity.h"

namespace AimControl
{
	static int HotKey = VK_LMENU;	// Ãé×¼ÈÈ¼ü
	static float AimRange = 300;	// Ãé×¼·¶Î§

	inline void AimBot(const CEntity& Local, Vec3 LocalPos,  Vec3 AimPos)
	{
		float Yaw, Pitch;
		float Distance;
		Vec3 OppPos;
		
		OppPos = AimPos - LocalPos;

		Distance = sqrt(pow(OppPos.x, 2) + pow(OppPos.y, 2));

		Yaw = atan2f(OppPos.y, OppPos.x) * 180 / M_PI;
		Pitch = -atan(OppPos.z / Distance) * 180 / M_PI;

		gGame.SetViewAngle(Yaw, Pitch);
	}
}
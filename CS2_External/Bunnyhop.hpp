#pragma once
#define _USE_MATH_DEFINES
#include <math.h>
#include "Game.h"
#include "Entity.h"
#include "MenuConfig.hpp"
#include <iostream>

namespace Bunnyhop
{
	inline void Run(const CEntity& Local)
	{

		if (GetAsyncKeyState(VK_SPACE) && (Local.Pawn.fFlags & (1 << 0)))
		{
			gGame.SetForceJump(65537);
		}
		else if (GetAsyncKeyState(VK_SPACE) && !(Local.Pawn.fFlags & (1 << 0)))
		{
			gGame.SetForceJump(256);
			gGame.SetForceJump(65537);
			gGame.SetForceJump(256);
		}
		else
		{
			gGame.SetForceJump(256);
		}
	}
}
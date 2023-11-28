#pragma once
#include "Game.h"
#include "Entity.h"
#include "AimBot.hpp"
#include "Radar/Radar.h"
#include "TriggerBot.h"
#include "Bunnyhop.hpp"
#include "AntiFlashbang.hpp"

namespace Cheats
{
    inline CEntity LocalEntity;
    //inline int LocalPlayerControllerIndex = 1;
	void Menu();
	void RadarSetting(Base_Radar& Radar);
	void Run();
    void Loop();
}

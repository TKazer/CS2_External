#pragma once
#include "Game.h"
#include "Entity.h"
#include <chrono>

namespace TriggerBot
{
	inline DWORD TriggerDelay = 90; // ms

	// Triggerbot
	void Run(const CEntity& LocalEntity);
}
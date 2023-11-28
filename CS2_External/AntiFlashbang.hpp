#pragma once

#include "Entity.h"

namespace AntiFlashbang
{
	inline void Run(const CEntity &aLocalPlayer) noexcept
	{
		float duration{};
		ProcessMgr.WPM<float>(aLocalPlayer.Pawn.Address + Offset::Pawn.flFlashDuration, duration);
	}
} // namespace AntiFlashbang

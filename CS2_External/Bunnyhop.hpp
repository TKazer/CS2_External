#pragma once
#include "MenuConfig.hpp"
#include "Entity.h"
#include <thread>
#include <chrono>

namespace Bunnyhop
{
    inline bool AirCheck(const CEntity& Local)
    {
        const bool hasFlagInAir = Local.Pawn.HasFlag(PlayerPawn::Flags::IN_AIR);
        return hasFlagInAir;
    }

    inline void Run(const CEntity& Local)
    {
        if (!MenuConfig::BunnyHop)
            return;

        int ForceJump = 0;
        bool spacePressed = GetAsyncKeyState(VK_SPACE);
        bool isInAir = AirCheck(Local);
        gGame.SetForceJump(ForceJump);

        if (spacePressed && isInAir)
        {
            std::this_thread::sleep_for(std::chrono::milliseconds(5)); // milliseconds
            gGame.SetForceJump(65537);
        }
        else if (spacePressed && !isInAir)
        {
            gGame.SetForceJump(256);
        }
        else if (!spacePressed && ForceJump == 65537)
        {
            gGame.SetForceJump(256);
        }
    }
}

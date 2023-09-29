#pragma once
#include <Windows.h>

/*
	Date: 2023/9/29
*/

namespace Offset
{
	constexpr DWORD EntityList = 0x178C878;
	constexpr DWORD Matrix = 0x187A6D0;
	constexpr DWORD ViewAngle = 0x18D9590;
	constexpr DWORD LocalController = 0x17DB0F8;

	struct
	{
		DWORD Health = 0x808;
		DWORD TeamID = 0x3BF;
		DWORD IsAlive = 0x804;
		DWORD PlayerPawn = 0x7FC;
	}Entity;

	struct
	{
		DWORD Pos = 0xCD8;
		DWORD MaxHealth = 0x328;
		DWORD CurrentHealth = 0x32C;
		DWORD GameSceneNode = 0x310;
		DWORD BoneArray = 0x1E0;
		DWORD angEyeAngles = 0x1500;
		DWORD vecLastClipCameraPos = 0x1274;
	}Pawn;
}

#pragma once
#include <Windows.h>
#include "Utils/ProcessManager.hpp"

namespace Offset
{
	inline DWORD EntityList;// = 0x178C878;
	inline DWORD Matrix;// = 0x187A6D0;
	inline DWORD ViewAngle;// = 0x18D9590;
	inline DWORD LocalPlayerController;// = 0x17DB0F8;

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

	namespace Signatures
	{
		const std::string EntityList = "48 8B 0D ?? ?? ?? ?? 48 89 7C 24 ?? 8B FA C1 EB";
		const std::string LocalPlayerController = "48 8B 05 ?? ?? ?? ?? 48 85 C0 74 4F";
		const std::string ViewAngles = "48 8B 0D ?? ?? ?? ?? 48 8B 01 48 FF 60 30";
		const std::string ViewMatrix = "48 8D 0D ?? ?? ?? ?? 48 C1 E0 06";
	}

	// 一键更新基址
	bool UpdateOffsets();
}

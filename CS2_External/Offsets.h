#pragma once
#include <Windows.h>
#include "Utils/ProcessManager.hpp"

// From: https://github.com/a2x/cs2-dumper/blob/main/generated/client.dll.hpp
namespace Offset
{
	inline DWORD EntityList;
	inline DWORD Matrix;
	inline DWORD ViewAngle;
	inline DWORD LocalPlayerController;
	inline DWORD LocalPlayerPawn;
	inline DWORD ForceJump;
	inline DWORD GlobalVars;

	struct
	{
		DWORD Health = 0x32C;
		DWORD TeamID = 0x3BF;
		DWORD IsAlive = 0x7DC;
		DWORD PlayerPawn = 0x5F4;
		DWORD iszPlayerName = 0x628;
	}Entity;

	struct
	{
		DWORD Pos = 0x1224;
		DWORD MaxHealth = 0x328;
		DWORD CurrentHealth = 0x32C;
		DWORD GameSceneNode = 0x310;
		DWORD BoneArray = 0x1E0;
		DWORD angEyeAngles = 0x1510;
		DWORD vecLastClipCameraPos = 0x128C;
		DWORD pClippingWeapon = 0x12A8;
		DWORD iShotsFired = 0x1418;
		DWORD flFlashDuration = 0x1468;
		DWORD aimPunchAngle = 0x1714;
		DWORD aimPunchCache = 0x1738;
		DWORD iIDEntIndex = 0x153C;
		DWORD iTeamNum = 0x3BF;
		DWORD CameraServices = 0x10E0;
		DWORD iFovStart = 0x214;
		DWORD fFlags = 0x3C8;
		DWORD bSpottedByMask = 0x1630 + 0xC; // entitySpottedState + bSpottedByMask
	}Pawn;

	struct
	{
		DWORD RealTime = 0x00;
		DWORD FrameCount = 0x04;
		DWORD MaxClients = 0x10;
		DWORD IntervalPerTick = 0x14;
		DWORD CurrentTime = 0x2C;
		DWORD CurrentTime2 = 0x30;
		DWORD TickCount = 0x40;
		DWORD IntervalPerTick2 = 0x44;
		DWORD CurrentNetchan = 0x0048;
		DWORD CurrentMap = 0x0180;
		DWORD CurrentMapName = 0x0188;
	} GlobalVar;

	namespace Signatures
	{
		const std::string GlobalVars = "48 89 0D ?? ?? ?? ?? 48 89 41";
		const std::string ViewMatrix = "48 8D 0D ?? ?? ?? ?? 48 C1 E0 06";
		const std::string ViewAngles = "48 8B 0D ?? ?? ?? ?? E9 ?? ?? ?? ?? CC CC CC CC 40 55";
		const std::string EntityList = "48 8B 0D ?? ?? ?? ?? 48 89 7C 24 ?? 8B FA C1";
		const std::string LocalPlayerController = "48 8B 05 ?? ?? ?? ?? 48 85 C0 74 4F";
		const std::string ForceJump = "48 8B 05 ?? ?? ?? ?? 48 8D 1D ?? ?? ?? ?? 48 89 45";
		const std::string LocalPlayerPawn = "48 8D 05 ?? ?? ?? ?? C3 CC CC CC CC CC CC CC CC 48 83 EC ?? 8B 0D";
	}

	bool UpdateOffsets();
}

#pragma once
#include <Windows.h>
#include "Utils/ProcessManager.hpp"

namespace Offset
{
	inline DWORD EntityList;
	inline DWORD Matrix;
	inline DWORD ViewAngle;
	inline DWORD LocalPlayerController;
	inline DWORD LocalPlayerPawn;
	inline DWORD ForceJump; 
	inline DWORD GlobalVars;
	inline DWORD PlantedC4;

	struct
	{
		DWORD Health = 0x32C;
		DWORD TeamID = 0x3BF;
		DWORD IsAlive = 0x7C4;
		DWORD PlayerPawn = 0x7BC;
		DWORD iszPlayerName = 0x610;
	}Entity;

	struct
	{
		DWORD Pos = 0x1214;
		DWORD MaxHealth = 0x328;
		DWORD CurrentHealth = 0x32C;
		DWORD GameSceneNode = 0x310;
		DWORD BoneArray = 0x1E0;
		DWORD angEyeAngles = 0x1500;
		DWORD vecLastClipCameraPos = 0x1274;
		DWORD pClippingWeapon = 0x1290;
		DWORD iShotsFired = 0x1404;
		DWORD aimPunchAngle = 0x1704;
		DWORD aimPunchCache = 0x1728;
		DWORD iIDEntIndex = 0x152C;
		DWORD iTeamNum = 0x3BF;
		DWORD CameraServices = 0x10E0;
		DWORD iFovStart = 0x214;
		DWORD fFlags = 0x3C8;
		DWORD bSpottedByMask = 0x1620 + 0xC; // entitySpottedState + bSpottedByMask
	}Pawn;

	struct
	{
		DWORD real_time = 0x00;
		DWORD frame_count = 0x04;
		DWORD max_clients = 0x10;
		DWORD interval_per_tick = 0x14;
		DWORD current_time = 0x2C;
		DWORD current_time2 = 0x30;
		DWORD tick_count = 0x40;
		DWORD interval_per_tick2 = 0x44;
		DWORD current_netchan = 0x0048;
		DWORD current_map = 0x0180;
		DWORD current_map_name = 0x0188;
	}GlobalVar;

	struct {
		DWORD m_nBombSite = 0xE84;
		DWORD m_bBombTicking = 0xE80;
		DWORD m_hBombDefuser = 0xEDC;
		DWORD m_flC4Blow = 0xEB0;
		DWORD m_flDefuseCountDown = 0xED4;
	} CPlantedC4;

	// https://github.com/a2x/cs2-dumper/blob/main/config.json

	namespace Signatures
	{
		const std::string EntityList = "48 8B 0D ?? ?? ?? ?? 48 89 7C 24 ?? 8B FA C1";
		const std::string LocalPlayerController = "48 8B 05 ?? ?? ?? ?? 48 85 C0 74 4F";
		const std::string ViewAngles = "48 8B 0D ?? ?? ?? ?? 48 8B 01 48 FF 60 30";
		const std::string ViewMatrix = "48 8D 0D ?? ?? ?? ?? 48 C1 E0 06";
		const std::string LocalPlayerPawn = "48 8D 05 ?? ?? ?? ?? C3 CC CC CC CC CC CC CC CC 48 83 EC ?? 8B 0D";
		const std::string ForceJump = "48 8B 05 ?? ?? ?? ?? 48 8D 1D ?? ?? ?? ?? 48 89 45";
		const std::string GlobalVars = "48 89 0D ?? ?? ?? ?? 48 89 41";
		const std::string PlantedC4 = "48 89 05 ?? ?? ?? ?? 8B 05 ?? ?? ?? ?? A9 ?? ?? ?? ?? 74 ?? 25 ?? ?? ?? ?? 89 05 ?? ?? ?? ?? 8B 0D";
	}

	bool UpdateOffsets();
}

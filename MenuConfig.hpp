#pragma once
#include "Game.h"
#include "OS-ImGui/ImGui/ImGui.h"

namespace MenuConfig
{
	extern bool ShowBoneESP;
	extern bool ShowBoxESP;
	extern bool ShowHealthBar;
	extern bool ShowWeaponESP;
	extern bool ShowEyeRay;
	extern bool ShowPlayerName;

	extern bool AimBot;
	//inline float Smooth = 0.7;
	// 0: head 1: neck 3: spine
	extern int  AimPosition;
	extern DWORD  AimPositionIndex;

	// 0: normal 1: dynamic
	extern int  BoxType;
	// 0: Vertical 1: Horizontal
	extern int  HealthBarType;

	extern ImVec4 BoneColor;
	extern ImVec4 BoxColor;
	extern ImVec4 EyeRayColor;

	extern bool ShowMenu;

	extern bool ShowRadar;
	extern float RadarRange;
	extern bool ShowCrossLine;
	extern ImVec4 CrossLineColor;
	// 0: circle 1: arrow 2: circle with arrow
	extern int RadarType;
	extern float Proportion;

	extern bool TriggerBot;
	
	extern bool TeamCheck;

	extern bool ShowHeadShootLine;
	extern ImVec4 HeadShootLineColor;
}
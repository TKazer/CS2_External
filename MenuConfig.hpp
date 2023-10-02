#pragma once
#include "Game.h"
#include "bone.h"

namespace MenuConfig
{
	inline bool ShowBoneESP = true;
	inline bool ShowBoxESP = true;
	inline bool ShowHealthBar = true;
	inline bool ShowWeaponESP = true;
	inline bool ShowEyeRay = true;
	inline bool ShowPlayerName = true;

	inline bool AimBot = true;
	//inline float Smooth = 0.7;
	// 0: head 1: neck 3: spine
	inline int  AimPosition = 0;
	inline DWORD  AimPositionIndex = BONEINDEX::head;

	// 0: normal 1: dynamic
	inline int  BoxType = 0;
	// 0: Vertical 1: Horizontal
	inline int  HealthBarType = 0;

	inline ImVec4 BoneColor = ImVec4(255, 255, 255, 255);
	inline ImVec4 BoxColor = ImVec4(255, 255, 255, 255);
	inline ImVec4 EyeRayColor = ImVec4(255, 0, 0, 255);

	inline bool ShowMenu = true;

	inline bool ShowRadar = true;
	inline float RadarRange = 150;
	inline bool ShowCrossLine = true;
	inline ImVec4 CrossLineColor = ImVec4(34, 34, 34, 180);
	// 0: circle 1: arrow 2: circle with arrow
	inline int RadarType = 2;
	inline float Proportion = 2300;

	inline bool TriggerBot = true;

	inline bool TeamCheck = true;

	inline bool ShowHeadShootLine = true;
	inline ImVec4 HeadShootLineColor = ImVec4(255, 255, 255, 255);
}
#include "Cheats.h"
#include "Render.hpp"
#include "MenuConfig.hpp"

void Cheats::Menu()
{
	ImGui::Begin("Menu",nullptr,ImGuiWindowFlags_AlwaysAutoResize);
	{
		// esp menu
		if (ImGui::CollapsingHeader("ESP"))
		{
			Gui.MyCheckBox("BoxESP", &MenuConfig::ShowBoxESP);
			ImGui::SameLine();
			ImGui::ColorEdit4("##BoxColor", reinterpret_cast<float*>(&MenuConfig::BoxColor));

			ImGui::Combo("BoxType", &MenuConfig::BoxType, "Normal\0Dynamic");

			Gui.MyCheckBox("BoneESP", &MenuConfig::ShowBoneESP);
			ImGui::SameLine();
			ImGui::ColorEdit4("##BoneColor", reinterpret_cast<float*>(&MenuConfig::BoneColor));

			Gui.MyCheckBox("EyeRay", &MenuConfig::ShowEyeRay);
			ImGui::SameLine();
			ImGui::ColorEdit4("##EyeRay", reinterpret_cast<float*>(&MenuConfig::EyeRayColor));

			Gui.MyCheckBox("HealthBar", &MenuConfig::ShowHealthBar);
			ImGui::Combo("HealthBarType", &MenuConfig::HealthBarType, "Vetical\0Horizontal");

			Gui.MyCheckBox("WeaponText", &MenuConfig::ShowWeaponESP);
			Gui.MyCheckBox("PlayerName", &MenuConfig::ShowPlayerName);
		}

		// aimbot menu
		if (ImGui::CollapsingHeader("AimBot"))
		{
			Gui.MyCheckBox("Aimbot", &MenuConfig::AimBot);
			float SmoothMin = 0.1f, SmoothMax = 1.f;
			Gui.SliderScalarEx1("Smooth", ImGuiDataType_Float, &MenuConfig::Smooth, &SmoothMin, &SmoothMax, "%.1f", ImGuiSliderFlags_None);
			if (ImGui::Combo("AimPos", &MenuConfig::AimPosition, "Head\0Neck\0Spine"))
			{
				switch (MenuConfig::AimPosition)
				{
				case 0:
					MenuConfig::AimPositionIndex = BONEINDEX::head;
					break;
				case 1:
					MenuConfig::AimPositionIndex = BONEINDEX::neck_0;
					break;
				case 2:
					MenuConfig::AimPositionIndex = BONEINDEX::spine_1;
					break;
				default:
					break;
				}
			}
		}

		// Radar menu
		if (ImGui::CollapsingHeader("Radar"))
		{
			Gui.MyCheckBox("Radar", &MenuConfig::ShowRadar);
			ImGui::Combo("RadarType", &MenuConfig::RadarType, "Circle\0Arrow\0CircleWithArrow");

			Gui.MyCheckBox("CrossLine", &MenuConfig::ShowCrossLine);
			ImGui::SameLine();
			ImGui::ColorEdit4("##CrossLineColor", reinterpret_cast<float*>(&MenuConfig::CrossLineColor));

			float ProportionMin = 500.f, ProportionMax = 3300.f;
			float RadarRangeMin = 100.f, RadarRangeMax = 300.f;

			Gui.SliderScalarEx1("Proportion", ImGuiDataType_Float, &MenuConfig::Proportion, &ProportionMin, &ProportionMax, "%.1f", ImGuiSliderFlags_None);
			Gui.SliderScalarEx1("RadarRange", ImGuiDataType_Float, &MenuConfig::RadarRange, &RadarRangeMin, &RadarRangeMax, "%.1f", ImGuiSliderFlags_None);
		}

		// TriggerBot
		if (ImGui::CollapsingHeader("TriggerBot"))
		{
			Gui.MyCheckBox("TriggerBot", &MenuConfig::TriggerBot);

			DWORD TriggerDelayMin = 15, TriggerDelayMax = 170;
			Gui.SliderScalarEx1("Delay", ImGuiDataType_U32, &TriggerBot::TriggerDelay, &TriggerDelayMin, &TriggerDelayMax, "%d", ImGuiSliderFlags_None);

		}

		ImGui::Text("[HOME] HideMenu");

	}ImGui::End();
}

void Cheats::RadarSetting(Base_Radar& Radar)
{
	Radar.SetPos({ Gui.Window.Size.x / 2,Gui.Window.Size.y / 2 });
	Radar.SetProportion(MenuConfig::Proportion);
	Radar.SetRange(MenuConfig::RadarRange);
	Radar.SetSize(MenuConfig::RadarRange * 2);
	Radar.SetCrossColor(MenuConfig::CrossLineColor);
	Radar.ShowCrossLine = MenuConfig::ShowCrossLine;
	Radar.Opened = true;
}

void Cheats::Run()
{
	// Show menu
	if (GetAsyncKeyState(VK_HOME) & 0x8000)
		MenuConfig::ShowMenu = !MenuConfig::ShowMenu;
	if(MenuConfig::ShowMenu)
		Menu();

	// Update matrix
	if(!ProcessMgr.ReadMemory(gGame.GetMatrixAddress(), gGame.View.Matrix,64))
		return;

	// Update EntityList Entry
	gGame.UpdateEntityListEntry();

	DWORD64 LocalControllerAddress = 0;
	DWORD64 LocalPawnAddress = 0;

	if (!ProcessMgr.ReadMemory(gGame.GetLocalControllerAddress(), LocalControllerAddress))
		return;
	if (!ProcessMgr.ReadMemory(gGame.GetLocalPawnAddress(), LocalPawnAddress))
		return;

	// LocalEntity
	CEntity LocalEntity;
	if (!LocalEntity.UpdateController(LocalControllerAddress))
		return;
	if (!LocalEntity.UpdatePawn(LocalPawnAddress))
		return;

	// HealthBar Map
	static std::map<DWORD64, Render::HealthBar> HealthBarMap;

	// AimBot data
	float DistanceToSight = 0;
	float MaxAimDistance = 100000;
	Vec3  HeadPos{ 0,0,0 };
	Vec3  AimPos{ 0,0,0 };

	// Radar Data
	Base_Radar Radar;
	RadarSetting(Radar);

	for (int i = 0; i < 64; i++)
	{
		CEntity Entity;
		DWORD64 EntityAddress = 0;
		if (!ProcessMgr.ReadMemory<DWORD64>(gGame.GetEntityListEntry() + (i + 1) * 0x78, EntityAddress))
			continue;
		if (EntityAddress == LocalEntity.Controller.Address)
			continue;
		if (!Entity.UpdateController(EntityAddress))
			continue;
		if (!Entity.UpdatePawn(Entity.Pawn.Address))
			continue;

		if (Entity.Controller.TeamID == LocalEntity.Controller.TeamID)
			continue;
		if (!Entity.IsAlive())
			continue;

		// Add entity to radar
		if(MenuConfig::ShowRadar)
			Radar.AddPoint(LocalEntity.Pawn.Pos, LocalEntity.Pawn.ViewAngle.y, Entity.Pawn.Pos, ImColor(237, 85, 106, 200), MenuConfig::RadarType, Entity.Pawn.ViewAngle.y);

		if (!Entity.IsInScreen())
			continue;

		// Bone Debug
	/*	for (int BoneIndex = 0; BoneIndex < Entity.BoneData.BonePosList.size(); BoneIndex++)
		{
			Vec2 ScreenPos{};
			if (gGame.View.WorldToScreen(Entity.BoneData.BonePosList[BoneIndex].Pos, ScreenPos))
			{
				Gui.Text(std::to_string(BoneIndex), ScreenPos, ImColor(255, 255, 255, 255));
			}
		}*/

		DistanceToSight = Entity.GetBone().BonePosList[BONEINDEX::head].ScreenPos.DistanceTo({Gui.Window.Size.x / 2,Gui.Window.Size.y / 2});

		if (DistanceToSight < AimControl::AimRange)
		{
			if (DistanceToSight < MaxAimDistance)
			{
				MaxAimDistance = DistanceToSight;
				AimPos = Entity.GetBone().BonePosList[MenuConfig::AimPositionIndex].Pos;
				if (MenuConfig::AimPositionIndex == BONEINDEX::head)
					AimPos.z -= 1.f;
			}
		}

		// Draw Bone
		if(MenuConfig::ShowBoneESP)
			Render::DrawBone(Entity, MenuConfig::BoneColor, 1.3);

		// Draw eyeRay
		if(MenuConfig::ShowEyeRay)
			Render::ShowLosLine(Entity, 50, MenuConfig::EyeRayColor, 1.3);

		ImVec4 Rect;
		switch (MenuConfig::BoxType)
		{
		case 0:
			Rect = Render::Get2DBox(Entity);
			break;
		case 1:
			Rect = Render::Get2DBoneRect(Entity);
			break;
		default:
			break;
		}

		// Draw Box
		if (MenuConfig::ShowBoxESP)
			Gui.Rectangle({ Rect.x,Rect.y }, { Rect.z,Rect.w }, MenuConfig::BoxColor, 1.3);

		// Draw HealthBar
		if (MenuConfig::ShowHealthBar)
		{
			ImVec2 HealthBarPos, HealthBarSize;
			if (MenuConfig::HealthBarType == 0)
			{
				// Vertical
				HealthBarPos = { Rect.x - 7.f,Rect.y };
				HealthBarSize = { 7 ,Rect.w };
			}
			else
			{
				// Horizontal
				HealthBarPos = { Rect.x + Rect.z / 2 - 70 / 2,Rect.y - 13 };
				HealthBarSize = { 70,8 };
			}
			Render::DrawHealthBar(EntityAddress, 100, Entity.Controller.Health, HealthBarPos, HealthBarSize, MenuConfig::HealthBarType);
		}

		// Draw weaponName
		if (MenuConfig::ShowWeaponESP)
			Gui.StrokeText(Entity.Pawn.WeaponName, { Rect.x,Rect.y + Rect.w }, ImColor(255, 255, 255, 255), 14);

		if (MenuConfig::ShowPlayerName)
		{
			if (MenuConfig::HealthBarType == 0)
				Gui.StrokeText(Entity.Controller.PlayerName, { Rect.x + Rect.z / 2,Rect.y - 14 }, ImColor(255, 255, 255, 255), 14, true);
			else
				Gui.StrokeText(Entity.Controller.PlayerName, { Rect.x + Rect.z / 2,Rect.y - 13 - 14 }, ImColor(255, 255, 255, 255), 14, true);
		}

	}

	// Radar render
	if(MenuConfig::ShowRadar)
		Radar.Render();
	
	// TriggerBot
	if(MenuConfig::TriggerBot)
		TriggerBot::Run(LocalEntity);

	if (MenuConfig::AimBot && GetAsyncKeyState(AimControl::HotKey))
	{
		if (AimPos != Vec3(0, 0, 0))
		{
			AimControl::AimBot(LocalEntity, LocalEntity.Pawn.CameraPos, AimPos);
		}
	}
}

#pragma once
#include <Windows.h>
#include "Utils/ProcessManager.hpp"
#include "Utils/Helpers.h"
#include "a2x/offsets.hpp"
#include "a2x/client.dll.hpp"
#include "a2x/buttons.hpp"

namespace Offset
{
	inline DWORD ForceJump = cs2_dumper::buttons::jump;
	inline DWORD ForceCrouch = cs2_dumper::buttons::duck;
	inline DWORD ForceForward = cs2_dumper::buttons::forward;
	inline DWORD ForceLeft = cs2_dumper::buttons::left;
	inline DWORD ForceRight = cs2_dumper::buttons::right;

	inline DWORD EntityList;// = cs2_dumper::offsets::client_dll::dwEntityList;
	inline DWORD Matrix;
	inline DWORD ViewAngle;
	inline DWORD LocalPlayerController;
	inline DWORD LocalPlayerPawn;
	inline DWORD GlobalVars;
	inline DWORD InventoryServices;
	inline DWORD PlantedC4;
	inline DWORD InputSystem;
	inline DWORD Sensitivity;
	inline DWORD Pointer;

	struct
	{
		//DWORD Health = Offset::Pawn.CurrentHealth;
		//DWORD TeamID = Offset::Pawn.iTeamNum;
		DWORD IsAlive = cs2_dumper::schemas::client_dll::CCSPlayerController::m_bPawnIsAlive;
		DWORD PlayerPawn = cs2_dumper::schemas::client_dll::CCSPlayerController::m_hPlayerPawn;
		DWORD iszPlayerName = cs2_dumper::schemas::client_dll::CBasePlayerController::m_iszPlayerName;
		//outdated DWORD EnemySensor = 0x1440;
		DWORD GravityScale = cs2_dumper::schemas::client_dll::C_BaseEntity::m_flGravityScale;
	}Entity;

	struct
	{
		DWORD MovementServices = cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_pMovementServices;		// CPlayer_MovementServices*
		DWORD WeaponServices = cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_pWeaponServices;			// CPlayer_WeaponServices*
		DWORD BulletServices = cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_pBulletServices;			// CCSPlayer_BulletServices*
		DWORD CameraServices = cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_pCameraServices;			// CPlayer_CameraServices*
		DWORD ViewModelServices = cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_pViewModelServices;		// CPlayer_ViewModelServices*
		DWORD pClippingWeapon = cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_pClippingWeapon;			// C_CSWeaponBase*

		DWORD ViewModel = cs2_dumper::schemas::client_dll::CCSPlayer_ViewModelServices::m_hViewModel;				// CCSPlayer_ViewModelServices::m_hViewModel
		//wahss diz? DWORD StartAccount = 0x1490;
		DWORD isScoped = cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_bIsScoped;
		DWORD isDefusing = cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_bIsDefusing;
		DWORD TotalHit = cs2_dumper::schemas::client_dll::CCSPlayer_BulletServices::m_totalHitsOnServer;
		DWORD Pos = cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_vOldOrigin;// C_BasePlayerPawn::m_vOldOrigin
		DWORD CurrentArmor = cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_ArmorValue;// C_CSPlayerPawn::m_ArmorValue
		DWORD MaxHealth = cs2_dumper::schemas::client_dll::C_BaseEntity::m_iMaxHealth;				// C_BaseEntity::m_iMaxHealth
		DWORD CurrentHealth = cs2_dumper::schemas::client_dll::C_BaseEntity::m_iHealth;// C_BaseEntity::m_iHealth
		DWORD GameSceneNode = cs2_dumper::schemas::client_dll::C_BaseEntity::m_pGameSceneNode;			// C_BaseEntity::m_pGameSceneNode
		DWORD BoneArray = cs2_dumper::schemas::client_dll::CSkeletonInstance::m_modelState + cs2_dumper::schemas::client_dll::CGameSceneNode::m_vecOrigin;				// CSkeletonInstance_::m_modelState + CGameSceneNode_::m_vecOrigin
		DWORD angEyeAngles = cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_angEyeAngles;
		DWORD vecLastClipCameraPos = cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_vecLastClipCameraPos;
		DWORD iShotsFired = cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_iShotsFired;
		DWORD flFlashMaxAlpha = cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_flFlashMaxAlpha;
		DWORD flFlashDuration = cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_flFlashDuration;
		DWORD aimPunchAngle = cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_aimPunchAngle;			// C_CSPlayerPawn::m_aimPunchAngle
		DWORD aimPunchCache = cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_aimPunchCache;
		DWORD iIDEntIndex = cs2_dumper::schemas::client_dll::C_CSPlayerPawnBase::m_iIDEntIndex;
		DWORD iTeamNum = cs2_dumper::schemas::client_dll::C_BaseEntity::m_iTeamNum;
		DWORD DesiredFov = cs2_dumper::schemas::client_dll::CBasePlayerController::m_iDesiredFOV;
		DWORD iFovStart = cs2_dumper::schemas::client_dll::CCSPlayerBase_CameraServices::m_iFOVStart;
		DWORD fFlags = cs2_dumper::schemas::client_dll::C_BaseEntity::m_fFlags;
		DWORD bSpottedByMask = cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_entitySpottedState + cs2_dumper::schemas::client_dll::EntitySpottedState_t::m_bSpottedByMask;	// C_CSPlayerPawn::entitySpottedState + EntitySpottedState_t::bSpottedByMask
		DWORD AbsVelocity = cs2_dumper::schemas::client_dll::C_BaseEntity::m_vecAbsVelocity;
		DWORD IsBuying = cs2_dumper::schemas::client_dll::C_CSPlayerPawn::m_bIsBuyMenuOpen;
	} Pawn;

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

	struct
	{
		DWORD m_hPawn = cs2_dumper::schemas::client_dll::CBasePlayerController::m_hPawn;
		DWORD m_pObserverServices = cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_pObserverServices;
		DWORD m_hObserverTarget = cs2_dumper::schemas::client_dll::CPlayer_ObserverServices::m_hObserverTarget;
		DWORD m_hController = cs2_dumper::schemas::client_dll::C_BasePlayerPawn::m_hController;
		DWORD PawnArmor = cs2_dumper::schemas::client_dll::CCSPlayerController::m_iPawnArmor;
		DWORD HasDefuser = cs2_dumper::schemas::client_dll::CCSPlayerController::m_bPawnHasDefuser;
		DWORD HasHelmet = cs2_dumper::schemas::client_dll::CCSPlayerController::m_bPawnHasHelmet;
	} PlayerController;

	struct
	{
		DWORD AttributeManager = cs2_dumper::schemas::client_dll::C_EconEntity::m_AttributeManager;		// C_AttributeContainer
		DWORD FallbackPaintKit = cs2_dumper::schemas::client_dll::C_EconEntity::m_nFallbackPaintKit;
		DWORD FallbackSeed = cs2_dumper::schemas::client_dll::C_EconEntity::m_nFallbackSeed;
		DWORD FallbackWear = cs2_dumper::schemas::client_dll::C_EconEntity::m_flFallbackWear;
		DWORD FallbackStatTrak = cs2_dumper::schemas::client_dll::C_EconEntity::m_nFallbackStatTrak;
		DWORD szCustomName = cs2_dumper::schemas::client_dll::C_EconItemView::m_szCustomName;

		DWORD EntityQuality = cs2_dumper::schemas::client_dll::C_EconItemView::m_iEntityQuality;			// EconItemView::m_iEntityQuality
		DWORD ItemIDHigh = cs2_dumper::schemas::client_dll::C_EconItemView::m_iItemIDHigh;				// EconItemView::m_iItemIDHigh
	} EconEntity;

	struct
	{
		//DWORD ClippingWeapon = Offset::Pawn.pClippingWeapon;			// WeaponBase
		DWORD WeaponDataPTR = 0x368;
		DWORD szName = cs2_dumper::schemas::client_dll::CCSWeaponBaseVData::m_szName;
		DWORD Clip1 = cs2_dumper::schemas::client_dll::C_BasePlayerWeapon::m_iClip1;					// C_BasePlayerWeapon::m_iClip1
		DWORD MaxClip = cs2_dumper::schemas::client_dll::CBasePlayerWeaponVData::m_iMaxClip1;					// CBasePlayerWeaponVData::m_iMaxClip1
		DWORD CycleTime = cs2_dumper::schemas::client_dll::CCSWeaponBaseVData::m_flCycleTime;
		DWORD Penetration = cs2_dumper::schemas::client_dll::CCSWeaponBaseVData::m_flPenetration;
		DWORD WeaponType = cs2_dumper::schemas::client_dll::CCSWeaponBaseVData::m_WeaponType;
		DWORD Inaccuracy = cs2_dumper::schemas::client_dll::CCSWeaponBaseVData::m_flInaccuracyMove;				// CCSWeaponBaseVData::m_flInaccuracyMove
		DWORD inReload = cs2_dumper::schemas::client_dll::C_CSWeaponBase::m_bInReload;

		DWORD WeaponSize = 0x50;
		DWORD ActiveWeapon = cs2_dumper::schemas::client_dll::CPlayer_WeaponServices::m_hActiveWeapon;
		DWORD Item = cs2_dumper::schemas::client_dll::C_AttributeContainer::m_Item;						// C_AttributeContainer::m_Item
		DWORD ItemDefinitionIndex = cs2_dumper::schemas::client_dll::C_EconItemView::m_iItemDefinitionIndex;
		DWORD m_MeshGroupMask = cs2_dumper::schemas::client_dll::CModelState::m_MeshGroupMask;			// CModelState::m_MeshGroupMask
	} WeaponBaseData;

	struct
	{
		DWORD m_bBeingDefused = cs2_dumper::schemas::client_dll::C_PlantedC4::m_bBeingDefused;
		DWORD m_flDefuseCountDown = cs2_dumper::schemas::client_dll::C_PlantedC4::m_flDefuseCountDown;
		DWORD m_nBombSite = cs2_dumper::schemas::client_dll::C_PlantedC4::m_nBombSite;
	} C4;

	struct
	{
		DWORD MoneyServices = cs2_dumper::schemas::client_dll::CCSPlayerController::m_pInGameMoneyServices;
		DWORD Account = cs2_dumper::schemas::client_dll::CCSPlayerController_InGameMoneyServices::m_iAccount;
		DWORD TotalCashSpent = cs2_dumper::schemas::client_dll::CCSPlayerController_InGameMoneyServices::m_iTotalCashSpent;
		DWORD CashSpentThisRound = cs2_dumper::schemas::client_dll::CCSPlayerController_InGameMoneyServices::m_iCashSpentThisRound;
	} InGameMoneyServices;

	struct // C_BaseCSGrenadeProjectile
	{
		DWORD nSmokeEffectTickBegin = cs2_dumper::schemas::client_dll::C_SmokeGrenadeProjectile::m_nSmokeEffectTickBegin; // int32_t
		DWORD bDidSmokeEffect = cs2_dumper::schemas::client_dll::C_SmokeGrenadeProjectile::m_bDidSmokeEffect; // bool
		DWORD nRandomSeed = cs2_dumper::schemas::client_dll::C_SmokeGrenadeProjectile::m_nRandomSeed; // int32_t
		DWORD vSmokeColor = cs2_dumper::schemas::client_dll::C_SmokeGrenadeProjectile::m_vSmokeColor; // Vector
		DWORD vSmokeDetonationPos = cs2_dumper::schemas::client_dll::C_SmokeGrenadeProjectile::m_vSmokeDetonationPos; // Vector
		DWORD VoxelFrameData = cs2_dumper::schemas::client_dll::C_SmokeGrenadeProjectile::m_VoxelFrameData; // CUtlVector<uint8_t>
		DWORD bSmokeVolumeDataReceived = cs2_dumper::schemas::client_dll::C_SmokeGrenadeProjectile::m_bSmokeVolumeDataReceived; // bool
		uintptr_t bSmokeEffectSpawned = cs2_dumper::schemas::client_dll::C_SmokeGrenadeProjectile::m_bSmokeEffectSpawned; // bool
	} SmokeGrenadeProjectile;

	namespace Signatures
	{
		/*
				const std::string ForceForward = "48 8D 05 ?? ?? ?? ?? 48 89 05 ?? ?? ?? ?? 48 83 C4 ?? E9 ?? ?? ?? ?? CC CC CC CC CC CC CC CC CC CC 48 81 EC";
				const std::string ForceLeft = "48 8D 05 ?? ?? ?? ?? 48 89 45 ? 48 8D 05 ?? ?? ?? ?? 48 89 45 ?? 48 8D 05 ?? ?? ?? ?? 48 89 45 ?? 4C 6B E3";
				const std::string ForceRight = "48 8D 05 ?? ?? ?? ?? 48 89 45 ? 48 8D 05 ?? ?? ?? ?? 48 89 45 ?? 4C 6B E3";
				const std::string ForceJump = "48 8D 05 ?? ?? ?? ?? 48 89 4D ?? 48 89 45 ?? 48 8D 05 ?? ?? ?? ?? 48 89 45 ?? 48 8D 05 ?? ?? ?? ?? 48 89 45 ?? 48 8D 05 ?? ?? ?? ?? 48 89 45 ?? 48 8D 05 ?? ?? ?? ?? 48 89 45 ?? 48 8D 05 ?? ?? ?? ?? 48 89 45 ?? 48 8D 05 ?? ?? ?? ?? 48 89 45 ?? 4C 6B E3";
				const std::string ForceCrouch = "48 8D 05 ?? ?? ?? ?? 48 89 05 ?? ?? ?? ?? 48 83 C4 ?? E9 ?? ?? ?? ?? CC CC CC CC CC CC CC CC CC CC 48 83 EC ?? 66 C7 44 24";
		*/
		const std::string LocalPlayerPawn = "48 8D 05 ?? ?? ?? ?? C3 CC CC CC CC CC CC CC CC 48 83 EC ?? 8B 0D";
		const std::string InventoryServices = "E8 ?? ?? ?? ?? 8B 45 D0 48 8B 55 D8";
		const std::string GlobalVars = "48 89 15 ?? ?? ?? ?? 48 8D 05 ?? ?? ?? ?? 48 85 D2";
		const std::string EntityList = "48 8B 0D ?? ?? ?? ?? 48 89 7C 24 ?? 8B FA C1 EB";
		const std::string LocalPlayerController = "48 8B 05 ?? ?? ?? ?? 48 85 C0 74 ?? 8B 88";
		const std::string ViewAngles = "48 8B 0D ?? ?? ?? ?? 48 8B 01 48 FF 60 30";
		const std::string ViewMatrix = "48 8D 0D ?? ?? ?? ?? 48 C1 E0 06";
		const std::string PlantedC4 = "48 8B 15 ?? ?? ?? ?? FF C0 48 8D 4C 24 40";
		const std::string InputSystem = "48 89 05 ?? ?? ?? ?? 48 8D 05";
		const std::string dwSensitivity = "48 8B 05 ?? ?? ?? ?? 48 8B 40 ?? F3 41 0F 59 F4";
	}

	bool UpdateOffsets();
}
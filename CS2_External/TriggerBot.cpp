#include "TriggerBot.h"

void TriggerBot::Run(const CEntity& LocalEntity)
{
    DWORD uHandle = ProcessMgr.RAM<DWORD>(LocalEntity.Pawn.Address + Offset::Pawn.iIDEntIndex);
	if (!uHandle)
		return;
	if (uHandle == -1)
		return;

	uintptr_t ListEntry = 0;
	ListEntry = ProcessMgr.TraceAddress(gGame.GetEntityListAddress(), { 0x8 * (uHandle >> 9) + 0x10,0x0 });
	if (ListEntry == 0)
		return;

    uintptr_t PawnAddress = ProcessMgr.RAM<uintptr_t>(ListEntry + 0x78 * (uHandle & 0x1FF));
	if (!PawnAddress)
		return;

	CEntity Entity;
	if (!Entity.UpdatePawn(PawnAddress))
		return;

	bool AllowShoot = false;

	if (MenuConfig::TeamCheck)
		AllowShoot = LocalEntity.Pawn.TeamID != Entity.Pawn.TeamID && Entity.Pawn.Health > 0;
	else
		AllowShoot = Entity.Pawn.Health > 0;

	if (!AllowShoot)
		return;

	static std::chrono::time_point LastTimePoint = std::chrono::steady_clock::now();
	auto CurTimePoint = std::chrono::steady_clock::now();
	if (CurTimePoint - LastTimePoint >= std::chrono::milliseconds(TriggerDelay))
	{
		const bool isAlreadyShooting = GetAsyncKeyState(VK_LBUTTON) < 0;
		if (!isAlreadyShooting)
		{
			mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
			mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
		}

		LastTimePoint = CurTimePoint;
	}
}

#include "Offsets.h"

uintptr_t SearchOffsets(std::string Signature, uintptr_t ModuleAddress)
{
	std::vector<uintptr_t> TempAddressList;
	uintptr_t Address = 0;


	TempAddressList = ProcessMgr.SearchMemory(Signature, ModuleAddress, ModuleAddress + 0x4000000);
	
	if (TempAddressList.size() <= 0)
		return 0;
    auto Offsets = ProcessMgr.RAM<DWORD>(TempAddressList.at(0) + 3);
	if (!Offsets)
		return 0;

	Address = TempAddressList.at(0) + Offsets + 7;
	return Address;
}

bool Offset::UpdateOffsets()
{
	uintptr_t ClientDLL = reinterpret_cast<uintptr_t>(ProcessMgr.GetProcessModuleHandle("client.dll"));
	if (ClientDLL == 0)
		return false;
	
	uintptr_t TempAddress = 0;

	TempAddress = SearchOffsets(Offset::Signatures::EntityList, ClientDLL);
	if (TempAddress == 0)
		return false;

	Offset::EntityList = TempAddress - ClientDLL;

	TempAddress = SearchOffsets(Offset::Signatures::LocalPlayerController, ClientDLL);
	if (TempAddress == 0)
		return false;

	Offset::LocalPlayerController = TempAddress - ClientDLL;

	TempAddress = SearchOffsets(Offset::Signatures::ViewMatrix, ClientDLL);
	if (TempAddress == 0)
		return false;

	Offset::Matrix = TempAddress - ClientDLL;

	TempAddress = SearchOffsets(Offset::Signatures::GlobalVars, ClientDLL);
	if (TempAddress == 0)
		return false;

	Offset::GlobalVars = TempAddress - ClientDLL;

	TempAddress = SearchOffsets(Offset::Signatures::ViewAngles, ClientDLL);
	if (TempAddress == 0)
		return false;
    TempAddress = ProcessMgr.RAM<uintptr_t>(TempAddress);
    if (!TempAddress)
		return false;

	Offset::ViewAngle = TempAddress + 0x6140 - ClientDLL;

	TempAddress = SearchOffsets(Offset::Signatures::LocalPlayerPawn, ClientDLL);
	if (TempAddress == 0)
		return false;

	Offset::LocalPlayerPawn = TempAddress + 0x138 - ClientDLL;

	TempAddress = SearchOffsets(Offset::Signatures::ForceJump, ClientDLL);
	if (TempAddress == 0)
		return false;

	Offset::ForceJump = TempAddress + 0x30 - ClientDLL;	
	return true;
}

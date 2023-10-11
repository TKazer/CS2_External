#include "Offsets.h"
#include "Cheats.h"
#include <iostream>
#include <iomanip>
#include <format>

int main()
{
	auto ProcessStatus = ProcessMgr.Attach("cs2.exe");
	if (ProcessStatus != StatusCode::SUCCEED)
	{
		std::cout << "[ERROR] Failed to attach process, StatusCode:" << ProcessStatus << std::endl;
		goto END;
	}

	if (!Offset::UpdateOffsets())
	{
		std::cout << "[ERROR] Failed to update offsets." << std::endl;
		goto END;
	}

	if (!gGame.InitAddress())
	{
		std::cout << "[ERROR] Failed to call InitAddress()."<< std::endl;
		goto END;
	}

	std::cout << std::format("[Game] Pid:{}\n", ProcessMgr.ProcessID);
	std::cout << std::format("[Game] Client:{:X}\n", gGame.GetClientDLLAddress());

	std::cout << "Offset:" << std::endl;
	std::cout << std::format("--EntityList:{:X}\n", Offset::EntityList);
	std::cout << std::format("--Matrix:{:X}\n", Offset::Matrix);
	std::cout << std::format("--LocalPlayerController:{:X}\n", Offset::LocalPlayerController);
	std::cout << std::format("--ViewAngles:{:X}\n", Offset::ViewAngle);
	std::cout << std::format("--LocalPlayerPawn:{:X}\n", Offset::LocalPlayerPawn);
	std::cout << std::format("--ForceJump:{:X}\n", Offset::ForceJump);

	std::cout << "Runing..." << std::endl;

	try
	{
		Gui.AttachAnotherWindow("Counter-Strike 2", "SDL_app", Cheats::Run);
	}
	catch (OSImGui::OSException& e)
	{
		std::cout << e.what() << std::endl;
	}

END:
	system("pause");
	return 0;
}

#include "Offsets.h"
#include "Cheats.h"
#include "Utils/Format.hpp"
#include "Utils/ConfigSaver.hpp"
#include <iostream>
#include <iomanip>
#include <filesystem>

int main()
{
	MyConfigSaver::SetupConfigDirectory();
	std::cout << "[Config] Current configs directory is set to " << std::filesystem::current_path() << std::endl;

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

	std::cout << Format("[Game] Pid:%d\n", ProcessMgr.ProcessID);
	std::cout << Format("[Game] Client:%llX\n", gGame.GetClientDLLAddress());

	std::cout << "Offset:" << std::endl;
	std::cout << Format("--EntityList:%llX\n", Offset::EntityList);
	std::cout << Format("--Matrix:%llX\n", Offset::Matrix);
	std::cout << Format("--LocalPlayerController:%llX\n", Offset::LocalPlayerController);
	std::cout << Format("--ViewAngles:%llX\n", Offset::ViewAngle);
	std::cout << Format("--LocalPlayerPawn:%llX\n", Offset::LocalPlayerPawn);
	std::cout << Format("--ForceJump:%llX\n", Offset::ForceJump);

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

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "ConfigSaver.hpp"
#include "../MenuConfig.hpp" // Include your global settings header
#include "../TriggerBot.h"
#include "../AimBot.hpp"

namespace MyConfigSaver {

    // Function to save the configuration to a file
    void SaveConfig(const std::string& filename) {
        std::ofstream configFile(filename);
        if (!configFile.is_open()) {
            std::cerr << "Error: Could not open the configuration file." << std::endl;
            return;
        }
       
        // Example: Save global settings to the file
        configFile << "ShowBoneESP " << MenuConfig::ShowBoneESP << std::endl;
        configFile << "TriggerDelay " << TriggerBot::TriggerDelay << std::endl;
        configFile << "ShowBoxESP " << MenuConfig::ShowBoxESP << std::endl;
        configFile << "TriggerHotKey " << MenuConfig::TriggerHotKey << std::endl;
        configFile << "RCSBullet " << AimControl::RCSBullet << std::endl;
        configFile << "ShowHealthBar " << MenuConfig::ShowHealthBar << std::endl;
        configFile << "AimFov " << AimControl::AimFov << std::endl;
        configFile << "FovLineSize " << MenuConfig::FovLineSize << std::endl;
        configFile << "AimBotHotKey " << MenuConfig::AimBotHotKey << std::endl;
        configFile << "ShowLineToEnemy " << MenuConfig::ShowLineToEnemy << std::endl;
        configFile << "RCSScale.x " << AimControl::RCSScale.x << std::endl;
        configFile << "RCSScale.y " << AimControl::RCSScale.y << std::endl;
        configFile << "ShowWeaponESP " << MenuConfig::ShowWeaponESP << std::endl;
        configFile << "Smooth " << AimControl::Smooth << std::endl;
        configFile << "ShowFovLine " << MenuConfig::ShowFovLine << std::endl;
        configFile << "ShowEyeRay " << MenuConfig::ShowEyeRay << std::endl;
        configFile << "ShowPlayerName " << MenuConfig::ShowPlayerName << std::endl;
        configFile << "AimBot " << MenuConfig::AimBot << std::endl;
        configFile << "AimPosition " << MenuConfig::AimPosition << std::endl;
        configFile << "AimPositionIndex " << MenuConfig::AimPositionIndex << std::endl;
        configFile << "HealthBarType " << MenuConfig::HealthBarType << std::endl;
        configFile << "BoneColor " << MenuConfig::BoneColor.Value.x << " " << MenuConfig::BoneColor.Value.y << " " << MenuConfig::BoneColor.Value.z << " " << MenuConfig::BoneColor.Value.w << std::endl;
        configFile << "FovLineColor " << MenuConfig::FovLineColor.Value.x << " " << MenuConfig::FovLineColor.Value.y << " " << MenuConfig::FovLineColor.Value.z << " " << MenuConfig::FovLineColor.Value.w << std::endl;
        configFile << "LineToEnemyColor " << MenuConfig::LineToEnemyColor.Value.x << " " << MenuConfig::LineToEnemyColor.Value.y << " " << MenuConfig::LineToEnemyColor.Value.z << " " << MenuConfig::LineToEnemyColor.Value.w << std::endl;
        configFile << "BoxColor " << MenuConfig::BoxColor.Value.x << " " << MenuConfig::BoxColor.Value.y << " " << MenuConfig::BoxColor.Value.z << " " << MenuConfig::BoxColor.Value.w << std::endl;
        configFile << "EyeRayColor " << MenuConfig::EyeRayColor.Value.x << " " << MenuConfig::EyeRayColor.Value.y << " " << MenuConfig::EyeRayColor.Value.z << " " << MenuConfig::EyeRayColor.Value.w << std::endl;
        configFile << "CrossLineColor " << MenuConfig::CrossLineColor.Value.x << " " << MenuConfig::CrossLineColor.Value.y << " " << MenuConfig::CrossLineColor.Value.z << " " << MenuConfig::CrossLineColor.Value.w << std::endl;
        configFile << "HeadShootLineColor " << MenuConfig::HeadShootLineColor.Value.x << " " << MenuConfig::HeadShootLineColor.Value.y << " " << MenuConfig::HeadShootLineColor.Value.z << " " << MenuConfig::HeadShootLineColor.Value.w << std::endl;
        configFile << "ShowMenu " << MenuConfig::ShowMenu << std::endl;
        configFile << "ShowRadar " << MenuConfig::ShowRadar << std::endl;
        configFile << "RadarRange " << MenuConfig::RadarRange << std::endl;
        configFile << "ShowCrossLine " << MenuConfig::ShowCrossLine << std::endl;
        configFile << "RadarType " << MenuConfig::RadarType << std::endl;
        configFile << "Proportion " << MenuConfig::Proportion << std::endl;
        configFile << "BoxType " << MenuConfig::BoxType << std::endl;
        configFile << "TriggerBot " << MenuConfig::TriggerBot << std::endl;
        configFile << "TeamCheck " << MenuConfig::TeamCheck << std::endl;
		configFile << "VisibleCheck " << MenuConfig::VisibleCheck << std::endl;
        configFile << "ShowHeadShootLine " << MenuConfig::ShowHeadShootLine << std::endl;

        configFile.close();
        std::cout << "Configuration saved to " << filename << std::endl;
    }

    // Function to load the configuration from a file
    void LoadConfig(const std::string& filename) {
        std::ifstream configFile(filename);
        if (!configFile.is_open()) {
            std::cerr << "Error: Could not open the configuration file." << std::endl;
            return;
        }

        std::string line;
        while (std::getline(configFile, line)) {
            std::istringstream iss(line);
            std::string key;
            if (iss >> key) {
                if (key == "ShowBoneESP") iss >> MenuConfig::ShowBoneESP;
                else if (key == "TriggerDelay") iss >> TriggerBot::TriggerDelay;
                else if (key == "ShowBoxESP") iss >> MenuConfig::ShowBoxESP;
                else if (key == "TriggerHotKey") iss >> MenuConfig::TriggerHotKey;
                else if (key == "RCSBullet") iss >> AimControl::RCSBullet;
                else if (key == "ShowHealthBar") iss >> MenuConfig::ShowHealthBar;
                else if (key == "AimFov") iss >> AimControl::AimFov;
                else if (key == "FovLineSize") iss >> MenuConfig::FovLineSize;
                else if (key == "AimBotHotKey") iss >> MenuConfig::AimBotHotKey;
                else if (key == "ShowLineToEnemy") iss >> MenuConfig::ShowLineToEnemy;
                else if (key == "RCSScale.x") iss >> AimControl::RCSScale.x;
                else if (key == "RCSScale.y") iss >> AimControl::RCSScale.y;
                else if (key == "ShowWeaponESP") iss >> MenuConfig::ShowWeaponESP;
                else if (key == "Smooth") iss >> AimControl::Smooth;
                else if (key == "ShowFovLine") iss >> MenuConfig::ShowFovLine;
                else if (key == "ShowEyeRay") iss >> MenuConfig::ShowEyeRay;
                else if (key == "ShowPlayerName") iss >> MenuConfig::ShowPlayerName;
                else if (key == "AimBot") iss >> MenuConfig::AimBot;
                else if (key == "AimPosition") iss >> MenuConfig::AimPosition;
                else if (key == "AimPositionIndex") iss >> MenuConfig::AimPositionIndex;
                else if (key == "HealthBarType") iss >> MenuConfig::HealthBarType;
                else if (key == "BoneColor") iss >> MenuConfig::BoneColor.Value.x >> MenuConfig::BoneColor.Value.y >> MenuConfig::BoneColor.Value.z >> MenuConfig::BoneColor.Value.w;
                else if (key == "FovLineColor") iss >> MenuConfig::FovLineColor.Value.x >> MenuConfig::FovLineColor.Value.y >> MenuConfig::FovLineColor.Value.z >> MenuConfig::FovLineColor.Value.w;
                else if (key == "LineToEnemyColor") iss >> MenuConfig::LineToEnemyColor.Value.x >> MenuConfig::LineToEnemyColor.Value.y >> MenuConfig::LineToEnemyColor.Value.z >> MenuConfig::LineToEnemyColor.Value.w;
                else if (key == "BoxColor") iss >> MenuConfig::BoxColor.Value.x >> MenuConfig::BoxColor.Value.y >> MenuConfig::BoxColor.Value.z >> MenuConfig::BoxColor.Value.w;
                else if (key == "EyeRayColor") iss >> MenuConfig::EyeRayColor.Value.x >> MenuConfig::EyeRayColor.Value.y >> MenuConfig::EyeRayColor.Value.z >> MenuConfig::EyeRayColor.Value.w;
                else if (key == "CrossLineColor") iss >> MenuConfig::CrossLineColor.Value.x >> MenuConfig::CrossLineColor.Value.y >> MenuConfig::CrossLineColor.Value.z >> MenuConfig::CrossLineColor.Value.w;
                else if (key == "HeadShootLineColor") iss >> MenuConfig::HeadShootLineColor.Value.x >> MenuConfig::HeadShootLineColor.Value.y >> MenuConfig::HeadShootLineColor.Value.z >> MenuConfig::HeadShootLineColor.Value.w;
                else if (key == "ShowMenu") iss >> MenuConfig::ShowMenu;
                else if (key == "ShowRadar") iss >> MenuConfig::ShowRadar;
                else if (key == "RadarRange") iss >> MenuConfig::RadarRange;
                else if (key == "ShowCrossLine") iss >> MenuConfig::ShowCrossLine;
                else if (key == "RadarType") iss >> MenuConfig::RadarType;
                else if (key == "Proportion") iss >> MenuConfig::Proportion;
                else if (key == "BoxType") iss >> MenuConfig::BoxType;
                else if (key == "TriggerBot") iss >> MenuConfig::TriggerBot;
                else if (key == "TeamCheck") iss >> MenuConfig::TeamCheck;
				else if (key == "VisibleCheck") iss >> MenuConfig::VisibleCheck;
                else if (key == "ShowHeadShootLine") iss >> MenuConfig::ShowHeadShootLine;
            }
        }

        configFile.close();
        std::cout << "Configuration loaded from " << filename << std::endl;
    }
} // namespace ConfigSaver

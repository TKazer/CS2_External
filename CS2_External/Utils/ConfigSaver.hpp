#pragma once

#include <string>

namespace MyConfigSaver {
    extern void SaveConfig(const std::string& filename);
    extern void LoadConfig(const std::string& filename);
}

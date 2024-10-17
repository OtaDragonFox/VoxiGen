#include "platform.h"

#include "modules/platforms/linux_platform.h"
#include "modules/platforms/windows_platform.h"

const char* Platform::GetName() {
    return "Unknown";
}

bool Platform::CreateFolder(const char* folder_path) {
    return false;
}

std::unique_ptr<Platform> PlatformManager::CreatePlatform() {
#ifdef _WIN32
    return std::make_unique<WindowsPlatform>();
#elif __linux__
    return std::make_unique<LinuxPlatform>();
#else
    return nullptr;  // Unsupported platform
#endif
}

std::unique_ptr<Platform> PlatformManager::current_platform_ = CreatePlatform();
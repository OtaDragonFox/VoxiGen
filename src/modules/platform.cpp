#include "platform.h"

#include "modules/platforms/linux_platform.h"
#include "modules/platforms/windows_platform.h"
#include "modules/logger.h"

#include <filesystem>
#include <fstream>

const char* Platform::GetName() {
    return "Unknown";
}

bool Platform::CreateFolder(const char* folder_path) {
    return std::filesystem::create_directory(folder_path) || std::filesystem::exists(folder_path);
}

std::optional<std::string> Platform::GetFileContentAsString(const char* file_path) {
    if (!std::filesystem::exists(file_path) || !std::filesystem::is_regular_file(file_path)) {
        LOG_WARNG("{} does not exist or is not a file!", file_path);
        return std::nullopt;
    }

    std::ifstream file(file_path);
    if (!file.is_open()) {
        LOG_WARNG("Failed to open file {}", file_path);
        return std::nullopt;
    }

    return std::string((std::istreambuf_iterator(file)), std::istreambuf_iterator<char>());
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
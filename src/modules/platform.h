#pragma once
#include <memory>
#include <string>
#include <optional>

class Platform {
public:
    virtual ~Platform() = default;
    virtual const char* GetName();
    static bool CreateFolder(const char* folder_path);
    static std::optional<std::string> GetFileContentAsString(const char* file_path);
};

class PlatformManager {
public:
    inline static Platform& GetPlatform() { return *current_platform_; }

private:
    static std::unique_ptr<Platform> current_platform_;
    static std::unique_ptr<Platform> CreatePlatform();
};

#define PLATFORM PlatformManager::GetPlatform()
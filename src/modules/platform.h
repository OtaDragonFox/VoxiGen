#pragma once
#include <memory>

class Platform {
 public:
  virtual ~Platform() = default;
  virtual const char* GetName();
  virtual bool CreateFolder(const char* folder_path);
};

class PlatformManager {
 public:
  inline static Platform& GetPlatform() {
    return *current_platform_;
  }

 private:
  static std::unique_ptr<Platform> current_platform_;
  static std::unique_ptr<Platform> CreatePlatform();
};

#define PLATFORM PlatformManager::GetPlatform()
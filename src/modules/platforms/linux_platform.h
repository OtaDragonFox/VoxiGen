#pragma once
#ifdef __linux__

#include "modules/platform.h"

class LinuxPlatform final : public Platform {
public:
    const char* GetName() override;
    // bool CreateFolder(const char* folder_path) override;
};
#endif
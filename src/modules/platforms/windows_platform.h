#pragma once
#ifdef _WIN32
#define WINDOWS_PLATFORM_H

#include "modules/platform.h"

class WindowsPlatform final : public Platform {
public:
    const char* GetName() override;
    bool CreateFolder(const char* folder_path) override;
};

#endif
#include "modules/platforms/windows_platform.h"

#ifdef _WIN32
#include <windows.h>

const char* WindowsPlatform::GetName() {
    return "Windows";
}

bool WindowsPlatform::CreateFolder(const char* folder_path) {
    if (CreateDirectoryA(folder_path, NULL) ||
        GetLastError() == ERROR_ALREADY_EXISTS) {
        return true;
    } else {
        return false;
    }
}
#endif
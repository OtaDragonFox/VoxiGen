#include "modules/platforms/linux_platform.h"

#ifdef __linux__
#include <sys/stat.h>

const char* LinuxPlatform::GetName() {
    return "Linux";
}

// bool LinuxPlatform::CreateFolder(const char* folder_path) {
//     return mkdir(folder_path, 0755) == 0 || errno == EEXIST;
// }
#endif

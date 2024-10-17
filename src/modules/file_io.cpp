#include "file_io.h"
#include "modules/logger.h"
#include <fcntl.h>

void FileIO::LoadTextFromFile(const char* file) {
    int fileFd;
    fileFd = open("test.txt", O_RDONLY);
    if (fileFd == -1) {
        LOG_MESSG("file cant be opened");
    }
}
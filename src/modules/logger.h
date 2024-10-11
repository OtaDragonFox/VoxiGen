#include "../types.h"
#include "spdlog/spdlog.h"


#define LOG_MESSG(...) spdlog::info(__VA_ARGS__)
#define LOG_WARNG(...) spdlog::warn(__VA_ARGS__)
#define LOG_ERROR(...) spdlog::error(__VA_ARGS__)

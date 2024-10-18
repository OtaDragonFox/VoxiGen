#pragma once

#include "../types.h"
#include "spdlog/async.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/rotating_file_sink.h"
#include "spdlog/sinks/stdout_color_sinks.h"

#define LOG_MESSG(...) spdlog::info(__VA_ARGS__)
#define LOG_WARNG(...) spdlog::warn(__VA_ARGS__)
#define LOG_ERROR(...) spdlog::error(__VA_ARGS__)

static void InitLogger() {
    const auto console_sink = std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
    console_sink->set_level(spdlog::level::info);

    const auto file_sink = std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
        "logs/log.txt", 1048576 * 5, 3);  // 5 MB max file size, max 3 files
    file_sink->set_level(spdlog::level::info);

    std::vector<spdlog::sink_ptr> sinks{console_sink, file_sink};
    const auto logger = std::make_shared<spdlog::logger>("voxigen", sinks.begin(), sinks.end());
    logger->set_level(spdlog::level::info);

    set_default_logger(logger);
}
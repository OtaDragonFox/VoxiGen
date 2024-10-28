#include "GameTime.h"
#include <chrono>
#include <thread>
#include "logger.h"

void GameTime::SetFramesPerSecound(int in_fps) {

        if (!(in_fps > 1)) {
        return;
    }
    delta_time = 1.0f / (float)in_fps;
    delta_in_ms = 1000.0f / (float)in_fps;
}

void GameTime::SetFrameRenderStart() {
    start_frame_time = std::chrono::steady_clock::now();
}

void GameTime::CalculateFrameEndDelta() {
    end_frame_time = std::chrono::steady_clock::now();
    std::chrono::duration<float> elapsed = end_frame_time - start_frame_time;

    if ((delta_in_ms - elapsed.count()) > 0) {
        std::this_thread::sleep_for(std::chrono::milliseconds(int64_t(delta_in_ms - elapsed.count() * 1000)));
    } else {
        LOG_ERROR("FRAME TAKES TOO LONG TO RENDER !");
    }

}

void GameTime::__DebugSleepThreadForDebugging(int in_ms) {
    std::this_thread::sleep_for(std::chrono::nanoseconds(in_ms));
}

float& GameTime::GetDeltaTime() {
    return delta_time;
}

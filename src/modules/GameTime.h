#include <chrono>
#include <thread>

class std::chrono::steady_clock::time_point;
class GameTime{
public:
    void SetFramesPerSecound(int in_fps = 60);

    void SetFrameRenderStart();
    void CalculateFrameEndDelta();

    void __DebugSleepThreadForDebugging(int in_ms);

private:
    //Represents the time each frame should take inside the engine. this is for calculating interpolation and so much more
    // This is important so each frame is independent and speed of animations isnt hooked into the framerate
    float delta_time = 0;
    float delta_in_ms = 0;

    std::chrono::steady_clock::time_point start_frame_time;
    std::chrono::steady_clock::time_point end_frame_time;

};
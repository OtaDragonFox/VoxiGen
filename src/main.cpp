#include "main.h"
#include "modules/file_io.h"
#include "modules/game_window.h"
#include "modules/logger.h"
#include "modules/platform.h"
#include "modules/renderer.h"
#include <chrono>
#include <thread>
#include <GLFW/glfw3.h>

#include <iostream>

Application* Application::game_application = nullptr;
using namespace std::chrono_literals;

// Application entry point :P
int main() {
    APP.StartApplication();
}

void Application::StartApplication() {
    InitLogger();
    // LOG_MESSG("welcome to voxigen");
    // LOG_WARNG("welcome to voxigen");
    // LOG_ERROR("welcome to voxigen");
    FileIO::LoadTextFromFile("a");  //-> TODO: this is testing code needs to be reworked later
    if (!SetFrameRate(60))
        return;

    LOG_MESSG(PLATFORM.CreateFolder("test"));

    glfwInit();
    //TODO: look into if we should go a bit newer for some fancy GLFW features :P
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    game_renderer_ = new Renderer();
    game_renderer_->SetupRenderer("Suer Cool GAME!", 400, 400);

    while (is_running_) {
        auto start_frame_time = std::chrono::steady_clock::now();
        //TODO: move time stuff into a custom class

        std::this_thread::sleep_for(std::chrono::nanoseconds(50));
        auto end_frame_time = std::chrono::steady_clock::now();
        std::chrono::duration<float> elapsed = end_frame_time - start_frame_time;

        game_renderer_->OnFrame();

        if (((int)delta_in_ms - elapsed.count() * 1000) > 0) {
            // LOG_MESSG("frame took {0:.3f}ms to process", (elapsed.count() * 1000));
            std::this_thread::sleep_for(std::chrono::milliseconds(int64_t(delta_in_ms - elapsed.count() * 1000)));
        } else {
            LOG_ERROR("FRAME TAKES TOO LONG TO RENDER !");
        }

        if (GameWindow::current_active_windows == 0) {
            LOG_MESSG("All windows where closed.");
            is_running_ = false;
        }
    }
}

bool Application::SetFrameRate(const float frames_sec) {
    if (!(frames_sec > 5)) {
        return false;
    }
    delta_time = 1.0f / frames_sec;
    delta_in_ms = 1000 / frames_sec;

    return true;
}

void Application::RequestShutdown(int reason) {
    //TODO: Log reason -> on crash should log everything to file and provide extra information
}

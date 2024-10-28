#include "main.h"
#include "renderer/game_window.h"
#include "modules/logger.h"
#include "modules/platform.h"
#include "renderer/renderer.h"
#include "modules/GameTime.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include "math/aabb.h"
#include "events/EventSystem.h"
#include "renderer/camera.h"
#include "events/KeyListeners.h"
// 

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

    LOG_MESSG(PLATFORM.CreateFolder("test"));

    game_time = new GameTime();
    game_time->SetFramesPerSecound(30);
    event_system = new GameEventSystem();

    game_renderer_ = new Renderer();
    game_renderer_->SetupRenderer("Suer Cool GAME!", 800, 800);

    Camera* game_cam = new Camera();
    game_cam->SetupCamera();



    while (is_running_) {
        game_time->SetFrameRenderStart();

        

        game_cam->FrameStep(game_time->GetDeltaTime());

        game_renderer_->OnFrame();



        game_time->CalculateFrameEndDelta();


        if (GameWindow::current_active_windows == 0) {
            LOG_MESSG("All windows where closed.");
            is_running_ = false;
        }
    }

    free(game_renderer_);
    free(game_time);
    free(event_system);
}



void Application::RequestShutdown(int reason) {
    //TODO: Log reason -> on crash should log everything to file and provide extra information
}

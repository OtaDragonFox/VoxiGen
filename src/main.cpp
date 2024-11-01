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

Application* Application::m_game_application = nullptr;
using namespace std::chrono_literals;

// Application entry point :P
int main() {
    APP.StartApplication();
}

const ivec2 BASE_RESULUTION(800,800);

void Application::StartApplication() {
    InitLogger();

    m_game_time = new GameTime();
    m_game_time->SetFramesPerSecound(30);
    m_event_system = new GameEventSystem();

    m_game_renderer = new Renderer();
    m_game_renderer->SetupRenderer("Suer Cool GAME!", BASE_RESULUTION);
    m_game_cam = new Camera();
    m_game_cam->SetupCamera(BASE_RESULUTION);

    while (m_is_running) {
        m_game_time->SetFrameRenderStart();
        m_game_cam->FrameStep(m_game_time->GetDeltaTime());
        m_game_renderer->OnFrame();
        m_game_time->CalculateFrameEndDelta();

    }

    free(m_game_renderer);
    free(m_game_time);
    free(m_event_system);
    free(m_game_cam);
}



void Application::RequestShutdown(int reason) {
    m_is_running = false;
    //TODO: add reason why shutdown was initiated

}

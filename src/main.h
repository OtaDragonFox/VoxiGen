#pragma once
class Renderer;
class GameTime;
class GameEventSystem;
class Camera;
class Application {
public:
    void StartApplication();
    //void RegisterApplication();
    //void LoadSettings();

    inline static Application& GetApplication() {
        if (!m_game_application) {
            m_game_application = new (Application);
        }
        return *m_game_application;
    }

    void RequestShutdown(int reason);

    static Application* m_game_application;

    GameEventSystem* m_event_system = nullptr;
    GameTime* m_game_time = nullptr;
    Renderer* m_game_renderer = nullptr;
    Camera* m_game_cam = nullptr;

private:

    bool m_is_running = true;
};

#define APP Application::GetApplication()
#define RENDERER Application::GetApplication().m_game_renderer
#define CAMERA Application::GetApplication().m_game_cam
#define EVENT Application::GetApplication().m_event_system
#define GTIME Application::GetApplication().m_game_time
#define WINDOW Application::GetApplication().m_game_renderer->m_game_window
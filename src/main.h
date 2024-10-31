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
        if (!game_application) {
            game_application = new (Application);
        }
        return *game_application;
    }

    void RequestShutdown(int reason);

    static Application* game_application;
    float zoom_level = 2;

    GameEventSystem* event_system = nullptr;
    GameTime* game_time = nullptr;
    Renderer* game_renderer_ = nullptr;
    Camera* game_cam = nullptr;

private:

    bool is_running_ = true;
};

#define APP Application::GetApplication()
#pragma once
class Renderer;

class Application {
public:
    void StartApplication();
    void RegisterApplication();
    void LoadSettings();

    //TODO: update the wanted update time -> we need to calculate delta time
    bool SetFrameRate(float frames_sec = 60.0);

    inline static Application& GetApplication() {
        if (!game_application) {
            game_application = new (Application);
        }
        return *game_application;
    }

    void RequestShutdown(int reason);

    static Application* game_application;

private:
    //Represents the time each frame should take inside the engine. this is for calculating interpolation and so much more
    // This is important so each frame is independent and speed of animations isnt hooked into the framerate
    float delta_time = 0;
    float delta_in_ms = 0;

    Renderer* game_renderer;
    Renderer* game_renderer2;
    bool is_running = true;
};

#define APP Application::GetApplication()
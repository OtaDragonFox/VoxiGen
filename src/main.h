#pragma once

class Application
{
public:
    Application();

    void StartApplication();
    void RegisterApplication();
    void LoadSettings();

    inline static Application& GetApplication(){
        return *game_application;
    
    }


    void RequestShutdown(int reason);


    static Application* game_application;
private:

    bool is_running = false;


};

#define APP Application::GetApplication()
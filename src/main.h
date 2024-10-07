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

    static Application* game_application;

};

#define APP Application::GetApplication()
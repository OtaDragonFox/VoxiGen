#include <iostream>
#include "main.h"

// Application entry point :P
int main()
{
    APP.StartApplication();
}

Application * Application::game_application = nullptr;
Application::Application()
{
    if(game_application)
    {
        //TODO: error applicaton allready fixend - you dont need two you greedy bean!
    }
    game_application = this;
}

void Application::StartApplication()
{
    std::cout << "hello world!" << std::endl;
    while(true)
    {

    }
}

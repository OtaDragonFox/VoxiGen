#include "main.h"
#include "modules/file_io.h"
#include "modules/logger.h"
#include "modules/platform.h"

#include <iostream>

Application* Application::game_application = nullptr;

// Application entry point :P
int main() {
  APP.StartApplication();
}

Application::Application() {

  if (game_application) {
    //TODO: error applicaton allready fixend - you dont need two you greedy bean!
  }
  game_application = this;
}

void Application::StartApplication() {
  // LOG_MESSG("welcome to voxigen");
  // LOG_WARNG("welcome to voxigen");
  // LOG_ERROR("welcome to voxigen");
  FileIO::LoadTextFromFile("a");

  LOG_MESSG(PLATFORM.CreateFolder("test"));

  //while(is_running)
  //{
  //    //TODO: calculate delta time and setup system sleep based on that so the game doesnt hog all system performance
  //
  //}
}

void Application::RequestShutdown(int reason) {
  //TODO: Log reason -> on crash should log everything to file and provide extra information
}

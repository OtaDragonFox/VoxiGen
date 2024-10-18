#pragma once

class GameWindow;

class Renderer {
public:
    void SetupRenderer(const char* window_name, int in_size_x, int in_size_y);
    void OnFrame();

private:
    GameWindow* game_app_window_ = nullptr;
    GameWindow* game_app_window2_ = nullptr;
};

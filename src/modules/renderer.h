#pragma once

class game_window;

class Renderer{
public:
    void SetupRenderer(const char* window_name, int in_size_x, int in_size_y);
    void OnFrame();
private:
    game_window* game_app_window;
};

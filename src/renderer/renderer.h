#pragma once
#include <types.h>
class GameWindow;

class Renderer {
public:
    void SetupRenderer(const char* in_window_name, ivec2 in_screen_resulution);
    void OnFrame();

    GameWindow* m_game_window;
};

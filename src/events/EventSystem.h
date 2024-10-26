
#pragma once
#include <vector>


class GameWindow;


class GameEventSystem{
public:



//Window event system
//Register window by reference



    std::vector<GameWindow*> game_windows;
    void RegisterWindow(GameWindow* in_game_window);
};
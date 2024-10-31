
#pragma once
#include <vector>
#include "KeyListeners.h"

//class GameWindow;

class GameEventSystem{
public:
    void OnKeyboardKeyEvent(int in_keycode, int in_state);
    void RegisterKeyListener(KeyListeners* in_new_listener);
    void OnMouseKeyEvent(int in_keycode, int in_state);
    void OnScrollCallback(float value);
    //std::vector<GameWindow*> game_windows;
    //void RegisterWindow(GameWindow* in_game_window);

    bool key_states[512] ;
    bool mouse_states[512] ;

    void OnKeyboardKeyEventChange(int in_keycode);

    void OnWindowResizeEvent(int in_size_x, int in_size_y);

private:
    std::vector<KeyListeners*>key_event_listeners;

};
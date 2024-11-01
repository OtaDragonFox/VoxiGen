
#pragma once
#include <vector>
#include "KeyListeners.h"
#include <types.h>

//class GameWindow;

class GameEventSystem{
public:
    void RegisterKeyListener(KeyListeners* in_new_listener);

    // keyboard events
    void OnKeyboardKeyEvent(int in_keycode, int in_state);
    void OnKeyboardKeyEventChange(int in_keycode);


    // mouse events
    void OnMouseKeyEvent(int in_keycode, int in_state);

    void OnScrollCallback(float value);

    // window events
    void OnWindowResizeEvent(const ivec2 in_screen_resulution);


    // system events
    void ShutDownRequest(int in_reason);


    bool key_states[512] ;
    bool mouse_states[512] ;

private:
    std::vector<KeyListeners*>key_event_listeners;
 
};
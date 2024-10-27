#include "EventSystem.h"
#include "../renderer/game_window.h"
#include <modules/logger.h>

void GameEventSystem::OnKeyboardKeyEvent(int in_keycode, int in_state) 
{    
    if(key_states[in_keycode]){
        if(in_state == 0){
            key_states[in_keycode] = 0;
            OnKeyboardKeyEventChange(in_keycode);

        }
    }
    else{
        if(in_state != 0){
            key_states[in_keycode] = 1; 
            OnKeyboardKeyEventChange(in_keycode);
        }
    }
}

void GameEventSystem::RegisterKeyListener(KeyListeners* in_new_listener) {
    key_event_listeners.push_back(in_new_listener);
}

void GameEventSystem::OnKeyboardKeyEventChange(int in_keycode) {
    for(int i = 0; i < key_event_listeners.size(); i++)
    {
        key_event_listeners[i]->OnKeyPress(in_keycode, key_states[in_keycode]);
    }    //notify listeners
}

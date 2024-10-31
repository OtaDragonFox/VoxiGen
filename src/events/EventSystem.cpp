#include "EventSystem.h"
#include "../renderer/game_window.h"
#include <modules/logger.h>
#include "../main.h"
#include "../renderer/camera.h"
#include "../renderer/renderer.h"

void GameEventSystem::OnKeyboardKeyEvent(int in_keycode, int in_state) 
{   
    if(key_states[in_keycode]){
        if(in_state == 0){
            key_states[in_keycode] = 0;
            OnKeyboardKeyEventChange(in_keycode);
                      LOG_MESSG(in_keycode); 
        }
    }
    else{
        if(in_state != 0){
            key_states[in_keycode] = 1; 
            OnKeyboardKeyEventChange(in_keycode);
                      LOG_MESSG(in_keycode); 
        }
    }
}

void GameEventSystem::RegisterKeyListener(KeyListeners* in_new_listener) {
    key_event_listeners.push_back(in_new_listener);
}

void GameEventSystem::OnMouseKeyEvent(int in_keycode, int in_state) {
    for(int i = 0; i < key_event_listeners.size(); i++)
    {
        if (in_state == 0)
        {
           key_event_listeners[i]->OnMouseKeyPress(in_keycode, false);
        }
        else {
key_event_listeners[i]->OnMouseKeyPress(in_keycode, true);
        }
        
        
    }    //notify listeners

}

void GameEventSystem::OnScrollCallback(float value) {
        for(int i = 0; i < key_event_listeners.size(); i++)
    {
        key_event_listeners[i]->OnScrollScallback(value);
    } 
}

void GameEventSystem::OnKeyboardKeyEventChange(int in_keycode) {
    for(int i = 0; i < key_event_listeners.size(); i++)
    {
        key_event_listeners[i]->OnKeyPress(in_keycode, key_states[in_keycode]);
    }    //notify listeners
}

void GameEventSystem::OnWindowResizeEvent(int in_size_x, int in_size_y) {
    APP.game_cam->OnWindowResize(in_size_x, in_size_y);
    APP.game_renderer_->game_app_window_->OnWindowResize(in_size_x, in_size_y);
}



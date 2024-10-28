#pragma once

class KeyListeners{
public:
    virtual void OnKeyPress(int in_keycode, bool in_state){};
    virtual void OnMouseKeyPress(int in_keycode, bool in_state){};
    virtual void OnMouseMove(float in_x_location, float in_y_location) {};

};
#pragma once

#include "../types.h"
#include <events/EventSystem.h>

class Camera : public KeyListeners
{
//void SetCameraLocation(vec3 in_location);
    virtual void OnKeyPress(int in_keycode, int in_state) override;
    virtual void OnMouseKeyPress(int in_keycode, int in_state) override;
    virtual void OnMouseMove(float in_x_location, float in_y_location) override;


public:






    mat4 view_matrix;
};
#include "camera.h"
#include <modules/logger.h>
#include <main.h>


void Camera::OnKeyPress(int in_keycode, int in_state) {
    if(in_keycode)
    {
        LOG_MESSG("Key {} was pressed", in_keycode);
    }
    else{
        LOG_MESSG("Key {} was released", in_keycode);

    }

}

void Camera::OnMouseKeyPress(int in_keycode, int in_state) {}

void Camera::OnMouseMove(float in_x_location, float in_y_location) {}

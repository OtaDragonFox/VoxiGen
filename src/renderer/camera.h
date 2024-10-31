#pragma once

#include "../types.h"
#include <events/EventSystem.h>

class Camera : public KeyListeners
{
public:
    virtual void OnKeyPress(int in_keycode, bool in_state) override;
    virtual void OnMouseKeyPress(int in_keycode, bool in_state) override;
    virtual void OnMouseMove(float in_x_location, float in_y_location) override;
    virtual void OnScrollScallback(float value ) override;
    void SetupCamera(int in_size_x, int in_size_y);

    //Step frame forward in time -> location updates
    void FrameStep(float in_delta_time);

    void OnWindowResize(int in_size_x, int in_size_y);

    const vec3& GetPosition() const { return camera_location; }

    const mat4& GetProjectionMatrix() const { return projection_matrix; }
    const mat4& GetViewMatrix() const { return view_matrix; }
    const mat4& GetViewProjectionMatrix() const { return view_projection_matrix; }



private:
    void RecalculateViewMatrix();

private:

    //originally this camera was derived by https://youtu.be/NjKv-HWstxA
    mat4 projection_matrix;
    mat4 view_matrix;
    mat4 view_projection_matrix;

    vec3 camera_location = vec3(0.0f, 0.0f,0.0f);
    float camera_rotation = 0.0f;

    vec2 window_size;

    vec2 aspect_ratio;
    float camera_zoom_level = 2.0f;

    bool is_forward_held = false;
    bool is_back_held = false;
    bool is_right_held = false;
    bool is_left_held = false;
    vec2 direction{};
    float camera_speed = 1;
};
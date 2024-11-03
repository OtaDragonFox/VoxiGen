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
    void SetupCamera(ivec2 in_screen_resulution);

    //Step frame forward in time -> location updates
    void FrameStep(float in_delta_time);

    void OnWindowResize(const ivec2 in_screen_resulutuion);

    const vec3& GetPosition() const { return m_camera_location; }
    mat4 m_view_projection_matrix;

private:
    void RecalculateViewMatrix();

private:

    //originally this camera was derived by https://youtu.be/NjKv-HWstxA
    mat4 m_projection_matrix;
    mat4 m_view_matrix;

    vec3 m_camera_location = vec3(0.0f, 0.0f,0.0f);
    float m_camera_rotation = 0.0f;

    vec2 m_window_size;

    vec2 m_aspect_ratio;
    float m_camera_zoom_level = 2.0f;

    bool m_is_forward_held = false;
    bool m_is_back_held = false;
    bool m_is_right_held = false;
    bool m_is_left_held = false;
    vec2 m_direction{};
    float m_camera_speed = 1;
};
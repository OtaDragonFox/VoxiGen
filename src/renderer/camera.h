#pragma once

#include "../types.h"
#include <events/EventSystem.h>

class Camera : public KeyListeners
{
public:
    virtual void OnKeyPress(int in_keycode, bool in_state) override;
    virtual void OnMouseKeyPress(int in_keycode, bool in_state) override;
    virtual void OnMouseMove(float in_x_location, float in_y_location) override;
    void SetupCamera();

    //Step frame forward in time -> location updates
    void FrameStep(float in_delta_time);

    //We need position interpolation :3 meaning smooth in and out transits
    //void SetPosition(const vec2 in_position) {
    //    camera_location = vec3(in_position.x, in_position.y, 0);
    //    RecalculateViewMatrix();
    //}


    //might remove this seems a bit uneccesary
    //void SetRotation(float in_rotation) {
    //    camera_rotation = in_rotation;
    //    RecalculateViewMatrix();
    //}

    const vec2& GetPosition() const { return vec2(camera_location.x, camera_location.y); }

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

    vec3 camera_location = vec3(0.0f, 0.0f, 0.0f);
    float camera_rotation = 0.0f;






    bool is_forward_held = false;
    bool is_back_held = false;
    bool is_right_held = false;
    bool is_left_held = false;
    vec2 direction{};
    float camera_speed = 1;
};
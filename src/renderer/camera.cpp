#include "camera.h"
#include <modules/logger.h>
#include <main.h>
#include <GLFW/glfw3.h>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>
#include "renderer/renderer.h"
#include "renderer/shader.h"
#include "renderer/game_window.h"
#include <glm/gtc/matrix_transform.hpp>


void Camera::SetupCamera() {
    float cam_off = 0.250f;

    APP.event_system->RegisterKeyListener(this);
    projection_matrix = glm::ortho(-cam_off, cam_off, -cam_off, cam_off, -1.0f, 1.0f);
    view_matrix = mat4(1.0f);
    RecalculateViewMatrix();


}

void Camera::FrameStep(float in_delta_time) {
    camera_location += vec3(direction.x, direction.y,0) * (camera_speed * in_delta_time);

    RecalculateViewMatrix();


}

void Camera::RecalculateViewMatrix() {
    mat4 transform = glm::translate(mat4(1.0f), camera_location);

    view_matrix = glm::inverse(transform);

    // ORDER IS IMPORTANT FIRST PROJECTION THEN VIEW thank you for listening.
    view_projection_matrix = projection_matrix * view_matrix;
    APP.game_renderer_->game_app_window_->shader_.SetMat4("u_view_projection", view_projection_matrix);


}
//TODO: Add on unfocus to well reset the direction multiply
//Smooth location stuff

//Scroll in out
//fix aspect ration / do updates via our message buffer.

void Camera::OnKeyPress(int in_keycode, bool in_state) {
    if (GLFW_KEY_W == in_keycode){
        LOG_MESSG("");
        is_forward_held = in_state;
    }
    if (GLFW_KEY_S == in_keycode){
        is_back_held = in_state;
    }
    if (GLFW_KEY_A == in_keycode){
        is_left_held = in_state;
    }
    
    if (GLFW_KEY_D == in_keycode){
        is_right_held = in_state;
    }

    //calculate player/camera direction -> :3
    direction = vec2(is_right_held - is_left_held,is_forward_held-is_back_held);

    glm::normalize(direction);

}

void Camera::OnMouseKeyPress(int in_keycode, bool in_state) {}

void Camera::OnMouseMove(float in_x_location, float in_y_location) {}



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


void Camera::SetupCamera(int in_size_x, int in_size_y) {
    camera_zoom_level = 2;
    view_matrix = mat4(1.0f);
    APP.event_system->RegisterKeyListener(this);
    OnWindowResize(in_size_x, in_size_y);


}

void Camera::FrameStep(float in_delta_time) {
    camera_location += vec3(direction.x, direction.y,0) * (camera_speed * in_delta_time);
    RecalculateViewMatrix();

 
}

void Camera::OnWindowResize(int in_size_x, int in_size_y) {
    window_size.x = in_size_x;
    window_size.y = in_size_y;

    if(in_size_x == in_size_y){
        aspect_ratio = vec2(1.0f,1.0f);
    }
    else{

        if(in_size_x > in_size_y)
        {
            aspect_ratio.x = 1.0f;
            aspect_ratio.y = (float)in_size_y / (float)in_size_x;
        }
        else
        {
            aspect_ratio.x = (float)in_size_x / (float)in_size_y;
            aspect_ratio.y = 1.0f;

        }
    }
    
    projection_matrix = glm::ortho(
        -aspect_ratio.x * camera_zoom_level, 
        aspect_ratio.x * camera_zoom_level, 
        -aspect_ratio.y * camera_zoom_level, 
        aspect_ratio.y * camera_zoom_level, 
        -1.0f, 
        1.0f);
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
    direction = vec2((float)is_right_held - (float)is_left_held,(float)is_forward_held-(float)is_back_held);

    glm::normalize(direction);

}

void Camera::OnMouseKeyPress(int in_keycode, bool in_state) {
    LOG_MESSG(in_keycode);

}

void Camera::OnMouseMove(float in_x_location, float in_y_location) {}

void Camera::OnScrollScallback(float value) {

    camera_zoom_level += value*0.1f;
        projection_matrix = glm::ortho(
        -aspect_ratio.x * camera_zoom_level, 
        aspect_ratio.x * camera_zoom_level, 
        -aspect_ratio.y * camera_zoom_level, 
        aspect_ratio.y * camera_zoom_level, 
        -1.0f, 
        1.0f);
    RecalculateViewMatrix();
    
}

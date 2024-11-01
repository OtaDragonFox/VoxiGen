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


void Camera::SetupCamera(ivec2 in_screen_resulution) {
    m_camera_zoom_level = 2;
    m_view_matrix = mat4(1.0f);
    EVENT->RegisterKeyListener(this);
    OnWindowResize(in_screen_resulution);


}

void Camera::FrameStep(float in_delta_time) {
    m_camera_location += vec3(m_direction.x, m_direction.y,0) * (m_camera_speed * in_delta_time);
    RecalculateViewMatrix();

 
}

void Camera::OnWindowResize(const ivec2 in_screen_resulutuion) {
    m_window_size = in_screen_resulutuion;

    if(m_window_size.x == m_window_size.y){
        m_aspect_ratio = vec2(1.0f,1.0f);
    }
    else{

        if(m_window_size.x > m_window_size.y)
        {
            m_aspect_ratio.x = 1.0f;
            m_aspect_ratio.y = (float)m_window_size.y / (float)m_window_size.x;
        }
        else
        {
            m_aspect_ratio.x = (float)m_window_size.x / (float)m_window_size.y;
            m_aspect_ratio.y = 1.0f;

        }
    }
    
    m_projection_matrix = glm::ortho(
        -m_aspect_ratio.x * m_camera_zoom_level, 
        m_aspect_ratio.x * m_camera_zoom_level, 
        -m_aspect_ratio.y * m_camera_zoom_level, 
        m_aspect_ratio.y * m_camera_zoom_level, 
        -1.0f, 
        1.0f);
    RecalculateViewMatrix();
}

void Camera::RecalculateViewMatrix() {
    mat4 transform = glm::translate(mat4(1.0f), m_camera_location);

    m_view_matrix = glm::inverse(transform);

    // ORDER IS IMPORTANT FIRST PROJECTION THEN VIEW thank you for listening.
    m_view_projection_matrix = m_projection_matrix * m_view_matrix;
    WINDOW->shader_.SetMat4("u_view_projection", m_view_projection_matrix);


}
//TODO: Add on unfocus to well reset the direction multiply
//Smooth location stuff

//Scroll in out
//fix aspect ration / do updates via our message buffer.

void Camera::OnKeyPress(int in_keycode, bool in_state) {
    if (GLFW_KEY_W == in_keycode){
        m_is_forward_held = in_state;
    }
    if (GLFW_KEY_S == in_keycode){
        m_is_back_held = in_state;
    }
    if (GLFW_KEY_A == in_keycode){
        m_is_left_held = in_state;
    }
    
    if (GLFW_KEY_D == in_keycode){
        m_is_right_held = in_state;
    }

    //calculate player/camera direction -> :3
    m_direction = vec2((float)m_is_right_held - (float)m_is_left_held,(float)m_is_forward_held-(float)m_is_back_held);


}

void Camera::OnMouseKeyPress(int in_keycode, bool in_state) {
    LOG_MESSG(in_keycode);

}

void Camera::OnMouseMove(float in_x_location, float in_y_location) {}

void Camera::OnScrollScallback(float value) {

    m_camera_zoom_level += value*0.1f;
        m_projection_matrix = glm::ortho(
        -m_aspect_ratio.x * m_camera_zoom_level, 
        m_aspect_ratio.x * m_camera_zoom_level, 
        -m_aspect_ratio.y * m_camera_zoom_level, 
        m_aspect_ratio.y * m_camera_zoom_level, 
        -1.0f, 
        1.0f);
    RecalculateViewMatrix();
    
}

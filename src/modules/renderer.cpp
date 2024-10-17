#include "renderer.h"
#include "game_window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
void Renderer::SetupRenderer(const char* window_name, int in_size_x, int in_size_y) 
{
    glfwInit();
    //TODO: look into if we should go a bit newer for some fancy GLFW features :P
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    game_app_window = new(game_window);
    game_app_window->SetupWindow(window_name,in_size_x,in_size_y);
}

void Renderer::OnFrame() 
{
    game_app_window->OnFrameRender();
}


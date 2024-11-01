#include "renderer.h"
#include "game_window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Renderer::SetupRenderer(const char* in_window_name, ivec2 in_screen_resulution) {
    
    //GLFW code should stay inside the renderer. 
    glfwInit();
    //TODO: look into if we should go a bit newer for some fancy GLFW features :P
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    m_game_window = new(GameWindow);
    m_game_window->SetupWindow(in_window_name,in_screen_resulution);
}

int Renderer::RegisterMesh(Mesh* in_new_mesh) {
    m_mesh_list.push_back(in_new_mesh);
    return (m_mesh_list.size()-1);
}

void Renderer::OnFrame() {
    m_game_window->StartRenderFrame();
    m_game_window->EndRenderFrame();
}

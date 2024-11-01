#include "game_window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "../modules/logger.h"
#include <main.h>
#include <events/EventSystem.h>
#include <types.h>

// calllbacks 
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    EVENT->OnKeyboardKeyEvent(key, action);
}
void FramebufferResizeCallback(GLFWwindow* window, int width, int height)
{
    EVENT->OnWindowResizeEvent(ivec2(width,height));
}
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    EVENT->OnMouseKeyEvent(button, action);
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    EVENT->OnScrollCallback(yoffset);
}

void window_close_callback(GLFWwindow* window)
{
    EVENT->ShutDownRequest(1);
}  

// Class implementations

void GameWindow::SetupWindow(const char* in_window_name,const ivec2 in_screen_size) {
    m_screen_size = in_screen_size;
    if (m_screen_size.x == 0 || m_screen_size.y == 0) {
        LOG_ERROR("WINDOW SIZE CANT BE 0 !!!! Please fix -> Error might have occured by passing screen value");
        glfwTerminate();
        return;
    }

    m_application_window = glfwCreateWindow(m_screen_size.x, m_screen_size.y, in_window_name, NULL, NULL);
    if (!m_application_window) {
        LOG_ERROR(
            "GLFWWindow failed to be created. -> Maybe try updating your video card driver if you havent done that in "
            "the past 10 years or create a issue on github");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(m_application_window);

    SetupWindowCallbacks();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR("Glad failed to initialize -> something went wrong in the Glad Loading process.");
        glfwTerminate();
        return;
    }


    // tmp for testing
    shader_ = Shader();
    if (shader_.LoadShaderFromPath("assets/shader/test.glsl")) {
        LOG_MESSG("Shader loaded");
    }
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    constexpr float vertices[] = {
        0.5f,  0.5f,  0.0f,  // top right
        0.5f,  -0.5f, 0.0f,  // bottom right
        -0.5f,  -0.5f, 0.0f,  // bottom left

        -0.5f, -0.5f, 0.0f,  // bottom left
        -0.5f, 0.5f,  0.0f,  // top left
        0.5f, 0.5f,  0.0f,  // top right
    };
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);  // location 0
    glEnableVertexAttribArray(0);
}

void GameWindow::SetupWindowCallbacks() {
    glfwSetFramebufferSizeCallback(m_application_window, FramebufferResizeCallback);
    glfwSetKeyCallback(m_application_window, key_callback);
    glfwSetMouseButtonCallback(m_application_window, mouse_button_callback);
    glfwSetScrollCallback(m_application_window, scroll_callback);
    glfwSetWindowCloseCallback(m_application_window, window_close_callback);
}


void GameWindow::DestroyWindow() const {
    glfwDestroyWindow(m_application_window);
}

void GameWindow::StartRenderFrame() {
    glClearColor(0.76f, 0.76f, 0.09f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT );

}

void GameWindow::EndRenderFrame() {
    shader_.UseProgram();
    shader_.SetTimeUniform();
    const int resolution_uniform_location = glGetUniformLocation(shader_.GetProgram(), "resolution");  //todo: cache glGetUniformLocation
    glUniform2f(resolution_uniform_location, static_cast<float>(m_screen_size.x), static_cast<float>(m_screen_size.y));

    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers(m_application_window);
    glfwPollEvents();
}

void GameWindow::OnWindowResize(const ivec2 in_screen_size) {
    glViewport(0, 0, in_screen_size.x, in_screen_size.y);
    m_screen_size = in_screen_size;
}

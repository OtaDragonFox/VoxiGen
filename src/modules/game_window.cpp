#include "game_window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "logger.h"

std::atomic<unsigned int> GameWindow::current_active_windows{0};

void GameWindow::SetupWindow(const char* window_name, const int in_size_x, const int in_size_y) {
    size_x = in_size_x;
    size_y = in_size_y;

    if (size_x == 0 || size_y == 0) {
        LOG_ERROR("WINDOW SIZE CANT BE 0 !!!! Please fix -> Error might have occured by passing screen value");
        glfwTerminate();
        return;
    }

    application_window = glfwCreateWindow(size_x, size_y, window_name, NULL, NULL);
    if (!application_window) {
        LOG_ERROR(
            "GLFWWindow failed to be created. -> Maybe try updating your video card driver if you havent done that in "
            "the past 10 years or create a issue on github");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(application_window);

    SetupWindowCallbacks();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        LOG_ERROR("Glad failed to initialize -> something went wrong in the Glad Loading process.");
        glfwTerminate();

        return;
    }
    current_active_windows += 1;

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
    glfwSetFramebufferSizeCallback(application_window, FramebufferResizeCallback);
}

void GameWindow::OnFrameRender() {
    glfwMakeContextCurrent(application_window);
    glClearColor(0.76f, 0.76f, 0.09f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader_.UseProgram();
    shader_.SetTimeUniform();
    const int resolution_uniform_location = glGetUniformLocation(shader_.GetProgram(), "resolution");  //todo: cache glGetUniformLocation
    glUniform2f(resolution_uniform_location, static_cast<float>(size_x), static_cast<float>(size_y));

    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, 6);

    glfwSwapBuffers(application_window);
    glfwPollEvents();
}

void GameWindow::DestroyWindow() const {
    glfwDestroyWindow(application_window);
    current_active_windows -= 1;
}

bool GameWindow::WindowShouldClose() const {
    return glfwWindowShouldClose(application_window);
}

void GameWindow::FramebufferResizeCallback(GLFWwindow* window, const int width, const int height) {
    glfwMakeContextCurrent(window); // save old context?
    glViewport(0, 0, width, height);
}
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
}

void GameWindow::SetupWindowCallbacks() {
    glfwSetFramebufferSizeCallback(application_window, FramebufferResizeCallback);
    glfwSetWindowCloseCallback(application_window, WindowCloseCallback);
}

void GameWindow::OnFrameRender() {
    glfwMakeContextCurrent(application_window);
    glClearColor(0.76f, 0.76f, 0.09f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(application_window);
    glfwPollEvents();
}

void GameWindow::DestroyWindow() const {
    glfwDestroyWindow(application_window);
}

bool GameWindow::WindowShouldClose() const {
    return glfwWindowShouldClose(application_window);
}

void GameWindow::FramebufferResizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void GameWindow::WindowCloseCallback(GLFWwindow* window) {
    current_active_windows -= 1;
}

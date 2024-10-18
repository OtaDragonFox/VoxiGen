#pragma once
#include "render/shader.h"
#include <atomic>

class GLFWwindow;

class GameWindow {
public:
    void SetupWindow(const char* window_name, int in_size_x, int in_size_y);
    void SetupWindowCallbacks();

    void OnFrameRender();
    void DestroyWindow() const;

    [[nodiscard]] bool WindowShouldClose() const;

    static std::atomic<unsigned int> current_active_windows;

private:
    GLFWwindow* application_window = nullptr;
    int size_x = 0, size_y = 0;

    // tmp for testing
    Shader shader_;
    unsigned int vao_ = 0, vbo_ = 0;

    static void FramebufferResizeCallback(GLFWwindow* window, int width, int height);
};
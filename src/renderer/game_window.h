#pragma once
#include "shader.h"

struct GLFWwindow;

class GameWindow {
public:
    void SetupWindow(const char* in_window_name,const ivec2 in_screen_size);
    void SetupWindowCallbacks();

    void DestroyWindow() const;

    //Start the render process so we can inject model rendering and other logic inbetween start and end.
    void StartRenderFrame();

    //End of the frame render process dealing with input and swapping the buffer.
    void EndRenderFrame();


    GLFWwindow* m_application_window = nullptr;
    ivec2 m_screen_size{};
    
    // tmp for testing
    Shader shader_;
    unsigned int vao_ = 0, vbo_ = 0;
    void OnWindowResize(const ivec2 in_screen_size);
};
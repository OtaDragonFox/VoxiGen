#pragma once

class GLFWwindow;
class game_window{
public:
    void SetupWindow(const char* window_name, int in_size_x, int in_size_y);
    void SetupWindowCallbacks();

    void OnFrameRender();
    

private:
    GLFWwindow* application_window;
    int size_x, size_y = 0;




};

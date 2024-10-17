#include "game_window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "logger.h"


void game_window::SetupWindow(const char* window_name, int in_size_x,int in_size_y) 
{
    size_x = in_size_x;
    size_y = in_size_y;

    if(size_x == 0 || size_y == 0)
    {
        LOG_ERROR("WINDOW SIZE CANT BE 0 !!!! Please fix -> Error might have occured by passing screen value");
        glfwTerminate();
        return;
    }

    application_window = glfwCreateWindow(size_x,size_y, window_name, NULL, NULL);
    if(!application_window)
    {
        LOG_ERROR("GLFWWindow failed to be created. -> Maybe try updating your video card driver if you havent done that in the past 10 years or create a issue on github");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(application_window);

    SetupWindowCallbacks();

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        LOG_ERROR("Glad failed to initialize -> something went wrong in the Glad Loading process.");
        glfwTerminate();
          
        return;
    }

}

void game_window::SetupWindowCallbacks() {}

void game_window::OnFrameRender() 
{
    glClearColor(0.76f,0.76f, 0.09f,0.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glfwSwapBuffers(application_window);
    glfwPollEvents();

}

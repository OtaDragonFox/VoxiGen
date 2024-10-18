#include "renderer.h"
#include "game_window.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Renderer::SetupRenderer(const char* window_name, const int in_size_x, const int in_size_y) {
    game_app_window_ = new GameWindow();
    game_app_window_->SetupWindow(window_name, in_size_x, in_size_y);

    game_app_window2_ = new GameWindow();
    game_app_window2_->SetupWindow(window_name, in_size_x, in_size_y);
}

void Renderer::OnFrame() {
    if (game_app_window_) {
        game_app_window_->OnFrameRender();
        if (game_app_window_->WindowShouldClose()) {
            game_app_window_->DestroyWindow();
            game_app_window_ = nullptr;
        }
    }

    if (game_app_window2_) {
        game_app_window2_->OnFrameRender();
        if (game_app_window2_->WindowShouldClose()) {
            game_app_window2_->DestroyWindow();
            game_app_window2_ = nullptr;
        }
    }
}

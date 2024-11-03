#pragma once
#include <types.h>
#include "Shader.h"
#include "mesh.h"
class GameWindow;

class Renderer {
public:
    void SetupRenderer(const char* in_window_name, ivec2 in_screen_resulution);
    int RegisterMesh(Mesh* in_new_mesh);

    void OnFrame();

    GameWindow* m_game_window;

    Mesh m_test_mesh;
    Shader m_test_shader;
    std::vector<Mesh*> m_mesh_list;
    std::vector<Shader*> m_shader_list;
};

#include "mesh.h"
#include <modules/logger.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

void Mesh::RegisterMesh(int in_num_quads, bool in_generate_uvs) {
    m_num_indicies = in_num_quads * 6;
    m_indicies = new int [m_num_indicies];
    m_num_verticies = in_num_quads+4;
    m_verticies = new vec3 [m_num_verticies];
    if(in_generate_uvs)
    {
        m_num_uvs = in_num_quads * 4;
        m_uvs = new vec2 [m_num_uvs];
    }

    m_is_mesh_registered = true;


}

void Mesh::SetQuadData(int in_index, const vec3 in_corners[4], bool in_enable_uvs, const vec2 in_uvs[4]) {
    int in_vertex_start_index = in_index * 4;
    int in_indicies_start_index = in_index * 6;

    for(int i = 0; i < 4; i++){
        SetVertexElement(in_vertex_start_index + i, in_corners[i]);
        if (in_enable_uvs)
        {
            SetUvElement(in_vertex_start_index+i, in_uvs[i]);
        }
        
    }
    SetIndexElement(in_indicies_start_index + 0, in_indicies_start_index + 0);
    SetIndexElement(in_indicies_start_index + 1, in_indicies_start_index + 1);
    SetIndexElement(in_indicies_start_index + 2, in_indicies_start_index + 2);
    SetIndexElement(in_indicies_start_index + 3, in_indicies_start_index + 1);
    SetIndexElement(in_indicies_start_index + 4, in_indicies_start_index + 3);
    SetIndexElement(in_indicies_start_index + 5, in_indicies_start_index + 2);


}

void Mesh::OnPrepareMesh() {
    if(!m_is_mesh_registered && !m_is_mesh_prepared)
    {
        LOG_ERROR("Mesh isnt Registered");
        return;
    }

}

void Mesh::OnMeshRender() {
    if(!m_is_mesh_registered && !m_is_mesh_prepared)
    {
        LOG_ERROR("Mesh isnt Registered");
        return;
    }
    glGenVertexArrays(1, &m_VBO);
    glGenBuffers(1, &m_VAO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ARRAY_BUFFER, m_num_verticies * sizeof(vec3), m_verticies, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_num_indicies * sizeof(int), m_indicies, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);


}


void Mesh::OnDestroy() {
    delete(m_verticies);
    delete(m_indicies);
    delete(m_uvs);
}

void Mesh::SetMeshLocation(vec3 in_location) {

}


void Mesh::SetVertexElement(int in_index, vec3 in_vertex_data) {
    if(in_index >= m_num_verticies){
        LOG_ERROR("Index is out of Range! index: {} max: {}", in_index, m_num_verticies-1);
        return;
    }
    m_verticies[in_index] = in_vertex_data;
}

void Mesh::SetIndexElement(int in_index, int in_index_data) {
    if(in_index >= m_num_indicies){
        LOG_ERROR("Index is out of Range! index: {} max: {}", in_index, m_num_indicies-1);
        return;
    }
    m_indicies[in_index] = in_index_data;
}

void Mesh::SetUvElement(int in_index, vec2 in_uv_data) {
    if(in_index >= m_num_uvs){
        LOG_ERROR("Index is out of Range! index: {} max: {}", in_index, m_num_uvs-1);
        return;
    }
    m_uvs[in_index] = in_uv_data;
}

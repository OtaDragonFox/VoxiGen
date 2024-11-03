#include "mesh.h"
#include <modules/logger.h>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <main.h>
#include <renderer/renderer.h>
#include <renderer/camera.h>

void Mesh::ReserveMeshData(unsigned int in_num_of_polgyons) {
    m_number_of_elements = in_num_of_polgyons;
    m_polygons = new PolygonElement[in_num_of_polgyons];
    m_indicies = new IndexElement[in_num_of_polgyons];

    LOG_MESSG("Registered {} Polygons of data", in_num_of_polgyons);
    m_has_data_reserved = true;
}

void Mesh::SetPolygonData(unsigned int in_index, const PolygonElement in_polygon) {
    if(in_index >= m_number_of_elements || !m_has_data_reserved){
        LOG_ERROR("Accessed index out of bounds Max index is {} Access being tried to access is {}",m_number_of_elements-1,in_index);
    }
    m_polygons[in_index] = in_polygon;
    unsigned int in_starting_index = in_index* 6;
    m_indicies[in_index].m_elements[0] = in_starting_index + 0;
    m_indicies[in_index].m_elements[1] = in_starting_index + 1;
    m_indicies[in_index].m_elements[2] = in_starting_index + 2;
    m_indicies[in_index].m_elements[3] = in_starting_index + 1;
    m_indicies[in_index].m_elements[4] = in_starting_index + 3;
    m_indicies[in_index].m_elements[5] = in_starting_index + 2;
}

void Mesh::PrepareMesh(int in_shader_id) {
    if(!m_has_data_reserved){
        LOG_ERROR("Mesh has no data reserved!");
        return;
    }
    m_material_index = in_shader_id;
    glGenVertexArrays(1, &m_VAO);
    glGenBuffers(1, &m_VBO);
    glGenBuffers(1, &m_EBO);

    glBindVertexArray(m_VAO);

    glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
    glBufferData(GL_ARRAY_BUFFER, m_number_of_elements * sizeof(PolygonElement), m_polygons, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_number_of_elements * sizeof(IndexElement), m_indicies, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexElement), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(VertexElement), (void*)(sizeof(vec3)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);   
    m_is_mesh_prepared = true;
}

void Mesh::SetMeshLocation(vec3 in_location) {
    m_mesh_transform = glm::translate(mat4(1), in_location);

}

void Mesh::RenderMesh() {
    if(!m_is_mesh_prepared && !m_has_data_reserved){
        LOG_ERROR("Mesh is not ready to be rendered Data_reserved {},Mesh_prepared {}!", m_has_data_reserved, m_is_mesh_prepared);
        return;
    }
    RENDERER->m_test_shader.UploadMat4("u_view_projection", CAMERA->m_view_projection_matrix);

    glBindVertexArray(m_VAO);
    glDrawElements(GL_TRIANGLES, m_number_of_elements * 6, GL_UNSIGNED_INT, 0);
}

void Mesh::OnDestroy() {

    delete(m_polygons);
    delete(m_indicies);

}

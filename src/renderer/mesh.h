#pragma Once

struct Polygon{
    vec3 m_corners[4];

    Polygon(vec3 in_top_left_corner, vec3 in_top_right_corner, vec3 in_bottom_left_corner, vec3 in_bottom_right_corner){
        m_corners[0] = in_top_left_corner;
        m_corners[1] = in_top_right_corner;
        m_corners[2] = in_bottom_left_corner;
        m_corners[3] = in_bottom_right_corner;
    }
};

struct UVVertex{
    vec3 m_location;
    vec2 m_uv;

    UVVertex(vec3 in_location, vec2 in_uv){
        m_location = in_location;
        m_uv = in_uv;
    }
};

struct UVPolygon{
    UVVertex m_corners[4];

    UVPolygon(UVVertex in_top_left_corner, UVVertex in_top_right_corner, UVVertex in_bottom_left_corner, UVVertex in_bottom_right_corner){
        m_corners[0] = in_top_left_corner;
        m_corners[1] = in_top_right_corner;
        m_corners[2] = in_bottom_left_corner;
        m_corners[3] = in_bottom_right_corner;
    }
};


#include <types.h>

class Mesh {
    void RegisterMesh(int in_num_quads, bool in_generate_uvs);

    void OnMeshRender();
    void SetupMesh(int m_material_index);
    void SetQuadData(int in_index,const vec3 in_corners[4], bool in_enable_uvs = false, const vec2 in_uvs[4] = 0);
    void OnPrepareMesh();
    void OnDestroy();
    void SetMeshLocation(vec3 in_location);


private:
    void SetVertexElement(int in_index, vec3 in_vertex_data);

    void SetIndexElement(int in_index, int in_index_data);

    void SetUvElement(int in_index, vec2 in_uv_data);

    // we should make a custom allocator ngl. this is kinda messy

    int m_num_indicies;
    int m_num_verticies;
private:
    bool m_is_mesh_registered = false;
    bool m_is_mesh_prepared = false;
    int* m_indicies;
    // Use these with simple verticies
    vec3* m_verticies;
    // Use these with verticies including uvs

    mat4 m_mesh_matrix = mat4(1);

    unsigned int m_VBO, m_VAO, m_EBO;

    int m_material_index = -1;
};
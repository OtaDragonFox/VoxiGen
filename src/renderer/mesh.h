#pragma Once
#include <types.h>

struct VertexElement{
    vec3 m_location{} ;
    vec2 m_uv{};

    VertexElement(vec3 in_location, vec2 in_uv = vec2{}){
        m_location = in_location;
        m_uv = in_uv;
    }
    VertexElement(){

    }
};

struct PolygonElement{
    VertexElement m_corners[4];

    PolygonElement(
        VertexElement in_top_left_corner = VertexElement(), 
        VertexElement in_top_right_corner= VertexElement(), 
        VertexElement in_bottom_left_corner= VertexElement(), 
        VertexElement in_bottom_right_corner= VertexElement())
    {
        m_corners[0] = in_top_left_corner;
        m_corners[1] = in_top_right_corner;
        m_corners[2] = in_bottom_left_corner;
        m_corners[3] = in_bottom_right_corner;
    }
};
struct IndexElement{
    int m_elements[6] = {};

    IndexElement(){

    };
};

#include <types.h>

class Mesh {
public:
    void ReserveMeshData(unsigned int in_num_of_polgyons);
    void SetPolygonData(unsigned int in_index, const PolygonElement in_polygon);    
    void PrepareMesh(int in_shader_id);
    
    void SetMeshLocation(vec3 in_location);


    void RenderMesh();


    


    void OnDestroy();

private:
    //We have two structures one is the index list which is 6 ints
    //We also have a polgon struct which includes 4 vertices
    //TOP LEFT - TOP RRIGHT - BOTTOM LEFT - BOTTOM RIGHT
    unsigned int m_number_of_elements = 0;
    bool m_has_data_reserved = false;
    bool m_is_mesh_prepared = false;
    PolygonElement* m_polygons;
    IndexElement* m_indicies;

    mat4 m_mesh_transform = mat4(1);

    int m_material_index = 0;

    unsigned int m_VBO, m_VAO, m_EBO;
};
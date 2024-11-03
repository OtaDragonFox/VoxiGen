#pragma once
#include <types.h>

class Shader{
    public:
    bool LoadShaderFile(const char* in_shader_path);

    void UseProgram() const;    
    unsigned int GetProgram()const;
    void UploadBool(const char* in_name, bool in_value) const;
    void UploadInt(const char* in_name, int in_value) const;
    void UploadFloat(const char* in_name, float in_value) const;

    void UploadVec2(const char* in_name, vec2 &in_value) const;
    void UploadVec3(const char* in_name, vec3 &in_value) const;
    void UploadVec4(const char* in_name, vec4 &in_value) const;

    void UploadMat2(const char* in_name, mat2 &in_value) const;
    void UploadMat3(const char* in_name, mat3 &in_value) const;
    void UploadMat4(const char* in_name, mat4 &in_value) const;

private:
    bool m_is_compiled = false;
    unsigned int m_shader_id = 0;

};
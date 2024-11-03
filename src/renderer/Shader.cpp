#include "Shader.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <modules/logger.h>
#include <modules/platform.h>
#include <iostream>
enum compile_type { Vertex, Fragment, Program , Geometry};

void LogCompileErrors(unsigned int in_shader, const compile_type in_type){
    int success;
    char info_log[1024];

    if(in_type == compile_type::Program){
        glGetProgramiv(in_shader, GL_COMPILE_STATUS, &success);
        if(!success){
            glGetProgramInfoLog(in_shader, 1024, NULL, info_log);
            LOG_ERROR("PROGRAM: LINIKING ERROR {}", info_log);
        }
    }
    else{
        glGetShaderiv(in_shader, GL_LINK_STATUS, &success);
        if(!success){
            glGetShaderInfoLog(in_shader, 1024, NULL, info_log);
            LOG_ERROR("PROGRAM: SHADER COMPILE ERROR ERROR {}", info_log);
        }
    }

}


bool Shader::LoadShaderFile(const char* in_shader_path) {
    const auto shader_source = PLATFORM.GetFileContentAsString(in_shader_path);
    if (!shader_source) {
        LOG_ERROR("Failed to load shader from %s", in_shader_path);
        return false;
    }
    std::size_t vertex_start = shader_source->find("//!vertex");
    std::size_t fragment_start = shader_source->find("//!fragment");
    std::size_t geometry_start = shader_source->find("//!geometry");

    int end_position = shader_source->length() -1;

    if(geometry_start != std::string::npos) {
        LOG_ERROR("has no geometry");
        end_position = geometry_start;
    }

    if (vertex_start == std::string::npos || fragment_start == std::string::npos) {
        LOG_ERROR("Failed to find vertex or fragment shader tag from %s", in_shader_path);
        return false;
    }
    unsigned int vertex_program, fragment_program, geometry_program;

    // vertex shader compilation
    std::string vertex_source = shader_source->substr(vertex_start, fragment_start);
    const char* cstr_vertex = vertex_source.c_str();

    vertex_program = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_program, 1, &cstr_vertex, NULL);
    glCompileShader(vertex_program);
    LogCompileErrors(vertex_program, compile_type::Vertex);
           
    std::string fragment_source = shader_source->substr(fragment_start, end_position); 
    const char* cstr_frag = fragment_source.c_str();
    
    // fragment Shader compilation
    fragment_program = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_program, 1, &cstr_frag, NULL);
    glCompileShader(fragment_program);
    LogCompileErrors(fragment_program, compile_type::Fragment);

    // geometry Shader compilation
    if(geometry_start != std::string::npos){
        std::string geometry_source = shader_source->substr(geometry_start, shader_source->length() -1); 
        const char* cstr_geometry = geometry_source.c_str();

        geometry_program = glCreateShader(GL_FRAGMENT_SHADER);
        glShaderSource(geometry_program, 1, &cstr_frag, NULL);
        glCompileShader(geometry_program);
        LogCompileErrors(geometry_program, compile_type::Geometry);
    } 
    
    // shader Program compilation
    m_shader_id = glCreateProgram();
    glAttachShader(m_shader_id, vertex_program);
    glAttachShader(m_shader_id, fragment_program);
    if(geometry_start != std::string::npos){
        glAttachShader(m_shader_id, geometry_program);   
    }

    glLinkProgram(m_shader_id);
    LogCompileErrors(m_shader_id, compile_type::Program);

    // delte the programs at the end for cleanup reasons :P
    glDeleteShader(vertex_program);
    glDeleteShader(fragment_program);
        if(geometry_start != std::string::npos){
        glDeleteShader(geometry_program);   
    }

    m_is_compiled = true;
    return true;
}

void Shader::UseProgram() const {
    glUseProgram(m_shader_id);
}

unsigned int Shader::GetProgram() const {
    return m_shader_id;
}

void Shader::UploadBool(const char* in_name, bool in_value) const {
    glUniform1i(glGetUniformLocation(m_shader_id, in_name), (int)in_value);
}

void Shader::UploadInt(const char* in_name, int in_value) const {
    glUniform1i(glGetUniformLocation(m_shader_id, in_name), in_value);
}

void Shader::UploadFloat(const char* in_name, float in_value) const {
    glUniform1f(glGetUniformLocation(m_shader_id, in_name), in_value); 
}

void Shader::UploadVec2(const char* in_name, vec2& in_value) const {
    glUniform2fv(glGetUniformLocation(m_shader_id, in_name), 1, &in_value[0]); 
}

void Shader::UploadVec3(const char* in_name, vec3& in_value) const {
    glUniform3fv(glGetUniformLocation(m_shader_id, in_name), 1, &in_value[0]); 
}

void Shader::UploadVec4(const char* in_name, vec4& in_value) const {
    glUniform4fv(glGetUniformLocation(m_shader_id, in_name), 1, &in_value[0]); 
}

void Shader::UploadMat2(const char* in_name, mat2& in_value) const {
    glUniformMatrix2fv(glGetUniformLocation(m_shader_id, in_name), 1, GL_FALSE, &in_value[0][0]);
}

void Shader::UploadMat3(const char* in_name, mat3& in_value) const {
    glUniformMatrix3fv(glGetUniformLocation(m_shader_id, in_name), 1, GL_FALSE, &in_value[0][0]);
}

void Shader::UploadMat4(const char* in_name, mat4& in_value) const {
    glUniformMatrix4fv(glGetUniformLocation(m_shader_id, in_name), 1, GL_FALSE, &in_value[0][0]);
}


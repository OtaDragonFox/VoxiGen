#include "shader.h"

#include "glad/glad.h"
#include "modules/logger.h"
#include "modules/platform.h"

bool Shader::LoadShaderFromPath(const char* shader_path) {
    const auto shader_source = PLATFORM.GetFileContentAsString(shader_path);
    if (!shader_source) {
        LOG_ERROR("Failed to load shader from %s", shader_path);
        return false;
    }

    // assume file format:
    // #!vertex
    // code{}
    // #!fragment
    // code{}
    // #!geometry
    // code{}

    const auto vertex_start = shader_source->find("//!vertex");
    const auto fragment_start = shader_source->find("//!fragment");
    if (vertex_start == std::string::npos || fragment_start == std::string::npos) {
        LOG_ERROR("Failed to find vertex or fragment shader tag from %s", shader_path);
        return false;
    }

    const auto vertex_shader = CompileShader(Vertex, shader_source->substr(vertex_start, fragment_start).c_str());
    if (!vertex_shader) {
        LOG_ERROR("Failed to compile vertex shader from %s", shader_path);
        return false;
    }

    const unsigned int program = glCreateProgram();
    glAttachShader(program, *vertex_shader);

    auto fragment_shader_end = shader_source->length();
    if (const auto geometry_start = shader_source->find("//!geometry"); geometry_start != std::string::npos) {
        fragment_shader_end = geometry_start;
        const auto geometry_shader =
            CompileShader(Geometry, shader_source->substr(geometry_start, shader_source->length()).c_str());
        if (!geometry_shader) {
            LOG_ERROR("Failed to compile geometry shader from %s", shader_path);
            return false;
        }
        glAttachShader(program, *geometry_shader);
    }
    const auto fragment_shader =
        CompileShader(Fragment, shader_source->substr(fragment_start, fragment_shader_end).c_str());
    if (!fragment_shader) {
        LOG_ERROR("Failed to compile fragment shader from %s", shader_path);
        return false;
    }
    glAttachShader(program, *fragment_shader);
    glLinkProgram(program);
    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetShaderInfoLog(program, sizeof(info_log), nullptr, info_log);
        LOG_ERROR("Failed to link shader program: %s", info_log);
    }
    glDeleteShader(*vertex_shader);
    glDeleteShader(*fragment_shader);
    this->program_ = program;
    this->compiled_at_ms_ =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    return true;
}

void Shader::SetTimeUniform() const {
    const int uniform_location = glGetUniformLocation(program_, "time");  //todo: cache glGetUniformLocation
    const long current_time_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
    glUniform1f(uniform_location, static_cast<float>(current_time_ms - compiled_at_ms_) / 1000);
}

std::optional<unsigned> Shader::CompileShader(const shader_type type, const char* source) {
    GLenum shader_type = 0;
    switch (type) {
        case Vertex:
            shader_type = GL_VERTEX_SHADER;
            break;
        case Fragment:
            shader_type = GL_FRAGMENT_SHADER;
            break;
        case Geometry:
            shader_type = GL_GEOMETRY_SHADER;
            break;
    }
    const unsigned int shader = glCreateShader(shader_type);
    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);
    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char info_log[512];
        glGetShaderInfoLog(shader, sizeof(info_log), nullptr, info_log);
        LOG_ERROR("Shader compilation failed: {}", info_log);
        return std::nullopt;
    }
    return std::make_optional(shader);
}
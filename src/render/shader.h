#pragma once
#include <optional>
#include "glad/glad.h"

enum shader_type { Vertex, Fragment, Geometry };

class Shader {
public:
    Shader() = default;

    inline void UseProgram() const { glUseProgram(program_); }

    bool LoadShaderFromPath(const char* shader_path);

    void SetTimeUniform() const;

    [[nodiscard]] unsigned int GetProgram() const { return program_; }

private:
    unsigned int program_{0};
    unsigned long compiled_at_ms_{0}; // used for shader animations.
    /// Tries to compile a shader of the given type
    /// @param type the shader type
    /// @param source the shader source
    /// @return p
    static std::optional<unsigned int> CompileShader(shader_type type, const char* source);
};

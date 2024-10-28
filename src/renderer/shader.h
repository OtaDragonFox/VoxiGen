#pragma once
#include <optional>
#include "types.h"

enum shader_type { Vertex, Fragment, Geometry };


class Shader {
public:
    Shader() = default;

    void UseProgram();

    bool LoadShaderFromPath(const char* shader_path);

    void SetTimeUniform() const;

    [[nodiscard]] unsigned int GetProgram() const { return program_; }

    void SetMat4(const char* name, const mat4& mat);




private:
    unsigned int program_{0};
    unsigned long compiled_at_ms_{0}; // used for shader animations.
    /// Tries to compile a shader of the given type
    /// @param type the shader type
    /// @param source the shader source
    /// @return p
    static std::optional<unsigned int> CompileShader(shader_type type, const char* source);
};

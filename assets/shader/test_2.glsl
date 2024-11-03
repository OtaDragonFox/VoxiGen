//!vertex
#version 330
layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 uv;
uniform mat4 u_view_projection;


void main() {
    gl_Position = u_view_projection * vec4(pos, 1.0);
}

//!fragment
#version 330
out vec4 fragColor;

void main() {
    fragColor = vec4(1.0,0.0,0.0, 1.0);
}
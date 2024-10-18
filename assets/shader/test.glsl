//!vertex
#version 330
layout (location = 0) in vec3 pos;

void main() {
    gl_Position = vec4(pos, 1.0);
}

//!fragment
#version 330
out vec4 fragColor;
uniform float time;
uniform vec2 resolution;

void main() {
    // Normalized pixel coordinates (from 0 to 1)
    vec2 uv = gl_FragCoord.xy / resolution;

    // Time varying pixel color
    vec3 col = 0.5 + 0.5 * cos(2.0 + time + uv.x + uv.y + vec3(0, 2, 4));

    // Output to screen
    fragColor = vec4(col, 1.0);
}
#version 430
// Vertex shader

layout (location = 0) in vec3 coords;
layout (location = 1) in vec3 colors;

out vec3 color;

void main() {
    color = colors;
    gl_Position = vec4(coords, 1.0);
}

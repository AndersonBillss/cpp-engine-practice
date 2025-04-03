#version 330 core
layout (location = 0) in vec3 aPos;

out vec4 vertexColor; // specify a color output to the fragment shader

uniform float angle;
void main() {
    float c = cos(angle);
    float s = sin(angle);

    // Rotation around Y-axis
    mat4 rotation = mat4(
        c,  0.0,  s,  0.0,
        0.0, 1.0, 0.0, 0.0,
       -s,  0.0,  c,  0.0,
        0.0, 0.0, 0.0, 1.0
    );

    gl_Position = rotation * vec4(aPos, 1.0);
    vertexColor = vec4(0.13, 0.09, 0.3, 1.0);
};
#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 ourColor;

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
    ourColor = aColor;
};
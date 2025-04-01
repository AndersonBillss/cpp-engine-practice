#include <vector>
using std::vector;
#include "window.h"

// Vertex Shader (applies manual rotation)
const char* vertexShaderSource = R"(
#version 330 core
layout (location = 0) in vec3 aPos;
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
}
)";

// Fragment Shader
const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColor;
void main() {
    FragColor = vec4(0.2, 0.6, 1.0, 1.0);
}
)";

int main() {
    // Define Cube Vertices
    vector<float> vertices = {
        // Front Face
        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        // Back Face
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    vector<unsigned int> indices = {
        // Front
        0, 1, 2, 2, 3, 0,
        // Back
        4, 5, 6, 6, 7, 4,
        // Left
        0, 3, 7, 7, 4, 0,
        // Right
        1, 2, 6, 6, 5, 1,
        // Top
        3, 2, 6, 6, 7, 3,
        // Bottom
        0, 1, 5, 5, 4, 0,
    };

    // Create window
    Window* window = new Window(800, 600, "Rotating Cube");
    Ctx* ctx = window->getCtx();
    ctx->bindBufferData(vertices, indices);
    ctx->addShader(vertexShaderSource, fragmentShaderSource);
    
    unsigned int angleLoc = ctx->getShaderVariableLoc("angle");
    auto process = [&]() {
        float angle = (float)window->getTime();  // Radians
        ctx->setShaderVariable(angleLoc, angle);
    };

    // Main loop
    while (!window->shouldClose()) window->process(process);

    // Cleanup
    delete window;
    return 0;
}

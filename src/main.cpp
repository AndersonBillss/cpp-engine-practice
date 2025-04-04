#include <vector>
using std::vector;
#include "window.h"
#include "shader.h"
#include "core.h"

int main() {
    vector<float> triangleVertices = {
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,   
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,   
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f 
    };  
    vector<unsigned int> triangleIndices = {
        0, 1, 2
    };

    string vertexShaderPath = "vertex_shader.glsl";
    string fragmentShaderPath = "fragment_shader.glsl";
    
    Window* window = new Window(800, 600, "Rotating Triangle");
    Mesh mesh(triangleVertices, triangleIndices, {3, 3});
    Shader shader(vertexShaderPath, fragmentShaderPath);
    
    Shader::Uniform<float> shaderAngle(shader, "angle");
    auto process = [&]() {
        shader.use();
        mesh.use();

        float time = (float)window->getTime();
        float angle = time;

        shaderAngle.set(angle);
    };

    // Main loop
    while (!window->shouldClose()) window->process(process);

    // Cleanup
    delete window;
    return 0;
}

#include <vector>
using std::vector;
#include "window.h"

int main() {
    vector<float> triangleVertices = {
        -0.5f, -0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        0.0f,  0.5f, 0.0f
    };
    vector<unsigned int> triangleIndices = {
        0, 1, 2
    };

    string vertexShaderPath = "vertex_shader.glsl";
    string fragmentShaderPath = "fragment_shader.glsl";
    
    // Create window
    Window* window = new Window(800, 600, "Rotating Triangle");
    Ctx* ctx = window->getCtx();
    ctx->bindBufferData(triangleVertices, triangleIndices);
    ctx->addShaderFiles(vertexShaderPath, fragmentShaderPath);
    
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

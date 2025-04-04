#include <vector>
using std::vector;
#include "window.h"
#include "core.h"

float currentGreen = 0;
int greenIncreasing = -1;
float lastTime = 0;
float getGreen(float time){
    float deltaTime = time - lastTime;
    lastTime = time;
    if(lastTime == 0) return 0;

    float nextGreen = currentGreen + (greenIncreasing * deltaTime);
    if(nextGreen < 0){
        greenIncreasing = 1;
        return currentGreen;
    }
    if(nextGreen > 1){
        greenIncreasing = -1;
        return currentGreen;
    }
    currentGreen = nextGreen;
    return nextGreen;
}

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

    lastTime = (float)window->getTime();
    
    unsigned int angleLoc = ctx->getUniformLocation("angle");
    unsigned int greenColor = ctx->getUniformLocation("greenValue");
    auto process = [&]() {
        float time = (float)window->getTime();
        float angle = time;
        float green = getGreen(time);
        ctx->setShaderVariable(angleLoc, angle);
        ctx->setShaderVariable(greenColor, green);
    };

    // Main loop
    while (!window->shouldClose()) window->process(process);

    // Cleanup
    delete window;
    return 0;
}

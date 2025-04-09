#include <vector>
using std::vector;

#include "window.h"
#include "shader.h"
#include "texture2D.h"
#include "core.h"

int main() {
    vector<unsigned int> attributes = {
            3,                   2
    };
         // Vertices          // Textures
    vector<float> rectangleVertices = {
         0.5f,  0.5f, 0.0f,   1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,   1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,   0.0f, 1.0f
    };  
    vector<unsigned int> rectangleIndices = {
        0, 1, 3, // first triangle
        1, 2, 3  // second triangle    
    };

    string vertexShaderPath = "vertex_shader.glsl";
    string fragmentShaderPath = "fragment_shader.glsl";
    
    Window window(800, 600, "Rotating Triangle");
    Mesh mesh(rectangleVertices, rectangleIndices, attributes);
    Shader shader(vertexShaderPath, fragmentShaderPath);
    Texture2D texture(shader);
    texture.useMipmaps();
    texture.useBilinearFiltering();
    texture.addTexture("wall.jpg", "texture1");
    texture.addTexture("opengl-1-logo-png-transparent.png", "texture2");

    Shader::Uniform<float> shaderAngle(shader, "angle");
    Shader::Uniform<float> shaderLogoOpacity(shader, "logoOpacity");
    float logoOpacity = .5f;
    shaderLogoOpacity.set(logoOpacity);

    auto process = [&](double deltaTime) {
        shader.use();
        mesh.use();
        texture.use();

        // Input handling
        if(window.isHeld(Key::Up)){
            logoOpacity += deltaTime * .75f;
            shaderLogoOpacity.set(logoOpacity);
        }
        if(window.isHeld(Key::Down)){
            logoOpacity -= deltaTime * .75f;
            shaderLogoOpacity.set(logoOpacity);
        }
        if (window.isJustPressed(Key::Escape)){
            window.close();
        }

        float time = (float)window.getTime();
        float angle = time;

        shaderAngle.set(angle);
    };

    // Main loop
    while (!window.shouldClose()) window.process(process);

    return 0;
}
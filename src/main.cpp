#include <vector>
using std::vector;

#include "math.hpp"
#include "ctx/mesh.hpp"
#include "ctx/window.hpp"
#include "ctx/shader.hpp"
#include "ctx/texture2D.hpp"

#include "core.hpp"

int main() {
    vector<unsigned int> attributes = {
            3,                   2
    };
         // Vertices          // Textures
    vector<float> vertices = {
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
        0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
        0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
    };

    Math::Vec3 cubePositions[] = {
        Math::Vec3( 0.0f,  0.0f,  0.0f),
        Math::Vec3( 2.0f,  5.0f, -15.0f),
        Math::Vec3(-1.5f, -2.2f, -2.5f),
        Math::Vec3(-3.8f, -2.0f, -12.3f),
        Math::Vec3( 2.4f, -0.4f, -3.5f),
        Math::Vec3(-1.7f,  3.0f, -7.5f),
        Math::Vec3( 1.3f, -2.0f, -2.5f),
        Math::Vec3( 1.5f,  2.0f, -2.5f),
        Math::Vec3( 1.5f,  0.2f, -1.5f),
        Math::Vec3(-1.3f,  1.0f, -1.5f)
    };

    string vertexShaderPath = "vertex_shader.glsl";
    string fragmentShaderPath = "fragment_shader.glsl";
    
    Window window(800, 600, "Rotating Cubes");
    Mesh mesh(vertices, attributes);
    Shader shader(vertexShaderPath, fragmentShaderPath);
    Texture2D texture(shader);
    texture.useMipmaps();
    texture.useBilinearFiltering();
    texture.addTexture("wall.jpg", "texture1");
    texture.addTexture("opengl-1-logo-png-transparent.png", "texture2");

    // Send matrices to the GPU
    Math::Mat4 model = Math::Mat4(1.0f);
    model = Math::rotate(model, -55.0f*Math::degToRad, Math::Vec3(1.0f, 0.0f, 0.0f)); 
    Shader::Uniform<Math::Mat4> shaderModel(shader, "model");
    shaderModel.set(model);

    Math::Mat4 view = Math::Mat4(1.0f);
    view = Math::translate(view, Math::Vec3(0.0f, 0.0f, -3.0f));
    Shader::Uniform<Math::Mat4> shaderView(shader, "view");
    shaderView.set(view);

    Math::Mat4 projection;
    projection = Math::perspective(45.0f * Math::degToRad, 800.0f / 600.0f, 0.1f, 100.0f);
    Shader::Uniform<Math::Mat4> shaderProjection(shader, "projection");
    shaderProjection.set(projection);


    Shader::Uniform<float> shaderLogoOpacity(shader, "logoOpacity");
    float logoOpacity = .5f;
    shaderLogoOpacity.set(logoOpacity);

    auto process = [&](double deltaTime) {
        shader.use();
        texture.use();

        // Input handling
        if(window.isHeld(Key::Up)){
            logoOpacity += deltaTime * 1.5f;
            shaderLogoOpacity.set(logoOpacity);
        }
        if(window.isHeld(Key::Down)){
            logoOpacity -= deltaTime * 1.5f;
            shaderLogoOpacity.set(logoOpacity);
        }
        if (window.isJustPressed(Key::Escape)){
            window.close();
        }

        for (unsigned int i = 0; i < 10; i++)
        {
            // calculate the model matrix for each object and pass it to shader before drawing
            Math::Mat4 model = Math::Mat4(1.0f);
            model = Math::translate(model, cubePositions[i]);
            model = Math::rotate(model, window.getTime() * 55.0f * Math::degToRad, Math::Vec3(0.5f, 1.0f, 0.0f));  
            float angle = 20.0f * i;
            model = Math::rotate(model, Math::degToRad*angle, Math::Vec3(1.0f, 0.3f, 0.5f));
            shaderModel.set(model);

            mesh.use();
        }
    };

    // Main loop
    while (!window.shouldClose()) window.process(process);

    return 0;
}
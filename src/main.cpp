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
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,
         0.5f, -0.5f, -0.5f,    1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 0.0f,

        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 1.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,

        -0.5f,  0.5f,  0.5f,    1.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    1.0f, 0.0f,

         0.5f,  0.5f,  0.5f,    1.0f, 0.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 0.0f,

        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,
         0.5f, -0.5f, -0.5f,    1.0f, 1.0f,
         0.5f, -0.5f,  0.5f,    1.0f, 0.0f,
         0.5f, -0.5f,  0.5f,    1.0f, 0.0f,
        -0.5f, -0.5f,  0.5f,    0.0f, 0.0f,
        -0.5f, -0.5f, -0.5f,    0.0f, 1.0f,

        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f,
         0.5f,  0.5f, -0.5f,    1.0f, 1.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 0.0f,
         0.5f,  0.5f,  0.5f,    1.0f, 0.0f,
        -0.5f,  0.5f,  0.5f,    0.0f, 0.0f,
        -0.5f,  0.5f, -0.5f,    0.0f, 1.0f
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
    window.hideCursor();
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


    // Camera
    Math::Vec3 cameraPos(0.0f, 0.0f, 3.0f);
    Math::Vec3 cameraTarget(0.0f, 0.0f, 0.0f);
    Math::Vec3 cameraDirection = Math::normalize(cameraPos - cameraTarget);
    Math::Vec3 up = Math::Vec3(0.0f, 1.0f, 0.0f); 
    Math::Vec3 cameraRight = Math::normalize(Math::cross(up, cameraDirection));
    Math::Vec3 cameraUp    = Math::Vec3(0.0f, 1.0f,  0.0f);
    Math::Vec3 cameraFront = Math::Vec3(0.0f, 0.0f, -1.0f);
    
    float pitch = 0;
    float yaw = -90.0f;
    bool firstMouse = true;
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
        if(window.isJustPressed(Key::Escape)){ window.close(); }

        float lookSpeedX = 0.1f;
        float lookSpeedY = 0.1f;
        if (firstMouse){
            firstMouse = false;
        } else {
            yaw   -= window.getMouseChangeX() * lookSpeedX;
            pitch += window.getMouseChangeY() * lookSpeedY;
        }
        if(pitch > 89.0f)
            pitch =  89.0f;
        if(pitch < -89.0f)
            pitch = -89.0f;

        Math::Vec3 direction;
        direction.x = cos(Math::degToRad * yaw);
        direction.y = sin(Math::degToRad * pitch);
        direction.z = sin(Math::degToRad * yaw);
        cameraFront = Math::normalize(direction);

        const float cameraSpeed = 5.0f * deltaTime;
        float calculatedSpeed = cameraSpeed;
        if(window.isHeld(Key::LeftShift))
            calculatedSpeed = cameraSpeed * 3;
        if(window.isHeld(Key::W))
            cameraPos += calculatedSpeed * cameraFront;
        if(window.isHeld(Key::S))
            cameraPos -= calculatedSpeed * cameraFront;
        if(window.isHeld(Key::A))
            cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * calculatedSpeed;
        if(window.isHeld(Key::D))
            cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * calculatedSpeed;
    
        
        for (unsigned int i = 0; i < 10; i++){
            // calculate the model matrix for each object and pass it to shader before drawing
            Math::Mat4 model = Math::Mat4(1.0f);
            model = Math::translate(model, cubePositions[i]);
            model = Math::rotate(model, window.getTime() * -10.0f * Math::degToRad, Math::Vec3(0.5f, 1.0f, 0.0f));  
            float angle = 20.0f * i;
            model = Math::rotate(model, Math::degToRad*angle, Math::Vec3(1.0f, 0.3f, 0.5f));
            shaderModel.set(model);

            mesh.use();
        }

        Math::Mat4 view(1.0f);
        const float radius = 10.0f;
        float camX = sin(glfwGetTime()) * radius;
        float camZ = cos(glfwGetTime()) * radius;
        view = Math::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);
        shaderView.set(view);      
    };

    // Main loop
    while (!window.shouldClose()) window.process(process);

    return 0;
}
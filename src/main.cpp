#define STB_IMAGE_IMPLEMENTATION
#include "lib/stb_image.h"
#include <GL/glew.h>

#include <vector>
using std::vector;
#include "window.h"
#include "shader.h"
#include "core.h"

int main() {
    vector<unsigned int> attributes = {
            3,                   3,                  2
    };
         // Vertices          // Colors           // Textures
    vector<float> rectangleVertices = {
         0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
         0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,
        -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f
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
    
    
    unsigned int texture1, texture2;
    stbi_set_flip_vertically_on_load(true);  

    glGenTextures(1, &texture1);  
    glBindTexture(GL_TEXTURE_2D, texture1);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, nrChannels;
    unsigned char *data = stbi_load("src\\assets\\wall.jpg", &width, &height, &nrChannels, 0); 
    if(data){
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3){
            format = GL_RGB;
        } else if (nrChannels == 4)
            format = GL_RGBA;
        else {
            std::cerr << "Unsupported number of channels: " << nrChannels << std::endl;
            return -1;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    //-----------------------------------------------------------------------    
    glGenTextures(1, &texture2);  
    glBindTexture(GL_TEXTURE_2D, texture2);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    data = stbi_load("src\\assets\\opengl-1-logo-png-transparent.png", &width, &height, &nrChannels, 0); 
    if(data){
        GLenum format;
        if (nrChannels == 1)
            format = GL_RED;
        else if (nrChannels == 3)
            format = GL_RGB;
        else if (nrChannels == 4){
            format = GL_RGBA;
        } else {
            std::cerr << "Unsupported number of channels: " << nrChannels << std::endl;
            return -1;
        }
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    shader.use();
    Shader::Uniform<int> tex1(shader, "texture1");
    tex1.set(0);
    Shader::Uniform<int> tex2(shader, "texture2");
    tex2.set(1);
    
    //-----------------------------------------------------------------------
    // GLenum err = glGetError();
    // if (err != GL_NO_ERROR)
    //     std::cerr << "OpenGL Error: " << err << std::endl; 

    
    Shader::Uniform<float> shaderAngle(shader, "angle");
    auto process = [&]() {
        shader.use();
        mesh.use();

        glBindTexture(GL_TEXTURE_2D, texture1);
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture2);
        glActiveTexture(GL_TEXTURE1);

        float time = (float)window.getTime();
        float angle = time;

        shaderAngle.set(angle);
    };

    // Main loop
    while (!window.shouldClose()) window.process(process);

    return 0;
}
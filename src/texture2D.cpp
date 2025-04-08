#define STB_IMAGE_IMPLEMENTATION
#include "texture2D.h"
#include "lib/stb_image.h"
#include <GL/glew.h>
#include <iostream>
using std::cerr, std::endl;

Texture2D::Texture2D(Shader& shader) : _shader(shader) {
    stbi_set_flip_vertically_on_load(true);
    _shader = shader;
}

void Texture2D::addTexture(const string& filePath, const string& textureName) {
    if(_textures.size() == 16){
        cerr << "No more than 16 textures allowed" << endl;
        return;
    }
    _shader.use();
    
    unsigned int texture;
    glGenTextures(1, &texture);  
    glBindTexture(GL_TEXTURE_2D, texture);
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    
    int width, height, nrChannels;

    unsigned char *data = stbi_load(("src\\assets\\" + filePath).c_str(), &width, &height, &nrChannels, 0); 
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
            exit(EXIT_FAILURE);
        }
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    } else {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);

    Shader::Uniform<int> tex(_shader, textureName);
    tex.set(_textures.size());

    _textures.push_back(texture);
}

void Texture2D::use(){
    for(size_t i=0; i<_textures.size(); i++){
        glBindTexture(GL_TEXTURE_2D, _textures[i]);
        glActiveTexture(GL_TEXTURE0 + i);
    }
}
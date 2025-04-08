#pragma once
#include <string>
using std::string;
#include <vector>
using std::vector;

#include "shader.h"

class Texture2D {
public:
    Texture2D(Shader& shader);

    void addTexture(const string& filePath, const string& textureName);
    void useMipmaps();

    void use();
private:
    bool _usingMipmaps = false;
    vector<unsigned int> _textures;
    Shader& _shader;
};
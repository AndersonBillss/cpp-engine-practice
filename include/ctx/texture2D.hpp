#pragma once
#include <string>
using std::string;
#include <vector>
using std::vector;

#include "shader.hpp"

class Texture2D {
public:
    Texture2D(Shader& shader);

    void addTexture(const string& filePath, const string& textureName);
    void useMipmaps();
    void useBilinearFiltering();

    void use();
private:
    bool _usingMipmaps = false;
    bool _usingBilinearFiltering = false;
    vector<unsigned int> _textures;
    Shader& _shader;
};
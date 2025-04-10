#pragma once
#include <GL/glew.h>
#include <functional>
using std::function;
#include <vector>
using std::vector;
#include <string>
using std::string;

class Mesh {
public:

    Mesh(
        const vector<float>& vertices,
        const vector<unsigned int>& attributes = vector<unsigned int>{3},
        const vector<unsigned int>& indices = vector<unsigned int>{}
    );
    ~Mesh();

    void use();
private:
    unsigned int _VAO, _VBO, _EBO;
    unsigned int _indexCount = 0;
    unsigned int _vertexCount = 0; 
};
#include "ctx/mesh.hpp"
#include <fstream>
using std::ifstream;
#include <sstream>
using std::stringstream;
#include <iostream>
using std::cerr;
#include "core.hpp"

Mesh::Mesh(const vector<float>& vertices, const vector<unsigned int>& attributes, const vector<unsigned int>& indices){
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);
    glEnable(GL_DEPTH_TEST);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    if(indices.size() > 0){
        _indexCount = indices.size();
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);
    }
    
    int attributesSize = 0;
    for(unsigned int attr : attributes) attributesSize += attr;
    _vertexCount = vertices.size() / attributesSize;

    // Enable and define each vertex attribute
    int offset = 0;
    for(unsigned int i = 0; i < attributes.size(); i++){
        unsigned int attr = attributes[i];
        glVertexAttribPointer(i, attr, GL_FLOAT, GL_FALSE, attributesSize * sizeof(float), (void*)(offset * sizeof(float)));
        glEnableVertexAttribArray(i);
        offset += attr;
    }
}

Mesh::~Mesh(){
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
    glDeleteBuffers(1, &_EBO);
}

void Mesh::use(){
    glBindVertexArray(_VAO);
    if (_indexCount > 0) {
        glDrawElements(GL_TRIANGLES, _indexCount, GL_UNSIGNED_INT, 0);
    } else if (_vertexCount > 0) {
        glDrawArrays(GL_TRIANGLES, 0, _vertexCount);
    }
}
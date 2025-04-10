#include "ctx/mesh.h"
#include <fstream>
using std::ifstream;
#include <sstream>
using std::stringstream;
#include <iostream>
using std::cerr;

Mesh::Mesh( const vector<float>& vertices, const vector<unsigned int>& indices, const vector<unsigned int>& attributes){
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);
    glEnable(GL_DEPTH_TEST);

    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    int attributesSize = 0;
    for(unsigned int attr : attributes) attributesSize += attr;

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
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}
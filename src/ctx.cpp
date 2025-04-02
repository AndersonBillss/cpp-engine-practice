#include "ctx.h"
#include <fstream>  // Required for std::ifstream
using std::ifstream;
#include <sstream>  // Required for std::stringstream
using std::stringstream;
#include <iostream>
using std::cerr;

Ctx::Ctx(){
    glGenVertexArrays(1, &_VAO);
    glGenBuffers(1, &_VBO);
    glGenBuffers(1, &_EBO);

    glBindVertexArray(_VAO);
    glEnable(GL_DEPTH_TEST);
}

Ctx::~Ctx(){
    glDeleteVertexArrays(1, &_VAO);
    glDeleteBuffers(1, &_VBO);
    glDeleteBuffers(1, &_EBO);
    glDeleteProgram(_shaderProgram);
}

void Ctx::bindBufferData(const vector<float>& vertices, const vector<unsigned int>& indices){
    glBindBuffer(GL_ARRAY_BUFFER, _VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), indices.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
}

void Ctx::addShaderFiles(const string& vertexShaderPath, const string& fragmentShaderPath){
    string vertexShaderSource = _readFileData("src\\shaders\\" + vertexShaderPath);
    string fragmentShaderSource = _readFileData("src\\shaders\\" + fragmentShaderPath);
    addShaders(vertexShaderSource.c_str(), fragmentShaderSource.c_str());
}

void Ctx::addShaders(const char* vertexShaderSource, const char* fragmentShaderSource){
    unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, vertexShader);
    glAttachShader(_shaderProgram, fragmentShader);
    glLinkProgram(_shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    _checkShaderCompilation();
    _checkProgramLinking();
}

int Ctx::getShaderVariableLoc(const char* variable){
    return glGetUniformLocation(_shaderProgram, variable);
}

void Ctx::process(function<void()> callback){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glUseProgram(_shaderProgram);
    callback();
    glBindVertexArray(_VAO);
    glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);
}


void Ctx::_checkShaderCompilation() {
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(_shaderProgram, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(_shaderProgram, 1024, NULL, infoLog);
        cerr << "Shader Compilation Error:\n" << infoLog << "\n";
    }
}

void Ctx::_checkProgramLinking() {
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(_shaderProgram, 1024, NULL, infoLog);
        cerr << "Shader Linking Error:\n" << infoLog << "\n";
    }
}

string Ctx::_readFileData(const string& filepath) {
    ifstream shaderFile(filepath);
    if (!shaderFile) {
        cerr << "Failed to open shader file: " << filepath << "\n";
        return "";
    }
    stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    return shaderStream.str();
}
#include "shader.h"
#include <fstream>  
using std::ifstream;
#include <sstream>
using std::stringstream;
#include <iostream>
using std::cerr;
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

Shader::Shader(string vertexPath, string fragmentPath){
    string vertexShaderSource = _readFileData("src\\shaders\\" + vertexPath);
    string fragmentShaderSource = _readFileData("src\\shaders\\" + fragmentPath);
    _addShaders(vertexShaderSource.c_str(), fragmentShaderSource.c_str());
}
Shader::~Shader(){
    glDeleteProgram(_shaderProgram);
}

void Shader::_addShaders(const char* vertexShaderSource, const char* fragmentShaderSource){
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

void Shader::use(){
    glUseProgram(_shaderProgram);
}

string Shader::_readFileData(const string& filePath){
    ifstream shaderFile(filePath);
    if (!shaderFile) {
        cerr << "Failed to open shader file: " << filePath << "\n";
        return "";
    }
    stringstream shaderStream;
    shaderStream << shaderFile.rdbuf();
    return shaderStream.str();
}


void Shader::_checkShaderCompilation() {
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(_shaderProgram, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(_shaderProgram, 1024, NULL, infoLog);
        cerr << "Shader Compilation Error:\n" << infoLog << "\n";
    }
}

void Shader::_checkProgramLinking() {
    GLint success;
    GLchar infoLog[1024];
    glGetProgramiv(_shaderProgram, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(_shaderProgram, 1024, NULL, infoLog);
        cerr << "Shader Linking Error:\n" << infoLog << "\n";
    }
}
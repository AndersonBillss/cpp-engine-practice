#include "ctx/shader.h"
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
    _checkShaderCompilation(vertexShader, "VERTEX");

    unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);
    _checkShaderCompilation(fragmentShader, "FRAGMENT");

    _shaderProgram = glCreateProgram();
    glAttachShader(_shaderProgram, vertexShader);
    glAttachShader(_shaderProgram, fragmentShader);
    glLinkProgram(_shaderProgram);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
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


void Shader::_checkShaderCompilation(GLuint shader, const string& type) {
    GLint success;
    GLchar infoLog[1024];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 1024, NULL, infoLog);
        cerr << type << " Shader Compilation Error:\n" << infoLog << "\n";
    }
}
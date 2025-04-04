#pragma once
#include <string>
#include <GL/glew.h>
using std::string;

class Shader{
public:
    Shader(string vertexPath, string fragmentPath);
    ~Shader();

    int getUniformLocation(const char* variable);
    template <class T>
    void setUniform(int varLoc, T value) {
        glUniform1f(varLoc, value);
    };

    void use();

private:
    GLuint _shaderProgram;

    void _checkShaderCompilation();
    void _checkProgramLinking();

    void _addShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
    string _readFileData(const string& filePath);
};
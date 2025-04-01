#pragma once
#include <GL/glew.h>
#include <functional>
using std::function;
#include <vector>
using std::vector;

class Ctx {
public:
    typedef void (*FrameCallback)();
    Ctx();
    ~Ctx();
    
    void bindBufferData(const vector<float>& vertices, const vector<unsigned int>& indices);
    void addShader(const char*& vertexShaderSource, const char*& fragmentShaderSource);

    int getShaderVariableLoc(const char* variable);
    
    template <class T>
    void setShaderVariable(int varLoc, T value) {
        glUniform1f(varLoc, value);
    };
    
    void process(function<void()> callback);
private:
    unsigned int _VAO, _VBO, _EBO;
    GLuint _shaderProgram;

    void _checkShaderCompilation();
    void _checkProgramLinking();
};
#pragma once
#include <GL/glew.h>
#include <functional>
using std::function;
#include <vector>
using std::vector;
#include <string>
using std::string;

class Ctx {
public:
    typedef void (*FrameCallback)();
    Ctx();
    ~Ctx();
    
    void bindBufferData(const vector<float>& vertices, const vector<unsigned int>& indices);
    void addShaderFiles(const string& vertexShaderPath, const string& fragmentShaderPath);
    void addShaders(const char* vertexShaderSource, const char* fragmentShaderSource);

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

    string _readFileData(const string& filePath);
};
#pragma once
#include <string>
#include <GL/glew.h>
using std::string;
#include <iostream>
using std::cerr;
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>


class Shader{
public:
    Shader(string vertexPath, string fragmentPath);
    ~Shader();

    void use();

    template <class T>
    class Uniform{
    public:
        Uniform(const Shader& shader, const string& name);
        inline void set(T value) const;
    private:
        int _location;
    };

    private:
    GLuint _shaderProgram;
    
    void _checkShaderCompilation(GLuint shader, const string& type);
    
    void _addShaders(const char* vertexShaderSource, const char* fragmentShaderSource);
    string _readFileData(const string& filePath);
    
    template <class T>
    friend class Uniform;
};



// Template constructor
template <class T>
Shader::Uniform<T>::Uniform(const Shader& shader, const string& name) {
    static_assert(
        std::is_same<T, float>::value ||
        std::is_same<T, int>::value ||
        std::is_same<T, bool>::value ||
        std::is_same<T, glm::vec2>::value ||
        std::is_same<T, glm::vec3>::value ||
        std::is_same<T, glm::vec4>::value ||
        std::is_same<T, glm::mat4>::value,
        "Unsupported uniform type"
    );
    _location = glGetUniformLocation(shader._shaderProgram, name.c_str());
}

// Specialization for float
template <>
inline void Shader::Uniform<float>::set(float value) const {
    glUniform1f(_location, value);
}

// Specialization for int
template <>
inline void Shader::Uniform<int>::set(int value) const {
    glUniform1i(_location, value);
}

// Specialization for bool (as int)
template <>
inline void Shader::Uniform<bool>::set(bool value) const {
    glUniform1i(_location, static_cast<int>(value));
}

// Specialization for glm::vec2
template <>
inline void Shader::Uniform<glm::vec2>::set(glm::vec2 value) const {
    glUniform2f(_location, value.x, value.y);
}

// Specialization for glm::vec3
template <>
inline void Shader::Uniform<glm::vec3>::set(glm::vec3 value) const {
    glUniform3f(_location, value.x, value.y, value.z);
}

// Specialization for glm::vec4
template <>
inline void Shader::Uniform<glm::vec4>::set(glm::vec4 value) const {
    glUniform4f(_location, value.x, value.y, value.z, value.w);
}

// Specialization for glm::mat4
template <>
inline void Shader::Uniform<glm::mat4>::set(glm::mat4 value) const {
    glUniformMatrix4fv(_location, 1, GL_FALSE, glm::value_ptr(value));
}

template <class T>
inline void Shader::Uniform<T>::set(T value) const {
    cerr << "Unsupported shader data type!";
}
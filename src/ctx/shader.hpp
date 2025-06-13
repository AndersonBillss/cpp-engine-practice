#pragma once
#include "../math.hpp"
#include <string>
#include <GL/glew.h>
using std::string;
#include <iostream>
using std::cerr;


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
        std::is_same<T, Math::Vec2>::value ||
        std::is_same<T, Math::Vec3>::value ||
        std::is_same<T, Math::Vec4>::value ||
        std::is_same<T, Math::Mat4>::value,
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

// Specialization for Math::vec2
template <>
inline void Shader::Uniform<Math::Vec2>::set(Math::Vec2 value) const {
    glUniform2f(_location, value.x, value.y);
}

// Specialization for Math::vec3
template <>
inline void Shader::Uniform<Math::Vec3>::set(Math::Vec3 value) const {
    glUniform3f(_location, value.x, value.y, value.z);
}

// Specialization for Math::vec4
template <>
inline void Shader::Uniform<Math::Vec4>::set(Math::Vec4 value) const {
    glUniform4f(_location, value.x, value.y, value.z, value.w);
}

// Specialization for Math::mat4
template <>
inline void Shader::Uniform<Math::Mat4>::set(Math::Mat4 value) const {
    glUniformMatrix4fv(_location, 1, GL_FALSE, Math::valuePtr(value));
}

template <class T>
inline void Shader::Uniform<T>::set(T value) const {
    cerr << "Unsupported shader data type!";
}
#pragma once
#include <math.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Math {
    // Types
    using Vec2 = glm::vec2;
    using Vec3 = glm::vec3;
    using Vec4 = glm::vec4;
    using Mat3 = glm::mat3;
    using Mat4 = glm::mat4;

    // Common operations
    inline Mat4 identity() {
        return glm::mat4(1.0f);
    }

    inline Mat4 translate(const Mat4& mat, const Vec3& offset) {
        return glm::translate(mat, offset);
    }

    inline Mat4 rotate(const Mat4& mat, float angleRadians, const Vec3& axis) {
        return glm::rotate(mat, angleRadians, axis);
    }

    inline Mat4 scale(const Mat4& mat, const Vec3& factors) {
        return glm::scale(mat, factors);
    }

    inline Mat4 perspective(float fovRadians, float aspect, float nearZ, float farZ) {
        return glm::perspective(fovRadians, aspect, nearZ, farZ);
    }

    inline Mat4 lookAt(const Vec3& eye, const Vec3& center, const Vec3& up) {
        return glm::lookAt(eye, center, up);
    }

    // Convert to pointer for passing to graphics APIs
    inline const float* valuePtr(const Mat4& mat) {
        return glm::value_ptr(mat);
    }

    inline const double pi = M_PI;
    inline const double degToRad = pi/180;
    inline const double radToDeg = 180/pi;
}
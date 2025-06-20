#include "camera.hpp"
#include "../core.hpp"

Math::Mat4 Camera::getView()
{
    return Math::lookAt(position, position + getFront(), getUp());
}

Math::Vec3 Camera::getFront()
{
    Math::Vec3 direction;
    direction.x = cos(Math::degToRad * yaw) * cos(Math::degToRad * pitch);
    direction.y = sin(Math::degToRad * pitch);
    direction.z = sin(Math::degToRad * yaw) * cos(Math::degToRad * pitch);
    Math::Vec3 cameraFront = Math::normalize(direction);
    return cameraFront;
}

Math::Vec3 Camera::getUp()
{
    return Math::Vec3(0.0f, 1.0f, 0.0f);
}

Math::Vec3 Camera::getRight()
{
    return Math::normalize(Math::cross(getFront(), getUp()));
}
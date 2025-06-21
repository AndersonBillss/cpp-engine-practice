#include "cameraController.hpp"

void CameraController::process(double deltaTime)
{
    float lookSpeedX = 0.1f;
    float lookSpeedY = 0.1f;
    if (firstMouse)
    {
        firstMouse = false;
    }
    else
    {
        _cam->yaw -= _window->getMouseChangeX() * lookSpeedX;
        _cam->pitch += _window->getMouseChangeY() * lookSpeedY;
    }
    if (_cam->pitch > 89.0f)
        _cam->pitch = 89.0f;
    if (_cam->pitch < -89.0f)
        _cam->pitch = -89.0f;

    const float cameraSpeed = 5.0f * deltaTime;
    float calculatedSpeed = cameraSpeed;

    Math::Vec3 camFront = _cam->getFront();
    Math::Vec3 camUp = _cam->getUp();
    Math::Vec3 camRight = _cam->getRight();
    if (_window->isHeld(Key::LeftControl))
        calculatedSpeed = cameraSpeed * 3;
    if (_window->isHeld(Key::W))
        _cam->position += calculatedSpeed * camFront;
    if (_window->isHeld(Key::S))
        _cam->position -= calculatedSpeed * camFront;
    if (_window->isHeld(Key::A))
        _cam->position -= calculatedSpeed * camRight;
    if (_window->isHeld(Key::D))
        _cam->position += calculatedSpeed * camRight;
    if (_window->isHeld(Key::Space))
        _cam->position += calculatedSpeed * camUp;
    if (_window->isHeld(Key::LeftShift))
        _cam->position -= calculatedSpeed * camUp;

    _shaderView->set(_cam->getView());
}
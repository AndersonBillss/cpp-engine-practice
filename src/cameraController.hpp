#include "ctx/camera.hpp"
#include "ctx/shader.hpp"
#include "ctx/window.hpp"
#include "math.hpp"
#include <functional>
using std::function;

class CameraController
{
public:
    CameraController(Shader::Uniform<Math::Mat4> *shaderView, Window *window)
    {
        _cam = new Camera();
        _shaderView = shaderView;
        _window = window;
    }
    void process(double deltaTime);

private:
    bool firstMouse = true;
    Camera *_cam;
    Shader::Uniform<Math::Mat4> *_shaderView;
    Window *_window;
};
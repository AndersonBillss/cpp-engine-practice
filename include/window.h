#pragma once
#include "mesh.h"
#include <GLFW/glfw3.h>
#include <string>
using std::string;
#include <functional>
using std::function;

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    bool shouldClose() const;
    double getTime() const;
    double getDeltaTime() const;

    void swapBuffers() const;
    void pollEvents() const;
    void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    void processInput();
    void close();

    void process(function<void(double deltaTime)> callback);

private:
    GLFWwindow* _window;

    double _deltaTime;
    double _lastTime;
};

#pragma once
#include "ctx.h"
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
    double getTime();

    void swapBuffers() const;
    void pollEvents() const;
    void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    void processInput();
    void close();

    Ctx* getCtx();

    void process(function<void()> callback);

private:
    GLFWwindow* _window;
    Ctx* _ctx;
};

#pragma once
#ifndef WINDOW_H
#define WINDOW_H
#include <GLFW/glfw3.h>
#include <string>
using std::string;

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

private:
    GLFWwindow* _window;
};

#endif
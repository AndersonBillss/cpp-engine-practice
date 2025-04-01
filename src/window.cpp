#include "window.h"
#include <iostream>
using std::string, std::cerr;

Window::Window(int width, int height, const char* title){
    // Initialize GLFW
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW\n";
        exit(-1);
    }

    // OpenGL 3.3 Core Profile
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    _window = glfwCreateWindow(width, height, title, NULL, NULL);

    // Create the window
    if (!_window) {
        cerr << "Failed to create GLFW window\n";
        glfwTerminate();
        exit(-1);
    }
    // Initialize GLEW
    glfwMakeContextCurrent(_window);
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        exit(-1);
    }
    _ctx = new Ctx();
}

Window::~Window(){
    glfwDestroyWindow(_window);
    glfwTerminate();
    delete _ctx;
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(_window);
}
double Window::getTime() {
    return glfwGetTime();
}

void Window::swapBuffers() const {
    glfwSwapBuffers(_window);
}
void Window::pollEvents() const {
    glfwPollEvents();
}
void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}
void Window::processInput() {
    if (glfwGetKey(_window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(_window, true);
}
void Window::close() {
    glfwSetWindowShouldClose(_window, true);
}

Ctx* Window::getCtx(){
    return _ctx;
}

void Window::process(function<void()> callback) {
    processInput();
    _ctx->process(callback);
    swapBuffers();
    pollEvents();
}



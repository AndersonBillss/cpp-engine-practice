#include "window.h"
#include <iostream>
using std::cerr;

constexpr std::array<Key, 61> allKeys = {
    Key::A, Key::B, Key::C, Key::D, Key::E, Key::F, Key::G,
    Key::H, Key::I, Key::J, Key::K, Key::L, Key::M, Key::N,
    Key::O, Key::P, Key::Q, Key::R, Key::S, Key::T, Key::U,
    Key::V, Key::W, Key::X, Key::Y, Key::Z,

    Key::Num0, Key::Num1, Key::Num2, Key::Num3, Key::Num4,
    Key::Num5, Key::Num6, Key::Num7, Key::Num8, Key::Num9,

    Key::Escape, Key::Enter, Key::Tab, Key::Backspace,
    Key::Insert, Key::Delete, Key::Right, Key::Left, Key::Down, Key::Up,
    Key::PageUp, Key::PageDown, Key::Home, Key::End,

    Key::Space, Key::LeftShift, Key::RightShift,
    Key::LeftControl, Key::RightControl,
    Key::LeftAlt, Key::RightAlt
};


static const unordered_map<int, Key> GLFWToKey {    
    {GLFW_KEY_A, Key::A},
    {GLFW_KEY_B, Key::B},
    {GLFW_KEY_C, Key::C},
    {GLFW_KEY_D, Key::D},
    {GLFW_KEY_E, Key::E},
    {GLFW_KEY_F, Key::F},
    {GLFW_KEY_G, Key::G},
    {GLFW_KEY_H, Key::H},
    {GLFW_KEY_I, Key::I},
    {GLFW_KEY_J, Key::J},
    {GLFW_KEY_K, Key::K},
    {GLFW_KEY_L, Key::L},
    {GLFW_KEY_M, Key::M},
    {GLFW_KEY_N, Key::N},
    {GLFW_KEY_O, Key::O},
    {GLFW_KEY_P, Key::P},
    {GLFW_KEY_Q, Key::Q},
    {GLFW_KEY_R, Key::R},
    {GLFW_KEY_S, Key::S},
    {GLFW_KEY_T, Key::T},
    {GLFW_KEY_U, Key::U},
    {GLFW_KEY_V, Key::V},
    {GLFW_KEY_W, Key::W},
    {GLFW_KEY_X, Key::X},
    {GLFW_KEY_Y, Key::Y},
    {GLFW_KEY_Z, Key::Z},

    {GLFW_KEY_0, Key::Num0},
    {GLFW_KEY_1, Key::Num1},
    {GLFW_KEY_2, Key::Num2},
    {GLFW_KEY_3, Key::Num3},
    {GLFW_KEY_4, Key::Num4},
    {GLFW_KEY_5, Key::Num5},
    {GLFW_KEY_6, Key::Num6},
    {GLFW_KEY_7, Key::Num7},
    {GLFW_KEY_8, Key::Num8},
    {GLFW_KEY_9, Key::Num9},

    {GLFW_KEY_ESCAPE,    Key::Escape},
    {GLFW_KEY_ENTER,     Key::Enter},
    {GLFW_KEY_TAB,       Key::Tab},
    {GLFW_KEY_BACKSPACE, Key::Backspace},
    {GLFW_KEY_INSERT,    Key::Insert},
    {GLFW_KEY_DELETE,    Key::Delete},
    {GLFW_KEY_RIGHT,     Key::Right},
    {GLFW_KEY_LEFT,      Key::Left},
    {GLFW_KEY_DOWN,      Key::Down},
    {GLFW_KEY_UP,        Key::Up},
    {GLFW_KEY_PAGE_UP,   Key::PageUp},
    {GLFW_KEY_PAGE_DOWN, Key::PageDown},
    {GLFW_KEY_HOME,      Key::Home},
    {GLFW_KEY_END,       Key::End},

    {GLFW_KEY_SPACE,         Key::Space},
    {GLFW_KEY_LEFT_SHIFT,    Key::LeftShift},
    {GLFW_KEY_RIGHT_SHIFT,   Key::RightShift},
    {GLFW_KEY_LEFT_CONTROL,  Key::LeftControl},
    {GLFW_KEY_RIGHT_CONTROL, Key::RightControl},
    {GLFW_KEY_LEFT_ALT,      Key::LeftAlt},
    {GLFW_KEY_RIGHT_ALT,     Key::RightAlt},

    {GLFW_KEY_UNKNOWN, Key::Unknown}
};

static const unordered_map<Key, int> keyToGLFW {
    {Key::A, GLFW_KEY_A},
    {Key::B, GLFW_KEY_B},
    {Key::C, GLFW_KEY_C},
    {Key::D, GLFW_KEY_D},
    {Key::E, GLFW_KEY_E},
    {Key::F, GLFW_KEY_F},
    {Key::G, GLFW_KEY_G},
    {Key::H, GLFW_KEY_H},
    {Key::I, GLFW_KEY_I},
    {Key::J, GLFW_KEY_J},
    {Key::K, GLFW_KEY_K},
    {Key::L, GLFW_KEY_L},
    {Key::M, GLFW_KEY_M},
    {Key::N, GLFW_KEY_N},
    {Key::O, GLFW_KEY_O},
    {Key::P, GLFW_KEY_P},
    {Key::Q, GLFW_KEY_Q},
    {Key::R, GLFW_KEY_R},
    {Key::S, GLFW_KEY_S},
    {Key::T, GLFW_KEY_T},
    {Key::U, GLFW_KEY_U},
    {Key::V, GLFW_KEY_V},
    {Key::W, GLFW_KEY_W},
    {Key::X, GLFW_KEY_X},
    {Key::Y, GLFW_KEY_Y},
    {Key::Z, GLFW_KEY_Z},

    {Key::Num0, GLFW_KEY_0},
    {Key::Num1, GLFW_KEY_1},
    {Key::Num2, GLFW_KEY_2},
    {Key::Num3, GLFW_KEY_3},
    {Key::Num4, GLFW_KEY_4},
    {Key::Num5, GLFW_KEY_5},
    {Key::Num6, GLFW_KEY_6},
    {Key::Num7, GLFW_KEY_7},
    {Key::Num8, GLFW_KEY_8},
    {Key::Num9, GLFW_KEY_9},

    {Key::Escape,    GLFW_KEY_ESCAPE},
    {Key::Enter,     GLFW_KEY_ENTER},
    {Key::Tab,       GLFW_KEY_TAB},
    {Key::Backspace, GLFW_KEY_BACKSPACE},
    {Key::Insert,    GLFW_KEY_INSERT},
    {Key::Delete,    GLFW_KEY_DELETE},
    {Key::Right,     GLFW_KEY_RIGHT},
    {Key::Left,      GLFW_KEY_LEFT},
    {Key::Down,      GLFW_KEY_DOWN},
    {Key::Up,        GLFW_KEY_UP},
    {Key::PageUp,    GLFW_KEY_PAGE_UP},
    {Key::PageDown,  GLFW_KEY_PAGE_DOWN},
    {Key::Home,      GLFW_KEY_HOME},
    {Key::End,       GLFW_KEY_END},

    {Key::Space,        GLFW_KEY_SPACE},
    {Key::LeftShift,    GLFW_KEY_LEFT_SHIFT},
    {Key::RightShift,   GLFW_KEY_RIGHT_SHIFT},
    {Key::LeftControl,  GLFW_KEY_LEFT_CONTROL},
    {Key::RightControl, GLFW_KEY_RIGHT_CONTROL},
    {Key::LeftAlt,      GLFW_KEY_LEFT_ALT},
    {Key::RightAlt,     GLFW_KEY_RIGHT_ALT},

    {Key::Unknown,       GLFW_KEY_UNKNOWN}
};


// Set the viewport to change with window resizing
void framebuffer_size_callback(GLFWwindow* window, int width, int height) { glViewport(0, 0, width, height); }
Window::Window(int width, int height, const char* title){
    // Initialize GLFW
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW\n";
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
    glfwSetFramebufferSizeCallback(_window, framebuffer_size_callback);

    _lastTime = getTime();

    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW\n";
        exit(-1);
    }
}

Window::~Window(){
    glfwDestroyWindow(_window);
    glfwTerminate();
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(_window);
}
double Window::getTime() const {
    return glfwGetTime();
}
double Window::getDeltaTime() const {
    return _deltaTime;
}

bool Window::isJustPressed(Key key) const {
    return _currentHeldKeys.find(key) != _currentHeldKeys.end() &&
           _lastFrameHeldKeys.find(key) == _lastFrameHeldKeys.end();
}
bool Window::isHeld(Key key) const {
    return _currentHeldKeys.find(key) != _currentHeldKeys.end() &&
           _lastFrameHeldKeys.find(key) != _lastFrameHeldKeys.end();
}

bool Window::isJustReleased(Key key) const {
    return _currentHeldKeys.find(key) == _currentHeldKeys.end() &&
           _lastFrameHeldKeys.find(key) != _lastFrameHeldKeys.end();
}

void Window::close() {
    glfwSetWindowShouldClose(_window, true);
}

void Window::process(function<void(double deltaTime)> callback) {
    _deltaTime = getTime() - _lastTime;
    _lastTime = getTime();
    _lastFrameHeldKeys = _currentHeldKeys;
    _currentHeldKeys.clear();

    for (Key key : allKeys) {
        int state = glfwGetKey(_window, keyToGLFW.at(key));
        if (state == GLFW_PRESS || state == GLFW_REPEAT) {
            _currentHeldKeys.insert(key);
        }
    }
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    callback(_deltaTime);
    glfwSwapBuffers(_window);
    glfwPollEvents();
}

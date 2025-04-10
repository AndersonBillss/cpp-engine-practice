#pragma once
#include "mesh.h"
#include <GLFW/glfw3.h>
#include <string>
using std::string;
#include <functional>
using std::function;
#include <unordered_set>
using std::unordered_set;
#include <unordered_map>
using std::unordered_map;
#include <vector>
using std::vector;

enum class Key {    
    Unknown = -1,
    A, B, C, D, E, F, G,
    H, I, J, K, L, M, N,
    O, P, Q, R, S, T, U,
    V, W, X, Y, Z,

    Num0, Num1, Num2, Num3, Num4,
    Num5, Num6, Num7, Num8, Num9,

    Escape, Enter, Tab, Backspace,
    Insert, Delete, Right, Left, Down, Up,
    PageUp, PageDown, Home, End,

    Space, LeftShift, RightShift,
    LeftControl, RightControl,
    LeftAlt, RightAlt,
};

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    bool shouldClose() const;
    double getTime() const;
    double getDeltaTime() const;

    bool isJustPressed(Key key) const;
    bool isHeld(Key key) const;
    bool isJustReleased(Key key) const;

    void close();
    
    void process(function<void(double deltaTime)> callback);
    
private:
    GLFWwindow* _window;
    
    double _deltaTime;
    double _lastTime;
    
    unordered_set<Key> _currentHeldKeys;
    unordered_set<Key> _lastFrameHeldKeys;
};

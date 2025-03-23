#pragma once
#ifndef WINDOW_H
#define WINDOW_H

class Window {
public:
    Window(int width, int height, const char* title);
    ~Window();

    void Run();
private:
    int width, height;
    const char* title;
};

#endif
#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "Camera.h"

// In the future : to be an interface so there can be a linux window, windows...
class Window {
private:
    inline static GLFWwindow *window;
    std::string title;
    int width;
    int height;

public:
    Window() {}

    // Getters
    int GetWidth();
    int GetHeight();
    GLFWwindow * GetWindow();

    // Creation
    void Create(const std::string title = "GLtemplate",
            int width = 1800,
            int height = 950);
};
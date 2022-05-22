#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <string>

#include "Camera.h"

namespace GLhf
{

    // In the future : to be an interface so there can be a linux window, windows...
    class Window {
    private:
        inline static GLFWwindow *glfw_window_;
        std::string title_;
        int width_;
        int height_;

    public:
        Window() {}

        // Getters
        int GetWidth();
        int GetHeight();
        GLFWwindow * GetWindow();

        // Creation
        void Create(const std::string title = "GLhf",
                int width = 1800,
                int height = 950);
    };

}
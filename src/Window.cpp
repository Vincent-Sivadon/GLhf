#include "Window.h"

namespace GLhf
{

    void Window::Create(const std::string title, int width, int height)
    {
        // Define member variables
        title_ = title;
        width_ = width;
        height_ = height;

        // GLFW initialization
        // -------------------
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // GLFW window creation
        // -------------------
        glfw_window_ = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
        if (glfw_window_ == NULL)
        {
            throw "Failed to create GLFW window";
            glfwTerminate();
        }
        glfwMakeContextCurrent(glfw_window_);
        glfwSetInputMode(glfw_window_, GLFW_STICKY_KEYS, GLFW_TRUE);

        // tell GLFW to capture our mouse
        glfwSetInputMode(glfw_window_, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

        // GLEW Initialization
        // -------------------
        if (glewInit() != GLEW_OK)
            throw "Failed to initialize GLEW";

        // Blending Mode
        // -------------
        glEnable(GL_BLEND);
        glEnable(GL_DEPTH_TEST);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }


    int Window::GetWidth()
    {
        glfwGetWindowSize(glfw_window_, &width_, &height_);
        return width_;
    }

    int Window::GetHeight()
    {
        glfwGetWindowSize(glfw_window_, &width_, &height_);
        return height_;
    }

    GLFWwindow *Window::GetWindow()
    {
        return glfw_window_;
    }

}
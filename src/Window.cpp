#include "Window.h"

void Window::Create(const std::string title_, int width_, int height_)
{
    // Define member variables
    title = title_;
    width = width_;
    height = height_;

    // GLFW initialization
    // -------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // GLFW window creation
    // -------------------
    window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
    if (window == NULL)
    {
        throw "Failed to create GLFW window";
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GLFW_TRUE);

    // tell GLFW to capture our mouse
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // GLAD Initialization
    // -------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        throw "Failed to initialize GLAD";

    // Blending Mode
    // -------------
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}


int Window::GetWidth()
{
    glfwGetWindowSize(window, &width, &height);
    return width;
}

int Window::GetHeight()
{
    glfwGetWindowSize(window, &width, &height);
    return height;
}

GLFWwindow *Window::GetWindow()
{
    return window;
}
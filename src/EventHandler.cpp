#include "EventHandler.h"

namespace GLhf
{

    void EventHandler::Create(Camera * camera_)
    {
        camera = camera_;
        SetEventCallback();
    }

    void EventHandler::SetEventCallback()
    {
        // Set center
        int width, height;
        GLFWwindow * glfw_window = window->GetWindow();
        glfwGetWindowSize(glfw_window, &width, &height);
        lastX = width / 2.0f;
        lastY = height / 2.0f;

        glfwMakeContextCurrent(glfw_window);

        auto FrameBuffer_Callback_Lambda = [](GLFWwindow *w, int width_, int height_)
        {
            FramebufferSizeCallback(width_, height_);
        };
        auto Mouse_Callback_Lambda = [](GLFWwindow *w, double xpos, double ypos)
        {
            MouseCallback(xpos, ypos);
        };
        auto Key_Callback_Lambda = [](GLFWwindow *w, int key, int scancode, int action, int mods)
        {
            KeyCallback(key, scancode, action, mods);
        };
        auto Scroll_Callback_Lambda = [](GLFWwindow *w, double xoffset, double yoffset)
        {
            ScrollCallback(xoffset, yoffset);
        };

        // Set Callback Functions
        glfwSetFramebufferSizeCallback(glfw_window, FrameBuffer_Callback_Lambda);
        glfwSetCursorPosCallback(glfw_window, Mouse_Callback_Lambda);
        glfwSetKeyCallback(glfw_window, Key_Callback_Lambda);
        glfwSetScrollCallback(glfw_window, Scroll_Callback_Lambda);
    }

    void EventHandler::FramebufferSizeCallback(int width, int height)
    {
        glViewport(0, 0, width, height);
    }

    void EventHandler::MouseCallback(double xpos, double ypos)
    {
        if (firstMouse)
        {
            lastX = xpos;
            lastY = ypos;
            firstMouse = false;
        }

        float xoffset = xpos - lastX;
        float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

        lastX = xpos;
        lastY = ypos;

        camera->ProcessMouseMovement(xoffset, yoffset);
    }

    void EventHandler::KeyCallback(int key, int scancode, int action, int mods)
    {
        switch (key)
        {
            case GLFW_KEY_ESCAPE:
                if (action==GLFW_PRESS)
                    glfwSetWindowShouldClose(window->GetWindow(), true);
                break;

            case GLFW_KEY_W:
                if (action == GLFW_PRESS) keys.W = true;
                else if (action == GLFW_RELEASE) keys.W = false;
                break;
            case GLFW_KEY_S:
                if (action == GLFW_PRESS) keys.S = true;
                else if (action == GLFW_RELEASE) keys.S = false;
                break;
            case GLFW_KEY_A:
                if (action == GLFW_PRESS) keys.A = true;
                else if (action == GLFW_RELEASE) keys.A = false;
                break;
            case GLFW_KEY_D:
                if (action == GLFW_PRESS) keys.D = true;
                else if (action == GLFW_RELEASE) keys.D = false;
                break;
                    
            case GLFW_KEY_SPACE:
                if (action == GLFW_PRESS) keys.SPACE = true;
                else if (action == GLFW_RELEASE) keys.SPACE = false;
                break;
            case GLFW_KEY_LEFT_SHIFT:
                if (action == GLFW_PRESS) keys.LEFT_SHIFT = true;
                else if (action == GLFW_RELEASE) keys.LEFT_SHIFT = false;
                break;

            default:
                break;
        }
    }

    void EventHandler::ScrollCallback(double xoffset, double yoffset)
    {
        if (yoffset>0)
            camera->ProcessKeyboard(FORWARD, 0.1f);
        else
            camera->ProcessKeyboard(BACKWARD, 0.1f);
    }


    void EventHandler::Process(float dt)
    {
        if (keys.W) camera->ProcessKeyboard(FORWARD, dt);
        if (keys.S) camera->ProcessKeyboard(BACKWARD, dt);
        if (keys.A) camera->ProcessKeyboard(LEFT, dt);
        if (keys.D) camera->ProcessKeyboard(RIGHT, dt);
        if (keys.SPACE) camera->ProcessKeyboard(UP, dt);
        if (keys.LEFT_SHIFT) camera->ProcessKeyboard(DOWN, dt);
    }

}
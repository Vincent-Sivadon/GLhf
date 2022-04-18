#include "App.h"

#include <iostream>

// App's main function
void App::Run()
{
    // GLFW initialization
    // -------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // GLFW window creation
    // -------------------
    window = glfwCreateWindow(WIDTH, HEIGHT, "Experimentation", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    // tell GLFW to capture our mouse
    // glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // GLAD Initialization
    // -------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        std::cout
            << "Failed to initialize GLAD" << std::endl;

    // Blending Mode
    // -------------
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // CALLBACK functions initialization
    // ---------------------------------
    initCallbackFunctions();

    // Overrided function
    // ------------------
    Startup();

    // Game loop
    // ----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // -------------------
        float ct = static_cast<float>(glfwGetTime());
        dt = ct - lt;
        lt = ct;

        // Input management
        defaultProcessInput();
        ProcessInput();

        // Rendering
        // ---------
        static const GLfloat black[] = {0.f, 0.f, 0.f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, black);

        // Draw every shapes
        for (Shape *shape : shapes)
        {
            shape->SetView(camera.GetViewMatrix());
            shape->Draw();
        }

        glfwSwapBuffers(window);

        // Input
        // -----
        glfwPollEvents();
    }

    // Clean memory
    // ------------
    for (Shape *shape : shapes)
        shape->Destroy();
    Shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void App::defaultProcessInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, dt);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, dt);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, dt);
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
        camera.ProcessKeyboard(UP, dt);
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
        camera.ProcessKeyboard(DOWN, dt);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void App::framebuffer_size_callback(int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void App::mouse_callback(double xposIn, double yposIn)
{
    float xpos = static_cast<float>(xposIn);
    float ypos = static_cast<float>(yposIn);

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

    // Line to de-comment if we want the camera to move with mouse
    // camera.ProcessMouseMovement(xoffset, yoffset);
}

void App::initCallbackFunctions()
{
    lastX = WIDTH / 2.0f;

    glfwMakeContextCurrent(window);

    // Glfw does not accept member function pointers as callback functions,
    // nor does it accept function objects.
    // You can only register function pointers.
    // Function pointers cannot point to non-static member functions
    // So this requiere a bit of dark magic
    auto FrameBuffer_Callback_Lambda = [](GLFWwindow *w, int width, int height)
    {
        framebuffer_size_callback(width, height);
    };
    auto Mouse_Callback_Lambda = [](GLFWwindow *w, double xpos, double ypos)
    {
        mouse_callback(xpos, ypos);
    };

    // Set Callback Functions
    glfwSetFramebufferSizeCallback(window, FrameBuffer_Callback_Lambda);
    glfwSetCursorPosCallback(window, Mouse_Callback_Lambda);
}
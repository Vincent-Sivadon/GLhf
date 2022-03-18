#include "App.h"

#include <iostream>

// App's main function
void App::run()
{
    // GLFW initialization
    // -------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Window Parameters
    // -------------------
    WIDTH = 1000;
    HEIGHT = 800;

    // GLFW window creation
    // -------------------
    window = glfwCreateWindow(WIDTH, HEIGHT, "Experimentation", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);

    // GLAD Initialization
    // -------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        std::cout
            << "Failed to initialize GLAD" << std::endl;

    // CALLBACK functions initialization
    // ---------------------------------
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // Overrided function
    // ------------------
    startup();

    // Game loop
    // ----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // -------------------
        float ct = static_cast<float>(glfwGetTime());
        dt = ct - lt;
        lt = ct;

        // Rendering
        // ---------
        render(glfwGetTime());
        glfwSwapBuffers(window);

        // Input
        // -----
        glfwPollEvents();
        processInput();
    }

    // Clean memory
    // ------------
    shutdown();
    glfwDestroyWindow(window);
    glfwTerminate();
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void App::processInput()
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

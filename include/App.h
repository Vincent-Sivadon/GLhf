/* Abstract Class Application to be implemented */

#pragma once

#include "Camera.h"
#include "Shape.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <GL/glext.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

// Callback functions
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void mouse_callback(GLFWwindow *window, double xpos, double ypos);

/*
 * ------------- Abstract Class Application -------------
 * A program that uses this paradigm should look like :
 * class ExampleApp : public App
 * {
 * public:
 *     void Startup() override {}           // Initialize OpenGL or GLtemplate objects
 *     void Render() override {}            // Manual Rendering protocole
 *     void ProcessInput() override {}      // Manual Input Management (on top of default ones)
 *     void Shutdown() override {}          // Manual Memory cleaning
 * private:
 *     int member;
 * }
 * -----------------------------------
 * DECLARE_MAIN(ExampleApp);
 * -----------------------------------
 * The main will look like :
 *    - Glad and GLFW initialization
 *    - while loop with :
 *        - framerate management
 *        - rendering
 *        - input management
 *    - memory cleaning
 * -----------------------------------
 *
 * Although, this library provides primitives that will makes things easier :
 * class ExamplePrimitiveApp : public App
 * {
 * public:
 *     void Startup() override {
 *          disk.Create();
 *          AddShape(&disk);
 *     }
 * private:
 *     Disk disk;
 * }
 */
class App
{
public:
    App() {}
    virtual ~App() = default;

    // App's main function
    void Run();

    // Functions to be implemented
    virtual void Startup() = 0;     // Initialize OpenGL objects
    virtual void Render(double ct); // Rendering protocole
    void defaultProcessInput();     // Default Input Management
    virtual void ProcessInput();    // Input Management (dev)
    virtual void Shutdown();        // Memory cleaning

    // Window
    inline static int WIDTH = 1800.0f;
    inline static int HEIGHT = 950.0f;

    inline static Camera camera;
    inline static bool firstMouse = true;
    inline static float lastX = WIDTH / 2.0f;
    inline static float lastY = HEIGHT / 2.0f;

    // Game Objects
    void AddShape(Shape *shape) { shapes.push_back(shape); }

protected:
    std::vector<Shape *> shapes;

    GLFWwindow *window;

    // Frames variables
    float dt = 0;
    float lt = 0;

    // Callback functions
    void initCallbackFunctions(); // Set event callback functions
    static void framebuffer_size_callback(int width, int height);
    static void mouse_callback(double xpos, double ypos);
};

// Useless for now
void App::Render(double ct) {}

// More input management
void App::ProcessInput() {}

// More memory cleaning
void App::Shutdown() {}

// Automatic main constructor
#define DECLARE_MAIN(a)                    \
    int main(int argc, const char **argv)  \
    {                                      \
        a *app = new a;                    \
        try                                \
        {                                  \
            app->Run();                    \
        }                                  \
        catch (const char *msg)            \
        {                                  \
            std::cerr << msg << std::endl; \
        }                                  \
        delete app;                        \
        return 0;                          \
    }

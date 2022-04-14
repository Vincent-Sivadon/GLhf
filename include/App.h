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
 *     void startup() override {}           // Initialize OpenGL objects
 *     void render() override {}            // Rendering protocole
 *     void ProcessInput() override {}      // Input Management (on top of default ones)
 *     void shutdown() override {}          // Memory cleaning
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
 */
class App
{
public:
    App() {}
    virtual ~App() = default;

    // App's main function
    void Run();

    // Functions to be implemented
    virtual void Startup() = 0;         // Initialize OpenGL objects
    virtual void Render(double ct) = 0; // Rendering protocole
    void defaultProcessInput();         // Default Input Management
    virtual void ProcessInput() = 0;    // Input Management (user)
    virtual void Shutdown() = 0;        // Memory cleaning

    // Window
    inline static int WIDTH = 1000.0f;
    inline static int HEIGHT = 800.0f;

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

// Automatic main constructor
#define DECLARE_MAIN(a)                   \
    int main(int argc, const char **argv) \
    {                                     \
        a *app = new a;                   \
        app->Run();                       \
        delete app;                       \
        return 0;                         \
    }

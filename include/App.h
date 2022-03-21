/* Abstract Class Application to be implemented */

#pragma once

#include <glad/glad.h>

#include <GLFW/glfw3.h>
#include <GL/glext.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// Callback functions
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

/*
 * ------------- Abstract Class Application -------------
 * A program that uses this paradigm should look like :
 * class ExampleApp : public App
 * {
 * public:
 *     void startup() override {}           // Initialize OpenGL objects
 *     void render() override {}            // Rendering protocole
 *     void processInput() override {}      // Input Management
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
    void run();

    // Functions to be implemented
    virtual void startup() = 0;         // Initialize OpenGL objects
    virtual void render(double ct) = 0; // Rendering protocole
    virtual void processInput();        // Input Management
    virtual void shutdown() = 0;        // Memory cleaning

protected:
    // Window
    int WIDTH;
    int HEIGHT;
    GLFWwindow *window;

    // Frames variables
    float dt = 0;
    float lt = 0;
};

// Automatic main constructor
#define DECLARE_MAIN(a)                   \
    int main(int argc, const char **argv) \
    {                                     \
        a *app = new a;                   \
        app->run();                       \
        delete app;                       \
        return 0;                         \
    }

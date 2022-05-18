#pragma once

#include <Camera.h>
#include <Shape.h>
#include <Window.h>
#include <EventHandler.h>

#include <GLFW/glfw3.h>
#include <GL/glext.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>

namespace GLhf
{

    /* See examples/app for an example of how to use this structure */
    class App
    {
    public:
        App() {}
        virtual ~App() = default;

        // App's main function
        void Run();

        // Functions to be implemented
        virtual void SetMainArgs(int argc, const char **argv);
        virtual void Startup() = 0;     // Initialize OpenGL objects
        virtual void Render(double ct); // Rendering protocole
        virtual void PollEvents(double ct);    // Input Management (dev)
        virtual void Shutdown();        // Memory cleaning

        // Game Objects
        void AddShape(Shape *shape) { shapes.push_back(shape); }

    protected:
        std::vector<Shape *> shapes;

        Window window;
        EventHandler event_handler;
        Camera camera;

        int argc;
        const char **argv;

        // Frames variables
        float dt = 0;
        float lt = 0;

    };

    // Set main arguments
    void App::SetMainArgs(int argc, const char **argv)
    {
        this->argc = argc;
        this->argv = argv;
    }

    // Useless for now
    void App::Render(double ct) {}

    // More input management
    void App::PollEvents(double ct) {}

    // More memory cleaning
    void App::Shutdown() {}

    // Automatic main constructor
    #define DECLARE_MAIN(a)                    \
        int main(int argc, const char **argv)  \
        {                                      \
            a *app = new a;                    \
            try                                \
            {                                  \
                app->SetMainArgs(argc, argv);  \
                app->Run();                    \
            }                                  \
            catch (const char *msg)            \
            {                                  \
                std::cerr << msg << std::endl; \
            }                                  \
            delete app;                        \
            return 0;                          \
        }

}
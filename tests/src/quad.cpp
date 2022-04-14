/* Supposed to print a orange quad on a green background */

#include "../include/GLtemplate.h"
#include "../primitives/Quad.h"

#include <iostream>
#include <string>

class QuadTest : public App
{
public:
    void Startup() override
    {
        camera.Set(0.0f, 0.0f, 4.0f);
        quad.Init(this);
        quad.SetView(camera.GetViewMatrix());
    }

    void Render(double time) override
    {
        static const GLfloat green[] = {0.0f, 0.25f, 0.0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, green);

        quad.SetView(camera.GetViewMatrix());
        quad.Draw();
    }

    void ProcessInput() override
    {
        // exit(0);
    }

    void Shutdown() override
    {
        quad.Destroy();
    }

private:
    Quad quad;
};

DECLARE_MAIN(QuadTest);
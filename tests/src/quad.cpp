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
        quad.Init();
    }

    void Render(double time) override
    {
        static const GLfloat green[] = {0.0f, 0.25f, 0.0f, 1.0f};
        glClearBufferfv(GL_COLOR, 0, green);

        // Translation
        glm::vec3 vec(0.5f * time, 0.5f * time, 0.0f);
        quad.ModelViewTranslatation(vec);

        quad.Draw(time);
    }

    void processInput()
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
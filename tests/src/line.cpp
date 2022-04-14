/* Supposed to print a orange quad on a green background */

#include "../include/GLtemplate.h"
#include "../primitives/Line.h"

#include <iostream>
#include <string>

class LineTest : public App
{
public:
    void Startup() override
    {
        line.Init(this, -0.5f, -0.5f, 0.5f, 0.5f);
    }

    void Render(double time) override
    {
        // static const GLfloat green[] = {0.0f, 0.25f, 0.0f, 1.0f};
        // glClearBufferfv(GL_COLOR, 0, green);

        // std::cout << color.y << std::endl;
        line.Draw();
    }

    void ProcessInput() override
    {
        // exit(0);
    }

    void Shutdown() override
    {
        line.Destroy();
    }

private:
    Line line;
};

DECLARE_MAIN(LineTest);
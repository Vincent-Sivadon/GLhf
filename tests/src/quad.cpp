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
        quad.width = 0.5f;
        quad.pos = glm::vec3(2.0f, -1.0f, 0.0f);
        quad.Create(WIDTH, HEIGHT);
        quad.SetColor(1.0, 1.0, 1.0);

        quad2.Create(WIDTH, HEIGHT);
        quad2.SetPosition(-2.0f, -1.0f);
        quad2.SetColor(1.0, 1.0, 1.0);

        AddShape(&quad2);
        AddShape(&quad);
    }

    void Render(double time) override {}

    void ProcessInput() override {}

    void Shutdown() override {}

private:
    Quad quad;
    Quad quad2;
};

DECLARE_MAIN(QuadTest);
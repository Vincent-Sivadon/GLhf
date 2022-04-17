/* Supposed to print a orange quad on a green background */

#include "../include/GLtemplate.h"
#include "../primitives/InstancedDisk.h"

#include <iostream>
#include <string>
#include <math.h>
#include <unistd.h>

class InstancingTest : public App
{
public:
    void Startup() override
    {
        srand(getpid());

        int N = 20;

        // Properties
        instDisk.N = N;
        instDisk.positions = new glm::vec2[N];
        instDisk.radius = 0.05f;
        instDisk.color = glm::vec3(0.15f, 0.6f, 0.76f);

        // Positions
        for (int i = 0; i < instDisk.N; i++)
        {
            // Between -10 et 10
            float x = 1 * (2 * (float)rand() / (float)RAND_MAX - 1);
            float y = 1 * (2 * (float)rand() / (float)RAND_MAX - 1);
            instDisk.positions[i] = glm::vec2(x, y);
        }

        // Change shaders
        instDisk.SetShaderNames("instanced_shiny_shape.vs", "instanced_shiny_shape.fs");

        // Creation
        instDisk.Create();
        AddShape(&instDisk);
    }

    void Render(double time) override {}

    void ProcessInput() override {}

    void Shutdown() override {}

private:
    InstancedDisk instDisk;
};

DECLARE_MAIN(InstancingTest);
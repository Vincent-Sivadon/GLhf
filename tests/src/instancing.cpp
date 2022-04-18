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
        instDisk.width = 0.2f;
        instDisk.height = 0.2f;
        instDisk.color = glm::vec3(0.52941f, 0.36863f, 0.85490f);

        // Positions
        for (int i = 0; i < instDisk.N; i++)
        {
            // Between -1 et 1
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
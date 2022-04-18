/* Supposed to print a orange quad on a green background */

#include "../include/GLtemplate.h"
#include "../primitives/InstancedDisk.h"
#include "../primitives/InstancedEdge.h"

#include <iostream>
#include <string>
#include <math.h>
#include <unistd.h>
#include <algorithm>

class InstancingTest : public App
{
public:
    void Startup() override
    {
        srand(getpid());

        int N = 10;

        // Properties
        instDisk.N = N;
        instDisk.positions = new glm::vec2[N];
        instDisk.width = new float[N];
        instDisk.height = new float[N];
        instDisk.angle = new float[N];
        for (int i = 0; i < N; i++)
        {
            instDisk.width[i] = 0.2f;
            instDisk.height[i] = 0.2f;
            instDisk.angle[i] = 0.0f;
        }
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

        // Edges (complete graph)
        instEdge.InitPositions(instDisk.positions, N);
        instEdge.color = glm::vec3(1.0f, 1.0f, 1.0f);
        instEdge.SetShaderNames("instanced_shiny_shape.vs", "instanced_shiny_shape.fs");
        instEdge.Create();

        // Creation
        instDisk.Create();

        AddShape(&instDisk);
        AddShape(&instEdge);
    }

    void Render(double time) override {}

    void ProcessInput() override {}

    void Shutdown() override {}

private:
    InstancedDisk instDisk;
    InstancedEdge instEdge;
};

DECLARE_MAIN(InstancingTest);
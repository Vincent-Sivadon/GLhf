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

        int N = 100;

        // Disk
        instDisk.N = N;
        instDisk.color = glm::vec3(0.52941f, 0.36863f, 0.85490f);
        instDisk.SetShaderNames("instanced_shiny_shape.vs", "instanced_shiny_shape.fs");
        instDisk.Create();
        AddShape(&instDisk);

        // Edges (complete graph)
        instEdge.color = glm::vec3(1.0f, 1.0f, 1.0f);
        instEdge.InitPositions(instDisk.positions, N);
        instEdge.SetShaderNames("instanced_shape.vs", "shape.fs");
        instEdge.Create();
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
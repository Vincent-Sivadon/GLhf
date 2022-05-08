/* Supposed to print a orange quad on a green background */

#include <GLhf/GLhf.h>

#include <iostream>
#include <string>
#include <math.h>
#include <unistd.h>
#include <algorithm>

class Instancing : public GLhf::App
{
public:
    void Startup() override
    {
        srand(getpid());

        int N = 30;

        // Disk
        instDisk.N = N;
        instDisk.color = glm::vec3(0.52941f, 0.36863f, 0.85490f);
        instDisk.SetShaderNames("instanced_shiny_shape.vs", "instanced_shiny_shape.fs");
        instDisk.Create();

        // Edges (complete graph)
        instEdge.color = glm::vec3(1.0f, 1.0f, 1.0f);
        instEdge.InitCompleteGraph(instDisk.positions, N);
        instEdge.Create();

        this->AddShape(&instEdge);
        this->AddShape(&instDisk);
    }

private:
    GLhf::InstancedDisk instDisk;
    GLhf::InstancedEdge instEdge;
};

DECLARE_MAIN(Instancing);
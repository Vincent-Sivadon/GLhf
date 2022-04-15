/* Supposed to print a orange quad on a green background */

#include "../include/GLtemplate.h"
#include "../primitives/InstancedDisk.h"

#include <iostream>
#include <string>
#include <math.h>

class InstancingTest : public App
{
public:
    void Startup() override
    {
        instDisk.N = 2;
        instDisk.positions = new glm::vec2[2];
        instDisk.positions[0] = glm::vec2(-1.0f, -1.0f);
        instDisk.positions[1] = glm::vec2(1.0f, 1.0f);
        instDisk.color = glm::vec3(1.0f, 1.0f, 1.0f);
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
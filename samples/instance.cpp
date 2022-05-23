/* Supposed to print a orange quad on a green background */

#include <GLhf.h>

#include <iostream>
#include <string>
#include <math.h>
#include <vector>

class Light : public GLhf::App
{
public:
    void Startup() override
    {
        /* Texture Init */
        white.Create("../resources/white.png");
        brickwall.Create("../resources/brickwall.jpg");

        // Instance Cube
        std::vector<glm::vec3> positions(2);
        positions[0] = glm::vec3(0.0f);
        positions[1] = glm::vec3(-1.0f);
        instance_cube.SetTexture(white);
        instance_cube.SetColor(1.0f, 1.0f, 1.0f);
        instance_cube.Create(positions);

        // Cube
        cube.SetPosition(1.0f, 1.0f, 1.0f);
        cube.SetColor(0.4f, 0.15f, 0.85f);
        cube.SetTexture(white);
        cube.Create();

        scene_.Add(instance_cube);
        scene_.Add(cube);
    }

private:
    GLhf::InstanceCube instance_cube;
    GLhf::Cube cube;

    GLhf::Texture2D white;
    GLhf::Texture2D brickwall;
};

DECLARE_MAIN(Light);
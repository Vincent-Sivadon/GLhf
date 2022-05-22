/* Supposed to print a orange quad on a green background */

#include <GLhf.h>

#include <iostream>
#include <string>
#include <math.h>

class Light : public GLhf::App
{
public:
    void Startup() override
    {
        /* Texture Init */
        white.Create("../resources/white.png");
        brickwall.Create("../resources/brickwall.jpg");

        cube.SetTexture(brickwall);
        cube.SetColor(1.0f, 0.5f, 0.31f);
        cube.Create();

        light_cube.SetTexture(white);
        light_cube.SetPosition(3.0f, 3.0f, -3.0f);
        light_cube.SetColor(100.0f, 100.0f, 100.0f);
        light_cube.Create();

        scene_.AddCube(cube);
        scene_.AddCube(light_cube);
    }

private:
    GLhf::Cube cube;
    GLhf::Cube light_cube;

    GLhf::Texture2D white;
    GLhf::Texture2D brickwall;
};

DECLARE_MAIN(Light);
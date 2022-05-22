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
        //cube.SetTexture("../resources/brickwall.jpg");
        cube.SetColor(1.0f, 0.5f, 0.31f);
        cube.Create();

        light_cube.SetPosition(3.0f, 3.0f, -3.0f);
        light_cube.SetColor(100.0f, 100.0f, 100.0f);
        light_cube.Create();

        scene_.AddCube(cube);
        scene_.AddCube(light_cube);
    }

private:
    GLhf::Cube cube;
    GLhf::Cube light_cube;
};

DECLARE_MAIN(Light);
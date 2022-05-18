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
        cube.Create();
        //cube.SetTexture("../resources/brickwall.jpg");
        AddShape(&cube);
    }

private:
    GLhf::Cube cube;
};

DECLARE_MAIN(Light);
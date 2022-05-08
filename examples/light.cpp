/* Supposed to print a orange quad on a green background */

#include <GLhf/GLhf.h>

#include <iostream>
#include <string>
#include <math.h>

class Light : public GLhf::App
{
public:
    void Startup() override
    {
        cube.Create();
        disk.SetPosition(1.0,1.0,0.0f);
        disk.Create();
        disk.SetTexture("../../resources/brickwall.jpg");

        AddShape(&cube);
        AddShape(&disk);
    }

private:
    GLhf::Cube cube;
    GLhf::Disk disk;
};

DECLARE_MAIN(Light);
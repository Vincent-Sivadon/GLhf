/* Supposed to print a orange quad on a green background */

#include <GLhf/GLhf.h>

#include <iostream>
#include <string>
#include <math.h>

class OneShape : public GLhf::App
{
public:
    void Startup() override
    {
        disk.pos = glm::vec3(2.0f, 1.0f, 0.0f);
        disk.Create();
        disk.SetTexture("../../resources/brickwall.jpg");
        disk.SetColor(1.0, .5f, 1.0);

        AddShape(&disk);
    }

private:
    GLhf::Disk disk;
};

DECLARE_MAIN(OneShape);
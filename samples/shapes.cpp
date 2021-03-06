/* Supposed to print a orange quad on a green background */

#include <GLhf.h>

#include <iostream>
#include <string>
#include <math.h>

class QuadTest : public GLhf::App
{
public:
    void Startup() override
    {
        disk.color = glm::vec3(1.0f, 1.0f, 1.0f);
        disk.Create();
        disk2.pos = glm::vec3(2.0f, -0.5f, 0.0f);
        disk2.Create();
        disk2.SetTexture("../resources/brickwall.jpg");

        edge.height = 0.05f;
        float dx = disk2.pos.x - disk.pos.x;
        float dy = disk2.pos.y - disk.pos.y;
        edge.width = sqrt(dx * dx + dy * dy);
        edge.pos.x = dx / 2.0f;
        edge.pos.y = dy / 2.0f;
        edge.angle = (float)atan(disk2.pos.y - edge.pos.y);
        // edge.angle = 1.6f;
        edge.color = glm::vec3(1.0f, 0.0f, 0.0f);
        edge.Create();

        edg.SetDisks(&disk, &disk2);
        edg.Create();

        quad.width = 0.5f;
        quad.pos = glm::vec3(2.0f, -1.0f, 0.0f);
        quad.Create();
        quad.SetColor(1.0, 1.0, 1.0);

        quad2.Create();
        quad2.SetPosition(-2.0f, -1.0f);
        quad2.SetColor(1.0, 1.0, 1.0);

        AddShape(&quad2);
        AddShape(&quad);
        AddShape(&disk);
        AddShape(&disk2);
        AddShape(&edg);
    }

private:
    GLhf::Quad quad;
    GLhf::Quad quad2;
    GLhf::Disk disk;
    GLhf::Disk disk2;
    GLhf::Quad edge;
    GLhf::Edge edg;
};

DECLARE_MAIN(QuadTest);
/* Primitive to draw and edge between 2 nodes (Disks) in a graph  */

#pragma once

#include "Quad.h"
#include "Disk.h"

namespace GLhf 
{

    class Edge : public Quad
    {
    private:
        Disk *disk1;
        Disk *disk2;

    public:
        Edge() {}
        Edge(Disk *d1, Disk *d2) : disk1(d1), disk2(d2)
        {
            // Thin quad (line)
            height = 0.05f;

            color = glm::vec3(1.0f, 1.0f, 1.0f);

            UpdatePosition();
        }

        void UpdatePosition()
        {
            // Delta
            float dx = disk2->pos.x - disk1->pos.x;
            float dy = disk2->pos.y - disk1->pos.y;

            // Position
            pos.x = dx / 2.0f;
            pos.y = dy / 2.0f;

            // Width
            width = sqrt(dx * dx + dy * dy);

            // Rotation
            angle = (float)atan(disk2->pos.y - pos.y);
        }
    };

}